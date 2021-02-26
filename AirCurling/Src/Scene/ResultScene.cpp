#include "ResultScene.h"
#include "../System/Inputter.h"
#include "SceneController.h"
#include "../Score/GameScore.h"

//!コンストラクタ
ResultScene::ResultScene():
	p_ui(nullptr)
{
	m_cur_step = SceneStep::InitStep;	
}

//!描画情報送信まとめ関数
void ResultScene::Draw()
{
	p_ui->Draw();
}

//! 初期化ステップ関数
void ResultScene::InitStep()
{
	//!UIインスタンス化
	if (p_ui == nullptr) { p_ui = new ResultUI(); }

	//!UI初期化
	p_ui->Init();

	SoundManager::Instance()->RegisterResultSound();
	SoundManager::Instance()->SoundBGM(ResultBGMVolume);

	//!次のステップへ
	m_cur_step = SceneStep::ThreadStep;
}

//!スレッド更新ステップ関数
void ResultScene::UpdateThreadStep()
{
	//!次のステップへ
	m_cur_step = SceneStep::MainStep;
}

//!更新ステップ関数
void ResultScene::MainStep()
{
	if (Inputter::Instance()->OnMouseDown(Inputter::Left))
	{
		//!次のステップへ
		m_cur_step = SceneStep::EndStep;
	}
}

//!終了ステップ関数
void ResultScene::EndStep()
{
	//!UI解放
	p_ui->ReleaseTex();
	delete p_ui;
	p_ui = nullptr;

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


