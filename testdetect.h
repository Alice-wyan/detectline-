#include"lib.h"
#include"commomfunction.h"

///
///class TestDetect 用于计算出探测线探测边缘像素点的rms的平均值
///
class TestDetect
{
public:
	///
	///calcpointyrms函数用于计算y方向的rms的平均值  输入被探测的像素点坐标  输入探测后的边缘像素点坐标
	///
void calcpointrms(vector<CvPoint> p,vector<double> pd)
{
	    ///
	    ///定义 CommomFunction class 对象
	    ///
	    CommomFunction  cf;

		vector<double> yx;//用于存储y方向边缘像素点x坐标
		vector<double> yy;//用于存储y方向边缘像素点y坐标


		yx.clear(); yy.clear();//清空

		
		bool* flag=new bool[p.size()];//定义flag数组

		for(int k=0;k<p.size();k++)//for循环用于计算rms
		{
			vector<double> px;
			vector<double> py;
			px.clear();
			py.clear();
								
				 for(int j=k+1;j<p.size();j++)//for循环用于筛选出相同像素点被探测后的边缘像素点便于计算rms
				{
					if(flag[k]==true){k++;break;}//如果已经被选出来后则直接不进入循环
			   else{
				    if((p[k].x==p[j].x)&&(p[k].y==p[j].y))//当vector p里的像素值相等时存储进文本框
				  {
					  
					  flag[j]=true;	///flag数组用于标记			
					  px.push_back(pd[j*2]);//存储x坐标
					  py.push_back(pd[j*2+1]);//存储y坐标
				

				  }
			      }//else
	           }//for循环已经把所有
                //求取RMSE
				 
			if(((px.size()!=0)&&(px.size()>50))&&((py.size()!=0)&&(py.size()>50)))//每次会选取100帧则size小于一半的则为不稳定像素
			{
				double deta=cf.getrmse(px);//获取像素点rms
				yx.push_back(deta);//存储进yx

				double deta1=cf.getrmse(py);//获取像素点rms
				yy.push_back(deta1);//存储进yy

			}
										
          }


		double sum=0;
		for(int i=0;i<yx.size();i++)//计算所有像素点的rms的和
		{
			 sum+=yx[i];//求x坐标和

		}
		double meanx=sum/yx.size();
		cout<<"meanx==="<<meanx<<endl;//计算所有像素点的rms的平均值

		double sumy=0;
		for(int i=0;i<yy.size();i++)//计算所有像素点的rms的和
		{
			 sumy+=yy[i];//求y坐标和

		}
		double meany=sumy/yy.size();//计算所有像素点的rms的平均值
     cout<<"meany==="<<meany<<endl;


}

};