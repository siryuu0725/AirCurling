#include "StopFloor.h"

StopFloor::StopFloor(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 angle_, float width_, float height_, std::string key_)
{
	m_stop_floor_info.m_key = key_; //!描画用キー

	m_stop_floor_info.m_pos = pos_;      //!座標
	m_stop_floor_info.m_scale = scale_;  //!描画用サイズ
	m_stop_floor_info.m_angle = angle_;  //!回転角度

	m_stop_floor_info.m_mat_world = Calculation::Matrix(m_stop_floor_info.m_pos, m_stop_floor_info.m_scale, m_stop_floor_info.m_angle);//!ワールド座標

	m_stop_floor_info.m_width = width_;   //!横幅
	m_stop_floor_info.m_height = height_; //!縦幅
}

//!描画情報送信関数
void StopFloor::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_stop_floor_info.m_key, m_stop_floor_info.m_mat_world);
}

//void StopFloor::ReleaseFbx()
//{
//	MyFbxManager::FbxManager::Instance()->ReleaseFbxMesh("stop");
//
//}