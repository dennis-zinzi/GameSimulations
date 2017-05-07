/**
 * Class: Vector3D
 * @author: Dennis Zinzi (130301136)
 *
 * Description: Implementation of a 3D vector object
 */

#include "Vector3D.h"


/**
 * Default constructor of a Vector3D object 
 */
Vector3D::Vector3D(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}


/**
 * Constructor of a Vector3D object with component values being assigned
 *
 * @param x: value of x component of the Vector3D object
 * @param y: value of y component of the Vector3D object
 * @param z: value of z component of the Vector3D object
 */
Vector3D::Vector3D(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}


/**
 * Copy Constructor
 *
 * @param copy: reference to Vector3D to copy values from
 */
Vector3D::Vector3D(const Vector3D& copy){
	this->copy(copy);
}


/**
 * Destructor of Vector3D object (empty as all internal variables stored on stack)
 */
Vector3D::~Vector3D(){
}


/**
 * Returns the magnitude value of a Vector3D object
 *
 * @return: the magnitude of the Vector3D as a float
 */
float Vector3D::magnitude() const{
	return sqrt((pow(getX(),2) + pow(getY(),2) + pow(getZ(),2)));
}


/**	
 * Generates a Vector3D unit vector from the current Vector3D object
 *
 * @return: Vector3D with a magnitude of 1 pointing in the same direction as current object
 */
Vector3D Vector3D::makeUnitVector3D() const{
	//Store the magnitude of this Vector3D
	float mag = magnitude();

	//If magnitude is 0 return default Vector3D
	if(mag == 0.0f){
		return Vector3D();
	}
	//If magnitude is one, return copy of current Vector3D 
	else if(mag == 1.0f){
		return Vector3D(*this);
	}

	//Calculate each component of unit vector
	float x = getX() / mag,
		y = getY() / mag,
		z = getZ() / mag;

	return Vector3D(x, y, z);
}


/**
* Creates a unit Vector3D orthogonal to the current Vector3D and another one
*
* @param v: reference to Vector3D to calculate orthogonal unit vector with
*
* @return: orthogonal unit vector made by current Vector3D object and Vector3D specified in parameter
*/
Vector3D Vector3D::findOrthagonalUnitVector(const Vector3D &v) const{
	//Calculate vector/cross product of two Vector3Ds
	Vector3D crossProd = *this % v;

	//Get unit Vector3D from crossProd Vector3D
	return crossProd.makeUnitVector3D();
}


/**
 * Operator overloading of '+' to allow addition of two Vector3Ds
 *
 * @param v: reference to Vector3D to add with current object
 *
 * @return: Vector3D sum of current object and addend in parameter
 */
Vector3D Vector3D::operator+(const Vector3D &v) const{
	//Calculate sum of each component of the two Vector3Ds
	float x = getX() + v.getX(),
		y = getY() + v.getY(),
		z = getZ() + v.getZ();

	return Vector3D(x, y, z);
}


/**
* Operator overloading of '-' to allow subtraction of two Vector3Ds
*
* @param v: reference to Vector3D to subract from current Vector3D
*
* @return: Vector3D difference of current object with Vector3D in parameter
*/
Vector3D Vector3D::operator-(const Vector3D &v) const{
	//Calculate difference of each component of the two Vector3Ds
	float x = getX() - v.getX(),
		y = getY() - v.getY(),
		z = getZ() - v.getZ();

	return Vector3D(x, y, z);
}


/**
* Operator overloading of '*' to allow multiplication of a Vector3D by a scalar/float
*
* @param s: scalar/factor to multiply current Vector3D by
*
* @return: Vector3D made by product of current Vector3D by scalar/float in parameter
*/
Vector3D Vector3D::operator*(const float s) const{
	//Calculate product of each component of the Vector3D by the scalar
	float x = getX() * s,
		y = getY() * s,
		z = getZ() * s;

	return Vector3D(x, y, z);
}


/**
* Operator overloading of '/' to allow division of a Vector3D by a scalar/float
*
* @param s: scalar/factor to divide current Vector3D by
*
* @return: Vector3D made by quotient of current Vector3D by scalar/float in parameter
*/
Vector3D Vector3D::operator/(const float s) const{
	//If divisor is 0 return current Vector3D
	if(s == 0){
		std::cout << "Error: Cannot divide by 0, returning copy of current Vector3D..." << std::endl;
		return Vector3D(*this);
	}
	//Calculate quotient of each component of the Vector3D by the scalar
	float x = getX() / s,
		y = getY() / s,
		z = getZ() / s;

	return Vector3D(x, y, z);
}


/**
* Operator overloading of '*' to allow calculating scalar/dot product of two Vector3Ds
*
* @param v: reference to Vector3D to calculate scalar/dot with
*
* @return: scalar/dot product of two Vector3Ds
*/
float Vector3D::operator*(const Vector3D &v) const{
	//Calculate product of each component of the two Vector3Ds
	float xProd = getX() * v.getX(),
		yProd = getY() * v.getY(),
		zProd = getZ() * v.getZ();

	return xProd + yProd + zProd;
}


/**
* Operator overloading of '%' to allow calculating vector/cross product of two Vector3Ds
*
* @param v: reference to Vector3D to calculate vector/cross with
*
* @return: Vector3D made by vector/cross product of two Vector3Ds
*/
Vector3D Vector3D::operator%(const Vector3D &v) const{
	//Formula for vector/cross product adapted from: https://www.mathsisfun.com/algebra/vectors-cross-product.html
	//Calculate each components' vector/cross product value
	float x = (getY() * v.getZ()) - (getZ() * v.getY()),
		y = (getZ() * v.getX()) - (getX() * v.getZ()),
		z = (getX() * v.getY()) - (getY() * v.getX());

	return Vector3D(x, y, z);
}


