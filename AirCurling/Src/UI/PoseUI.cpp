﻿#include "PoseUI.h"
#include "../Utility/Collision/Collision.h"
#include "../System/Inputter.h"

//!初期化関数
void PoseUI::Init()
{
	//!外部データ読み込み
	LoadPoseUIExternalInfo();

	for (int i = 0; i < m_ui_num; i++)
	{
		m_poseui_info.m_ui_pos[i] = D3DXVECTOR2(m_poseui_externalinfo[i].m_pos.x, m_poseui_externalinfo[i].m_pos.y);  //!背景
	}

	m_poseui_info.m_select = false;
	m_poseui_info.m_continue = false;
	m_poseui_info.m_end = false;
	m_poseui_info.m_help = false;

	//!テクスチャ読み込み
	LoadTex();
}

//!外部データ読み込み関数
void PoseUI::LoadPoseUIExternalInfo()
{
	FILE* fp = NULL;

	fopen_s(&fp, "Res/UIData/PoseUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//!書き込む
		fread(&m_poseui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!更新関数
void PoseUI::Update()
{
	//!ヘルプ画面ではないと時
	if (m_poseui_info.m_help == false)
	{
		SelectUI(); //!ポーズ中UI当たり判定関数
	}
	else
	{
		HelpMode();
	}
}

//!ポーズ中UI当たり判定関数
void PoseUI::SelectUI()
{
	m_poseui_info.m_select = false;
	m_poseui_info.m_continue = false;
	m_poseui_info.m_end = false;

	//!文字「つづける」にマウスが当たっているとき
	if (Collision::RectToPoint(m_poseui_info.m_ui_pos[(int)HelpUICategory::Continue], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_poseui_info.m_ui_tex[(int)HelpUICategory::Continue].Width, m_poseui_info.m_ui_tex[(int)HelpUICategory::Continue].Height) == true)
	{
		//!選択中テクスチャを「つづける」に合わせる
		m_poseui_info.m_ui_pos[(int)HelpUICategory::Select] = m_poseui_info.m_ui_pos[(int)HelpUICategory::Continue];
		m_poseui_info.m_select = true;

		//!選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_poseui_info.m_continue = true;
		}
	}
	//!文字「おわる」にマウスが当たっているとき
	else if (Collision::RectToPoint(m_poseui_info.m_ui_pos[(int)HelpUICategory::End], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_poseui_info.m_ui_tex[(int)HelpUICategory::End].Width, m_poseui_info.m_ui_tex[(int)HelpUICategory::End].Height) == true)
	{
		//!選択中テクスチャを「おわる」に合わせる
		m_poseui_info.m_ui_pos[(int)HelpUICategory::Select] = m_poseui_info.m_ui_pos[(int)HelpUICategory::End];

		m_poseui_info.m_select = true;
		m_poseui_info.m_continue = false;

		//!選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_poseui_info.m_end = true;
		}
	}
	//!文字「へるぷ」にマウスが当たっているとき
	else if (Collision::RectToPoint(m_poseui_info.m_ui_pos[(int)HelpUICategory::Help], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_poseui_info.m_ui_tex[(int)HelpUICategory::Help].Width, m_poseui_info.m_ui_tex[(int)HelpUICategory::Help].Height) == true)
	{
		//!選択中テクスチャを「へるぷ」に合わせる
		m_poseui_info.m_ui_pos[(int)HelpUICategory::Select] = m_poseui_info.m_ui_pos[(int)HelpUICategory::Help];

		m_poseui_info.m_select = true;
		m_poseui_info.m_continue = false;

		//!選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_poseui_info.m_help = true;
		}
	}
	
}

//!ヘルプ画面切り替え関数
void PoseUI::HelpMode()
{
	//!ヘルプ画面時
	if (m_poseui_info.m_help == true)
	{
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_poseui_info.m_help = false;
		}
	}
}

//!テクスチャ読み込み関数
void PoseUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/OptionBG.png", &m_poseui_info.m_ui_tex[(int)HelpUICategory::BG]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Tudukeru.png", &m_poseui_info.m_ui_tex[(int)HelpUICategory::Continue]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Owaru.png", &m_poseui_info.m_ui_tex[(int)HelpUICategory::End]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Help.png", &m_poseui_info.m_ui_tex[(int)HelpUICategory::Help]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_SelectFrame.png", &m_poseui_info.m_ui_tex[(int)HelpUICategory::Select]);
	Graphics::Instance()->LoadTexture("Res/Tex/HelpBg.png", &m_poseui_info.m_ui_tex[(int)HelpUICategory::HelpBg]);

}

//!描画情報送信関数
void PoseUI::Draw()
{
	Graphics::Instance()->DrawTexture(&m_poseui_info.m_ui_tex[(int)HelpUICategory::BG], m_poseui_info.m_ui_pos[(int)HelpUICategory::BG]);
	Graphics::Instance()->DrawTexture(&m_poseui_info.m_ui_tex[(int)HelpUICategory::Continue], m_poseui_info.m_ui_pos[(int)HelpUICategory::Continue]);
	Graphics::Instance()->DrawTexture(&m_poseui_info.m_ui_tex[(int)HelpUICategory::End], m_poseui_info.m_ui_pos[(int)HelpUICategory::End]);
	Graphics::Instance()->DrawTexture(&m_poseui_info.m_ui_tex[(int)HelpUICategory::Help], m_poseui_info.m_ui_pos[(int)HelpUICategory::Help]);

	if (m_poseui_info.m_select == true)
	{
		Graphics::Instance()->DrawTexture(&m_poseui_info.m_ui_tex[(int)HelpUICategory::Select], m_poseui_info.m_ui_pos[(int)HelpUICategory::Select]);
	}

	if (m_poseui_info.m_help == true)
	{
		Graphics::Instance()->DrawTexture(&m_poseui_info.m_ui_tex[(int)HelpUICategory::HelpBg], m_poseui_info.m_ui_pos[(int)HelpUICategory::HelpBg]);
	}
}

//!テクスチャ解放関数
void PoseUI::ReleaseTex()
{
	for (int i = 0; i < (int)HelpUICategory::CategoryMax; i++)
	{
		if (&m_poseui_info.m_ui_tex[i] != nullptr)
		{
			m_poseui_info.m_ui_tex[i].Texture->Release();
			m_poseui_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}