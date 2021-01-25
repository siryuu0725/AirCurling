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
		fread(&goal_info_copy, sizeof(ObjectInfoCopy), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	m_goal_info.key = "goal";  //!描画用キー

	m_goal_info.pos = D3DXVECTOR3(goal_info_copy.pos_x, goal_info_copy.pos_y, goal_info_copy.pos_z);          //!座標
	m_goal_info.scale = D3DXVECTOR3(goal_info_copy.scale_x, goal_info_copy.scale_y, goal_info_copy.scale_z);  //!描画サイズ
	m_goal_info.angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //!回転角度

	m_goal_info.mat_world = Calculation::Matrix(m_goal_info.pos, m_goal_info.scale, m_goal_info.angle); //!ワールド座標
}

//!描画情報送信関数
void Goal::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_goal_info.key, m_goal_info.mat_world);
}

