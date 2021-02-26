#include "GameScene.h"
#include "../System/Inputter.h"
#include "../System/FBX.h"
#include "../System/Effect.h"

#include <thread>

//!コンストラクタ
GameScene::GameScene() :
	p_camera(nullptr),
	p_block_controller(nullptr), 
	m_player(nullptr), 
	m_player_direction(nullptr), 
	m_sky_dome(nullptr),
	m_sky_floor(nullptr),
	p_floor(nullptr),
	p_debuf(nullptr),
	p_goal(nullptr),
	p_gmae_ui(nullptr),
	p_load_ui(nullptr),
	p_pose_ui(nullptr),
	m_is_pose(false)
{
	m_cur_step = SceneStep::InitStep;
}

//!描画情報送信まとめ関数
void GameScene::Draw()
{
	//ロード画面描画
	if (WaitForSingleObject(thread_h, 0) != WAIT_OBJECT_0)
	{
		p_load_ui->Draw();
		return;
	}

	//!オブジェクト
	ObjectDraw();

	//!ゲームUI
	p_gmae_ui->Draw();

	//!ポーズ中のみ
	if (m_is_pose == true)
	{
		p_pose_ui->Draw();
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
		nullptr,
		0,
		this->LoadResorse,
		nullptr,
		0,
		&thread_id);

	//!UIインスタンス化
	if (p_gmae_ui == nullptr) { p_gmae_ui = new GameUI(); }
	if (p_load_ui == nullptr) { p_load_ui = new LoadUI(); }
	if (p_pose_ui == nullptr) { p_pose_ui = new PoseUI(); }

	//!オブジェクトインスタンス化
	if (p_block_controller == nullptr) { p_block_controller = new BlockController; }
	if (m_sky_dome == nullptr) { m_sky_dome = new SkyDome; }
	if (m_sky_floor == nullptr) { m_sky_floor = new SkyFloor; }
	if (p_floor == nullptr) { p_floor = new Floor; }
	if (p_debuf == nullptr) { p_debuf = new DebufController; }
	if (p_goal == nullptr) { p_goal = new Goal; }
	if (p_camera == nullptr) { p_camera = new Camera(); }
	if (m_player == nullptr) { m_player = new Player(p_camera, p_block_controller, p_floor, p_debuf, p_goal); }
	if (m_player_direction == nullptr) { m_player_direction = new PlayerDirection(m_player,p_camera, p_gmae_ui); }

	//!オブジェクト初期化
	ObjectInit();

	//!UI初期化
	p_gmae_ui->Init();
	p_load_ui->Init();
	p_pose_ui->Init();

	//!エフェクト初期化
	Effect::Instance()->InitEffect();

	//!サウンド初期化
	SoundManager::Instance()->RegisterGameSound();
	SoundManager::Instance()->SoundBGM(GameBGMVolume);

	//!スレッドステップへ
	m_cur_step = SceneStep::ThreadStep;
}

//!ロード画面更新ステップ関数
void GameScene::UpdateThreadStep()
{
	//ロード画面演出用
	if (WaitForSingleObject(thread_h, 0) != WAIT_OBJECT_0)
	{
		p_load_ui->Update();
		return;
	}

	m_cur_step = SceneStep::MainStep;
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
		p_gmae_ui->Update(m_player, p_camera);

		//!エフェクト更新
		Effect::Instance()->UpdateEffect(p_camera);
	}
	else
	{
		//!ポーズ中UI更新
		p_pose_ui->Update();

		//!ポーズ中、「つづける」が押された場合
		if (p_pose_ui->GetGameUIInfo()->m_continue == true)
		{
			m_is_pose = false;
		}
		//!ポーズ中、「おわる」が押された場合
		else if (p_pose_ui->GetGameUIInfo()->m_end == true)
		{
			PostQuitMessage(0);
		}
	}

	

	//!ポーズ画面切り替え
	if(Inputter::Instance()->GetKeyDown(Inputter::ESC_KEY))
	{
		//!ポーズ中、「つづける」が押された場合
		if (p_pose_ui->GetGameUIInfo()->m_help == false)
		{
			m_is_pose = (m_is_pose == true) ? false : true;
		}
		
	}

	//!ゴール、もしくはターン制限を超えた時
	if (p_gmae_ui->GetGameUIInfo()->m_end_game == true)
	{
		m_cur_step = SceneStep::EndStep;
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
	p_camera->Init(SceneController::Instance()->GetStageID());
	p_block_controller->Init(SceneController::Instance()->GetStageID());
	m_player->Init(SceneController::Instance()->GetStageID());
	m_sky_dome->Init(SceneController::Instance()->GetStageID());
	m_sky_floor->Init(SceneController::Instance()->GetStageID());
	p_floor->Init(SceneController::Instance()->GetStageID());
	p_debuf->Init(SceneController::Instance()->GetStageID());
	p_goal->Init(SceneController::Instance()->GetStageID());
	m_player_direction->Init();
}

//!オブジェクト更新関数
void GameScene::ObjectUpdate()
{
	m_player->Update();
	p_camera->Update(m_player->GetObjInfo()->m_pos);
	m_player_direction->Update();
}

//!オブジェクト描画情報送信関数
void GameScene::ObjectDraw()
{
	p_block_controller->Draw();
	m_player->Draw();
	m_player_direction->Draw();
	m_sky_dome->Draw();
	m_sky_floor->Draw();
	p_floor->Draw();
	p_debuf->Draw();
	p_goal->Draw();
}

//!オブジェクト解放関数
void GameScene::ObjectDelete()
{
	//!カメラ
	delete p_camera;
	p_camera = nullptr;

	//!ブロック
	p_block_controller->ReleaseModel();
	delete p_block_controller;
	p_block_controller = nullptr;

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
	p_floor->ReleaseModel();
	delete p_floor;
	p_floor = nullptr;

	//!デバフ床
	p_debuf->ReleaseModel();
	delete p_debuf;
	p_debuf = nullptr;

	//!ゴール床
	p_goal->ReleaseModel();
	delete p_goal;
	p_goal = nullptr;
}

//!UI解放関数
void GameScene::UIDelete()
{
	//!ゲーム本編用UI
	p_gmae_ui->ReleaseTex();
	delete p_gmae_ui;
	p_gmae_ui = nullptr;

	//!ロード画面用UI
	p_load_ui->ReleaseTex();
	delete p_load_ui;
	p_load_ui = nullptr;

	//!ポーズ画面用UI
	p_pose_ui->ReleaseTex();
	delete p_pose_ui;
	p_pose_ui = nullptr;
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
