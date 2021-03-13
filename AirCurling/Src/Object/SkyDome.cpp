#include "SkyDome.h"

//!初期化関数
void SkyDome::Init(std::string stage_str_)
{
	//!外部データ読み込み
	LoadSkyDomeExternalInfo(stage_str_);

	m_skydome_info.m_key = "skydome";  //!描画用キー

	m_skydome_info.m_pos   = m_skydome_externalinfo.m_pos;   //!座標
	m_skydome_info.m_scale = m_skydome_externalinfo.m_scale; //!描画サイズ
	m_skydome_info.m_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //!回転角度

	m_skydome_info.m_mat_world = Calculation::Matrix(m_skydome_info.m_pos, m_skydome_info.m_scale, m_skydome_info.m_angle);  //!ワールド座標
}

//!外部データ読み込み関数
void SkyDome::LoadSkyDomeExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "SkyDomeData.dat";

	//!ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		//!書き込む
		fread(&m_skydome_externalinfo, sizeof(SkyDomeExternalInfo), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!描画情報送信関数
void SkyDome::Draw()
{
	FbxController::Instance()->DrawFbx(m_skydome_info.m_key, m_skydome_info.m_mat_world);
}

//!FBXモデル解放関数
void SkyDome::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(m_skydome_info.m_key);
}
