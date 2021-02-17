#include "FBX.h"

#pragma region 読み込み
// マテリアル情報の初期化
void InitMaterial(MaterialData* pMaterial, int materialNum)
{
	ZeroMemory(pMaterial, sizeof(MaterialData) * materialNum);

	D3DMATERIAL9 material;
	//	材質設定
	//	アンビエント(環境)カラー
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	//	ディフューズ(素材の)カラー
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;
	//	スペキュラー（テカり）カラー
	material.Specular.r = 1.0f;
	material.Specular.g = 1.0f;
	material.Specular.b = 1.0f;
	material.Specular.a = 1.0f;
	material.Power = 15.0f;
	//	エミッシブ（発光）
	material.Emissive.r = 0.0f;
	material.Emissive.g = 0.0f;
	material.Emissive.b = 0.0f;
	material.Emissive.a = 0.0f;

	for (int i = 0; i < materialNum; i++)
	{
		pMaterial[i].material = material;
	}
}

//FBXのマネージャー作成
FBXMeshData Fbx::LoadFbx(const char* file_name)
{
	FBXMeshData fbxMeshData;
	ZeroMemory(&fbxMeshData, sizeof(fbxMeshData));

	strcpy_s(m_RootPath, file_name);
	UINT i;
	for (i = strlen(m_RootPath); 0 < i; i--)
	{
		if (m_RootPath[i] == '/') break;
	}
	m_RootPath[i] = '\0';

	//FBXのマネージャー作成
	FbxManager* m_manager = FbxManager::Create();
	//インポーター作成
	FbxImporter* importer = FbxImporter::Create(m_manager, "");
	//シーン作成
	FbxScene* m_scene = FbxScene::Create(m_manager, "");
	
	//filePathに指定したファイルを読み込む
	importer->Initialize(file_name);
	//シーンにインポートしたファイルを渡す
	bool result = importer->Import(m_scene);
	//インポーターの役目は終わりなので解放する
	


	//シーンのポリゴンを三角にする
	fbxsdk::FbxGeometryConverter geometryConverter(m_manager);
	// マテリアルと1メッシュ毎に分ける
	geometryConverter.SplitMeshesPerMaterial(m_scene, true);
	geometryConverter.Triangulate(m_scene, true);

	//メッシュ取得
	int meshcount = m_scene->GetSrcObjectCount<FbxMesh>();
	MeshData* pMeshData = (MeshData*)malloc(meshcount * sizeof(MeshData));
	ZeroMemory(pMeshData, meshcount * sizeof(MeshData));

	// マテリアル分のバッファを確保
	int materialcount = meshcount;
	MaterialData* pMaterialData = (MaterialData*)malloc(materialcount * sizeof(MaterialData));
	ZeroMemory(pMaterialData, materialcount * sizeof(MaterialData));


	D3DXMatrixIdentity(&fbxMeshData.fbxinfo.world);
	fbxMeshData.fbxinfo.meshcount = meshcount;
	fbxMeshData.fbxinfo.pMesh = pMeshData;
	fbxMeshData.fbxinfo.materialcount = materialcount;
	fbxMeshData.fbxinfo.pMaterial = pMaterialData;
	fbxMeshData.fbxinfo.bonecount = 0;
	ZeroMemory(fbxMeshData.fbxinfo.bone, sizeof(fbxMeshData.fbxinfo.bone));

	//	モーション情報取得
	FbxArray<FbxString*> names;
	m_scene->FillAnimStackNameArray(names);

	int StartFrame = 0;
	if (names != NULL) {
		//	モーションが存在するとき
		FbxTakeInfo* take = m_scene->GetTakeInfo(names[0]->Buffer());
		FbxLongLong start = take->mLocalTimeSpan.GetStart().Get();
		FbxLongLong stop = take->mLocalTimeSpan.GetStop().Get();
		FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);
		StartFrame = (int)(start / fps60);

		fbxMeshData.fbxinfo.pMotion = new std::map<std::string, Motion>();
		(*fbxMeshData.fbxinfo.pMotion)["default"].numFrame = (int)((stop - start) / fps60);
	}
	fbxMeshData.fbxinfo.startFrame = StartFrame;

	// メッシュ単位で展開していく
	for (int i = 0; i < meshcount; i++)
	{
		FbxMesh* pMesh = m_scene->GetSrcObject<FbxMesh>(i);

		LoadMesh(&pMeshData[i], pMesh);
		GetTextureInfo(&pMaterialData[i], pMesh);
		GetBone(&fbxMeshData.fbxinfo, &pMeshData[i], pMesh);
		pMeshData[i].materialIndex = i;
	}

	importer->Destroy();
	m_scene->Destroy();
	m_manager->Destroy();

	Play(&fbxMeshData, "default");

	return fbxMeshData;

}

