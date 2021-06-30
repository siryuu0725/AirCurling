#include "LoadIconUI.h"

//初期化関数
void LoadIconUI::Init()
{
	//座標初期化
	m_loadicon_info.m_ui_pos = m_external_pos[(__int8)LoadIconTexCategory::RotTex];

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/LoadingIcon.png", &m_loadicon_info.m_ui_tex);

	m_loadicon_info.left_top_pos = m_loadicon_info.m_ui_pos;
	m_loadicon_info.left_down_pos = D3DXVECTOR2(m_loadicon_info.m_ui_pos.x, m_loadicon_info.m_ui_pos.y + m_loadicon_info.m_ui_tex.Height);
	m_loadicon_info.right_top_pos = D3DXVECTOR2(m_loadicon_info.m_ui_pos.x + m_loadicon_info.m_ui_tex.Width, m_loadicon_info.m_ui_pos.y);
	m_loadicon_info.right_down_pos = D3DXVECTOR2(m_loadicon_info.m_ui_pos.x + m_loadicon_info.m_ui_tex.Width, m_loadicon_info.m_ui_pos.y + m_loadicon_info.m_ui_tex.Height);

	m_loadicon_info.m_rot_angle = 1.5f;
	m_loadicon_info.m_center_pos = D3DXVECTOR2(m_loadicon_info.left_top_pos.x + 60.0f, m_loadicon_info.left_top_pos.y + 55.0f);
	m_loadicon_info.m_rot_timer = 0;

	m_loadicon_info.m_rot_angle = 1.5f;


	m_loadicon_info.left_top_pos = D3DXVECTOR2(1720.0f, 960.0f);
	m_loadicon_info.left_down_pos = D3DXVECTOR2(1720.0f, 1070.0f);
	m_loadicon_info.right_top_pos = D3DXVECTOR2(1840.0f, 960.0f);
	m_loadicon_info.right_down_pos = D3DXVECTOR2(1840.0f, 1070.0f);

	m_loadicon_info.m_rot_angle = 1.5f;
	m_loadicon_info.m_center_pos = D3DXVECTOR2(m_loadicon_info.left_top_pos.x + 60.0f, m_loadicon_info.left_top_pos.y + 55.0f);
}

//更新関数
void LoadIconUI::Update()
{
	//回転用olpos
	D3DXVECTOR3 rot_pos(m_loadicon_info.left_top_pos.x, 0.0f, m_loadicon_info.left_top_pos.y);
	D3DXVECTOR3 rot_pos2(m_loadicon_info.left_down_pos.x, 0.0f, m_loadicon_info.left_down_pos.y);
	D3DXVECTOR3 rot_pos3(m_loadicon_info.right_top_pos.x, 0.0f, m_loadicon_info.right_top_pos.y);
	D3DXVECTOR3 rot_pos4(m_loadicon_info.right_down_pos.x, 0.0f, m_loadicon_info.right_down_pos.y);

	D3DXVECTOR3 center_pos(m_loadicon_info.m_center_pos.x, 0.0f, m_loadicon_info.m_center_pos.y);

	//各頂点を回転
	//左上
	m_loadicon_info.left_top_pos.x = Calculation::Rotate_Y(rot_pos, center_pos, m_loadicon_info.m_rot_angle).x;
	m_loadicon_info.left_top_pos.y = Calculation::Rotate_Y(rot_pos, center_pos, m_loadicon_info.m_rot_angle).z;
	//左下
	m_loadicon_info.left_down_pos.x = Calculation::Rotate_Y(rot_pos2, center_pos, m_loadicon_info.m_rot_angle).x;
	m_loadicon_info.left_down_pos.y = Calculation::Rotate_Y(rot_pos2, center_pos, m_loadicon_info.m_rot_angle).z;
	//右上																   
	m_loadicon_info.right_top_pos.x = Calculation::Rotate_Y(rot_pos3, center_pos, m_loadicon_info.m_rot_angle).x;
	m_loadicon_info.right_top_pos.y = Calculation::Rotate_Y(rot_pos3, center_pos, m_loadicon_info.m_rot_angle).z;
	//右下
	m_loadicon_info.right_down_pos.x = Calculation::Rotate_Y(rot_pos4, center_pos, m_loadicon_info.m_rot_angle).x;
	m_loadicon_info.right_down_pos.y = Calculation::Rotate_Y(rot_pos4, center_pos, m_loadicon_info.m_rot_angle).z;
}

//描画情報送信関数
void LoadIconUI::Draw()
{
	Graphics::Instance()->DrawRotTexture(&m_loadicon_info.m_ui_tex,
		m_loadicon_info.left_top_pos,
		m_loadicon_info.right_top_pos,
		m_loadicon_info.left_down_pos,
		m_loadicon_info.right_down_pos);
}

//テクスチャ解放関数
void LoadIconUI::ReleaseTex()
{
	m_loadicon_info.m_ui_tex.Texture->Release();
	m_loadicon_info.m_ui_tex.Texture = nullptr;
}
