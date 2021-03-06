﻿/**
 * @file RankingData.h
 * @brief ランキング保存用csvファイル管理
 * @details 中身：CSVファイル取り扱いクラス
**/
#ifndef RANKINGDATA_H_
#define RANKINGDATA_H_
#include "../Utility/Calculation.h"
#include <string>
#include <vector>
#include <map>

/**
* ランキングデータクラス
*/
class RankingData 
{
public:
	RankingData() {}
	~RankingData() {}

	static RankingData* Instance();

	/**
     *	@brief ファイル読み込み関数
     *	@param[in] str_		string型の文字列を入れる
     *	@param[in] string_	vector型を返す(string型を格納して)
     */
	std::vector<std::string>* LoadFile(std::string str_);

	/**
	*	@brief データ書き込み関数
	*	@param[in] str_    string型の文字列を入れる
	*	@param[in] string_ vector型を返す(string型を格納して)
	*	※今はランキングしか考えていないので、上位3位までを書き込むようにしている
	*/
	void WriteData(std::string str_, std::vector<__int16> strvec_);

	/**
	*	@brief Instance解放関数(Debug用)
	*	@details 手動でインスタンスを解放する
	*/
	void ReleaseInstance();

private:
	/**
	*	@brief コンマ区切りで文字列を分割する関数
	*	@param[in] str_	string型の文字列を入れる
	*	@param[in] delimiter_ 区切りたい文字を入れる
	*	@return	vector型を返す(string型を格納して)
	*/
	std::vector<std::string> Split(std::string& str_, char delimiter_);

private:
	static RankingData* mp_instance;

	std::vector<std::string> m_ranking_data; 

	std::map < std::string, std::vector<std::string> > character_param;

};

#endif