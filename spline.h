#pragma once

#include "lib.h"

/*=======================================================================*/  

////////////////////////////////////////////////////////////////////////////////  
//#define  MAXNUM  50   //定义样条数据区间个数最多为50个  



class spline    //定义样条结构体，用于存储一条样条的所有信息  
{ //初始化数据输入  
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
H=new double[n];     //小区间的步长  
Fi=new double[n];     //中间量  
U=new double[n+1];    //中间量  
A=new double[n+1];    //中间量  
D=new double[n+1];    //中间量  
M=new double[n+1];    //M矩阵  
B=new double[n+1];    //追赶法中间量  
Y=new double[n+1];    //追赶法中间变量  
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
 double *x;    //存储样条上的点的x坐标，最多51个点  
 double *y;    //存储样条上的点的y坐标，最多51个点  
 unsigned int point_num;   //存储样条上的实际的 点 的个数  
 double begin_k1;     //开始点的一阶导数信息  
 double end_k1;     //终止点的一阶导数信息  
 //double begin_k2;    //开始点的二阶导数信息  
 //double end_k2;     //终止点的二阶导数信息  
 //计算所得的样条函数S(x)  
 double *k1;    //所有点的一阶导数信息  
 double *k2;    //所有点的二阶导数信息  
 //51个点之间有50个段，func[]存储每段的函数系数  
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
 ////////////////////////////////////////计算中间参数  
 if((point_num < 3) || (point_num > MAXNUM + 1))  
 {  
  return -2;       //输入数据点个数太少或太多  
 }  
 for(i = 0;i <= point_num - 2;i++)  
 {          //求H[i]  
  H[i] = x[i+1] - x[i];  
  Fi[i] = (y[i+1] - y[i]) / H[i]; //求F[x(i),x(i+1)]  
 }  
 for(i = 1;i <= point_num - 2;i++)  
 {          //求U[i]和A[i]和D[i]  
  U[i] = H[i-1] / (H[i-1] + H[i]);  
  A[i] = H[i] / (H[i-1] + H[i]);  
  D[i] = 6 * (Fi[i] - Fi[i-1]) / (H[i-1] + H[i]);  
 }  
 //若边界条件为1号条件，则  
 U[i] = 1;  
 A[0] = 1;  
 D[0] = 6 * (Fi[0] - begin_k1) / H[0];  
 D[i] = 6 * (end_k1 - Fi[i-1]) / H[i-1];  
 //若边界条件为2号条件，则  
 //U[i] = 0;  
 //A[0] = 0;  
 //D[0] = 2 * begin_k2;  
 //D[i] = 2 * end_k2;  
 /////////////////////////////////////////追赶法求解M矩阵  
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
 //////////////////////////////////////////计算方程组最终结果  
 for(i = 0;i <= point_num - 2;i++)  
 {  
  a3[i] = M[i] / (6 * H[i]);  
  a1[i] = (y[i] - M[i] * H[i] * H[i] / 6) / H[i];  
  b3[i] = M[i+1] / (6 * H[i]);  
  b1[i] = (y[i+1] - M[i+1] * H[i] * H[i] / 6) /H[i];  
 }

 
 return 1;  
}  
 
 
 
 //分段函数的形式为 Si(x) = a3[i] * {x(i+1) - x}^3  + a1[i] * {x(i+1) - x} +  
 //        b3[i] * {x - x(i)}^3 + b1[i] * {x - x(i)}  
 //xi为x[i]的值，xi_1为x[i+1]的值        
};


////////////////////////////////////////////////////////////////////////////  

