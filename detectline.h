#include"lib.h"

//!  a DetectLine class
class DetectLine
{

public:
	//���캯��
	DetectLine(){};

	
vector<CvScalar> getrgb(double x,double y,IplImage* src)
{


	 vector<CvScalar> ps;//����һCvScalar�������ڴ洢�ĸ����ص��rgbֵ
	 ps.clear();//��ռ���
	 
	 ps.push_back(cvGet2D(src,(int)(y),int(x)));//int(x,y)���ص��rgbֵ
	 ps.push_back(cvGet2D(src,(int)(y+1),int(x)));//int(x,y+1)���ص��rgbֵ
	 ps.push_back(cvGet2D(src,(int)y,int(x+1)));//int(x+1,y)���ص��rgbֵ
	 ps.push_back(cvGet2D(src,(int)(y+1),int(x+1)));//int(x+1,y+1)���ص��rgbֵ

	 return ps;

}

//vector<double>pointsx,vector<double>pointsy  ̽�����������ص�xy���꼯��
void getpixelrgb(vector<double>pointsx,vector<double>pointsy,IplImage* src)//��ȡ̽�����������ص��rgbֵ
{
	   bb.clear();///vector clear
	   gg.clear();
	   rr.clear();
	 CvPoint* pp=new CvPoint[4];
	 double sum=0;
	 double b=0;
	 double g=0;
	 double r=0;
	  int pmin ;//�����Сֵ
	  int min;//������Сֵ

	 //��ȡ�����ص��rgbֵ
		for(int i=0;i<pointsx.size();i++)
		{
			vector<CvScalar>prgb=getrgb(pointsx[i],pointsy[i],src);//��ȡ���ص���Χ��4�����ص��rgb��
			if((pointsx[i]==int(pointsx[i]))&&(pointsy[i]==int(pointsy[i]))){bb.push_back(prgb[0].val[0]);gg.push_back(prgb[0].val[1]);rr.push_back(prgb[0].val[2]);}
			else
			{
				pp[0].x=int(pointsx[i]);pp[0].y=int(pointsy[i]);//int(x,y)���ص�
				pp[1].x=int(pointsx[i]);pp[1].y=int(pointsy[i]+1);//int(x,y+1)���ص�
				pp[2].x=int(pointsx[i]+1);pp[2].y=int(pointsy[i]);//int(x+1,y)���ص�
				pp[3].x=int(pointsx[i]+1);pp[3].y=int(pointsy[i]+1);//int(x+1,y+1)���ص�

			 vector<double> L;//�洢���ص������Χ�ĸ����ص����еľ���

				for(int j=0;j<4;j++)//��������ص�����Χ4�����ص�ľ���
				{	  
				   L.push_back((pointsx[i]-pp[j].x)*(pointsx[i]-pp[j].x)+(pointsy[i]-pp[j].y)*(pointsy[i]-pp[j].y));
				   //cout<<"L="<<L[j]<<endl;
				}
             for(int k=0;k<L.size();k++)//��ȡ���������ص��������int�����ص�ľ���֮��
			 {
				 sum+=L[k];//���

			 }
			// cout<<"sum="<<sum<<endl;
			 for(int k=0;k<prgb.size();k++)//�Ѹ��������ص��������int�����ص��rgb�������Ȩƽ��ֵ�������������ص�rgbֵ
			 {
				b+=prgb[k].val[0]*(L[k]/sum);//bֵ
				g+=prgb[k].val[1]*(L[k]/sum);//gֵ
				r+=prgb[k].val[2]*(L[k]/sum);//rֵ
			 }
			 bb.push_back(b);//�洢bֵ
			 gg.push_back(g);//�洢gֵ
			 rr.push_back(r);//�洢rֵ
			}
		}



}

///
///����getedgepix ���ڻ�ȡ���ص�ı�Ե���ص�
///���� ��̽������ص�����
///
vector<double> getedgepix(CvPoint point)
{

	  vector<double> XY;// vector<double> XY is to store the xy coordinate of accurate point
	  XY.clear();//vector clear


 	 vector<double> bgr;//���ڴ洢bgr�ļ�Ȩƽ��ֵ
	 bgr.clear();//vector clear

	 CvScalar ss;//define the object of CvScalar

	  vector<double> dd;//vector<double> dd �����洢����rgb�Ĳ�ֵ
	  dd.clear();//���

	  int aa=0;//�����ж����
	  double m=0;//�����ж����

	 double x=0;double y=0;//��Ե��������
	 int p1=0;int p2=0; //rbg��ֵ���ֵ�ʹδ�ֵ��Ӧ�����ص�
	 int a=0;//�������ֲ�ֵ�����ı���



		 for(int i=0;i<bb.size();i++)//�ı�bgrֵ��Ϊ����ǿ�ź�
	 {
		 double aveage=(bb[i]+gg[i]+rr[i]);//̽������ÿ�����ص��rgb�ļ�Ȩƽ��ֵ
		 if(aveage!=0)
		 {bgr.push_back((bb[i]*(bb[i]/aveage)+gg[i]*(gg[i]/aveage)+rr[i]*(rr[i]/aveage)));}//bgr�洢��bgr�ļ�Ȩƽ��ֵ
		 else{bgr.push_back(0);}
   		 ss.val[0]=ss.val[1]=ss.val[2]=bgr[i];//��̽������ÿ�����ص�ĵ�bgr�ֱ�����ͬһ��ֵ��Ϊbgr�ļ�Ȩƽ��ֵ
		 //cvSet2D(detect,points[i].y,points[i].x,s1);///��ԭͼ̽�����ϵ����ص�����Ϊ�ı���rgbֵ�����ص�
	 }
     



	for(int i=0;i<bb.size()-1;i++)//for ���ڴ洢̽�������������صĲ�ֵ
	 {
		 dd.push_back(abs(bgr[i]-bgr[i+1]));//ddΪ̽�������������ص�rgb�Ĳ�ֵ
	 
	 }

	 

	for(int i=0;i<dd.size();i++)//ȡrgb��ֵ�����ֵ
	{

		if(dd[i]>m){ m=dd[i];}//ѡȡ������֮���rgbֵ�Ĳ�ֵ�����ֵ
		/**aa  �����ж�̽�����ϵĵ��rgbֵ�Ƿ��б仯���û�б仯��˵��̽�����ϲ�û�б�Ե��
		*���aa ��size==dd.size()-1  ��˵����û�б�Ե����̽������
		*ֻ�е�aa<dd.size()-1 ʱ��˵��̽�����ϵ�����������֮���rgb��ֵ����2  ���б�Ե�����
		*/
		if(dd[i]<2){aa++;}
	}
	
	
	if(aa<(dd.size()-1))//�����ifѭ���ڵ�˵���б�Ե��
	{
		
        /**˫��forѭ�������ж����ص�rgb��ֵ���м������ֵ
		*������������ֵ ����Ҫ�������ֵ��Ӧ���������ֵ
		*��ֻ��һ�����ֵ������ȡ���ӽ����ֵ��Χ�Ĵδ�ֵ��������Ϊ�����ߵļ�Ȩƽ������
			*/
		for(int i=0;i<dd.size();i++)
		{
			
			for(int j=(dd.size()-1);j>i;j--)
			{
					if((dd[i]==m)&&(dd[j]==m))//˵��rgb��ֵ�����������������ֵ
				  {
					 a=1;
					{
						 x=(double)(pointsx[i]+pointsx[j+1])/2;//��ȡ���������ֵ����ֵ��Ϊ��Ե�����ľ�ȷ����
						 y=(double)(pointsy[i]+pointsy[j+1])/2;
					 }

				   XY.push_back(x);//�ѱ�Ե��x���괫�ݸ�vectorXY[0]
				   XY.push_back(y);//�ѱ�Ե��y���괫�ݸ�vectorXY[1]
				     break;
				  }
			 }
		}
	

			if(a==0)//��˵��ֻ��һ�����ֵ
			{
		
				for(int i=0;i<dd.size();i++)
				{
					if(dd[i]==m)//ѡȡ���ĸ������Ϊ���ֵ
					{
						p1=i+1;//p1��Ϊӵ��rgb��ֵ���������
					}
				 }

					double mm=0;
					for(int c=0;c<dd.size();c++)
					{
						if(c!=p1-1)
						{
							
							if(dd[c]>mm){mm=dd[c];}//ѡȡ����ֵ�г����ֵ֮��Ĵδ�ֵ
						}
						
					}
										
					for(int h=0;h<dd.size();h++)
					{
							if(dd[h]==mm)
						{
							p2=h+1;//p2��Ϊrgb��ֵΪ�δ�ֵ�������
						
						}
					}

					double ave=(bgr[p1]+bgr[p2]);

					x=(pointsx[p1]*(bgr[p1]/ave))+(pointsx[p2]*(bgr[p2]/ave));//��ȡ����ֵ���ֵ��δ�ֵ�ļ�Ȩƽ��ֵ��Ϊ��Ե������
					y=(pointsy[p1]*(bgr[p1]/ave))+(pointsy[p2]*(bgr[p2]/ave));

				   XY.push_back(x);//�ѱ�Ե��x���괫�ݸ�vectorXY[0]
				   XY.push_back(y);//�ѱ�Ե��y���괫�ݸ�vectorXY[1]
				   			
	            }
	}
	else{
		   cout<<"ERROR=="<<point.x<<"  "<<point.y<<"���������м�û�б�Ե��"<<endl;				
	       XY.push_back(point.x);//�ѱ�Ե��x���괫�ݸ�vectorXY[0]
		   XY.push_back(point.y);//�ѱ�Ե��y���괫�ݸ�vectorXY[1]
           
	    }
	return  XY;


}



///
///CvPoint point int�����ص�����   vector<double>pointsx,vector<double>pointsy�洢̽�������ص�xy���� int distance̽���߳���
///
vector<double> detectline(CvPoint point,vector<double>pointsx,vector<double>pointsy,int distance,IplImage* src,IplImage* dst)//src ��ԭͼ
{


	//.............................����������.............................................//
	  CvPoint X,Y;	//����̽�������Ҷ˵��Ա�����dst�ϻ���
	  vector<double> XY;// vector<double> XY is to store the xy coordinate of accurate point
	  XY.clear();//vector clear

//....................................................................................................//

	 X.x=pointsx[0];X.y=pointsy[0];//XY�ֱ�Ϊ���˶˵㣬ת��Ϊint �������ͽ�Ϊ�˻�ֱ�ߺÿ� 
	Y.x=pointsx[2*distance];Y.y=pointsy[2*distance];//YΪ̽�����Ҷ˶ϵ�

	cvLine(dst,X,Y,CV_RGB(255,0,0),1,8,0);//��XY�������� 	
	getpixelrgb(pointsx,pointsy,src);//��ȡ̽�������ص�rgbֵ

	  XY=getedgepix(point);//��ȡ��Ե����	 
	  return XY;//return   ��Ե��xy����

}
///
///CvPoint x��̽���ߵ��м����ص�    double degree��̽���ߵĽǶȣ���ֵΪ���£���ֵ���ϣ� IplImage *src--����ԭͼ  IplImage *dst--Ϊ����̽���ߵ�ͼƬ
///
 vector<double> detectlinedegree(CvPoint x,double degree,int distance,IplImage *src,IplImage *dst)
{

	vector<double>XY;//���弯�����ڴ洢̽�⵽�ı�Ե���ص�����
	XY.clear();//��ռ���
	///
	///����getdetectpoints����ȡ̽�������������ص�����
	///
	getdetectpoints(x,degree,distance);	 
	///
	///����detectline��������ȡ��Ե���ص����겢�洢�ڼ���XY��
	///
	XY=detectline(x,pointsx,pointsy,distance,src,dst);
	
	return XY;


}

 ///
 ///getdetectpoints�������ڻ�ȡ̽���������е����ص�����
 ///CvPoint x ����̽���ߵ��е�����  degreeΪ̽���߽Ƕ�  distanceΪ̽���߳��ȵ�һ��
 ///
void getdetectpoints(CvPoint x,double degree,int distance)
{
	  ///
	  ///̽���߱�����ֱ�ߣ�������̽���߻�������б�ģ���̽�����ϵĵ������double������
	  ///
		double* x1=new double[distance]; double* y1=new double[distance];//Ϊ̽���ߵ�������ص�
        double* x2=new double[distance]; double* y2=new double[distance];//Ϊ̽���ߵ��Ҷ����ص�

		pointsx.clear();//�洢̽�������˵�
		pointsy.clear();//�洢̽�����Ҳ�˵�

    if(degree<=0)//��̽���߽Ƕ�С�ڻ����0ʱ
	{
		for(int i=0;i<distance;i++)//��x1��Ϊx���ص��ϰ벿�֣�x2Ϊx���°벿��
		{
			x1[i]=x.x-((distance-i)*cos(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����
			y1[i]=x.y+((distance-i)*sin(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����

			x2[i]=x.x+((i+1)*cos(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����
			y2[i]=x.y-((i+1)*sin(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����
		
		}
	}
	else//��̽���߽Ƕ�Ϊ��ʱ
	{    for(int i=0;i<distance;i++)//��x1��Ϊx���ص��ϰ벿�֣�x2Ϊx���°벿��
		{

			x1[i]=x.x+((distance-i)*cos(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����
			y1[i]=x.y-((distance-i)*sin(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����

			x2[i]=x.x-((i+1)*cos(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����
			y2[i]=x.y+((i+1)*sin(degree*CV_PI/180.0));//����̽���߽Ƕ���̽���߳�������ȡ̽�������������ص�����

		}

	}

		for(int i=0;i<distance;i++)//��̽���������ص㶼�洢�ڼ���pointsx��pointsy
		{
			pointsx.push_back(x1[i]);
			pointsy.push_back(y1[i]);
		}
		  pointsx.push_back(x.x);//��̽�����е����ص�洢�ڼ���pointsx��pointsy
		  pointsy.push_back(x.y);
		for(int k=0;k<distance;k++)//��̽���������ص㶼�洢�ڼ���pointsx��pointsy
		{
			pointsx.push_back(x2[k]);
			pointsy.push_back(y2[k]);
		}


		delete x1;delete x2;//ɾ����̬����ռ�
		delete y1; delete y2;

}

private:
///
///˽�б���  
///
	vector<double> pointsx;//�洢̽�������������ص�����
	vector<double> pointsy;//�洢̽�������������ص�����
	 vector<double> bb;//�洢��ԭͼ��̽�����ϵ�ÿ�����ص��bֵ 
     vector<double> gg;//�洢��ԭͼ��̽�����ϵ�ÿ�����ص��gֵ 
	 vector<double> rr;//�洢��ԭͼ��̽�����ϵ�ÿ�����ص��rֵ 

};