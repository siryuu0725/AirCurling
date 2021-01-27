#include "Sky.h"

//!初期化関数
void SkyDome::Init(std::string stage_id_)
{
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "SkyDomeData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");
	
	if (fp != nullptr)
	{
		//!書き込む
		fread(&skydome_info_copy, sizeof(ObjectInfoCopy), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	m_skydome_info.m_key = "skydome";  //!描画用キー

	m_skydome_info.m_pos = D3DXVECTOR3(skydome_info_copy.pos_x, skydome_info_copy.pos_y, skydome_info_copy.pos_z);   //!座標
	m_skydome_info.m_scale = D3DXVECTOR3(skydome_info_copy.scale_x, skydome_info_copy.scale_y, skydome_info_copy.scale_z);	//!描画サイズ
	m_skydome_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!回転角度

	m_skydome_info.m_mat_world = Calculation::Matrix(m_skydome_info.m_pos, m_skydome_info.m_scale, m_skydome_info.m_angle);  //!ワールド座標
}

//!描画情報送信関数
void SkyDome::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_skydome_info.m_key, m_skydome_info.m_mat_world);
}

//!コンストラクタ
SkyFloor::SkyFloor()
{
	
}

//!初期化関数
void SkyFloor::Init(std::string stage_id_)
{
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "SkyFloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		//rectdata = new RectData[head_data.DataNum];

		// 書き込む
		fread(&skyfloor_info_copy, sizeof(ObjectInfoCopy), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	m_skyfloor_info.m_key = "skyfloor";//!描画用キー

	m_skyfloor_info.m_pos   = D3DXVECTOR3(skyfloor_info_copy.pos_x, skyfloor_info_copy.pos_y, skyfloor_info_copy.pos_z); //!座標
	m_skyfloor_info.m_scale = D3DXVECTOR3(skyfloor_info_copy.scale_x, skyfloor_info_copy.scale_y, skyfloor_info_copy.scale_z);   //!描画サイズ
	m_skyfloor_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //!回転角度

	m_skyfloor_info.m_mat_world = Calculation::Matrix(m_skyfloor_info.m_pos, m_skyfloor_info.m_scale, m_skyfloor_info.m_angle);  //!ワールド座標
}

//!描画情報送信関数
void SkyFloor::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_skyfloor_info.m_key, m_skyfloor_info.m_mat_world);
}
