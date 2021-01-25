﻿#ifndef DIRECTION_H_
#define DIRECTION_H_

#include "ObjectBase.h"
#include "Player.h"
#include "../UI/GameUI.h"

//矢印
class PlayerDirection :public ObjectBase
{
public:
	struct DirectionInfo :public ObjectInfo
	{
		D3DXVECTOR3 old_pos;  //!回転用oldpos

		D3DXVECTOR3 player_pos;  //!プレイヤーpos保存用

		D3DXVECTOR3 dir_vec; //!カメラの方向Vec保存用

		float add_zpos; //!

		float rote;       //!モデル回転角度

		float pos_rote_r; //!pos回転角度

		bool shotmode;  //!打つモードかどうか

	}direction_info;
public:
	/**
 　　* @brief  コンストラクタ
     * @param (player_) プレイヤーアドレス
 　　* @param (camera_) カメラアドレス
 　　* @param (ui_)     ゲームUIアドレス
 　　*/
	PlayerDirection(Player* player_, Camera* camera_, GameUI* ui_);
	~PlayerDirection() {}

	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init();

	/**
	 * @brief  更新関数
	 * @detail 更新処理まとめ関数
	 */
	void Update();

	/**
	 * @brief   描画情報送信関数
	 * @detail  Fbx管理クラスにオブジェクト情報を送る
	 */
	void SetUpBuffer();

	/**
	 * @brief   矢印回転関数
	 * @detail  プレイヤーが視を動かした時矢印も一緒に動くようにする
	 */
	void Rote();

	/**
	 * @brief  モード切替関数
	 * @detail shotとviewモードの切り替えを行う
	 */
	void ModeChange();

private:
	Player* m_player;  //!プレイヤーアドレス保存用
	Camera* m_camera;  //!カメラアドレス保存用
	GameUI* m_ui;	   //!ゲーム用UIアドレス保存用
};

#endif