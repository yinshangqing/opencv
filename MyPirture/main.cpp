//#include <vector>  
//#include <stdio.h>  
//#include<opencv2/opencv.hpp>  
//
//using namespace cv;  
//using namespace std;  
//
//void createAlphaMat(Mat &mat)  
//{  
//	for(int i = 0; i < mat.rows; ++i) {  
//		for(int j = 0; j < mat.cols; ++j) {  
//			Vec4b&rgba = mat.at<Vec4b>(i, j);  
//			rgba[0]= UCHAR_MAX;  
//			rgba[1]= saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);  
//			rgba[2]= saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);  
//			rgba[3]= saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));  
//		}  
//	}  
//}  
//
//int main( )  
//{  
//	//������alphaͨ����Mat  
//	Mat mat(480, 640, CV_8UC4);  
//	createAlphaMat(mat);  
//
//	vector<int>compression_params;  
//	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);  
//	compression_params.push_back(9);  
//
//	try{  
//		imwrite("͸��Alphaֵͼ.png", mat, compression_params);  
//	}  
//	catch(runtime_error& ex) {  
//		fprintf(stderr,"ͼ��ת����PNG��ʽ��������%s\n", ex.what());  
//		return 1;  
//	}  
//
//	fprintf(stdout,"PNGͼƬ�ļ���alpha���ݱ������~\n");  
//	return 0;  
//}  

//#include<opencv2/core/core.hpp>  
//#include<opencv2/highgui/highgui.hpp>  
//
//using namespace cv;  
//
//
//int main( )  
//{  
//	//-----------------------------------��һ��ͼ����������ʾ��--------------------------------------  
//	//     �������������д����������ͼ����������ʾ  
//	//--------------------------------------------------------------------------------------------------  
//
//	Mat girl=imread("Erric_1.jpg"); //����ͼ��Mat  
//	namedWindow("��1������ͼ"); //����һ����Ϊ "��1������ͼ"�Ĵ���   
//	imshow("��1������ͼ",girl);//��ʾ��Ϊ "��1������ͼ"�Ĵ���   
//
//	//-----------------------------------����������ͼ���ϡ�--------------------------------------  
//	//     ��������������ͼ����  
//	//-----------------------------------------------------------------------------------------------  
//	//����ͼƬ  
//	Mat image= imread("girl.jpg",199);  
//	Mat logo= imread("Erric_4.jpg");  
//
//	//���������ʾ  
//	namedWindow("��2��ԭ��ͼ");  
//	imshow("��2��ԭ��ͼ",image);  
//
//	namedWindow("��3��logoͼ");  
//	imshow("��3��logoͼ",logo);  
//
//	//����һ��Mat���ͣ����ڴ�ţ�ͼ���ROI  
//	Mat imageROI;  
//	//����һ  
//	imageROI=image(Rect(400,350,logo.cols,logo.rows));  
//	//������  
//	//imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));  
//
//	//��logo�ӵ�ԭͼ��  
//	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);  
//
//	//��ʾ���  
//	namedWindow("��4��ԭ��+logoͼ");  
//	imshow("��4��ԭ��+logoͼ",image);  
//
//	//-----------------------------------������ͼ��������--------------------------------------  
//	//     ��������һ��Matͼ�������ͼ���ļ�  
//	//-----------------------------------------------------------------------------------------------  
//	//���һ��jpgͼƬ������Ŀ¼��  
//	imwrite("Erric___.jpg",image);  
//
//	waitKey();  
//
//	return 0;  
//}  


//-----------------------------------������˵����----------------------------------------------  
//  ��������:����OpenCV���Ž̳�֮�ġ� ROI����ͼ�����&����ͼ���� ȫ����   ����Դ��  
// VS2010��   OpenCV�汾��2.4.8  
//     2014��3��10�� Create by ǳī  
//    ͼƬ�زĳ�����dota2ԭ�� dota2logo   
//     ǳī��΢����@ǳī_ë����  
//------------------------------------------------------------------------------------------------  

