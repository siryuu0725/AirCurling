﻿/**
 * @file DebufController.h
 * @brief ステージに配置されているデバフ効果の床オブジェクトを管理している
 * @details　中身：デバフ床管理クラス
**/
#ifndef DEBUFCONTROLLER_H_
#define DEBUFCONTROLLER_H_
#include "ResetFloor.h"
#include "StopFloor.h"
#include <vector>

//!ステージに置ける最大デバフ床数数 
constexpr unsigned __int8 ResetFloorMaxNum = 5; //!リセット床
constexpr unsigned __int8 StopFloorMaxNum = 5;  //!スピード減衰床


/**
* デバフ床管理クラス
*/
class DebufController :public ObjectBase
{
public:
	DebufController() {}
	~DebufController();


	/**
	 * @brief  初期化関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details オブジェクト情報初期化
	 */
	virtual void Init(std::string stage_str_)override;

	/**
	 * @brief  外部データ読み込み関数(リセット床)
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadResetFloorExternalInfo(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数(スピード減衰床)
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadStopFloorExternalInfo(std::string stage_str_);

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

	/**
　　* @brief 当たり判定用情報Set関数
	* @details ObjectCollisionで使用するオブジェクトコピー情報にオリジナルの情報を渡す
　　*/
	void SetCollisionInfo();

private:
	std::vector<ResetFloor*> m_resetfloors;  //!リセット床情報保存用
	std::vector<StopFloor*> m_stopfloors;	 //!スピード減衰床情報保存用

	int m_resetfloor_num;  //!リセット床数
	int m_stopfloor_num;   //!スピード減衰床数

	//!外部データ保存用構造体(リセット床)
	struct ResetFloorExternalInfo
	{
		ResetFloorExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_radius(0.0f)
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

		float m_radius; //!半径
	};

	//!外部データ保存用構造体(スピード減衰床)
	struct StopFloorExternalInfo
	{
		StopFloorExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_rot_angle(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_width(0.0f),
			m_height(0.0f)
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

		//!回転角度
		D3DXVECTOR3 m_rot_angle;

		float m_width;  //!横幅 
		float m_height; //!縦幅
	};

	//!外部データ保存用
	ResetFloorExternalInfo m_resetfloor_externalinfo[ResetFloorMaxNum];  //!リセット床
	StopFloorExternalInfo m_stopfloor_externalinfo[StopFloorMaxNum];    //!スピード減衰床

};


#endif