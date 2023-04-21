#include "stdafx.h"
#include "Vec3.h"

using namespace MATH;

Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float xyz_)
{
	x = y = z = xyz_;
}

Vec3::Vec3(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

//Assignment
Vec3 Vec3::operator = (const Vec3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return Vec3(x, y, z);
}

//Add Two Vec3 Together
Vec3 Vec3::operator + (const Vec3& v)
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

//Add a Vec3 to Itself
Vec3 Vec3::operator += (const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return Vec3(x, y, z);
}

//Subtract Two Vec3
Vec3 Vec3::operator - (const Vec3& v)
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

//Subtract a Vec3 From Itself
Vec3 Vec3::operator -= (const Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return Vec3(x, y, z);
}

//Negative of Vec3
Vec3 Vec3::operator - ()
{
	return Vec3(-x, -y, -z);
}

//Multiply Vec3 by a Scalar
Vec3 Vec3::operator * (const float s)
{
	return Vec3(x * s, y * s, z * s);
}

//Multiply Vec3 by a Scalar and Assign it to Itself
Vec3 Vec3::operator *= (const float s)
{
	x *= s;
	y *= s;
	z *= s;

	return Vec3(x, y, z);
}

//Divide Vec3 by a Scalar
Vec3 Vec3::operator / (const float s)
{
	return Vec3(x / s, y / s, z / s);
}

//Divide Vec3 by a Scalar and Assign it to Itself
Vec3 Vec3::operator /= (const float s)
{
	x /= s;
	y /= s;
	z /= s;

	return Vec3(x, y, z);
}

//Calculate Magnitude of Vec3
float Vec3::mag(const Vec3& a) 
{
	return(sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

//Calculate Normalized Vec3
Vec3 Vec3::normalize(const Vec3& a) 
{
	float magnitude;
	magnitude = mag(a);
	return Vec3(a.x / magnitude, a.y / magnitude, a.z / magnitude);
}

//Calculate Dot Product of Two Vec3
float Vec3::dot(const Vec3& a, const Vec3& b) 
{
	return(a.x * b.x + a.y * b.y + a.z * b.z);
}

//Calculate Cross Product of Two Vec3
Vec3 Vec3::cross(const Vec3& a, const Vec3& b) 
{
	return Vec3(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
}

//Calculate Distance Between Two Vec3
float Vec3::distance(const Vec3& a, const Vec3& b) 
{
	return(mag(Vec3(a.x - b.x, a.y - b.y, a.z - b.z)));
}