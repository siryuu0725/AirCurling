#include "SoundController.h"

SoundManager* SoundManager::mp_instance = nullptr;

SoundManager* SoundManager::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new SoundManager; }

	return mp_instance;
}

SoundManager::SoundManager()
{
	m_select1_flag = false;

	bgm = "BGM";
	select1_se = "SelectSE";

	shot_se = "ShotSE";
	reflect_se = "ReflectionSE";
	goal_se = "GoalSE";
	friction_se = "StopSE";
	fall_se = "FallSE";
}


//タイトルシーン音源設定
void SoundManager::RegisterTitleSound()
{
	bgm_file = "Res/wav/BGM/Title.wav";
	se1_file = "Res/wav/SE/Select.wav";
	p_audio->LoadUI(bgm, bgm_file);
	p_audio->LoadUI(select1_se, se1_file);
}

//ゲームシーン音源設定
void SoundManager::RegisterGameSound()
{
	bgm_file = "Res/wav/BGM/Game.wav";
	shot_file = "Res/wav/SE/Shot.wav";
	reflect_file = "Res/wav/SE/Reflection.wav";
	goal_file = "Res/wav/SE/Goal.wav";
	friction_file = "Res/wav/SE/Stop.wav";
	//m_fall_file= "Res/wav/SE/落ちたとき.wav";

	p_audio->LoadUI(bgm, bgm_file);
	p_audio->LoadUI(shot_se, shot_file);
	p_audio->LoadUI(reflect_se, reflect_file);
	p_audio->LoadUI(goal_se, goal_file);
	p_audio->LoadUI(friction_se, friction_file);
	//m_pAudio->Load(m_fall_se, m_fall_file);


}

//リザルト(エンド)シーン音源設定
void SoundManager::RegisterResultSound()
{
	bgm_file = "Res/wav/BGM/Result.wav";

	p_audio->LoadUI(bgm, bgm_file);
}

//BGM再生関数
void SoundManager::SoundBGM(int volume_)
{
	p_audio->Play(bgm, volume_, true);
}

//選択SE音再生関数
void SoundManager::SoundSelectSE()
{
	if (m_select1_flag == false)
	{
		p_audio->Play(select1_se, SoundVolumeMin, false);
		m_select1_flag = true;
	}
}

//打った時のSE音再生関数
void SoundManager::SoundShotSE()
{
	p_audio->Play(shot_se, SoundVolumeMax, false);
}

//反射SE音再生関数
void SoundManager::SoundReflectSE()
{
	p_audio->Play(reflect_se, SoundVolumeMax, false);
}

//ゴールSE音再生関数
void SoundManager::SoundGoalSE()
{
	p_audio->Play(goal_se, SoundVolumeMax, false);
}

//スピード減衰時SE音再生関数
void SoundManager::SoundFrictionSE()
{
	p_audio->Play(friction_se, SoundVolumeMax, false);
}

//落下時SE音再生関数
void SoundManager::SoundFallSE()
{
	p_audio->Play(fall_se, SoundVolumeMax, false);
}

//選択フラグリセット関数
void SoundManager::ResetSelectFlag()
{
	m_select1_flag = false;
}

//タイトルシーンサウンド解放関数
void SoundManager::ReleaseTitleSound()
{
	p_audio->Release(bgm);
	p_audio->Release(select1_se);

}

//ゲームシーンサウンド解放関数
void SoundManager::ReleaseGameSound()
{
	p_audio->Release(bgm);
}

//エンド(リザルト)シーンサウンド解放関数
void SoundManager::ReleaseReselutSound()
{
	p_audio->Release(bgm);
}

