#include "ProductionUI.h"
#include "../../Object/Player.h"

//初期化関数
void ProductionUI::Init()
{
	//座標初期化
	for (__int8 i = __int8(ProductionTexCategory::Start); i <= __int8(ProductionTexCategory::Finish); i++)
	{
		m_production_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Start.png", &m_production_info.m_ui_tex[(__int8)ProductionTexCategory::Start]);
	Graphics::Instance()->LoadTexture("Res/Tex/Finish.png", &m_production_info.m_ui_tex[(__int8)ProductionTexCategory::Finish]);
	Graphics::Instance()->LoadTexture("Res/Tex/StartFrame.png", &m_production_info.m_ui_tex[(__int8)ProductionTexCategory::Kacco]);

	m_production_info.timer = 0.0f;
	m_production_info.flame = 0.01666667f;

	m_production_info.m_movespeed = 20.0f; //開始演出の文字が動くスピード
	m_production_info.m_is_stop = false;  //開始演出の文字が止まるフラグ
	m_production_info.m_is_remove = false;    //開始演出の文字が再び動くフラグ

	m_production_info.m_is_start_game = false;  //操作可能になるまでのフラグ
	m_production_info.m_is_end_game = false;    //リザルトシーンに移行するフラグ
	m_production_info.m_is_draw_finish = false; //文字「フィニッシュ」の描画フラグ
}

//開始演出関数
void ProductionUI::StartProduction(Camera* camera_)
{
	//画面両サイドから流れてくるようにする
	m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Start].x -= m_production_info.m_movespeed;
	m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Kacco].x += m_production_info.m_movespeed;

	//左右から流れてきたテクスチャの座標が重なり合う位置に来たら
	if (m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Kacco].x >= m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Start].x && m_production_info.m_is_stop == false)
	{
		m_production_info.m_movespeed = 0.0f;
		m_production_info.m_is_stop = true;  //一度テクスチャの移動を止める
	}
	//再び動かせるようになった時
	else if (m_production_info.m_is_remove == true)
	{
		m_production_info.m_movespeed = 20.0f;
	}

	//一度テクスチャがとまった時
	if (m_production_info.m_is_stop == true)
	{
		m_production_info.m_stoptimer++;
		//1秒程止める
		if (m_production_info.m_stoptimer >= StartFontStopTime)
		{
			//再び動かす
			m_production_info.m_is_remove = true;
		}
	}

	//再移動後、画面外にテクスチャが出た時
	if (m_production_info.m_is_remove == true && m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Kacco].x >= StartFontEndPosX)
	{
		m_production_info.m_is_start_game = true;
		camera_->SetCameraOperation(true);

	}
}

//終了演出関数
void ProductionUI::EndProduction()
{
	//テクスチャが画面内にある時
	if (m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Finish].y >= FinishFontEndPosX)
	{
		m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Finish].y += Buoyancy * m_production_info.timer + ((-Gravity) * (m_production_info.timer * m_production_info.timer)) / 2.0f;

		m_production_info.timer += m_production_info.flame;

		m_production_info.m_is_draw_finish = true;
	}
	else
	{
		m_production_info.m_is_end_game = true;
	}
}

//描画情報送信関数
void ProductionUI::Draw()
{
	if (m_production_info.m_is_draw_finish == true)
	{
		Graphics::Instance()->DrawTexture(&m_production_info.m_ui_tex[(__int8)ProductionTexCategory::Finish], m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Finish]);
	}
	else
	{
		Graphics::Instance()->DrawTexture(&m_production_info.m_ui_tex[(__int8)ProductionTexCategory::Start], m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Start]);
		Graphics::Instance()->DrawTexture(&m_production_info.m_ui_tex[(__int8)ProductionTexCategory::Kacco], m_production_info.m_ui_pos[(__int8)ProductionTexCategory::Kacco]);
	}
}

//テクスチャ解放関数
void ProductionUI::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)ProductionTexCategory::CategoryMax; i++)
	{
		if (&m_production_info.m_ui_tex[i] != nullptr)
		{
			m_production_info.m_ui_tex[i].Texture->Release();
			m_production_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
