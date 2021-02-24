#include "RectBlock.h"

//!コンストラクタ
RectBlock::RectBlock(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_)
{
	m_rectblock_info.m_key = key_;       //!描画用キー

	m_rectblock_info.m_pos = pos_;       //!座標
	m_rectblock_info.m_width = width_;   //!横幅
	m_rectblock_info.m_height = height_; //!縦幅


	m_rectblock_info.m_scale = scale_;   //!描画サイズ
	m_rectblock_info.m_angle = angle_;   //!回転角度

	//!ワールド座標
	m_rectblock_info.m_mat_world = Calculation::Matrix(m_rectblock_info.m_pos, m_rectblock_info.m_scale, m_rectblock_info.m_angle);
}

//!描画情報送信関数
void RectBlock::Draw()
{
	FbxController::Instance()->DrawFbx(m_rectblock_info.m_key, m_rectblock_info.m_mat_world);
}

//!FBXモデル解放関数
void RectBlock::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_rectblock_info.m_key);
}
