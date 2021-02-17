﻿#include "GameUI.h"
#include "../Object/Player.h"
#include "../Score/GameScore.h"

//!初期化関数
void GameUI::Init()
{
	FILE* fp = NULL;

	fopen_s(&fp, "Res/UIData/GameUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//!書き込む
		fread(&m_gameui_info_copy, sizeof(UIExternalInfo), m_ui_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	for (int i = 0; i < m_ui_num; i++)
	{
		m_game_ui_info.m_ui_pos[i] = D3DXVECTOR2(m_gameui_info_copy[i].pos_x, m_gameui_info_copy[i].pos_y);  //!背景
	}

#pragma region テクスチャ座標初期化
	

	m_game_ui_info.m_ui_tu[(int)GameUICategory::TurnNumber] = 0.1f; //!ターン数のtu値
	m_game_ui_info.m_ui_tv[(int)GameUICategory::TurnNumber] = 1.0f;	//!ターン数のtv値

	m_game_ui_info.m_ui_tu[(int)GameUICategory::One_Score] = 0.0f; //!スコア数1の位のtu値
	m_game_ui_info.m_ui_tv[(int)GameUICategory::One_Score] = 1.0f; //!スコア数1の位のtv値

	m_game_ui_info.m_ui_tu[(int)GameUICategory::Ten_Score] = 0.0f; //!スコア数10の位のtu値
	m_game_ui_info.m_ui_tv[(int)GameUICategory::Ten_Score] = 1.0f; //!スコア数10の位のtv値

#pragma endregion

	m_update_step = UpdateStep::StartProduction;

	m_game_ui_info.m_gauge_speed = 7.0f; //!ゲージバーの動くスピード
	m_game_ui_info.m_gauge_pos = 0.0f;   //!ゲージバーの座標
	m_game_ui_info.m_gauge_stop = false; //!ゲージバー停止フラグ

	m_game_ui_info.m_add_speed = 0.0f;  //!プレイヤーの移動スピード

	m_game_ui_info.m_now_score = 0;   //!総合スコア 
	m_game_ui_info.m_one_score = 0; //!スコア1の位保存用
	m_game_ui_info.m_ten_score = 0; //!スコア10の位保存用

	m_game_ui_info.m_is_shotmode = false; //!shot(打つ)モード切り替えフラグ

	m_game_ui_info.m_stoptimer = 0; //!開始演出の文字が止まる演出時間

	m_game_ui_info.m_movespeed = 20.0f; //!開始演出の文字が動くスピード
	m_game_ui_info.m_movestop = false;  //!開始演出の文字が止まるフラグ
	m_game_ui_info.m_remove = false;    //!開始演出の文字が再び動くフラグ

	m_game_ui_info.m_end_game = false; //!ゲームUIの終了演出が終わったかどうか

	m_game_ui_info.t = 0.0f;
	m_game_ui_info.flame = 0.01666667f;

	//!テクスチャ読み込み
	LoadTex();

}

//!テクスチャ読み込み関数
void GameUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/shot2.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotGauge]);
	Graphics::Instance()->LoadTexture("Res/Tex/shot_frame.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotGaugeFlame]);
	Graphics::Instance()->LoadTexture("Res/Tex/ShotBar.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotBox]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_SHOT.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotMode]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_View.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::ViewMode]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_math.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::TurnNumber]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Turn.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::Turn]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Score.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::One_Score]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Score.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::Ten_Score]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Center_Start.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::Start]);
	Graphics::Instance()->LoadTexture("Res/Tex/カッコ.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::Kacco]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Center_Finish.png", &m_game_ui_info.m_ui_tex[(int)GameUICategory::Finish]);

}

//!描画情報送信関数
void GameUI::SetUpBuffer()
{
	//!開始演出時のみ
	if (m_update_step == UpdateStep::StartProduction)
	{
		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::Start], m_game_ui_info.m_ui_pos[(int)GameUICategory::Start]);
		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::Kacco], m_game_ui_info.m_ui_pos[(int)GameUICategory::Kacco]);
	}
	//!終了演出時のみ
	else if (m_update_step == UpdateStep::EndProduction)
	{
		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::Finish], m_game_ui_info.m_ui_pos[(int)GameUICategory::Finish]);
	}

	//!打つとき(shotモードの時)
	if (m_game_ui_info.m_is_shotmode == true)
	{
		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotGaugeFlame], m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotGaugeFlame]);
		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotGauge], m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotGauge]);
		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotBox], m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotBox]);

		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::ShotMode], m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotMode]);
	}
	//!見る時(viewモードの時)
	else
	{
		Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::ViewMode], m_game_ui_info.m_ui_pos[(int)GameUICategory::ViewMode]);
	}

	//!ターン数
	Graphics::Instance()->DrawUVTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::TurnNumber], m_game_ui_info.m_ui_pos[(int)GameUICategory::TurnNumber], 94.0f, 94.0f, m_game_ui_info.m_ui_tu[(int)GameUICategory::TurnNumber], m_game_ui_info.m_ui_tv[(int)GameUICategory::TurnNumber]);
	//!文字「ターン」
	Graphics::Instance()->DrawTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::Turn], m_game_ui_info.m_ui_pos[(int)GameUICategory::Turn]);

	//!スコア1の位
	Graphics::Instance()->DrawUVTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::One_Score], m_game_ui_info.m_ui_pos[(int)GameUICategory::One_Score], 64.0f, 64.0f, m_game_ui_info.m_ui_tu[(int)GameUICategory::One_Score], m_game_ui_info.m_ui_tv[(int)GameUICategory::One_Score]);
	//!スコア10の位
	Graphics::Instance()->DrawUVTexture(&m_game_ui_info.m_ui_tex[(int)GameUICategory::Ten_Score], m_game_ui_info.m_ui_pos[(int)GameUICategory::Ten_Score], 64.0f, 64.0f, m_game_ui_info.m_ui_tu[(int)GameUICategory::Ten_Score], m_game_ui_info.m_ui_tv[(int)GameUICategory::Ten_Score]);
	
}

