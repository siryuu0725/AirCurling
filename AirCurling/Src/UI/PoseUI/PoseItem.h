/**
 * @file PoseItemUI.h
 * @brief ポーズ中の各選択項目を扱う
 * @details 中身：ポーズ中項目クラス
**/
#ifndef POSEUI_ITEM_H_
#define POSEUI_ITEM_H_

#include "../UIBase.h"
#include "PoseUICategory.h"
//!Textureの種類
enum class PoseItemTexCategory :__int8
{
	Continue,    //!文字「つづける」
	End,         //!文字「おわる」
	Help,        //!文字「へるぷ」
	Select,      //!選択中
	CategoryMax,
};


/**
* ポーズ中項目クラス
*/

class PoseItemUI :public UIBase
{
public:
	//!ポーズ中項目情報
	struct PoseItemInfo
	{
		PoseItemInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_is_continue(false),
			m_is_end(false),
			m_is_help(false)
		{}

		Graphics::TextureData m_ui_tex[(__int8)PoseItemTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)PoseItemTexCategory::CategoryMax]; //Texture座標

		bool m_is_continue;  //!「つづける」選択フラグ
		bool m_is_end;		  //!「おわる」選択フラグ
		bool m_is_help;	  //!「へるぷ」選択フラグ
	};

	PoseItemUI() {}
	~PoseItemUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  更新関数
	 * @details 更新処理まとめ関数
	 */
	virtual void Update();

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

	/**
	 * @brief  ポーズ中UI当たり判定関数
	 * @details ポーズ画面中の「つづける」などのUIとの当たり判定を行う
	 */
	void SelectUI();

	/**
	 * @brief  ヘルプ画面切り替え関数
	 * @details ポーズ画面中からヘルプ画面に行った際再びポーズ画面に戻るかどうかを判定する
	 */
	void HelpMode();

	/**
　　* @brief  UI情報Getter
	* @param[out] copy_info_ 保存用UI構造体
	* @details 引数にUIの情報を渡す
　　*/
	void GetPoseItemInfo(PoseItemInfo& copy_info_) { copy_info_ = m_poseitem_info; }

private:
	PoseItemInfo m_poseitem_info; //!ポーズ中項目情報
};
#endif