#include "ResultUI.h"
#include "../Score/GameScore.h"
#include <algorithm>

//!初期化関数
void ResultUI::Init()
{
	m_resultui_info.m_ui_pos[(int)ResultUICategory::BG] = D3DXVECTOR2(0.0f, 0.0f);  //!背景
	m_resultui_info.m_firstui_pos = D3DXVECTOR2(750.0f, 370.0f);
	m_resultui_info.m_secondui_pos = D3DXVECTOR2(750.0f, 540.0f);
	m_resultui_info.m_thirdui_pos = D3DXVECTOR2(750.0f, 710.0f);


	//!外部データ取得
	m_ranking.score_table = *csv->Instance()->LoadFile("Res/RankingData.txt");

	char a[10];

	//!ゲームスコア取得
	sprintf_s(a, "%d", Score::Instance()->GetNowScore());
	m_ranking.score_table.push_back(a);

	//!整数型に変換
	std::vector<__int16> score_table;
	for (int i = 0; i < m_ranking.score_table.size(); i++)
	{
		score_table.push_back(std::stoi(m_ranking.score_table[i]));
	}

	//!小さい順にソート
	std::sort(score_table.begin(), score_table.end());

	//!外部データに出力
	csv->Instance()->WriteData("Res/RankingData.txt", score_table);

	//!数字を文字に変換
	sprintf_s(m_ranking.first, "%d", score_table[0]);
	sprintf_s(m_ranking.second, "%d", score_table[1]);
	sprintf_s(m_ranking.third, "%d", score_table[2]);

	LoadTex();
}

//!テクスチャ読み込み関数
void ResultUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/ResultBg.png", &m_resultui_info.m_ui_tex[(int)ResultUICategory::BG]);

}

//!描画情報送信関数
void ResultUI::Draw()
{
	Graphics::Instance()->DrawTexture(&m_resultui_info.m_ui_tex[(int)ResultUICategory::BG], m_resultui_info.m_ui_pos[(int)ResultUICategory::BG]);
	Graphics::Instance()->DrawFont(m_resultui_info.m_firstui_pos, m_ranking.first, Graphics::FontSize::Large, Graphics::FontColor::Red);   //!1位
	Graphics::Instance()->DrawFont(m_resultui_info.m_secondui_pos, m_ranking.second, Graphics::FontSize::Large, Graphics::FontColor::Red);  //!2位
	Graphics::Instance()->DrawFont(m_resultui_info.m_thirdui_pos, m_ranking.third, Graphics::FontSize::Large, Graphics::FontColor::Red);	  //!3位
}

//!テクスチャ解放関数
void ResultUI::ReleaseTex()
{
	for (int i = 0; i < (int)ResultUICategory::CategoryMax; i++)
	{
		if (&m_resultui_info.m_ui_tex[i] != nullptr)
		{
			m_resultui_info.m_ui_tex[i].Texture->Release();
			m_resultui_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
