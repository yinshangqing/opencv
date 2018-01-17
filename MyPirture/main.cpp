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
//	//创建带alpha通道的Mat  
//	Mat mat(480, 640, CV_8UC4);  
//	createAlphaMat(mat);  
//
//	vector<int>compression_params;  
//	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);  
//	compression_params.push_back(9);  
//
//	try{  
//		imwrite("透明Alpha值图.png", mat, compression_params);  
//	}  
//	catch(runtime_error& ex) {  
//		fprintf(stderr,"图像转换成PNG格式发生错误：%s\n", ex.what());  
//		return 1;  
//	}  
//
//	fprintf(stdout,"PNG图片文件的alpha数据保存完毕~\n");  
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
//	//-----------------------------------【一、图像的载入和显示】--------------------------------------  
//	//     描述：以下三行代码用于完成图像的载入和显示  
//	//--------------------------------------------------------------------------------------------------  
//
//	Mat girl=imread("Erric_1.jpg"); //载入图像到Mat  
//	namedWindow("【1】动漫图"); //创建一个名为 "【1】动漫图"的窗口   
//	imshow("【1】动漫图",girl);//显示名为 "【1】动漫图"的窗口   
//
//	//-----------------------------------【二、初级图像混合】--------------------------------------  
//	//     描述：二、初级图像混合  
//	//-----------------------------------------------------------------------------------------------  
//	//载入图片  
//	Mat image= imread("girl.jpg",199);  
//	Mat logo= imread("Erric_4.jpg");  
//
//	//载入后先显示  
//	namedWindow("【2】原画图");  
//	imshow("【2】原画图",image);  
//
//	namedWindow("【3】logo图");  
//	imshow("【3】logo图",logo);  
//
//	//定义一个Mat类型，用于存放，图像的ROI  
//	Mat imageROI;  
//	//方法一  
//	imageROI=image(Rect(400,350,logo.cols,logo.rows));  
//	//方法二  
//	//imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));  
//
//	//将logo加到原图上  
//	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);  
//
//	//显示结果  
//	namedWindow("【4】原画+logo图");  
//	imshow("【4】原画+logo图",image);  
//
//	//-----------------------------------【三、图像的输出】--------------------------------------  
//	//     描述：将一个Mat图像输出到图像文件  
//	//-----------------------------------------------------------------------------------------------  
//	//输出一张jpg图片到工程目录下  
//	imwrite("Erric___.jpg",image);  
//
//	waitKey();  
//
//	return 0;  
//}  


//-----------------------------------【程序说明】----------------------------------------------  
//  程序名称:：【OpenCV入门教程之四】 ROI区域图像叠加&初级图像混合 全剖析   配套源码  
// VS2010版   OpenCV版本：2.4.8  
//     2014年3月10日 Create by 浅墨  
//    图片素材出处：dota2原画 dota2logo   
//     浅墨的微博：@浅墨_毛星云  
//------------------------------------------------------------------------------------------------  

