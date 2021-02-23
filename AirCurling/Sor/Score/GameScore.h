#ifndef GAME_SCORE_H_
#define GAME_SCORE_H_

/**
*@clss   スコア管理クラス
*@brief  ゲーム内で計算されたスコアをリザルトに持っていくためなどに使用
*/

class Score
{
private:
	Score();
	~Score() {}

public:

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
	static Score* p_instance;

	__int16 m_score;  //!スコア保存用
};

#endif