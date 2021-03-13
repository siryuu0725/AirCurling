/**
 * @file DirectSound.h
 * @brief DXサウンドを管理する
 * @details 中身：DXサウンドクラス
**/
#ifndef DIRECTSOUND_H_
#define DIRECTSOUND_H_
#include <dsound.h>
#include <string>

/**
* DXサウンドクラス
*/
class DirectSound {

public:


	DirectSound(HWND hwnd_ = nullptr);

	/**
	 * @brief  ファイル読み込み書き出し関数
	 * @param[in] file_name_ ファイルパス
	 * @param[in] alias_ サウンドを使用する際の別名
	 * @details wavファイルの書き出しを行い、データを返す
	 */
	IDirectSoundBuffer8* LoadWaveFile(std::string file_name_);

	~DirectSound();

private:

	IDirectSound8* m_DSound8;			 //!サウンドインターフェース
	IDirectSoundBuffer8* m_SecBuffer;
};

#endif
