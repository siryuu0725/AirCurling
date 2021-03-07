#include "CSV.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

//int CSV::CreateFile_()
//{
//	const char* fileName = "test.txt";
//	std::ofstream ofs(fileName);
//	if (!ofs)
//	{
//		std::cout << "ファイルが開けませんでした。" << std::endl;
//		std::cin.get();
//		return 0;
//	}
//	ofs << "player\n" << std::endl;       // 題名とかがいいかも
//	std::cout << fileName << "に書き込みました。" << std::endl;
//	std::cin.get();
//}
CSV* CSV::mp_instance = nullptr;

CSV* CSV::Instance()
{
	if (mp_instance == nullptr) { mp_instance = new CSV; }

	return mp_instance;
}

//ファイル読み込み関数
std::vector<std::string>* CSV::LoadFile(std::string str_)
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
void CSV::WriteData(std::string str_, std::vector<__int16> strvec_)
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
std::vector<std::string> CSV::Split(std::string& input_, char delimiter_)
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