#pragma once
/**
 * Class: Vector3D
 * @author: Dennis Zinzi (130301136)
 *
 * Description: Implementation of a 3D vector object 
 */

#include <iostream>
#include <cmath>


class Vector3D{
	public:
		//Vector3D constructors
		Vector3D();
		Vector3D(float x, float y, float z);

		//Copy Constructor
		Vector3D(const Vector3D &copy);

		//Destructor
		~Vector3D();

		/**
		 * Getter method for the x component of a Vector3D
		 *
		 * @return: x component of current object
		 */
		inline float getX() const{
			return x;
		}

		/**
		* Getter method for the y component of a Vector3D
		*
		* @return: y component of current object
		*/
		inline float getY() const{
			return y;
		}

		/**
		* Getter method for the z component of a Vector3D
		*
		* @return: z component of current object
		*/
		inline float getZ() const{
			return z;
		}

		/**
		* Getter method for the x component of a Vector3D
		*
		* @return: x component of current object
		*/
		inline void setX(float x){
			this->x = x;
		}

		/**
		* Getter method for the y component of a Vector3D
		*
		* @return: y component of current object
		*/
		inline void setY(float y){
			this->y = y;
		}

		/**
		* Getter method for the z component of a Vector3D
		*
		* @return: z component of current object
		*/
		inline void setZ(float z){
			this->z = z;
		}


		//Vector3D functions
		float magnitude() const;
		Vector3D makeUnitVector3D() const;
		Vector3D findOrthagonalUnitVector(const Vector3D &v) const;
		float getVector3DDirection() const;

		//Operator overloading operations
		Vector3D operator+(const Vector3D &v) const;
		Vector3D operator-(const Vector3D &v) const;
		Vector3D operator*(const float s) const;
		Vector3D operator/(const float s) const;

		//Operator overload to calculate scalar/dot product of two Vector3Ds
		float operator*(const Vector3D &v) const;
		//Operator overload to calculate vector/cross product of two Vector3Ds
		Vector3D operator%(const Vector3D &v) const;

		//Operator overload of assignment operator
		Vector3D& operator=(const Vector3D &copy);

		//Extra operator overloading operations
		Vector3D& operator+=(const Vector3D &v);
		Vector3D& operator-=(const Vector3D &v);
		Vector3D& operator*=(const float s);
		Vector3D& operator/=(const float s);

		//Comparison operator overloads
		bool operator==(const Vector3D &v) const;
		bool operator!=(const Vector3D &v) const;
		bool operator<(const Vector3D &v) const;
		bool operator<=(const Vector3D &v) const;
		bool operator>(const Vector3D &v) const;
		bool operator>=(const Vector3D &v) const;

	private:
		//Member variables representing each component of a Vector3D
		float x, y, z;

		//copy function to be used by assingment operator and copy constructor
		void copy(const Vector3D &copy);
};


//Overload input stream >> operator to accept a Vector3D
std::istream& operator>>(std::istream &inStream, Vector3D &v);

//Overload output stream << operator to display a Vector3D
std::ostream& operator<<(std::ostream &outStream, const Vector3D &v);