#pragma once

#include "lib.h"

/*=======================================================================*/  

////////////////////////////////////////////////////////////////////////////////  
//#define  MAXNUM  50   //����������������������Ϊ50��  



class spline    //���������ṹ�壬���ڴ洢һ��������������Ϣ  
{ //��ʼ����������  
public:
spline(int n){
x=new double[n+1];
 y=new double[n+1];
 k1=new double[n+1];
 k2=new double[n+1];
 a3=new double[n];
 a1=new double[n];
 b3=new double[n];
 b1=new double[n];
H=new double[n];     //С����Ĳ���  
Fi=new double[n];     //�м���  
U=new double[n+1];    //�м���  
A=new double[n+1];    //�м���  
D=new double[n+1];    //�м���  
M=new double[n+1];    //M����  
B=new double[n+1];    //׷�Ϸ��м���  
Y=new double[n+1];    //׷�Ϸ��м����  
 MAXNUM=n;	
}
~spline(){
delete []x;
delete []y;
delete []k1;
delete []k2;
delete []a3;
delete []a1;
delete []b3;
delete []b1;
 delete [] H;
 delete [] Fi;
 delete [] U;
 delete [] A;
 delete [] D;
 delete [] M;
 delete [] B;
 delete [] Y;
}
int MAXNUM;
 double *x;    //�洢�����ϵĵ��x���꣬���51����  
 double *y;    //�洢�����ϵĵ��y���꣬���51����  
 unsigned int point_num;   //�洢�����ϵ�ʵ�ʵ� �� �ĸ���  
 double begin_k1;     //��ʼ���һ�׵�����Ϣ  
 double end_k1;     //��ֹ���һ�׵�����Ϣ  
 //double begin_k2;    //��ʼ��Ķ��׵�����Ϣ  
 //double end_k2;     //��ֹ��Ķ��׵�����Ϣ  
 //�������õ���������S(x)  
 double *k1;    //���е��һ�׵�����Ϣ  
 double *k2;    //���е�Ķ��׵�����Ϣ  
 //51����֮����50���Σ�func[]�洢ÿ�εĺ���ϵ��  
 double *a3;
 double *a1;
 double *b3;
 double *b1;

 double *H;
 double *Fi;
 double *U;
 double *A;
 double *D;
 double *M;
 double *B;
 double *Y;
 
 
 int xbin(double a){
	int i=-1;
	for(i = 0;i < point_num;i++){
		if(x[i]>a&&i==0) return 0;
		if(x[i]<=a&&x[i+1]>a) break;
	}
	if(i>=point_num-1)	return point_num-2;	
	//cout<<"xbin= "<<i<<endl;
	return i;	 
	 
 }
 
 double si(double a){
	 int i=xbin(a);
	 return a3[i] * pow(x[i+1] - a,3)  + a1[i] * (x[i+1] - a) +  
        b3[i] * pow(a - x[i],3) + b1[i] * (a - x[i]) ;
 }
 
 
void set_end(){
	begin_k1=(y[1]-y[0])/(x[1]-x[0]);
	end_k1=(y[point_num-1]-y[point_num-2])/(x[point_num-1]-x[point_num-2]);
} 
 
int spline3()  
{  

 int i = 0;  
 ////////////////////////////////////////�����м����  
 if((point_num < 3) || (point_num > MAXNUM + 1))  
 {  
  return -2;       //�������ݵ����̫�ٻ�̫��  
 }  
 for(i = 0;i <= point_num - 2;i++)  
 {          //��H[i]  
  H[i] = x[i+1] - x[i];  
  Fi[i] = (y[i+1] - y[i]) / H[i]; //��F[x(i),x(i+1)]  
 }  
 for(i = 1;i <= point_num - 2;i++)  
 {          //��U[i]��A[i]��D[i]  
  U[i] = H[i-1] / (H[i-1] + H[i]);  
  A[i] = H[i] / (H[i-1] + H[i]);  
  D[i] = 6 * (Fi[i] - Fi[i-1]) / (H[i-1] + H[i]);  
 }  
 //���߽�����Ϊ1����������  
 U[i] = 1;  
 A[0] = 1;  
 D[0] = 6 * (Fi[0] - begin_k1) / H[0];  
 D[i] = 6 * (end_k1 - Fi[i-1]) / H[i-1];  
 //���߽�����Ϊ2����������  
 //U[i] = 0;  
 //A[0] = 0;  
 //D[0] = 2 * begin_k2;  
 //D[i] = 2 * end_k2;  
 /////////////////////////////////////////׷�Ϸ����M����  
 B[0] = A[0] / 2;  
 for(i = 1;i <= point_num - 2;i++)  
 {  
  B[i] = A[i] / (2 - U[i] * B[i-1]);  
 }  
 Y[0] = D[0] / 2;  
 for(i = 1;i <= point_num - 1;i++)  
 {  
  Y[i] = (D[i] - U[i] * Y[i-1]) / (2 - U[i] * B[i-1]);  
 }  
 M[point_num - 1] = Y[point_num - 1];  
 for(i = point_num - 1;i > 0;i--)  
 {  
  M[i-1] = Y[i-1] - B[i-1] * M[i];  
 }  
 //////////////////////////////////////////���㷽�������ս��  
 for(i = 0;i <= point_num - 2;i++)  
 {  
  a3[i] = M[i] / (6 * H[i]);  
  a1[i] = (y[i] - M[i] * H[i] * H[i] / 6) / H[i];  
  b3[i] = M[i+1] / (6 * H[i]);  
  b1[i] = (y[i+1] - M[i+1] * H[i] * H[i] / 6) /H[i];  
 }

 
 return 1;  
}  
 
 
 
 //�ֶκ�������ʽΪ Si(x) = a3[i] * {x(i+1) - x}^3  + a1[i] * {x(i+1) - x} +  
 //        b3[i] * {x - x(i)}^3 + b1[i] * {x - x(i)}  
 //xiΪx[i]��ֵ��xi_1Ϊx[i+1]��ֵ        
};


////////////////////////////////////////////////////////////////////////////  

