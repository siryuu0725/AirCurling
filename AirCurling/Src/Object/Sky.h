#ifndef SKY_H_
#define SKY_H_
#include "ObjectBase.h"

/**
*@class  空(上空)オブジェクトクラス
*/

class SkyDome :public ObjectBase
{
public:
	SkyDome() {}
	~SkyDome() {}

	/**
	 * @brief  初期化関数
	 * @param (stage_id_) 選択ステージ名(例"Stage1")
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数
	 * @detail 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadSkyDomeExternalInfo(std::string stage_str_);


	/**
	 * @brief   描画情報送信関数
	 * @detail  Fbx管理クラスにオブジェクト情報を送る
	 */
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_skydome_info; }
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
*@class  空(床)クラス
*/

class SkyFloor :public ObjectBase
{
public:
	SkyFloor() {}
	~SkyFloor() {}


	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数
	 * @detail 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadSkyFloorExternalInfo(std::string stage_str_);


	/**
	 * @brief   描画情報送信関数
	 * @detail  Fbx管理クラスにオブジェクト情報を送る
	 */
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_skyfloor_info; }

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