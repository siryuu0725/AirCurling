#include "Floor.h"

//!初期化関数
void Floor::Init(std::string stage_str_)
{
	//!外部データ読み込み
	LoadFloorExternalInfo(stage_str_);

	m_floor_info.m_key = "stage"; //!描画用キー

	m_floor_info.m_pos = D3DXVECTOR3(m_floor_info_copy.pos[ARRAY_DATA::X], m_floor_info_copy.pos[ARRAY_DATA::Y], m_floor_info_copy.pos[ARRAY_DATA::Z]);         //!座標
	m_floor_info.m_scale = D3DXVECTOR3(m_floor_info_copy.scale[ARRAY_DATA::X], m_floor_info_copy.scale[ARRAY_DATA::Y], m_floor_info_copy.scale[ARRAY_DATA::Z]); //!描画サイズ
	m_floor_info.m_angle = D3DXVECTOR3(m_floor_info_copy.rote[ARRAY_DATA::X], m_floor_info_copy.rote[ARRAY_DATA::Y], m_floor_info_copy.rote[ARRAY_DATA::Z]);     //!回転角度

	m_floor_info.m_mat_world = Calculation::Matrix(m_floor_info.m_pos, m_floor_info.m_scale, m_floor_info.m_angle);      //!ワールド座標

	m_floor_info.m_width = m_floor_info_copy.width;   //!横幅
	m_floor_info.m_height = m_floor_info_copy.height; //!縦幅
}

//!外部データ読み込み関数
void Floor::LoadFloorExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string stage_id = "Res/ObjectData/" + stage_str_ + "FloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		//!書き込む
		fread(&m_floor_info_copy, sizeof(FloorExternalInfo), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!描画情報送信関数
void Floor::Draw()
{
	FbxController::Instance()->DrawFbx(m_floor_info.m_key, m_floor_info.m_mat_world);

}

//!FBXモデル解放関数
void Floor::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_floor_info.m_key);
}
