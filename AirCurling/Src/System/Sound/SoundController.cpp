#include "SoundController.h"

SoundManager* SoundManager::p_instance = nullptr;

SoundManager* SoundManager::Instance()
{
	if (p_instance == nullptr) { p_instance = new SoundManager; }

	return p_instance;
}

void SoundManager::RegisterTitleSound()
{
	bgm_file = "Res/wav/BGM/Title.wav";
	se1_file = "Res/wav/SE/Select.wav";
	click_se_file = "Res/wav/SE/Decision.wav";
	cancel_file = "Res/wav/SE/Reset.wav";
	p_audio->LoadUI(bgm, bgm_file);
	p_audio->LoadUI(select1_se, se1_file);
	p_audio->LoadUI(click_se, click_se_file);
	p_audio->LoadUI(cancel_se, cancel_file);
}

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

void SoundManager::RegisterHelpSound()
{
}

void SoundManager::RegisterResultSound()
{
	bgm_file = "Res/wav/BGM/Result.wav";

	p_audio->LoadUI(bgm, bgm_file);
}


void SoundManager::SoundBGM(int volume_)
{
	p_audio->Play(bgm, volume_, true);
}

void SoundManager::SoundSelectBGM()
{
	p_audio->Play(bgm, 0, true);
}

void SoundManager::SoundSelectSE()
{
	if (m_select1_flag == false)
	{
		p_audio->Play(select1_se, -1000, false);
		m_select1_flag = true;
		m_cancel_flag = false;
	}
}

void SoundManager::SoundCancelSE()
{
	if (m_cancel_flag == false)
	{
		p_audio->Play(cancel_se, -1000, false);
		m_select1_flag = false;
		m_cancel_flag = true;
	}
}

void SoundManager::SoundClickSE()
{
	p_audio->Play(click_se, 0, false);
}

void SoundManager::SoundShotSE()
{
	p_audio->Play(shot_se, 0, false);
}

void SoundManager::SoundReflectSE()
{
	p_audio->Play(reflect_se, 0, false);
}

void SoundManager::SoundGoalSE()
{
	p_audio->Play(goal_se, 0, false);
}

void SoundManager::SoundFrictionSE()
{
	p_audio->Play(friction_se, 0, false);
}

void SoundManager::SoundFallSE()
{
	p_audio->Play(fall_se, 0, false);
}


void SoundManager::ResetSelectFlag()
{
	m_select1_flag = false;
	m_cancel_flag = false;
}

void SoundManager::ReleaseTitleSound()
{
	p_audio->Release(bgm);
	p_audio->Release(select1_se);
	p_audio->Release(click_se);
	p_audio->Release(cancel_se);

}

void SoundManager::ReleaseSelectSound()
{
	p_audio->Release(bgm);

}

void SoundManager::ReleaseGameSound()
{
	p_audio->Release(bgm);
}

void SoundManager::ReleaseReselutSound()
{
	p_audio->Release(bgm);
}

SoundManager::SoundManager()
{
	m_select1_flag = false;
	m_cancel_flag = false;

	bgm = "BGM";
	select1_se = "SelectSE";
	click_se = "ClickSE";
	cancel_se = "CancelSE";

	shot_se = "ShotSE";
	reflect_se = "ReflectionSE";
	goal_se = "GoalSE";
	friction_se = "StopSE";
	fall_se = "FallSE";
}