////-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
////     ����������������������ͷ�ļ�  
////----------------------------------------------------------------------------------------------                                                                                      
//#include <cv.h>  
//#include <highgui.h>  
//#include <iostream>  
//
////-----------------------------------�������ռ��������֡�---------------------------------------  
////     ����������������ʹ�õ������ռ�  
////-----------------------------------------------------------------------------------------------    
//using namespace cv;  
//using namespace std;  
//
//
////-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
////     ������ȫ�ֺ�������  
////-----------------------------------------------------------------------------------------------  
//bool ROI_AddImage();  
//bool LinearBlending();  
//bool ROI_LinearBlending();  
//
////-----------------------------------��main( )������--------------------------------------------  
////     ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
////-----------------------------------------------------------------------------------------------  
//int main(  )  
//{  
//	system("color 5E");  
//
//	if(ROI_AddImage()&& LinearBlending( )&&ROI_LinearBlending( ))  
//	{  
//		cout<<endl<<"�š����ˣ��ó�������Ҫ��ͼ��~! : )";  
//	}  
//
//	waitKey(0);  
//	return 0;  
//}  
//
////----------------------------------��ROI_AddImage( )������----------------------------------  
//// ��������ROI_AddImage����  
////     ���������ø���Ȥ����ROIʵ��ͼ�����  
////----------------------------------------------------------------------------------------------  
//bool ROI_AddImage()  
//{  
//
//	//��1������ͼ��  
//	Mat srcImage1= imread("2.jpg");  
//	Mat logoImage= imread("Erric_4.jpg");  
//	if(!srcImage1.data ) { printf("���ã���ȡsrcImage1����~�� \n"); return false; }  
//	if(!logoImage.data ) { printf("���ã���ȡlogoImage����~�� \n"); return false; }  
//
//	//��2������һ��Mat���Ͳ������趨ROI����  
//	Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));  
//
//	//��3��������ģ�������ǻҶ�ͼ��  
//	Mat mask= imread("dota_logo.jpg",0);  
//
//	//��4������Ĥ������ROI  
//	logoImage.copyTo(imageROI,mask);  
//
//	//��5����ʾ���  
//	namedWindow("<1>����ROIʵ��ͼ�����ʾ������");  
//	imshow("<1>����ROIʵ��ͼ�����ʾ������",srcImage1);  
//
//	return true;  
//}  
//
//
////---------------------------------��LinearBlending����������-------------------------------------  
//// ��������LinearBlending����  
//// ����������cv::addWeighted��������ʵ��ͼ�����Ի��  
////--------------------------------------------------------------------------------------------  
//bool LinearBlending()  
//{  
//	//��0������һЩ�ֲ�����  
//	double alphaValue = 0.5;  
//	double betaValue;  
//	Mat srcImage2, srcImage3, dstImage;  
//
//	//��1����ȡͼ�� ( ����ͼƬ��Ϊͬ�������ͺͳߴ� )  
//	srcImage2= imread("Erric_3.jpg");  
//	srcImage3= imread("Erric_4.jpg");  
//
//	if(!srcImage2.data ) { printf("���ã���ȡsrcImage2����~�� \n"); return false; }  
//	if(!srcImage3.data ) { printf("���ã���ȡsrcImage3����~�� \n"); return false; }  
//
//	//��2������ͼ���ϼ�Ȩ����  
//	betaValue= ( 1.0 - alphaValue );  
//	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);  
//
//	//��3����������ʾԭͼ����  
//	namedWindow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", 1);  
//	imshow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", srcImage2 );  
//
//	namedWindow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", 1);  
//	imshow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", dstImage );  
//
//	return true;  
//
//}  
//
////---------------------------------��ROI_LinearBlending������-------------------------------------  
//// ��������ROI_LinearBlending����  
//// ���������Ի��ʵ�ֺ���,ָ����������ͼ����.����cv::addWeighted����������϶���  
////                     ����Ȥ����ROI��ʵ���Զ�����������Ի��  
////--------------------------------------------------------------------------------------------  
//bool ROI_LinearBlending()  
//{  
//
//	//��1����ȡͼ��  
//	Mat srcImage4= imread("2.jpg",1);  
//	Mat logoImage= imread("Erric_4.jpg");  
//
//	if(!srcImage4.data ) { printf("���ã���ȡsrcImage4����~�� \n"); return false; }  
//	if(!logoImage.data ) { printf("���ã���ȡlogoImage����~�� \n"); return false; }  
//
//	//��2������һ��Mat���Ͳ������趨ROI����  
//	Mat imageROI;  
//	//����һ  
//	imageROI=srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));  
//	//������  
//	//imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));  
//
//	//��3����logo�ӵ�ԭͼ��  
//	addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);  
//
//	//��4����ʾ���  
//	namedWindow("<4>��������ͼ����ʾ������ byǳī");  
//	imshow("<4>��������ͼ����ʾ������ byǳī",srcImage4);  
//
//	return true;  
//}  


