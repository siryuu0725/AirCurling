/**
 * @file UIBase.h
 * @brief 各UIの共通部分を扱う
 * @details 中身：UIベースクラス
**/
#ifndef UIBASE_H_
#define UIBASE_H_
#include "../System/DirectGraphics.h"
#include "../Utility/Collision/Collision.h"
#include "../System/Inputter.h"
#include "../System/Sound/SoundController.h"
#include <d3d9.h>
#include <d3dx9.h>

/**
* UIベースクラス
*/
class UIBase
{
public:
	UIBase() :m_ui_num(0) {}
	~UIBase() {}

	/**
     * @brief  初期化関数
     * @details オブジェクト情報初期化
     */
	virtual void Init() = 0;

	/**
	 * @brief  描画情報送信関数
	 */
	virtual void Draw() {}

	/**
	 * @brief  テクスチャ解放関数
	 */
	virtual void ReleaseTex() = 0;
	

	/**
     * @brief  外部データ保存関数
     * @details 各UI管理クラスからUIオブジェクトに送る外部データを保存する
     */
	template<typename... UIPos>
	void SetUIPos(const UIPos&... ui_pos_)
	{
		Develop(ui_pos_...);
	}

	/**
	 * @brief  外部データ追加関数
	 * @details SetUIPosから送られてきた情報を1つずつ追加する
	 */
	template<typename First, typename... Rest>
	void Develop(const First& first_, const Rest&... rest_)
	{
		m_external_pos.push_back(first_);
		Develop(rest_...);
	}

	//! 無限ループにならないように
	void Develop() { return; }

protected:
	int m_ui_num;

	struct UIExternalInfo
	{
		UIExternalInfo() :
			m_pos(D3DXVECTOR2(0.0f, 0.0f))
		{}

		D3DXVECTOR2 m_pos;  //!座標
	};

	std::vector<D3DXVECTOR2> m_external_pos; //座標外部データ
};

#endif