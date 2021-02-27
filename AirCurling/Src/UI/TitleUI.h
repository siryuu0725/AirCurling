#ifndef TITLE_H_
#define TITLE_H_

#include "UIBase.h"
#include "../System/Sound/SoundController.h"

/**
*@class  タイトル用UIクラス
*/

class TitleUI :public UIBase
{
public:
	//!UIの種類
	enum class TitleUICategory :int
	{
		BG,            //!背景
		Name,		   //!タイトル名
		Start,		   //!文字「スタート」
		End,		   //!文字「終わり」
		Help,		   //!文字「ヘルプ」
		NowSelect,	   //!現在選択枠
		HelpBG,	       //!ヘルプ画面用BG
		SelectStage1,  //!文字「1」
		SelectStage2,  //!文字「2」
		NowSelectStage,//!現在選択ステージ枠
		SelectStageFont,//!文字「ステージを選択」
		CategoryMax,   //!UI数
	};

private:
	//!タイトル画面UI情報
	struct TitleUIInfo
	{
		TitleUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			startui_flg(false),
			endui_flg(false),
			helpui_flg(false),
			m_stage_1(false),
			m_stage_2(false)
		{}

		Graphics::TextureData m_ui_tex[(int)TitleUICategory::CategoryMax];  

		D3DXVECTOR2  m_ui_pos[(int)TitleUICategory::CategoryMax];

		/* 各Sceneへ飛ぶ判定 */
		bool startui_flg;  //!「はじめる」を押した時
		bool endui_flg;	   //!「おわる」を押した時
		bool helpui_flg;   //!「ヘルプ」を押した時

		bool m_stage_1;   //!ステージ1を選んだ場合
		bool m_stage_2;   //!ステージ2を選んだ場合

	}m_titleui_info;


public:
	TitleUI() {}
	~TitleUI() {}

	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init();

	/**
	 * @brief  外部データ読み込み関数
	 * @detail 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadTitleUIExternalInfo();

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
	void Update();

	/**
	 * @brief  テクスチャ解放関数
	 */
	void ReleaseTex();

	/**
	 * @brief  UI当たり判定関数
	 * @detail 次のシーンに移るための当たり判定を行う
	 */
	void Select();

	/**
	 * @brief  選択画面キャンセル関数
	 * @detail ステージ選択、またはヘルプ画面時初期のタイトル画面に戻る用
	 */
	void ReturnSelect();

	/**
	 * @brief  ステージUI当たり判定関数
	 * @detail ステージ選択画面のUIとの当たり判定と選択したステージ情報保存を行う
	 */
	void SelectStage();

	/**
 　　* @brief  UI情報Getter
 　　*/
	const TitleUIInfo* GetTitleUIInfo() { return &m_titleui_info; }

private:
	UIExternalInfo m_titleui_externalinfo[static_cast<int>(TitleUICategory::CategoryMax)];
};
#endif