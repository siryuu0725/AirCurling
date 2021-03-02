/**
 * @file GameUI.h
 * @brief ゲームシーン中のUIを扱う
 * @details 中身：ゲーム用UIクラス、更新ステップ列挙体
**/
#ifndef GAMEUI_H
#define GAMEUI_H
#include "UIBase.h"
#include "../System/Graphics.h"
#include "../Object/Camera.h"
#include "../Object/Player.h"
#include "UIBase.h"

constexpr float AddSpeedPower = 0.001f;   //!プレイヤーに加える力
constexpr float TrunTexUVAddValue = 0.1f; //!テクスチャのUV値に加算する値(ターン数用)
constexpr float TrunTexUVMax = 1.0f;      //!テクスチャの最大UV値
constexpr unsigned __int8 StartFontStopTime = 60; //!開始演出の文字を止める時間

constexpr float StartFontEndPosX = 1900.0f;  //!開始演出の終了座標
constexpr float FinishFontEndPosX = -500.0f; //!開始演出の終了座標
constexpr float Buoyancy = 8.0f; //!浮力(終了演出で使用)

//!更新ステップ
enum class UpdateStep
{
	StartProduction,  //!開始演出
	GameMain,		  //!本編
	EndProduction,	  //!終了演出
};

//!UIの種類
enum class GameUICategory :int
{
	ShotGauge,       //!打つ威力ゲージ
	ShotGaugeFlame,	 //!打つ威力ゲージ枠
	ShotBox,		 //!打つ威力決定バー
	Turn,			 //!文字「ターン」
	TurnNumber,		 //!ターン数
	ViewMode,		 //!文字「View」
	ShotMode,		 //!文字「shot」
	One_Score,		 //!スコア数1の位
	Ten_Score,		 //!スコア数10の位
	Start,			 //!文字「スタート」
	Kacco,			 //!文字「=」
	Finish,          //!文字「フィニッシュ」
	CategoryMax,	 //!UI数
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
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_ui_tu{ 0.0f },
			m_ui_tv{ 0.0f },
			m_gauge_speed(0.0f),
			m_gauge_pos(0.0f),
			m_gauge_stop(false),
			m_add_speed(0.0f),
			m_now_score(0),
			m_one_score(0),
			m_ten_score(0),
			m_score(""),
			m_is_shotmode(false),
			m_movestop(false),
			m_remove(false),
			m_end_game(false),
			m_stoptimer(0),
			m_movespeed(0.0f),
			t(0.0f),
			flame(0.0f)
		{}

		Graphics::TextureData m_ui_tex[(int)GameUICategory::CategoryMax];  //!テクスチャ

		D3DXVECTOR2  m_ui_pos[(int)GameUICategory::CategoryMax]; //!座標

		float  m_ui_tu[(int)GameUICategory::CategoryMax]; //!テクスチャのTU値
		float  m_ui_tv[(int)GameUICategory::CategoryMax]; //!テクスチャのTV値

		float m_gauge_speed;  //!ゲージバーの動くスピード
		float m_gauge_pos;    //!ゲージバーの座標
		bool m_gauge_stop;    //!ゲージバー停止フラグ

		float m_add_speed;  //!プレイヤーの移動スピード

		__int8 m_now_score; //!総合スコア 

		__int8 m_one_score;  //!スコア1の位保存用
		__int8 m_ten_score;  //!スコア10の位保存用


		char m_score[20];//!スコア描画用

		bool m_is_shotmode; //!shot(打つ)モード切り替えフラグ

		__int16 m_stoptimer; //!開始演出の文字が止まる演出時間

		float m_movespeed;  //!開始演出の文字が動くスピード

		bool m_movestop;   //!開始演出の文字が止まるフラグ

		bool m_remove;//!開始演出の文字が再び動くフラグ

		bool m_end_game;

		float t;		// 秒
		float flame;	// 1フレーム当たりの時間

	};
private:
	GameUIInfo m_gameui_info;

public:
	GameUI() {}
	~GameUI() {}

	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init();

	/**
	 * @brief  外部データ読み込み関数
	 * @detail 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadGameUIExternalInfo();

	/**
     * @brief  テクスチャ読み込み関数
     */
	void LoadTex();

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief  更新関数
	 * @detail 更新処理まとめ関数
	 */
	void Update(Player* player_, Camera* camera_);

	/**
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();

	/**
     * @brief  スピードゲージ停止関数
     * @detail プレイヤーに加えるスピードを決定する
     */
	void StopGauge(Player* player_);

	/**
	 * @brief  ターン終了時初期化関数
	 * @detail 1ターン終了するたびターン経過とゲージの数値の初期化を行う
	 */
	void UpdateTurn(Player* player_);

	/**
	 * @brief  スコア加算関数
	 * @detail 1ターン終了時にターン経過によるスコア加算を行う
	 */
	void AddScore(Player* player_);

	/**
	 * @brief  モード切替判定関数
	 * @detail ゲージがshotモード時にしか表示されないようにフラグを切り替える
	 */
	void ModeChange();

	/**
	 * @brief  開始演出関数
	 * @detail プレイヤーがステージに着いた後に「スタート」の文字が流れる処理を行う
	 */
	void StartProduction(Camera* camera_);

	/**
	 * @brief  終了演出関数
	 * @detail プレイヤーがゴール、またはターン制限後超えた時の終了演出を行う
	 */
	void EndProduction();


	/**
 　　* @brief  UI情報Getter
 　　*/
	const GameUIInfo* GetGameUIInfo() { return &m_gameui_info; }

private:
	UpdateStep m_update_step;  //!更新ステップ

	UIExternalInfo m_gameui_externalinfo[static_cast<int>(GameUICategory::CategoryMax)];
};
#endif