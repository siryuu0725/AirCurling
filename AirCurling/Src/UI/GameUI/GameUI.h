/**
 * @file GameUI.h
 * @brief ゲームシーン中のUIを扱う
 * @details 中身：ゲーム用UIクラス、更新ステップ列挙体
**/
#ifndef GAMEUI_H
#define GAMEUI_H
#include "../UIBase.h"
#include "../../Object/Camera.h"
#include "../../Object/Player.h"
#include "../UIBase.h"
#include "GameScoreUI.h"
#include "ModeUI.h"
#include "ProductionUI.h"
#include "ShotGaugeUI.h"
#include "TurnUI.h"

constexpr unsigned __int8 GameUICategoryNum = 5;  //!ゲームシーンで使用するUIオブジェクトの数

//!更新ステップ
enum class UpdateStep
{
	StartProduction,  //!開始演出
	GameMain,		  //!本編
	EndProduction,	  //!終了演出
};

/**
* ゲーム用UIクラス
*/

class GameUI :public UIBase
{
public:
	//!ゲーム画面UI情報
	struct GameUIInfo
	{
		GameUIInfo() :
			m_is_endgame(false),
			m_is_stop_gauge(false)
		{}
		bool m_is_endgame;
		bool m_is_stop_gauge;    //!ゲージバー停止フラグ
	};
private:
	GameUIInfo m_gameui_info;

public:
	GameUI() {}
	~GameUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	void Init();

	/**
	 * @brief  外部データセット関数
	 * @details 各UIカテゴリーに必要な座標を渡す
	 */
	void SetUIPos();

	/**
	 * @brief  外部データ読み込み関数
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadGameUIExternalInfo();

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief  更新関数
 　　* @param[in] player_ プレイヤーアドレス
 　　* @param[in] camera_ カメラアドレス
	 * @details 更新処理まとめ関数
	 */
	void Update(Player* player_, Camera* camera_);

	/**
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();

	/**
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI情報構造体
	* @details 引数にUIの情報を渡す
　　*/
	const void GetGameUIInfo(GameUIInfo& copy_info_) { copy_info_ = m_gameui_info; }

private:
	UpdateStep m_update_step;  //!更新ステップ

	UIExternalInfo m_gameui_externalinfo[static_cast<int>(GameUICategory::CategoryMax)];

	Player::PlayerInfo m_player_infocopy;

	GameScoreUI* mp_game_score;    //!スコアUI
	PlayerModeUI* mp_player_mode;  //!モードUI
	ProductionUI* mp_production;   //!演出
	ShotGaugeUI* mp_shot_gauge;	   //!ShotGaugeUI
	TurnUI* mp_turn;			   //!ターンUI
};
#endif