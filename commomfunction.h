#include"lib.h"

class  CommomFunction
{
public:

double getrmse(vector<double> xx)//函数getrmse用于获取集合xx的rms值
{
        double sum=0;
		double ave=0;
	for(int a=0;a<xx.size();a++)//先算出平均值
	{
		
		ave+=xx[a];
	}
	for(int i=0;i<xx.size();i++)//计算出rmse值
	{
		
			//cout<<"ave== "<<ave/xx.size()<<endl;
			//cout<<"sum "<<ave/n<<endl;
			sum+=(xx[i]-(ave/xx.size()))*(xx[i]-(ave/xx.size()));//代入公式	
	}
	

  double deta=sqrt((double)(sum/xx.size()));//求取出每个像素点的rmse值
  //	cout<<"deta== "<<deta<<endl;
  return deta;//返回rmse值
}
};