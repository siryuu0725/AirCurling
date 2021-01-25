#include "GameUI.h"
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
		fread(&gameui_info_copy, sizeof(UIInfoCopy), m_ui_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	for (int i = 0; i < m_ui_num; i++)
	{
		game_ui_info.ui_pos[i] = D3DXVECTOR2(gameui_info_copy[i].pos_x, gameui_info_copy[i].pos_y);  //!背景
	}

#pragma region テクスチャ座標初期化
	

	game_ui_info.ui_tu[(int)GameUICategory::TurnNumber] = 0.1f; //!ターン数のtu値
	game_ui_info.ui_tv[(int)GameUICategory::TurnNumber] = 1.0f;	//!ターン数のtv値

	game_ui_info.ui_tu[(int)GameUICategory::One_Score] = 0.0f; //!スコア数1の位のtu値
	game_ui_info.ui_tv[(int)GameUICategory::One_Score] = 1.0f; //!スコア数1の位のtv値

	game_ui_info.ui_tu[(int)GameUICategory::Ten_Score] = 0.0f; //!スコア数10の位のtu値
	game_ui_info.ui_tv[(int)GameUICategory::Ten_Score] = 1.0f; //!スコア数10の位のtv値

#pragma endregion

	m_update_step = UpdateStep::StartProduction;

	game_ui_info.gauge_speed = 7.0f; //!ゲージバーの動くスピード
	game_ui_info.gauge_pos = 0.0f;   //!ゲージバーの座標
	game_ui_info.gauge_stop = false; //!ゲージバー停止フラグ

	game_ui_info.add_speed = 0.0f;  //!プレイヤーの移動スピード

	game_ui_info.now_score = 0;   //!総合スコア 
	game_ui_info.m_one_score = 0; //!スコア1の位保存用
	game_ui_info.m_ten_score = 0; //!スコア10の位保存用

	game_ui_info.shotmode = false; //!shot(打つ)モード切り替えフラグ

	game_ui_info.stoptimer = 0; //!開始演出の文字が止まる演出時間

	game_ui_info.movespeed = 20.0f; //!開始演出の文字が動くスピード
	game_ui_info.movestop = false;  //!開始演出の文字が止まるフラグ
	game_ui_info.remove = false;    //!開始演出の文字が再び動くフラグ

	game_ui_info.m_end_game = false;

	game_ui_info.t = 0.0f;
	game_ui_info.flame = 0.01666667f;

	//!テクスチャ読み込み
	LoadTex();

}

//!テクスチャ読み込み関数
void GameUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/shot2.png", &game_ui_info.ui_tex[(int)GameUICategory::ShotGauge]);
	Graphics::Instance()->LoadTexture("Res/Tex/shot_frame.png", &game_ui_info.ui_tex[(int)GameUICategory::ShotGaugeFlame]);
	Graphics::Instance()->LoadTexture("Res/Tex/ShotBar.png", &game_ui_info.ui_tex[(int)GameUICategory::ShotBox]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_SHOT.png", &game_ui_info.ui_tex[(int)GameUICategory::ShotMode]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_View.png", &game_ui_info.ui_tex[(int)GameUICategory::ViewMode]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_math.png", &game_ui_info.ui_tex[(int)GameUICategory::TurnNumber]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Turn.png", &game_ui_info.ui_tex[(int)GameUICategory::Turn]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Score.png", &game_ui_info.ui_tex[(int)GameUICategory::One_Score]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Score.png", &game_ui_info.ui_tex[(int)GameUICategory::Ten_Score]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Center_Start.png", &game_ui_info.ui_tex[(int)GameUICategory::Start]);
	Graphics::Instance()->LoadTexture("Res/Tex/カッコ.png", &game_ui_info.ui_tex[(int)GameUICategory::Kacco]);
	Graphics::Instance()->LoadTexture("Res/Tex/UI_Center_Finish.png", &game_ui_info.ui_tex[(int)GameUICategory::Finish]);

}

