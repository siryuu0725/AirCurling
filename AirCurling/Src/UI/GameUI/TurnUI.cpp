#include "TurnUI.h"

//初期化関数
void TurnUI::Init()
{
	for (__int8 i = __int8(TurnTexCategory::Turn); i <= __int8(TurnTexCategory::TurnNumber); i++)
	{
		m_turn_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Turn.png", &m_turn_info.m_ui_tex[(__int8)TurnTexCategory::Turn]);
	Graphics::Instance()->LoadTexture("Res/Tex/Math.png", &m_turn_info.m_ui_tex[(__int8)TurnTexCategory::TurnNumber]);

	m_turn_info.m_ui_tu[(int)TurnTexCategory::TurnNumber] = 0.1f; //ターン数のtu値
	m_turn_info.m_ui_tv[(int)TurnTexCategory::TurnNumber] = 1.0f; //ターン数のtv値
}

//更新関数
void TurnUI::Update(bool is_turnend_)
{
	//1ターン終わった時
	if (is_turnend_ == true)
	{
		//ターン数加算
		m_turn_info.m_ui_tu[(int)TurnTexCategory::TurnNumber] += TrunTexUVAddValue;

		if (m_turn_info.m_ui_tu[(int)TurnTexCategory::TurnNumber] > TrunTexUVMax)
		{
			m_turn_info.m_ui_tu[(int)TurnTexCategory::TurnNumber] = TrunTexUVMax;
		}
	}
}

//描画情報送信関数
void TurnUI::Draw()
{
	//ターン数
	Graphics::Instance()->DrawUVTexture(&m_turn_info.m_ui_tex[(int)TurnTexCategory::TurnNumber], m_turn_info.m_ui_pos[(int)TurnTexCategory::TurnNumber], 94.0f, 94.0f, m_turn_info.m_ui_tu[(int)TurnTexCategory::TurnNumber], m_turn_info.m_ui_tv[(int)TurnTexCategory::TurnNumber]);
	//文字「ターン」
	Graphics::Instance()->DrawTexture(&m_turn_info.m_ui_tex[(__int8)TurnTexCategory::Turn], m_turn_info.m_ui_pos[(__int8)TurnTexCategory::Turn]);
}

//テクスチャ解放関数
void TurnUI::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)TurnTexCategory::CategoryMax; i++)
	{
		if (&m_turn_info.m_ui_tex[i] != nullptr)
		{
			m_turn_info.m_ui_tex[i].Texture->Release();
			m_turn_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