//!更新関数
void GameUI::Update(Player* player_, Camera* camera_)
{
	switch (m_update_step)
	{
	case UpdateStep::StartProduction:  //!開始演出ステップ
		StartProduction(camera_);
		break;
	case UpdateStep::GameMain:
		ModeChange();  //!モード切り替え判定

		GaugeStop(player_);   //!スピードゲージ更新

		AddScore(player_);    //!スコア更新

		//!プレイヤーがゴールした場合
		if (player_->GetObjInfo()->m_goal == true)
		{
			m_update_step = UpdateStep::EndProduction;
			break;
		}

		UpdateTurn(player_);  //!ターン数更新
		break;
	case UpdateStep::EndProduction: //!終了演出ステップ
		EndProduction();
	default:
		break;
	}
}

//!スピードゲージ停止関数
void GameUI::GaugeStop(Player* player_)
{
	//!バーを止めるキーが押されていない間
	if (m_game_ui_info.m_gauge_stop == false)
	{
		//!バーを動かす
		m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotBox].y -= m_game_ui_info.m_gauge_speed;
		
		m_game_ui_info.m_gauge_pos += m_game_ui_info.m_gauge_speed;
	}

	//!スペースキーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::SPACE_KEY) && m_game_ui_info.m_gauge_stop == false
		&& m_game_ui_info.m_is_shotmode == true)
	{
		m_game_ui_info.m_gauge_speed = 0.0f; //!バーの移動スピードを0に
		m_game_ui_info.m_add_speed = ADD_SPEED_POWER * m_game_ui_info.m_gauge_pos; //!プレイヤーの移動速度を設定
		m_game_ui_info.m_gauge_stop = true;  //!ゲージバー移動
		//!移動スピードをUIのバーが止まったとこらから加算
		player_->SetAddSpeed(m_game_ui_info.m_add_speed);
		player_->SetPlayerMove(true);
		//!サウンド再生
		SoundManager::Instance()->SoundShotSE();
	}

	//!バーがゲージの最大値or最小値に達した時
	if (m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotBox].y > 860.0f || m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotBox].y < 200.0f)
	{
		m_game_ui_info.m_gauge_speed = -m_game_ui_info.m_gauge_speed;
	}
}

//!ターン終了時初期化関数
void GameUI::UpdateTurn(Player* player_)
{
	//!1ターン終了時(プレイヤーが移動し終わった時)
	if (player_->GetObjInfo()->m_is_turnend == true)
	{
		//!ターン数加算
		m_game_ui_info.m_ui_tu[(int)GameUICategory::TurnNumber] += 0.1f;

		
		if (m_game_ui_info.m_ui_tu[(int)GameUICategory::TurnNumber] > 1.0f)
		{
			m_game_ui_info.m_ui_tu[(int)GameUICategory::TurnNumber] = 0.1f;
		}

		//!バー移動フラグ切り替え
		m_game_ui_info.m_gauge_stop = false;
		//!バーの位置を初期位置に
		m_game_ui_info.m_ui_pos[(int)GameUICategory::ShotBox].y = 860.0f;
		m_game_ui_info.m_gauge_pos = 0.0f;

		m_game_ui_info.m_gauge_speed = 7.0f;

	}

}

