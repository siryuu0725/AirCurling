#include "TitleScene.h"
#include <WinUser.h>
#include "SceneController.h"
#include "../Score/GameScore.h"

//初期化ステップ関数
void TitleScene::InitStep()
{
	if (mp_ui == nullptr) { mp_ui = new TitleUI; }

	mp_ui->Init(); //UI初期化

	//サウンド初期化
	SoundController::Instance()->RegisterTitleSound();
	SoundController::Instance()->SoundBGM(TitleBGMVolume);

	m_cur_step = SceneStep::MainStep;
}

//スレッド更新ステップ関数
void TitleScene::UpdateThreadStep()
{
	m_cur_step = SceneStep::MainStep;
}

//更新ステップ関数
void TitleScene::MainStep()
{
	TitleUI::TitleUIInfo ui_info;

	//UI更新
	mp_ui->Update();

	mp_ui->GetTitleUIInfo(ui_info);

	//ステージ選択が終わった場合
	if (ui_info.m_is_stage_1 == true || ui_info.m_is_stage_2 == true)
	{
		//m_sound_manager->SoundClickSE();
		m_cur_step = SceneStep::EndStep;
	}
	//「おわる」が選択された場合
	else if (ui_info.endui_flg == true)
	{
		PostQuitMessage(0);

		//UI解放
		mp_ui->ReleaseTex();

		delete mp_ui;
		mp_ui = nullptr;

		//サウンド解放
		SoundController::Instance()->ReleaseTitleSound();

#ifdef _DEBUG
		SoundController::Instance()->ReleaseInstance();
		Score::Instance()->ReleaseInstance();
#endif
	}
}

//終了ステップ関数
void TitleScene::EndStep()
{
	TitleUI::TitleUIInfo ui_info;

	mp_ui->GetTitleUIInfo(ui_info);

	//UI解放
	mp_ui->ReleaseTex();
	delete mp_ui;
	mp_ui = nullptr;

	//サウンド解放
	SoundController::Instance()->ReleaseTitleSound();

	//マウスを画面中心に
	SetCursorPos(960, 540);

	//初期化ステップに変更
	m_cur_step = SceneStep::InitStep;

	//ステージ1が選ばれた場合
	if (ui_info.m_is_stage_1 == true)
	{
		SceneController::Instance()->SetStageID("Stage1");
	}
	//ステージ2が選ばれた場合
	else if(ui_info.m_is_stage_2 == true)
	{
		SceneController::Instance()->SetStageID("Stage2");
	}

	SceneController::Instance()->SetSceneId(SceneId::Game);
	m_is_change_scene = true;
}

//描画情報送信まとめ関数
void TitleScene::Draw()
{
	if (mp_ui != nullptr)
	{
		mp_ui->Draw();
	}
}

//インスタンス返還関数
SceneBase* TitleScene::Instance()
{
	return static_cast<SceneBase*>(new TitleScene);
}


