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
CSV* CSV::p_instance = 0;

CSV* CSV::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new CSV;
	}

	return p_instance;
}

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

void CSV::LoadData(std::string str_)
{
	std::ifstream ifs(str_.c_str(), std::ios_base::in);

	if (ifs.fail() == false)
	{
		std::string str;
		while (getline(ifs, str))
		{
			ifs >> str;

			std::vector<std::string> strvec = Split(str, ',');

			if (strvec.empty() == false)
			{
				std::string key_name = strvec[0];
				auto itr = character_param.find(key_name);
				if (itr != character_param.end())
				{
					// キーが設定されている場合
					//要素をいったん消してからpush_back
					character_param.erase(key_name);
					for (int i = 1; i < strvec.size(); ++i)
					{
						character_param[key_name].push_back(strvec[i]);
					}
				}
				else {
					// キーが設定されていない場合
					for (int i = 1; i < strvec.size(); ++i)
					{
						character_param[key_name].push_back(strvec[i]);
					}
				}
			}
		}

		ifs.close();
	}
}

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