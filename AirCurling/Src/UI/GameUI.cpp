#include "GameUI.h"
#include "../Object/Player.h"
#include "../Score/GameScore.h"

//!初期化関数
void GameUI::Init()
{
	//!外部データ読み込み
	LoadGameUIExternalInfo();

	for (int i = 0; i < m_ui_num; i++)
	{
		m_gameui_info.m_ui_pos[i] = D3DXVECTOR2(m_gameui_externalinfo[i].m_pos.x, m_gameui_externalinfo[i].m_pos.y);  //!背景
	}

#pragma region テクスチャUV値初期化
	m_gameui_info.m_ui_tu[(int)GameUICategory::TurnNumber] = 0.1f; //!ターン数のtu値
	m_gameui_info.m_ui_tv[(int)GameUICategory::TurnNumber] = 1.0f;	//!ターン数のtv値

	m_gameui_info.m_ui_tu[(int)GameUICategory::One_Score] = 0.0f; //!スコア数1の位のtu値
	m_gameui_info.m_ui_tv[(int)GameUICategory::One_Score] = 1.0f; //!スコア数1の位のtv値

	m_gameui_info.m_ui_tu[(int)GameUICategory::Ten_Score] = 0.0f; //!スコア数10の位のtu値
	m_gameui_info.m_ui_tv[(int)GameUICategory::Ten_Score] = 1.0f; //!スコア数10の位のtv値
#pragma endregion

	m_update_step = UpdateStep::StartProduction;

	m_gameui_info.m_gauge_speed = 7.0f; //!ゲージバーの動くスピード
	m_gameui_info.m_gauge_pos = 0.0f;   //!ゲージバーの座標
	m_gameui_info.m_gauge_stop = false; //!ゲージバー停止フラグ

	m_gameui_info.m_add_speed = 0.0f;  //!プレイヤーの移動スピード

	m_gameui_info.m_now_score = 0;   //!総合スコア 
	m_gameui_info.m_one_score = 0; //!スコア1の位保存用
	m_gameui_info.m_ten_score = 0; //!スコア10の位保存用

	m_gameui_info.m_is_shotmode = false; //!shot(打つ)モード切り替えフラグ

	m_gameui_info.m_stoptimer = 0; //!開始演出の文字が止まる演出時間

	m_gameui_info.m_movespeed = 20.0f; //!開始演出の文字が動くスピード
	m_gameui_info.m_movestop = false;  //!開始演出の文字が止まるフラグ
	m_gameui_info.m_remove = false;    //!開始演出の文字が再び動くフラグ

	m_gameui_info.m_end_game = false; //!ゲームUIの終了演出が終わったかどうか

	m_gameui_info.t = 0.0f;
	m_gameui_info.flame = 0.01666667f;

	//!テクスチャ読み込み
	LoadTex();

}

