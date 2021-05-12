/**
 * @file FbxController.h
 * @brief FBXファイルの読み込み描画等を管理する
 * @details 中身：FBX管理クラス
**/
#ifndef FBXCONTROLLER_H_
#define FBXCONTROLLER_H_
#include "FBX.h"

/**
* FBX管理クラス
*/
class FbxController
{
private:
	FbxController();
	~FbxController();

public:
	static FbxController* Instance();

	/**
	 * @brief  Meshデータセット関数
	 * @param[in] key_ オブジェクトのキー
	 * @param[in] pFilename_ 読み込むFbxファイルのパス
	 * @details 引数のキーのメッシュデータに引数のパスのFbxデータを代入する
	 */
	FBXMeshData LoadFbxMesh(std::string key_, const char* pFilename_);

	/**
	 * @brief  メッシュデータ読み込みまとめ関数
	 * @details 各オブジェクトのLoadFbxMesh関数をまとめたもの
	 */
	void LoadFbx();

	/**
	 * @brief  メッシュデータ解放関数
	 * @param[in] key_ オブジェクトのキー
	 */
	void ReleaseFbxMesh(std::string key_);

	/**
	 * @brief  Fbfファイル描画関数
	 * @details 各オブジェクトのLoadFbxMesh関数をまとめたもの
	 * @param[in] key_ オブジェクトのキー
	 * @param[in] mat_world_ オブジェクトのワールド座標
	 */
	void DrawFbx(std::string key_, D3DXMATRIX& mat_world_);

	/**
	 * @brief  メッシュデータ解放まとめ関数
	 * @param[in] key_ メッシュデータのキー
	 * @details 各オブジェクトのLoadFbxMesh関数をまとめたもの
	 */
	FBXMeshData GetMeshData(std::string key_) { return m_MeshData[key_]; }

	/**
	*	@brief Instance解放関数(Debug用)
	*	@details 手動でインスタンスを解放する
	*/
	void ReleaseInstance();

private:
	static FbxController* mp_instance;

	Fbx* p_Fbx;

	std::map<std::string, FBXMeshData> m_MeshData;

	bool HasKey(std::string key_);
};


#endif
