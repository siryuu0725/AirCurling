#include "GameScore.h"

Score* Score::mp_instance = nullptr;

//コンストラクタ
Score::Score() :
	m_score(0)
{
}

//インスタンス化関数
Score* Score::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new Score; }

	return mp_instance;
}

//スコア加算関数
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
