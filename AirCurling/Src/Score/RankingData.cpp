#include "RankingData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


RankingData* RankingData::mp_instance = nullptr;

RankingData* RankingData::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new RankingData; }

	return mp_instance;
}

//ファイル読み込み関数
std::vector<std::string>* RankingData::LoadFile(std::string str_)
{
	std::ifstream ifs(str_.c_str(), std::ios_base::in);

	if (ifs.fail())
	{
		return nullptr;
	}

	std::string str;

	ifs >> str;
	m_ranking_data = Split(str, ',');

	ifs.close();

	return &m_ranking_data;
}

//データ書き込み関数
void RankingData::WriteData(std::string str_, std::vector<__int16> strvec_)
{
	std::ofstream ofs(str_, std::ios_base::out);

	if (ofs.fail() == false)
	{
		std::vector<std::string> ranking;

		for (int i = 0; i < strvec_.size() - 1; i++)
		{
			ranking.push_back(std::to_string(strvec_[i]));
		}
		//ranking = m_calculation.FixTheMinute(score_table);

		ofs << ranking[0] << ','
			<< ranking[1] << ','
			<< ranking[2]
			<< std::endl;

		ofs.close();
	}

}

//コンマ区切りで文字列を分割する関数
std::vector<std::string> RankingData::Split(std::string& input_, char delimiter_)
{
	std::istringstream stream(input_);
	std::string field;
	std::vector<std::string> result;
	while (getline(stream, field, delimiter_))
	{
		result.push_back(field);
	}

	return result;
}

//Instance解放関数(Debug用)
void RankingData::ReleaseInstance()
{
	delete mp_instance;
	mp_instance = nullptr;
}