#ifndef FBXCONTROLLER_H_
#define FBXCONTROLLER_H_
#include "FBX.h"

/**
*@clss  FBX管理クラス
*/

class FbxController
{
public:
	static FbxController* Instance();

	FbxController();
	~FbxController();

	/**
	 * @brief  Meshデータセット関数
	 * @param (key_) オブジェクトのキー
	 * @param (pFilename_) 読み込むFbxファイルのパス
	 * @detail 引数のキーのメッシュデータに引数のパスのFbxデータを代入する
	 */
	FBXMeshData LoadFbxMesh(std::string key_, const char* pFilename_);

	/**
	 * @brief  メッシュデータ読み込みまとめ関数
	 * @detail 各オブジェクトのLoadFbxMesh関数をまとめたもの
	 */
	void LoadFbx();

	/**
	 * @brief  メッシュデータ解放関数
	 * @param (key_) オブジェクトのキー
	 */
	void ReleaseFbxMesh(std::string key_);

	/**
	 * @brief  Fbfファイル描画関数
	 * @detail 各オブジェクトのLoadFbxMesh関数をまとめたもの
	 * @param (key_) オブジェクトのキー
	 * @param (mat_world_) オブジェクトのワールド座標
	 */
	void DrawFbx(std::string key_, D3DXMATRIX& mat_world_);

	/**
	 * @brief  メッシュデータ解放まとめ関数
	 * @detail 各オブジェクトのLoadFbxMesh関数をまとめたもの
	 */
	FBXMeshData GetMeshData(std::string key_) { return m_MeshData[key_]; }
private:
	static FbxController* p_instance;

	Fbx* m_Fbx;

	std::map<std::string, FBXMeshData> m_MeshData;

	bool HasKey(std::string key_);
};


#endif
