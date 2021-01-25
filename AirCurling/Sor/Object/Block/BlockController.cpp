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
#pragma region 円型ブロック
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "CircleBlockData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_circleblock_num, sizeof(m_circleblock_num), 1, fp);

		//!書き込む
		fread(&circleblock_info_copy, sizeof(CircleBlockInfoCopy), m_circleblock_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	//!インスタンス化
	for (int i = 0; i < m_circleblock_num; i++)
	{
		//あたり判定用に追加
		m_circle_block.push_back(new CircleBlock(D3DXVECTOR3(circleblock_info_copy[i].pos_x, circleblock_info_copy[i].pos_y, circleblock_info_copy[i].pos_z),
			D3DXVECTOR3(circleblock_info_copy[i].scale_x, circleblock_info_copy[i].scale_y, circleblock_info_copy[i].scale_z),
			circleblock_info_copy[i].radius, "circleblock"));
	}

	for (int i = 0; i < m_circleblock_num; i++)
	{
		//あたり判定用に追加
		m_circleshape.push_back(new CircleShape(m_circle_block[i]->GetObjInfo()->pos, m_circle_block[i]->GetObjInfo()->radius));
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
		fread(&rectblock_info_copy, sizeof(RectBlockInfoCopy), m_rectblock_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	//!インスタンス化
	for (int i = 0; i < m_rectblock_num; i++)
	{
		//読み込んだ数分追加
		m_rect_block.push_back(new RectBlock(D3DXVECTOR3(rectblock_info_copy[i].pos_x, rectblock_info_copy[i].pos_y, rectblock_info_copy[i].pos_z),
			D3DXVECTOR3(rectblock_info_copy[i].scale_x, rectblock_info_copy[i].scale_y, rectblock_info_copy[i].scale_z),
			D3DXVECTOR3(rectblock_info_copy[i].rote_x, rectblock_info_copy[i].rote_y, rectblock_info_copy[i].rote_z),
			rectblock_info_copy[i].width, rectblock_info_copy[i].height ,"rectblock"));
	}

	for (int i = 0; i < m_rectblock_num; i++)
	{
		//あたり判定用に追加
		m_rect_shape.push_back(new RectShape(m_rect_block[i]->GetObjInfo()->pos, m_rect_block[i]->GetObjInfo()->width, m_rect_block[i]->GetObjInfo()->height, m_rect_block[i]->GetObjInfo()->angle.y));
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
