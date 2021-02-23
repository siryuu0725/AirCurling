#include "GameScene.h"
#include "../System/Inputter.h"
#include "../System/FBX.h"
#include "../System/Effect.h"

#include <thread>

//!コンストラクタ
GameScene::GameScene()
{
	cur_step_step = SceneStep::InitStep;
}

//!描画情報送信まとめ関数
void GameScene::SetUpBuffer()
{
	//ロード画面描画
	if (WaitForSingleObject(thread_h, 0) != WAIT_OBJECT_0)
	{
		m_load_ui->SetUpBuffer();
		return;
	}

	//!オブジェクト
	ObjectSetUpBuffer();

	//!ゲームUI
	m_gmae_ui->SetUpBuffer();

	//!ポーズ中のみ
	if (m_is_pose == true)
	{
		m_pose_ui->SetUpBuffer();
	}

	//!エフェクト描画開始
	Effect::Instance()->StartEffect();

	//!エフェクト描画
	Effect::Instance()->DrawEffect();

	//!エフェクト描画終了
	Effect::Instance()->EndEffect();

}

//!初期化ステップ関数
void GameScene::InitStep()
{
	//各読み込み関数をマルチ化
	thread_h = CreateThread(
		NULL,
		0,
		this->LoadResorse,
		NULL,
		0,
		&thread_id);

	//!UIインスタンス化
	if (m_gmae_ui == nullptr) { m_gmae_ui = new GameUI(); }
	if (m_load_ui == nullptr) { m_load_ui = new LoadUI(); }
	if (m_pose_ui == nullptr) { m_pose_ui = new PoseUI(); }

	//!オブジェクトインスタンス化
	if (m_block_controller == nullptr) { m_block_controller = new BlockController; }
	if (m_sky_dome == nullptr) { m_sky_dome = new SkyDome; }
	if (m_sky_floor == nullptr) { m_sky_floor = new SkyFloor; }
	if (m_floor == nullptr) { m_floor = new Floor; }
	if (m_debuf == nullptr) { m_debuf = new DebufController; }
	if (m_goal == nullptr) { m_goal = new Goal; }
	if (m_camera == nullptr) { m_camera = new Camera(); }
	if (m_player == nullptr) { m_player = new Player(m_camera, m_block_controller, m_floor, m_debuf, m_goal); }
	if (m_player_direction == nullptr) { m_player_direction = new PlayerDirection(m_player,m_camera, m_gmae_ui); }

	//!オブジェクト初期化
	ObjectInit();

	//!UI初期化
	m_gmae_ui->Init();
	m_load_ui->Init();
	m_pose_ui->Init();

	//!エフェクト初期化
	Effect::Instance()->InitEffect();

	//!サウンド初期化
	SoundManager::Instance()->RegisterGameSound();
	SoundManager::Instance()->SoundBGM(-300);

	//!スレッドステップへ
	cur_step_step = SceneStep::ThreadStep;
}

//!ロード画面更新ステップ関数
void GameScene::UpdateThreadStep()
{
	//ロード画面演出用
	if (WaitForSingleObject(thread_h, 0) != WAIT_OBJECT_0)
	{
		m_load_ui->Update();
		return;
	}

	cur_step_step = SceneStep::MainStep;
}

//!更新ステップ関数
void GameScene::MainStep()
{
	//!ポーズ中出ない時
	if (m_is_pose == false)
	{
		//!オブジェクトの更新
		ObjectUpdate();

		//!UIの更新
		m_gmae_ui->Update(m_player, m_camera);

		//!エフェクト更新
		Effect::Instance()->UpdateEffect(m_camera);
	}
	else
	{
		//!ポーズ中UI更新
		m_pose_ui->Update();

		//!ポーズ中、「つづける」が押された場合
		if (m_pose_ui->GetGameUIInfo()->m_continue == true)
		{
			m_is_pose = false;
		}
		//!ポーズ中、「おわる」が押された場合
		else if (m_pose_ui->GetGameUIInfo()->m_end == true)
		{
			PostQuitMessage(0);
		}
	}

	

	//!ポーズ画面切り替え
	if(Inputter::Instance()->GetKeyDown(Inputter::ESC_KEY))
	{
		//!ポーズ中、「つづける」が押された場合
		if (m_pose_ui->GetGameUIInfo()->m_help == false)
		{
			m_is_pose = (m_is_pose == true) ? false : true;
		}
		
	}

	//!ゴール、もしくはターン制限を超えた時
	if (m_gmae_ui->GetGameUIInfo()->m_end_game == true)
	{
		cur_step_step = SceneStep::EndStep;
	}

	if (Inputter::Instance()->GetKeyDown(Inputter::E_KEY))
	{
		PostQuitMessage(0);
	}
}

