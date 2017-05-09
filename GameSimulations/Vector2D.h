#pragma once

/**
* Class: Vector2D
* @author: Dennis Zinzi (130301136)
*
* Description: Implementation of a 2D vector object
*/

#include "Vector3D.h"
#include <iostream>
#include <cmath>


class Vector2D{
	public:
	//Vector2D constructors
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector3D &v);

	//Copy Constructor
	Vector2D(const Vector2D &copy);

	//Destructor
	~Vector2D();

	/**
	* Getter method for the x component of a Vector2D
	*
	* @return: x component of current object
	*/
	inline float getX() const{
		return x;
	}

	/**
	* Getter method for the y component of a Vector2D
	*
	* @return: y component of current object
	*/
	inline float getY() const{
		return y;
	}

	
	/**
	* Getter method for the x component of a Vector2D
	*
	* @return: x component of current object
	*/
	inline void setX(float x){
		this->x = x;
	}

	/**
	* Getter method for the y component of a Vector2D
	*
	* @return: y component of current object
	*/
	inline void setY(float y){
		this->y = y;
	}

	//Calculate scalar/dot product of two Vector2Ds
	static float dotProduct(const Vector2D &v1, const Vector2D &v2);
	//Calculate distance between two Vector2Ds
	static float distance(const Vector2D &v1, const Vector2D &v2);

	//Vector3D functions
	float magnitude() const;
	Vector2D makeUnitVector2D() const;
	//Vector2D findOrthagonalUnitVector(const Vector2D &v) const;
	float getVector2DDirection() const;

	//Operator overloading operations
	Vector2D operator+(const Vector2D &v) const;
	Vector2D operator-(const Vector2D &v) const;
	Vector2D operator*(const float s) const;
	Vector2D operator/(const float s) const;

	//Operator overload to calculate scalar/dot product of two Vector2Ds
	//float operator*(const Vector2D &v) const;

	//Multiply two Vector2Ds
	Vector2D operator*(const Vector2D &v) const;
	//Operator overload to calculate vector/cross product of two Vector2Ds
	//Vector2D operator%(const Vector2D &v) const;

	//Operator overload of assignment operator
	Vector2D& operator=(const Vector2D &copy);

	//Extra operator overloading operations
	Vector2D& operator+=(const Vector2D &v);
	Vector2D& operator-=(const Vector2D &v);
	Vector2D& operator*=(const float s);
	Vector2D& operator/=(const float s);

	//Comparison operator overloads
	bool operator==(const Vector2D &v) const;
	bool operator!=(const Vector2D &v) const;
	bool operator<(const Vector2D &v) const;
	bool operator<=(const Vector2D &v) const;
	bool operator>(const Vector2D &v) const;
	bool operator>=(const Vector2D &v) const;

	private:
	//Member variables representing each component of a Vector2D
	float x, y;

	//copy function to be used by assingment operator and copy constructor
	void copy(const Vector2D &copy);
};


//Overload input stream >> operator to accept a Vector2D
std::istream& operator>>(std::istream &inStream, Vector2D &v);

//Overload output stream << operator to display a Vector2D
std::ostream& operator<<(std::ostream &outStream, const Vector2D &v);