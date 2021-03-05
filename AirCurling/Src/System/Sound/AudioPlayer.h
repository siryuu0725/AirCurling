/**
 * @file AudioPlayer.h
 * @brief サウンドプレーヤー
 * @details 中身：オーディオプレイヤークラス
**/
#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#include "DirectSound.h"
#include "../../System/Window.h"
#include <string>
#include <unordered_map>

/**
* オーディオプレイヤークラス
*/
class AudioPlayer {

public:

	static AudioPlayer* GetInstance(HWND hwnd_ = nullptr) {
		static AudioPlayer instance(hwnd_);
		return &instance;
	}

	
	/**
	 * @brief  ウェブファイル読み込み関数
	 * @param[in] alias_ サウンドを使用する際の別名
	 * @param[in] file_name_ サウンドファイル名
	 * @details 指定されたサウンドファイルを読み込む
	 */
	bool LoadUI(std::string alias_, std::string file_name_);

	/**
	 * @brief  再生処理関数
	 * @param[in] alias_ サウンドを使用する際の別名
	 * @param[in] volumr_ 音量（０で最大　-10000で無音）
	 * @param[in] is_loop_ 再生方法（true=ループ再生）
	 * @details 指定された音量で、第２引数でしていされた再生方法により再生する
	 */
	void Play(std::string alias_, int volume_ = -1000, bool is_loop_ = false);

	/**
	 * @brief  停止処理関数
	 * @param[in] alias_ サウンドを使用する際の別名
	 * @details 呼び出したタイミングで停止させる
	 */
	void Stop(std::string alias_);


	/**
	 * @brief  ボリューム設定関数
	 * @param[in] volume_ 音量（0で最大 -10000で無音）
	 * @param[in] alias_ サウンドを使用する際の別名
	 * @details 呼び出したタイミングで音量を変える
	 */
	void SetVolume(std::string alias_, int volume_);

	/**
	 * @brief  解放関数
	 * @param[in] alias_ サウンドを使用する際の別名
	 */
	void Release(std::string alias_);

private:

	/**
	 * @brief  コンストラクタ
	 */
	AudioPlayer(HWND hwnd_) {
		//再生先のウィンドウハンドルを取得
		m_Sound = new DirectSound(hwnd_);
	}

	/**
	 * @brief  サウンドファイル検索関数
	 * @param[in] alias_  読み込み時に設定したサウンドファイルの別名
	 * @return 成功→サウンドデータ
	 */
	IDirectSoundBuffer8* Find(std::string alias_);

	~AudioPlayer();

private:
	DirectSound* m_Sound;
	std::unordered_map<std::string, IDirectSoundBuffer8*> m_SoundData; //!セカンダリバッファ
	WAVEFORMATEX m_format;			  //!データフォーマット構造体
	DWORD m_size;					  //!waveファイルのサイズ


};



#endif

