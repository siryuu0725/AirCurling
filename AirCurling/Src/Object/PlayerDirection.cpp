﻿#include "PlayerDirection.h"
#include "../System/Inputter.h"

//コンストラクタ
PlayerDirection::PlayerDirection(Player* player_, Camera* camera_, GameUI* ui_)
{
	mp_player = player_;  //!プレイヤーアドレス
	mp_camera = camera_;  //!カメラアドレス
	mp_ui = ui_;          //!ゲーム用UIアドレス
}

//初期化関数
void PlayerDirection::Init()
{
	m_direction_info.m_key = "direction";  //描画用キー

	m_direction_info.m_rot_angle = 0.0f; //モデル回転角度

	Player::PlayerInfo player_info;

	mp_player->GetPlayerInfo(player_info);

	m_direction_info.m_pos = player_info.m_pos;  //座標
	m_direction_info.m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //サイズ
	m_direction_info.m_angle = D3DXVECTOR3(0.0f, m_direction_info.m_rot_angle, 0.0f); //回転角度

	m_direction_info.m_mat_world = Calculation::Matrix(m_direction_info.m_pos, m_direction_info.m_scale, m_direction_info.m_angle);

	m_direction_info.m_add_zpos = 3.0;

	m_direction_info.m_is_shotmode = false;
}

//更新関数
void PlayerDirection::Update()
{
	//矢印回転
	Rotate();
}

//描画情報送信関数
void PlayerDirection::Draw()
{
	Player::PlayerInfo player_info;
	Camera::CameraInfo camera_info;

	mp_player->GetPlayerInfo(player_info);
	mp_camera->GetCameraInfo(camera_info);

	if (player_info.m_is_movement == false
		&& camera_info.m_is_shotmode == true)
	{
		FbxController::Instance()->DrawFbx(m_direction_info.m_key, m_direction_info.m_mat_world);
	}
}

//FBXモデル解放関数
void PlayerDirection::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_direction_info.m_key);
}

//矢印回転関数
void PlayerDirection::Rotate()
{
	GameUI::GameUIInfo ui_info;

	mp_ui->GetGameUIInfo(ui_info);

	if (ui_info.m_is_stop_gauge == false)
	{
		Player::PlayerInfo player_info;
		Camera::CameraInfo camera_info;
		mp_player->GetPlayerInfo(player_info);
		mp_camera->GetCameraInfo(camera_info);

		m_direction_info.m_player_pos = player_info.m_pos;
		m_direction_info.m_pos = player_info.m_pos;
		m_direction_info.m_pos.z = player_info.m_pos.z + m_direction_info.m_add_zpos;
		m_direction_info.m_old_pos = m_direction_info.m_pos;

		m_direction_info.m_dir_vec = camera_info.m_forward;

		m_direction_info.m_pos_rot = D3DXToDegree (-atan2f(m_direction_info.m_dir_vec.x, m_direction_info.m_dir_vec.z));
		m_direction_info.m_rot_angle = D3DXToDegree(atan2f(m_direction_info.m_dir_vec.x, m_direction_info.m_dir_vec.z));

		m_direction_info.m_pos = Calculation::Rotate(m_direction_info.m_old_pos, m_direction_info.m_player_pos, m_direction_info.m_pos_rot);

		m_direction_info.m_angle = D3DXVECTOR3(0.0f, m_direction_info.m_rot_angle, 0.0f);
		m_direction_info.m_mat_world = Calculation::Matrix(m_direction_info.m_pos, m_direction_info.m_scale, m_direction_info.m_angle);
	}
}
