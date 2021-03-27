#include "ShotGaugeUI.h"

//初期化関数
void ShotGaugeUI::Init()
{
	//座標初期化
	for (__int8 i = __int8(ShotGaugeTexCategory::ShotGauge); i <= __int8(ShotGaugeTexCategory::ShotBox); i++)
	{
		m_shotgauge_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/ShotBar.png", &m_shotgauge_info.m_ui_tex[(__int8)ShotGaugeTexCategory::ShotBox]);
	Graphics::Instance()->LoadTexture("Res/Tex/ShotGauge.png", &m_shotgauge_info.m_ui_tex[(__int8)ShotGaugeTexCategory::ShotGauge]);
	Graphics::Instance()->LoadTexture("Res/Tex/ShotFrame.png", &m_shotgauge_info.m_ui_tex[(__int8)ShotGaugeTexCategory::ShotGaugeFlame]);

	m_shotgauge_info.m_gauge_speed = 7.0f; //ゲージバーの動くスピード
	m_shotgauge_info.m_gauge_pos = 0.0f;   //ゲージバーの座標
	m_shotgauge_info.m_is_stop_gauge = false; //ゲージバー停止フラグ
	m_shotgauge_info.m_add_speed = 0.0f;  //プレイヤーの移動スピード
}

//更新関数
void ShotGaugeUI::Update(Player* player_, bool is_turnend_)
{
	PlayerModeUI::PlayerModeUIInfo mode_info;
	mp_mode->GetPlayerModeUIInfo(mode_info);

	//バーを止めるキーが押されていない間
	if (m_shotgauge_info.m_is_stop_gauge == false)
	{
		//バーを動かす
		m_shotgauge_info.m_ui_pos[(int)ShotGaugeTexCategory::ShotBox].y -= m_shotgauge_info.m_gauge_speed;

		m_shotgauge_info.m_gauge_pos += m_shotgauge_info.m_gauge_speed;
	}

	//スペースキーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::SpaceKey) && m_shotgauge_info.m_is_stop_gauge == false
		&& mode_info.m_is_shotmode == true)
	{
		m_shotgauge_info.m_gauge_speed = 0.0f; //バーの移動スピードを0に
		m_shotgauge_info.m_add_speed = AddSpeedPower * m_shotgauge_info.m_gauge_pos; //プレイヤーの移動速度を設定
		m_shotgauge_info.m_is_stop_gauge = true;  //ゲージバー移動
		//移動スピードをUIのバーが止まったとこらから加算
		player_->SetAddSpeed(m_shotgauge_info.m_add_speed);
		player_->SetIsMovePlayer(true);
		//サウンド再生
		SoundController::Instance()->PlaySoundSE(PlaySEType::Shot);
	}

	//バーがゲージの最大値or最小値に達した時
	if (m_shotgauge_info.m_ui_pos[(int)ShotGaugeTexCategory::ShotBox].y + m_shotgauge_info.m_ui_tex[(int)ShotGaugeTexCategory::ShotBox].Height >
		m_shotgauge_info.m_ui_pos[(int)ShotGaugeTexCategory::ShotGauge].y + m_shotgauge_info.m_ui_tex[(int)ShotGaugeTexCategory::ShotGauge].Height
		|| m_shotgauge_info.m_ui_pos[(int)ShotGaugeTexCategory::ShotBox].y < m_shotgauge_info.m_ui_pos[(int)ShotGaugeTexCategory::ShotGauge].y)
	{
		m_shotgauge_info.m_gauge_speed = -m_shotgauge_info.m_gauge_speed;
	}

	//1ターン終わった時
	if (is_turnend_ == true)
	{
		//バー移動フラグ切り替え
		m_shotgauge_info.m_is_stop_gauge = false;
		//バーの位置を初期位置に
		m_shotgauge_info.m_ui_pos[(int)ShotGaugeTexCategory::ShotBox].y = m_shotgauge_info.m_ui_pos[(int)ShotGaugeTexCategory::ShotGauge].y + m_shotgauge_info.m_ui_tex[(int)ShotGaugeTexCategory::ShotGauge].Height - m_shotgauge_info.m_ui_tex[(int)ShotGaugeTexCategory::ShotBox].Height;
		m_shotgauge_info.m_gauge_pos = 0.0f;

		m_shotgauge_info.m_gauge_speed = 7.0f;
	}
}

//描画情報送信関数
void ShotGaugeUI::Draw()
{
	PlayerModeUI::PlayerModeUIInfo mode_info;
	mp_mode->GetPlayerModeUIInfo(mode_info);

	if (mode_info.m_is_shotmode == true)
	{
		Graphics::Instance()->DrawTexture(&m_shotgauge_info.m_ui_tex[(__int8)ShotGaugeTexCategory::ShotGaugeFlame], m_shotgauge_info.m_ui_pos[(__int8)ShotGaugeTexCategory::ShotGaugeFlame]);
		Graphics::Instance()->DrawTexture(&m_shotgauge_info.m_ui_tex[(__int8)ShotGaugeTexCategory::ShotGauge], m_shotgauge_info.m_ui_pos[(__int8)ShotGaugeTexCategory::ShotGauge]);
		Graphics::Instance()->DrawTexture(&m_shotgauge_info.m_ui_tex[(__int8)ShotGaugeTexCategory::ShotBox], m_shotgauge_info.m_ui_pos[(__int8)ShotGaugeTexCategory::ShotBox]);
	}
}

//テクスチャ解放関数
void ShotGaugeUI::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)ShotGaugeTexCategory::CategoryMax; i++)
	{
		if (&m_shotgauge_info.m_ui_tex[i] != nullptr)
		{
			m_shotgauge_info.m_ui_tex[i].Texture->Release();
			m_shotgauge_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
