//#include"detectline.h"
#include"lib.h"
#include"math.h"

///
///class  TestDetectPoint
///��ҪĿ�ģ�̽�����ص�ı�Ե����
///
class TestDetectPoint
{
public:
	///
	///getdetectedge ����  ����ԭͼ �뻭̽���ߺ���ڹ۲��ͼƬ
	///
	void getdetectedge(IplImage *src,IplImage *dst)
	{
		///
		///����DetectLine�����dll
		///
				DetectLine dll;
            ///
		   ///����CvPoint������ pp��
		   ///pp��Ϊ��Ҫ��̽��Ľǵ�����
		   ///
				CvPoint pp;//pp��Ϊ��Ҫ��̽�������˽���ĵĽǵ�����
				pp.x=380;pp.y=57;

			///
		   ///����CvPoint������ p1��
		   ///p1��Ϊ��Ҫ��̽��Ľǵ�����·��Ľǵ�����
		   ///����ȷ��̽���߽Ƕ�
		   ///
				CvPoint p1;//p1��Ϊ��Ҫ��̽��Ľǵ�����·��Ľǵ�����
				p1.x=383;p1.y=197;


				float k1=(-1)*float((p1.y-pp.y)/(p1.x-pp.x));//��ȡ�����ص���ϵ�б��

				double s1=atan((double)(k1))/CV_PI*180;//��ȡ�����ص���ϵĽǶ�

				double sita1=atan((double)(-1/k1))/CV_PI*180;//��ȡ��̽���ߵĽǶ�

				vector<double>xyx;//�洢��Ե�����x��y����
				vector<double>xyy;
		      cvCircle(dst,pp,10, CV_RGB(255,0,0), 1,8,0);//��dst�ϻ�̽����
			  ///
			  ///����ѭ����y����70��̽����
			  ///
			  for(int i=10;i<80;i++)//����ѭ����y����70��̽����
			  {
				 CvPoint po;
				 po.x=pp.x-i*cos((sita1)*CV_PI/180.0); po.y=pp.y+i*sin((sita1)*CV_PI/180.0);//ͨ��������ص�Ƕ�����ȡ��Ҫ��̽������ص�
				 xyy=dll.detectlinedegree(po,(s1),5,src,dst);
				 ydetectpoint.push_back(xyy[0]);//�洢y�����x����
				 ydetectpoint.push_back(xyy[1]);//�洢y�����y����
				 py.push_back(po);//�洢y�������ص�
			  }
			   ///
			  ///����ѭ����x����90��̽����
			  ///
			   for(int i=10;i<100;i++)//����ѭ����x����90��̽����
			  {
				  CvPoint po;
				  po.x=pp.x+i*cos((-s1)*CV_PI/180.0); po.y=pp.y+i*sin((-s1)*CV_PI/180.0);//ͨ��������ص�Ƕ�����ȡ��Ҫ��̽������ص�
				 xyx=dll.detectlinedegree(po,(-sita1),5,src,dst);//����dll�ĺ���detectlinedegree��ȡ��Ե����
				 xdetectpoint.push_back(xyx[0]);//�洢y�����x����
				 xdetectpoint.push_back(xyx[1]);//�洢y�����y����
				 px.push_back(po);//�洢x�������ص�
			  }
			   cvShowImage( "dst", dst );//  show  the  IplImage *dst

	}

public:
///
///��������
///
vector<CvPoint> px;//�洢y�������ص�
vector<CvPoint> py;//�洢x�������ص�
vector<double> xdetectpoint;//���峣�����������ʼ����
vector<double> ydetectpoint;//�洢��Ե��������


};