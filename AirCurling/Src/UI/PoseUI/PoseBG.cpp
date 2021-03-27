#include "PoseBG.h"

//初期化関数
void PoseBG::Init()
{
	//座標初期化
	for (__int8 i = __int8(PoseUICategory::BG); i <= __int8(PoseUICategory::HelpBG); i++)
	{
		m_bg_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/OptionBG.png", &m_bg_info.m_ui_tex[(__int8)PoseUICategory::BG]);
	Graphics::Instance()->LoadTexture("Res/Tex/HelpBg.png", &m_bg_info.m_ui_tex[(__int8)PoseUICategory::HelpBG]);

}

//描画情報送信関数
void PoseBG::Draw()
{
	PoseItemUI::PoseItemInfo item_info;
	mp_pose_item->GetPoseItemInfo(item_info);

	if (item_info.m_is_help == false)
	{
		Graphics::Instance()->DrawTexture(&m_bg_info.m_ui_tex[(__int8)PoseUICategory::BG], m_bg_info.m_ui_pos[(__int8)PoseUICategory::BG]);
	}
	else
	{
		Graphics::Instance()->DrawTexture(&m_bg_info.m_ui_tex[(__int8)PoseUICategory::HelpBG], m_bg_info.m_ui_pos[(__int8)PoseUICategory::HelpBG]);
	}
}

//テクスチャ解放関数
void PoseBG::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)PoseBGTexCategory::CategoryMax; i++)
	{
		if (&m_bg_info.m_ui_tex[i] != nullptr)
		{
			m_bg_info.m_ui_tex[i].Texture->Release();
			m_bg_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
