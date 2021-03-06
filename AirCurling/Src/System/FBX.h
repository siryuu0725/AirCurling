﻿/**
 * @file Fbx.h
 * @brief Fbxファイルが扱えるようにする
 * @details 中身：FBXクラス、頂点の情報構造体、ボーン情報構造体、マテリアルの情報構造体
 * メッシュの情報構造体、FBXの情報構造体
**/
#ifndef FBX_H
#define FBX_H
#include <d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include "DirectGraphics.h"
#include <map>
#include <iostream>

//頂点の情報
struct VERTEX_3D {
	D3DXVECTOR3 m_pos;
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
//!マテリアルの情報
struct MaterialData
{
	Graphics::TextureData textureData; //!テクスチャ
	D3DMATERIAL9 material;              //!マテリアル
};

//!メッシュの情報
struct MeshData {
	int polygonCount;         //!ポリゴンの数

	unsigned int vertexCount; //!頂点の数

	int indexCount;           //!頂点インデックスの数

	int vertexStride;         //!1頂点辺りのサイズ

	int materialIndex;        //!マテリアル番号

	VERTEX_3D* vertex;        //!頂点

	IDirect3DVertexBuffer9* pVB; //!頂点バッファ

	IDirect3DIndexBuffer9* pIB;  //!インデックスバッファ 
};

static const int BONE_MAX = 256;

//!アニメーション
struct Motion
{
	Motion()
	{
		ZeroMemory(p_Key, sizeof(p_Key));
	}

	UINT		numFrame;		//!フレーム数	
	D3DXMATRIX* p_Key[BONE_MAX];	//!キーフレーム
};

//!FBXの情報
struct FbxInfo {
	MeshData* p_Mesh;            //!メッシュ
							    
	unsigned int meshcount;     //!メッシュの数 
							    
	MaterialData* pMaterial;    //!マテリアル

	unsigned int materialcount; //!マテリアルの数

	Bone bone[BONE_MAX];        //!ボーン情報
	unsigned int bonecount;

	int	startFrame;             //!開始フレーム

	D3DXMATRIX	world;          //!ワールドマトリックス
};

struct FBXMeshData
{
	FbxInfo fbxinfo;
};

/**
* FBXファイルクラス
*/
class Fbx
{
public:
	Fbx() {}
	~Fbx() {}

	/**
	 * @brief  FBXファイル読み込み関数
	 * @param[in] file_name ファイルパス
	 * @details 読み込んだファイルのメッシュデータを返す
	 */
	FBXMeshData LoadFbx(const char* file_name);

	/**
	 * @brief  メッシュデータ解析関数
	 * @param[in] pMeshData_ メッシュデータ
	 * @param[in] pMesh_ メッシュ単位で展開後のデータ
	 * @details 頂点、法線、UV情報などの解析を行う
	 */
	bool LoadMesh(MeshData* pMeshData_, FbxMesh* pMesh_);

	/**
	 * @brief  ポリゴン情報取得関数
	 * @param[in] pMeshData_ メッシュデータ
	 * @param[in] pMesh_ メッシュ単位で展開後のデータ
	 */
	void LoadIndeces(MeshData* pMeshData_, FbxMesh* pMesh_);

	/**
	 * @brief  頂点情報取得関数
	 * @param[in] pMeshData_ メッシュデータ
	 * @param[in] pMesh_ メッシュ単位で展開後のデータ
	 */
	void LoadVertex(MeshData* pMeshData_, FbxMesh* pMesh_);

	/**
	 * @brief 法線情報取得関数
	 * @param[in] pMeshData_ メッシュデータ
	 * @param[in] pMesh_ メッシュ単位で展開後のデータ
	 */
	void LoadNormal(MeshData* pMeshData_, FbxMesh* pMesh_);
	
	/**
	 * @brief  UV情報取得関数
	 * @param[in] pMeshData_ メッシュデータ
	 * @param[in] pMesh_ メッシュ単位で展開後のデータ
	 */
	void LoadUV(MeshData* pMeshData_, FbxMesh* pMesh_);

	/**
	 * @brief テクスチャ情報取得
	 * @param[in] stage_id_ 選択ステージ名(例"Stage1")
	 */
	void LoadTextureInfo(MaterialData* pMaterialData_, FbxMesh* pMesh_);

	/**
	 * @brief  FBXモデル描画関数
	 * @param[in] pModel 描画させるFBXモデル情報
	 */
	void DrawModel(FbxInfo* pModel);

	/**
	 * @brief  メッシュデータ解放関数
	 * @param[in] pModel 解放するFBXモデル情報
	 */
	void ReleaseModel(FbxInfo* pModel);


	/**
	 * @brief  頂点バッファの生成関数
	 */
	IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices_, UINT size_);

	/**
	 * @brief  インデックスバッファの生成関数
	 */
	IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces_, UINT size_);

private:
	char m_RootPath[MAX_PATH]; // ファイルのパス
};

#endif