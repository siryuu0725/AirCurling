#include "TitleBG.h"

//初期化関数
void TitleBG::Init()
{
	//座標初期化
	for (__int8 i = 0; i < (__int8)TitleBGTexCategory::CategoryMax; i++)
	{
		m_titlebg_info.m_ui_pos[i] = m_external_pos[i];
	}

	//テクスチャ読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/TitleBg.png", &m_titlebg_info.m_ui_tex[(__int8)TitleBGTexCategory::BG]);
	Graphics::Instance()->LoadTexture("Res/Tex/HelpBg.png", &m_titlebg_info.m_ui_tex[(__int8)TitleBGTexCategory::HelpBG]);
}

//描画情報送信関数
void TitleBG::Draw()
{
	TitleItem::ItemInfo item_info;
	mp_title_item->GetTitleItemInfo(item_info);

	if (item_info.m_is_help == false)
	{
		//背景
		Graphics::Instance()->DrawTexture(&m_titlebg_info.m_ui_tex[(__int8)TitleBGTexCategory::BG], m_titlebg_info.m_ui_pos[(__int8)TitleBGTexCategory::BG]);
	}
	else
	{
		//背景
		Graphics::Instance()->DrawTexture(&m_titlebg_info.m_ui_tex[(__int8)TitleBGTexCategory::HelpBG], m_titlebg_info.m_ui_pos[(__int8)TitleBGTexCategory::HelpBG]);
	}
}

//テクスチャ解放関数
void TitleBG::ReleaseTex()
{
	for (int i = 0; i < (__int8)TitleBGTexCategory::CategoryMax; i++)
	{
		if (&m_titlebg_info.m_ui_tex[i] != nullptr)
		{
			m_titlebg_info.m_ui_tex[i].Texture->Release();
			m_titlebg_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
