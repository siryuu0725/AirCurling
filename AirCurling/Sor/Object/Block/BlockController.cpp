#include "BlockController.h"
#include "../../System/FBXController.h"

//!デストラクタ
BlockController::~BlockController()
{
	for (int i = 0; i < m_circle_block.size(); i++)
	{
		delete m_circle_block[i];
		m_circle_block[i] = nullptr;
	}

	for (int i = 0; i < m_rect_block.size(); i++)
	{
		delete m_rect_block[i];
		m_rect_block[i] = nullptr;
	}
}

//!初期化関数
void BlockController::Init(std::string stage_id_)
{
#pragma region 円形ブロック
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "CircleBlockData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_circleblock_num, sizeof(m_circleblock_num), 1, fp);

		//!書き込む
		fread(&m_circleblock_info_copy, sizeof(CircleBlockInfoCopy), m_circleblock_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	//!インスタンス化
	for (int i = 0; i < m_circleblock_num; i++)
	{
		//あたり判定用に追加
		m_circle_block.push_back(new CircleBlock(D3DXVECTOR3(m_circleblock_info_copy[i].pos_x, m_circleblock_info_copy[i].pos_y, m_circleblock_info_copy[i].pos_z),
			D3DXVECTOR3(m_circleblock_info_copy[i].scale_x, m_circleblock_info_copy[i].scale_y, m_circleblock_info_copy[i].scale_z),
			m_circleblock_info_copy[i].radius, "circleblock"));
	}

	for (int i = 0; i < m_circleblock_num; i++)
	{
		//あたり判定用に追加
		m_circleshape.push_back(new CircleShape(m_circle_block[i]->GetObjInfo()->m_pos, m_circle_block[i]->GetObjInfo()->m_radius));
	}
#pragma endregion

#pragma region 矩形型ブロック
	fp = NULL;

	stage_id = "Res/ObjectData/" + stage_id_ + "RectBlockData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_rectblock_num, sizeof(m_rectblock_num), 1, fp);

		//!書き込む
		fread(&m_rectblock_info_copy, sizeof(RectBlockInfoCopy), m_rectblock_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	//!インスタンス化
	for (int i = 0; i < m_rectblock_num; i++)
	{
		//読み込んだ数分追加
		m_rect_block.push_back(new RectBlock(D3DXVECTOR3(m_rectblock_info_copy[i].pos_x, m_rectblock_info_copy[i].pos_y, m_rectblock_info_copy[i].pos_z),
			D3DXVECTOR3(m_rectblock_info_copy[i].scale_x, m_rectblock_info_copy[i].scale_y, m_rectblock_info_copy[i].scale_z),
			D3DXVECTOR3(m_rectblock_info_copy[i].rote_x, m_rectblock_info_copy[i].rote_y, m_rectblock_info_copy[i].rote_z),
			m_rectblock_info_copy[i].width, m_rectblock_info_copy[i].height ,"rectblock"));
	}

	for (int i = 0; i < m_rectblock_num; i++)
	{
		//あたり判定用に追加
		m_rect_shape.push_back(new RectShape(m_rect_block[i]->GetObjInfo()->m_pos, m_rect_block[i]->GetObjInfo()->m_width, m_rect_block[i]->GetObjInfo()->m_height, m_rect_block[i]->GetObjInfo()->m_angle.y));
	}

#pragma endregion
}

//!描画情報送信関数
void BlockController::SetUpBuffer()
{
	for (int i = 0; i < m_circle_block.size(); i++)
	{
		m_circle_block[i]->SetUpDrawBuffer();
	}
	
	for (int i = 0; i < m_rect_block.size(); i++)
	{
		m_rect_block[i]->SetUpDrawBuffer();
	}
}
