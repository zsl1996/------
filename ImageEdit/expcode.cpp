#include "expcode.h"
#include <iostream>
#include<mat.h>
using namespace std;
int QuickSortOnce(int a[], int low, int high)
{  
	int pivot = a[low];
	int i = low, j = high;
	while (i < j)
	{
		while (a[j] >= pivot && i < j)
		{
			j--;
		}  
		a[i] = a[j];  
		while (a[i] <= pivot && i < j)
		{
			i++;
		}
		a[j] = a[i];
	} 
	a[i] = pivot;

	return i;
}

void QuickSort(int a[], int low, int high)
{
	if (low >= high)
	{
		return;
	}

	int pivot = QuickSortOnce(a, low, high);

  
	QuickSort(a, low, pivot - 1);
	QuickSort(a, pivot + 1, high);
}

int EvaluateMedian(int a[], int n)
{
	QuickSort(a, 0, n - 1);
	if (n % 2 != 0)
	{
		return a[n / 2];
	}
	else
	{
		return (a[n / 2] + a[n / 2 - 1]) / 2;
	}
}
//示例: 求图像中心点像素的灰度值


int midptvalue(int** pixelmat, int mheight, int mwidth)
{
	//pixelmat为指向图像像素值二维数组指针, 指向图像左上角的像素, 像素值类型为int;
	//mheight为图像的高度(行), mwidth为图像的宽度(列);
	int middlerow = mheight / 2 - 1;
	int middlecol = mwidth / 2 - 1;
	return pixelmat[middlerow][middlecol];
}

//求最大值
int maxvalue(int** pixelmat, int mheight, int mwidth)
{
	int i, j, max = 0;
	for (i = 0; i <= mheight - 1; i++)
	{
		for (j = 0; j <= mwidth - 1; j++)
		{
			if (pixelmat[i][j] > max)
			{
				max = pixelmat[i][j];
			}
		}
	}
	return max;
}

//求最小值
int minvalue(int** pixelmat, int mheight, int mwidth)
{
	int i, j, min = 255;
	for (i = 0; i <= mheight - 1; i++)
	{
		for (j = 0; j <= mwidth - 1; j++)
		{
			if (pixelmat[i][j] < min)
			{
				min = pixelmat[i][j];
			}
		}
	}
	return min;
}

//求平均值
float avgvalue(int** pixelmat, int mheight, int mwidth)
{
	int i, j, sum = 0;
	float  avg = 0.0;
	for (i = 0; i <= mheight - 1; i++)
	{
		for (j = 0; j <= mwidth - 1; j++)
		{
			sum = sum + pixelmat[i][j];
		}
	}
	avg = sum / float(mheight*mwidth);
	return avg;
}

//求方差
float varvalue(int** pixelmat, int mheight, int mwidth)
{
	float avg, sum = 0.0, var;
	int i, j;
	avg = avgvalue(pixelmat, mheight, mwidth);
	for (i = 0; i <= mheight - 1; i++)
	{
		for (j = 0; j <= mwidth - 1; j++)
		{
			sum = sum + pow(pixelmat[i][j] - avg, 2.0);
		}
	}
	var = sum / (mheight*mwidth);
	return var;
}

//统计直方图, 返回长度为256的1维数组
int* histogram(int** pixelmat, int mheight, int mwidth)
{
	//注意:函数内分配数组必须使用动态分配;
	int* histo = new int[256]{ 0 };
	int i, j, k;
	for (i = 0; i <= mheight - 1; i++)
	{
		for (j = 0; j <= mwidth - 1; j++)
		{
			k = pixelmat[i][j];
			histo[k]++;
		}
	}
	return histo;
}

//示例,将灰度图转化为二值图像,返回处理后的图像
int** binaryimg(int** pixelmat, int mheight, int mwidth)
{
	for (int i = 0; i < mheight; i++)
	{
		for (int j = 0; j < mwidth; j++)
		{
			//从左上角开始遍历整幅图像, 实现二值化;
			pixelmat[i][j] = pixelmat[i][j] > 128 ? 255 : 0;
		}
	}
	//根据实验要求返回对应的值;
	return pixelmat;
}

