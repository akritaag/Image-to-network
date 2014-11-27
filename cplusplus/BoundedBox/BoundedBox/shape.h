//
//  shape.h
//  BoundedBox
//
//  Created by Akrita Agarwal on 11/13/14.
//  Copyright (c) 2014 Akrita Agarwal. All rights reserved.
//

#ifndef BoundedBox_shape_h
#define BoundedBox_shape_h

#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

#endif
using namespace std;
using namespace cv;

static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/**
 * Helper function to display text in the center of a contour
 */
void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;
    
    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);
    
    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}

bool detectshape(Mat src)
{
    src = cv::imread("/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork/Image-to-network/cplusplus/images/sample22/4.png");
    if (src.empty())
        return -1;
    //THRESH_TOZERO
    //cout<<src;
    
    //convert to grayscale
    Mat gray, src_gray;
    cvtColor(src,gray,CV_BGR2GRAY);
    
    //convert to binary image using Canny
    Mat bw;
    blur( src_gray, bw, Size(3,3) );
    //void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false )
    Canny(gray,bw,0,50,5);

    imwrite("/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork/Image-to-network/cplusplus/images/cpp_output/canny.jpg",bw);
    
    //Find contours
    vector<vector<Point>> contours;
    findContours(bw.clone(),contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    //The array for storing the approximation curve
    vector<Point> approx;
    
    //we'll put the labels in this destination image
    Mat dst = src.clone();
    //cout<<"\n contour size:"<<contours.size();
    
    for(int i=0;i<contours.size();i++)
    {
        //Approximate contour with accuracy propotional
        //to the contour perimeter
        approxPolyDP( Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02,true );
        
        //skip small or non-convex objects
        if(fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
            continue;
        
        int a = (int)approx.size();
        if (a!= 0)
        {
            //cout<<"\n contour no. :"<<i+1<<" size: "<<to_string(a);
            setLabel(dst, to_string(a), contours[i]);
        }
        
        /*
        if(approx.size() == 3)
            setLabel(dst, "TRI", contours[i]); //TRI
        
        //either 6 or 7
        else if(approx.size() >=6)
        {
            //number of vertices of polygonal curve
            int vtc = (int)approx.size();
            
            //Get the degree (in cosines) of all corners
            vector<double> cos;
            for(int j=2;j<vtc+1;j++)
                cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));
            
            //sort ascending the corner degree values
            sort(cos.begin(), cos.end());
            
            //Get the lowest and the highest degree
            double mincos = cos.front();
            double maxcos = cos.back();
            
            //use the degrees obtained above and the no. of vertices
            //to determine the shape of the contour
            if(vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
            {
                //detect rect
                Rect r = boundingRect(contours[i]);
                double ratio = abs(1 - (double)r.width / r.height);
                
                setLabel(dst, ratio <= 0.02 ? "SQU" : "RECT", contours[i]);
            }
            else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
                setLabel(dst, "PENTA", contours[i]);
            else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
                setLabel(dst, "HEXA", contours[i]);
            else if (vtc == 7)// && mincos >= -0.55 && maxcos <= -0.45)
                setLabel(dst, "ARROW", contours[i]);
            
        }
        else if(approx.size() == 7)
            setLabel(dst, "ARROW", contours[i]); //ARROW
        else
        {
            // Detect and label circles
            double area = cv::contourArea(contours[i]);
            cv::Rect r = cv::boundingRect(contours[i]);
            int radius = r.width / 2;
            
            if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
            {
                setLabel(dst, "CIR", contours[i]);
            }
        }
         */
    }
    
    //cout<<"ps? "<<contours.size();
    imwrite("/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork/Image-to-network/cplusplus/images/cpp_output/dest.jpg",dst);
    return 0;
    
}