/**
* Class: Vector2D
* @author: Dennis Zinzi (130301136)
*
* Description: Implementation of a 2D vector object
*/

#include "Vector2D.h"


/**
* Default constructor of a Vector2D object
*/
Vector2D::Vector2D(){
	x = 0.0f;
	y = 0.0f;
}


/**
* Constructor of a Vector2D object with component values being assigned
*
* @param x: value of x component of the Vector3D object
* @param y: value of y component of the Vector3D object
*/
Vector2D::Vector2D(float x, float y){
	this->x = x;
	this->y = y;
}


/**
* Constructor of a Vector2D object from a Vector3D (strips z away)
*
* @param v: Vector3D object to convert from
*/
Vector2D::Vector2D(const Vector3D &v){
	x = v.getX();
	y = v.getY();
}

/**
* Copy Constructor
*
* @param copy: reference to Vector2D to copy values from
*/
Vector2D::Vector2D(const Vector2D& copy){
	this->copy(copy);
}


/**
* Destructor of Vector2D object (empty as all internal variables stored on stack)
*/
Vector2D::~Vector2D(){
}


/**
* Returns the magnitude value of a Vector3D object
*
* @return: the magnitude of the Vector3D as a float
*/
float Vector2D::magnitude() const{
	return sqrt((pow(x, 2) + pow(y, 2)));
}


/**
* Generates a Vector2D unit vector from the current Vector2D object
*
* @return: Vector2D with a magnitude of 1 pointing in the same direction as current object
*/
Vector2D Vector2D::makeUnitVector2D() const{
	//Store the magnitude of this Vector3D
	float mag = magnitude();

	//If magnitude is 0 return default Vector3D
	if(mag == 0.0f){
		return Vector2D();
	}
	//If magnitude is one, return copy of current Vector3D 
	else if(mag == 1.0f){
		return Vector2D(*this);
	}

	//Calculate each component of unit vector
	float xU = x / mag,
		yU = y / mag;

	return Vector2D(xU, yU);
}


///**
//* Creates a unit Vector2D orthogonal to the current Vector2D and another one
//*
//* @param v: reference to Vector2D to calculate orthogonal unit vector with
//*
//* @return: orthogonal unit vector made by current Vector2D object and Vector2D specified in parameter
//*/
//Vector2D Vector2D::findOrthagonalUnitVector(const Vector2D &v) const{
//	//Calculate vector/cross product of two Vector3Ds
//	Vector2D crossProd = *this % v;
//
//	//Get unit Vector3D from crossProd Vector3D
//	return crossProd.makeUnitVector2D();
//}


float Vector2D::getVector2DDirection() const{
	return 0.0f;
}


/**
* Operator overloading of '+' to allow addition of two Vector2Ds
*
* @param v: reference to Vector2D to add with current object
*
* @return: Vector2D sum of current object and addend in parameter
*/
Vector2D Vector2D::operator+(const Vector2D &v) const{
	//Calculate sum of each component of the two Vector3Ds
	float xSum = x + v.getX(),
		ySum = y + v.getY();

	return Vector2D(xSum, ySum);
}


/**
* Operator overloading of '-' to allow subtraction of two Vector2Ds
*
* @param v: reference to Vector2D to subract from current Vector2D
*
* @return: Vector2D difference of current object with Vector2D in parameter
*/
Vector2D Vector2D::operator-(const Vector2D &v) const{
	//Calculate difference of each component of the two Vector3Ds
	float xDiff = x - v.getX(),
		yDiff = y - v.getY();

	return Vector2D(xDiff, yDiff);
}


/**
* Operator overloading of '*' to allow multiplication of a Vector2D by a scalar/float
*
* @param s: scalar/factor to multiply current Vector2D by
*
* @return: Vector2D made by product of current Vector2D by scalar/float in parameter
*/
Vector2D Vector2D::operator*(const float s) const{
	//Calculate product of each component of the Vector2D by the scalar
	float xMult = x * s,
		yMult = y * s;

	return Vector2D(xMult, yMult);
}


