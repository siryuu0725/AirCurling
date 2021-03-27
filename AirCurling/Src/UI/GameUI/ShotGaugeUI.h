/**
 * @file ShotGaugeUI.h
 * @brief ゲーム中の右に表示するゲージを扱う
 * @details 中身：ShotGaugeUIクラス
**/
#ifndef GAMEUI_SHOTGAUGE_H_
#define GAMEUI_SHOTGAUGE_H_

#include "../UIBase.h"
#include "GameUICategory.h"
#include "ModeUI.h"
#include "../../Object/Player.h"
constexpr float AddSpeedPower = 0.001f;   //!プレイヤーに加える力

//!Textureの種類
enum class ShotGaugeTexCategory :__int8
{
	ShotGauge,       //!打つ威力ゲージ
	ShotGaugeFlame,	 //!打つ威力ゲージ枠
	ShotBox,		 //!打つ威力決定バー
	CategoryMax,	 //!UI数
};


/**
* ShotGaugeUIクラス
*/

class ShotGaugeUI :public UIBase
{
public:
	//!ShotGaugeUI情報
	struct ShotGaugeUIInfo
	{
		ShotGaugeUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_gauge_speed(0.0f),
			m_gauge_pos(0.0f),
			m_is_stop_gauge(false),
			m_add_speed(0.0f)
		{}

		Graphics::TextureData m_ui_tex[(__int8)ShotGaugeTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)ShotGaugeTexCategory::CategoryMax]; //Texture座標

		float m_gauge_speed;  //!ゲージバーの動くスピード
		float m_gauge_pos;    //!ゲージバーの座標
		bool m_is_stop_gauge; //!ゲージバー停止フラグ

		float m_add_speed;  //!プレイヤーの移動スピード
	};

	/**
 　　* @brief  コンストラクタ
 　　* @param[in] mode_ プレイヤーモードアドレス
 　　*/
	ShotGaugeUI(PlayerModeUI* mode_) :mp_mode(mode_) {}
	~ShotGaugeUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  更新関数
	 * @param[in] player_ プレイヤーアドレス
	 * @param[in] is_turnend_ 1ターン終了フラグ
	 * @details スピードゲージ更新処理関数
	 */
	void Update(Player* player_, bool is_turnend_);

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

private:
	PlayerModeUI* mp_mode; //モードUI
	ShotGaugeUIInfo m_shotgauge_info; //!ShotGaugeUI情報
};
#endif