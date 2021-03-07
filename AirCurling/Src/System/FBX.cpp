#include "FBX.h"

#pragma region 読み込み
//マテリアル情報の初期化
void InitMaterial(MaterialData* pMaterial, int materialNum)
{
	ZeroMemory(pMaterial, sizeof(MaterialData) * materialNum);

	D3DMATERIAL9 material;
	//材質設定
	//アンビエント(環境)カラー
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	//ディフューズ(素材の)カラー
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;
	//スペキュラー（テカり）カラー
	material.Specular.r = 1.0f;
	material.Specular.g = 1.0f;
	material.Specular.b = 1.0f;
	material.Specular.a = 1.0f;
	material.Power = 15.0f;
	//エミッシブ（発光）
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
	__int8 i;
	for (i = static_cast<__int8>(strlen(m_RootPath)); 0 < i; i--)
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
	//シーンのポリゴンを三角にする
	fbxsdk::FbxGeometryConverter geometryConverter(m_manager);
	//マテリアルと1メッシュ毎に分ける
	geometryConverter.SplitMeshesPerMaterial(m_scene, true);
	geometryConverter.Triangulate(m_scene, true);

	//メッシュ取得
	int meshcount = m_scene->GetSrcObjectCount<FbxMesh>();
	MeshData* pMeshData = (MeshData*)malloc(meshcount * sizeof(MeshData));
	ZeroMemory(pMeshData, meshcount * sizeof(MeshData));

	//マテリアル分のバッファを確保
	int materialcount = meshcount;
	MaterialData* pMaterialData = (MaterialData*)malloc(materialcount * sizeof(MaterialData));
	ZeroMemory(pMaterialData, materialcount * sizeof(MaterialData));


	D3DXMatrixIdentity(&fbxMeshData.fbxinfo.world);
	fbxMeshData.fbxinfo.meshcount = meshcount;
	fbxMeshData.fbxinfo.p_Mesh = pMeshData;
	fbxMeshData.fbxinfo.materialcount = materialcount;
	fbxMeshData.fbxinfo.pMaterial = pMaterialData;
	fbxMeshData.fbxinfo.bonecount = 0;
	ZeroMemory(fbxMeshData.fbxinfo.bone, sizeof(fbxMeshData.fbxinfo.bone));


	//メッシュ単位で展開していく
	for (int i = 0; i < meshcount; i++)
	{
		//i番目のメッシュを取得
		FbxMesh* p_Mesh = m_scene->GetSrcObject<FbxMesh>(i);

		LoadMesh(&pMeshData[i], p_Mesh);
		GetTextureInfo(&pMaterialData[i], p_Mesh);
		pMeshData[i].materialIndex = i;
	}

	importer->Destroy();
	m_scene->Destroy();
	m_manager->Destroy();

	return fbxMeshData;
}

