#include <iostream>
//#import "cv.h"
//#import "highgui.h"

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main1(int argc, char**argv) {

    std::cout << "Hello, World!" << std::endl;

    IplImage * pImg = cvLoadImage("/home/pc/Desktop/1.jpeg", 1);
    //if (argc == 2 && (pImg = cvLoadImage(argv[1], 1)) != 0) {
    if (false){
        namedWindow("Image", CV_WINDOW_AUTOSIZE);

        cvShowImage("Image", pImg);

        cvWaitKey(0);

        cvDestroyWindow("Image");
        cvReleaseImage( & pImg );
        return 0;
    }

    Mat image = imread("/home/pc/Desktop/111.jpg");
    if (image.empty()){
        printf("空的");
    }

    Mat gray;
    cvtColor(image, gray, COLOR_RGB2GRAY);

    Mat thresh;
    threshold(gray, thresh, 0, 255, THRESH_BINARY_INV|THRESH_OTSU);


    morphologyEx(thresh, thresh, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(11, 11)), Point(-1,-1), 2);
    morphologyEx(thresh, thresh, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1,-1), 2);

    vector<vector<Point>> contours;
    findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    printf("contours.size() = %lu\n", contours.size());

    for (int i = 0; i< contours.size(); i++) {
        printf("contourArea = %f\n", contourArea(contours[i]));
        if (contourArea(contours[i]) < 10000) {
            continue;
        }

        //drawContours(image, contours, i, Scalar(255,0,0), 2);

        Rect rect = boundingRect(contours[i]);
        //rectangle(image, rect, Scalar(0, 0, 255), 1);

        ostringstream stream;
        stream << i;
        imwrite("/home/pc/Desktop/" + stream.str() + ".jpg", image(rect));
    }

    return -1;

}