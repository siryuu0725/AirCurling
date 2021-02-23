#ifndef SKY_H_
#define SKY_H_
#include "ObjectBase.h"

/**
*@clss  空オブジェクトクラス
*/

//空(上空)
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
	void SetUpBuffer();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_skydome_info; }
private:
	ObjectInfo m_skydome_info;

	struct SkyDomeExternalInfo
	{
		//!座標
		float pos[3];
		//!サイズ
		float scale[3];

	}m_skydome_info_copy;
};

/**
*@clss  背景床クラス
*/

//空(床)
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
	void SetUpBuffer();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_skyfloor_info; }

private:
	ObjectInfo m_skyfloor_info;

	struct SkyFloorExternalInfo
	{
		//!座標
		float pos[3];
		//!サイズ
		float scale[3];

	}m_skyfloor_info_copy;
};
#endif