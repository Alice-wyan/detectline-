/*
�������Լ�����
*/

#pragma once

#include "lib.h"

#define DIM_OF_LBP 256
using namespace std;

/*
���룺 1��ͼƬ����
       2��ͼƬָ�� IplImage*
	   
����� �����DIM_OF_LBP��double���� outPut 

*/


class CLBP
{
public:
	CLBP(void);
	~CLBP(void);

private:
int bin2value( int a[], int n )//2����ת��Ϊ10����
{
    int value = 0;
    for( int i=0; i<n; ++i )
        value |= a[i]<<i;
    return value;
}	
	
void ComputingPro(int r,int c,int **a)//�������LBP�е�ÿ��Ԫ�ظ���
{

	int count[DIM_OF_LBP];    //����һ�����飬��Ƶ��
	for(int t=0;t<DIM_OF_LBP;t++)
			count[t]=0;
	
	for(int i=0;i<DIM_OF_LBP;i++)
	{
		for(int k=0;k<r-2;k++)
		{
			for(int j=0;j<c-2;j++)
			{
				if(i==a[k][j])
					count[i]++;
			}
		}
		outPut[i]=count[i]/((double)((r-2)*(c-2)));//����Ƶ��
	}
}	
void clear(){
	if (m_cvImageFlag==1) {cvReleaseImage(&m_cvImage); m_cvImageFlag=0;}
	if (m_cvImageRBGFlag==1) {cvReleaseImage(&m_cvImageRBG); m_cvImageRBGFlag=0;}

	if(LBPFlag==1){
	  for(int i=0;i<width;i++)
	  {
		  delete [] LBPData[i];
		  LBPData[i]=NULL;
	  }
	  delete [] LBPData;
	  LBPData=NULL;	
	  LBPFlag=0;
	}

	height=0;
	width=0;	
}

public:
void setup(string src_image_fl){
	clear();
	m_cvImageRBG = cvLoadImage(src_image_fl.c_str(), 1);// ��ȡͼƬ
	m_cvImageRBGFlag=1;

	height=m_cvImageRBG->height;
	width=m_cvImageRBG->width;	

	m_cvImage = cvCreateImage(cvSize(m_cvImageRBG->width, m_cvImageRBG->height), 8, 1);
    m_cvImageFlag=1;

	LBPData=new int*[width];    //����һ��ָ�����飬�����׵�ַ������LBP��  
	for(int i=0;i<width;i++)             //Ϊָ�������ÿ��Ԫ�ط���һ������
	{LBPData[i]=new int[height];}
	LBPFlag=1;

	cvCvtColor(m_cvImageRBG, m_cvImage, CV_BGR2GRAY);

	
}
void setup(IplImage* temp_image){
	m_cvImageRBG=temp_image;	
	m_cvImageRBGFlag=0;
	
	if(height==m_cvImageRBG->height&&width==m_cvImageRBG->width){
	}else{
	clear();	
	m_cvImage = cvCreateImage(cvSize(m_cvImageRBG->width, m_cvImageRBG->height), 8, 1);
    m_cvImageFlag=1;	
	height=m_cvImageRBG->height;
	width=m_cvImageRBG->width;	

	LBPData=new int*[width];    //����һ��ָ�����飬�����׵�ַ������LBP��  
	for(int i=0;i<width;i++)             //Ϊָ�������ÿ��Ԫ�ط���һ������
	{LBPData[i]=new int[height];}
	LBPFlag=1;

	}
	cvCvtColor(m_cvImageRBG, m_cvImage, CV_BGR2GRAY);
	
}

void transform(){
	
	if(m_cvImageFlag==0) {
		cout<<"CLBP::transform m_cvImageFlag==0"<<endl;
		exit(0);
	}




	/*������̬��άָ���ʾLBP����*/


	int center=0;
	int center_lbp=0;
	for (int row=1; row<m_cvImage->width-1; row++)
	{
		for (int col=1; col<m_cvImage->height-1; col++)
		{
			int lbp[8]={0,0,0,0,0,0,0,0};//����ֲ�lbp����ֵ
			center = (int)cvGetReal2D(m_cvImage, row, col);
			center_lbp=0; 
			if (center >= cvGetReal2D(m_cvImage, row-1, col-1))
			{
				center_lbp= 1;
				lbp[0]=center_lbp;
			}
			else 
			{
				center_lbp =0;
				lbp[0]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row-1, col))
			{
				center_lbp= 1;
				lbp[1]=center_lbp;
			}
			else 
			{
				center_lbp =0; 
				lbp[1]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row-1, col+1))
			{
				center_lbp= 1;
				lbp[2]=center_lbp;	
			}
			else 
			{
				center_lbp =0; 
				lbp[2]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row, col-1))
			{
				center_lbp= 1;
				lbp[3]=center_lbp;
			}
			else 
			{
				center_lbp = 0; 
				lbp[3]=center_lbp;	
			}

