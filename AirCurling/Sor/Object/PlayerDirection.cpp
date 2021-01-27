#include "PlayerDirection.h"
#include "../System/Inputter.h"

//!コンストラクタ
PlayerDirection::PlayerDirection(Player* player_, Camera* camera_, GameUI* ui_)
{
	m_player = player_;  //!プレイヤーアドレス
	m_camera = camera_;  //!カメラアドレス
	m_ui = ui_;          //!ゲーム用UIアドレス
}

//!初期化関数
void PlayerDirection::Init()
{
	direction_info.m_key = "direction";  //!描画用キー

	direction_info.m_rote = 0.0; //!モデル回転角度

	direction_info.m_pos = m_player->GetObjInfo()->m_pos;  //!座標
	direction_info.m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //!サイズ
	direction_info.m_angle = D3DXVECTOR3(0.0f, direction_info.m_rote, 0.0f); //!回転角度

	direction_info.m_mat_world = Calculation::Matrix(direction_info.m_pos, direction_info.m_scale, direction_info.m_angle);

	direction_info.m_add_zpos = 3.0;

	direction_info.m_shotmode = false;
}

//!更新関数
void PlayerDirection::Update()
{
	//!カメラが操作できるようなった時(ゲーム開始演出終了後)
	if (m_camera->GetObjInfo()->m_operation == true)
	{
		//!モード切替判定
		ModeChange();

		//!矢印回転
		Rote();
	}
}

//!描画情報送信関数
void PlayerDirection::SetUpBuffer()
{
	if (m_ui->GetGameUIInfo()->gauge_stop == false
		&& direction_info.m_shotmode == true)
	{
		FbxController::Instance()->DrawFbx(direction_info.m_key, direction_info.m_mat_world);
	}
}

//!矢印回転関数
void PlayerDirection::Rote()
{
	if (m_ui->GetGameUIInfo()->gauge_stop == false)
	{
		direction_info.m_player_pos = m_player->GetObjInfo()->m_pos;
		direction_info.m_pos = m_player->GetObjInfo()->m_pos;
		direction_info.m_pos.z = m_player->GetObjInfo()->m_pos.z + direction_info.m_add_zpos;
		direction_info.m_old_pos = direction_info.m_pos;

		direction_info.m_dir_vec = m_camera->GetObjInfo()->m_forward;

		direction_info.m_pos_rote_r = D3DXToDegree (-atan2f(direction_info.m_dir_vec.x, direction_info.m_dir_vec.z));
		direction_info.m_rote = D3DXToDegree(atan2f(direction_info.m_dir_vec.x, direction_info.m_dir_vec.z));

		direction_info.m_pos = Calculation::Rote(direction_info.m_old_pos, direction_info.m_player_pos, direction_info.m_pos_rote_r);


		direction_info.m_angle = D3DXVECTOR3(0.0f, direction_info.m_rote, 0.0f);
		direction_info.m_mat_world = Calculation::Matrix(direction_info.m_pos, direction_info.m_scale, direction_info.m_angle);
	}

}

//!モード切替関数
void PlayerDirection::ModeChange()
{
	if (Inputter::Instance()->GetKeyDown(Inputter::F_KEY))
	{
		if (direction_info.m_shotmode == false)
		{
			direction_info.m_shotmode = true;
		}
		else
		{
			direction_info.m_shotmode = false;
		}
	}
}
