﻿#include "Floor.h"

//!初期化関数
void Floor::Init(std::string stage_id_)
{
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "FloorData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		//!書き込む
		fread(&floor_info_copy, sizeof(ObjectInfoCopy), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	m_floor_info.key = "stage"; //!描画用キー

	m_floor_info.pos = D3DXVECTOR3(floor_info_copy.pos_x, floor_info_copy.pos_y, floor_info_copy.pos_z);         //!座標
	m_floor_info.scale = D3DXVECTOR3(floor_info_copy.scale_x, floor_info_copy.scale_y, floor_info_copy.scale_z); //!描画サイズ
	m_floor_info.angle = D3DXVECTOR3(floor_info_copy.rote_x, floor_info_copy.rote_y, floor_info_copy.pos_z);     //!回転角度

	m_floor_info.mat_world = Calculation::Matrix(m_floor_info.pos, m_floor_info.scale, m_floor_info.angle);      //!ワールド座標

	m_floor_info.width = floor_info_copy.width;   //!横幅
	m_floor_info.height = floor_info_copy.height; //!縦幅
}

//!描画情報送信関数
void Floor::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(m_floor_info.key, m_floor_info.mat_world);

}
