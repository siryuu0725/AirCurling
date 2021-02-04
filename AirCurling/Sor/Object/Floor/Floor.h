#ifndef FLOOR_H_
#define FLOOR_H_
#include "../ObjectBase.h"

/**
*@clss   ステージ床クラス
*/

class Floor :public ObjectBase
{
public:
	Floor() {}
	~Floor() {}

	/**
	 * @brief  初期化関数
	 * @param (stage_id_) 選択ステージ名(例"Stage1")
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_id_);

	/**
	 * @brief  描画情報送信関数
	 */
	void SetUpBuffer();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_floor_info; }

private:
	ObjectInfo m_floor_info;  //!ステージ床情報

	//!外部データ保存用構造体
	struct ObjectInfoCopy
	{
		//!座標
		float pos_x;   
		float pos_y;  
		float pos_z;  

		//!サイズ
		float scale_x;
		float scale_y;
		float scale_z;

		//!回転角度
		float rote_x; 
		float rote_y; 
		float rote_z; 

		float width;  //!横幅
		float height; //!縦幅


	}m_floor_info_copy;
};


#endif