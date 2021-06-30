#include "PauseItem.h"

//初期化関数
void PauseItemUI::Init()
{
	//座標初期化
	for (__int8 i = __int8(PauseItemTexCategory::Continue); i <= __int8(PauseItemTexCategory::Select); i++)
	{
		m_pauseitem_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Continue.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Continue]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_End.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::End]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_Help.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Help]);
	Graphics::Instance()->LoadTexture("Res/Tex/Pose_SelectFrame.png", &m_pauseitem_info.m_ui_tex[(__int8)PauseItemTexCategory::Select]);
    
	m_pauseitem_info.m_is_continue = false;  //「つづける」選択フラグ
	m_pauseitem_info.m_is_end = false;		 //「おわる」選択フラグ
	m_pauseitem_info.m_is_help = false;		 //「へるぷ」選択フラグ
}

//更新関数
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

//描画情報送信関数
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

//ポーズ中UIフラグ管理関数
void PauseItemUI::SelectUI()
{
	m_pauseitem_info.m_is_continue = false;
	m_pauseitem_info.m_is_end = false;

	//文字「つづける」にマウスが当たっているとき
	if (HitSelectUI(PauseItemTexCategory::Continue) == true)
	{
		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_pauseitem_info.m_is_continue = true;
		}
	}
	//文字「おわる」にマウスが当たっているとき
	else if (HitSelectUI(PauseItemTexCategory::End) == true)
	{
		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_pauseitem_info.m_is_end = true;
		}
	}
	//文字「へるぷ」にマウスが当たっているとき
	else if (HitSelectUI(PauseItemTexCategory::Help) == true)
	{
		//選択した場合
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_pauseitem_info.m_is_help = true;
		}
	}
	else
	{
		m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Select].y = -400.0f;
		//音が連続再生しないようにする
		SoundController::Instance()->ResetSelectFlag();
	}
}

//ポーズ中UI当たり判定関数
bool PauseItemUI::HitSelectUI(PauseItemTexCategory category_)
{
	//引数の文字項目にマウスが当たっているとき
	if (Collision::RectAndPoint(m_pauseitem_info.m_ui_pos[(__int8)category_], D3DXVECTOR2(Inputter::Instance()->GetMousePos().x, Inputter::Instance()->GetMousePos().y),
		m_pauseitem_info.m_ui_tex[(__int8)category_].Width, m_pauseitem_info.m_ui_tex[(__int8)category_].Height) == true)
	{
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//選択中テクスチャを引数の文字項目に合わせる
		m_pauseitem_info.m_ui_pos[(__int8)PauseItemTexCategory::Select] = m_pauseitem_info.m_ui_pos[(__int8)category_];

		return true;
	}
	else
	{
		return false;
	}
}

//ヘルプ画面切り替え関数
void PauseItemUI::HelpMode()
{
	if (Inputter::Instance()->OnMouseDown(Inputter::Left))
	{
		m_pauseitem_info.m_is_help = false;
	}
}

//テクスチャ解放関数
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