//
//  main.cpp
//  BoundedBox
//
//  Created by Akrita Agarwal on 10/5/14.
//  Copyright (c) 2014 Akrita Agarwal. All rights reserved.
//

#include "opencv2/opencv.hpp"
#include <string>
#include <iostream>
//#include <cstdlib>
#include<stdlib.h>
#include <fstream>
#include "node.h"

std::vector<cv::Rect> detectLetters(cv::Mat img)
{
    std::vector<cv::Rect> boundRect;
    cv::Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(10, 15) );
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

bool ValidNodalText(char c)
{
    if (isalnum(c) || c=='-' || c=='&' || c == '\n' || c == ' ')
        return false;
    return true;
}

int main(int argc,char** argv)
{
    //Read
    std::string filename;
    std::cout<<"enter file name:";
    std::cin>>filename;
    graph g;
    std::string filepath = "/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork/Image-to-network/cplusplus/images/";
    if(g.isempty(filepath,filename))
    {
        //std::cout << "\n me! \n";
        std::string filename_path = filepath + filename + ".jpg";
        cv::Mat image = cv::imread(filename_path);

        //Detect
        std::vector<cv::Rect> letterBBoxes=detectLetters(image);
        
        //node* n = new node[int(letterBBoxes.size())];
        std::cout <<"size:"<<(int)letterBBoxes.size();
        node* n = (node*)malloc((int)letterBBoxes.size()*sizeof(node));

        //Display
        for(int i=0; i<letterBBoxes.size(); i++)
        {
            cv::Rect roi = letterBBoxes[i];
            cv::Mat img_roi(image, roi);
            
            filename_path = filepath + "cpp_output/" + filename + "_" + std::to_string(i+1) + ".jpg";
            cv::imwrite(filename_path, img_roi);
            std::string outputpath = filepath + "cpp_output/" + filename;
            std::string tess_command = "/usr/local/bin/tesseract " + filename_path + " " + outputpath;
            const char * tess = tess_command.c_str ();
            std::system(tess);
            std::ifstream myfile (outputpath+".txt");
            std::string str((std::istreambuf_iterator<char>(myfile)),
                            std::istreambuf_iterator<char>());
            
            //cleaning the string :- erase-remove algorithm
            str.erase(std::remove_if(str.begin(),str.end(),&ValidNodalText),str.end());
            size_t ln = str.length() - 1;
            
            for(int j=0;j<=ln;j++)
                if(str[j] == '\n')
                    str[j] = ' ';
            
            if(str!="")
            {
                (n+i)->createnode(str,roi.height,roi.width,roi.x,roi.y);
                
                //draw rectangles
                cv::rectangle(image,letterBBoxes[i],cv::Scalar(0,255,0),3,8,0);
                filename_path = filepath + "cpp_output/" + filename + ".jpg";
                cv::imwrite( filename_path, image);
            }
           
        }
        
        //ignore the warning for now. Create & save the graph
        if(g.creategraph(int(letterBBoxes.size()),n,filepath,filename) == false)
            std::cout<<"error printing file.";
        
        //removing the text area from image :- grab-cut algorithm
        for(int i=0; i<letterBBoxes.size(); i++)
        {
            cv::Rect rectangle = letterBBoxes[i];
            filename_path = filepath + "cpp_output/" + filename + "grab" ;
            
            if(i==0)
            {
                std::cout<<"here?";
                imwrite(filename_path+".jpg",image);
            }
            
            //std::cout<<"or here?"<<(char)i<<" "<<filename_path+".jpg";
            cv::Mat image = cv::imread(filename_path+".jpg");
            
            cv::Mat result; // segmentation result (4 possible values)
            cv::Mat bgModel,fgModel; // the models (internally used)
            
            // GrabCut segmentation
            cv::grabCut(image,    // input image
                        result,   // segmentation result
                        rectangle,// rectangle containing foreground
                        bgModel,fgModel, // models
                        1,        // number of iterations
                        cv::GC_INIT_WITH_RECT); // use rectangle
            
            // Get the pixels marked as likely foreground
            cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
            // Generate output image
            
            cv::Mat background(image.size(),CV_8UC3,cv::Scalar(255,255,255));
            image.copyTo(background,~result);
            
            imwrite(filename_path+".jpg",background);
            
        }
    
    }
    
    //load the graph here.
    /*
    for (int i = 0; i<g.getsize(); i++)
    {
     
    }
     */
    
    return 0;
}