//!描画情報送信関数
void GameUI::SetUpBuffer()
{
	//!開始演出時のみ
	if (m_update_step == UpdateStep::StartProduction)
	{
		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::Start], game_ui_info.ui_pos[(int)GameUICategory::Start]);
		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::Kacco], game_ui_info.ui_pos[(int)GameUICategory::Kacco]);
	}
	//!終了演出時のみ
	else if (m_update_step == UpdateStep::EndProduction)
	{
		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::Finish], game_ui_info.ui_pos[(int)GameUICategory::Finish]);
	}

	//!打つとき(shotモードの時)
	if (game_ui_info.shotmode == true)
	{
		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::ShotGaugeFlame], game_ui_info.ui_pos[(int)GameUICategory::ShotGaugeFlame]);
		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::ShotGauge], game_ui_info.ui_pos[(int)GameUICategory::ShotGauge]);
		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::ShotBox], game_ui_info.ui_pos[(int)GameUICategory::ShotBox]);

		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::ShotMode], game_ui_info.ui_pos[(int)GameUICategory::ShotMode]);
	}
	//!見る時(viewモードの時)
	else
	{
		Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::ViewMode], game_ui_info.ui_pos[(int)GameUICategory::ViewMode]);
	}

	//!ターン数
	Graphics::Instance()->DrawUVTexture(&game_ui_info.ui_tex[(int)GameUICategory::TurnNumber], game_ui_info.ui_pos[(int)GameUICategory::TurnNumber], 94.0f, 94.0f, game_ui_info.ui_tu[(int)GameUICategory::TurnNumber], game_ui_info.ui_tv[(int)GameUICategory::TurnNumber]);
	//!文字「ターン」
	Graphics::Instance()->DrawTexture(&game_ui_info.ui_tex[(int)GameUICategory::Turn], game_ui_info.ui_pos[(int)GameUICategory::Turn]);

	//!スコア1の位
	Graphics::Instance()->DrawUVTexture(&game_ui_info.ui_tex[(int)GameUICategory::One_Score], game_ui_info.ui_pos[(int)GameUICategory::One_Score], 64.0f, 64.0f, game_ui_info.ui_tu[(int)GameUICategory::One_Score], game_ui_info.ui_tv[(int)GameUICategory::One_Score]);
	//!スコア10の位
	Graphics::Instance()->DrawUVTexture(&game_ui_info.ui_tex[(int)GameUICategory::Ten_Score], game_ui_info.ui_pos[(int)GameUICategory::Ten_Score], 64.0f, 64.0f, game_ui_info.ui_tu[(int)GameUICategory::Ten_Score], game_ui_info.ui_tv[(int)GameUICategory::Ten_Score]);
	
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

		Rset();

		//!プレイヤーがゴールした場合
		if (player_->GetObjInfo()->goal == true)
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
	if (game_ui_info.gauge_stop == false)
	{
		//!バーを動かす
		game_ui_info.ui_pos[(int)GameUICategory::ShotBox].y -= game_ui_info.gauge_speed;
		
		game_ui_info.gauge_pos += game_ui_info.gauge_speed;
	}

	//!スペースキーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::SPACE_KEY) && game_ui_info.gauge_stop == false)
	{
		game_ui_info.gauge_speed = 0.0f; //!バーの移動スピードを0に
		game_ui_info.add_speed = 0.001f * game_ui_info.gauge_pos; //!プレイヤーの移動速度を設定
		game_ui_info.gauge_stop = true;  //!ゲージバー移動
		//!移動スピードをUIのバーが止まったとこらから加算
		player_->SetAddSpeed(game_ui_info.add_speed);
		player_->SetPlayerMove(true);
		//!サウンド再生
		SoundManager::Instance()->SoundShotSE();
	}

	//!バーがゲージの最大値or最小値に達した時
	if (game_ui_info.ui_pos[(int)GameUICategory::ShotBox].y > 860.0f || game_ui_info.ui_pos[(int)GameUICategory::ShotBox].y < 200.0f)
	{
		game_ui_info.gauge_speed *= -1.0f;
	}
}

//!ターン終了時初期化関数
void GameUI::UpdateTurn(Player* player_)
{
	//!1ターン終了時(プレイヤーが移動し終わった時)
	if (player_->GetObjInfo()->turnend == true)
	{
		//!ターン数加算
		game_ui_info.ui_tu[(int)GameUICategory::TurnNumber] += 0.1f;

		
		if (game_ui_info.ui_tu[(int)GameUICategory::TurnNumber] > 1.0f)
		{
			game_ui_info.ui_tu[(int)GameUICategory::TurnNumber] = 0.1f;
		}

		//!バー移動フラグ切り替え
		game_ui_info.gauge_stop = false;
		//!バーの位置を初期位置に
		game_ui_info.ui_pos[(int)GameUICategory::ShotBox].y = 860.0f;
		game_ui_info.gauge_pos = 0.0f;

		game_ui_info.gauge_speed = 7.0f;

	}

}

