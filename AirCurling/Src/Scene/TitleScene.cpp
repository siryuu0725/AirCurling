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
	TitleUI::TitleUIInfo ui_info;

	//!UI更新
	p_ui->Update();

	p_ui->GetTitleUIInfo(ui_info);

	//!ステージ選択が終わった場合
	if (ui_info.m_stage_1 == true || ui_info.m_stage_2 == true)
	{
		//m_sound_manager->SoundClickSE();
		m_cur_step = SceneStep::EndStep;
	}
	//!「おわる」が選択された場合
	else if (ui_info.endui_flg == true)
	{
		PostQuitMessage(0);
	}
}

//!終了ステップ関数
void TitleScene::EndStep()
{
	TitleUI::TitleUIInfo ui_info;

	p_ui->GetTitleUIInfo(ui_info);

	//!UI解放
	p_ui->ReleaseTex();

	//!サウンド解放
	SoundManager::Instance()->ReleaseTitleSound();

	//!マウスを画面中心に
	SetCursorPos(960, 540);

	//!初期化ステップに変更
	m_cur_step = SceneStep::InitStep;

	//!ステージ1が選ばれた場合
	if (ui_info.m_stage_1 == true)
	{
		SceneController::Instance()->SetStageID("Stage1");
	}
	//!ステージ2が選ばれた場合
	else if(ui_info.m_stage_2 == true)
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


