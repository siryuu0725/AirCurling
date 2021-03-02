/**
 * @file GameScore.h
 * @brief ゲーム内で計算されたスコアを管理する
 * @details 中身：スコアクラス
**/
#ifndef GAME_SCORE_H_
#define GAME_SCORE_H_

constexpr unsigned __int8 ScoreMinValue = 0;   //!スコアの最小値

/**
* スコア管理クラス
*/
class Score
{
public:
	Score();
	~Score() {}

	/**
　　* @brief  インスタンス化関数
　　* @detail 初回のみインスタンス化し、それ以外は実態を呼ぶ
　　*/
	static Score* Instance();

	/**
　　* @brief  スコア加算関数
　　* @detail 初回のみインスタンス化し、それ以外は実態を呼ぶ
　　*/
	void AddGameScore(__int16 score_);

	/**
　　* @brief  スコア初期化関数
　　* @detail ResultScene終了時にスコアが残らないようにするため
　　*/
	void Reset();

	/**
　　* @brief  スコアGetter関数
　　*/
	const __int16 GetNowScore()const { return m_score; }

private:
	static Score* mp_instance;

	__int16 m_score;  //!スコア保存用
};

#endif