////-----------------------------------【头文件包含部分】---------------------------------------  
////     描述：包含程序所依赖的头文件  
////----------------------------------------------------------------------------------------------                                                                                      
//#include <cv.h>  
//#include <highgui.h>  
//#include <iostream>  
//
////-----------------------------------【命名空间声明部分】---------------------------------------  
////     描述：包含程序所使用的命名空间  
////-----------------------------------------------------------------------------------------------    
//using namespace cv;  
//using namespace std;  
//
//
////-----------------------------------【全局函数声明部分】--------------------------------------  
////     描述：全局函数声明  
////-----------------------------------------------------------------------------------------------  
//bool ROI_AddImage();  
//bool LinearBlending();  
//bool ROI_LinearBlending();  
//
////-----------------------------------【main( )函数】--------------------------------------------  
////     描述：控制台应用程序的入口函数，我们的程序从这里开始  
////-----------------------------------------------------------------------------------------------  
//int main(  )  
//{  
//	system("color 5E");  
//
//	if(ROI_AddImage()&& LinearBlending( )&&ROI_LinearBlending( ))  
//	{  
//		cout<<endl<<"嗯。好了，得出了你需要的图像~! : )";  
//	}  
//
//	waitKey(0);  
//	return 0;  
//}  
//
////----------------------------------【ROI_AddImage( )函数】----------------------------------  
//// 函数名：ROI_AddImage（）  
////     描述：利用感兴趣区域ROI实现图像叠加  
////----------------------------------------------------------------------------------------------  
//bool ROI_AddImage()  
//{  
//
//	//【1】读入图像  
//	Mat srcImage1= imread("2.jpg");  
//	Mat logoImage= imread("Erric_4.jpg");  
//	if(!srcImage1.data ) { printf("你妹，读取srcImage1错误~！ \n"); return false; }  
//	if(!logoImage.data ) { printf("你妹，读取logoImage错误~！ \n"); return false; }  
//
//	//【2】定义一个Mat类型并给其设定ROI区域  
//	Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));  
//
//	//【3】加载掩模（必须是灰度图）  
//	Mat mask= imread("dota_logo.jpg",0);  
//
//	//【4】将掩膜拷贝到ROI  
//	logoImage.copyTo(imageROI,mask);  
//
//	//【5】显示结果  
//	namedWindow("<1>利用ROI实现图像叠加示例窗口");  
//	imshow("<1>利用ROI实现图像叠加示例窗口",srcImage1);  
//
//	return true;  
//}  
//
//
////---------------------------------【LinearBlending（）函数】-------------------------------------  
//// 函数名：LinearBlending（）  
//// 描述：利用cv::addWeighted（）函数实现图像线性混合  
////--------------------------------------------------------------------------------------------  
//bool LinearBlending()  
//{  
//	//【0】定义一些局部变量  
//	double alphaValue = 0.5;  
//	double betaValue;  
//	Mat srcImage2, srcImage3, dstImage;  
//
//	//【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )  
//	srcImage2= imread("Erric_3.jpg");  
//	srcImage3= imread("Erric_4.jpg");  
//
//	if(!srcImage2.data ) { printf("你妹，读取srcImage2错误~！ \n"); return false; }  
//	if(!srcImage3.data ) { printf("你妹，读取srcImage3错误~！ \n"); return false; }  
//
//	//【2】进行图像混合加权操作  
//	betaValue= ( 1.0 - alphaValue );  
//	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);  
//
//	//【3】创建并显示原图窗口  
//	namedWindow("<2>线性混合示例窗口【原图】 by浅墨", 1);  
//	imshow("<2>线性混合示例窗口【原图】 by浅墨", srcImage2 );  
//
//	namedWindow("<3>线性混合示例窗口【效果图】 by浅墨", 1);  
//	imshow("<3>线性混合示例窗口【效果图】 by浅墨", dstImage );  
//
//	return true;  
//
//}  
//
////---------------------------------【ROI_LinearBlending（）】-------------------------------------  
//// 函数名：ROI_LinearBlending（）  
//// 描述：线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义  
////                     感兴趣区域ROI，实现自定义区域的线性混合  
////--------------------------------------------------------------------------------------------  
//bool ROI_LinearBlending()  
//{  
//
//	//【1】读取图像  
//	Mat srcImage4= imread("2.jpg",1);  
//	Mat logoImage= imread("Erric_4.jpg");  
//
//	if(!srcImage4.data ) { printf("你妹，读取srcImage4错误~！ \n"); return false; }  
//	if(!logoImage.data ) { printf("你妹，读取logoImage错误~！ \n"); return false; }  
//
//	//【2】定义一个Mat类型并给其设定ROI区域  
//	Mat imageROI;  
//	//方法一  
//	imageROI=srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));  
//	//方法二  
//	//imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));  
//
//	//【3】将logo加到原图上  
//	addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);  
//
//	//【4】显示结果  
//	namedWindow("<4>区域线性图像混合示例窗口 by浅墨");  
//	imshow("<4>区域线性图像混合示例窗口 by浅墨",srcImage4);  
//
//	return true;  
//}  


