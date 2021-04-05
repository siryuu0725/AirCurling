/**
 * @file PlayerDirection.h
 * @brief プレイヤーが向いている方向に向く矢印オブジェクト
 * @details 中身：プレイヤーの矢印(向いている方向)クラス
**/
#ifndef PLAYERDIRECTION_H_
#define PLAYERDIRECTION_H_

#include "ObjectBase.h"
#include "Player.h"
#include "../UI/GameUI/GameUI.h"

/**
* プレイヤーの矢印(向いている方向)クラス
*/
class PlayerDirection :public ObjectBase
{
public:
	/**
 　　* @brief  コンストラクタ
     * @param[in] player_ プレイヤーアドレス
 　　* @param[in] camera_ カメラアドレス
 　　* @param[in] ui_     ゲームUIアドレス
 　　*/
	PlayerDirection(Player* player_, Camera* camera_, GameUI* ui_);
	~PlayerDirection() {}

	/**
	 * @brief  初期化関数
	 * @details オブジェクト情報初期化
	 */
	void Init();

	/**
	 * @brief  更新関数
	 * @details 更新処理まとめ関数
	 */
	void Update();

	/**
	 * @brief   描画情報送信関数
	 * @details  Fbx管理クラスにオブジェクト情報を送る
	 */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

	/**
	 * @brief   矢印回転関数
	 * @detail  プレイヤーが視を動かした時矢印も一緒に動くようにする
	 */
	void Rotate();

private:
	struct DirectionInfo :public ObjectInfo
	{
		DirectionInfo() :
			m_old_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_player_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_dir_vec(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_add_zpos(0.0f),
			m_rot_angle(0.0f),
			m_pos_rot(0.0f)
		{}

		D3DXVECTOR3 m_old_pos;     //!回転用oldpos

		D3DXVECTOR3 m_player_pos;  //!プレイヤーpos保存用

		D3DXVECTOR3 m_dir_vec;     //!カメラの方向Vec保存用

		float m_add_zpos;          //!プレイヤーの前にくるように足す値
							       
		float m_rot_angle;              //!モデル回転角度
							       
		float m_pos_rot;        //!pos回転角度
	};

	DirectionInfo m_direction_info;

	Player* mp_player;  //!プレイヤー保存用
	Camera* mp_camera;  //!カメラ保存用
	GameUI* mp_ui;	   //!ゲーム用UI保存用
};

#endif