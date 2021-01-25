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

	skydome_info.key = "skydome";  //!描画用キー

	skydome_info.pos = D3DXVECTOR3(skydome_info_copy.pos_x, skydome_info_copy.pos_y, skydome_info_copy.pos_z);   //!座標
	skydome_info.scale = D3DXVECTOR3(skydome_info_copy.scale_x, skydome_info_copy.scale_y, skydome_info_copy.scale_z);	//!描画サイズ
	skydome_info.angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//!回転角度

	skydome_info.mat_world = Calculation::Matrix(skydome_info.pos, skydome_info.scale, skydome_info.angle);  //!ワールド座標
}

//!描画情報送信関数
void SkyDome::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(skydome_info.key, skydome_info.mat_world);
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

	skyfloor_info.key = "skyfloor";//!描画用キー

	skyfloor_info.pos   = D3DXVECTOR3(skyfloor_info_copy.pos_x, skyfloor_info_copy.pos_y, skyfloor_info_copy.pos_z); //!座標
	skyfloor_info.scale = D3DXVECTOR3(skyfloor_info_copy.scale_x, skyfloor_info_copy.scale_y, skyfloor_info_copy.scale_z);   //!描画サイズ
	skyfloor_info.angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //!回転角度

	skyfloor_info.mat_world = Calculation::Matrix(skyfloor_info.pos, skyfloor_info.scale, skyfloor_info.angle);  //!ワールド座標
}

//!描画情報送信関数
void SkyFloor::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(skyfloor_info.key, skyfloor_info.mat_world);
}