			if (center >= cvGetReal2D(m_cvImage, row, col+1))
			{
				center_lbp= 1;
				lbp[4]=center_lbp;
			}
			else 
			{
				center_lbp = 0; 
				lbp[4]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row+1, col-1))
			{
				center_lbp= 1;
				lbp[5]=center_lbp;	
			}
			else 
			{
				center_lbp = 0; 
				lbp[5]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row+1, col))
			{
				center_lbp=1;
				lbp[6]=center_lbp;
			}
			else 
			{
				center_lbp =0;
				lbp[6]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row+1, col+1))
			{
				center_lbp= 1;
				lbp[7]=center_lbp;	
			}
			else 
			{
				center_lbp = 0;
				lbp[7]=center_lbp;
			}
			if(row-1<0||row-1>=m_cvImageRBG->width)cout<<row-1<<"  x "<<m_cvImageRBG->width<<endl;
			if(col-1<0||col-1>=m_cvImageRBG->height)cout<<col-1<<" y  "<<m_cvImageRBG->height<<endl;
			LBPData[row-1][col-1]=bin2value(lbp,sizeof(lbp)/sizeof(lbp[0]));
		}
	}

	ComputingPro(m_cvImage->width,m_cvImage->height,LBPData);

	

	
}

void print(){
	cout<<"���LBP����ֵ�������ʣ�"<<endl;
	for(int t=0;t<DIM_OF_LBP;t++)
	{
		cout<<outPut[t]<<" ";
		if((t+1)%15==0)
			cout<<endl;
	}	
}

	void	LBP(string src_image_fl);
	void   LBP(IplImage* temp_image);

private:
	IplImage*			m_cvImageRBG;
	IplImage*			m_cvImage;
	int m_cvImageRBGFlag;	
	int m_cvImageFlag;	
	int height;
	int width;
	int **LBPData;
	int LBPFlag;
public:
	double outPut[DIM_OF_LBP];

};




/*
��LBP��������������ȡ�Ĳ���
��1�����Ƚ���ⴰ�ڻ���ΪN��N��С����cell������N �Ĵ�С��Ҫ�ǿ�ͼƬ�����أ�Ҳ����˵һ��cell����һ�����أ�
��2������cell�е����أ������ڵ�8�����صĻҶ�ֵ������бȽϣ�����Χ����ֵ������������ֵ��������ص��λ�ñ����Ϊ1������Ϊ0��
		������3*3�����ڵ�8���㾭�ȽϿɲ���8λ������������ת��Ϊ10�������������õ��ô����������ص��LBPֵ��
��3��Ȼ�����ÿ��cell��ֱ��ͼ����ÿ�����֣��ٶ���ʮ������LBPֵ�����ֵ�Ƶ�ʣ�Ȼ��Ը�ֱ��ͼ���й�һ�������˴���������ʣ���
��4����󽫵õ���ÿ��cell��ͳ��ֱ��ͼ�������ӳ�Ϊһ������������Ҳ��������ͼ��LBP��������������
*/


