/**
 * @file Sky.h
 * @brief ゲームの背景を構成するオブジェクト
 * @details 中身：空(上空)オブジェクトクラス、空(床)クラス
**/
#ifndef SKYDOME_H_
#define SKYDOME_H_
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
	virtual void Init(std::string stage_str_)override;

	/**
	 * @brief  外部データ読み込み関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	virtual void LoadExternalInfo(std::string stage_str_)override;


	/**
	 * @brief   描画情報送信関数
	 * @details  Fbx管理クラスにオブジェクト情報を送る
	 */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

	/**
　　* @brief  オブジェクト情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	const void GetSkyDomeInfo(ObjectInfo& copy_info_) { copy_info_ = m_skydome_info; }
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

#endif