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
	direction_info.key = "direction";  //!描画用キー

	direction_info.rote = 0.0; //!モデル回転角度

	direction_info.pos = m_player->GetObjInfo()->pos;  //!座標
	direction_info.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //!サイズ
	direction_info.angle = D3DXVECTOR3(0.0f, direction_info.rote, 0.0f); //!回転角度

	direction_info.mat_world = Calculation::Matrix(direction_info.pos, direction_info.scale, direction_info.angle);

	direction_info.add_zpos = 3.0;

	direction_info.shotmode = false;
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
		&& direction_info.shotmode == true)
	{
		FbxController::Instance()->DrawFbx(direction_info.key, direction_info.mat_world);
	}
}

//!矢印回転関数
void PlayerDirection::Rote()
{
	if (m_ui->GetGameUIInfo()->gauge_stop == false)
	{
		direction_info.player_pos = m_player->GetObjInfo()->pos;
		direction_info.pos = m_player->GetObjInfo()->pos;
		direction_info.pos.z = m_player->GetObjInfo()->pos.z + direction_info.add_zpos;
		direction_info.old_pos = direction_info.pos;

		direction_info.dir_vec = m_camera->GetObjInfo()->m_forward;

		direction_info.pos_rote_r = D3DXToDegree (-atan2f(direction_info.dir_vec.x, direction_info.dir_vec.z));
		direction_info.rote = D3DXToDegree(atan2f(direction_info.dir_vec.x, direction_info.dir_vec.z));

		direction_info.pos = Calculation::Rote(direction_info.old_pos, direction_info.player_pos, direction_info.pos_rote_r);


		direction_info.angle = D3DXVECTOR3(0.0f, direction_info.rote, 0.0f);
		direction_info.mat_world = Calculation::Matrix(direction_info.pos, direction_info.scale, direction_info.angle);
	}

}

//!モード切替関数
void PlayerDirection::ModeChange()
{
	if (Inputter::Instance()->GetKeyDown(Inputter::F_KEY))
	{
		if (direction_info.shotmode == false)
		{
			direction_info.shotmode = true;
		}
		else
		{
			direction_info.shotmode = false;
		}
	}
}