//
//
////-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
////  ����������������������ͷ�ļ�  
////----------------------------------------------------------------------------------------------   
//#include "opencv2/imgproc/imgproc.hpp"  
//#include "opencv2/highgui/highgui.hpp"  
//#include <iostream>  
//
////-----------------------------------�������ռ��������֡�---------------------------------------  
////  ����������������ʹ�õ������ռ�  
////-----------------------------------------------------------------------------------------------     
//using namespace cv;  
//using namespace std;  
//
////-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
////  ������ȫ�ֺ�������  
////-----------------------------------------------------------------------------------------------  
//Mat img;  
//int threshval = 160;            //�켣�������Ӧ��ֵ������ֵ160  
//
////-----------------------------��on_trackbar( )������------------------------------------  
////  �������켣���Ļص�����  
////-----------------------------------------------------------------------------------------------  
//static void on_trackbar(int, void*)  
//{  
//	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);  
//
//	//����������  
//	vector<vector<Point> > contours;  
//	vector<Vec4i> hierarchy;  
//
//	//��������  
//	findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );  
//	//��ʼ��dst  
//	Mat dst = Mat::zeros(img.size(), CV_8UC3);  
//	//��ʼ����  
//	if( !contours.empty() && !hierarchy.empty() )  
//	{  
//		//�������ж������������������ɫֵ���Ƹ���������ɲ���  
//		int idx = 0;  
//		for( ; idx >= 0; idx = hierarchy[idx][0] )  
//		{  
//			Scalar color( (rand()&255), (rand()&255), (rand()&255) );  
//			//�����������  
//			drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );  
//		}  
//	}  
//	//��ʾ����  
//	imshow( "Connected Components", dst );  
//}  
//
//
////-----------------------------------��main( )������--------------------------------------------  
////  ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
////-----------------------------------------------------------------------------------------------  
//int main()  
//{  
//	system("color 5F");    
//	//����ͼƬ  
//	img = imread("3.jpg", 0);  
//	if( !img.data ) { printf("Oh��no����ȡimgͼƬ�ļ�����~�� \n"); return -1; }  
//
//	//��ʾԭͼ  
//	namedWindow( "Image", 1 );  
//	imshow( "Image", img );  
//
//	//����������  
//	namedWindow( "Connected Components", 1 );  
//	//�����켣��  
//	createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );  
//	on_trackbar(threshval, 0);//�켣���ص�����  
//
//	waitKey(0);  
//	return 0;  
//}  
//








