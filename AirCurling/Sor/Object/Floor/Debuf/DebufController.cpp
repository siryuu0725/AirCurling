#include "DebufController.h"

//!デストラクタ
DebufController::~DebufController()
{
	//!リセット床
	for (__int16 i = 0; i < m_reset_floor.size(); i++)
	{
		delete m_reset_floor[i];
		m_reset_floor[i] = nullptr;
	}

	//!スピード減衰床
	for (__int16 i = 0; i < m_stop_floor.size(); i++)
	{
		delete m_stop_floor[i];
		m_stop_floor[i] = nullptr;
	}
}

//!初期化関数
void DebufController::Init(std::string stage_str_)
{
	//!外部データ読み込み
	LoadResetFloorExternalInfo(stage_str_);
	LoadStopFloorExternalInfo(stage_str_);

	//!リセット床
	for (__int16 i = 0; i < m_resetfloor_num; i++)
	{
		//!読み込んだ数分追加
		m_reset_floor.push_back(new ResetFloor
		(D3DXVECTOR3(m_resetfloor_info_copy[i].pos[ARRAY_DATA::X], m_resetfloor_info_copy[i].pos[ARRAY_DATA::Y], m_resetfloor_info_copy[i].pos[ARRAY_DATA::Z]),
		 D3DXVECTOR3(m_resetfloor_info_copy[i].scale[ARRAY_DATA::X], m_resetfloor_info_copy[i].scale[ARRAY_DATA::Y], m_resetfloor_info_copy[i].scale[ARRAY_DATA::Z]),
		 m_resetfloor_info_copy[i].radius, "reset"));

		//あたり判定用に追加
		m_reset_shape.push_back(new CircleShape(m_reset_floor[i]->GetObjInfo()->m_pos, m_reset_floor[i]->GetObjInfo()->m_radius));
	}

	//!スピード減衰床
	for (__int16 i = 0; i < m_stopfloor_num; i++)
	{
		//!読み込んだ数分追加
		m_stop_floor.push_back(new StopFloor
		(D3DXVECTOR3(m_stopfloor_info_copy[i].pos[ARRAY_DATA::X], m_stopfloor_info_copy[i].pos[ARRAY_DATA::Y], m_stopfloor_info_copy[i].pos[ARRAY_DATA::Z]),
		 D3DXVECTOR3(m_stopfloor_info_copy[i].scale[ARRAY_DATA::X], m_stopfloor_info_copy[i].scale[ARRAY_DATA::Y], m_stopfloor_info_copy[i].scale[ARRAY_DATA::Z]),
		 D3DXVECTOR3(m_stopfloor_info_copy[i].rote[ARRAY_DATA::X], m_stopfloor_info_copy[i].rote[ARRAY_DATA::Y], m_stopfloor_info_copy[i].rote[ARRAY_DATA::Z]),
		 m_stopfloor_info_copy[i].width, m_stopfloor_info_copy[i].height, "stop"));

		//あたり判定用に追加
		m_stop_shape.push_back(new RectShape(m_stop_floor[i]->GetObjInfo()->m_pos, m_stop_floor[i]->GetObjInfo()->m_width, m_stop_floor[i]->GetObjInfo()->m_height, m_stop_floor[i]->GetObjInfo()->m_angle.y));
	}
}

//!外部データ読み込み関数(リセット床)
void DebufController::LoadResetFloorExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string stage_id = "Res/ObjectData/" + stage_str_ + "ResetFloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");


	if (fp != nullptr)
	{
		fread(&m_resetfloor_num, sizeof(m_resetfloor_num), 1, fp);

		//!書き込む
		fread(&m_resetfloor_info_copy, sizeof(ResetFloorExternalInfo), m_resetfloor_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!外部データ読み込み関数(スピード減衰床)
void DebufController::LoadStopFloorExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string stage_id = "Res/ObjectData/" + stage_str_ + "StopFloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_stopfloor_num, sizeof(m_stopfloor_num), 1, fp);

		//!書き込む
		fread(&m_stopfloor_info_copy, sizeof(StopFloorExternalInfo), m_stopfloor_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!描画情報送信関数
void DebufController::SetUpBuffer()
{
	//!リセット床
	for (__int16 i = 0; i < m_reset_floor.size(); i++)
	{
		m_reset_floor[i]->SetUpBuffer();
	}

	//!スピード減衰床
	for (__int16 i = 0; i < m_stop_floor.size(); i++)
	{
		m_stop_floor[i]->SetUpBuffer();
	}
}

//!FBXモデル解放関数
void DebufController::ReleaseModel()
{
	//!リセット床
	for (__int16 i = 0; i < m_reset_floor.size(); i++)
	{
		m_reset_floor[i]->ReleaseModel();
	}

	//!スピード減衰床
	for (__int16 i = 0; i < m_stop_floor.size(); i++)
	{
		m_stop_floor[i]->ReleaseModel();
	}

}
