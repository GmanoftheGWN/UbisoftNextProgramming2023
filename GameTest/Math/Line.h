#ifndef LINE_H
#define LINE_H

#include "Vec3.h"

namespace MATH 
{
	class Line 
	{
	public:
		Vec3 start;
		Vec3 end;

		Line();
		Line(Vec3 lineStart_, Vec3 lineEnd_);
	};
}
#endif 