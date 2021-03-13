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
void Score::Add(__int16 score_)
{
	//スコア加算
	m_score += score_;

	//スコアが最低値以下の場合
	if (m_score < ScoreMinValue)
	{
		//最低値に設定
		m_score = ScoreMinValue;
	}
}

//スコア初期化関数
void Score::Reset()
{
	m_score = ScoreMinValue;
}