/**
* Operator overloading of '/' to allow division of a Vector2D by a scalar/float
*
* @param s: scalar/factor to divide current Vector2D by
*
* @return: Vector2D made by quotient of current Vector2D by scalar/float in parameter
*/
Vector2D Vector2D::operator/(const float s) const{
	//If divisor is 0 return current Vector2D
	if(s == 0){
		std::cout << "Error: Cannot divide by 0, returning copy of current Vector2D..." << std::endl;
		return Vector2D(*this);
	}
	//Calculate quotient of each component of the Vector2D by the scalar
	float xDiv = x / s,
		yDiv = y / s;

	return Vector2D(xDiv, yDiv);
}


/**
* Operator overloading of '*' to allow calculating scalar/dot product of two Vector3Ds
*
* @param v: reference to Vector3D to calculate scalar/dot with
*
* @return: scalar/dot product of two Vector3Ds
*/
//float Vector2D::operator*(const Vector2D &v) const{
float Vector2D::dotProduct(const Vector2D &v1, const Vector2D &v2){
	//Calculate product of each component of the two Vector3Ds
	float xProd = v1.getX() * v2.getX(),
		yProd = v1.getY() * v2.getY();

	return xProd + yProd;
}


///**
//* Operator overloading of '%' to allow calculating vector/cross product of two Vector2Ds
//*
//* @param v: reference to Vector2D to calculate vector/cross with
//*
//* @return: Vector2D made by vector/cross product of two Vector2Ds
//*/
//Vector2D Vector2D::operator%(const Vector2D &v) const{
//	//Formula for vector/cross product adapted from: https://www.mathsisfun.com/algebra/vectors-cross-product.html
//	//Calculate each components' vector/cross product value
//	float x = (getY() * v.getZ()) - (getZ() * v.getY()),
//		y = (getZ() * v.getX()) - (getX() * v.getZ()),
//		z = (getX() * v.getY()) - (getY() * v.getX());
//
//	return Vector3D(x, y, z);
//}


/**
* Operator overloading of '='/assignment operator
*
* @param copy: reference to Vector2D to copy values from
*
* @return: reference to Vector2D copied over
*/
Vector2D& Vector2D::operator=(const Vector2D& copy){
	//Check if copied Vector2D is equivalent to current object
	if(this == &copy){
		//If same object, return itself
		return *this;
	}

	//If different Vector2D, copy values across
	this->copy(copy);
	//Return modified Vector2D
	return *this;
}


/**
* Operator overloading of '+=' operator
*
* @param copy: reference to Vector3D to add values from
*
* @return: reference to Vector3D modified
*/
Vector2D& Vector2D::operator+=(const Vector2D &v){
	//Add to each component of the Vector2D the respective component in v
	x += v.getX();
	y += v.getY();

	//Return (modified) current object 
	return *this;
}


/**
* Operator overloading of '-=' operator
*
* @param copy: reference to Vector3D to subtract values from
*
* @return: reference to Vector3D modified
*/
Vector2D& Vector2D::operator-=(const Vector2D &v){
	//Subtract from each component of the Vector2D the respective component in v
	x -= v.getX();
	y -= v.getY();

	//Return (modified) current object 
	return *this;
}


/**
* Operator overloading of '*=' operator
*
* @param copy: reference to Vector2D to multiply values from
*
* @return: reference to Vector2D modified
*/
Vector2D& Vector2D::operator*=(const float s){
	//Multiply each component of the Vector2D by s
	x *= s;
	y *= s;

	//Return (modified) current object 
	return *this;
}


/**
* Operator overloading of '/=' operator
*
* @param copy: reference to Vector2D to divide values from
*
* @return: reference to Vector2D modified
*/
Vector2D& Vector2D::operator/=(const float s){
	//If divisor is 0 return current Vector3D
	if(s == 0){
		std::cout << "Error: Cannot divide by 0, returning current Vector2D..." << std::endl;
		return *this;
	}

	//Divide each component of the Vector2D by s
	x /= s;
	y /= s;

	//Return (modified) current object 
	return *this;
}


