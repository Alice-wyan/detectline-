//#include"getcorner.h"
#include"lib.h"
//#include"getrectframe.h"
//#include"GetCameraNoise.h"
#include"testdetect.h"
#include"testdetectpoint.h"

///
///������
///
int  main()
{
	///
	///������Ҫ�����������
	///
	TestDetect  td;//������Ҫ�����������
	TestDetectPoint tp;
	DetectLine dl;
   ///
  ///����CvCapture ��������ͷ����˿�
  ///
	CvCapture* capture1 = cvCreateCameraCapture( 0 );//������ͷ���洫�ݸ�ָ��
   ///
  ///������ͷ����ͼƬ����IplImage ָ�� src
  ///
	IplImage *src = cvQueryFrame(capture1 );//������ͷ����ͼƬ����IplImage
	///
	///������GetCameraNoise��ʱʹ������ռ� 
	///
	int row=src->height;//ͼƬ����
	int com=src->width;
	double ** a = new double *[row];//���嶯̬����洢ͼƬ��ά�������ص�garyֵ
	for(int i = 0;i < row;i++)
	{a[i] = new double[com];}//��ʼ������
		double ** b = new double *[row];//���嶯̬����洢ͼƬ��ά�������ص�garyֵ
	for(int i = 0;i < row;i++)
	{b[i] = new double[com];}//��ʼ������



	cvNamedWindow( "src", CV_WINDOW_AUTOSIZE );	 ///define a window
	cvResizeWindow( "src", 320, 320 );///���ô��ڴ�С
	///
	///����i�����òɼ�100֡ͼƬ���˳�����
    ///
	int i=0;
	///
	///����sec��dst dst������Ϊ�˻���̽���߽�ֱ�۹۲�
	///
	IplImage *dst=cvCloneImage(src);

	///
	///����ѭ��һֱ�ɼ�����ͷͼƬ
	///
	while(1)
	{
		   ///
		  ///����CvCapture ��������ͷ����˿�
		  ///
		CvCapture* capture1 = cvCreateCameraCapture( 0 );//������ͷ���洫�ݸ�ָ��
		///
		///������ͷ����ͼƬ����IplImage ָ�� src
		///
		IplImage *src = cvQueryFrame( capture1 );//������ͷ����ͼƬ����IplImage
		  ///
		  ///dst��¡src
		  ///
		IplImage *dst=cvCloneImage(src);//��ԭͼ���Ƹ�dstָ��


		if((src!=0))//���src��Ϊ����ִ�����³���
		{
			
		if(i>=10)
		{		
		 //gc.getcornerpoint(src,dst,9,10,30,0);//��ȡ�����Ͼ�ȷ�ǵ�����
		 // gn.getallgary(dst,a,b);//��ȡ����ͷrgb����
		    ///
			///����TestDetect���е�getdetectedge��������ȡ��Ե����
			///
		    tp.getdetectedge(src,dst);//����TestDetect���е�getdetectedge��������ȡ��Ե����
		}
		cvShowImage( "src", src );///  show  the  IplImage *dst
		i++;
		cout<<"i="<<i<<endl;
		if(i==110){break;}
		char c=cvWaitKey(33);//��esc���˳�ѭ��
		 //cvReleaseImage(&dst);
		 cvReleaseImage(&src);//�ͷ�ָ��
		 if(c==27)break;
		}
	}
	cvWaitKey(27);
	
	cout<<"xxx===="<<endl;
	///
	///����TestDetect���е�testdetectpointx��������ȡ�����rmseƽ��ֵ
	///
	td.calcpointrms(tp.px,tp.xdetectpoint);//����̽�������ܲ���
	cout<<"yyy==="<<endl;
	///
	///����TestDetect���е�testdetectpointx��������ȡ�����rmseƽ��ֵ
	///
	td.calcpointrms(tp.py,tp.ydetectpoint);//����TestDetect���е�testdetectpointx��������ȡ�����rmseƽ��ֵ
		delete a;//�ͷŶ�̬�����ڴ�
		delete b;//�ͷŶ�̬�����ڴ�

		return 0;

}
		