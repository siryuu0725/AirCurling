#include "ResultBG.h"

//初期化関数
void RusultBG::Init()
{
	//座標初期化
	m_bg_info.m_ui_pos = m_external_pos[(__int8)ResultBGTexCategory::BG];

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/ResultBg.png", &m_bg_info.m_ui_tex);
}

//描画情報送信関数
void RusultBG::Draw()
{
	//背景
	Graphics::Instance()->DrawTexture(&m_bg_info.m_ui_tex, m_bg_info.m_ui_pos);
}

//テクスチャ解放関数
void RusultBG::ReleaseTex()
{
	m_bg_info.m_ui_tex.Texture->Release();
	m_bg_info.m_ui_tex.Texture = nullptr;
}