////-----------------------------------������˵����----------------------------------------------  
////            ��������:����OpenCV���Ž̳�֮�ˡ������˲�ר���������˲�����ֵ�˲����˹�˲� ����Դ��  
////            ��������OpenCV�汾��2.4.8  
////            2014��3��31 �� Create by ǳī  
////------------------------------------------------------------------------------------------------  
//
////-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
////     ����������������������ͷ�ļ�  
////----------------------------------------------------------------------------------------------  
//#include <opencv2/core/core.hpp>  
//#include<opencv2/highgui/highgui.hpp>  
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <iostream>  
//
////-----------------------------------�������ռ��������֡�---------------------------------------  
////     ����������������ʹ�õ������ռ�  
////-----------------------------------------------------------------------------------------------   
//using namespace std;  
//using namespace cv;  
//
//
////-----------------------------------��ȫ�ֱ����������֡�--------------------------------------  
////     ������ȫ�ֱ�������  
////-----------------------------------------------------------------------------------------------  
//Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3;//�洢ͼƬ��Mat����  
//int g_nBoxFilterValue=3;  //�����˲�����ֵ  
//int g_nMeanBlurValue=3;  //��ֵ�˲�����ֵ  
//int g_nGaussianBlurValue=3;  //��˹�˲�����ֵ  
//
//
////-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
////     ������ȫ�ֺ�������  
////-----------------------------------------------------------------------------------------------  
////�켣���Ļص�����  
//static void on_BoxFilter(int, void *);            //�����˲�  
//static void on_MeanBlur(int, void *);           //��ֵ�˲�  
//static void on_GaussianBlur(int, void *);                    //��˹�˲�  
//
//
//
////-----------------------------------��main( )������--------------------------------------------  
////     ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
////-----------------------------------------------------------------------------------------------  
//int main(  )  
//{  
//	//�ı�console������ɫ  
//	system("color5E");   
//
//	//����ԭͼ  
//	g_srcImage= imread( "2.jpg", 1 );  
//	if(!g_srcImage.data ) { printf("Oh��no����ȡsrcImage����~��\n"); return false; }  
//
//	//��¡ԭͼ������Mat������  
//	g_dstImage1= g_srcImage.clone( );  
//	g_dstImage2= g_srcImage.clone( );  
//	g_dstImage3= g_srcImage.clone( );  
//
//	//��ʾԭͼ  
//	namedWindow("��<0>ԭͼ���ڡ�", 1);  
//	imshow("��<0>ԭͼ���ڡ�",g_srcImage);  
//
//
//	//=================��<1>�����˲���==================  
//	//��������  
//	namedWindow("��<1>�����˲���", 1);  
//	//�����켣��  
//	createTrackbar("�ں�ֵ��", "��<1>�����˲���",&g_nBoxFilterValue, 40,on_BoxFilter );  
//	on_MeanBlur(g_nBoxFilterValue,0);  
//	imshow("��<1>�����˲���", g_dstImage1);  
//	//================================================  
//
//	//=================��<2>��ֵ�˲���==================  
//	//��������  
//	namedWindow("��<2>��ֵ�˲���", 1);  
//	//�����켣��  
//	createTrackbar("�ں�ֵ��", "��<2>��ֵ�˲���",&g_nMeanBlurValue, 40,on_MeanBlur );  
//	on_MeanBlur(g_nMeanBlurValue,0);  
//	//================================================  
//
//	//=================��<3>��˹�˲���=====================  
//	//��������  
//	namedWindow("��<3>��˹�˲���", 1);  
//	//�����켣��  
//	createTrackbar("�ں�ֵ��", "��<3>��˹�˲���",&g_nGaussianBlurValue, 40,on_GaussianBlur );  
//	on_GaussianBlur(g_nGaussianBlurValue,0);  
//	//================================================  
//
//
//	//���һЩ������Ϣ  
//	cout<<endl<<"\t�š����ˣ�������������۲�ͼ��Ч��~\n\n"  
//		<<"\t���¡�q����ʱ�������˳�~!\n"  
//		<<"\n\n\t\t\t\tbyǳī";  
//
//	//���¡�q����ʱ�������˳�  
//	while(char(waitKey(1))!= 'q') {}  
//
//	return 0;  
//}  
//
//
////-----------------------------��on_BoxFilter( )������------------------------------------  
////     �����������˲������Ļص�����  
////-----------------------------------------------------------------------------------------------  
//static void on_BoxFilter(int, void *)  
//{  
//	//�����˲�����  
//	boxFilter(g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));  
//	//��ʾ����  
//	imshow("��<1>�����˲���", g_dstImage1);  
//}  
//
//
////-----------------------------��on_MeanBlur( )������------------------------------------  
////     ��������ֵ�˲������Ļص�����  
////-----------------------------------------------------------------------------------------------  
//static void on_MeanBlur(int, void *)  
//{  
//	//��ֵ�˲�����  
//	blur(g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1),Point(-1,-1));  
//	//��ʾ����  
//	imshow("��<2>��ֵ�˲���", g_dstImage2);  
//}  
//
//
////-----------------------------��on_GaussianBlur( )������------------------------------------  
////     ��������˹�˲������Ļص�����  
////-----------------------------------------------------------------------------------------------  
//static void on_GaussianBlur(int, void *)  
//{  
//	//��˹�˲�����  
//	GaussianBlur(g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1 ), 0, 0);  
//	//��ʾ����  
//	imshow("��<3>��˹�˲���", g_dstImage3);  
//}  


