#include "Floor.h"

//初期化関数
void Floor::Init(std::string stage_str_)
{
	//外部データ読み込み
	LoadFloorExternalInfo(stage_str_);

	m_floor_info.m_key = "stage"; //描画用キー

	m_floor_info.m_pos = m_floor_externalinfo.m_pos;      //座標
	m_floor_info.m_scale = m_floor_externalinfo.m_scale;  //描画サイズ
	m_floor_info.m_angle = m_floor_externalinfo.m_rote;   //回転角度

	m_floor_info.m_mat_world = Calculation::Matrix(m_floor_info.m_pos, m_floor_info.m_scale, m_floor_info.m_angle);  //ワールド座標

	m_floor_info.m_width = m_floor_externalinfo.m_width;   //横幅
	m_floor_info.m_height = m_floor_externalinfo.m_height; //縦幅
}

//外部データ読み込み関数
void Floor::LoadFloorExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "FloorData.dat";

	//ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		//書き込む
		fread(&m_floor_externalinfo, sizeof(FloorExternalInfo), 1, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//描画情報送信関数
void Floor::Draw()
{
	FbxController::Instance()->DrawFbx(m_floor_info.m_key, m_floor_info.m_mat_world);

}

//FBXモデル解放関数
void Floor::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_floor_info.m_key);
}
