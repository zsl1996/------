#include "mat.h"



mat::mat(int h, int w, int** p)
{
	this->h = h;
	this->w = w;
	//实现指向指针的指针的深复制
	param = new int*[h];//申请一块内存用来储存元素为指向int的指针的数组，这些指针分别指向每一行
	for (int i = 0; i < h; ++i) {
		//为每一个存放指针的数组申请一块内存储存元素为int的数组，这个数组储存一行里的每一个元素，并将元素初始化为0
		param[i] = new int[w]();
		for (int j = 0; j < w; ++j) {
			param[i][j] = p[i][j];//进行逐个元素赋值
		}
	}
}

mat::~mat()
{
}
