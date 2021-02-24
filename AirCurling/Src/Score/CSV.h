#ifndef CSV_H_
#define CSV_H_
#include "../Utility/Calculation.h"
#include <string>
#include <vector>
#include <map>

enum class RANK
{
	FIRST,
	SECOND,
	THIRD,

	MAX
};

/**
*@class  CSVファイル取り扱いクラス
*/

class CSV 
{
private:
	CSV() {}
	~CSV() {}

	CSV(const CSV&);
	CSV& operator=(const CSV&) = delete;

	CSV& operator=(const CSV&&) = delete;
public:
	static CSV* Instance();
	/**
	*	@brief<Get> 指定されたキーの中のパラメータ取得する関数
	*	@param[in] key_ keyの名前を入れる
	*	@return	キーの中の値を返す
	*/
	std::vector<std::string>* GetParam(std::string key_)
	{
		std::map<std::string, std::vector<std::string>>::iterator itr = character_param.find(key_);
		if (itr == character_param.end())
		{
			return nullptr;
		}

		return &character_param[key_];
	}

	/**
     *	@brief csv(txt)     ファイル読み込み関数
     *	@param[in] str_		string型の文字列を入れる
     *	@param[in] string_	vector型を返す(string型を格納して)
     */
	std::vector<std::string>* LoadFile(std::string str_);

	/**
	*	@brief csv(txt) データ書き込み関数
	*	@param(str_)    string型の文字列を入れる
	*	@param(string_)	vector型を返す(string型を格納して)
	*	※今はランキングしか考えていないので、上位3位までを書き込むようにしている
	*/
	void WriteData(std::string str_, std::vector<__int16> strvec_);

private:
	/**
	*	@brief コンマ区切りで文字列を分割する関数
	*	@param(str_)		string型の文字列を入れる
	*	@param(delimiter_)	区切りたい文字を入れる
	*	@return	vector型を返す(string型を格納して)
	*/
	std::vector<std::string> Split(std::string& str_, char delimiter_);

private:
	static CSV* p_instance;

	std::vector<std::string> m_ranking_data;

	std::map < std::string, std::vector<std::string> > character_param;

};

#endif