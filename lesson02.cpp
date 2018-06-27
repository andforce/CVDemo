//
// Created by pc on 6/27/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main1(int argc, char**argv) {
    printf("加载图像练习\n");

    Mat src = imread("/home/pc/Desktop/111.jpg", IMREAD_UNCHANGED);

    namedWindow("加载图像练习", WINDOW_AUTOSIZE);

    imshow("加载图像练习", src);

    // 颜色转换
    namedWindow("output Windows", WINDOW_AUTOSIZE);

    Mat outPutImage;

    cvtColor(src, outPutImage, CV_BGR2GRAY);

    imshow("output Windows", outPutImage);

    waitKey(0);

    return 0;
}