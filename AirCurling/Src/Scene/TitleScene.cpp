#include "TitleScene.h"
#include <WinUser.h>
#include "SceneController.h"

//!初期化ステップ関数
void TitleScene::InitStep()
{
	if (p_ui == nullptr) { p_ui = new TitleUI; }

	p_ui->Init(); //!UI初期化

	//!サウンド初期化
	SoundManager::Instance()->RegisterTitleSound();
	SoundManager::Instance()->SoundBGM(TitleBGMVolume);

	m_cur_step = SceneStep::MainStep;
}

//!スレッド更新ステップ関数
void TitleScene::UpdateThreadStep()
{
	m_cur_step = SceneStep::MainStep;
}

//!更新ステップ関数
void TitleScene::MainStep()
{
	//!UI更新
	p_ui->Update();

	//!ステージ選択が終わった場合
	if (p_ui->GetTitleUIInfo()->m_stage_1 == true || p_ui->GetTitleUIInfo()->m_stage_2 == true)
	{
		//m_sound_manager->SoundClickSE();
		m_cur_step = SceneStep::EndStep;
	}
	//!「おわる」が選択された場合
	else if (p_ui->GetTitleUIInfo()->endui_flg == true)
	{
		PostQuitMessage(0);
	}
}

//!終了ステップ関数
void TitleScene::EndStep()
{
	//!UI解放
	p_ui->ReleaseTex();

	//!サウンド解放
	SoundManager::Instance()->ReleaseTitleSound();

	//!マウスを画面中心に
	SetCursorPos(960, 540);

	//!初期化ステップに変更
	m_cur_step = SceneStep::InitStep;

	//!ステージ1が選ばれた場合
	if (p_ui->GetTitleUIInfo()->m_stage_1 == true)
	{
		SceneController::Instance()->SetStageID("Stage1");
	}
	//!ステージ2が選ばれた場合
	else if(p_ui->GetTitleUIInfo()->m_stage_2 == true)
	{
		SceneController::Instance()->SetStageID("Stage2");
	}

	SceneController::Instance()->SetSceneId(SceneId::Game);
	m_change_scene = true;
}

//!描画情報送信まとめ関数
void TitleScene::Draw()
{
	p_ui->Draw();
}

//!インスタンス返還関数
SceneBase* TitleScene::InstanceTitleScene()
{
	return static_cast<SceneBase*>(new TitleScene);
}


