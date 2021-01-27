#include "ResetFloor.h"

ResetFloor::ResetFloor(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, float radius_, std::string key_)
{
	m_reset_floor_info.m_key = key_;  //!描画用キー

	m_reset_floor_info.m_pos = pos_;      //!座標
	m_reset_floor_info.m_scale = scale_;  //!描画サイズ
	m_reset_floor_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //!回転角度


	m_reset_floor_info.m_mat_world = Calculation::Matrix(m_reset_floor_info.m_pos, m_reset_floor_info.m_scale, m_reset_floor_info.m_angle); //!ワールド座標

	m_reset_floor_info.m_radius = radius_; //!半径
}


//!描画情報送信関数
void ResetFloor::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_reset_floor_info.m_key, m_reset_floor_info.m_mat_world);
}

//void ResetFloor::ReleaseFbx()
//{
//	MyFbxManager::FbxManager::Instance()->ReleaseFbxMesh("reset");
//
//}