#include "GameUI.h"
#include "../../Object/Player.h"
#include "../../Score/GameScore.h"

//初期化関数
void GameUI::Init()
{
	if (mp_game_score == nullptr) { mp_game_score = new GameScoreUI; }
	if (mp_player_mode == nullptr) { mp_player_mode = new PlayerModeUI; }
	if (mp_production == nullptr) { mp_production = new ProductionUI; }
	if (mp_shot_gauge == nullptr) { mp_shot_gauge = new ShotGaugeUI(mp_player_mode); }
	if (mp_turn == nullptr) { mp_turn = new TurnUI; }

	//外部データ読み込み
	LoadGameUIExternalInfo();

	//外部データセット
	SetUIPos();

	//各UIを配列でまとめる
	UIBase* ui[GameUICategoryNum] =
	{ mp_game_score ,mp_player_mode,mp_production ,mp_shot_gauge ,mp_turn };

	for (int i = 0; i < GameUICategoryNum; i++)
	{
		ui[i]->Init(); //初期化
	}
}

//外部データセット関数
void GameUI::SetUIPos()
{
	mp_game_score->SetUIPos(m_gameui_externalinfo[(__int8)GameUICategory::One_Score].m_pos,
		m_gameui_externalinfo[(__int8)GameUICategory::Ten_Score].m_pos);

	mp_player_mode->SetUIPos(m_gameui_externalinfo[(__int8)GameUICategory::ViewMode].m_pos,
		m_gameui_externalinfo[(__int8)GameUICategory::ShotMode].m_pos);


	mp_production->SetUIPos(m_gameui_externalinfo[(__int8)GameUICategory::Start].m_pos,
		m_gameui_externalinfo[(__int8)GameUICategory::Kacco].m_pos,
		m_gameui_externalinfo[(__int8)GameUICategory::Finish].m_pos);

	mp_shot_gauge->SetUIPos(m_gameui_externalinfo[(__int8)GameUICategory::ShotGauge].m_pos,
		m_gameui_externalinfo[(__int8)GameUICategory::ShotGaugeFlame].m_pos,
		m_gameui_externalinfo[(__int8)GameUICategory::ShotBox].m_pos);

	mp_turn->SetUIPos(m_gameui_externalinfo[(__int8)GameUICategory::Turn].m_pos,
		m_gameui_externalinfo[(__int8)GameUICategory::TurnNumber].m_pos);
}

//外部データ読み込み関数
void GameUI::LoadGameUIExternalInfo()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "Res/UIData/GameUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//書き込む
		fread(&m_gameui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//描画情報送信関数
void GameUI::Draw()
{
	//開始、終了演出時のみ
	if (m_update_step == UpdateStep::StartProduction || m_update_step == UpdateStep::EndProduction)
	{
		mp_production->Draw();
	}

	mp_turn->Draw();
	mp_shot_gauge->Draw();
	mp_player_mode->Draw();
	mp_game_score->Draw();

}

//更新関数
void GameUI::Update(Player* player_, Camera* camera_)
{
	player_->GetPlayerInfo(m_player_infocopy);
	ProductionUI::ProductionInfo production_info;

	switch (m_update_step)
	{
	case UpdateStep::StartProduction:  //開始演出ステップ
		mp_production->StartProduction(camera_);

		mp_production->GetProductionInfo(production_info);

		if (production_info.m_is_start_game == true)
		{
			m_update_step = UpdateStep::GameMain; //更新ステップをゲーム本編へ
		}

		break;
	case UpdateStep::GameMain:
		mp_player_mode->Update();                                        //モード切り替え判定
		mp_shot_gauge->Update(player_, m_player_infocopy.m_is_turnend); //スピードゲージ更新
		mp_game_score->AddScore(m_player_infocopy.m_is_turnend);        //スコア更新
		mp_turn->Update(m_player_infocopy.m_is_turnend);                //ターン更新

		//プレイヤーがゴールした場合
		if (m_player_infocopy.m_is_goal == true)
		{
			m_update_step = UpdateStep::EndProduction;
		}
		break;
	case UpdateStep::EndProduction: //終了演出ステップ
		mp_production->EndProduction();

		mp_production->GetProductionInfo(production_info);

		//演出が終わったら
		if (production_info.m_is_end_game == true)
		{
			m_gameui_info.m_is_endgame = true;
		}
		break;
	default:
		break;
	}
}

//テクスチャ解放関数
void GameUI::ReleaseTex()
{
	//各UIを配列でまとめる
	UIBase* ui[GameUICategoryNum] =
	{ mp_game_score ,mp_player_mode,mp_production ,mp_shot_gauge ,mp_turn };

	for (int i = 0; i < GameUICategoryNum; i++)
	{
		ui[i]->ReleaseTex();
	}
}

