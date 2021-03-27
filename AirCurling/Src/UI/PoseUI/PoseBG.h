/**
 * @file BG.h
 * @brief ポーズ中の背景を扱う
 * @details 中身：ポーズ中背景クラス
**/
#ifndef POSEUI_BG_H_
#define POSEUI_BG_H_

#include "../UIBase.h"
#include "PoseUICategory.h"
#include "PoseItem.h"

//!Textureの種類
enum class PoseBGTexCategory :__int8
{
	BG,          //!背景
	HelpBg,      //!ヘルプ画面背景
	CategoryMax
};


/**
* ポーズ中背景クラス
*/

class PoseBG :public UIBase
{
public:
	//!ポーズ中背景情報
	struct PoseBGInfo
	{
		PoseBGInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) }
		{}

		Graphics::TextureData m_ui_tex[(__int8)PoseBGTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)PoseBGTexCategory::CategoryMax]; //Texture座標
	};

	PoseBG(PoseItemUI* pose_item_) :mp_pose_item(pose_item_) {}
	~PoseBG() {}

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
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

private:
	PoseBGInfo m_bg_info;  //!ポーズ中背景情報
	PoseItemUI* mp_pose_item; //!//!ポーズ中項目

};
#endif