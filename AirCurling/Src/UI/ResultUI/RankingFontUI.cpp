#include "RankingFontUI.h"
#include "../../Score/GameScore.h"
#include <algorithm>

//初期化関数
void RankingFontUI::Init()
{
	//座標初期化
	m_ranking_info.m_firstui_pos = m_external_pos[(__int8)ResultRankingCategory::Number_One];
	m_ranking_info.m_secondui_pos = m_external_pos[(__int8)ResultRankingCategory::Number_Two];
	m_ranking_info.m_thirdui_pos = m_external_pos[(__int8)ResultRankingCategory::Number_Three];

	//外部データ取得
	m_ranking_info.score_table = *mp_ranking_data->Instance()->LoadFile("Res/RankingData.txt");

	char a[10];

	//ゲームスコア取得
	sprintf_s(a, "%d", Score::Instance()->GetScore());
	m_ranking_info.score_table.push_back(a);

	//整数型に変換
	std::vector<__int16> score_table;
	for (int i = 0; i < m_ranking_info.score_table.size(); i++)
	{
		score_table.push_back(std::stoi(m_ranking_info.score_table[i]));
	}

	//小さい順にソート
	std::sort(score_table.begin(), score_table.end());

	//外部データに出力
	mp_ranking_data->Instance()->WriteData("Res/RankingData.txt", score_table);

	//数字を文字に変換
	sprintf_s(m_ranking_info.first, "%d", score_table[0]);
	sprintf_s(m_ranking_info.second, "%d", score_table[1]);
	sprintf_s(m_ranking_info.third, "%d", score_table[2]);
}

//描画情報送信関数
void RankingFontUI::Draw()
{
	Graphics::Instance()->DrawFont(m_ranking_info.m_firstui_pos, m_ranking_info.first, Graphics::FontSize::Large, Graphics::FontColor::Red);   //!1位
	Graphics::Instance()->DrawFont(m_ranking_info.m_secondui_pos, m_ranking_info.second, Graphics::FontSize::Large, Graphics::FontColor::Red);  //!2位
	Graphics::Instance()->DrawFont(m_ranking_info.m_thirdui_pos, m_ranking_info.third, Graphics::FontSize::Large, Graphics::FontColor::Red);	  //!3位
}