//直方图均衡, 返回处理后的图像
int** histogramequ(int** pixelmat, int mheight, int mwidth)
{
	int* histo = new int[256]{ 0 };
	int narry[256]{ 0 };
	float p[256]{ 0 };
	float c[256]{ 0 };
	histo = histogram(pixelmat, mheight, mwidth); //每个灰度值出现的次数（直方图）
	int i;
	for (i = 0; i <= 255; i++)
	{
		p[i] = histo[i] / float(mheight*mwidth); //每个灰度值出现的概率（直方图）
		if (i == 0)
		{
			c[i] = p[i];
		}
		else
		{
			c[i] = p[i] + c[i - 1];  //累积概率的直方图
		}
		narry[i] = (int)(255 * c[i] + 0.5); //映射关系
	}
	for (int i = 0; i < mheight; i++)
	{
		for (int j = 0; j < mwidth; j++)
		{
			pixelmat[i][j] = narry[pixelmat[i][j]];  //将图像根据映射关系改灰度值
		}
	}

	return pixelmat;
}

//灰度拉伸, 返回处理后的图像
int** graystretch(int** pixelmat, int mheight, int mwidth)
{
	//分段拉伸，找出分段函数，写个循环即可
	return NULL;
}

//中值滤波, 返回处理后的图像
int** medianfit(int** pixelmat, int mheight, int mwidth)
{
	mat m(mheight, mwidth, pixelmat);
	for (int i = 1; i < mheight - 1; i++) {
		for (int j = 1; j < mwidth - 1; j++) {
			int a[9] = { m.param[i - 1][j - 1] , m.param[i - 1][j] , m.param[i - 1][j + 1] , m.param[i][j - 1] , m.param[i][j] , m.param[i][j + 1] , m.param[i + 1][j - 1] , m.param[i + 1][j] , m.param[i + 1][j + 1] };
			pixelmat[i][j]=EvaluateMedian(a, 9);
		}
	}
	return pixelmat;
}

//均值滤波, 返回处理后的图像
int** averagefit(int** pixelmat, int mheight, int mwidth)
{
	mat m(mheight, mwidth, pixelmat);
	for (int i = 1; i < mheight - 1; i++) {
		for (int j = 1; j < mwidth - 1; j++) {
			pixelmat[i][j] = float(m.param[i - 1][j - 1] + m.param[i - 1][j] + m.param[i - 1][j + 1] + m.param[i][j - 1] + m.param[i][j] + m.param[i][j + 1] + m.param[i + 1][j - 1] + m.param[i + 1][j] + m.param[i + 1][j + 1]) / 9;
		}
	}
	return pixelmat;
}

//理想低通滤波, 返回处理后的图像
int** lowpassfit(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//sobel算子, 返回处理后的图像
int** sobel(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//laplace算子, 返回处理后的图像
int** laplace(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//理想高通滤波, 返回处理后的图像
int** highpassfit(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//示例, 将图像平移到显示区域的中心
int** centralize(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	//framemat为指向显示区域(画板)的二维数组指针, 大小为FRAME_HEIGHT x FRAMEWIDTH = 800 x 800
	int xpt = (FRAME_HEIGHT - mheight) / 2;
	int ypt = (FRAME_WIDTH - mwidth) / 2;
	for (int i = 0; i < mheight; i++)
	{
		for (int j = 0; j < mwidth; j++)
		{
			framemat[i + xpt][j + ypt] = pixelmat[i][j];
		}
	}
	return framemat;
}

//旋转图像, 返回显示区域(画板)指针
int** rotation(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//平移图像, 返回显示区域(画板)指针
int** moveimage(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//缩放图像, 返回显示区域(画板)指针
int** scaling(int** framemat, int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//DFT变换, 返回处理后的图像, 注意缩放到0~255的整型
int** DFT(int** pixelmat, int mheight, int mwidth)
{	
	mat m(mheight, mwidth, pixelmat);
	m.getDFT();
	m.printDFT();

	return m.param;
}

//DCT变换, 返回处理后的图像
int** DCT(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//walsh变换, 返回处理后的图像
int** walsh(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//haar变换, 返回处理后的图像
int** haar(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//生成随机噪声, 返回处理后的图像;
int** randomnoise(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//生成椒盐噪声, 返回处理后的图像
int** impulsenoise(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//逆滤波复原
int** inversefit(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

//维纳滤波
int** wienerfit(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}


//示例: JPEG压缩及解压缩
int** jpeg(int** pixelmat, int mheight, int mwidth)
{
	return NULL;
}

