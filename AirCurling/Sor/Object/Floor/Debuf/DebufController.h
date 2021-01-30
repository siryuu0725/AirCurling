#ifndef DEBUF_CONTROLLER_H_
#define DEBUF_CONTROLLER_H_
#include "ResetFloor.h"
#include "StopFloor.h"
#include <vector>

/**
*@clss   デバフ床管理クラス
*@brief  各デバフの床の処理を管理する
*/

class DebufController
{
public:
	DebufController() {}
	~DebufController();


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
	* @brief  各デバフ床情報Getter関数
	* @return 各デバフ床の座標、サイズの情報を返す
	*/
	const std::vector<Shape*>* GetResetShape()const { return &m_reset_shape; }
	const std::vector<Shape*>* GetStopShape()const { return &m_stop_shape; }

private:
	std::vector<ResetFloor*> m_reset_floor;  //!リセット床情報保存用
	std::vector<StopFloor*> m_stop_floor;	 //!スピード減衰床情報保存用

	std::vector<Shape*> m_reset_shape;  //!リセット床情報保存用
	std::vector<Shape*> m_stop_shape;   //!スピード減衰床情報保存用

	int m_resetfloor_num;  //!リセット床数
	int m_stopfloor_num;   //!スピード減衰床数

	//!外部データ保存用構造体(リセット床)
	struct ResetFloorInfoCopy
	{
		//!座標
		float pos_x;   
		float pos_y;   
		float pos_z;   

		//!サイズ
		float scale_x; 
		float scale_y; 
		float scale_z; 

		float radius; //!半径
	};

	//!外部データ保存用構造体(スピード減衰床)
	struct StopFloorInfoCopy
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
	};

	//!外部データ保存用
	ResetFloorInfoCopy m_resetfloor_info_copy[5];  //!リセット床
	StopFloorInfoCopy m_stopfloor_info_copy[5];    //!スピード減衰床

};


#endif