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
	int** temp; //����һЩ�м�����


public:
	void calculate(int col, int row);
	void mulcomplex(int &re1,int &im1, int re2, int im2);
	void getDFT(); //���������ŵ�Remat ��Immat����
	void printDFT(); //��DFT���ѹ����0-255������ʾ
	void swap(int** p);
	void getIDFT();
	mat(int h, int w, int ** p);
	~mat();
};

//���캯����ʵ��
