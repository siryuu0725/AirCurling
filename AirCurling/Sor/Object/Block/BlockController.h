#ifndef BLOCK_CONTROLLER_H_
#define BLOCK_CONTROLLER_H_
#include "CircleBlock.h"
#include "RectBlock.h"
#include "../../System/FBXController.h"
#include <vector>

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
	std::vector<CircleBlock*> m_circle_block;  //!円型ブロック
	std::vector<RectBlock*> m_rect_block;	   //!矩形ブロック

	std::vector<Shape*> m_rect_shape;    //!矩形情報保存用
	std::vector<Shape*> m_circleshape;	 //!円形型情報保存用

	int m_rectblock_num;    //!矩形ブロックデータ数
	int m_circleblock_num;  //!円型ブロック

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

	CircleBlockInfoCopy circleblock_info_copy[20];
	RectBlockInfoCopy rectblock_info_copy[20];
};


#endif