/**
 * @file ProductionUI.h
 * @brief ゲームシーンの開始演出と終了演出を扱う
 * @details 中身：演出クラス
**/
#ifndef GAMEUI_PRODUCTION_H_
#define GAMEUI_PRODUCTION_H_

#include "../UIBase.h"
#include "GameUICategory.h"
#include "../../Object/Camera.h"
constexpr unsigned __int8 StartFontStopTime = 60; //!開始演出の文字を止める時間
constexpr float StartFontEndPosX = 2000.0f;  //!開始演出の終了座標
constexpr float FinishFontEndPosX = -500.0f; //!開始演出の終了座標
constexpr float Buoyancy = 8.0f; //!浮力(終了演出で使用)

//!Textureの種類
enum class ProductionTexCategory :__int8
{
	Start,			 //!文字「スタート」
	Kacco,			 //!文字「=」
	Finish,          //!文字「フィニッシュ」
	CategoryMax,	 //!UI数
};


/**
* 演出クラス
*/

class ProductionUI :public UIBase
{
public:
	//!演出情報
	struct ProductionInfo
	{
		ProductionInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_movestop(false),
			m_remove(false),
			m_is_start_game(false),
			m_is_end_game(false),
			m_is_draw_finish(false),
			m_stoptimer(0),
			m_movespeed(0.0f),
			timer(0.0f),
			flame(0.0f)
		{}

		Graphics::TextureData m_ui_tex[(__int8)ProductionTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)ProductionTexCategory::CategoryMax]; //Texture座標

		__int16 m_stoptimer; //!開始演出の文字が止まる演出時間

		float m_movespeed;  //!開始演出の文字が動くスピード

		bool m_movestop;   //!開始演出の文字が止まるフラグ

		bool m_remove;//!開始演出の文字が再び動くフラグ

		bool m_is_start_game;   //!操作可能になるまでのフラグ
		bool m_is_end_game;     //!リザルトシーンに移行するフラグ
		bool m_is_draw_finish;  //!文字「フィニッシュ」の描画フラグ

		float timer;	//!flameの合計値
		float flame;	//!1フレーム当たりの時間
	};

	ProductionUI() {}
	~ProductionUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  開始演出関数
 　　* @param[in] camera_ カメラアドレス
	 * @details プレイヤーがステージに着いた後に「スタート」の文字が流れる処理を行う
	 */
	void StartProduction(Camera* camera_);

	/**
	 * @brief  終了演出関数
	 * @details プレイヤーがゴール、またはターン制限後超えた時の終了演出を行う
	 */
	void EndProduction();

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

	/**
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI構造体
	* @details 引数にUIの情報を渡す
　　*/
	void GetProductionInfo(ProductionInfo& copy_info_) { copy_info_ = m_production_info; }

private:
	ProductionInfo m_production_info; //!演出情報
};
#endif