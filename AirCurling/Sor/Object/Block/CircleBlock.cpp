#include "CircleBlock.h"

//!コンストラクタ
CircleBlock::CircleBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, float radius_, std::string key_)
{
	m_circle_block_info.key = key_;        //!描画用キー

	m_circle_block_info.pos = pos_;        //!座標
	m_circle_block_info.radius = radius_;  //!半径

	m_circle_block_info.scale = scale_;    //!描画サイズ
	m_circle_block_info.angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //!回転角度

	//!ワールド座標
	m_circle_block_info.mat_world = Calculation::Matrix(m_circle_block_info.pos, m_circle_block_info.scale, m_circle_block_info.angle);
}

//!描画情報送信関数
void CircleBlock::SetUpDrawBuffer()
{
	FbxController::Instance()->DrawFbx(m_circle_block_info.key, m_circle_block_info.mat_world);
}
