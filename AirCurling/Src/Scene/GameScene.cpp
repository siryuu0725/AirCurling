#include "GameScene.h"
#include "../System/Inputter.h"
#include "../System/FBX.h"
#include "../System/Effect.h"

#include <thread>

//コンストラクタ
GameScene::GameScene() :
	mp_camera(nullptr),
	mp_block(nullptr), 
	mp_player(nullptr), 
	mp_player_direction(nullptr), 
	mp_sky_dome(nullptr),
	mp_sky_floor(nullptr),
	mp_floor(nullptr),
	mp_debuf(nullptr),
	mp_goal(nullptr),
	mp_gmae_ui(nullptr),
	mp_load_ui(nullptr),
	mp_pose_ui(nullptr),
	m_is_pose(false),
	m_re_title(false)
{
	m_cur_step = SceneStep::InitStep;
}

//描画情報送信まとめ関数
void GameScene::Draw()
{
	//ロード画面描画
	if (WaitForSingleObject(thread_h, 0) != WAIT_OBJECT_0)
	{
		mp_load_ui->Draw();
		return;
	}

	//オブジェクト
	DrawObject();

	//ゲームUI
	mp_gmae_ui->Draw();

	//ポーズ中のみ
	if (m_is_pose == true)
	{
		mp_pose_ui->Draw();
	}

	//エフェクト描画開始
	Effect::Instance()->StartEffect();

	//エフェクト描画
	Effect::Instance()->DrawEffect();

	//エフェクト描画終了
	Effect::Instance()->EndEffect();

}

//初期化ステップ関数
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

	//UIインスタンス化
	if (mp_gmae_ui == nullptr) { mp_gmae_ui = new GameUI(); }
	if (mp_load_ui == nullptr) { mp_load_ui = new LoadUI(); }
	if (mp_pose_ui == nullptr) { mp_pose_ui = new PauseUI(); }

	//オブジェクトインスタンス化
	if (mp_block == nullptr) { mp_block = new BlockController; }
	if (mp_sky_dome == nullptr) { mp_sky_dome = new SkyDome; }
	if (mp_sky_floor == nullptr) { mp_sky_floor = new SkyFloor; }
	if (mp_floor == nullptr) { mp_floor = new Floor; }
	if (mp_debuf == nullptr) { mp_debuf = new DebufController; }
	if (mp_goal == nullptr) { mp_goal = new Goal; }
	if (mp_camera == nullptr) { mp_camera = new Camera(); }
	if (mp_player == nullptr) { mp_player = new Player(mp_camera, mp_block, mp_floor, mp_debuf, mp_goal); }
	if (mp_player_direction == nullptr) { mp_player_direction = new PlayerDirection(mp_player,mp_camera); }

	//オブジェクト初期化
	InitObject();

	//UI初期化
	mp_gmae_ui->Init();
	mp_load_ui->Init();
	mp_pose_ui->Init();

	//エフェクト初期化
	Effect::Instance()->InitEffect();

	//サウンド初期化
	SoundController::Instance()->RegisterGameSound();
	SoundController::Instance()->SoundBGM(GameBGMVolume);

	m_is_pose = false;
	m_re_title = false;

	//スレッドステップへ
	m_cur_step = SceneStep::ThreadStep;
}

//ロード画面更新ステップ関数
void GameScene::UpdateThreadStep()
{
	//ロード画面演出用
	if (WaitForSingleObject(thread_h, 0) != WAIT_OBJECT_0)
	{
		mp_load_ui->Update();
		return;
	}

	m_cur_step = SceneStep::MainStep;
}

//更新ステップ関数
void GameScene::MainStep()
{
	//ポーズ中UIの情報取得
	PauseUI::PauseUIInfo pose_ui_infocopy;
	mp_pose_ui->GetHelpUIInfo(pose_ui_infocopy);

	//ゲームUIの情報取得
	GameUI::GameUIInfo game_ui_infocopy;
	mp_gmae_ui->GetGameUIInfo(game_ui_infocopy);

	//ポーズ中出ない時
	if (m_is_pose == false)
	{
		//オブジェクトの更新
		UpdateObject();

		//UIの更新
		mp_gmae_ui->Update(mp_player, mp_camera);

		//エフェクト更新
		Effect::Instance()->UpdateEffect(mp_camera);
	}
	else
	{
		PauseUI::PauseUIInfo pose_ui_infocopy;

		//ポーズ中UI更新
		mp_pose_ui->Update();

		mp_pose_ui->GetHelpUIInfo(pose_ui_infocopy);

		//ポーズ中、「つづける」が押された場合
		if (pose_ui_infocopy.m_is_continue == true)
		{
			m_is_pose = false;
		}
		//ポーズ中、「おわる」が押された場合
		else if (pose_ui_infocopy.m_is_end == true)
		{
			m_re_title = true;
			m_cur_step = SceneStep::EndStep;
		}
	}

	

	//ポーズ画面切り替え
	if(Inputter::Instance()->GetKeyDown(Inputter::ESCKey))
	{
		//ポーズ中、「つづける」が押された場合
		if (pose_ui_infocopy.m_is_help == false)
		{
			m_is_pose = !m_is_pose;
		}
		
	}

	//ゴール、もしくはターン制限を超えた時
	if (game_ui_infocopy.m_is_endgame == true)
	{
		SoundController::Instance()->StopSE(PlaySEType::Goal);
		m_cur_step = SceneStep::EndStep;
	}
}

