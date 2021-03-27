#include "ResultUI.h"
#include "../../Score/GameScore.h"
#include <algorithm>

//初期化関数
void ResultUI::Init()
{
	if (mp_bg == nullptr) { mp_bg = new RusultBG; }
	if (mp_ranking_font == nullptr) { mp_ranking_font = new RankingFontUI; }

	//外部データ読み込み
	LoadResultUIExternalInfo();

	//外部データセット
	SetUIPos();

	//各UIを配列でまとめる
	UIBase* ui[ResultUICategoryNum] =
	{ mp_bg ,mp_ranking_font };

	for (__int8 i = 0; i < ResultUICategoryNum; i++)
	{
		ui[i]->Init(); //初期化
	}
}

//外部データセット関数
void ResultUI::SetUIPos()
{
	mp_bg->SetUIPos(m_resultui_externalinfo[(__int8)ResultUICategory::BG].m_pos);

	mp_ranking_font->SetUIPos(m_resultui_externalinfo[(__int8)ResultUICategory::Number_One].m_pos,
		m_resultui_externalinfo[(__int8)ResultUICategory::Number_Two].m_pos,
		m_resultui_externalinfo[(__int8)ResultUICategory::Number_Three].m_pos);
}

//外部データ読み込み関数
void ResultUI::LoadResultUIExternalInfo()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "Res/UIData/ResultUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//書き込む
		fread(&m_resultui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//描画情報送信関数
void ResultUI::Draw()
{
	//各UIを配列でまとめる
	UIBase* ui[ResultUICategoryNum] =
	{ mp_bg ,mp_ranking_font };

	for (__int8 i = 0; i < ResultUICategoryNum; i++)
	{
		ui[i]->Draw();
	}
}

//テクスチャ解放関数
void ResultUI::ReleaseTex()
{
	mp_bg->ReleaseTex();
}
