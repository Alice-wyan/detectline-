#include"lib.h"

class  CommomFunction
{
public:

double getrmse(vector<double> xx)//����getrmse���ڻ�ȡ����xx��rmsֵ
{
        double sum=0;
		double ave=0;
	for(int a=0;a<xx.size();a++)//�����ƽ��ֵ
	{
		
		ave+=xx[a];
	}
	for(int i=0;i<xx.size();i++)//�����rmseֵ
	{
		
			//cout<<"ave== "<<ave/xx.size()<<endl;
			//cout<<"sum "<<ave/n<<endl;
			sum+=(xx[i]-(ave/xx.size()))*(xx[i]-(ave/xx.size()));//���빫ʽ	
	}
	

  double deta=sqrt((double)(sum/xx.size()));//��ȡ��ÿ�����ص��rmseֵ
  //	cout<<"deta== "<<deta<<endl;
  return deta;//����rmseֵ
}
};