//終了ステップ関数
void GameScene::EndStep()
{
	SoundController::Instance()->ReleaseGameSound();

	DeleteObject();

	DeleteUI();

	if (m_re_title == true)
	{
		SceneController::Instance()->SetSceneId(SceneId::Title);
	}
	else
	{
		SceneController::Instance()->SetSceneId(SceneId::Result);
	}
	
	m_is_change_scene = true;
}

//オブジェクト初期化関数
void GameScene::InitObject()
{
	//選択ステージ保存
	std::string stage_str = SceneController::Instance()->GetStageID();

	//各オブジェクトを配列でまとめる
	ObjectBase* obj[StageObjectNum] =
	{ mp_camera ,mp_player ,mp_block,mp_debuf,mp_sky_dome ,mp_sky_floor ,mp_floor ,mp_goal,mp_player_direction };

	for (int i = 0; i < StageObjectNum; i++)
	{
		obj[i]->Init(stage_str);
	}

	//プレイヤー方向オブジェクトだけステージIDが変わっても初期化の処理が変わらないため別
	mp_player_direction->Init();
}

//オブジェクト更新関数
void GameScene::UpdateObject()
{
	Player::PlayerInfo player_info;
	mp_player->GetPlayerInfo(player_info);

	mp_player->Update();
	mp_camera->Update(player_info.m_pos);
	mp_player_direction->Update();
}

//オブジェクト描画情報送信関数
void GameScene::DrawObject()
{
	//各オブジェクトを配列でまとめる
	ObjectBase* obj[StageObjectNum] =
	{ mp_camera ,mp_player ,mp_block,mp_debuf,mp_sky_dome ,mp_sky_floor ,mp_floor ,mp_goal,mp_player_direction };

	for (int i = 0; i < StageObjectNum; i++)
	{
		obj[i]->Draw();
	}
}

//オブジェクト解放関数
void GameScene::DeleteObject()
{
	//カメラ
	delete mp_camera;
	mp_camera = nullptr;

	//ブロック
	mp_block->ReleaseModel();
	delete mp_block;
	mp_block = nullptr;

	//プレイヤー
	mp_player->ReleaseModel();
	delete mp_player;
	mp_player = nullptr;

	//プレイヤー矢印
	mp_player_direction->ReleaseModel();
	delete mp_player_direction;
	mp_player_direction = nullptr;

	//背景
	mp_sky_dome->ReleaseModel();
	delete mp_sky_dome;
	mp_sky_dome = nullptr;

	//背景床
	mp_sky_floor->ReleaseModel();
	delete mp_sky_floor;
	mp_sky_floor = nullptr;

	//ステージ床
	mp_floor->ReleaseModel();
	delete mp_floor;
	mp_floor = nullptr;

	//デバフ床
	mp_debuf->ReleaseModel();
	delete mp_debuf;
	mp_debuf = nullptr;

	//ゴール床
	mp_goal->ReleaseModel();
	delete mp_goal;
	mp_goal = nullptr;
}

//UI解放関数
void GameScene::DeleteUI()
{
	//ゲーム本編用UI
	mp_gmae_ui->ReleaseTex();
	delete mp_gmae_ui;
	mp_gmae_ui = nullptr;

	//ロード画面用UI
	mp_load_ui->ReleaseTex();
	delete mp_load_ui;
	mp_load_ui = nullptr;

	//ポーズ画面用UI
	mp_pose_ui->ReleaseTex();
	delete mp_pose_ui;
	mp_pose_ui = nullptr;
}

//インスタンス返還関数
SceneBase* GameScene::Instance()
{
	return static_cast<SceneBase*>(new GameScene);
}

DWORD WINAPI GameScene::LoadResorse(LPVOID lpparm)
{
	FbxController::Instance()->LoadFbx();

	Effect::Instance()->LoadEffect();

	return 0;
}
