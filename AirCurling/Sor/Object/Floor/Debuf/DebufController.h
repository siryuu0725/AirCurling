#ifndef DEBUF_CONTROLLER_H_
#define DEBUF_CONTROLLER_H_
#include "ResetFloor.h"
#include "StopFloor.h"
#include <vector>

#define RESET_FLOOR_NUM 2   //!リセット床数
#define STOP_FLOOR_NUM 1    //!スピード減衰床数

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
	std::vector<ResetFloor*> m_reset_floor;    //!矩形型情報保存用
	std::vector<StopFloor*> m_stop_floor;	 //!円形型情報保存用

	std::vector<Shape*> m_reset_shape;    //!矩形型情報保存用
	std::vector<Shape*> m_stop_shape;	 //!円形型情報保存用

	int m_resetfloor_num;
	int m_stopfloor_num;


	struct ResetFloorInfoCopy
	{
		float pos_x;   //!座標
		float pos_y;   //!座標
		float pos_z;   //!座標

		float scale_x; //!サイズ
		float scale_y; //!サイズ
		float scale_z; //!サイズ

		float radius;
	};

	struct StopFloorInfoCopy
	{
		float pos_x;   //!座標
		float pos_y;   //!座標
		float pos_z;   //!座標

		float scale_x; //!サイズ
		float scale_y; //!サイズ
		float scale_z; //!サイズ

		float rote_x; //!サイズ
		float rote_y; //!サイズ
		float rote_z; //!サイズ

		float width;
		float height;
	};


	ResetFloorInfoCopy resetfloor_info_copy[5];
	StopFloorInfoCopy stopfloor_info_copy[5];

};


#endif