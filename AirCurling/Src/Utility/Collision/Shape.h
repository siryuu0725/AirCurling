#ifndef SHAPE_H_
#define SHAPE_H_
#include <d3dx9.h>

/**
*@class  型基底クラス
*/

class Shape
{
public:
	Shape() {}
	~Shape() {}

public:
	virtual D3DXVECTOR3 GetCirclePos()const { return D3DXVECTOR3(); };

	virtual float GetRadius()const { return 0.0f; }

public:
	virtual D3DXVECTOR3 GetBoxPos()const { return D3DXVECTOR3(); };

	virtual float GetWidth()const { return 0.0f; }
	virtual float GetHeight()const { return 0.0f; }
	virtual float GetRote()const { return 0.0f; }
};


/**
*@clss  矩形型クラス
*/

class RectShape : public Shape {
public:
	RectShape(D3DXVECTOR3 pos_, float width_, float height_, float rote_) :
		pos(pos_), width(width_), height(height_), rote(rote_) {}
	~RectShape() {}

	virtual D3DXVECTOR3 GetBoxPos()const override { return pos; }

	virtual float GetWidth()const override { return width; }

	virtual float GetHeight()const override { return height; }

	virtual float GetRote()const override { return rote; }
private:
	D3DXVECTOR3 pos;
	float width, height;

	float rote;
};

/**
*@clss  円型クラス
*/
class CircleShape :public Shape
{
public:
	CircleShape(D3DXVECTOR3 pos_, float radius_) :
		pos(pos_), radius(radius_) {}
	~CircleShape() {}

	virtual D3DXVECTOR3 GetCirclePos()const override { return pos; }

	virtual float GetRadius()const override { return radius; }

private:
	D3DXVECTOR3 pos;
	float radius;
};

#endif