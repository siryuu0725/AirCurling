#include "GameScore.h"

Score* Score::p_instance = nullptr;

//!コンストラクタ
Score::Score() :
	m_score(0)
{
}

//!インスタンス化関数
Score* Score::Instance()
{
	if (p_instance == nullptr)
	{
		p_instance = new Score;
	}

	return p_instance;
}

//!スコア加算関数
void Score::AddGameScore(__int16 score_)
{
	m_score += score_;

	if (m_score < ScoreMinValue)
	{
		m_score = ScoreMinValue;
	}
}

void Score::Reset()
{
	m_score = ScoreMinValue;
}
