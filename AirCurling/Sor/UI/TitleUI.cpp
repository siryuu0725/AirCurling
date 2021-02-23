﻿#include "TitleUI.h"
#include "../System/Inputter.h"
#include "../Utility/Collision/Collision.h"

//!初期化関数
void TitleUI::Init()
{
	FILE* fp = NULL;

	fopen_s(&fp, "Res/UIData/TitleUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		// 書き込む
		fread(&m_titleui_info_copy, sizeof(UIExternalInfo), m_ui_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	for (int i = 0; i < m_ui_num; i++)
	{
		m_title_ui_info.m_ui_pos[i] = D3DXVECTOR2(m_titleui_info_copy[i].pos_x, m_titleui_info_copy[i].pos_y);  //!背景
	}


	m_title_ui_info.startui_flg = false;  //!ゲームシーン移行フラグ
	m_title_ui_info.endui_flg = false;	//!終了フラグ
	m_title_ui_info.helpui_flg = false;	//!ヘルプシーン移行フラグ
	m_title_ui_info.m_stage_1 = false;	//!ステージ1を選んだ場合
	m_title_ui_info.m_stage_2 = false;	//!ステージ2を選んだ場合

	LoadTex();
}

//!テクスチャ読み込み関数
void TitleUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/TitleBg.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::BG]);
	Graphics::Instance()->LoadTexture("Res/Tex/GameTitle.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::Name]);
	Graphics::Instance()->LoadTexture("Res/Tex/Title_Hazimeru.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::Start]);
	Graphics::Instance()->LoadTexture("Res/Tex/Title_Owaru.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::End]);
	Graphics::Instance()->LoadTexture("Res/Tex/Title_Help.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::Help]);
	Graphics::Instance()->LoadTexture("Res/Tex/Title_SelectFrame.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::NowSelect]);
	Graphics::Instance()->LoadTexture("Res/Tex/HelpBg.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::HelpBG]);
	Graphics::Instance()->LoadTexture("Res/Tex/Stage_1.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::SelectStage1]);
	Graphics::Instance()->LoadTexture("Res/Tex/Stage_2.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::SelectStage2]);
	Graphics::Instance()->LoadTexture("Res/Tex/StageSelectFrame.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::NowSelectStage]);
	Graphics::Instance()->LoadTexture("Res/Tex/StageSelect.png", &m_title_ui_info.m_ui_tex[(int)TitleUICategory::SelectStageFont]);
}

//!描画情報送信関数
void TitleUI::SetUpBuffer()
{
	//!背景
	Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::BG], m_title_ui_info.m_ui_pos[(int)TitleUICategory::BG]);
	
	//!「はじめる」が押された後(ステージ選択画面中)
	if (m_title_ui_info.startui_flg == false)
	{
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::Name], m_title_ui_info.m_ui_pos[(int)TitleUICategory::Name]);
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::Start], m_title_ui_info.m_ui_pos[(int)TitleUICategory::Start]);
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::End], m_title_ui_info.m_ui_pos[(int)TitleUICategory::End]);
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::Help], m_title_ui_info.m_ui_pos[(int)TitleUICategory::Help]);
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::NowSelect], m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect]);
	}
	else
	{
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::SelectStageFont], m_title_ui_info.m_ui_pos[(int)TitleUICategory::SelectStageFont]);
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::SelectStage1], m_title_ui_info.m_ui_pos[(int)TitleUICategory::SelectStage1]);
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::SelectStage2], m_title_ui_info.m_ui_pos[(int)TitleUICategory::SelectStage2]);
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::NowSelectStage], m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelectStage]);
	}

	//!「ヘルプ」が押された場合(ヘルプ画面中)
	if (m_title_ui_info.helpui_flg == true)
	{
		//!背景
		Graphics::Instance()->DrawTexture(&m_title_ui_info.m_ui_tex[(int)TitleUICategory::HelpBG], m_title_ui_info.m_ui_pos[(int)TitleUICategory::HelpBG]);
	}
}