//!スコア加算関数
void GameUI::AddScore(Player* player_)
{
	//!1ターン終了時(プレイヤーが移動し終わった時)
	if (player_->GetObjInfo()->turnend == true)
	{
		//!スコアの1の位を算出
		game_ui_info.m_one_score = Score::Instance()->GetNowScore() % 10;
		//!スコアの10の位を算出
		game_ui_info.m_ten_score = Score::Instance()->GetNowScore() / 10;

		//!スコア数分テクスチャのTU値設定
		game_ui_info.ui_tu[(int)GameUICategory::One_Score] = 0.1f * game_ui_info.m_one_score;
		game_ui_info.ui_tu[(int)GameUICategory::Ten_Score] = 0.1f * game_ui_info.m_ten_score;

		//!現在のスコアに加算
		game_ui_info.now_score += Score::Instance()->GetNowScore();
	}

	//!文字列にスコアをコピー
	sprintf_s(game_ui_info.score, "%d", game_ui_info.now_score);
}

void GameUI::Rset()
{
	if (Inputter::Instance()->GetKeyDown(Inputter::A_KEY))
	{
		game_ui_info.gauge_speed = 7.0f;
		game_ui_info.gauge_stop = false;

		game_ui_info.add_speed = 0.0f;
	}

}

//!モード切替判定関数
void GameUI::ModeChange()
{
	//!モード切替キーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::F_KEY))
	{
		if (game_ui_info.shotmode == false)
		{
			game_ui_info.shotmode = true;
		}
		else
		{
			game_ui_info.shotmode = false;
		}
	}
}

//!開始演出関数
void GameUI::StartProduction(Camera* camera_)
{
	//!画面両サイドから流れてくるようにする
	game_ui_info.ui_pos[(int)GameUICategory::Start].x -= game_ui_info.movespeed;
	game_ui_info.ui_pos[(int)GameUICategory::Kacco].x += game_ui_info.movespeed;

	//!左右から流れてきたテクスチャの座標が重なり合う位置に来たら
	if (game_ui_info.ui_pos[(int)GameUICategory::Kacco].x >= game_ui_info.ui_pos[(int)GameUICategory::Start].x && game_ui_info.movestop == false)
	{
		game_ui_info.movespeed = 0.0f;
		game_ui_info.movestop = true;  //!一度テクスチャの移動を止める
	}
	//!再び動かせるようになった時
	else if (game_ui_info.remove == true)
	{
		game_ui_info.movespeed = 20.0f;
	}

	//!一度テクスチャがとまった時
	if (game_ui_info.movestop == true)
	{
		//!1秒程止める
		if (game_ui_info.stoptimer <= 60)
		{
			game_ui_info.stoptimer++;
		}
		else
		{
			//!再び動かす
			game_ui_info.remove = true;
		}
	}
	
	//!再移動後、画面外にテクスチャが出た時
	if (game_ui_info.remove == true && game_ui_info.ui_pos[(int)GameUICategory::Kacco].x >= 1900.0f)
	{
		m_update_step = UpdateStep::GameMain; //!更新ステップをゲーム本編へ
		camera_->SetCameraOperation(true);

	}
}

//!終了演出関数
void GameUI::EndProduction()
{
	//!テクスチャが画面内にある時
	if (game_ui_info.ui_pos[(int)GameUICategory::Finish].y >= -500.0f)
	{
		game_ui_info.ui_pos[(int)GameUICategory::Finish].y += 8.0f * game_ui_info.t + ((-9.8f) * (game_ui_info.t * game_ui_info.t)) / 2.0f;

		game_ui_info.t += game_ui_info.flame;
	}
	else
	{
		game_ui_info.m_end_game = true;
	}
}

//!テクスチャ解放関数
void GameUI::ReleaseTex()
{
	for (int i = 0; i < (int)GameUICategory::CategoryMax; i++)
	{
		if (&game_ui_info.ui_tex[i] != nullptr)
		{
			game_ui_info.ui_tex[i].Texture->Release();
			game_ui_info.ui_tex[i].Texture = nullptr;
		}
	}
}
