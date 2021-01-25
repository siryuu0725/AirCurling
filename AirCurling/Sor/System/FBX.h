#ifndef FBX_H
#define FBX_H
#include <d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include "Graphics.h"
#include <map>
#include <iostream>

//頂点の情報
struct VERTEX_3D {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR    col;
	float u, v;

	/* スキンメッシュ用 */
	BYTE index[4];
	float weight[4];

};

// ボーン情報
struct Bone
{
	char		name[64];
	D3DXMATRIX	offset;
	D3DXMATRIX	transform;
};
//マテリアルの情報
struct MaterialData
{
	/* テクスチャ */
	Graphics::TEXTURE_DATA textureData;

	/* マテリアル */
	D3DMATERIAL9 material;
};

//メッシュの情報
struct MeshData {
	/* ポリゴンの数 */
	int polygonCount;

	/* 頂点の数 */
	int vertexCount;

	/* 頂点インデックスの数 */
	int indexCount;

	/* 1頂点辺りのサイズ */
	int vertexStride;

	/* マテリアル番号 */
	int materialIndex;

	int uvSetCount;
	/* 頂点 */
	VERTEX_3D* vertex;

	/* 頂点バッファ */
	IDirect3DVertexBuffer9* pVB;

	/* インデックスバッファ */
	IDirect3DIndexBuffer9* pIB;
};
static const int BONE_MAX = 256;

//	アニメーション
struct Motion
{
	Motion()
	{
		ZeroMemory(pKey, sizeof(pKey));
	}

	UINT		numFrame;		// フレーム数	
	D3DXMATRIX* pKey[BONE_MAX];	// キーフレーム
};



//FBXの情報
struct FbxInfo {
	/* メッシュ */
	MeshData* pMesh;

	/* メッシュの数 */
	int meshcount;

	/* マテリアル */
	MaterialData* pMaterial;

	/* マテリアルの数 */
	int materialcount;

	/* ボーン情報 */
	Bone bone[BONE_MAX];
	int bonecount;

	/* 開始フレーム */
	int	startFrame;

	/* モーション */
	std::map<std::string, Motion>* pMotion;

	/* ワールドマトリックス */
	D3DXMATRIX	world;
};

struct FBXMeshData
{
	FbxInfo fbxinfo;

	/* モーション名 */
	char	motion[64];

	/* フレーム */
	float	frame;
};



enum class Object
{
	PLAYER,
	MaxObject
};


/**
*@clss  FBXファイルクラス
*/

class Fbx
{
public:
	Fbx() {}
	~Fbx() {}

	//FBX準備
	// Keyで読み込むモデルを設定する
	FBXMeshData LoadFbx(const char* file_name);

	bool LoadMesh(MeshData* pMeshData_, FbxMesh* pMesh_);

	void ReleaseFbxMesh(FBXMeshData* pData_);

	void GetIndeces(MeshData* pMeshData_, FbxMesh* pMesh_);
	//頂点情報取得
	void GetVertex(MeshData* pMeshData_, FbxMesh* pMesh_);
	//法線情報取得
	void GetNormal(MeshData* pMeshData_, FbxMesh* pMesh_);
	//UV座標の取得
	void GetUV(MeshData* pMeshData_, FbxMesh* pMesh_);
	//カラー取得
	void GetColor(MeshData* pMeshData_, FbxMesh* pMesh_);

	int FindBone(FbxInfo* pModel_, const char* pName_);

	void GetBone(FbxInfo* pModel_, MeshData* pMeshData_, FbxMesh* pMesh_);

	void GetKeyFrames(FbxInfo* pModel_, std::string name_, int bone_, FbxNode* pBoneNode_);

	void Play(FBXMeshData* pData_, std::string name_);
	//テクスチャ情報取得
	void GetTextureInfo(MaterialData* pMaterialData_, FbxMesh* pMesh_);
	//アニメーション無し
	void RenderFbxMesh(FBXMeshData* pData_);

	void DrawModel(FbxInfo* pModel);

	void Skinning(FBXMeshData* pData_);

	void MatrixInterporate(D3DXMATRIX& out_, D3DXMATRIX& A_, D3DXMATRIX B_, float rate_);

	void ReleaseModel(FbxInfo* pModel);

	void Animate(FBXMeshData* pData_, float sec_);

	void ResetAnimate(FBXMeshData* pData_);

	// 頂点バッファの生成
	IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices_, UINT size_);
	// インデックスバッファの生成
	IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces_, UINT size_);


private:

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;

	char m_RootPath[MAX_PATH]; // ファイルのパス
};

#endif