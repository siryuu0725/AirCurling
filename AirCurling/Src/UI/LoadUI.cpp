#include "LoadUI.h"
#include "../Utility/Calculation.h"

//!初期化関数
void LoadUI::Init()
{
	m_loadui_info.left_top_pos = D3DXVECTOR2(1720.0f, 960.0f);
	m_loadui_info.left_down_pos = D3DXVECTOR2(1720.0f, 1070.0f);
	m_loadui_info.right_top_pos = D3DXVECTOR2(1840.0f, 960.0f);
	m_loadui_info.right_down_pos = D3DXVECTOR2(1840.0f, 1070.0f);

	m_loadui_info.m_rote_angle = 1.5f;
	m_loadui_info.m_center_pos = D3DXVECTOR2(m_loadui_info.left_top_pos.x + 60.0f, m_loadui_info.left_top_pos.y + 55.0f);
	m_loadui_info.m_rote_timer = 0;

	m_loadui_info.m_rote_angle = 1.5f;

	m_loadui_info.m_nowload_pos = D3DXVECTOR2(1000.0f, 940.0f);

	//!テクスチャ読み込み
	LoadTex();
}

//!テクスチャ読み込み関数
void LoadUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/LoadingIcon.png", &m_loadui_info.m_ui_tex[(int)LoadUICategory::RoteTex]);
	Graphics::Instance()->LoadTexture("Res/Tex/NowLoading.png", &m_loadui_info.m_ui_tex[(int)LoadUICategory::NowLoad]);
}

//!描画情報送信関数
void LoadUI::Draw()
{
	Graphics::Instance()->DrawRoteTexture(&m_loadui_info.m_ui_tex[(int)LoadUICategory::RoteTex], m_loadui_info.left_top_pos, m_loadui_info.right_top_pos, m_loadui_info.left_down_pos, m_loadui_info.right_down_pos);
	Graphics::Instance()->DrawTexture(&m_loadui_info.m_ui_tex[(int)LoadUICategory::NowLoad], m_loadui_info.m_nowload_pos);
}

//!更新関数
void LoadUI::Update()
{
	LoadTexRote();
}

//!テクスチャ解放関数
void LoadUI::ReleaseTex()
{
	for (int i = 0; i < (int)LoadUICategory::CategoryMax; i++)
	{
		if (&m_loadui_info.m_ui_tex[i] != nullptr)
		{
			m_loadui_info.m_ui_tex[i].Texture->Release();
			m_loadui_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}

//!ロード中テクスチャ回転関数
void LoadUI::LoadTexRote()
{
	/* 回転用olpos */
	D3DXVECTOR3 rote_pos = D3DXVECTOR3(m_loadui_info.left_top_pos.x, 0.0f, m_loadui_info.left_top_pos.y);
	D3DXVECTOR3 rote_pos2 = D3DXVECTOR3(m_loadui_info.left_down_pos.x, 0.0f, m_loadui_info.left_down_pos.y);
	D3DXVECTOR3 rote_pos3 = D3DXVECTOR3(m_loadui_info.right_top_pos.x, 0.0f, m_loadui_info.right_top_pos.y);
	D3DXVECTOR3 rote_pos4 = D3DXVECTOR3(m_loadui_info.right_down_pos.x, 0.0f, m_loadui_info.right_down_pos.y);

	D3DXVECTOR3 center_pos= D3DXVECTOR3(m_loadui_info.m_center_pos.x, 0.0f, m_loadui_info.m_center_pos.y);

	//!各頂点を回転
	//!左上
	m_loadui_info.left_top_pos.x = Calculation::Rote(rote_pos, center_pos, m_loadui_info.m_rote_angle).x;
	m_loadui_info.left_top_pos.y = Calculation::Rote(rote_pos, center_pos, m_loadui_info.m_rote_angle).z;
	//!左下
	m_loadui_info.left_down_pos.x = Calculation::Rote(rote_pos2, center_pos, m_loadui_info.m_rote_angle).x;
	m_loadui_info.left_down_pos.y = Calculation::Rote(rote_pos2, center_pos, m_loadui_info.m_rote_angle).z;
	//右上
	m_loadui_info.right_top_pos.x = Calculation::Rote(rote_pos3, center_pos, m_loadui_info.m_rote_angle).x;
	m_loadui_info.right_top_pos.y = Calculation::Rote(rote_pos3, center_pos, m_loadui_info.m_rote_angle).z;
	//!右下
	m_loadui_info.right_down_pos.x = Calculation::Rote(rote_pos4, center_pos, m_loadui_info.m_rote_angle).x;
	m_loadui_info.right_down_pos.y = Calculation::Rote(rote_pos4, center_pos, m_loadui_info.m_rote_angle).z;

}