/**
* Operator overloading of '=='/comparison operator
*
* @param v: reference to Vector2D to compare
*
* @return: true if objects have same component values, false if any are different
*/
bool Vector2D::operator==(const Vector2D &v) const{
	//Check if Vector2D being compared is the current object
	if(this == &v){
		//If same object, return true
		return true;
	}

	//Check if two Vector2D have same size, if not must be different
	if(magnitude() != v.magnitude()){
		return false;
	}

	//Compare each component coordinates
	if((x == v.getX()) && (y == v.getY())){
		return true;
	}

	return false;
}


/**
* Operator overloading of '!=' operator
*
* @param v: reference to Vector2D to compare
*
* @return: false if objects have same component values, true if any are different
*/
bool Vector2D::operator!=(const Vector2D &v) const{
	//Negate == operator result
	return !(operator==(v));
}


/**
* Operator overloading of '<' operator
*
* @param v: reference to Vector2D to compare
*
* @return: true current object's magnitude smaller than v's magnitude, false otherwise
*/
bool Vector2D::operator<(const Vector2D &v) const{
	//Check if Vector2D being compared is the current object
	if(this == &v){
		//If same object, return false
		return false;
	}

	return magnitude() < v.magnitude() ? true : false;
}


/**
* Operator overloading of '<=' operator
*
* @param v: reference to Vector2D to compare
*
* @return: true current object's magnitude smaller than OR equal to v's magnitude, false otherwise
*/
bool Vector2D::operator<=(const Vector2D &v) const{
	return operator==(v) || operator<(v);
}


/**
* Operator overloading of '>' operator
*
* @param v: reference to Vector2D to compare
*
* @return: true current object's magnitude greater than v's magnitude, false otherwise
*/
bool Vector2D::operator>(const Vector2D &v) const{
	//Check if Vector3D being compared is the current object
	if(this == &v){
		//If same object, return false
		return false;
	}

	return magnitude() > v.magnitude() ? true : false;
}


/**
* Operator overloading of '>=' operator
*
* @param v: reference to Vector2D to compare
*
* @return: true current object's magnitude greater than OR equal to v's magnitude, false otherwise
*/
bool Vector2D::operator>=(const Vector2D &v) const{
	return operator==(v) || operator>(v);
}






Vector2D Vector2D::operator*(const Vector2D &v) const{
	float xProd = x * v.getX(),
		yProd = y * v.getY();

	return Vector2D(xProd, yProd);
}

float Vector2D::dist(const Vector2D &v1, const Vector2D &v2){
	float dX = v2.getX() - v1.getX(),
		dY = v2.getY() - v1.getY();

	return sqrtf((dX*dX) + (dY*dY));
}







/**
* Copies content from specified Vector2D object into current object
*
* @param copy: reference to Vector2D to copy values from
*/
void Vector2D::copy(const Vector2D &copy){
	//Update components value equal to copy's values
	this->x = copy.x;
	this->y = copy.y;
}



/**
* Operator overloading of '>>' operator of the input stream class to accept Vector2Ds
*
* @param inStream: reference to input stream
* @param v: reference to the Vector2D object to write values into
*
* @return: reference to input stream
*/
std::istream& operator>> (std::istream &inStream, Vector2D &v){
	//Values to assign the input into in order to create a Vector2D
	float x, y;
	//Any character the user uses to separate Vector2D components
	char separator;

	inStream >> x >> separator >> y;

	//Create Vector2D from input stream
	v = Vector2D(x, y);
	return inStream;
}


/**
* Operator overloading of '<<' operator of the output stream class to accept Vector2Ds
*
* @param outStream: reference to output stream
* @param v: reference to Vector2D to output
*
* @return: reference to output stream
*/
std::ostream& operator<< (std::ostream &outStream, const Vector2D &v){
	outStream << '(' << v.getX() << ',' << v.getY() << ')';
	return outStream;
}