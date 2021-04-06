#include "PlayerDirection.h"
#include "../System/Inputter.h"

//コンストラクタ
PlayerDirection::PlayerDirection(Player* player_, Camera* camera_)
{
	mp_player = player_;  //!プレイヤーアドレス
	mp_camera = camera_;  //!カメラアドレス
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

	m_direction_info.m_add_zpos = 3.0f; //プレイヤーの位置からどのくらい前に描画するかの距離
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

	//プレイヤーが動いていない間&ShotModeの間
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

//矢印オブジェクト回転関数
void PlayerDirection::Rotate()
{
	Player::PlayerInfo player_info;
	mp_player->GetPlayerInfo(player_info);

	//ShotGaugeが動いている間()
	if (player_info.m_is_movement == false)
	{
		Camera::CameraInfo camera_info;
		mp_camera->GetCameraInfo(camera_info);

		//矢印オブジェクトもプレイヤーの位置に合わせる
		m_direction_info.m_pos = player_info.m_pos;
		m_direction_info.m_pos.z = player_info.m_pos.z + m_direction_info.m_add_zpos;

		//プレイヤーが向いている方向ベクトル取得
		m_direction_info.m_dir_vec = camera_info.m_forward;

		//矢印オブジェクトの座標回転角度取得
		m_direction_info.m_pos_rot = D3DXToDegree(-atan2f(m_direction_info.m_dir_vec.x, m_direction_info.m_dir_vec.z));

		//矢印オブジェクトの向き回転角度取得
		m_direction_info.m_rot_angle = D3DXToDegree(atan2f(m_direction_info.m_dir_vec.x, m_direction_info.m_dir_vec.z));

		//矢印オブジェクトの座標回転
		m_direction_info.m_pos = Calculation::Rotate(m_direction_info.m_pos, player_info.m_pos, m_direction_info.m_pos_rot);

		//矢印オブジェクトの向き回転
		m_direction_info.m_angle = D3DXVECTOR3(0.0f, m_direction_info.m_rot_angle, 0.0f);
		m_direction_info.m_mat_world = Calculation::Matrix(m_direction_info.m_pos, m_direction_info.m_scale, m_direction_info.m_angle);
	}
}
