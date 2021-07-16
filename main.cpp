#include <iostream>
#include <vector>
#include <assert.h>

#define SQRT2 1.41421356

struct Point2i
{
	Point2i()
	{
		x = 0;
		y = 0;
	}

	Point2i(const int& _x, const int& _y)
	{
		x = _x;
		y = _y;
	}

	int x, y;
};

// 获取给定圆内的整数点
std::vector<Point2i> GetAllPointInCircle(const Point2i& center, const int& radius)
{
	assert(radius > 0);

	std::vector<Point2i> points;
	// 坐标轴
	for (int i = 0; i <= radius; i++)
	{
		points.push_back(Point2i(i, 0));
	}
	// y = x
	int maxI = floor(radius / SQRT2);
	for (int i = 1; i <= maxI; i++)
	{
		points.push_back(Point2i(i, i));
	}
	// 其他点
	// 下部分
	int xBottomMax = radius - 1;
	int yBottomMax = floor(sqrt(radius * radius - xBottomMax * xBottomMax));
	for (int i = 1; i <= yBottomMax; i++)
	{
		for (int j = i + 1; j <= xBottomMax; j++)
		{
			points.push_back(Point2i(j, i));
		}
	}

	// 上部分
	for (int i = yBottomMax + 1; i <= maxI; i++)
	{
		int xMaxUpper = floor(sqrt(radius * radius - i * i));
		for (int j = i + 1; j <= xMaxUpper; j++)
		{
			points.push_back(Point2i(j, i));
		}
	}

	// 做对称
	// 根据y = x对称
	int pointNum;
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != points[i].y)
		{
			points.push_back(Point2i(points[i].y, points[i].x));
		}
	}

	// 根据y轴对称
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != 0)
		{
			points.push_back(Point2i(-points[i].x, points[i].y));
		}
	}

	// 根据x轴对称
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].y != 0)
		{
			points.push_back(Point2i(points[i].x, -points[i].y));
		}
	}

	// 把圆平移到圆心
	for (auto& point : points)
	{
		point.x += center.x;
		point.y += center.y;
	}
	return points;
}

// 获取给定圆环内的整数点
std::vector<Point2i> GetAllPointInRing(const Point2i& center, const int& radiusSmall, const int& radiusBig)
{
	assert(radiusBig > radiusSmall);
	assert(radiusSmall >= 0);

	std::vector<Point2i> points;
	// 坐标轴上的
	for (int i = radiusSmall + 1; i <= radiusBig; i++)
	{
		points.push_back(Point2i(i, 0));
	}

	// y = x上的
	int maxXSmall = floor(radiusSmall / SQRT2);
	int maxXBig = floor(radiusBig / SQRT2);
	for (int i = maxXSmall + 1; i <= maxXBig; i++)
	{
		points.push_back(Point2i(i, i));
	}

	// 其他的
	// 下部分
	int maxXBottomSmall = radiusSmall - 1;
	int maxYBottomSmall = floor(sqrt(radiusSmall * radiusSmall - maxXBottomSmall * maxXBottomSmall));
	int maxXBottomBig = radiusBig - 1;
	int maxYBottomBig = floor(sqrt(radiusBig * radiusBig - maxXBottomBig * maxXBottomBig));

	for (int i = 1; i <= maxYBottomBig; i++)
	{
		// 如果到了小圆上半部分，每行先计算那一行小圆的最大x值
		// 只要比小圆对角线y值大的点一定不在小圆里，所以这里不计算
		int xMaxUpperSmall = 0;
		if (i > maxYBottomSmall && i <= maxXSmall)
		{
			xMaxUpperSmall = floor(sqrt(radiusSmall * radiusSmall - i * i));
		}
		for (int j = i + 1; j <= maxXBottomBig; j++)
		{
			// 如果在小圆的直角梯形内直接丢弃
			if (j <= maxXBottomSmall && i <= maxYBottomSmall) continue;
			// 如果在小圆上半部分且比x值那一行小圆的最大x值小，也丢弃
			if (i > maxYBottomSmall && i <= maxXSmall)
			{
				if (j <= xMaxUpperSmall) continue;
			}
			points.push_back(Point2i(j, i));
		}
	}

	// 上部分
	for (int i = maxYBottomBig + 1; i <= maxXBig; i++)
	{
		int xMaxUpper = floor(sqrt(radiusBig * radiusBig - i * i));
		// 这里与上面一样，只要比小圆对角线y值大，就一定不在小圆里，不需要判断
		int xMaxUpperSmall = 0;
		if (i <= maxXSmall)
		{
			xMaxUpperSmall = floor(sqrt(radiusSmall * radiusSmall - i * i));
		}
		for (int j = i + 1; j <= xMaxUpper; j++)
		{
			if (i <= maxXSmall)
			{
				if (j <= xMaxUpperSmall) continue;
			}
			points.push_back(Point2i(j, i));
		}
	}

	// 对称
	// 根据y = x对称
	int pointNum;
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != points[i].y)
		{
			points.push_back(Point2i(points[i].y, points[i].x));
		}
	}

	// 根据y轴对称
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != 0)
		{
			points.push_back(Point2i(-points[i].x, points[i].y));
		}
	}

	// 根据x轴对称
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].y != 0)
		{
			points.push_back(Point2i(points[i].x, -points[i].y));
		}
	}

	// 平移到圆心
	for (auto& point : points)
	{
		point.x += center.x;
		point.y += center.y;
	}
	return points;
}

int main()
{
	Point2i center(0, 0);
	int radius = 7;
	std::vector<Point2i> points;

	//points = GetAllPointInCircle(center, radius);
	points = GetAllPointInRing(center, 0, 1);

	for (auto& point : points)
	{
		std::cout << point.x << " " << point.y << std::endl;
	}

	return 0;
}