void Fbx::Play(FBXMeshData* pData_, std::string name_)
{
	if (pData_ == nullptr) return;
	strcpy_s(pData_->motion, name_.c_str());
	pData_->frame = 0.0f;
}

void Fbx::ReleaseFbxMesh(FBXMeshData* pData_)
{
	if (pData_ == nullptr) return;

	ReleaseModel(&pData_->fbxinfo);
}

//各情報取得
bool Fbx::LoadMesh(MeshData* pMeshData_, FbxMesh* pMesh_)
{
	GetIndeces(pMeshData_, pMesh_);

	GetVertex(pMeshData_, pMesh_);
	GetUV(pMeshData_, pMesh_);
	GetColor(pMeshData_, pMesh_);
	GetNormal(pMeshData_, pMesh_);

	int vertexNum = pMesh_->GetPolygonVertexCount();
	UINT size = (UINT)(vertexNum * sizeof(VERTEX_3D));
	VERTEX_3D* vertex;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVB->Lock(0, size, (void**)&vertex, 0);

	pMeshData_->vertex = (VERTEX_3D*)malloc(size);
	memcpy(pMeshData_->vertex, vertex, size);

	pMeshData_->pVB->Unlock();

	return true;
}

//ポリゴン情報
void Fbx::GetIndeces(MeshData* pMeshData_, FbxMesh* pMesh_)
{
	int polyCount = pMesh_->GetPolygonCount();
	UINT size = (UINT)((polyCount * 3) * sizeof(UINT16));

	pMeshData_->polygonCount = (UINT)polyCount;
	pMeshData_->indexCount = (UINT)(polyCount * 3);
	pMeshData_->pIB = CreateIndexBuffer(NULL, size);

	UINT16* pIndeces;
	// バッファをロックしてデータを書き込む
	pMeshData_->pIB->Lock(0, size, (void**)&pIndeces, 0);

	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
	{
		pIndeces[polyIdx * 3 + 0] = polyIdx * 3 + 2;
		pIndeces[polyIdx * 3 + 1] = polyIdx * 3 + 1;
		pIndeces[polyIdx * 3 + 2] = polyIdx * 3 + 0;
	}
	pMeshData_->pIB->Unlock();
}
//頂点情報
void Fbx::GetVertex(MeshData* pMeshData_, FbxMesh* pMesh_) {

	int vertexCount = pMesh_->GetPolygonVertexCount();
	UINT size = (UINT)(vertexCount * sizeof(VERTEX_3D));

	//メッシュに含まれる頂点座標pMesh_を取得
	FbxVector4* vtx = pMesh_->GetControlPoints();
	// メッシュのトランスフォーム
	FbxVector4 T = pMesh_->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = pMesh_->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = pMesh_->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix TRS = FbxAMatrix(T, R, S);
	//	全頂点変換
	for (int v = 0; v < pMesh_->GetControlPointsCount(); v++)
	{
		vtx[v] = TRS.MultT(vtx[v]);
	}

	pMeshData_->vertexCount = (UINT)vertexCount;
	pMeshData_->vertexStride = sizeof(VERTEX_3D);
	pMeshData_->pVB = CreateVertexBuffer(NULL, size);

	VERTEX_3D* pVertex;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVB->Lock(0, size, (void**)&pVertex, 0);
	int* pIndex = pMesh_->GetPolygonVertices();
	for (int vIdx = 0; vIdx < vertexCount; vIdx++)
	{
		pVertex[vIdx].pos.x = -vtx[pIndex[vIdx]][0];
		pVertex[vIdx].pos.y = vtx[pIndex[vIdx]][1];
		pVertex[vIdx].pos.z = vtx[pIndex[vIdx]][2];
		pVertex[vIdx].nor.x = 0.0f;
		pVertex[vIdx].nor.y = 1.0f;
		pVertex[vIdx].nor.z = 0.0f;
		pVertex[vIdx].u = 0.0f;
		pVertex[vIdx].v = 0.0f;
		pVertex[vIdx].col = 0xffffff;
		ZeroMemory(pVertex[vIdx].index, sizeof(pVertex[vIdx].index));
		ZeroMemory(pVertex[vIdx].weight, sizeof(pVertex[vIdx].weight));
	}

	pMeshData_->pVB->Unlock();

}
//法線情報取得
void Fbx::GetNormal(MeshData* pMeshData_, FbxMesh* pMesh_) {
	FbxArray<FbxVector4> normals;

	//法線を取得
	pMesh_->GetPolygonVertexNormals(normals);

	UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);
	VERTEX_3D* pVertex;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVB->Lock(0, size, (void**)&pVertex, 0);

	//法線の数を取得
	//int normalCount = normals.Size();
	for (int vtxIdx = 0; vtxIdx < normals.Size(); vtxIdx++)
	{
		FbxVector4& normal = normals[vtxIdx];
		//頂点インデックスに対応した頂点に値を代入
		pVertex[vtxIdx].nor.x = (float)normal[0];
		pVertex[vtxIdx].nor.y = (float)normal[1];
		pVertex[vtxIdx].nor.z = (float)normal[2];
	}
	pMeshData_->pVB->Unlock();

}
//UV情報取得
void Fbx::GetUV(MeshData* pMeshData_, FbxMesh* pMesh_) {

	FbxStringList uvsetName;
	//メッシュに含まれるUVSet名をすべて取得
	pMesh_->GetUVSetNames(uvsetName);

	FbxArray<FbxVector2> uvSets;
	pMesh_->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvSets);

	UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);

	VERTEX_3D* pVertex;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVB->Lock(0, size, (void**)&pVertex, 0);
	for (int vtxIdx = 0; vtxIdx < uvSets.Size(); vtxIdx++)
	{
		FbxVector2& uvSet = uvSets[vtxIdx];

		pVertex[vtxIdx].u = (float)uvSet[0];
		pVertex[vtxIdx].v = (float)(1.0 - uvSet[1]);
	}
	pMeshData_->pVB->Unlock();
}
//カラー情報取得
void Fbx::GetColor(MeshData* pMeshData_, FbxMesh* pMesh_)
{
	int colorElementCount = pMesh_->GetElementVertexColorCount();
	if (colorElementCount == 0) return;

	FbxLayerElementVertexColor* pColor = pMesh_->GetElementVertexColor(0);

	FbxLayerElement::EMappingMode mapMode = pColor->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = pColor->GetReferenceMode();

	if (mapMode == FbxLayerElement::eByPolygonVertex)
	{
		if (refMode == FbxLayerElement::eIndexToDirect)
		{
			UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);
			VERTEX_3D* pVertex;
			// バッファをロックしてデータを書き込む
			pMeshData_->pVB->Lock(0, size, (void**)&pVertex, 0);

			FbxLayerElementArrayTemplate<FbxColor>& colors = pColor->GetDirectArray();
			FbxLayerElementArrayTemplate<int>& indeces = pColor->GetIndexArray();
			for (int i = 0; i < indeces.GetCount(); i++)
			{
				const FbxColor& color = colors.GetAt(indeces.GetAt(i));
				DWORD a = (DWORD)(color.mAlpha * 255.0);
				DWORD r = (DWORD)(color.mRed * 255.0);
				DWORD g = (DWORD)(color.mGreen * 255.0);
				DWORD b = (DWORD)(color.mBlue * 255.0);

				pVertex[i].col = (a << 24) + (r << 16) + (g << 8) + (b);
			}
			pMeshData_->pVB->Unlock();
		}
	}
}
//骨情報検索
int Fbx::FindBone(FbxInfo* pModel_, const char* pName_)
{
	for (UINT boneIdx = 0; boneIdx < pModel_->bonecount; boneIdx++)
	{
		if (strcmp(pModel_->bone[boneIdx].name, pName_) == 0)
		{
			return (int)boneIdx;
		}
	}
	return -1;
}
//骨情報取得
void Fbx::GetBone(FbxInfo* pModel_, MeshData* pMeshData_, FbxMesh* pMesh_)
{
	// スキン情報の有無
	int skinCount = pMesh_->GetDeformerCount(FbxDeformer::eSkin);
	if (skinCount <= 0)
	{
		return;
	}
	int vertexcount = pMeshData_->vertexCount;
	UINT size = (UINT)(vertexcount * sizeof(VERTEX_3D));

	VERTEX_3D* pVertex;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVB->Lock(0, size, (void**)&pVertex, 0);

	FbxSkin* pSkin = (FbxSkin*)pMesh_->GetDeformer(0, FbxDeformer::eSkin);
	// ボーン数
	int nBone = pSkin->GetClusterCount();
	//	全ボーン情報取得
	for (int bone = 0; bone < nBone; bone++)
	{
		//	ボーン情報取得
		FbxCluster* pCluster = pSkin->GetCluster(bone);
		FbxAMatrix trans;
		pCluster->GetTransformMatrix(trans);
		trans.mData[0][1] *= -1;
		trans.mData[0][2] *= -1;
		trans.mData[1][0] *= -1;
		trans.mData[2][0] *= -1;
		trans.mData[3][0] *= -1;

		//	ボーン名取得
		const char* pName = pCluster->GetLink()->GetName();

		Bone* pBone;
		//	ボーン検索
		int bone_no = FindBone(pModel_, pName);
		if (bone_no != -1)
		{
			pBone = &pModel_->bone[bone_no];
		}
		else
		{
			bone_no = pModel_->bonecount;
			pBone = &pModel_->bone[bone_no];
			pModel_->bonecount++;

			strcpy_s(pBone->name, pName);
			//	オフセット行列作成
			FbxAMatrix LinkMatrix;
			pCluster->GetTransformLinkMatrix(LinkMatrix);
			LinkMatrix.mData[0][1] *= -1;
			LinkMatrix.mData[0][2] *= -1;
			LinkMatrix.mData[1][0] *= -1;
			LinkMatrix.mData[2][0] *= -1;
			LinkMatrix.mData[3][0] *= -1;

			FbxAMatrix Offset = LinkMatrix.Inverse() * trans;
			FbxDouble* OffsetM = (FbxDouble*)Offset;

			//	オフセット行列保存
			for (int i = 0; i < 16; i++)
			{
				pBone->offset.m[i / 4][i % 4] = (float)OffsetM[i];
			}
			//	キーフレーム読み込み
			GetKeyFrames(pModel_, "default", bone_no, pCluster->GetLink());
		}

		//	ウェイト読み込み
		int weightCount = pCluster->GetControlPointIndicesCount();
		int* pWeightIndex = pCluster->GetControlPointIndices();
		double* wgt = pCluster->GetControlPointWeights();

		int* index = pMesh_->GetPolygonVertices();


		for (int i = 0; i < weightCount; i++)
		{
			int wgtIdx2 = pWeightIndex[i];
			//	全ポリゴンからwgtIdx2番目の頂点検索
			for (int vtxIdx = 0; vtxIdx < vertexcount; vtxIdx++)
			{
				if (index[vtxIdx] != wgtIdx2) continue;
				//	頂点にウェイト保存
				int weightCount;
				for (weightCount = 0; weightCount < 4; weightCount++)
				{
					if (pVertex[vtxIdx].weight[weightCount] <= 0.0f)
					{
						break;
					}
				}
				if (4 <= weightCount) continue;

				pVertex[vtxIdx].index[weightCount] = bone_no;
				pVertex[vtxIdx].weight[weightCount] = (float)wgt[i];
			}
		}
	}
	//	ウェイト正規化
	// ５本以上にまたっがてる場合のため
	for (int vtxIdx = 0; vtxIdx < vertexcount; vtxIdx++)
	{
		float n = 0;
		int weightCount;
		//	頂点のウェイトの合計値
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			if (pVertex[vtxIdx].weight[weightCount] <= 0.0f)
			{
				break;
			}
			n += pVertex[vtxIdx].weight[weightCount];
		}
		//	正規化
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			pVertex[vtxIdx].weight[weightCount] /= n;
		}
	}
	pMeshData_->pVB->Unlock();
}

