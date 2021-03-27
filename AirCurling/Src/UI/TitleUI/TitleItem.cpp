#include "TitleItem.h"

//初期化関数
void TitleItem::Init()
{
	//座標初期化
	for (__int8 i = 0; i < (__int8)TitleItemTexCategory::CategoryMax; i++)
	{
		m_titleitem_info.m_ui_pos[i] = m_external_pos[i];
	}
	
	//テクスチャ読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Title_Hazimeru.png", &m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Start]);
	Graphics::Instance()->LoadTexture("Res/Tex/Title_Owaru.png", &m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::End]);
	Graphics::Instance()->LoadTexture("Res/Tex/Title_Help.png", &m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Help]);
	Graphics::Instance()->LoadTexture("Res/Tex/Title_SelectFrame.png", &m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::NowSelect]);

	m_titleitem_info.m_is_start = false; //ゲームシーン移行フラグ
	m_titleitem_info.m_is_end = false;	 //終了フラグ
	m_titleitem_info.m_is_help = false;	 //ヘルプシーン移行フラグ
}

//更新関数
void TitleItem::Update()
{
	if (m_titleitem_info.m_is_help == true)
	{
		if (Inputter::Instance()->GetKeyDown(Inputter::ESCKey) ||
			Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			m_titleitem_info.m_is_help = false;
		}
	}
	//文字「はじめる」との当たり判定
	else if (Collision::RectAndPoint(m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::Start],
		D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Start].Width, m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Start].Height) == true)
	{
		//選択枠テクスチャの座標を代入
		m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect].x = 210.0f;
		m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect].y = 400.0f;

		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//「はじめる」が押されたフラグtrue
			m_titleitem_info.m_is_start = true;
		}
	}
	//文字「おわる」との当たり判定
	else if (Collision::RectAndPoint(m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::End],
		D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::End].Width, m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::End].Height) == true)
	{
		//選択枠テクスチャの座標を代入
		m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect].x = 210.0f;
		m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect].y = 600.0f;

		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//「おわる」が押されたフラグtrue
			m_titleitem_info.m_is_end = true;
		}
	}
	//文字「ヘルプ」との当たり判定
	else if (Collision::RectAndPoint(m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::Help],
		D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Help].Width, m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Help].Height) == true)
	{
		//選択枠テクスチャの座標を代入
		m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect].x = 210.0f;
		m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect].y = 800.0f;

		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//「ヘルプ」が押されたフラグtrue
			m_titleitem_info.m_is_help = true;
		}
	}
	else
	{
		//選択枠テクスチャの座標を代入
		m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect].y = -300.0f;

		SoundController::Instance()->ResetSelectFlag();
	}

	
}

//描画情報送信関数
void TitleItem::Draw()
{
	//「はじめる」「ヘルプ」が押されていない間
	if (m_titleitem_info.m_is_start == false && m_titleitem_info.m_is_help == false)
	{
		Graphics::Instance()->DrawTexture(&m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Start], m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::Start]);
		Graphics::Instance()->DrawTexture(&m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::End], m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::End]);
		Graphics::Instance()->DrawTexture(&m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::Help], m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::Help]);
		Graphics::Instance()->DrawTexture(&m_titleitem_info.m_ui_tex[(__int8)TitleItemTexCategory::NowSelect], m_titleitem_info.m_ui_pos[(__int8)TitleItemTexCategory::NowSelect]);
	}
}

//テクスチャ解放関数
void TitleItem::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)TitleItemTexCategory::CategoryMax; i++)
	{
		if (&m_titleitem_info.m_ui_tex[i] != nullptr)
		{
			m_titleitem_info.m_ui_tex[i].Texture->Release();
			m_titleitem_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}

//フラグ初期化関数
void TitleItem::FlgReset()
{
	m_titleitem_info.m_is_start = false; //ゲームシーン移行フラグ
	m_titleitem_info.m_is_end = false;	//終了フラグ
	m_titleitem_info.m_is_help = false;	//ヘルプシーン移行フラグ
}
