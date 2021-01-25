#include "DebufController.h"

//!デストラクタ
DebufController::~DebufController()
{
	for (int i = 0; i < m_reset_floor.size(); i++)
	{
		delete m_reset_floor[i];
		m_reset_floor[i] = nullptr;
	}

	for (int i = 0; i < m_stop_floor.size(); i++)
	{
		delete m_stop_floor[i];
		m_stop_floor[i] = nullptr;
	}
}

//!ステージ2用初期化関数
void DebufController::Init(std::string stage_id_)
{
#pragma region リセット床
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "ResetFloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");


	if (fp != nullptr)
	{
		fread(&m_resetfloor_num, sizeof(m_resetfloor_num), 1, fp);

		//!書き込む
		fread(&resetfloor_info_copy, sizeof(ResetFloorInfoCopy), m_resetfloor_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	for (int i = 0; i < m_resetfloor_num; i++)
	{
		//!読み込んだ数分追加
		m_reset_floor.push_back(new ResetFloor(D3DXVECTOR3(resetfloor_info_copy[i].pos_x, resetfloor_info_copy[i].pos_y, resetfloor_info_copy[i].pos_z),
			D3DXVECTOR3(resetfloor_info_copy[i].scale_x, resetfloor_info_copy[i].scale_y, resetfloor_info_copy[i].scale_z),
			resetfloor_info_copy[i].radius, "reset"));
	}

	for (int i = 0; i < m_resetfloor_num; i++)
	{
		//あたり判定用に追加
		m_reset_shape.push_back(new CircleShape(m_reset_floor[i]->GetObjInfo()->pos, m_reset_floor[i]->GetObjInfo()->radius));
	}
#pragma endregion

#pragma region スピード減衰床
	fp = NULL;

	stage_id = "Res/ObjectData/" + stage_id_ + "StopFloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_stopfloor_num, sizeof(m_stopfloor_num), 1, fp);

		//!書き込む
		fread(&stopfloor_info_copy, sizeof(StopFloorInfoCopy), m_stopfloor_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	for (int i = 0; i < m_stopfloor_num; i++)
	{
		//!読み込んだ数分追加
		m_stop_floor.push_back(new StopFloor(D3DXVECTOR3(stopfloor_info_copy[i].pos_x, stopfloor_info_copy[i].pos_y, stopfloor_info_copy[i].pos_z),
			D3DXVECTOR3(stopfloor_info_copy[i].scale_x, stopfloor_info_copy[i].scale_y, stopfloor_info_copy[i].scale_z),
			D3DXVECTOR3(stopfloor_info_copy[i].rote_x, stopfloor_info_copy[i].rote_y, stopfloor_info_copy[i].rote_z),
			stopfloor_info_copy[i].width, stopfloor_info_copy[i].height, "stop"));
	}

	for (int i = 0; i < m_stopfloor_num; i++)
	{
		//あたり判定用に追加
		m_stop_shape.push_back(new RectShape(m_stop_floor[i]->GetObjInfo()->pos, m_stop_floor[i]->GetObjInfo()->width, m_stop_floor[i]->GetObjInfo()->height, m_stop_floor[i]->GetObjInfo()->angle.y));
	}

#pragma endregion
}

//!描画情報送信関数
void DebufController::SetUpBuffer()
{
	for (int i = 0; i < m_reset_floor.size(); i++)
	{
		m_reset_floor[i]->SetUpBuffer();
	}

	for (int i = 0; i < m_stop_floor.size(); i++)
	{
		m_stop_floor[i]->SetUpBuffer();
	}
}
