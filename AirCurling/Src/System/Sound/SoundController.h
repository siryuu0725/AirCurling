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

enum class PlaySEType
{
	Selsect,
	Shot,
	Reflect,
	Goal,
	Stop,
	Reset
};


/**
* サウンド管理クラス
*/

class SoundController
{
private:
	SoundController();
	~SoundController() {}

public:
	static SoundController* Instance();

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
	*	@brief SE停止関数
	*	@details SEの停止
	*/
	void StopSE(PlaySEType se_type_);

	/**
	*	@brief 選択SE音再生関数
	*	@details 選択SE音の再生
	*/
	void SoundSelectSE();

	/**
	*	@brief SE音再生関数
	*   @param[in] se_type_ 鳴らしたいSEの種類
	*	@details 落下時のSE音の再生
	*/
	void PlaySoundSE(PlaySEType se_type_);

	/**
	*	@brief 選択SEリセット関数
	*	@details 選択SEをもう一度流れるようにする
	*/
	void ResetSelectFlag();

	/**
	*	@brief ストップSEリセット関数
	*	@details StopSEをもう一度流れるようにする
	*/
	void ResetStopFlag();

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
	static SoundController* mp_instance;


	// 使用する際の変数名(音ごとに必要)
	std::string m_bgm;          //!BGM用(各シーン使い回し)
	std::string m_select_se;    //!選択時SE
	std::string m_shot_se;      //!打った時のSE
	std::string m_reflect_se;	//!反射SE
	std::string m_goal_se;	    //!ゴールSE
	std::string m_stop_se;      //!スピード減衰時SE
	std::string m_reset_se;	    //!落下時SE



	// flie読み込み用変数(音ごとに必要)
	std::string m_bgm_file;       //!BGMファイルパス保存用
	std::string m_select_file;	  //!選択時SEファイルパス保存用
	std::string m_shot_file;	  //!打った時のSEファイルパス保存用
	std::string m_reflect_file;	  //!反射SEファイルパス保存用
	std::string m_goal_file;	  //!ゴールSEファイルパス保存用
	std::string m_stop_file;      //!スピード減衰時SEファイルパス保存用
	std::string m_reset_file;	  //!落下時SEファイルパス保存用

	AudioPlayer* mp_audio = AudioPlayer::GetInstance(GetWindowHandle());

	bool m_is_select;  //!selectSEをループさせないためのフラグ
	bool m_is_stop;    //!stopSEをループさせないためのフラグ


};

#endif