//!終了ステップ関数
void GameScene::EndStep()
{
	SoundManager::Instance()->ReleaseGameSound();

	ObjectDelete();

	SceneController::Instance()->SetSceneId(SceneId::Result);

	m_change_scene = true;
}

//!オブジェクト初期化関数
void GameScene::ObjectInit()
{
	m_camera->Init(SceneController::Instance()->GetStageID());
	m_block_controller->Init(SceneController::Instance()->GetStageID());
	m_player->Init(SceneController::Instance()->GetStageID());
	m_sky_dome->Init(SceneController::Instance()->GetStageID());
	m_sky_floor->Init(SceneController::Instance()->GetStageID());
	m_floor->Init(SceneController::Instance()->GetStageID());
	m_debuf->Init(SceneController::Instance()->GetStageID());
	m_goal->Init(SceneController::Instance()->GetStageID());
	m_player_direction->Init();
}

//!オブジェクト更新関数
void GameScene::ObjectUpdate()
{
	m_player->Update();
	m_camera->Update(m_player->GetObjInfo()->m_pos);
	m_player_direction->Update();
}

//!オブジェクト描画情報送信関数
void GameScene::ObjectSetUpBuffer()
{
	m_block_controller->SetUpBuffer();
	m_player->SetUpBuffer();
	m_player_direction->SetUpBuffer();
	m_sky_dome->SetUpBuffer();
	m_sky_floor->SetUpBuffer();
	m_floor->SetUpBuffer();
	m_debuf->SetUpBuffer();
	m_goal->SetUpBuffer();
}

//!オブジェクト解放関数
void GameScene::ObjectDelete()
{
	//!カメラ
	delete m_camera;
	m_camera = nullptr;

	//!ブロック
	m_block_controller->ReleaseModel();
	delete m_block_controller;
	m_block_controller = nullptr;

	//!プレイヤー
	m_player->ReleaseModel();
	delete m_player;
	m_player = nullptr;

	//!プレイヤー矢印
	m_player_direction->ReleaseModel();
	delete m_player_direction;
	m_player_direction = nullptr;

	//!背景
	m_sky_dome->ReleaseModel();
	delete m_sky_dome;
	m_sky_dome = nullptr;

	//!背景床
	m_sky_floor->ReleaseModel();
	delete m_sky_floor;
	m_sky_floor = nullptr;

	//!ステージ床
	m_floor->ReleaseModel();
	delete m_floor;
	m_floor = nullptr;

	//!デバフ床
	m_debuf->ReleaseModel();
	delete m_debuf;
	m_debuf = nullptr;

	//!ゴール床
	m_goal->ReleaseModel();
	delete m_goal;
	m_goal = nullptr;
}

//!UI解放関数
void GameScene::UIDelete()
{
	//!ゲーム本編用UI
	m_gmae_ui->ReleaseTex();
	delete m_gmae_ui;
	m_gmae_ui = nullptr;

	//!ロード画面用UI
	m_load_ui->ReleaseTex();
	delete m_load_ui;
	m_load_ui = nullptr;

	//!ポーズ画面用UI
	m_pose_ui->ReleaseTex();
	delete m_pose_ui;
	m_pose_ui = nullptr;
}

//!インスタンス返還関数
SceneBase* GameScene::InstanceGameScene()
{
	return static_cast<SceneBase*>(new GameScene);
}

DWORD WINAPI GameScene::LoadResorse(LPVOID lpparm)
{
	FbxController::Instance()->LoadFbx();

	Effect::Instance()->LoadEffect();

	return 0;
}
