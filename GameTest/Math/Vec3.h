#ifndef VEC3_H
#define VEC3_H

#include <math.h>

namespace MATH 
{
	#ifndef VERY_SMALL
	#define VERY_SMALL 1.0e-7f
	#endif

	class Vec3 
	{
	public:
		float x, y, z;

		Vec3();
		Vec3(float xyz_);
		Vec3(float x_, float y_, float z_);

		Vec3 operator = (const Vec3& v);

		Vec3 operator + (const Vec3& v);
		Vec3 operator += (const Vec3& v);

		Vec3 operator - (const Vec3& v);
		Vec3 operator -= (const Vec3& v);

		Vec3 operator - ();

		Vec3 operator * (const float s);
		Vec3 operator *= (const float s);

		Vec3 operator / (const float s);
		Vec3 operator /= (const float s);

		static float mag(const Vec3& a);

		static Vec3 normalize(const Vec3& a);

		static float dot(const Vec3& a, const Vec3& b);

		static Vec3 cross(const Vec3& a, const Vec3& b);

		static float distance(const Vec3& a, const Vec3& b);
	};
}
#endif