//
//
////-----------------------------------【头文件包含部分】---------------------------------------  
////  描述：包含程序所依赖的头文件  
////----------------------------------------------------------------------------------------------   
//#include "opencv2/imgproc/imgproc.hpp"  
//#include "opencv2/highgui/highgui.hpp"  
//#include <iostream>  
//
////-----------------------------------【命名空间声明部分】---------------------------------------  
////  描述：包含程序所使用的命名空间  
////-----------------------------------------------------------------------------------------------     
//using namespace cv;  
//using namespace std;  
//
////-----------------------------------【全局函数声明部分】--------------------------------------  
////  描述：全局函数声明  
////-----------------------------------------------------------------------------------------------  
//Mat img;  
//int threshval = 160;            //轨迹条滑块对应的值，给初值160  
//
////-----------------------------【on_trackbar( )函数】------------------------------------  
////  描述：轨迹条的回调函数  
////-----------------------------------------------------------------------------------------------  
//static void on_trackbar(int, void*)  
//{  
//	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);  
//
//	//定义点和向量  
//	vector<vector<Point> > contours;  
//	vector<Vec4i> hierarchy;  
//
//	//查找轮廓  
//	findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );  
//	//初始化dst  
//	Mat dst = Mat::zeros(img.size(), CV_8UC3);  
//	//开始处理  
//	if( !contours.empty() && !hierarchy.empty() )  
//	{  
//		//遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分  
//		int idx = 0;  
//		for( ; idx >= 0; idx = hierarchy[idx][0] )  
//		{  
//			Scalar color( (rand()&255), (rand()&255), (rand()&255) );  
//			//绘制填充轮廓  
//			drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );  
//		}  
//	}  
//	//显示窗口  
//	imshow( "Connected Components", dst );  
//}  
//
//
////-----------------------------------【main( )函数】--------------------------------------------  
////  描述：控制台应用程序的入口函数，我们的程序从这里开始  
////-----------------------------------------------------------------------------------------------  
//int main()  
//{  
//	system("color 5F");    
//	//载入图片  
//	img = imread("3.jpg", 0);  
//	if( !img.data ) { printf("Oh，no，读取img图片文件错误~！ \n"); return -1; }  
//
//	//显示原图  
//	namedWindow( "Image", 1 );  
//	imshow( "Image", img );  
//
//	//创建处理窗口  
//	namedWindow( "Connected Components", 1 );  
//	//创建轨迹条  
//	createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );  
//	on_trackbar(threshval, 0);//轨迹条回调函数  
//
//	waitKey(0);  
//	return 0;  
//}  
//








