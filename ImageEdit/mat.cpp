#include "mat.h"



mat::mat(int h, int w, int** p)
{
	this->h = h;
	this->w = w;
	//ʵ��ָ��ָ���ָ������
	param = new int*[h];//����һ���ڴ���������Ԫ��Ϊָ��int��ָ������飬��Щָ��ֱ�ָ��ÿһ��
	for (int i = 0; i < h; ++i) {
		//Ϊÿһ�����ָ�����������һ���ڴ洢��Ԫ��Ϊint�����飬������鴢��һ�����ÿһ��Ԫ�أ�����Ԫ�س�ʼ��Ϊ0
		param[i] = new int[w]();
		for (int j = 0; j < w; ++j) {
			param[i][j] = p[i][j];//�������Ԫ�ظ�ֵ
		}
	}
}

mat::~mat()
{
}