//各情報取得
bool Fbx::LoadMesh(MeshData* pMeshData_, FbxMesh* pMesh_)
{
	//ポリゴン情報取得
	GetIndeces(pMeshData_, pMesh_);
	//頂点情報取得
	GetVertex(pMeshData_, pMesh_);
	//UV情報取得
	GetUV(pMeshData_, pMesh_);
	//法線情報取得
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

//ポリゴン情報取得関数
void Fbx::GetIndeces(MeshData* pMeshData_, FbxMesh* pMesh_)
{
	int polyCount = pMesh_->GetPolygonCount();
	UINT size = (UINT)((polyCount * 3) * sizeof(UINT16));

	pMeshData_->polygonCount = (UINT)polyCount;
	pMeshData_->indexCount = (UINT)(polyCount * 3);
	pMeshData_->pIB = CreateIndexBuffer(nullptr, size);

	UINT16* pIndeces;
	//バッファをロックしてデータを書き込む
	pMeshData_->pIB->Lock(0, size, (void**)&pIndeces, 0);

	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
	{
		pIndeces[polyIdx * 3 + 0] = polyIdx * 3 + 2;
		pIndeces[polyIdx * 3 + 1] = polyIdx * 3 + 1;
		pIndeces[polyIdx * 3 + 2] = polyIdx * 3 + 0;
	}
	pMeshData_->pIB->Unlock();
}

//頂点情報取得関数
void Fbx::GetVertex(MeshData* pMeshData_, FbxMesh* pMesh_) {

	int vertexCount = pMesh_->GetPolygonVertexCount();
	UINT size = (UINT)(vertexCount * sizeof(VERTEX_3D));

	//メッシュに含まれる頂点座標pMesh_を取得
	FbxVector4* vtx = pMesh_->GetControlPoints();
	//メッシュのトランスフォーム
	FbxVector4 T = pMesh_->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = pMesh_->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = pMesh_->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix TRS = FbxAMatrix(T, R, S);
	//!全頂点変換
	for (int v = 0; v < pMesh_->GetControlPointsCount(); v++)
	{
		vtx[v] = TRS.MultT(vtx[v]);
	}

	pMeshData_->vertexCount = (UINT)vertexCount;
	pMeshData_->vertexStride = sizeof(VERTEX_3D);
	pMeshData_->pVB = CreateVertexBuffer(nullptr, size);

	VERTEX_3D* pVertex;
	//バッファをロックしてデータを書き込む
	pMeshData_->pVB->Lock(0, size, (void**)&pVertex, 0);
	int* pIndex = pMesh_->GetPolygonVertices();
	for (int vIdx = 0; vIdx < vertexCount; vIdx++)
	{
		pVertex[vIdx].m_pos.x = static_cast<float>(-vtx[pIndex[vIdx]][0]);
		pVertex[vIdx].m_pos.y = static_cast<float>(vtx[pIndex[vIdx]][1]);
		pVertex[vIdx].m_pos.z = static_cast<float>(vtx[pIndex[vIdx]][2]);
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

//法線情報取得関数
void Fbx::GetNormal(MeshData* pMeshData_, FbxMesh* pMesh_) {
	FbxArray<FbxVector4> normals;

	//法線を取得
	pMesh_->GetPolygonVertexNormals(normals);

	UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);
	VERTEX_3D* pVertex;
	//バッファをロックしてデータを書き込む
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

//UV情報取得関数
void Fbx::GetUV(MeshData* pMeshData_, FbxMesh* pMesh_) {

	FbxStringList uvsetName;
	//メッシュに含まれるUVSet名をすべて取得
	pMesh_->GetUVSetNames(uvsetName);

	FbxArray<FbxVector2> uvSets;
	pMesh_->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvSets);

	UINT size = pMeshData_->vertexCount * sizeof(VERTEX_3D);

	VERTEX_3D* pVertex;
	//バッファをロックしてデータを書き込む
	pMeshData_->pVB->Lock(0, size, (void**)&pVertex, 0);
	for (int vtxIdx = 0; vtxIdx < uvSets.Size(); vtxIdx++)
	{
		FbxVector2& uvSet = uvSets[vtxIdx];

		pVertex[vtxIdx].u = (float)uvSet[0];
		pVertex[vtxIdx].v = (float)(1.0 - uvSet[1]);
	}
	pMeshData_->pVB->Unlock();
}

//テクスチャ情報取得
void Fbx::GetTextureInfo(MaterialData* pMaterialData_, FbxMesh* pMesh_) {

	InitMaterial(pMaterialData_, 1);
	FbxLayerElementMaterial* pElementMaterial = pMesh_->GetElementMaterial();
	if (pElementMaterial)
	{
		//マテリアル解析
		int index = pElementMaterial->GetIndexArray().GetAt(0);
		FbxSurfaceMaterial* pMaterial = pMesh_->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index);

		if (pMaterial)
		{
			//diffuseの情報を取得
			FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

			//テクスチャ読み込み
			const char* filename = nullptr;

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
			if (filename == nullptr) return;

			char* pFileName;
			size_t size = 0;
			FbxUTF8ToAnsi(filename, pFileName, &size);

			//PSDが使用されている場合は読めないのでTGAで試す
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

//FBXモデル描画関数
void Fbx::DrawModel(FbxInfo* pModel)
{
	if (pModel == nullptr) return;
	if (pModel->materialcount == 0) return;

	IDirect3DDevice9* pDevice = Graphics::Instance()->GetD3DDevice();
	pDevice->SetTransform(D3DTS_WORLD, &pModel->world);

	for (UINT matIdx = 0; matIdx < pModel->materialcount; matIdx++)
	{
		MaterialData* pMaterial = &pModel->pMaterial[matIdx];
		//テクスチャーの設定
		pDevice->SetTexture(0, pMaterial->textureData.Texture);

		pDevice->SetMaterial(&pMaterial->material);

		for (UINT meshIdx = 0; meshIdx < pModel->materialcount; meshIdx++)
		{
			MeshData* p_Mesh = &pModel->p_Mesh[meshIdx];
			if (matIdx != p_Mesh->materialIndex)
			{
				continue;
			}

			//頂点バッファの設定
			pDevice->SetStreamSource(0, p_Mesh->pVB, 0, p_Mesh->vertexStride);

			//頂点フォーマットの指定
			pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE);

			if (p_Mesh->pIB)
			{
				//インデックスバッファの設定
				pDevice->SetIndices(p_Mesh->pIB);
				//描画
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, p_Mesh->vertexCount, 0, p_Mesh->polygonCount);
			}
			else
			{
				//描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, p_Mesh->polygonCount);
			}
		}
	}
}

//メッシュデータ解放関数
void Fbx::ReleaseModel(FbxInfo* pModel)
{
	if (pModel == nullptr) return;

	for (UINT i = 0; i < pModel->meshcount; i++)
	{
		SAFE_RELEASE(pModel->p_Mesh[i].pVB);
		SAFE_RELEASE(pModel->p_Mesh[i].pIB);
		free(pModel->p_Mesh[i].vertex);
	}
	for (UINT i = 0; i < pModel->materialcount; i++)
	{
		Graphics::Instance()->ReleaseTexture(&pModel->pMaterial[i].textureData);
	}

	free(pModel->p_Mesh);
	free(pModel->pMaterial);

	ZeroMemory(pModel, sizeof(FbxInfo));
}

//頂点バッファの生成関数
IDirect3DVertexBuffer9* Fbx::CreateVertexBuffer(const void* pVertices_, UINT size_)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = Graphics::Instance()->GetD3DDevice();
	//指定したサイズの頂点バッファを作成
	if (FAILED(pDevice->CreateVertexBuffer(size_, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, nullptr)))
	{
		return nullptr;
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

//インデックスバッファの生成関数
IDirect3DIndexBuffer9* Fbx::CreateIndexBuffer(const UINT16* pIndeces_, UINT size_)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	IDirect3DDevice9* pDevice = Graphics::Instance()->GetD3DDevice();
	//16byte型のインデックスバッファを作成
	if (FAILED(pDevice->CreateIndexBuffer(size_, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, nullptr)))
	{
		return nullptr;
	}
	if (pIndeces_)
	{
		void* pData;
		//バッファをロックしてデータを書き込む
		if (SUCCEEDED(pIndexBuffer->Lock(0, size_, &pData, 0)))
		{
			memcpy(pData, pIndeces_, size_);
			pIndexBuffer->Unlock();
		}
	}
	return pIndexBuffer;
}
