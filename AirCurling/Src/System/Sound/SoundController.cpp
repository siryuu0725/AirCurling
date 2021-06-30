#include "SoundController.h"

SoundController* SoundController::mp_instance = nullptr;

SoundController* SoundController::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new SoundController; }

	return mp_instance;
}

SoundController::~SoundController()
{
	AudioPlayer::Instance()->ReleaseInstance();
}

//コンストラクタ
SoundController::SoundController()
{
	m_is_select = false;

	m_bgm = "BGM";
	m_select_se = "SelectSE";

	m_shot_se = "ShotSE";
	m_reflect_se = "ReflectionSE";
	m_goal_se = "GoalSE";
	m_stop_se = "StopSE";
	m_reset_se = "FallSE";
}


//タイトルシーン音源設定
void SoundController::RegisterTitleSound()
{
	m_bgm_file = "Res/wav/BGM/Title.wav";
	m_select_file = "Res/wav/SE/Select.wav";
	AudioPlayer::Instance()->LoadAudioFail(m_bgm, m_bgm_file);
	AudioPlayer::Instance()->LoadAudioFail(m_select_se, m_select_file);
}

//ゲームシーン音源設定
void SoundController::RegisterGameSound()
{
	m_bgm_file = "Res/wav/BGM/Game.wav";
	m_select_file = "Res/wav/SE/Select.wav";
	m_shot_file = "Res/wav/SE/Shot.wav";
	m_reflect_file = "Res/wav/SE/Reflection.wav";
	m_goal_file = "Res/wav/SE/Goal.wav";
	m_stop_file = "Res/wav/SE/Stop.wav";
	m_reset_file= "Res/wav/SE/Reset.wav";

	AudioPlayer::Instance()->LoadAudioFail(m_bgm, m_bgm_file);
	AudioPlayer::Instance()->LoadAudioFail(m_select_se, m_select_file);
	AudioPlayer::Instance()->LoadAudioFail(m_shot_se, m_shot_file);
	AudioPlayer::Instance()->LoadAudioFail(m_reflect_se, m_reflect_file);
	AudioPlayer::Instance()->LoadAudioFail(m_goal_se, m_goal_file);
	AudioPlayer::Instance()->LoadAudioFail(m_stop_se, m_stop_file);
	AudioPlayer::Instance()->LoadAudioFail(m_reset_se, m_reset_file);
}

//リザルト(エンド)シーン音源設定
void SoundController::RegisterResultSound()
{
	m_bgm_file = "Res/wav/BGM/Result.wav";

	AudioPlayer::Instance()->LoadAudioFail(m_bgm, m_bgm_file);
}

//BGM再生関数
void SoundController::SoundBGM(int volume_)
{
	AudioPlayer::Instance()->Play(m_bgm, volume_, true);
}

//SE停止関数
void SoundController::StopSE(PlaySEType se_type_)
{
	switch (se_type_)
	{
	case PlaySEType::Selsect:
		AudioPlayer::Instance()->Stop(m_select_se);
		break;
	case PlaySEType::Shot:
		AudioPlayer::Instance()->Stop(m_shot_se);
		break;
	case PlaySEType::Reflect:
		AudioPlayer::Instance()->Stop(m_reflect_se);
		break;
	case PlaySEType::Goal:
		AudioPlayer::Instance()->Stop(m_goal_se);
		break;
	case PlaySEType::Stop:
		AudioPlayer::Instance()->Stop(m_stop_se);
		break;
	case PlaySEType::Reset:
		AudioPlayer::Instance()->Stop(m_reset_se);
		break;
	default:
		break;
	}
}

//選択SE音再生関数
void SoundController::SoundSelectSE()
{
	if (m_is_select == false)
	{
		AudioPlayer::Instance()->Play(m_select_se, SoundVolumeMin, false);
		m_is_select = true;
	}
}

//SE音再生関数
void SoundController::PlaySoundSE(PlaySEType se_type_)
{
	switch (se_type_)
	{
	case PlaySEType::Selsect:
		if (m_is_select == false)
		{
			AudioPlayer::Instance()->Play(m_select_se, SoundVolumeMax, false);
			m_is_select = true;
		}
		break;
	case PlaySEType::Shot:
		AudioPlayer::Instance()->Play(m_shot_se, SoundVolumeMax, false);
		break;
	case PlaySEType::Reflect:
		AudioPlayer::Instance()->Play(m_reflect_se, SoundVolumeMax, false);
		break;
	case PlaySEType::Goal:
		AudioPlayer::Instance()->Play(m_goal_se, SoundVolumeMax, false);
		break;
	case PlaySEType::Stop:
		if (m_is_stop == false)
		{
			AudioPlayer::Instance()->Play(m_stop_se, SoundVolumeMax, false);
			m_is_stop = true;
		}
		break;
	case PlaySEType::Reset:
		AudioPlayer::Instance()->Play(m_reset_se, SoundVolumeMax, false);
		break;
	default:
		break;
	}
}

//選択SEリセット関数
void SoundController::ResetSelectFlag()
{
	m_is_select = false;
}

//ストップSEリセット関数
void SoundController::ResetStopFlag()
{
	m_is_stop = false;
}

//タイトルシーンサウンド解放関数
void SoundController::ReleaseTitleSound()
{
	AudioPlayer::Instance()->Release(m_bgm);
	AudioPlayer::Instance()->Release(m_select_se);
}

//ゲームシーンサウンド解放関数
void SoundController::ReleaseGameSound()
{
	AudioPlayer::Instance()->Release(m_bgm);
	AudioPlayer::Instance()->Release(m_select_se);
	AudioPlayer::Instance()->Release(m_shot_file);
	AudioPlayer::Instance()->Release(m_reflect_file);
	AudioPlayer::Instance()->Release(m_goal_file);
	AudioPlayer::Instance()->Release(m_stop_file);
	AudioPlayer::Instance()->Release(m_reset_file);
}

//エンド(リザルト)シーンサウンド解放関数
void SoundController::ReleaseReselutSound()
{
	AudioPlayer::Instance()->Release(m_bgm);
}

//Instance解放関数(Debug用)
void SoundController::ReleaseInstance()
{
	delete mp_instance;
	mp_instance = nullptr;
}

