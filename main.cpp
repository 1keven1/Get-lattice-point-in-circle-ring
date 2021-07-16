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

// ��ȡ����Բ�ڵ�������
std::vector<Point2i> GetAllPointInCircle(const Point2i& center, const int& radius)
{
	assert(radius > 0);

	std::vector<Point2i> points;
	// ������
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
	// ������
	// �²���
	int xBottomMax = radius - 1;
	int yBottomMax = floor(sqrt(radius * radius - xBottomMax * xBottomMax));
	for (int i = 1; i <= yBottomMax; i++)
	{
		for (int j = i + 1; j <= xBottomMax; j++)
		{
			points.push_back(Point2i(j, i));
		}
	}

	// �ϲ���
	for (int i = yBottomMax + 1; i <= maxI; i++)
	{
		int xMaxUpper = floor(sqrt(radius * radius - i * i));
		for (int j = i + 1; j <= xMaxUpper; j++)
		{
			points.push_back(Point2i(j, i));
		}
	}

	// ���Գ�
	// ����y = x�Գ�
	int pointNum;
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != points[i].y)
		{
			points.push_back(Point2i(points[i].y, points[i].x));
		}
	}

	// ����y��Գ�
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != 0)
		{
			points.push_back(Point2i(-points[i].x, points[i].y));
		}
	}

	// ����x��Գ�
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].y != 0)
		{
			points.push_back(Point2i(points[i].x, -points[i].y));
		}
	}

	// ��Բƽ�Ƶ�Բ��
	for (auto& point : points)
	{
		point.x += center.x;
		point.y += center.y;
	}
	return points;
}

// ��ȡ����Բ���ڵ�������
std::vector<Point2i> GetAllPointInRing(const Point2i& center, const int& radiusSmall, const int& radiusBig)
{
	assert(radiusBig > radiusSmall);
	assert(radiusSmall >= 0);

	std::vector<Point2i> points;
	// �������ϵ�
	for (int i = radiusSmall + 1; i <= radiusBig; i++)
	{
		points.push_back(Point2i(i, 0));
	}

	// y = x�ϵ�
	int maxXSmall = floor(radiusSmall / SQRT2);
	int maxXBig = floor(radiusBig / SQRT2);
	for (int i = maxXSmall + 1; i <= maxXBig; i++)
	{
		points.push_back(Point2i(i, i));
	}

	// ������
	// �²���
	int maxXBottomSmall = radiusSmall - 1;
	int maxYBottomSmall = floor(sqrt(radiusSmall * radiusSmall - maxXBottomSmall * maxXBottomSmall));
	int maxXBottomBig = radiusBig - 1;
	int maxYBottomBig = floor(sqrt(radiusBig * radiusBig - maxXBottomBig * maxXBottomBig));

	for (int i = 1; i <= maxYBottomBig; i++)
	{
		// �������СԲ�ϰ벿�֣�ÿ���ȼ�����һ��СԲ�����xֵ
		// ֻҪ��СԲ�Խ���yֵ��ĵ�һ������СԲ��������ﲻ����
		int xMaxUpperSmall = 0;
		if (i > maxYBottomSmall && i <= maxXSmall)
		{
			xMaxUpperSmall = floor(sqrt(radiusSmall * radiusSmall - i * i));
		}
		for (int j = i + 1; j <= maxXBottomBig; j++)
		{
			// �����СԲ��ֱ��������ֱ�Ӷ���
			if (j <= maxXBottomSmall && i <= maxYBottomSmall) continue;
			// �����СԲ�ϰ벿���ұ�xֵ��һ��СԲ�����xֵС��Ҳ����
			if (i > maxYBottomSmall && i <= maxXSmall)
			{
				if (j <= xMaxUpperSmall) continue;
			}
			points.push_back(Point2i(j, i));
		}
	}

	// �ϲ���
	for (int i = maxYBottomBig + 1; i <= maxXBig; i++)
	{
		int xMaxUpper = floor(sqrt(radiusBig * radiusBig - i * i));
		// ����������һ����ֻҪ��СԲ�Խ���yֵ�󣬾�һ������СԲ�����Ҫ�ж�
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

	// �Գ�
	// ����y = x�Գ�
	int pointNum;
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != points[i].y)
		{
			points.push_back(Point2i(points[i].y, points[i].x));
		}
	}

	// ����y��Գ�
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].x != 0)
		{
			points.push_back(Point2i(-points[i].x, points[i].y));
		}
	}

	// ����x��Գ�
	pointNum = points.size();
	for (int i = 0; i < pointNum; i++)
	{
		if (points[i].y != 0)
		{
			points.push_back(Point2i(points[i].x, -points[i].y));
		}
	}

	// ƽ�Ƶ�Բ��
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