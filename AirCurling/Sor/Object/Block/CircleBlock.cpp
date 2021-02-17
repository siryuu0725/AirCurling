#include "CircleBlock.h"

//!コンストラクタ
CircleBlock::CircleBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, float radius_, std::string key_)
{
	m_circle_block_info.m_key = key_;        //!描画用キー

	m_circle_block_info.m_pos = pos_;        //!座標
	m_circle_block_info.m_radius = radius_;  //!半径

	m_circle_block_info.m_scale = scale_;    //!描画サイズ
	m_circle_block_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //!回転角度

	//!ワールド座標
	m_circle_block_info.m_mat_world = Calculation::Matrix(m_circle_block_info.m_pos, m_circle_block_info.m_scale, m_circle_block_info.m_angle);
}

//!描画情報送信関数
void CircleBlock::SetUpDrawBuffer()
{
	FbxController::Instance()->DrawFbx(m_circle_block_info.m_key, m_circle_block_info.m_mat_world);
}

//!FBXモデル解放関数
void CircleBlock::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_circle_block_info.m_key);
}