//-----------------------------------������˵����----------------------------------------------  
//            ��������:������OpenCV���Ž̳�֮�š��������˲�ר������ֵ�˲���˫���˲�  �� ��������Դ��  
//            ��������IDE�汾��Visual Studio 2010  
//          ��������OpenCV�汾�� 2.4.8  
//            2014��4��8�� Create by ǳī  
//------------------------------------------------------------------------------------------------  

//-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
//            ����������������������ͷ�ļ�  
//----------------------------------------------------------------------------------------------  
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include <iostream>  

//-----------------------------------�������ռ��������֡�---------------------------------------  
//            ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------   
using namespace std;  
using namespace cv;  


//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------  
//            ������ȫ�ֱ�������  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;  
int g_nBoxFilterValue=6;  //�����˲��ں�ֵ  
int g_nMeanBlurValue=10;  //��ֵ�˲��ں�ֵ  
int g_nGaussianBlurValue=6;  //��˹�˲��ں�ֵ  
int g_nMedianBlurValue=10;  //��ֵ�˲�����ֵ  
int g_nBilateralFilterValue=10;  //˫���˲�����ֵ  


//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
//            ������ȫ�ֺ�������  
//-----------------------------------------------------------------------------------------------  
//�켣���ص�����  
static void on_BoxFilter(int, void *);            //�����˲�  
static void on_MeanBlur(int, void *);           //��ֵ���˲���  
static void on_GaussianBlur(int, void *);                    //��˹�˲���  
static void on_MedianBlur(int, void *);               //��ֵ�˲���  
static void on_BilateralFilter(int, void*);                    //˫���˲���  