//!外部データ読み込み関数
void GameUI::LoadGameUIExternalInfo()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "Res/UIData/GameUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//!書き込む
		fread(&m_gameui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!テクスチャ読み込み関数
void GameUI::LoadTex()
{
	Graphics::Instance()->LoadTexture("Res/Tex/ShotGauge.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::ShotGauge]);
	Graphics::Instance()->LoadTexture("Res/Tex/ShotFrame.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::ShotGaugeFlame]);
	Graphics::Instance()->LoadTexture("Res/Tex/ShotBar.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::ShotBox]);
	Graphics::Instance()->LoadTexture("Res/Tex/ModeShot.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::ShotMode]);
	Graphics::Instance()->LoadTexture("Res/Tex/ModeView.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::ViewMode]);
	Graphics::Instance()->LoadTexture("Res/Tex/Math.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::TurnNumber]);
	Graphics::Instance()->LoadTexture("Res/Tex/Turn.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::Turn]);
	Graphics::Instance()->LoadTexture("Res/Tex/Score.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::One_Score]);
	Graphics::Instance()->LoadTexture("Res/Tex/Score.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::Ten_Score]);
	Graphics::Instance()->LoadTexture("Res/Tex/Start.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::Start]);
	Graphics::Instance()->LoadTexture("Res/Tex/StartFrame.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::Kacco]);
	Graphics::Instance()->LoadTexture("Res/Tex/Finish.png", &m_gameui_info.m_ui_tex[(int)GameUICategory::Finish]);

}

//!描画情報送信関数
void GameUI::Draw()
{
	//!開始演出時のみ
	if (m_update_step == UpdateStep::StartProduction)
	{
		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::Start], m_gameui_info.m_ui_pos[(int)GameUICategory::Start]);
		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::Kacco], m_gameui_info.m_ui_pos[(int)GameUICategory::Kacco]);
	}
	//!終了演出時のみ
	else if (m_update_step == UpdateStep::EndProduction)
	{
		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::Finish], m_gameui_info.m_ui_pos[(int)GameUICategory::Finish]);
	}

	//!打つとき(shotモードの時)
	if (m_gameui_info.m_is_shotmode == true)
	{
		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::ShotGaugeFlame], m_gameui_info.m_ui_pos[(int)GameUICategory::ShotGaugeFlame]);
		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::ShotGauge], m_gameui_info.m_ui_pos[(int)GameUICategory::ShotGauge]);
		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::ShotBox], m_gameui_info.m_ui_pos[(int)GameUICategory::ShotBox]);

		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::ShotMode], m_gameui_info.m_ui_pos[(int)GameUICategory::ShotMode]);
	}
	//!見る時(viewモードの時)
	else
	{
		Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::ViewMode], m_gameui_info.m_ui_pos[(int)GameUICategory::ViewMode]);
	}

	//!ターン数
	Graphics::Instance()->DrawUVTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::TurnNumber], m_gameui_info.m_ui_pos[(int)GameUICategory::TurnNumber], 94.0f, 94.0f, m_gameui_info.m_ui_tu[(int)GameUICategory::TurnNumber], m_gameui_info.m_ui_tv[(int)GameUICategory::TurnNumber]);
	//!文字「ターン」
	Graphics::Instance()->DrawTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::Turn], m_gameui_info.m_ui_pos[(int)GameUICategory::Turn]);

	//!スコア1の位
	Graphics::Instance()->DrawUVTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::One_Score], m_gameui_info.m_ui_pos[(int)GameUICategory::One_Score], 64.0f, 64.0f, m_gameui_info.m_ui_tu[(int)GameUICategory::One_Score], m_gameui_info.m_ui_tv[(int)GameUICategory::One_Score]);
	//!スコア10の位
	Graphics::Instance()->DrawUVTexture(&m_gameui_info.m_ui_tex[(int)GameUICategory::Ten_Score], m_gameui_info.m_ui_pos[(int)GameUICategory::Ten_Score], 64.0f, 64.0f, m_gameui_info.m_ui_tu[(int)GameUICategory::Ten_Score], m_gameui_info.m_ui_tv[(int)GameUICategory::Ten_Score]);
	
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
		if (player_->GetObjInfo()->m_is_goal == true)
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
	if (m_gameui_info.m_gauge_stop == false)
	{
		//!バーを動かす
		m_gameui_info.m_ui_pos[(int)GameUICategory::ShotBox].y -= m_gameui_info.m_gauge_speed;
		
		m_gameui_info.m_gauge_pos += m_gameui_info.m_gauge_speed;
	}

	//!スペースキーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::SPACE_KEY) && m_gameui_info.m_gauge_stop == false
		&& m_gameui_info.m_is_shotmode == true)
	{
		m_gameui_info.m_gauge_speed = 0.0f; //!バーの移動スピードを0に
		m_gameui_info.m_add_speed = ADD_SPEED_POWER * m_gameui_info.m_gauge_pos; //!プレイヤーの移動速度を設定
		m_gameui_info.m_gauge_stop = true;  //!ゲージバー移動
		//!移動スピードをUIのバーが止まったとこらから加算
		player_->SetAddSpeed(m_gameui_info.m_add_speed);
		player_->SetPlayerMove(true);
		//!サウンド再生
		SoundManager::Instance()->SoundShotSE();
	}

	//!バーがゲージの最大値or最小値に達した時
	if (m_gameui_info.m_ui_pos[(int)GameUICategory::ShotBox].y > 860.0f || m_gameui_info.m_ui_pos[(int)GameUICategory::ShotBox].y < 200.0f)
	{
		m_gameui_info.m_gauge_speed = -m_gameui_info.m_gauge_speed;
	}
}

//!ターン終了時初期化関数
void GameUI::UpdateTurn(Player* player_)
{
	//!1ターン終了時(プレイヤーが移動し終わった時)
	if (player_->GetObjInfo()->m_is_turnend == true)
	{
		//!ターン数加算
		m_gameui_info.m_ui_tu[(int)GameUICategory::TurnNumber] += TrunTexUVAddValue;

		
		if (m_gameui_info.m_ui_tu[(int)GameUICategory::TurnNumber] > 1.0f)
		{
			m_gameui_info.m_ui_tu[(int)GameUICategory::TurnNumber] = TrunTexUVAddValue;
		}

		//!バー移動フラグ切り替え
		m_gameui_info.m_gauge_stop = false;
		//!バーの位置を初期位置に
		m_gameui_info.m_ui_pos[(int)GameUICategory::ShotBox].y = 860.0f;
		m_gameui_info.m_gauge_pos = 0.0f;

		m_gameui_info.m_gauge_speed = 7.0f;

	}

}

