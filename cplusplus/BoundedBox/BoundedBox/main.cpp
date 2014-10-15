//
//  main.cpp
//  BoundedBox
//
//  Created by Akrita Agarwal on 10/5/14.
//  Copyright (c) 2014 Akrita Agarwal. All rights reserved.
//

/*
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    IplImage *img = cvCreateImage( cvSize(100,200), IPL_DEPTH_8U, 3);
    cvNamedWindow("Hello World!", CV_WINDOW_AUTOSIZE);
    cvShowImage("Hello World!", img);
    cvWaitKey(0);
    cvDestroyWindow("Hello World!");
    cvReleaseImage(&img);
    
    return 0;
}
*/

#include "opencv2/opencv.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

std::vector<cv::Rect> detectLetters(cv::Mat img)
{
    std::vector<cv::Rect> boundRect;
    cv::Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10) );
    cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
    std::vector< std::vector< cv::Point> > contours;
    cv::findContours(img_threshold, contours, 0, 1);
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    if (contours[i].size()>100) //&& contours[i].size()<2000)
    {
        cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
        cv::Rect appRect( boundingRect( cv::Mat(contours_poly[i]) ));
        if (appRect.width>appRect.height)
        boundRect.push_back(appRect);
    }
    
//boundrECT.
    return boundRect;
}

class node
{
    std::string data;

};

class graph
{
    
};

int main(int argc,char** argv)
{
    //Read
    std::string filename;
    std::cout<<"enter file name:";
    std::cin>>filename;
    std::string filepath = "/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork/images/";
    std::string filename_path = filepath + filename + ".jpg";
    cv::Mat image = cv::imread(filename_path);

    //Detect
    std::vector<cv::Rect> letterBBoxes=detectLetters(image);
    
    //Display
    for(int i=0; i< letterBBoxes.size(); i++)
    {
        //std::cout<<letterBBoxes[i];
        cv::Rect roi = letterBBoxes[i];
        //cv::Mat roi = cv::Mat(image, imgroi);
        cv::Mat img_roi(image, roi);
        
        filename_path = filepath + "cpp_output/" + filename + "_" + std::to_string(i+1) + ".jpg";
        cv::imwrite(filename_path, img_roi);
        std::string tess_command = "tesseract " + filename_path + " " + filepath + "cpp_output/" + filename + ".txt";
        //std::cout<<"\n"<<tess_command;
        const char * tess = tess_command.c_str ();
        
        std::system(tess);
        
        //draw rectangles
        cv::rectangle(image,letterBBoxes[i],cv::Scalar(0,255,0),3,8,0);
        filename_path = filepath + "cpp_output/" + filename + ".jpg";
        //std::cout<<"\n"<<filename_path;
        cv::imwrite( filename_path, image);
    }
    return 0;
}