CLBP::CLBP(void)
{
	m_cvImageFlag=0;
	m_cvImageRBGFlag=0;
	height=0;
	width=0;
}
CLBP::~CLBP(void)
{
clear();
}





void CLBP::LBP(string src_image_fl){
	IplImage* temp_image = cvLoadImage(src_image_fl.c_str(), 1);// ��ȡͼƬ
	
	LBP(temp_image);
	cvReleaseImage(&temp_image);
}


void CLBP::LBP(IplImage* temp_image)
{
	
	m_cvImage = cvCreateImage(cvSize(temp_image->width, temp_image->height), 8, 1);

	if (temp_image->nChannels == 3)
	{
		cvCvtColor(temp_image, m_cvImage, CV_BGR2GRAY);
	}

	
	int r=m_cvImage->width,c=m_cvImage->height;


	/*������̬��άָ���ʾLBP����*/
	int **LBP=new int*[r-2];    //����һ��ָ�����飬�����׵�ַ������LBP��  
	for(int i=0;i<r-2;i++)             //Ϊָ�������ÿ��Ԫ�ط���һ������
		LBP[i]=new int[c-2];

	int center=0;
	int center_lbp=0;
	for (int row=1; row<c-1; row++)
	{
		for (int col=1; col<r-1; col++)
		{
			int lbp[8]={0,0,0,0,0,0,0,0};//����ֲ�lbp����ֵ
			center = (int)cvGetReal2D(m_cvImage, row, col);
			center_lbp=0; 
			if (center >= cvGetReal2D(m_cvImage, row-1, col-1))
			{
				center_lbp= 1;
				lbp[0]=center_lbp;
			}
			else 
			{
				center_lbp =0;
				lbp[0]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row-1, col))
			{
				center_lbp= 1;
				lbp[1]=center_lbp;
			}
			else 
			{
				center_lbp =0; 
				lbp[1]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row-1, col+1))
			{
				center_lbp= 1;
				lbp[2]=center_lbp;	
			}
			else 
			{
				center_lbp =0; 
				lbp[2]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row, col-1))
			{
				center_lbp= 1;
				lbp[3]=center_lbp;
			}
			else 
			{
				center_lbp = 0; 
				lbp[3]=center_lbp;	
			}

			if (center >= cvGetReal2D(m_cvImage, row, col+1))
			{
				center_lbp= 1;
				lbp[4]=center_lbp;
			}
			else 
			{
				center_lbp = 0; 
				lbp[4]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row+1, col-1))
			{
				center_lbp= 1;
				lbp[5]=center_lbp;	
			}
			else 
			{
				center_lbp = 0; 
				lbp[5]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row+1, col))
			{
				center_lbp=1;
				lbp[6]=center_lbp;
			}
			else 
			{
				center_lbp =0;
				lbp[6]=center_lbp;
			}

			if (center >= cvGetReal2D(m_cvImage, row+1, col+1))
			{
				center_lbp= 1;
				lbp[7]=center_lbp;	
			}
			else 
			{
				center_lbp = 0;
				lbp[7]=center_lbp;
			}
			LBP[row-1][col-1]=bin2value(lbp,sizeof(lbp)/sizeof(lbp[0]));
		}
	}

	ComputingPro(r,c,LBP);
	cout<<"���LBP����ֵ�������ʣ�"<<endl;
	for(int t=0;t<DIM_OF_LBP;t++)
	{
		cout<<outPut[t]<<" ";
		if((t+1)%15==0)
			cout<<endl;
	}
	
	/*�ͷŶ�ά��̬����LBP*/
	  for(int i=0;i<r-2;i++)
	  {
		  delete [c-2]LBP[i];
		  LBP[i]=NULL;
	  }
	  delete [r-2]LBP;
	  LBP=NULL;

	 system("pause");

	cvWaitKey(0);

} 
