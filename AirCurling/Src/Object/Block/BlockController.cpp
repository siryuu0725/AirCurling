#include "BlockController.h"
#include "../../System/FBXController.h"
#include "../../Utility/Collision/ObjectCollision.h"

//デストラクタ
BlockController::~BlockController()
{
	//円形ブロック
	for (__int8 i = 0; i < m_circleblocks.size(); i++)
	{
		delete m_circleblocks[i];
		m_circleblocks[i] = nullptr;
	}
	
	//矩形ブロック
	for (__int8 i = 0; i < m_rectblocks.size(); i++)
	{
		delete m_rectblocks[i];
		m_rectblocks[i] = nullptr;
	}
}

//初期化関数
void BlockController::Init(std::string stage_str_)
{
	ObjectBase::ObjectInfo block_info;

	//外部データ読み込み
	LoadCircleBlockExternalInfo(stage_str_);
	LoadRectBlockExternalInfo(stage_str_);

	//円形ブロック
	for (__int8 i = 0; i < m_circleblock_num; i++)
	{
		//あたり判定用に追加
		m_circleblocks.push_back(new CircleBlock
		(m_circleblock_externalinfo[i].m_pos,
		 m_circleblock_externalinfo[i].m_scale,
		 m_circleblock_externalinfo[i].m_radius, "circleblock"));

		m_circleblocks[i]->GetCircleBlockInfo(block_info);


		//あたり判定用に追加
		m_circleshapes.push_back(new CircleShape(block_info.m_pos, block_info.m_radius));
	}

	//矩形ブロック
	for (__int8 i = 0; i < m_rectblock_num; i++)
	{
		//読み込んだ数分追加
		m_rectblocks.push_back(new RectBlock
		(m_rectblock_externalinfo[i].m_pos,
		 m_rectblock_externalinfo[i].m_scale,
		 m_rectblock_externalinfo[i].m_rote,
		 m_rectblock_externalinfo[i].m_width, m_rectblock_externalinfo[i].m_height ,"rectblock"));

		m_rectblocks[i]->GetRectBlockInfo(block_info);

		//あたり判定用に追加
		m_rect_shapes.push_back(new RectShape(block_info.m_pos, block_info.m_width, block_info.m_height, block_info.m_angle.y));
	}

	SetCollisionInfo();
}

//外部データ読み込み関数(矩形ブロック)
void BlockController::LoadRectBlockExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "RectBlockData.dat";

	//ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_rectblock_num, sizeof(m_rectblock_num), 1, fp);

		//書き込む
		fread(&m_rectblock_externalinfo, sizeof(RectBlockExternalInfo), m_rectblock_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//外部データ読み込み関数(円形ブロック)
void BlockController::LoadCircleBlockExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "CircleBlockData.dat";

	//ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		fread(&m_circleblock_num, sizeof(m_circleblock_num), 1, fp);

		//書き込む
		fread(&m_circleblock_externalinfo, sizeof(CircleBlockExternalInfo), m_circleblock_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//描画情報送信関数
void BlockController::Draw()
{
	//円形ブロック
	for (__int8 i = 0; i < m_circleblocks.size(); i++)
	{
		m_circleblocks[i]->Draw();
	}
	
	//矩形ブロック
	for (__int8 i = 0; i < m_rectblocks.size(); i++)
	{
		m_rectblocks[i]->Draw();
	}
}

//FBXモデル解放関数
void BlockController::ReleaseModel()
{
	//円形ブロック
	for (__int8 i = 0; i < m_circleblocks.size(); i++)
	{
		m_circleblocks[i]->ReleaseModel();
	}

	//矩形ブロック
	for (__int8 i = 0; i < m_rectblocks.size(); i++)
	{
		m_rectblocks[i]->ReleaseModel();
	}
}

void BlockController::SetCollisionInfo()
{
	//矩形ブロック
	for (__int8 i = 0; i < m_rectblock_num; i++)
	{
		RectBlock::ObjectInfo rectblock_info;

		m_rectblocks[i]->GetRectBlockInfo(rectblock_info);

		ObjectCollision::Instance()->SetRectBlockInfo(rectblock_info);
	}

	//矩形ブロック
	for (__int8 i = 0; i < m_circleblock_num; i++)
	{
		CircleBlock::ObjectInfo circleblock_info;

		m_circleblocks[i]->GetCircleBlockInfo(circleblock_info);

		ObjectCollision::Instance()->SetCircleBlockInfo(circleblock_info);
	}
}

void BlockController::GetCircleBlockInfo(CircleBlock::ObjectInfo& copy_info_, __int8 id_)
{
	m_circleblocks[id_]->GetCircleBlockInfo(copy_info_);
}

void BlockController::GetRectBlockInfo(RectBlock::ObjectInfo& copy_info_, __int8 id_)
{
	m_rectblocks[id_]->GetRectBlockInfo(copy_info_);
}