/**
* Operator overloading of '='/assignment operator
*
* @param copy: reference to Vector3D to copy values from
*
* @return: reference to Vector3D copied over
*/
Vector3D& Vector3D::operator=(const Vector3D& copy){
	//Check if copied Vector3D is equivalent to current object
	if (this == &copy){
		//If same object, return itself
		return *this;
	}

	//If different Vector3Ds, copy values across
	this->copy(copy);
	//Return modified Vector3D
	return *this;
}


/**
 * Operator overloading of '+=' operator
 *
 * @param copy: reference to Vector3D to add values from
 *
 * @return: reference to Vector3D modified
 */
Vector3D& Vector3D::operator+=(const Vector3D &v){
	//Add to each component of the Vector3D the respective component in v
	this->x += v.getX();
	this->y += v.getY();
	this->z += v.getZ();

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
Vector3D& Vector3D::operator-=(const Vector3D &v){
	//Subtract from each component of the Vector3D the respective component in v
	this->x -= v.getX();
	this->y -= v.getY();
	this->z -= v.getZ();

	//Return (modified) current object 
	return *this;
}


/**
 * Operator overloading of '*=' operator
 *
 * @param copy: reference to Vector3D to multiply values from
 *
 * @return: reference to Vector3D modified
 */
Vector3D& Vector3D::operator*=(const float s){
	//Multiply each component of the Vector3D by s
	this->x *= s;
	this->y *= s;
	this->z *= s;

	//Return (modified) current object 
	return *this;
}


/**
 * Operator overloading of '/=' operator
 *
 * @param copy: reference to Vector3D to divide values from
 *
 * @return: reference to Vector3D modified
 */
Vector3D& Vector3D::operator/=(const float s){
	//If divisor is 0 return current Vector3D
	if (s == 0){
		std::cout << "Error: Cannot divide by 0, returning current Vector3D..." << std::endl;
		return *this;
	}

	//Divide each component of the Vector3D by s
	this->x /= s;
	this->y /= s;
	this->z /= s;

	//Return (modified) current object 
	return *this;
}


/**
 * Operator overloading of '=='/comparison operator
 *
 * @param v: reference to Vector3D to compare
 *
 * @return: true if objects have same component values, false if any are different
 */
bool Vector3D::operator==(const Vector3D &v) const{
	//Check if Vector3D being compared is the current object
	if(this == &v){
		//If same object, return true
		return true;
	}

	//Check if two Vector3Ds have same size, if not must be different
	if(this->magnitude() != v.magnitude()){
		return false;
	}

	//Compare each component coordinates
	if((getX() == v.getX()) && (getY() == v.getY()) && (getZ() == v.getZ())){
		return true;
	}

	return false;
}


/**
 * Operator overloading of '!=' operator
 *
 * @param v: reference to Vector3D to compare
 *
 * @return: false if objects have same component values, true if any are different
 */
bool Vector3D::operator!=(const Vector3D &v) const{
	//Negate == operator result
	return !(this->operator==(v));
}


/**
 * Operator overloading of '<' operator
 *
 * @param v: reference to Vector3D to compare
 *
 * @return: true current object's magnitude smaller than v's magnitude, false otherwise
 */
bool Vector3D::operator<(const Vector3D &v) const{
	//Check if Vector3D being compared is the current object
	if (this == &v){
		//If same object, return false
		return false;
	}

	return magnitude() < v.magnitude() ? true : false;
}


/**
 * Operator overloading of '<=' operator
 *
 * @param v: reference to Vector3D to compare
 *
 * @return: true current object's magnitude smaller than OR equal to v's magnitude, false otherwise
 */
bool Vector3D::operator<=(const Vector3D &v) const{
	return this->operator==(v) || this->operator<(v);
}


/**
 * Operator overloading of '>' operator
 *
 * @param v: reference to Vector3D to compare
 *
 * @return: true current object's magnitude greater than v's magnitude, false otherwise
 */
bool Vector3D::operator>(const Vector3D &v) const{
	//Check if Vector3D being compared is the current object
	if (this == &v){
		//If same object, return false
		return false;
	}

	return magnitude() > v.magnitude() ? true : false;
}


/**
 * Operator overloading of '>=' operator
 *
 * @param v: reference to Vector3D to compare
 *
 * @return: true current object's magnitude greater than OR equal to v's magnitude, false otherwise
 */
bool Vector3D::operator>=(const Vector3D &v) const{
	return this->operator==(v) || this->operator>(v);
}



/** 
 * Copies content from specified Vector3D object into current object
 *
 * @param copy: reference to Vector3D to copy values from 
 */
void Vector3D::copy(const Vector3D &copy){
	//Update components value equal to copy's values
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
}



/**
* Operator overloading of '>>' operator of the input stream class to accept Vector3Ds
*
* @param inStream: reference to input stream
* @param v: reference to the Vector3D object to write values into
*
* @return: reference to input stream
*/
std::istream& operator>> (std::istream &inStream, Vector3D &v){
	//Values to assign the input into in order to create a Vector3D
	float x, y, z;
	//Any character the user uses to separate Vector3D components
	char separator;

	inStream >> x >> separator >> y >> separator >> z;

	//Create Vector3D from input stream
	v = Vector3D(x, y, z);
	return inStream;
}


/**
* Operator overloading of '<<' operator of the output stream class to accept Vector3Ds
*
* @param outStream: reference to output stream
* @param v: reference to Vector3D to output
*
* @return: reference to output stream
*/
std::ostream& operator<< (std::ostream &outStream, const Vector3D &v){
	outStream << '(' << v.getX() << ',' << v.getY() << ',' << v.getZ() << ')';
	return outStream;
}