//!更新関数
void TitleUI::Update()
{
	//!「はじめる」が押された後(ステージ選択画面中)
	if (m_title_ui_info.startui_flg == true)
	{
		//!UI当たり判定関数
		SelectStage();

		if (Inputter::Instance()->GetKeyDown(Inputter::ESC_KEY))
		{
			m_title_ui_info.startui_flg = false;
		}
	}
	else 
	{
		//!UI当たり判定関数
		Select();
	}

	//!選択画面キャンセル関数
	ReturnSelect();
}

//!UI当たり判定関数
void TitleUI::Select()
{
	//!文字「はじめる」との当たり判定
	if (Collision::RectToPoint(m_title_ui_info.m_ui_pos[(int)TitleUICategory::Start], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		460.0f, 115.0f) == true)
	{
		//!選択枠テクスチャの座標を代入
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect].x = 210.0f;
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect].y = 400.0f;

		sound_mgr->SoundSelectSE();

		//!マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//!「はじめる」が押されたフラグtrue
			m_title_ui_info.startui_flg = true;
		}
	}
	//!文字「おわる」との当たり判定
	else if (Collision::RectToPoint(m_title_ui_info.m_ui_pos[(int)TitleUICategory::End], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		340.0f, 115.0f) == true)
	{
		//!選択枠テクスチャの座標を代入
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect].x = 210.0f;
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect].y = 600.0f;

		sound_mgr->SoundSelectSE();

		//!マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//!「おわる」が押されたフラグtrue
			m_title_ui_info.endui_flg = true;
		}
	}
	//!文字「ヘルプ」との当たり判定
	else if (Collision::RectToPoint(m_title_ui_info.m_ui_pos[(int)TitleUICategory::Help], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		350.0f, 115.0f) == true)
	{
		//!選択枠テクスチャの座標を代入
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect].x = 210.0f;
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect].y = 800.0f;

		sound_mgr->SoundSelectSE();

		//!マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//!「ヘルプ」が押されたフラグtrue
			m_title_ui_info.helpui_flg = true;
		}
	}
	else
	{
		//!選択枠テクスチャの座標を代入
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelect].y = -300.0f;

		sound_mgr->ResetSelectFlag();
	}
}

//!選択画面キャンセル関数
void TitleUI::ReturnSelect()
{
	//!ステージ選択画面、もしくはヘルプ画面時
	if (m_title_ui_info.startui_flg == true || m_title_ui_info.helpui_flg == true)
	{
		//!ESCキーが押された場合
		if (Inputter::Instance()->GetKeyDown(Inputter::ESC_KEY))
		{
			m_title_ui_info.startui_flg = false;
			m_title_ui_info.helpui_flg = false;
		}
	}
}

//!ステージUI当たり判定関数
void TitleUI::SelectStage()
{
	//!文字「1」との当たり判定
	if (Collision::RectToPoint(m_title_ui_info.m_ui_pos[(int)TitleUICategory::SelectStage1], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		316.0f, 400.0f) == true)
	{
		//!選択枠テクスチャの座標を代入
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelectStage] = m_title_ui_info.m_ui_pos[(int)TitleUICategory::SelectStage1];
		sound_mgr->SoundSelectSE();

		//!マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//!ステージ1を選んだフラグtrue
			m_title_ui_info.m_stage_1 = true;
		}
	}
	//!文字「2」との当たり判定
	else if (Collision::RectToPoint(m_title_ui_info.m_ui_pos[(int)TitleUICategory::SelectStage2], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		316.0f, 400.0f) == true)
	{
		//!選択枠テクスチャの座標を代入
		m_title_ui_info.m_ui_pos[(int)TitleUICategory::NowSelectStage] = m_title_ui_info.m_ui_pos[(int)TitleUICategory::SelectStage2];
		sound_mgr->SoundSelectSE();

		//!マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//!ステージ2を選んだフラグtrue
			m_title_ui_info.m_stage_2 = true;
		}
	}
}

//!テクスチャ解放関数
void TitleUI::ReleaseTex()
{
	for (int i = 0; i < (int)TitleUICategory::CategoryMax; i++)
	{
		if (&m_title_ui_info.m_ui_tex[i] != nullptr)
		{
			m_title_ui_info.m_ui_tex[i].Texture->Release();
			m_title_ui_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}