void Fbx::GetKeyFrames(FbxInfo* pModel_, std::string name_, int bone_, FbxNode* pBoneNode_)
{
	//	メモリ確保
	Motion* pMotion = &(*pModel_->pMotion)[name_];
	pMotion->pKey[bone_] = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * (pMotion->numFrame + 1));

	double time = (double)pModel_->startFrame * (1.0 / 60);
	FbxTime T;
	for (UINT f = 0; f < pMotion->numFrame; f++)
	{
		T.SetSecondDouble(time);
		//	T秒の姿勢行列をGet
		FbxMatrix m = pBoneNode_->EvaluateGlobalTransform(T);
		m.mData[0][1] *= -1;// _12
		m.mData[0][2] *= -1;// _13
		m.mData[1][0] *= -1;// _21
		m.mData[2][0] *= -1;// _31
		m.mData[3][0] *= -1;// _41

		FbxDouble* mat = (FbxDouble*)m;
		for (int i = 0; i < 16; i++)
		{
			pMotion->pKey[bone_][f].m[i / 4][i % 4] = (float)mat[i];
		}

		time += 1.0 / 60.0;
	}
}

//テクスチャ情報取得
void Fbx::GetTextureInfo(MaterialData* pMaterialData_, FbxMesh* pMesh_) {

	InitMaterial(pMaterialData_, 1);
	FbxLayerElementMaterial* pElementMaterial = pMesh_->GetElementMaterial();
	if (pElementMaterial)
	{
		// マテリアル解析
		int index = pElementMaterial->GetIndexArray().GetAt(0);
		FbxSurfaceMaterial* pMaterial = pMesh_->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index);

		if (pMaterial)
		{
			//diffuseの情報を取得
			FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

			//	テクスチャ読み込み
			const char* filename = NULL;

			//テクスチャの数を取得する
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
			if (fileTextureCount > 0)
			{
				//テクスチャを取得する
				FbxFileTexture* FileTex = prop.GetSrcObject<FbxFileTexture>(0);
				filename = FileTex->GetFileName();
			}
			else
			{
				//レイヤテクスチャの数を取得する
				int numLayer = prop.GetSrcObjectCount<FbxLayeredTexture>();
				if (numLayer > 0)
				{
					//レイヤテクスチャを取得する
					FbxLayeredTexture* LayerTex = prop.GetSrcObject<FbxLayeredTexture>(0);
					//テクスチャを取得する
					FbxFileTexture* FileTex = LayerTex->GetSrcObject<FbxFileTexture>(0);
					filename = FileTex->GetFileName();
				}
			}
			if (filename == NULL) return;

			//	テクスチャーの取得
			char* pFileName;
			size_t size = 0;
			FbxUTF8ToAnsi(filename, pFileName, &size);

			// PSDが使用されている場合は読めないのでTGAで試す
			char* ext = (char*)strstr(pFileName, ".psd");
			if (ext)
			{
				strcpy_s(ext, 5, ".tga");
			}

			char path[MAX_PATH];
			if (strstr(pFileName, "\\"))
			{
				strcpy_s(path, pFileName);
			}
			else
			{
				strcpy_s(path, m_RootPath);
				strcat_s(path, "/texture/");
				strcat_s(path, pFileName);
			}
			Graphics::Instance()->LoadTexture(path, &pMaterialData_->textureData);

			FbxFree(pFileName);
		}
	}
}
#pragma endregion

