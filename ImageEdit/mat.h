#pragma once
class mat
{
public:
	int h;
	int w;
	int** param;

public:
	mat(int h, int w,int **p);
	~mat();
};

//构造函数的实现
