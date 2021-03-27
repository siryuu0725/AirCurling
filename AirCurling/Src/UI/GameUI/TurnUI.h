/**
 * @file TurnUI.h
 * @brief ゲーム中の上に表示するターン数を扱う
 * @details 中身：ターン数UIクラス
**/
#ifndef GAMEUI_TURN_H_
#define GAMEUI_TURN_H_

#include "../UIBase.h"
#include "GameUICategory.h"
constexpr float TrunTexUVAddValue = 0.1f; //!テクスチャのUV値に加算する値(ターン数用)
constexpr float TrunTexUVMax = 1.0f;      //!テクスチャの最大UV値

//!Textureの種類
enum class TurnTexCategory :__int8
{
	Turn,			 //!文字「ターン」
	TurnNumber,		 //!ターン数
	CategoryMax,	 //!UI数
};

/**
* ターン数UIクラス
*/

class TurnUI :public UIBase
{
public:
	//!ターン数UI情報
	struct TurnUIInfo
	{
		TurnUIInfo() :
			m_ui_pos{ D3DXVECTOR2(0.0f,0.0f) },
			m_ui_tu{ 0.0f },
			m_ui_tv{ 0.0f }
		{}

		Graphics::TextureData m_ui_tex[(__int8)TurnTexCategory::CategoryMax]; //Textureデータ

		D3DXVECTOR2  m_ui_pos[(__int8)TurnTexCategory::CategoryMax]; //Texture座標

		float  m_ui_tu[(__int8)TurnTexCategory::CategoryMax]; //!テクスチャのTU値
		float  m_ui_tv[(__int8)TurnTexCategory::CategoryMax]; //!テクスチャのTV値
	};

	TurnUI() {}
	~TurnUI() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	virtual void Init()override;

	/**
	 * @brief  更新関数
     * @param[in] is_turnend_ 1ターン終了フラグ
	 * @details ターン終了時初期化
	 */
	virtual void Update(bool is_turnend_);

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex()override;

private:
	TurnUIInfo m_turn_info; //!ターン数UI情報
};
#endif