#include "AudioPlayer.h"


//==========================================
//  サウンドプレーヤー
//==========================================

bool AudioPlayer::LoadUI(std::string alias, std::string file_name) {

	//まだ読み込んでいないサウンドデータである
	/*
		std::unordered_map.count(value）
		 valueをキーとした要素の検索を行う。
		 要素あり→１　要素なし→０
	*/
	if (m_SoundData.count(alias) == 0) {
		m_SoundData.emplace(alias, m_Sound->LoadWaveFile(file_name));
		return true;
	}
	return false;
}

//------------------------------------
// 再生
void AudioPlayer::Play(
	std::string alias,
	int volume,
	bool is_loop
) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}

	if (is_loop) {
		sound->SetVolume(volume);
		sound->Play(0, 0, DSBPLAY_LOOPING);
	}
	else {
		sound->SetVolume(volume);
		sound->Play(0, 0, 0);
		sound->SetCurrentPosition(0);
	}
}

//----------------------------------
// 停止
void AudioPlayer::Stop(std::string alias) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}
	sound->Stop();
}

//----------------------------------
// ボリューム調整
void AudioPlayer::SetVolume(std::string alias, int volume) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}
	sound->SetVolume(volume);
}

//-------------------------------
//解放処理
void AudioPlayer::Release(std::string alias) {

	IDirectSoundBuffer8* sound = Find(alias);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}

	if (sound) {
		sound->Release();
		sound = nullptr;
		m_SoundData.erase(alias);//要素削除
	}
}

IDirectSoundBuffer8* AudioPlayer::Find(std::string alias) {

	//サウンドデータをキーで検索
	auto data = m_SoundData.find(alias);
	//サウンドデータがみつかった場合
	if (data != m_SoundData.end()) {
		return data->second;
	}
	return nullptr;//見つからなかったのでnullを渡す
}

AudioPlayer::~AudioPlayer() {

	if (m_SoundData.empty()) {
		//要素の削除がすべて完了している場合はクリア
		m_SoundData.clear();
	}
	//解放漏れがある場合
	for (auto data : m_SoundData) {
		IDirectSoundBuffer8* sound = data.second;
		if (sound == nullptr) {
			continue;
		}
		sound->Release();
		//m_SoundData.erase(data.first);
	}
	m_SoundData.clear();

	if (m_Sound) {
		delete m_Sound;
	}
}