void Fbx::RenderFbxMesh(FBXMeshData* pData_)
{
	if (pData_ == nullptr) return;

	Skinning(pData_);

	DrawModel(&pData_->fbxinfo);
}

void Fbx::DrawModel(FbxInfo* pModel)
{
	if (pModel == NULL) return;
	if (pModel->materialcount == 0) return;

	IDirect3DDevice9* pDevice = Graphics::Instance()->GetD3DDevice();
	pDevice->SetTransform(D3DTS_WORLD, &pModel->world);

	for (UINT matIdx = 0; matIdx < pModel->materialcount; matIdx++)
	{
		MaterialData* pMaterial = &pModel->pMaterial[matIdx];
		// テクスチャーの設定
		pDevice->SetTexture(0, pMaterial->textureData.Texture);

		pDevice->SetMaterial(&pMaterial->material);
		for (UINT meshIdx = 0; meshIdx < pModel->materialcount; meshIdx++)
		{
			MeshData* pMesh = &pModel->pMesh[meshIdx];
			if (matIdx != pMesh->materialIndex)
			{
				continue;
			}

			// 頂点バッファの設定
			pDevice->SetStreamSource(0, pMesh->pVB, 0, pMesh->vertexStride);

			// 頂点フォーマットの指定
			pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE);

			if (pMesh->pIB)
			{
				// インデックスバッファの設定
				pDevice->SetIndices(pMesh->pIB);
				// 描画
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pMesh->vertexCount, 0, pMesh->polygonCount);
			}
			else
			{
				// 描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pMesh->polygonCount);
			}
		}
	}
}

