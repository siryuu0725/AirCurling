#include "SoundController.h"

SoundController* SoundController::mp_instance = nullptr;

SoundController* SoundController::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new SoundController; }

	return mp_instance;
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
	mp_audio->LoadAudioFail(m_bgm, m_bgm_file);
	mp_audio->LoadAudioFail(m_select_se, m_select_file);
}

//ゲームシーン音源設定
void SoundController::RegisterGameSound()
{
	m_bgm_file = "Res/wav/BGM/Game.wav";
	m_shot_file = "Res/wav/SE/Shot.wav";
	m_reflect_file = "Res/wav/SE/Reflection.wav";
	m_goal_file = "Res/wav/SE/Goal.wav";
	m_stop_file = "Res/wav/SE/Stop.wav";
	m_reset_file= "Res/wav/SE/Reset.wav";

	mp_audio->LoadAudioFail(m_bgm, m_bgm_file);
	mp_audio->LoadAudioFail(m_shot_se, m_shot_file);
	mp_audio->LoadAudioFail(m_reflect_se, m_reflect_file);
	mp_audio->LoadAudioFail(m_goal_se, m_goal_file);
	mp_audio->LoadAudioFail(m_stop_se, m_stop_file);
	mp_audio->LoadAudioFail(m_reset_se, m_reset_file);
}

//リザルト(エンド)シーン音源設定
void SoundController::RegisterResultSound()
{
	m_bgm_file = "Res/wav/BGM/Result.wav";

	mp_audio->LoadAudioFail(m_bgm, m_bgm_file);
}

//BGM再生関数
void SoundController::SoundBGM(int volume_)
{
	mp_audio->Play(m_bgm, volume_, true);
}

//選択SE音再生関数
void SoundController::SoundSelectSE()
{
	if (m_is_select == false)
	{
		mp_audio->Play(m_select_se, SoundVolumeMin, false);
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
			mp_audio->Play(m_select_se, SoundVolumeMax, false);
			m_is_select = true;
		}
		break;
	case PlaySEType::Shot:
		mp_audio->Play(m_shot_se, SoundVolumeMax, false);
		break;
	case PlaySEType::Reflect:
		mp_audio->Play(m_reflect_se, SoundVolumeMax, false);
		break;
	case PlaySEType::Goal:
		mp_audio->Play(m_goal_se, SoundVolumeMax, false);
		break;
	case PlaySEType::Stop:
		if (m_is_stop == false)
		{
			mp_audio->Play(m_stop_se, SoundVolumeMax, false);
			m_is_stop = true;
		}
		break;
	case PlaySEType::Reset:
		mp_audio->Play(m_reset_se, SoundVolumeMax, false);
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
	mp_audio->Release(m_bgm);
	mp_audio->Release(m_select_se);

}

//ゲームシーンサウンド解放関数
void SoundController::ReleaseGameSound()
{
	mp_audio->Release(m_bgm);
}

//エンド(リザルト)シーンサウンド解放関数
void SoundController::ReleaseReselutSound()
{
	mp_audio->Release(m_bgm);
}

