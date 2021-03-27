#include "PoseItem.h"

void PoseItemUI::Init()
{
	//座標初期化
	for (__int8 i = __int8(PoseItemTexCategory::Continue); i <= __int8(PoseItemTexCategory::Select); i++)
	{
		m_poseitem_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Tudukeru.png", &m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::Continue]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Owaru.png", &m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::End]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Help.png", &m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::Help]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_SelectFrame.png", &m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::Select]);
}


void PoseItemUI::Update()
{
	//ヘルプ画面ではないと時
	if (m_poseitem_info.m_help == false)
	{
		SelectUI(); //ポーズ中UI当たり判定関数
	}
	else
	{
		HelpMode();
	}
}

void PoseItemUI::Draw()
{
	if (m_poseitem_info.m_help == false)
	{
		Graphics::Instance()->DrawTexture(&m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::Continue], m_poseitem_info.m_ui_pos[(__int8)PoseItemTexCategory::Continue]);
		Graphics::Instance()->DrawTexture(&m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::End], m_poseitem_info.m_ui_pos[(__int8)PoseItemTexCategory::End]);
		Graphics::Instance()->DrawTexture(&m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::Help], m_poseitem_info.m_ui_pos[(__int8)PoseItemTexCategory::Help]);
		Graphics::Instance()->DrawTexture(&m_poseitem_info.m_ui_tex[(__int8)PoseItemTexCategory::Select], m_poseitem_info.m_ui_pos[(__int8)PoseItemTexCategory::Select]);
	}
}

void PoseItemUI::SelectUI()
{
	m_poseitem_info.m_continue = false;
	m_poseitem_info.m_end = false;

	//文字「つづける」にマウスが当たっているとき
	if (Collision::RectAndPoint(m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::Continue], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_poseitem_info.m_ui_tex[(int)PoseItemTexCategory::Continue].Width, m_poseitem_info.m_ui_tex[(int)PoseItemTexCategory::Continue].Height) == true)
	{
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//選択中テクスチャを「つづける」に合わせる
		m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::Select] = m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::Continue];

		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_poseitem_info.m_continue = true;
		}
	}
	//文字「おわる」にマウスが当たっているとき
	else if (Collision::RectAndPoint(m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::End], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_poseitem_info.m_ui_tex[(int)PoseItemTexCategory::End].Width, m_poseitem_info.m_ui_tex[(int)PoseItemTexCategory::End].Height) == true)
	{
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//選択中テクスチャを「おわる」に合わせる
		m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::Select] = m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::End];

		m_poseitem_info.m_continue = false;

		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_poseitem_info.m_end = true;
		}
	}
	//文字「へるぷ」にマウスが当たっているとき
	else if (Collision::RectAndPoint(m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::Help], D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_poseitem_info.m_ui_tex[(int)PoseItemTexCategory::Help].Width, m_poseitem_info.m_ui_tex[(int)PoseItemTexCategory::Help].Height) == true)
	{
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//選択中テクスチャを「へるぷ」に合わせる
		m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::Select] = m_poseitem_info.m_ui_pos[(int)PoseItemTexCategory::Help];

		m_poseitem_info.m_continue = false;

		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_poseitem_info.m_help = true;
		}
	}
	else
	{
		SoundController::Instance()->ResetSelectFlag();
	}
}

void PoseItemUI::HelpMode()
{
	if (Inputter::Instance()->OnMouseDown(Inputter::Left))
	{
		m_poseitem_info.m_help = false;
	}
}

void PoseItemUI::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)PoseItemTexCategory::CategoryMax; i++)
	{
		if (&m_poseitem_info.m_ui_tex[i] != nullptr)
		{
			m_poseitem_info.m_ui_tex[i].Texture->Release();
			m_poseitem_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}