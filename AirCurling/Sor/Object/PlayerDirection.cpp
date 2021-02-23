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
	m_direction_info.m_key = "direction";  //!描画用キー

	m_direction_info.m_rote = 0.0; //!モデル回転角度

	m_direction_info.m_pos = m_player->GetObjInfo()->m_pos;  //!座標
	m_direction_info.m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //!サイズ
	m_direction_info.m_angle = D3DXVECTOR3(0.0f, m_direction_info.m_rote, 0.0f); //!回転角度

	m_direction_info.m_mat_world = Calculation::Matrix(m_direction_info.m_pos, m_direction_info.m_scale, m_direction_info.m_angle);

	m_direction_info.m_add_zpos = 3.0;

	m_direction_info.m_is_shotmode = false;
}

//!更新関数
void PlayerDirection::Update()
{
	//!カメラが操作できるようなった時(ゲーム開始演出終了後)
	if (m_camera->GetObjInfo()->m_is_operation == true)
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
	if (m_ui->GetGameUIInfo()->m_gauge_stop == false
		&& m_direction_info.m_is_shotmode == true)
	{
		FbxController::Instance()->DrawFbx(m_direction_info.m_key, m_direction_info.m_mat_world);
	}
}

//!FBXモデル解放関数
void PlayerDirection::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_direction_info.m_key);
}

//!矢印回転関数
void PlayerDirection::Rote()
{
	if (m_ui->GetGameUIInfo()->m_gauge_stop == false)
	{
		m_direction_info.m_player_pos = m_player->GetObjInfo()->m_pos;
		m_direction_info.m_pos = m_player->GetObjInfo()->m_pos;
		m_direction_info.m_pos.z = m_player->GetObjInfo()->m_pos.z + m_direction_info.m_add_zpos;
		m_direction_info.m_old_pos = m_direction_info.m_pos;

		m_direction_info.m_dir_vec = m_camera->GetObjInfo()->m_forward;

		m_direction_info.m_pos_rote_r = D3DXToDegree (-atan2f(m_direction_info.m_dir_vec.x, m_direction_info.m_dir_vec.z));
		m_direction_info.m_rote = D3DXToDegree(atan2f(m_direction_info.m_dir_vec.x, m_direction_info.m_dir_vec.z));

		m_direction_info.m_pos = Calculation::Rote(m_direction_info.m_old_pos, m_direction_info.m_player_pos, m_direction_info.m_pos_rote_r);

		m_direction_info.m_angle = D3DXVECTOR3(0.0f, m_direction_info.m_rote, 0.0f);
		m_direction_info.m_mat_world = Calculation::Matrix(m_direction_info.m_pos, m_direction_info.m_scale, m_direction_info.m_angle);
	}
}

//!モード切替関数
void PlayerDirection::ModeChange()
{
	if (Inputter::Instance()->GetKeyDown(Inputter::F_KEY))
	{
		if (m_direction_info.m_is_shotmode == false)
		{
			m_direction_info.m_is_shotmode = true;
		}
		else
		{
			m_direction_info.m_is_shotmode = false;
		}
	}
}
