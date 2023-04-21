#include "stdafx.h"
#include "Line.h"

using namespace MATH;

Line::Line()
{
	start = Vec3(0.0f);
	end = Vec3(1.0f);
}

Line::Line(Vec3 lineStart_, Vec3 lineEnd_)
{
	start = lineStart_;
	end = lineEnd_;
}
