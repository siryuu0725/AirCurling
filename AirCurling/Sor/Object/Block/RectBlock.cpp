#include "RectBlock.h"

//!コンストラクタ
RectBlock::RectBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_)
{
	m_rect_block_info.key = key_;       //!描画用キー

	m_rect_block_info.pos = pos_;       //!座標
	m_rect_block_info.width = width_;   //!横幅
	m_rect_block_info.height = height_; //!縦幅


	m_rect_block_info.scale = scale_;   //!描画サイズ
	m_rect_block_info.angle = angle_;   //!回転角度

	//!ワールド座標
	m_rect_block_info.mat_world = Calculation::Matrix(m_rect_block_info.pos, m_rect_block_info.scale, m_rect_block_info.angle);
}

//!描画情報送信関数
void RectBlock::SetUpDrawBuffer()
{
	FbxController::Instance()->DrawFbx(m_rect_block_info.key, m_rect_block_info.mat_world);
}
