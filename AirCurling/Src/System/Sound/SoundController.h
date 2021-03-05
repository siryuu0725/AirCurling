/**
 * @file SoundManager.h
 * @brief サウンド全体を管理する
 * @details 中身：サウンド管理クラス
**/
#ifndef SOUNDCONTROLLER_H_
#define SOUNDCONTROLLER_H_
#include "../Sound/AudioPlayer.h"
#include"../../System/Window.h"
#include <string>


constexpr __int16 SoundVolumeMax = 0;      //!各音量の最大値
constexpr __int16 SoundVolumeMin = -1000;  //!各音量の最小値


/**
* サウンド管理クラス
*/

class SoundManager
{
private:
	SoundManager();
	~SoundManager() {}

public:
	static SoundManager* Instance();

	/**
	*	@brief タイトルシーン音源設定
	*	@details タイトルシーンで使用する音の設定
	*/
	void RegisterTitleSound();

	/**
	*	@brief ゲームシーン音源設定
	*	@details ゲームシーンで使用する音の設定
	*/
	void RegisterGameSound();	  

	/**
	*	@brief リザルト(エンド)シーン音源設定
	*	@details リザルト(エンド)シーンで使用する音の設定
	*/
	void RegisterResultSound();	

	/**
	*	@brief BGM再生関数
	*　 @param[in] volume_ 音量（0で最大 -10000で無音）
	*	@details BGMの再生
	*/
	void SoundBGM(int volume_);

	/**
	*	@brief 選択SE音再生関数
	*	@details 選択SE音の再生
	*/
	void SoundSelectSE();

	/**
	*	@brief 打った時のSE音再生関数
	*	@details プレイヤーを移動させる時(打った時)のSE音の再生
	*/
	void SoundShotSE();

	/**
	*	@brief 反射SE音再生関数
	*	@details プレイヤーの反射SE音の再生
	*/
	void SoundReflectSE();

	/**
	*	@brief ゴールSE音再生関数
	*	@details ゴール時のSE音の再生
	*/
	void SoundGoalSE();

	/**
	*	@brief スピード減衰時SE音再生関数
	*	@details スピード減衰時SE音の再生
	*/
	void SoundFrictionSE();

	/**
	*	@brief 落下時SE音再生関数
	*	@details 落下時のSE音の再生
	*/
	void SoundFallSE();

	/**
	*	@brief 選択フラグリセット関数
	*	@details 選択音が鳴り終わったらフラグを元に戻す
	*/
	void ResetSelectFlag();

	
	/**
	*	@brief タイトルシーンサウンド解放関数
	*	@details タイトルシーンで使用した音を解放する
	*/
	void ReleaseTitleSound();

    /**
	*	@brief ゲームシーンサウンド解放関数
	*	@details ゲームシーンで使用した音を解放する
	*/
	void ReleaseGameSound();

	/**
    *	@brief エンド(リザルト)シーンサウンド解放関数
    *	@details エンド(リザルト)シーンで使用した音を解放する
    */
	void ReleaseReselutSound();

private:
	static SoundManager* mp_instance;


	// 使用する際の変数名(音ごとに必要)
	std::string bgm;         //!BGM用(各シーン使い回し)
	std::string select1_se;	 //!選択時SE
	std::string shot_se;     //!打った時のSE
	std::string reflect_se;	 //!反射SE
	std::string goal_se;	 //!ゴールSE
	std::string friction_se; //!スピード減衰時SE
	std::string fall_se;	 //!落下時SE



	// flie読み込み用変数(音ごとに必要)
	std::string bgm_file;       //!BGMファイルパス保存用
	std::string se1_file;		//!選択時SEファイルパス保存用
	std::string shot_file;		//!打った時のSEファイルパス保存用
	std::string reflect_file;	//!反射SEファイルパス保存用
	std::string goal_file;		//!ゴールSEファイルパス保存用
	std::string friction_file;	//!スピード減衰時SEファイルパス保存用
	std::string fall_file;		//!落下時SEファイルパス保存用

	AudioPlayer* p_audio = AudioPlayer::GetInstance(GetWindowHandle());

	bool m_select1_flag;  //!selectSEをループさせないためのフラグ

};

#endif