void Fbx::Skinning(FBXMeshData* pData_)
{
	if (!pData_->fbxinfo.pMotion) return;

	Motion* pMotion = &(*pData_->fbxinfo.pMotion)[pData_->motion];
	if (pMotion == nullptr) return;
	if (pMotion->numFrame < 0) return;

	float Frame = pData_->frame;
	//	配列用変数
	int f = (int)Frame;
	//	行列準備
	D3DXMATRIX KeyMatrix[256];
	for (UINT b = 0; b < pData_->fbxinfo.bonecount; b++)
	{
		if (!pMotion->pKey[b]) continue;
		//	行列補間
		D3DXMATRIX m;
		MatrixInterporate(m, pMotion->pKey[b][f], pMotion->pKey[b][f + 1], Frame - (int)Frame);
		pData_->fbxinfo.bone[b].transform = m;
		//	キーフレーム
		KeyMatrix[b] = pData_->fbxinfo.bone[b].offset * m;
	}

	//	頂点変形
	for (UINT meshIdx = 0; meshIdx < pData_->fbxinfo.meshcount; meshIdx++)
	{
		MeshData* pMeshData = &pData_->fbxinfo.pMesh[meshIdx];
		VERTEX_3D* pSrcVertex = pMeshData->vertex;

		UINT size = (UINT)(pMeshData->vertexCount * sizeof(VERTEX_3D));
		VERTEX_3D* pVertex;
		// バッファをロックしてデータを書き込む
		pMeshData->pVB->Lock(0, size, (void**)&pVertex, 0);
		for (UINT v = 0; v < pMeshData->vertexCount; v++)
		{
			//	頂点 * ボーン行列
			// b = v番目の頂点の影響ボーン[n]
			if (pVertex[v].weight[0] <= 0) continue;

			pVertex[v].pos.x = 0;
			pVertex[v].pos.y = 0;
			pVertex[v].pos.z = 0;

			//	影響個数分ループ
			for (int n = 0; n < 4; n++)
			{
				if (pVertex[v].weight[n] <= 0) break;

				int b = (int)pVertex[v].index[n];

				float x = pSrcVertex[v].pos.x;
				float y = pSrcVertex[v].pos.y;
				float z = pSrcVertex[v].pos.z;
				//	座標を影響力分移動
				pVertex[v].pos.x += (x * KeyMatrix[b]._11 + y * KeyMatrix[b]._21 + z * KeyMatrix[b]._31 + 1 * KeyMatrix[b]._41) * pVertex[v].weight[n];
				pVertex[v].pos.y += (x * KeyMatrix[b]._12 + y * KeyMatrix[b]._22 + z * KeyMatrix[b]._32 + 1 * KeyMatrix[b]._42) * pVertex[v].weight[n];
				pVertex[v].pos.z += (x * KeyMatrix[b]._13 + y * KeyMatrix[b]._23 + z * KeyMatrix[b]._33 + 1 * KeyMatrix[b]._43) * pVertex[v].weight[n];

				float nx = pSrcVertex[v].nor.x;
				float ny = pSrcVertex[v].nor.y;
				float nz = pSrcVertex[v].nor.z;
				//	法線を影響力分変換
				pVertex[v].nor.x += (nx * KeyMatrix[b]._11 + ny * KeyMatrix[b]._21 + nz * KeyMatrix[b]._31) * pVertex[v].weight[n];
				pVertex[v].nor.y += (nx * KeyMatrix[b]._12 + ny * KeyMatrix[b]._22 + nz * KeyMatrix[b]._32) * pVertex[v].weight[n];
				pVertex[v].nor.z += (nx * KeyMatrix[b]._13 + ny * KeyMatrix[b]._23 + nz * KeyMatrix[b]._33) * pVertex[v].weight[n];
			}
		}
		pMeshData->pVB->Unlock();
	}
}

