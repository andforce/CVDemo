#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    Mat image = imread("/home/pc/Desktop/111.jpg");
    Mat dst, bgTransparentMat;
    // 转化颜色，转成含有透明度的
    cvtColor(image, dst, COLOR_BGR2BGRA);

    vector<Mat> channels;
    //分离通道
    split(dst, channels);

    // 把alpha设置成0， 表示透明
    for (int i = 0; i < channels[3].rows; i++) {
        for (int j = 0; j < channels[3].cols; j++) {
            channels[3].at<uchar>(i, j) = 0;
        }
    }

    merge(channels, bgTransparentMat);

    // 转成灰度图
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    //二值化
    Mat thresh;
    threshold(gray, thresh, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);


    // 消除噪点
    morphologyEx(thresh, thresh, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(15, 15)), Point(-1, -1), 2);
    //morphologyEx(thresh, thresh, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1,-1), 2);


    // 查找轮廓,的出来的是不规则的区域
    vector<vector<Point>> contours;
    findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    printf("contours.size() = %lu\n", contours.size());

    for (int i = 0; i < contours.size(); i++) {

        printf("contourArea = %f\n", contourArea(contours[i]));

        if (contourArea(contours[i]) < 10000) {
            // 过滤掉过小的轮廓
            continue;
        }

        for (int k = 0; k < bgTransparentMat.rows; k++) {
            for (int j = 0; j < bgTransparentMat.cols; j++) {
                if (pointPolygonTest(contours[i], Point2f(j, k), false) > 0) {
                    bgTransparentMat.at<Vec4b>(k, j)[3] = 255;
                }

            }
        }
    }

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) < 10000) {
            continue;
        }

        Rect rect = boundingRect(contours[i]);
        //rectangle(image, rect, Scalar(0, 0, 255), 1);

        ostringstream stream;
        stream << i;
        imwrite("/home/pc/Desktop/OUT/" + stream.str() + ".png", bgTransparentMat(rect));
    }

//    imwrite("/home/pc/Desktop/bgTransparentMat.png", bgTransparentMat);
//
//    imshow("image", image);
//
//    waitKey();

    return 0;

}