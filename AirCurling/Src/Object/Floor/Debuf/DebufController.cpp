#include "DebufController.h"
#include "../../../Utility/Collision/ObjectCollision.h"

//デストラクタ
DebufController::~DebufController()
{
	//リセット床
	for (__int8 i = 0; i < m_resetfloors.size(); i++)
	{
		delete m_resetfloors[i];
		m_resetfloors[i] = nullptr;
	}

	//スピード減衰床
	for (__int8 i = 0; i < m_stopfloors.size(); i++)
	{
		delete m_stopfloors[i];
		m_stopfloors[i] = nullptr;
	}
}

//初期化関数
void DebufController::Init(std::string stage_str_)
{
	ObjectBase::ObjectInfo debuf_floor_info;

	//外部データ読み込み
	LoadResetFloorExternalInfo(stage_str_);
	LoadStopFloorExternalInfo(stage_str_);

	//リセット床
	for (__int8 i = 0; i < m_resetfloor_num; i++)
	{
		//!読み込んだ数分追加
		m_resetfloors.push_back(new ResetFloor
		(m_resetfloor_externalinfo[i].m_pos,
		 m_resetfloor_externalinfo[i].m_scale,
		 m_resetfloor_externalinfo[i].m_radius, "reset"));
	}

	//スピード減衰床
	for (__int8 i = 0; i < m_stopfloor_num; i++)
	{
		//読み込んだ数分追加
		m_stopfloors.push_back(new StopFloor
		(m_stopfloor_externalinfo[i].m_pos,
		 m_stopfloor_externalinfo[i].m_scale,
		 m_stopfloor_externalinfo[i].m_rot_angle,
		 m_stopfloor_externalinfo[i].m_width, m_stopfloor_externalinfo[i].m_height, "stop"));
	}

	SetCollisionInfo(); //当たり判定用情報Set
}

//外部データ読み込み関数(リセット床)
void DebufController::LoadResetFloorExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "ResetFloorData.dat";

	//ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");


	if (fp != nullptr)
	{
		fread(&m_resetfloor_num, sizeof(m_resetfloor_num), 1, fp);

		//書き込む
		fread(&m_resetfloor_externalinfo, sizeof(ResetFloorExternalInfo), m_resetfloor_num, fp);

		//ファイルクローズ 
		fclose(fp);
	}
}

//外部データ読み込み関数(スピード減衰床)
void DebufController::LoadStopFloorExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "StopFloorData.dat";

	//ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_stopfloor_num, sizeof(m_stopfloor_num), 1, fp);

		//書き込む
		fread(&m_stopfloor_externalinfo, sizeof(StopFloorExternalInfo), m_stopfloor_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//当たり判定用情報Set関数
void DebufController::SetCollisionInfo()
{
	//リセット床
	for (__int8 i = 0; i < m_resetfloors.size(); i++)
	{
		ResetFloor::ObjectInfo resetfloor_info;

		m_resetfloors[i]->GetResetFloorInfo(resetfloor_info);

		ObjectCollision::Instance()->SetResetFloorInfo(resetfloor_info);
	}

	//スピード減衰床
	for (__int8 i = 0; i < m_stopfloors.size(); i++)
	{
		StopFloor::ObjectInfo stopfloor_info;

		m_stopfloors[i]->GetStopFloorInfo(stopfloor_info);

		ObjectCollision::Instance()->SetStopFloorInfo(stopfloor_info);
	}
}

//描画情報送信関数
void DebufController::Draw()
{
	//リセット床
	for (__int8 i = 0; i < m_resetfloors.size(); i++)
	{
		m_resetfloors[i]->Draw();
	}

	//スピード減衰床
	for (__int8 i = 0; i < m_stopfloors.size(); i++)
	{
		m_stopfloors[i]->Draw();
	}
}

//FBXモデル解放関数
void DebufController::ReleaseModel()
{
	//リセット床
	for (__int8 i = 0; i < m_resetfloors.size(); i++)
	{
		m_resetfloors[i]->ReleaseModel();
	}

	//スピード減衰床
	for (__int8 i = 0; i < m_stopfloors.size(); i++)
	{
		m_stopfloors[i]->ReleaseModel();
	}

}
