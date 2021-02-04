#include "GoalFloor.h"
#include "../../Object/Player.h"

//!初期化関数
void Goal::Init(std::string stage_id_)
{
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "GoalData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{

		//!書き込む
		fread(&m_goal_info_copy, sizeof(ObjectInfoCopy), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	m_goal_info.m_key = "goal";  //!描画用キー

	m_goal_info.m_pos = D3DXVECTOR3(m_goal_info_copy.pos_x, m_goal_info_copy.pos_y, m_goal_info_copy.pos_z);          //!座標
	m_goal_info.m_scale = D3DXVECTOR3(m_goal_info_copy.scale_x, m_goal_info_copy.scale_y, m_goal_info_copy.scale_z);  //!描画サイズ
	m_goal_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //!回転角度

	m_goal_info.m_mat_world = Calculation::Matrix(m_goal_info.m_pos, m_goal_info.m_scale, m_goal_info.m_angle); //!ワールド座標
}

//!描画情報送信関数
void Goal::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_goal_info.m_key, m_goal_info.m_mat_world);
}

