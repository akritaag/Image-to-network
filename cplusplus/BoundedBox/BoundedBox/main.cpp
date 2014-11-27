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
#include <cstdlib>
#include <fstream>
#include "node.h"
#include "reduce.h"
#include <vector>
#include "shape.h"

using namespace  std;
using namespace cv;

vector<Rect> detectLetters(Mat img)
{
    vector<Rect> boundRect;
    Mat img_gray, img_sobel, img_threshold, element;
    GaussianBlur( img, img, Size(3,3), 0, 0, BORDER_DEFAULT );
    cvtColor(img, img_gray, CV_BGR2GRAY);
    Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_BINARY+CV_THRESH_OTSU);
    element = getStructuringElement(MORPH_RECT, Size(10, 3) ); //Size(10, 3)
    morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
    vector< vector<Point> > contours;
    findContours(img_threshold, contours, 0, 1);
    vector<vector<Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    {
        if (contours[i].size()>100) //&& >100 contours[i].size()<2000)
        {
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            Rect appRect( boundingRect( Mat(contours_poly[i]) ));
            cout<<"contour : "<<i<<" w:"<<appRect.width<<" h:"<< appRect.width;
            if (appRect.width>appRect.height)
                boundRect.push_back(appRect);
        }
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
    string filename;
    cout<<"enter file name:";
    cin>>filename;
    graph g;
    Mat image;
    string filepath = "/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork/Image-to-network/cplusplus/images/";
    //checks for existance of the .csv file
    if(g.isempty(filepath,filename))
    {
        string filename_path = filepath + filename + ".jpg";
        image = imread(filename_path);

        //Detect letters.
        vector<Rect> letterBBoxes=detectLetters(image);
        
        int newsize = (int)letterBBoxes.size();
        vector<node> n(newsize);

        int i=0,j=0;

        for(; i<newsize;i++)
        {
            Rect roi = letterBBoxes[i];
            Mat img_roi(image, roi);
            
            Mat imageMat = img_roi;
            cvtColor(imageMat, imageMat, COLOR_BGR2GRAY);
            GaussianBlur(imageMat, imageMat, Size(3, 3), 0);
            adaptiveThreshold(imageMat, imageMat, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 4);
            img_roi = imageMat;
            filename_path = filepath + "cpp_output/" + filename + "_" + to_string(i+1) + ".jpg";
            imwrite(filename_path, img_roi);
            string outputpath = filepath + "cpp_output/" + filename;
            string tess_command = "/usr/local/bin/tesseract " + filename_path + " " + outputpath;
            const char * tess = tess_command.c_str ();
            system(tess);
            ifstream myfile (outputpath+".txt");
            string str((istreambuf_iterator<char>(myfile)),
                            istreambuf_iterator<char>());
            
            //cleaning the string :- erase-remove algorithm
            str.erase(remove_if(str.begin(),str.end(),&ValidNodalText),str.end());
            
            str = replaceAll(str, "\n", " ");
            str = reduce(str);
        
            if(str!="")
            {
                n[j].createnode(str,roi.height,roi.width,roi.x,roi.y);
                //draw rectangles
                rectangle(image,letterBBoxes[i],Scalar(255,0,255),3,8,0);
                //rectangle(image,letterBBoxes[i],Scalar(255,255,255),CV_FILLED);
                filename_path = filepath + "cpp_output/" + filename + ".jpg";
                imwrite( filename_path, image);
                j++;
            }
        }
        
        n.erase(n.begin()+j,n.end());
        
        //ignore the warning for now. Create & save the graph
        try
        {
            if(g.creategraph((int)n.size(),n,filepath,filename) == false)
                cout<<"error printing file.";
        }
        catch(Exception e)
        {
            cout<<&e;
        }
    }
    //11.29 8.47
    
    //load the graph here.
    /*
    for (int i = 0; i<g.getsize(); i++)
    {
     
    }
    */
    
    //load the other files here.
    string scene_path = filepath+"cpp_output/"+ filename + ".jpg"; //object_path = filepath + "sample22/1.jpg",
    //cout<<"scene path:"<<scene_path<<"\n";
    Mat scene = imread(scene_path);
    //cout<<"scene:"<<scene<<"\n";
    //imshow("src", scene);
    cout<<"\n worked? ";
    detectshape(scene);
    
    return 0;
}