////-----------------------------------【程序说明】----------------------------------------------  
////            程序名称:：【OpenCV入门教程之八】线性滤波专场：方框滤波、均值滤波与高斯滤波 配套源码  
////            开发所用OpenCV版本：2.4.8  
////            2014年3月31 日 Create by 浅墨  
////------------------------------------------------------------------------------------------------  
//
////-----------------------------------【头文件包含部分】---------------------------------------  
////     描述：包含程序所依赖的头文件  
////----------------------------------------------------------------------------------------------  
//#include <opencv2/core/core.hpp>  
//#include<opencv2/highgui/highgui.hpp>  
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <iostream>  
//
////-----------------------------------【命名空间声明部分】---------------------------------------  
////     描述：包含程序所使用的命名空间  
////-----------------------------------------------------------------------------------------------   
//using namespace std;  
//using namespace cv;  
//
//
////-----------------------------------【全局变量声明部分】--------------------------------------  
////     描述：全局变量声明  
////-----------------------------------------------------------------------------------------------  
//Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3;//存储图片的Mat类型  
//int g_nBoxFilterValue=3;  //方框滤波参数值  
//int g_nMeanBlurValue=3;  //均值滤波参数值  
//int g_nGaussianBlurValue=3;  //高斯滤波参数值  
//
//
////-----------------------------------【全局函数声明部分】--------------------------------------  
////     描述：全局函数声明  
////-----------------------------------------------------------------------------------------------  
////轨迹条的回调函数  
//static void on_BoxFilter(int, void *);            //方框滤波  
//static void on_MeanBlur(int, void *);           //均值滤波  
//static void on_GaussianBlur(int, void *);                    //高斯滤波  
//
//
//
////-----------------------------------【main( )函数】--------------------------------------------  
////     描述：控制台应用程序的入口函数，我们的程序从这里开始  
////-----------------------------------------------------------------------------------------------  
//int main(  )  
//{  
//	//改变console字体颜色  
//	system("color5E");   
//
//	//载入原图  
//	g_srcImage= imread( "2.jpg", 1 );  
//	if(!g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  
//
//	//克隆原图到三个Mat类型中  
//	g_dstImage1= g_srcImage.clone( );  
//	g_dstImage2= g_srcImage.clone( );  
//	g_dstImage3= g_srcImage.clone( );  
//
//	//显示原图  
//	namedWindow("【<0>原图窗口】", 1);  
//	imshow("【<0>原图窗口】",g_srcImage);  
//
//
//	//=================【<1>方框滤波】==================  
//	//创建窗口  
//	namedWindow("【<1>方框滤波】", 1);  
//	//创建轨迹条  
//	createTrackbar("内核值：", "【<1>方框滤波】",&g_nBoxFilterValue, 40,on_BoxFilter );  
//	on_MeanBlur(g_nBoxFilterValue,0);  
//	imshow("【<1>方框滤波】", g_dstImage1);  
//	//================================================  
//
//	//=================【<2>均值滤波】==================  
//	//创建窗口  
//	namedWindow("【<2>均值滤波】", 1);  
//	//创建轨迹条  
//	createTrackbar("内核值：", "【<2>均值滤波】",&g_nMeanBlurValue, 40,on_MeanBlur );  
//	on_MeanBlur(g_nMeanBlurValue,0);  
//	//================================================  
//
//	//=================【<3>高斯滤波】=====================  
//	//创建窗口  
//	namedWindow("【<3>高斯滤波】", 1);  
//	//创建轨迹条  
//	createTrackbar("内核值：", "【<3>高斯滤波】",&g_nGaussianBlurValue, 40,on_GaussianBlur );  
//	on_GaussianBlur(g_nGaussianBlurValue,0);  
//	//================================================  
//
//
//	//输出一些帮助信息  
//	cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"  
//		<<"\t按下“q”键时，程序退出~!\n"  
//		<<"\n\n\t\t\t\tby浅墨";  
//
//	//按下“q”键时，程序退出  
//	while(char(waitKey(1))!= 'q') {}  
//
//	return 0;  
//}  
//
//
////-----------------------------【on_BoxFilter( )函数】------------------------------------  
////     描述：方框滤波操作的回调函数  
////-----------------------------------------------------------------------------------------------  
//static void on_BoxFilter(int, void *)  
//{  
//	//方框滤波操作  
//	boxFilter(g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));  
//	//显示窗口  
//	imshow("【<1>方框滤波】", g_dstImage1);  
//}  
//
//
////-----------------------------【on_MeanBlur( )函数】------------------------------------  
////     描述：均值滤波操作的回调函数  
////-----------------------------------------------------------------------------------------------  
//static void on_MeanBlur(int, void *)  
//{  
//	//均值滤波操作  
//	blur(g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1),Point(-1,-1));  
//	//显示窗口  
//	imshow("【<2>均值滤波】", g_dstImage2);  
//}  
//
//
////-----------------------------【on_GaussianBlur( )函数】------------------------------------  
////     描述：高斯滤波操作的回调函数  
////-----------------------------------------------------------------------------------------------  
//static void on_GaussianBlur(int, void *)  
//{  
//	//高斯滤波操作  
//	GaussianBlur(g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1 ), 0, 0);  
//	//显示窗口  
//	imshow("【<3>高斯滤波】", g_dstImage3);  
//}  


//-----------------------------------【程序说明】----------------------------------------------  
//            程序名称:：《【OpenCV入门教程之九】非线性滤波专场：中值滤波、双边滤波  》 博文配套源码  
//            开发所用IDE版本：Visual Studio 2010  
//          开发所用OpenCV版本： 2.4.8  
//            2014年4月8日 Create by 浅墨  
//------------------------------------------------------------------------------------------------  

//-----------------------------------【头文件包含部分】---------------------------------------  
//            描述：包含程序所依赖的头文件  
//----------------------------------------------------------------------------------------------  
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include <iostream>  

//-----------------------------------【命名空间声明部分】---------------------------------------  
//            描述：包含程序所使用的命名空间  
//-----------------------------------------------------------------------------------------------   
using namespace std;  
using namespace cv;  


//-----------------------------------【全局变量声明部分】--------------------------------------  
//            描述：全局变量声明  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;  
int g_nBoxFilterValue=6;  //方框滤波内核值  
int g_nMeanBlurValue=10;  //均值滤波内核值  
int g_nGaussianBlurValue=6;  //高斯滤波内核值  
int g_nMedianBlurValue=10;  //中值滤波参数值  
int g_nBilateralFilterValue=10;  //双边滤波参数值  


//-----------------------------------【全局函数声明部分】--------------------------------------  
//            描述：全局函数声明  
//-----------------------------------------------------------------------------------------------  
//轨迹条回调函数  
static void on_BoxFilter(int, void *);            //方框滤波  
static void on_MeanBlur(int, void *);           //均值块滤波器  
static void on_GaussianBlur(int, void *);                    //高斯滤波器  
static void on_MedianBlur(int, void *);               //中值滤波器  
static void on_BilateralFilter(int, void*);                    //双边滤波器  