void Fbx::MatrixInterporate(D3DXMATRIX& out_, D3DXMATRIX& A_, D3DXMATRIX B_, float rate_)
{
	out_ = A_ * (1.0f - rate_) + B_ * rate_;
}

void Fbx::ReleaseModel(FbxInfo* pModel)
{
	if (pModel == nullptr) return;

	for (UINT i = 0; i < pModel->meshcount; i++)
	{
		SAFE_RELEASE(pModel->pMesh[i].pVB);
		SAFE_RELEASE(pModel->pMesh[i].pIB);
		free(pModel->pMesh[i].vertex);
	}
	for (UINT i = 0; i < pModel->materialcount; i++)
	{
		Graphics::Instance()->ReleaseTexture(&pModel->pMaterial[i].textureData);
	}
	if (pModel->pMotion)
	{
		std::map<std::string, Motion>::iterator it;
		for (it = pModel->pMotion->begin(); it != pModel->pMotion->end(); it++)
		{
			for (int i = 0; i < 256; i++)
			{
				if (it->second.pKey[i])
				{
					free(it->second.pKey[i]);
				}
			}
		}
		delete pModel->pMotion;
	}
	free(pModel->pMesh);
	free(pModel->pMaterial);

	ZeroMemory(pModel, sizeof(FbxInfo));
}