//!スコア加算関数
void GameUI::AddScore(Player* player_)
{
	//!1ターン終了時(プレイヤーが移動し終わった時)
	if (player_->GetObjInfo()->m_is_turnend == true)
	{
		//!スコアの1の位を算出
		m_game_ui_info.m_one_score = Score::Instance()->GetNowScore() % 10;
		//!スコアの10の位を算出
		m_game_ui_info.m_ten_score = Score::Instance()->GetNowScore() / 10;

		//!スコア数分テクスチャのTU値設定
		m_game_ui_info.m_ui_tu[(int)GameUICategory::One_Score] = 0.1f * m_game_ui_info.m_one_score;
		m_game_ui_info.m_ui_tu[(int)GameUICategory::Ten_Score] = 0.1f * m_game_ui_info.m_ten_score;

		//!現在のスコアに加算
		m_game_ui_info.m_now_score += Score::Instance()->GetNowScore();
	}

	//!文字列にスコアをコピー
	sprintf_s(m_game_ui_info.m_score, "%d", m_game_ui_info.m_now_score);
}

//!モード切替判定関数
void GameUI::ModeChange()
{
	//!モード切替キーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::F_KEY))
	{
		if (m_game_ui_info.m_is_shotmode == false)
		{
			m_game_ui_info.m_is_shotmode = true;
		}
		else
		{
			m_game_ui_info.m_is_shotmode = false;
		}
	}
}

//!開始演出関数
void GameUI::StartProduction(Camera* camera_)
{
	//!画面両サイドから流れてくるようにする
	m_game_ui_info.m_ui_pos[(int)GameUICategory::Start].x -= m_game_ui_info.m_movespeed;
	m_game_ui_info.m_ui_pos[(int)GameUICategory::Kacco].x += m_game_ui_info.m_movespeed;

	//!左右から流れてきたテクスチャの座標が重なり合う位置に来たら
	if (m_game_ui_info.m_ui_pos[(int)GameUICategory::Kacco].x >= m_game_ui_info.m_ui_pos[(int)GameUICategory::Start].x && m_game_ui_info.m_movestop == false)
	{
		m_game_ui_info.m_movespeed = 0.0f;
		m_game_ui_info.m_movestop = true;  //!一度テクスチャの移動を止める
	}
	//!再び動かせるようになった時
	else if (m_game_ui_info.m_remove == true)
	{
		m_game_ui_info.m_movespeed = 20.0f;
	}

	//!一度テクスチャがとまった時
	if (m_game_ui_info.m_movestop == true)
	{
		//!1秒程止める
		if (m_game_ui_info.m_stoptimer <= 60)
		{
			m_game_ui_info.m_stoptimer++;
		}
		else
		{
			//!再び動かす
			m_game_ui_info.m_remove = true;
		}
	}
	
	//!再移動後、画面外にテクスチャが出た時
	if (m_game_ui_info.m_remove == true && m_game_ui_info.m_ui_pos[(int)GameUICategory::Kacco].x >= 1900.0f)
	{
		m_update_step = UpdateStep::GameMain; //!更新ステップをゲーム本編へ
		camera_->SetCameraOperation(true);

	}
}

//!終了演出関数
void GameUI::EndProduction()
{
	//!テクスチャが画面内にある時
	if (m_game_ui_info.m_ui_pos[(int)GameUICategory::Finish].y >= -500.0f)
	{
		m_game_ui_info.m_ui_pos[(int)GameUICategory::Finish].y += 8.0f * m_game_ui_info.t + ((-9.8f) * (m_game_ui_info.t * m_game_ui_info.t)) / 2.0f;

		m_game_ui_info.t += m_game_ui_info.flame;
	}
	else
	{
		m_game_ui_info.m_end_game = true;
	}
}

//!テクスチャ解放関数
void GameUI::ReleaseTex()
{
	for (int i = 0; i < (int)GameUICategory::CategoryMax; i++)
	{
		if (&m_game_ui_info.m_ui_tex[i] != nullptr)
		{
			m_game_ui_info.m_ui_tex[i].Texture->Release();
			m_game_ui_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
