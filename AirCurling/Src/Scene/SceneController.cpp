#include "SceneController.h"
#include"../Scene/TitleScene.h"
#include"../Scene/GameScene.h"
#include"../Scene/ResultScene.h"
#include"../System/Inputter.h"
#include"../System/DirectGraphics.h"
#include <thread>

SceneController* SceneController::mp_instance = nullptr;

//インスタンス化関数
SceneController* SceneController::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new SceneController; }

	return mp_instance;
}

void SceneController::Init()
{
	mp_scene = nullptr;

	Graphics::Instance()->SetRenderMode(true);

	Graphics::Instance()->GetD3DDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	Graphics::Instance()->SetLight();
}

//更新関数
void SceneController::Update()
{
	//入力クラス更新
	Inputter::Instance()->UpdateInput();

	//シーン切り替え判定
	ChangeScene();

	//各シーン更新
	mp_scene->Update();
}

//描画関数
void SceneController::Draw()
{
	//各シーンで更新もしくはロードステップ中のみ描画
	if (mp_scene->NowStep() == SceneStep::ThreadStep ||
		mp_scene->NowStep() == SceneStep::MainStep)
	{
		//描画開始
		Graphics::Instance()->DrawStart();

		//描画情報送信関数
		mp_scene->Draw();

		Graphics::Instance()->DrawEnd();
	}
}

//現在シーンSetter
void SceneController::SetSceneId(SceneId sceneid_)
{
	m_scene_id = sceneid_;
}

//シーン切り替え判定関数
void SceneController::ChangeScene()
{
	if (mp_scene == nullptr) { mp_scene = new TitleScene; }

	if (mp_scene->GetIsChangeScene() == true)
	{
		delete mp_scene;
		//指定のゲームの管理クラスに切り替える
		mp_scene = s_controller_array[static_cast<int>(m_scene_id)]();
	}
}

void SceneController::SetStageID(std::string stage_)
{
	m_stagename = stage_;
}

//各ゲーム管理クラスアドレス配列
SceneBase* (*SceneController::s_controller_array[static_cast<int>(SceneId::Max)])() =
{
	TitleScene::Instance,   //タイトル
	GameScene::Instance,	  //ゲーム
	ResultScene::Instance  //リザルト
};

//デストラクタ
SceneController::~SceneController()
{
	delete mp_scene;
	mp_scene = nullptr;
}

//Instance解放関数(Debug用)
void SceneController::ReleaseInstance()
{
	delete mp_instance;
	mp_instance = nullptr;
}

