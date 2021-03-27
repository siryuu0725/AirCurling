#include "LoadFontUI.h"

//初期化関数
void LoadFontUI::Init()
{
	//座標初期化
	m_loadfont_info.m_ui_pos = m_external_pos[(__int8)LoadFontTexCategory::NowLoad];

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/NowLoading.png", &m_loadfont_info.m_ui_tex);
}

//描画情報送信関数
void LoadFontUI::Draw()
{
	//背景
	Graphics::Instance()->DrawTexture(&m_loadfont_info.m_ui_tex, m_loadfont_info.m_ui_pos);
}

//テクスチャ解放関数
void LoadFontUI::ReleaseTex()
{
	m_loadfont_info.m_ui_tex.Texture->Release();
	m_loadfont_info.m_ui_tex.Texture = nullptr;
}