//-----------------------------------【main( )函数】--------------------------------------------  
//            描述：控制台应用程序的入口函数，我们的程序从这里开始  
//-----------------------------------------------------------------------------------------------  
int main()  
{  
	system("color 5E");   

	//载入原图  
	g_srcImage= imread( "3.jpg", 1 );  
	if(!g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  

	//克隆原图到四个Mat类型中  
	g_dstImage1= g_srcImage.clone( );  
	g_dstImage2= g_srcImage.clone( );  
	g_dstImage3= g_srcImage.clone( );  
	g_dstImage4= g_srcImage.clone( );  
	g_dstImage5= g_srcImage.clone( );  

	//显示原图  
	namedWindow("【<0>原图窗口】", 1);  
	imshow("【<0>原图窗口】",g_srcImage);  


	//=================【<1>方框滤波】=========================  
	//创建窗口  
	namedWindow("【<1>方框滤波】", 1);  
	//创建轨迹条  
	createTrackbar("内核值：", "【<1>方框滤波】",&g_nBoxFilterValue, 50,on_BoxFilter );  
	on_MeanBlur(g_nBoxFilterValue,0);  
	imshow("【<1>方框滤波】", g_dstImage1);  
	//=====================================================  


	//=================【<2>均值滤波】==========================  
	//创建窗口  
	namedWindow("【<2>均值滤波】", 1);  
	//创建轨迹条  
	createTrackbar("内核值：", "【<2>均值滤波】",&g_nMeanBlurValue, 50,on_MeanBlur );  
	on_MeanBlur(g_nMeanBlurValue,0);  
	//======================================================  


	//=================【<3>高斯滤波】===========================  
	//创建窗口  
	namedWindow("【<3>高斯滤波】", 1);  
	//创建轨迹条  
	createTrackbar("内核值：", "【<3>高斯滤波】",&g_nGaussianBlurValue, 50,on_GaussianBlur );  
	on_GaussianBlur(g_nGaussianBlurValue,0);  
	//=======================================================  


	//=================【<4>中值滤波】===========================  
	//创建窗口  
	namedWindow("【<4>中值滤波】", 1);  
	//创建轨迹条  
	createTrackbar("参数值：", "【<4>中值滤波】",&g_nMedianBlurValue, 50,on_MedianBlur );  
	on_MedianBlur(g_nMedianBlurValue,0);  
	//=======================================================  


	//=================【<5>双边滤波】===========================  
	//创建窗口  
	namedWindow("【<5>双边滤波】", 1);  
	//创建轨迹条  
	createTrackbar("参数值：", "【<5>双边滤波】",&g_nBilateralFilterValue, 50,on_BilateralFilter);  
	on_BilateralFilter(g_nBilateralFilterValue,0);  
	//=======================================================  


	//输出一些帮助信息  
	cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"  
		<<"\t按下“q”键时，程序退出~!\n"  
		<<"\n\n\t\t\t\tby浅墨";  
	while(char(waitKey(1))!= 'q') {}  

	return 0;  
}  

//-----------------------------【on_BoxFilter( )函数】------------------------------------  
//            描述：方框滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_BoxFilter(int, void *)  
{  
	//方框滤波操作  
	boxFilter(g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));  
	//显示窗口  
	imshow("【<1>方框滤波】", g_dstImage1);  
}  

//-----------------------------【on_MeanBlur( )函数】------------------------------------  
//            描述：均值滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_MeanBlur(int, void *)  
{  
	blur(g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1),Point(-1,-1));  
	imshow("【<2>均值滤波】", g_dstImage2);  

}  

//-----------------------------【on_GaussianBlur( )函数】------------------------------------  
//            描述：高斯滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_GaussianBlur(int, void *)  
{  
	GaussianBlur(g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1 ), 0, 0);  
	imshow("【<3>高斯滤波】", g_dstImage3);  
}  


//-----------------------------【on_MedianBlur( )函数】------------------------------------  
//            描述：中值滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_MedianBlur(int, void *)  
{  
	medianBlur( g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1 );  
	imshow("【<4>中值滤波】", g_dstImage4);  
}  


//-----------------------------【on_BilateralFilter( )函数】------------------------------------  
//            描述：双边滤波操作的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_BilateralFilter(int, void *)  
{  
	bilateralFilter( g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2,g_nBilateralFilterValue/2 );  
	imshow("【<5>双边滤波】", g_dstImage5);  
}  