//-----------------------------------��main( )������--------------------------------------------  
//            ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  
int main()  
{  
	system("color 5E");   

	//����ԭͼ  
	g_srcImage= imread( "3.jpg", 1 );  
	if(!g_srcImage.data ) { printf("Oh��no����ȡsrcImage����~��\n"); return false; }  

	//��¡ԭͼ���ĸ�Mat������  
	g_dstImage1= g_srcImage.clone( );  
	g_dstImage2= g_srcImage.clone( );  
	g_dstImage3= g_srcImage.clone( );  
	g_dstImage4= g_srcImage.clone( );  
	g_dstImage5= g_srcImage.clone( );  

	//��ʾԭͼ  
	namedWindow("��<0>ԭͼ���ڡ�", 1);  
	imshow("��<0>ԭͼ���ڡ�",g_srcImage);  


	//=================��<1>�����˲���=========================  
	//��������  
	namedWindow("��<1>�����˲���", 1);  
	//�����켣��  
	createTrackbar("�ں�ֵ��", "��<1>�����˲���",&g_nBoxFilterValue, 50,on_BoxFilter );  
	on_MeanBlur(g_nBoxFilterValue,0);  
	imshow("��<1>�����˲���", g_dstImage1);  
	//=====================================================  


	//=================��<2>��ֵ�˲���==========================  
	//��������  
	namedWindow("��<2>��ֵ�˲���", 1);  
	//�����켣��  
	createTrackbar("�ں�ֵ��", "��<2>��ֵ�˲���",&g_nMeanBlurValue, 50,on_MeanBlur );  
	on_MeanBlur(g_nMeanBlurValue,0);  
	//======================================================  


	//=================��<3>��˹�˲���===========================  
	//��������  
	namedWindow("��<3>��˹�˲���", 1);  
	//�����켣��  
	createTrackbar("�ں�ֵ��", "��<3>��˹�˲���",&g_nGaussianBlurValue, 50,on_GaussianBlur );  
	on_GaussianBlur(g_nGaussianBlurValue,0);  
	//=======================================================  


	//=================��<4>��ֵ�˲���===========================  
	//��������  
	namedWindow("��<4>��ֵ�˲���", 1);  
	//�����켣��  
	createTrackbar("����ֵ��", "��<4>��ֵ�˲���",&g_nMedianBlurValue, 50,on_MedianBlur );  
	on_MedianBlur(g_nMedianBlurValue,0);  
	//=======================================================  


	//=================��<5>˫���˲���===========================  
	//��������  
	namedWindow("��<5>˫���˲���", 1);  
	//�����켣��  
	createTrackbar("����ֵ��", "��<5>˫���˲���",&g_nBilateralFilterValue, 50,on_BilateralFilter);  
	on_BilateralFilter(g_nBilateralFilterValue,0);  
	//=======================================================  


	//���һЩ������Ϣ  
	cout<<endl<<"\t�š����ˣ�������������۲�ͼ��Ч��~\n\n"  
		<<"\t���¡�q����ʱ�������˳�~!\n"  
		<<"\n\n\t\t\t\tbyǳī";  
	while(char(waitKey(1))!= 'q') {}  

	return 0;  
}  

//-----------------------------��on_BoxFilter( )������------------------------------------  
//            �����������˲������Ļص�����  
//-----------------------------------------------------------------------------------------------  
static void on_BoxFilter(int, void *)  
{  
	//�����˲�����  
	boxFilter(g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));  
	//��ʾ����  
	imshow("��<1>�����˲���", g_dstImage1);  
}  

//-----------------------------��on_MeanBlur( )������------------------------------------  
//            ��������ֵ�˲������Ļص�����  
//-----------------------------------------------------------------------------------------------  
static void on_MeanBlur(int, void *)  
{  
	blur(g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1),Point(-1,-1));  
	imshow("��<2>��ֵ�˲���", g_dstImage2);  

}  

//-----------------------------��on_GaussianBlur( )������------------------------------------  
//            ��������˹�˲������Ļص�����  
//-----------------------------------------------------------------------------------------------  
static void on_GaussianBlur(int, void *)  
{  
	GaussianBlur(g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1 ), 0, 0);  
	imshow("��<3>��˹�˲���", g_dstImage3);  
}  


//-----------------------------��on_MedianBlur( )������------------------------------------  
//            ��������ֵ�˲������Ļص�����  
//-----------------------------------------------------------------------------------------------  
static void on_MedianBlur(int, void *)  
{  
	medianBlur( g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1 );  
	imshow("��<4>��ֵ�˲���", g_dstImage4);  
}  


//-----------------------------��on_BilateralFilter( )������------------------------------------  
//            ������˫���˲������Ļص�����  
//-----------------------------------------------------------------------------------------------  
static void on_BilateralFilter(int, void *)  
{  
	bilateralFilter( g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2,g_nBilateralFilterValue/2 );  
	imshow("��<5>˫���˲���", g_dstImage5);  
}  


