//#include"detectline.h"
#include"lib.h"
#include"math.h"

///
///class  TestDetectPoint
///主要目的：探测像素点的边缘坐标
///
class TestDetectPoint
{
public:
	///
	///getdetectedge 函数  输入原图 与画探测线后便于观察的图片
	///
	void getdetectedge(IplImage *src,IplImage *dst)
	{
		///
		///定义DetectLine类对象dll
		///
				DetectLine dll;
            ///
		   ///定义CvPoint数据型 pp，
		   ///pp即为需要被探测的角点坐标
		   ///
				CvPoint pp;//pp即为需要被探测线两端交点的的角点坐标
				pp.x=380;pp.y=57;

			///
		   ///定义CvPoint数据型 p1，
		   ///p1即为需要被探测的角点的由下方的角点坐标
		   ///用于确定探测线角度
		   ///
				CvPoint p1;//p1即为需要被探测的角点的由下方的角点坐标
				p1.x=383;p1.y=197;


				float k1=(-1)*float((p1.y-pp.y)/(p1.x-pp.x));//求取出像素点拟合的斜率

				double s1=atan((double)(k1))/CV_PI*180;//求取出像素点拟合的角度

				double sita1=atan((double)(-1/k1))/CV_PI*180;//求取出探测线的角度

				vector<double>xyx;//存储边缘坐标的x、y坐标
				vector<double>xyy;
		      cvCircle(dst,pp,10, CV_RGB(255,0,0), 1,8,0);//在dst上画探测线
			  ///
			  ///利用循环在y方向画70条探测线
			  ///
			  for(int i=10;i<80;i++)//利用循环在y方向画70条探测线
			  {
				 CvPoint po;
				 po.x=pp.x-i*cos((sita1)*CV_PI/180.0); po.y=pp.y+i*sin((sita1)*CV_PI/180.0);//通过拟合像素点角度来获取需要被探测的像素点
				 xyy=dll.detectlinedegree(po,(s1),5,src,dst);
				 ydetectpoint.push_back(xyy[0]);//存储y方向的x坐标
				 ydetectpoint.push_back(xyy[1]);//存储y方向的y坐标
				 py.push_back(po);//存储y方向像素点
			  }
			   ///
			  ///利用循环在x方向画90条探测线
			  ///
			   for(int i=10;i<100;i++)//利用循环在x方向画90条探测线
			  {
				  CvPoint po;
				  po.x=pp.x+i*cos((-s1)*CV_PI/180.0); po.y=pp.y+i*sin((-s1)*CV_PI/180.0);//通过拟合像素点角度来获取需要被探测的像素点
				 xyx=dll.detectlinedegree(po,(-sita1),5,src,dst);//调用dll的函数detectlinedegree获取边缘像素
				 xdetectpoint.push_back(xyx[0]);//存储y方向的x坐标
				 xdetectpoint.push_back(xyx[1]);//存储y方向的y坐标
				 px.push_back(po);//存储x方向像素点
			  }
			   cvShowImage( "dst", dst );//  show  the  IplImage *dst

	}

public:
///
///公共变量
///
vector<CvPoint> px;//存储y方向像素点
vector<CvPoint> py;//存储x方向像素点
vector<double> xdetectpoint;//定义常量与变量并初始化。
vector<double> ydetectpoint;//存储边缘像素坐标


};