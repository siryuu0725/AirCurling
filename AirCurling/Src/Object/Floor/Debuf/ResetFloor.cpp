#include "ResetFloor.h"

//コンストラクタ
ResetFloor::ResetFloor(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, float radius_, std::string key_)
{
	m_resetfloor_info.m_key = key_;  //描画用キー

	m_resetfloor_info.m_pos = pos_;      //座標
	m_resetfloor_info.m_scale = scale_;  //描画サイズ
	m_resetfloor_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //回転角度


	m_resetfloor_info.m_mat_world = Calculation::Matrix(m_resetfloor_info.m_pos, m_resetfloor_info.m_scale, m_resetfloor_info.m_angle); //!ワールド座標

	m_resetfloor_info.m_radius = radius_; //半径
}


//描画情報送信関数
void ResetFloor::Draw()
{
	FbxController::Instance()->DrawFbx(m_resetfloor_info.m_key, m_resetfloor_info.m_mat_world);
}

//FBXモデル解放関数
void ResetFloor::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_resetfloor_info.m_key);
}
