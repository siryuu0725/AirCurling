#ifndef BLOCK_CONTROLLER_H_
#define BLOCK_CONTROLLER_H_
#include "CircleBlock.h"
#include "RectBlock.h"
#include "../../System/FBXController.h"
#include <vector>

//!ステージに置ける最大ブロック数 
#define RECTBLOCK_MAX_NUM 20   
#define CIRCLEBLOCK_MAX_NUM 20 

/**
*@clss   ブロック管理クラス
*@brief  各ブロックの処理を管理する
*/
class BlockController
{
public:
	BlockController() {}
	~BlockController();

	/**
	 * @brief  初期化関数
	 * @param (stage_id_) 選択ステージ名(例"Stage1")
	 * @detail 各ブロックのメンバ変数初期化
	 */
	void Init(std::string stage_id_);


	/**
     * @brief  描画情報送信関数
     */
	void SetUpBuffer();

	/**
	 * @brief  各ブロック情報Getter関数
	 * @return 各ブロック座標、サイズの情報を返す
	 */
	const std::vector<Shape*>* GetRectShape()const { return &m_rect_shape; }
	const std::vector<Shape*>* GetCircleShape()const { return &m_circleshape; }

private:
	std::vector<CircleBlock*> m_circle_block;  //!円形ブロック
	std::vector<RectBlock*> m_rect_block;	   //!矩形ブロック

	std::vector<Shape*> m_rect_shape;    //!矩形情報保存用(当たり判定用)
	std::vector<Shape*> m_circleshape;	 //!円形情報保存用(当たり判定用)

	int m_rectblock_num;    //!矩形ブロックデータ数
	int m_circleblock_num;  //!円形ブロックデータ数

	//!外部データ保存用構造体(矩形ブロック)
	struct RectBlockInfoCopy
	{
		//!座標
		float pos_x;   
		float pos_y; 
		float pos_z; 

		//!サイズ
		float scale_x; 
		float scale_y; //!サイズ
		float scale_z; //!サイズ

		//!回転角度
		float rote_x; 
		float rote_y; 
		float rote_z; 

		float width;  //!横幅
		float height; //!縦幅
	};

	//!外部データ保存用構造体(円形ブロック)
	struct CircleBlockInfoCopy
	{
		//!座標
		float pos_x;   
		float pos_y;  
		float pos_z; 

		//!サイズ
		float scale_x; 
		float scale_y; 
		float scale_z; 

		//!半径
		float radius;

	};

	//!外部データ保存用
	CircleBlockInfoCopy m_circleblock_info_copy[CIRCLEBLOCK_MAX_NUM]; //!円形ブロック
	RectBlockInfoCopy m_rectblock_info_copy[RECTBLOCK_MAX_NUM];	 //!矩形ブロック
};


#endif