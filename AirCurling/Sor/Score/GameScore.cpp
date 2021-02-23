#include "GameScore.h"

Score* Score::p_instance = 0;

//!コンストラクタ
Score::Score() :
	m_score(0)
{
}

//!インスタンス化関数
Score* Score::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new Score;
	}

	return p_instance;
}

//!スコア加算関数
void Score::AddGameScore(__int16 score_)
{
	m_score += score_;

	if (m_score < 0)
	{
		m_score = 0;
	}
}

void Score::Reset()
{
	m_score = 0;
}
