﻿#include "GoalFloor.h"
#include "../../Object/Player.h"

//!初期化関数
void Goal::Init(std::string stage_str_)
{
	//!外部データ読み込み
	LoadGoalExternalInfo(stage_str_);

	m_goal_info.m_key = "goal";  //!描画用キー

	m_goal_info.m_pos = m_goal_externalinfo.m_pos;       //!座標
	m_goal_info.m_scale = m_goal_externalinfo.m_scale;   //!描画サイズ
	m_goal_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //!回転角度

	m_goal_info.m_mat_world = Calculation::Matrix(m_goal_info.m_pos, m_goal_info.m_scale, m_goal_info.m_angle); //!ワールド座標

	m_goal_info.m_red_radius = m_goal_externalinfo.m_red_radius;
	m_goal_info.m_yellow_radius = m_goal_externalinfo.m_yellow_radius;
	m_goal_info.m_green_radius = m_goal_externalinfo.m_green_radius;

}

//!外部データ読み込み関数
void Goal::LoadGoalExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "GoalData.dat";

	//!ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		//!書き込む
		fread(&m_goal_externalinfo, sizeof(GoalExternalInfo), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!描画情報送信関数
void Goal::Draw()
{
	FbxController::Instance()->DrawFbx(m_goal_info.m_key, m_goal_info.m_mat_world);
}

//!FBXモデル解放関数
void Goal::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_goal_info.m_key);
}
