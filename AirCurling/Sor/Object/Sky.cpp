#include "Sky.h"

//!初期化関数
void SkyDome::Init(std::string stage_id_)
{
	FILE* fp = nullptr;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "SkyDomeData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");
	
	if (fp != nullptr)
	{
		//!書き込む
		fread(&m_skydome_info_copy, sizeof(SkyDomeExternalInfo), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	m_skydome_info.m_key = "skydome";  //!描画用キー

	m_skydome_info.m_pos = D3DXVECTOR3(m_skydome_info_copy.pos[ARRAY_DATA::X], m_skydome_info_copy.pos[ARRAY_DATA::Y], m_skydome_info_copy.pos[ARRAY_DATA::Z]);   //!座標
	m_skydome_info.m_scale = D3DXVECTOR3(m_skydome_info_copy.scale[ARRAY_DATA::X], m_skydome_info_copy.scale[ARRAY_DATA::Y], m_skydome_info_copy.scale[ARRAY_DATA::Z]);	//!描画サイズ
	m_skydome_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!回転角度

	m_skydome_info.m_mat_world = Calculation::Matrix(m_skydome_info.m_pos, m_skydome_info.m_scale, m_skydome_info.m_angle);  //!ワールド座標
}

//!描画情報送信関数
void SkyDome::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_skydome_info.m_key, m_skydome_info.m_mat_world);
}

//!FBXモデル解放関数
void SkyDome::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_skydome_info.m_key);
}

//!初期化関数
void SkyFloor::Init(std::string stage_id_)
{
	FILE* fp = nullptr;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "SkyFloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		//rectdata = new RectData[head_data.DataNum];

		// 書き込む
		fread(&m_skyfloor_info_copy, sizeof(SkyFloorExternalInfo), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	m_skyfloor_info.m_key = "skyfloor";//!描画用キー

	m_skyfloor_info.m_pos   = D3DXVECTOR3(m_skyfloor_info_copy.pos[ARRAY_DATA::X], m_skyfloor_info_copy.pos[ARRAY_DATA::Y], m_skyfloor_info_copy.pos[ARRAY_DATA::Z]); //!座標
	m_skyfloor_info.m_scale = D3DXVECTOR3(m_skyfloor_info_copy.scale[ARRAY_DATA::X], m_skyfloor_info_copy.scale[ARRAY_DATA::Y], m_skyfloor_info_copy.scale[ARRAY_DATA::Z]);   //!描画サイズ
	m_skyfloor_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //!回転角度

	m_skyfloor_info.m_mat_world = Calculation::Matrix(m_skyfloor_info.m_pos, m_skyfloor_info.m_scale, m_skyfloor_info.m_angle);  //!ワールド座標
}

//!描画情報送信関数
void SkyFloor::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_skyfloor_info.m_key, m_skyfloor_info.m_mat_world);
}

//!FBXモデル解放関数
void SkyFloor::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_skyfloor_info.m_key);
}
