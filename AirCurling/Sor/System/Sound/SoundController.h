#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_
#include "../Sound/AudioPlayer.h"
#include"../../System/Window.h"
#include <string>


/**
*@clss  サウンド管理クラス
*/

class SoundManager
{
public:
	static SoundManager* Instance();

	// 各シーンごとの音素材登録
	void RegisterTitleSound();		// タイトル
	void RegisterGameSound();	// ゲームメイン
	void RegisterHelpSound();	    // ヘルプ
	void RegisterResultSound();		// ゲームエンド

	// 鳴らす関数※音ごとに関数が必要
	void SoundBGM(int volume_);
	void SoundSelectBGM();
	void SoundSelectSE();
	void SoundCancelSE();
	void SoundClickSE();

	void SoundShotSE();
	void SoundReflectSE();
	void SoundGoalSE();
	void SoundFrictionSE();
	void SoundFallSE();

	//音が鳴り終わったらフラグを元に戻す関数
	void ResetSelectFlag();

	// 解放関数
	void ReleaseTitleSound();
	void ReleaseSelectSound();
	void ReleaseGameSound();
	void ReleaseReselutSound();


protected:
	SoundManager();

private:
	static SoundManager* p_instance;

	// selectSEをループさせないためのフラグ
	bool m_select1_flag;
	bool m_cancel_flag;


	// 使用する際の変数名(音ごとに必要)　※初期化必須
	std::string bgm;
	std::string select1_se;
	std::string cancel_se;
	std::string click_se;

	std::string shot_se;
	std::string reflect_se;
	std::string goal_se;
	std::string friction_se;
	std::string fall_se;



	// flie読み込み用変数(音ごとに必要)
	std::string bgm_file;
	std::string se1_file;
	std::string cancel_file;
	std::string click_se_file;

	std::string shot_file;
	std::string reflect_file;
	std::string goal_file;
	std::string friction_file;
	std::string fall_file;

	AudioPlayer* p_audio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

