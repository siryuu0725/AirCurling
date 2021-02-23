#include "RectBlock.h"

//!コンストラクタ
RectBlock::RectBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_)
{
	m_rect_block_info.m_key = key_;       //!描画用キー

	m_rect_block_info.m_pos = pos_;       //!座標
	m_rect_block_info.m_width = width_;   //!横幅
	m_rect_block_info.m_height = height_; //!縦幅


	m_rect_block_info.m_scale = scale_;   //!描画サイズ
	m_rect_block_info.m_angle = angle_;   //!回転角度

	//!ワールド座標
	m_rect_block_info.m_mat_world = Calculation::Matrix(m_rect_block_info.m_pos, m_rect_block_info.m_scale, m_rect_block_info.m_angle);
}

//!描画情報送信関数
void RectBlock::SetUpDrawBuffer()
{
	FbxController::Instance()->DrawFbx(m_rect_block_info.m_key, m_rect_block_info.m_mat_world);
}

//!FBXモデル解放関数
void RectBlock::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_rect_block_info.m_key);
}
