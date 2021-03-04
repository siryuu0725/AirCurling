/**
 * @file Sky.h
 * @brief ゲームの背景を構成するオブジェクト
 * @details 中身：空(上空)オブジェクトクラス、空(床)クラス
**/
#ifndef SKY_H_
#define SKY_H_
#include "ObjectBase.h"

/**
* 空(上空)オブジェクトクラス
*/
class SkyDome :public ObjectBase
{
public:
	SkyDome() {}
	~SkyDome() {}

	/**
	 * @brief  初期化関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details オブジェクト情報初期化
	 */
	void Init(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadSkyDomeExternalInfo(std::string stage_str_);


	/**
	 * @brief   描画情報送信関数
	 * @details  Fbx管理クラスにオブジェクト情報を送る
	 */
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
　　* @brief  オブジェクト情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	void GetSkyDomeInfo(ObjectInfo& copy_info_) { copy_info_ = m_skydome_info; }
private:
	//!外部データ保存用構造体
	struct SkyDomeExternalInfo
	{
		SkyDomeExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

	};

	ObjectInfo m_skydome_info;
	SkyDomeExternalInfo m_skydome_externalinfo;

};

/**
* 空(床)クラス
*/

class SkyFloor :public ObjectBase
{
public:
	SkyFloor() {}
	~SkyFloor() {}


	/**
	 * @brief  初期化関数
	 * @param[in] stage_id_ 選択ステージ名(例"Stage1")
	 * @details オブジェクト情報初期化
	 */
	void Init(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadSkyFloorExternalInfo(std::string stage_str_);


	/**
	 * @brief   描画情報送信関数
	 * @details  Fbx管理クラスにオブジェクト情報を送る
	 */
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
　　* @brief  オブジェクト情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	void GetSkyFloorInfo(ObjectInfo& copy_info_) { copy_info_ = m_skyfloor_info; }

private:
	//!外部データ保存用構造体
	struct SkyFloorExternalInfo
	{
		SkyFloorExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

	};

	ObjectInfo m_skyfloor_info;
	SkyFloorExternalInfo m_skyfloor_externalinfo;
};
#endif