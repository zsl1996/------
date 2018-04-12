#include "mat.h"
#include<math.h>
#define PI 3.14159265359  

mat::mat(int h, int w, int** p) 	//实现深copy
{
	this->h = h;
	this->w = w;
	param = new int*[h];
	Remat = new int*[h];
	Immat = new int*[h];
	temp = new int*[h];
	for (int i = 0; i < h; ++i) {
		param[i] = new int[w]();
		for (int j = 0; j < w; ++j) {
			param[i][j] = p[i][j];
		}
	}
	for (int i = 0; i < h; ++i) {
		Remat[i] = new int[w] {0};
	}
	for (int i = 0; i < h; ++i) {
		Immat[i] = new int[w] {0};
	}
	for (int i = 0; i < h; ++i) {
		temp[i] = new int[w] {0};
	}
}
mat::~mat()
{
}

void mat::calculate(int col, int row) //计算e-j*2pi（u/w+v/h） 因为三角运算及其占据计算资源,利用周期性查表，最好还是写fft	
{
	trigalesin = new float[col*row];
	trigalecos = new float[col*row];

	for (int y = 0; y< row; y++)
	{
		for (int x = 0; x< col; x++)
		{
			float tmp = -2 * PI*(1.0*x / col + 1.0*y / row);

			trigalesin[y*col + x] = sin(tmp);
			trigalecos[y*col + x] = cos(tmp);
		}
	}
}

void mat::getDFT() //
{
	
	calculate(w, h);
	for (int v = 0; v < h ; v++)
	{
		for (int u = 0; u< w; u++)
		{
			float tmpre = 0;
			float tmpim = 0;
			for (int i = 0; i<h ; i++)
			{
				for (int j = 0; j<w ; j++)
				{

					int index1 = (u*j) % w;
					int index2 = (v*i) % h;
					int index = index2 * w + index1;
					
					tmpre += param[i][j] * trigalesin[index];
					tmpim += param[i][j] * trigalecos[index];
				}
			}

			Remat[v][u] = tmpre;
			Immat[v][u] = tmpim;
		}
	}
}
void mat::swap(int** p) { //将低频转移至中央
	int midh = (h-1) / 2;
	int midw = (w-1) / 2;
	for  (int i = 0;  i  < h;  i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (i<=midh &&j<=midw)
			{
				param[i + midh][j + midw] = p[i][j];
			}
			if (i<midh &&j>midw)
			{
				param[i + midh][j - midw] = p[i][j];
			}
			if (i>midh &&j <= midw)
			{
				param[i - midh][j + midw] = p[i][j];
			}
			if(i>midh &&j > midw)
			{
				param[i - midh][j - midw] = p[i][j];
			}
		
		}
	}
}
void mat::printDFT() //将DFT结果压缩到0-255用于演示
{
	int max = 0;
	for (int i = 0; i < h; i++)
	{
		for(int j= 0;j< w ; j++){
			int q = pow(Remat[i][j], 2) + pow(Immat[i][j], 2);
			if (q > max) {
				max = q;
			}
			temp[i][j] = q; //暂时保存，避免重复计算
		}
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j< w; j++) {
			temp[i][j] = (float(temp[i][j]) / max) * 255;
			
		}
	}
	swap(temp);
}
					 
					 
					 

void mat::getIDFT()
{
	//for (int i = 0; i< h;  i++)
	//{
	//	for (int j = 0; j < w; j++)
	//	{
	//		float tmpa = 0;
	//		float tmpb = 0;

	//		for (int v = 0; v< arows; v++)
	//		{
	//			for (int u = 0; u< acols; u++)
	//			{
	//				float tmpfa = a[v*acols + u];
	//				float tmpfb = b[v*acols + u];

	//				int index1 = (u*x) % acols;
	//				int index2 = (v*y) % arows;
	//				int index = index2 * acols + index1;

	//				float tmpea = -trigalesin[index];//sin(2*PI*(u*x/acols+v*y/arows));  
	//				float tmpeb = trigalecos[index];//cos(2*PI*(u*x/acols+v*y/arows));  

	//				tmpa += tmpfa * tmpea - tmpfb * tmpeb;
	//				tmpb += tmpfa * tmpeb + tmpfb * tmpea;
	//			}
	//		}

	//		(*c)[y*acols + x] = sqrt(tmpa*tmpa + tmpb * tmpb);
	//	}
	//}
}


