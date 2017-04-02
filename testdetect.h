#include"lib.h"
#include"commomfunction.h"

///
///class TestDetect ���ڼ����̽����̽���Ե���ص��rms��ƽ��ֵ
///
class TestDetect
{
public:
	///
	///calcpointyrms�������ڼ���y�����rms��ƽ��ֵ  ���뱻̽������ص�����  ����̽���ı�Ե���ص�����
	///
void calcpointrms(vector<CvPoint> p,vector<double> pd)
{
	    ///
	    ///���� CommomFunction class ����
	    ///
	    CommomFunction  cf;

		vector<double> yx;//���ڴ洢y�����Ե���ص�x����
		vector<double> yy;//���ڴ洢y�����Ե���ص�y����


		yx.clear(); yy.clear();//���

		
		bool* flag=new bool[p.size()];//����flag����

		for(int k=0;k<p.size();k++)//forѭ�����ڼ���rms
		{
			vector<double> px;
			vector<double> py;
			px.clear();
			py.clear();
								
				 for(int j=k+1;j<p.size();j++)//forѭ������ɸѡ����ͬ���ص㱻̽���ı�Ե���ص���ڼ���rms
				{
					if(flag[k]==true){k++;break;}//����Ѿ���ѡ��������ֱ�Ӳ�����ѭ��
			   else{
				    if((p[k].x==p[j].x)&&(p[k].y==p[j].y))//��vector p�������ֵ���ʱ�洢���ı���
				  {
					  
					  flag[j]=true;	///flag�������ڱ��			
					  px.push_back(pd[j*2]);//�洢x����
					  py.push_back(pd[j*2+1]);//�洢y����
				

				  }
			      }//else
	           }//forѭ���Ѿ�������
                //��ȡRMSE
				 
			if(((px.size()!=0)&&(px.size()>50))&&((py.size()!=0)&&(py.size()>50)))//ÿ�λ�ѡȡ100֡��sizeС��һ�����Ϊ���ȶ�����
			{
				double deta=cf.getrmse(px);//��ȡ���ص�rms
				yx.push_back(deta);//�洢��yx

				double deta1=cf.getrmse(py);//��ȡ���ص�rms
				yy.push_back(deta1);//�洢��yy

			}
										
          }


		double sum=0;
		for(int i=0;i<yx.size();i++)//�����������ص��rms�ĺ�
		{
			 sum+=yx[i];//��x�����

		}
		double meanx=sum/yx.size();
		cout<<"meanx==="<<meanx<<endl;//�����������ص��rms��ƽ��ֵ

		double sumy=0;
		for(int i=0;i<yy.size();i++)//�����������ص��rms�ĺ�
		{
			 sumy+=yy[i];//��y�����

		}
		double meany=sumy/yy.size();//�����������ص��rms��ƽ��ֵ
     cout<<"meany==="<<meany<<endl;


}

};