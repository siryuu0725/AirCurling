/**
 * @file ObjectBase.h
 * @brief 各オブジェクトの共通部分を扱う
**/

#ifndef OBJBASE_H_
#define OBJBASE_H_
#include"../System/FBXController.h"
#include "../Utility/Calculation.h"
#include "../System/FBX.h"
#include <vector>
#include <string>

/**
*@class   オブジェクトベースクラス
*/
class ObjectBase
{
public:
	//!オブジェクト情報
	struct ObjectInfo
	{
		ObjectInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_angle(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_width(0.0f),
			m_height(0.0f),
			m_radius(0.0f),
			m_rot_angle(0.0f)
		{
			D3DXMatrixIdentity(&m_mat_world);
		}

		D3DXVECTOR3 m_pos;   //!座標
		D3DXVECTOR3 m_scale; //!サイズ
		D3DXVECTOR3 m_angle; //!回転角度

		D3DXMATRIX m_mat_world;		//!ワールド座標

		std::string m_key;  //!描画用キー

		float m_width;    //!横幅
		float m_height;	 //!縦幅

		float m_radius;   //!半径

		float m_rot_angle;   //!回転角度

	};

	ObjectBase() {}
	virtual ~ObjectBase() {}

	/**
     * @brief  初期化関数
     * @param[in] stage_str_ 選択ステージ名(例"Stage1")
     * @details オブジェクト情報初期化
     */
	virtual void Init(std::string stage_str_) {}

	/**
	 * @brief  外部データ読み込み関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	virtual void LoadExternalInfo(std::string stage_str_) {}


	/**
	 * @brief   描画情報送信関数
	 * @details  Fbx管理クラスにオブジェクト情報を送る
	 */
	virtual void Draw() {}

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel() {}
};

#endif
