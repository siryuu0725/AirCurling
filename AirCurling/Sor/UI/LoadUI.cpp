#include "LoadUI.h"
#include "../Utility/Calculation.h"

//!初期化関数
void LoadUI::Init()
{
	load_ui_info.left_top_pos = D3DXVECTOR2(1720.0f, 960.0f);
	load_ui_info.left_down_pos = D3DXVECTOR2(1720.0f, 1070.0f);
	load_ui_info.right_top_pos = D3DXVECTOR2(1840.0f, 960.0f);
	load_ui_info.right_down_pos = D3DXVECTOR2(1840.0f, 1070.0f);

	load_ui_info.m_rote_angle = 1.5f;
	load_ui_info.center_pos = D3DXVECTOR2(load_ui_info.left_top_pos.x + 60.0f, load_ui_info.left_top_pos.y + 55.0f);
	load_ui_info.m_rote_timer = 0;

	load_ui_info.m_rote_angle = 1.5f;

	load_ui_info.nowload_pos = D3DXVECTOR2(1000.0f, 940.0f);

	//!テクスチャ読み込み
	LoadTex();
}

//!テクスチャ読み込み関数
void LoadUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/ローディング中のアイコン1.png", &load_ui_info.ui_tex[(int)LoadUICategory::RoteTex]);
	Graphics::Instance()->LoadTexture("Res/Tex/文字「NowLoading」.png", &load_ui_info.ui_tex[(int)LoadUICategory::NowLoad]);
}

//!描画情報送信関数
void LoadUI::SetUpBuffer()
{
	Graphics::Instance()->DrawRoteTexture(&load_ui_info.ui_tex[(int)LoadUICategory::RoteTex], load_ui_info.left_top_pos, load_ui_info.right_top_pos, load_ui_info.left_down_pos, load_ui_info.right_down_pos);
	Graphics::Instance()->DrawTexture(&load_ui_info.ui_tex[(int)LoadUICategory::NowLoad], load_ui_info.nowload_pos);
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
		if (&load_ui_info.ui_tex[i] != nullptr)
		{
			load_ui_info.ui_tex[i].Texture->Release();
			load_ui_info.ui_tex[i].Texture = nullptr;
		}
	}
}

//!ロード中テクスチャ回転関数
void LoadUI::LoadTexRote()
{
	/* 回転用olpos */
	D3DXVECTOR3 rote_pos = D3DXVECTOR3(load_ui_info.left_top_pos.x, 0.0f, load_ui_info.left_top_pos.y);
	D3DXVECTOR3 rote_pos2 = D3DXVECTOR3(load_ui_info.left_down_pos.x, 0.0f, load_ui_info.left_down_pos.y);
	D3DXVECTOR3 rote_pos3 = D3DXVECTOR3(load_ui_info.right_top_pos.x, 0.0f, load_ui_info.right_top_pos.y);
	D3DXVECTOR3 rote_pos4 = D3DXVECTOR3(load_ui_info.right_down_pos.x, 0.0f, load_ui_info.right_down_pos.y);

	D3DXVECTOR3 center_pos= D3DXVECTOR3(load_ui_info.center_pos.x, 0.0f, load_ui_info.center_pos.y);

	//!各頂点を回転
	//!左上
	load_ui_info.left_top_pos.x = Calculation::Rote(rote_pos, center_pos, load_ui_info.m_rote_angle).x;
	load_ui_info.left_top_pos.y = Calculation::Rote(rote_pos, center_pos, load_ui_info.m_rote_angle).z;
	//!左下
	load_ui_info.left_down_pos.x = Calculation::Rote(rote_pos2, center_pos, load_ui_info.m_rote_angle).x;
	load_ui_info.left_down_pos.y = Calculation::Rote(rote_pos2, center_pos, load_ui_info.m_rote_angle).z;
	//右上
	load_ui_info.right_top_pos.x = Calculation::Rote(rote_pos3, center_pos, load_ui_info.m_rote_angle).x;
	load_ui_info.right_top_pos.y = Calculation::Rote(rote_pos3, center_pos, load_ui_info.m_rote_angle).z;
	//!右下
	load_ui_info.right_down_pos.x = Calculation::Rote(rote_pos4, center_pos, load_ui_info.m_rote_angle).x;
	load_ui_info.right_down_pos.y = Calculation::Rote(rote_pos4, center_pos, load_ui_info.m_rote_angle).z;

}
