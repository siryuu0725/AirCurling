#include "PauseItem.h"

void PauseItemUI::Init()
{
	//座標初期化
	for (__int8 i = __int8(PauseItemTexCategory::Continue); i <= __int8(PauseItemTexCategory::Select); i++)
	{
		m_pauseitem_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Tudukeru.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Continue]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Owaru.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::End]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Help.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Help]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_SelectFrame.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Select]);
}


void PauseItemUI::Update()
{
	//ヘルプ画面ではないと時
	if (m_pauseitem_info.m_is_help == false)
	{
		SelectUI(); //ポーズ中UI当たり判定関数
	}
	else
	{
		HelpMode();
	}
}

void PauseItemUI::Draw()
{
	if (m_pauseitem_info.m_is_help == false)
	{
		Graphics::Instance()->DrawTexture(&m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Continue], m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Continue]);
		Graphics::Instance()->DrawTexture(&m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::End], m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::End]);
		Graphics::Instance()->DrawTexture(&m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Help], m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Help]);
		Graphics::Instance()->DrawTexture(&m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Select], m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Select]);
	}
}

void PauseItemUI::SelectUI()
{
	m_pauseitem_info.m_is_continue = false;
	m_pauseitem_info.m_is_end = false;

	//文字「つづける」にマウスが当たっているとき
	if (Collision::RectAndPoint(m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Continue], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Continue].Width, m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Continue].Height) == true)
	{
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//選択中テクスチャを「つづける」に合わせる
		m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Select] = m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Continue];

		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_pauseitem_info.m_is_continue = true;
		}
	}
	//文字「おわる」にマウスが当たっているとき
	else if (Collision::RectAndPoint(m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::End], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_pauseitem_info.m_ui_tex[(int)PauseItemTexCategory::End].Width, m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::End].Height) == true)
	{
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//選択中テクスチャを「おわる」に合わせる
		m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Select] = m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::End];

		m_pauseitem_info.m_is_continue = false;

		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_pauseitem_info.m_is_end = true;
		}
	}
	//文字「へるぷ」にマウスが当たっているとき
	else if (Collision::RectAndPoint(m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Help], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Help].Width, m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Help].Height) == true)
	{
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//選択中テクスチャを「へるぷ」に合わせる
		m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Select] = m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Help];

		m_pauseitem_info.m_is_continue = false;

		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_pauseitem_info.m_is_help = true;
		}
	}
	else
	{
		SoundController::Instance()->ResetSelectFlag();
	}
}

void PauseItemUI::HelpMode()
{
	if (Inputter::Instance()->OnMouseDown(Inputter::Left))
	{
		m_pauseitem_info.m_is_help = false;
	}
}

void PauseItemUI::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)PauseItemTexCategory::CategoryMax; i++)
	{
		if (&m_pauseitem_info.m_ui_tex[i] != nullptr)
		{
			m_pauseitem_info.m_ui_tex[i].Texture->Release();
			m_pauseitem_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}