//!スコア加算関数
void GameUI::AddScore(Player* player_)
{
	//!1ターン終了時(プレイヤーが移動し終わった時)
	if (player_->GetObjInfo()->m_is_turnend == true)
	{
		//!スコアの1の位を算出
		m_gameui_info.m_one_score = Score::Instance()->GetNowScore() % 10;
		//!スコアの10の位を算出
		m_gameui_info.m_ten_score = Score::Instance()->GetNowScore() / 10;

		//!スコア数分テクスチャのTU値設定
		m_gameui_info.m_ui_tu[(int)GameUICategory::One_Score] = TrunTexUVAddValue * m_gameui_info.m_one_score;
		m_gameui_info.m_ui_tu[(int)GameUICategory::Ten_Score] = TrunTexUVAddValue * m_gameui_info.m_ten_score;

		//!現在のスコアに加算
		m_gameui_info.m_now_score += Score::Instance()->GetNowScore();
	}

	//!文字列にスコアをコピー
	sprintf_s(m_gameui_info.m_score, "%d", m_gameui_info.m_now_score);
}

//!モード切替判定関数
void GameUI::ModeChange()
{
	//!モード切替キーが押された場合
	if (Inputter::Instance()->GetKeyDown(Inputter::F_KEY))
	{
		if (m_gameui_info.m_is_shotmode == false)
		{
			m_gameui_info.m_is_shotmode = true;
		}
		else
		{
			m_gameui_info.m_is_shotmode = false;
		}
	}
}

//!開始演出関数
void GameUI::StartProduction(Camera* camera_)
{
	//!画面両サイドから流れてくるようにする
	m_gameui_info.m_ui_pos[(int)GameUICategory::Start].x -= m_gameui_info.m_movespeed;
	m_gameui_info.m_ui_pos[(int)GameUICategory::Kacco].x += m_gameui_info.m_movespeed;

	//!左右から流れてきたテクスチャの座標が重なり合う位置に来たら
	if (m_gameui_info.m_ui_pos[(int)GameUICategory::Kacco].x >= m_gameui_info.m_ui_pos[(int)GameUICategory::Start].x && m_gameui_info.m_movestop == false)
	{
		m_gameui_info.m_movespeed = 0.0f;
		m_gameui_info.m_movestop = true;  //!一度テクスチャの移動を止める
	}
	//!再び動かせるようになった時
	else if (m_gameui_info.m_remove == true)
	{
		m_gameui_info.m_movespeed = 20.0f;
	}

	//!一度テクスチャがとまった時
	if (m_gameui_info.m_movestop == true)
	{
		//!1秒程止める
		if (m_gameui_info.m_stoptimer <= StartFontStopTime)
		{
			m_gameui_info.m_stoptimer++;
		}
		else
		{
			//!再び動かす
			m_gameui_info.m_remove = true;
		}
	}
	
	//!再移動後、画面外にテクスチャが出た時
	if (m_gameui_info.m_remove == true && m_gameui_info.m_ui_pos[(int)GameUICategory::Kacco].x >= 1900.0f)
	{
		m_update_step = UpdateStep::GameMain; //!更新ステップをゲーム本編へ
		camera_->SetCameraOperation(true);

	}
}

//!終了演出関数
void GameUI::EndProduction()
{
	//!テクスチャが画面内にある時
	if (m_gameui_info.m_ui_pos[(int)GameUICategory::Finish].y >= -500.0f)
	{
		m_gameui_info.m_ui_pos[(int)GameUICategory::Finish].y += 8.0f * m_gameui_info.t + ((-9.8f) * (m_gameui_info.t * m_gameui_info.t)) / 2.0f;

		m_gameui_info.t += m_gameui_info.flame;
	}
	else
	{
		m_gameui_info.m_end_game = true;
	}
}

//!テクスチャ解放関数
void GameUI::ReleaseTex()
{
	for (int i = 0; i < (int)GameUICategory::CategoryMax; i++)
	{
		if (&m_gameui_info.m_ui_tex[i] != nullptr)
		{
			m_gameui_info.m_ui_tex[i].Texture->Release();
			m_gameui_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}
