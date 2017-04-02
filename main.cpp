//#include"getcorner.h"
#include"lib.h"
//#include"getrectframe.h"
//#include"GetCameraNoise.h"
#include"testdetect.h"
#include"testdetectpoint.h"

///
///主函数
///
int  main()
{
	///
	///定义需要被调用类对象
	///
	TestDetect  td;//定义需要被调用类对象
	TestDetectPoint tp;
	DetectLine dl;
   ///
  ///定义CvCapture 对象即摄像头输入端口
  ///
	CvCapture* capture1 = cvCreateCameraCapture( 0 );//把摄像头画面传递给指针
   ///
  ///把摄像头输入图片传给IplImage 指针 src
  ///
	IplImage *src = cvQueryFrame(capture1 );//把摄像头输入图片传给IplImage
	///
	///给调用GetCameraNoise类时使用申请空间 
	///
	int row=src->height;//图片长宽
	int com=src->width;
	double ** a = new double *[row];//定义动态数组存储图片二维数组像素点gary值
	for(int i = 0;i < row;i++)
	{a[i] = new double[com];}//初始化数组
		double ** b = new double *[row];//定义动态数组存储图片二维数组像素点gary值
	for(int i = 0;i < row;i++)
	{b[i] = new double[com];}//初始化数组



	cvNamedWindow( "src", CV_WINDOW_AUTOSIZE );	 ///define a window
	cvResizeWindow( "src", 320, 320 );///设置窗口大小
	///
	///定义i有利用采集100帧图片后退出程序
    ///
	int i=0;
	///
	///复制sec给dst dst作用是为了画出探测线较直观观测
	///
	IplImage *dst=cvCloneImage(src);

	///
	///进入循环一直采集摄像头图片
	///
	while(1)
	{
		   ///
		  ///定义CvCapture 对象即摄像头输入端口
		  ///
		CvCapture* capture1 = cvCreateCameraCapture( 0 );//把摄像头画面传递给指针
		///
		///把摄像头输入图片传给IplImage 指针 src
		///
		IplImage *src = cvQueryFrame( capture1 );//把摄像头输入图片传给IplImage
		  ///
		  ///dst克隆src
		  ///
		IplImage *dst=cvCloneImage(src);//把原图复制给dst指针


		if((src!=0))//如果src不为空则执行以下程序
		{
			
		if(i>=10)
		{		
		 //gc.getcornerpoint(src,dst,9,10,30,0);//获取轮廓上精确角点坐标
		 // gn.getallgary(dst,a,b);//获取摄像头rgb噪声
		    ///
			///调用TestDetect类中的getdetectedge函数来获取边缘坐标
			///
		    tp.getdetectedge(src,dst);//调用TestDetect类中的getdetectedge函数来获取边缘坐标
		}
		cvShowImage( "src", src );///  show  the  IplImage *dst
		i++;
		cout<<"i="<<i<<endl;
		if(i==110){break;}
		char c=cvWaitKey(33);//按esc键退出循环
		 //cvReleaseImage(&dst);
		 cvReleaseImage(&src);//释放指针
		 if(c==27)break;
		}
	}
	cvWaitKey(27);
	
	cout<<"xxx===="<<endl;
	///
	///调用TestDetect类中的testdetectpointx函数来获取坐标的rmse平均值
	///
	td.calcpointrms(tp.px,tp.xdetectpoint);//进行探测线性能测试
	cout<<"yyy==="<<endl;
	///
	///调用TestDetect类中的testdetectpointx函数来获取坐标的rmse平均值
	///
	td.calcpointrms(tp.py,tp.ydetectpoint);//调用TestDetect类中的testdetectpointx函数来获取坐标的rmse平均值
		delete a;//释放动态数组内存
		delete b;//释放动态数组内存

		return 0;

}
		