#include "ModeUI.h"

//初期化関数
void PlayerModeUI::Init()
{
	//座標初期化
	for (__int8 i = __int8(PlayerModeTexCategory::ViewMode); i <= __int8(PlayerModeTexCategory::ShotMode); i++)
	{
		m_mode_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/ModeView.png", &m_mode_info.m_ui_tex[(__int8)PlayerModeTexCategory::ViewMode]);
	Graphics::Instance()->LoadTexture("Res/Tex/ModeShot.png", &m_mode_info.m_ui_tex[(__int8)PlayerModeTexCategory::ShotMode]);

	m_mode_info.m_is_shotmode = false;
}

//更新関数
void PlayerModeUI::Update()
{
	//モード切替キーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::FKey))
	{
		m_mode_info.m_is_shotmode = !m_mode_info.m_is_shotmode;
	}
}

//描画情報送信関数
void PlayerModeUI::Draw()
{
	//!ShotModeの時
	if (m_mode_info.m_is_shotmode == false)
	{
		Graphics::Instance()->DrawTexture(&m_mode_info.m_ui_tex[(__int8)PlayerModeTexCategory::ViewMode], m_mode_info.m_ui_pos[(__int8)PlayerModeTexCategory::ViewMode]);
	}
	else
	{
		Graphics::Instance()->DrawTexture(&m_mode_info.m_ui_tex[(__int8)PlayerModeTexCategory::ShotMode], m_mode_info.m_ui_pos[(__int8)PlayerModeTexCategory::ShotMode]);
	}
	
}

//テクスチャ解放関数
void PlayerModeUI::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)PlayerModeTexCategory::CategoryMax; i++)
	{
		if (&m_mode_info.m_ui_tex[i] != nullptr)
		{
			m_mode_info.m_ui_tex[i].Texture->Release();
			m_mode_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
