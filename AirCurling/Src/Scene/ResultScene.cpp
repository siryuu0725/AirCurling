#include "ResultScene.h"
#include "../System/Inputter.h"
#include "SceneController.h"
#include "../Score/GameScore.h"

//!コンストラクタ
ResultScene::ResultScene()
{
	cur_step_step = SceneStep::InitStep;	
}

//!描画情報送信まとめ関数
void ResultScene::Draw()
{
	m_ui->Draw();
}

//! 初期化ステップ関数
void ResultScene::InitStep()
{
	//!UIインスタンス化
	if (m_ui == nullptr) { m_ui = new ResultUI(); }

	//!UI初期化
	m_ui->Init();

	SoundManager::Instance()->RegisterResultSound();
	SoundManager::Instance()->SoundBGM(-300);

	//!次のステップへ
	cur_step_step = SceneStep::ThreadStep;
}

//!スレッド更新ステップ関数
void ResultScene::UpdateThreadStep()
{
	//!次のステップへ
	cur_step_step = SceneStep::MainStep;
}

//!更新ステップ関数
void ResultScene::MainStep()
{
	if (Inputter::Instance()->OnMouseDown(Inputter::Left))
	{
		//!次のステップへ
		cur_step_step = SceneStep::EndStep;
	}
}

//!終了ステップ関数
void ResultScene::EndStep()
{
	//!UI解放
	m_ui->ReleaseTex();
	delete m_ui;
	m_ui = nullptr;

	//!スコア初期化
	Score::Instance()->Reset();
	
	SoundManager::Instance()->ReleaseReselutSound();
	SceneController::Instance()->SetSceneId(SceneId::Title);

	//!シーン移行フラグtrue
	m_change_scene = true;
}

//!インスタンス返還関数
SceneBase* ResultScene::InstanceResultScene()
{
	return static_cast<SceneBase*>(new ResultScene);
}


