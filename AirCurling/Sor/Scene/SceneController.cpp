#include "SceneController.h"
#include"../Scene/TitleScene.h"
#include"../Scene/GameScene.h"
#include"../Scene/ResultScene.h"
#include"../System/Inputter.h"
#include"../System/Graphics.h"
#include <thread>

SceneController* SceneController::p_instance = nullptr;

//!インスタンス化関数
SceneController* SceneController::Instance()
{
	if (p_instance == nullptr)
	{
		p_instance = new SceneController;
	}

	return p_instance;
}

void SceneController::Init()
{
	m_scene = nullptr;

	Graphics::Instance()->SetRenderMode(true);

	Graphics::Instance()->GetD3DDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	Graphics::Instance()->SetLight();
}

//!更新関数
void SceneController::Update()
{
	//!入力クラス更新
	Inputter::Instance()->UpdateInput();

	//!シーン切り替え判定
	ChangeScene();

	//!各シーン更新
	m_scene->Update();
}

//!描画関数
void SceneController::Draw()
{
	//!各シーンで更新もしくはロードステップ中のみ描画
	if (m_scene->NowStep() == SceneStep::ThreadStep ||
		m_scene->NowStep() == SceneStep::MainStep)
	{
		//!描画開始
		Graphics::Instance()->DrawStart();

		//!描画情報送信関数
		SetUpBuffer();

		Graphics::Instance()->DrawEnd();
	}
}

//!描画情報送信関数
void SceneController::SetUpBuffer()
{
	m_scene->SetUpBuffer();
}

//!現在シーンSetter
void SceneController::SetSceneId(SceneId sceneid_)
{
	m_cur_scene_id = sceneid_;
}

//!シーン切り替え判定関数
void SceneController::ChangeScene()
{
	if (m_scene == nullptr) { m_scene = new TitleScene; }

	if (m_scene->GetChangeSceneFlg() == true)
	{
		delete m_scene;
		m_scene = nullptr;

		//!指定のゲームの管理クラスに切り替える
		m_scene = s_controller_array[static_cast<int>(m_cur_scene_id)]();
	}
}

void SceneController::SetStageID(std::string stage_)
{
	m_stage = stage_;
}

//!各ゲーム管理クラスアドレス配列
SceneBase* (*SceneController::s_controller_array[static_cast<int>(SceneId::Max)])() =
{
	TitleScene::InstanceTitleScene,   //!タイトル
	GameScene::InstanceGameScene,	  //!ゲーム
	ResultScene::InstanceResultScene  //!リザルト
};

//!デストラクタ
SceneController::~SceneController()
{
	delete m_scene;
	m_scene = nullptr;

}
