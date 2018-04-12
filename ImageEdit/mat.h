#pragma once
class mat 
{
public:
	int h;
	int w;
	int** param;
	float *trigalesin;
	float *trigalecos;
	int** Remat;
	int** Immat;
	int** temp; //保存一些中间数据


public:
	void calculate(int col, int row);
	void mulcomplex(int &re1,int &im1, int re2, int im2);
	void getDFT(); //将计算结果放到Remat 与Immat里面
	void printDFT(); //将DFT结果压缩到0-255用于演示
	void swap(int** p);
	void getIDFT();
	mat(int h, int w, int ** p);
	~mat();
};

//构造函数的实现
