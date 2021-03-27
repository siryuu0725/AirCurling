#include "GameScoreUI.h"
#include "../../Score/GameScore.h"
#include "TurnUI.h"

//初期化関数
void GameScoreUI::Init()
{
	//座標初期化
	for (__int8 i = __int8(GameScoreTexCategory::One_Score); i <= __int8(GameScoreTexCategory::Ten_Score); i++)
	{
		m_gamescoer_info.m_ui_pos[i] = m_external_pos[i];
	}

	//Texture読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Score.png", &m_gamescoer_info.m_ui_tex[(__int8)GameScoreTexCategory::One_Score]);
	Graphics::Instance()->LoadTexture("Res/Tex/Score.png", &m_gamescoer_info.m_ui_tex[(__int8)GameScoreTexCategory::Ten_Score]);

	m_gamescoer_info.m_ui_tu[(int)GameScoreTexCategory::One_Score] = 0.0f; //スコア数1の位のtu値
	m_gamescoer_info.m_ui_tv[(int)GameScoreTexCategory::One_Score] = 1.0f; //スコア数1の位のtv値

	m_gamescoer_info.m_ui_tu[(int)GameScoreTexCategory::Ten_Score] = 0.0f; //スコア数10の位のtu値
	m_gamescoer_info.m_ui_tv[(int)GameScoreTexCategory::Ten_Score] = 1.0f; //スコア数10の位のtv値

	m_gamescoer_info.m_now_score = 0; //総合スコア 
	m_gamescoer_info.m_one_score = 0; //スコア1の位保存用
	m_gamescoer_info.m_ten_score = 0; //スコア10の位保存用
}

//更新関数
void GameScoreUI::AddScore(bool is_turnend_)
{
	//1ターン終了時(プレイヤーが移動し終わった時)
	if (is_turnend_ == true)
	{
		//スコアの1の位を算出
		m_gamescoer_info.m_one_score = Score::Instance()->GetScore() % 10;
		//スコアの10の位を算出
		m_gamescoer_info.m_ten_score = Score::Instance()->GetScore() / 10;

		//スコア数分テクスチャのTU値設定
		m_gamescoer_info.m_ui_tu[(int)GameScoreTexCategory::One_Score] = TrunTexUVAddValue * m_gamescoer_info.m_one_score;
		m_gamescoer_info.m_ui_tu[(int)GameScoreTexCategory::Ten_Score] = TrunTexUVAddValue * m_gamescoer_info.m_ten_score;

		//現在のスコアに加算
		m_gamescoer_info.m_now_score += Score::Instance()->GetScore();

		//文字列にスコアをコピー
		sprintf_s(m_gamescoer_info.m_score, "%d", m_gamescoer_info.m_now_score);
	}
}

//描画情報送信関数
void GameScoreUI::Draw()
{
	//スコア1の位
	Graphics::Instance()->DrawUVTexture(&m_gamescoer_info.m_ui_tex[(int)GameScoreTexCategory::One_Score], m_gamescoer_info.m_ui_pos[(int)GameScoreTexCategory::One_Score], 64.0f, 64.0f,
		m_gamescoer_info.m_ui_tu[(int)GameScoreTexCategory::One_Score], m_gamescoer_info.m_ui_tv[(int)GameScoreTexCategory::One_Score]);
	//スコア10の位
	Graphics::Instance()->DrawUVTexture(&m_gamescoer_info.m_ui_tex[(int)GameScoreTexCategory::Ten_Score], m_gamescoer_info.m_ui_pos[(int)GameScoreTexCategory::Ten_Score], 64.0f, 64.0f,
		m_gamescoer_info.m_ui_tu[(int)GameScoreTexCategory::Ten_Score], m_gamescoer_info.m_ui_tv[(int)GameScoreTexCategory::Ten_Score]);
}

//テクスチャ解放関数
void GameScoreUI::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)GameScoreTexCategory::CategoryMax; i++)
	{
		if (&m_gamescoer_info.m_ui_tex[i] != nullptr)
		{
			m_gamescoer_info.m_ui_tex[i].Texture->Release();
			m_gamescoer_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