void Fbx::Animate(FBXMeshData* pData_, float sec_)
{
	if (pData_ == nullptr) return;
	if (pData_->fbxinfo.pMotion == nullptr) return;
	//	モーション時間の更新
	pData_->frame += sec_ * 120.0f;

	//	ループチェック
	if (pData_->frame >= (*pData_->fbxinfo.pMotion)[pData_->motion].numFrame - 1)
	{
		// ループ
		pData_->frame = 0;
	}
}

void Fbx::ResetAnimate(FBXMeshData* pData_)
{
	if (pData_ == nullptr) return;
	pData_->frame = 0;
}

IDirect3DVertexBuffer9* Fbx::CreateVertexBuffer(const void* pVertices_, UINT size_)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = Graphics::Instance()->GetD3DDevice();
	// 指定したサイズの頂点バッファを作成
	if (FAILED(pDevice->CreateVertexBuffer(size_, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}

	if (pVertices_)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pVertexBuffer->Lock(0, size_, &pData, 0)))
		{
			memcpy(pData, pVertices_, size_);
			pVertexBuffer->Unlock();
		}
	}
	return pVertexBuffer;

}

IDirect3DIndexBuffer9* Fbx::CreateIndexBuffer(const UINT16* pIndeces_, UINT size_)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	IDirect3DDevice9* pDevice = Graphics::Instance()->GetD3DDevice();
	// 16byte型のインデックスバッファを作成
	if (FAILED(pDevice->CreateIndexBuffer(size_, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL)))
	{
		return NULL;
	}
	if (pIndeces_)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pIndexBuffer->Lock(0, size_, &pData, 0)))
		{
			memcpy(pData, pIndeces_, size_);
			pIndexBuffer->Unlock();
		}
	}
	return pIndexBuffer;
}
