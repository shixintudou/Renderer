#include "Rasterize.h"

void Rasterize::ScanTriangle(const V2F& v1, const V2F& v2, const V2F& v3)
{
	std::vector<V2F> arr = { v1,v2,v3 };
	Sort(arr, 0, arr.size() - 1);
	if (arr[0].windowPos.y == arr[1].windowPos.y)
		UpTriangle(arr[0], arr[1], arr[2]);
	else if (arr[1].windowPos.y == arr[2].windowPos.y)
		DownTriangle(arr[1], arr[2], arr[0]);
	else
	{
		float weight = (arr[2].windowPos.y - arr[1].windowPos.y) / (arr[2].windowPos.y - arr[0].windowPos.y);
		V2F newEdge = V2F::Lerp(arr[2], arr[0], weight);
		UpTriangle(arr[1], newEdge, arr[2]);
		DownTriangle(arr[1], newEdge, arr[0]);
	}
}

void Rasterize::UpTriangle(const V2F& v1, const V2F& v2, const V2F& v3)
{
	V2F left, right, top;
	left = v1.windowPos.x > v2.windowPos.x ? v2 : v1;
	right = v1.windowPos.x > v2.windowPos.x ? v1 : v2;
	top = v3;
	left.windowPos.x = (int)left.windowPos.x;
	int dy = top.windowPos.y - left.windowPos.y;
	int nowY = top.windowPos.y;
	//从上往下插值
	for (int i = dy; i >= 0; i--) 
	{
		float weight = 0;
		if (dy != 0) 
		{
			weight = (float)i / dy;
		}
		V2F newLeft = V2F::Lerp(left, top, weight);
		V2F newRight = V2F::Lerp(right, top, weight);
		newLeft.windowPos.x = int(newLeft.windowPos.x);
		newRight.windowPos.x = int(newRight.windowPos.x + 0.5);
		newLeft.windowPos.y = newRight.windowPos.y = nowY;
		ScanLine(newLeft, newRight);
		nowY--;
	}
}

void Rasterize::DownTriangle(const V2F& v1, const V2F& v2, const V2F& v3)
{
	V2F left, right, bottom;
	left = v1.windowPos.x > v2.windowPos.x ? v2 : v1;
	right = v1.windowPos.x > v2.windowPos.x ? v1 : v2;
	bottom = v3;
	int dy = left.windowPos.y - bottom.windowPos.y;
	int nowY = left.windowPos.y;
	//从上往下插值
	for (int i = 0; i < dy; i++) 
	{
		float weight = 0;
		if (dy != 0) 
		{
			weight = (float)i / dy;
		}
		V2F newLeft = V2F::Lerp(left, bottom, weight);
		V2F newRight = V2F::Lerp(right, bottom, weight);
		newLeft.windowPos.x = int(newLeft.windowPos.x);
		newRight.windowPos.x = int(newRight.windowPos.x + 0.5);
		newLeft.windowPos.y = newRight.windowPos.y = nowY;
		ScanLine(newLeft, newRight);
		nowY--;
	}
}

void Rasterize::ScanLine(const V2F& v1, const V2F& v2)
{
	int length = v2.windowPos.x - v1.windowPos.x;
	for (int i = 0; i < length; i++)
	{
		V2F v = V2F::Lerp(v1, v2, (float)i / length);
		FrontBuffer.WritePoint(v.windowPos.x, v.windowPos.y, shader.FragmentShader(v));
	}
}

void Rasterize::Sort(std::vector<V2F>& arr, int l, int r)
{
	if (l >= r)
		return;
	int i = l;
	int j = r;
	V2F x = arr[l];
	while (i<j)
	{
		while (i<j&&arr[j].windowPos.y>=x.windowPos.y)
		{
			j--;
		}
		while (i<j&&arr[i].windowPos.y<=x.windowPos.y)
		{
			i++;
		}
		if (i < j)
		{
			V2F t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}		
	}
	if (i>l)
	{
		V2F t = arr[i];
		arr[i] = arr[l];
		arr[l] = t;
	}
	Sort(arr, l, i - 1);
	Sort(arr, i + 1, r);
}
