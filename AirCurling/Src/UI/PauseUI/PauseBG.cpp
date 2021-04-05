#include "PauseBG.h"

//初期化関数
void PauseBG::Init()
{
	//座標初期化
	for (__int8 i = __int8(PauseUICategory::BG); i <= __int8(PauseUICategory::HelpBG); i++)
	{
		m_bg_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/OptionBG.png", &m_bg_info.m_ui_tex[(__int8)PauseUICategory::BG]);
	Graphics::Instance()->LoadTexture("Res/Tex/HelpBg.png", &m_bg_info.m_ui_tex[(__int8)PauseUICategory::HelpBG]);

}

//描画情報送信関数
void PauseBG::Draw()
{
	PauseItemUI::PauseItemInfo item_info;
	mp_pause_item->GetPoseItemInfo(item_info);

	if (item_info.m_is_help == false)
	{
		Graphics::Instance()->DrawTexture(&m_bg_info.m_ui_tex[(__int8)PauseUICategory::BG], m_bg_info.m_ui_pos[(__int8)PauseUICategory::BG]);
	}
	else
	{
		Graphics::Instance()->DrawTexture(&m_bg_info.m_ui_tex[(__int8)PauseUICategory::HelpBG], m_bg_info.m_ui_pos[(__int8)PauseUICategory::HelpBG]);
	}
}

//テクスチャ解放関数
void PauseBG::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)PauseBGTexCategory::CategoryMax; i++)
	{
		if (&m_bg_info.m_ui_tex[i] != nullptr)
		{
			m_bg_info.m_ui_tex[i].Texture->Release();
			m_bg_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
