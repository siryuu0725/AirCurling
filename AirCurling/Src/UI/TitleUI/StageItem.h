/**
 * @file TitleUI.h
 * @brief タイトルシーンのステージ選択画面を扱う
 * @details 中身：ステージ選択画面項目クラス
**/
#ifndef TITLEUI_STAGEITEM_H_
#define TITLEUI_STAGEITEM_H_

#include "../UIBase.h"
#include "TitleUICategory.h"
#include "TitleItem.h"

//!Textureの種類
enum class TitleStageItemTexCategory :__int8
{
	SelectStage1,    //!文字「1」
	SelectStage2,    //!文字「2」
	NowSelectStage,  //!現在選択ステージ枠
	SelectStageFont, //!文字「ステージを選択」
	CategoryMax,     //!UI数
};

/**
* ステージ選択画面項目クラス
*/

class TitleStageItem :public UIBase
{
public:
	//!ステージ選択画面項目情報
	struct TitleStageItemInfo
	{
		TitleStageItemInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_stage_1(false),
			m_stage_2(false)
		{}

		Graphics::TextureData m_ui_tex[(__int8)TitleStageItemTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)TitleStageItemTexCategory::CategoryMax]; //Texture座標

		bool m_stage_1;  //!ステージ1を選んだ場合
		bool m_stage_2;	 //!ステージ2を選んだ場合
	};

	/**
 　　* @brief  コンストラクタ
 　　* @param[in] title_item_ タイトル画面選択項目アドレス
 　　*/
	TitleStageItem(TitleItem* title_item_) :mp_title_item(title_item_) {}
	~TitleStageItem() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  更新関数
	 * @details 更新処理まとめ関数
	 */
	virtual void Update();

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

	/**
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI構造体
	* @details 引数にUIの情報を渡す
　　*/
	void GetStageItemInfo(TitleStageItemInfo& copy_info_) { copy_info_ = m_stageitem_info; }

private:
	TitleStageItemInfo m_stageitem_info; //!ステージ選択画面項目情報
	TitleItem* mp_title_item; //!タイトル画面選択項目
};
#endif