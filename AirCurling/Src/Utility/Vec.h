#ifndef VEC_H_
#define VEC_H_

struct Vec2
{
	/** Constructor */
	Vec2()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x 横幅
	* @param[in] y 縦幅
	*/
	Vec2(float x, float y)
	{
		X = x;
		Y = y;
	}



	float X;	//!< X値
	float Y;	//!< Y値
};



struct Vec3
{
	/** Constructor */
	Vec3()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x 横幅
	* @param[in] y 縦幅
	*/
	Vec3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}



	float X;	//!< X値
	float Y;	//!< Y値
	float Z;	//!< Z値
};


#endif


