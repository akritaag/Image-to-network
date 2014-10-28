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
#include <vector>
using namespace  std;
using namespace cv;

vector<Rect> detectLetters(Mat img)
{
    vector<Rect> boundRect;
    Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    element = getStructuringElement(MORPH_RECT, Size(10, 15) );
    morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
    vector< vector< Point> > contours;
    findContours(img_threshold, contours, 0, 1);
    vector<vector<Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    {
        if (contours[i].size()>100) //&& contours[i].size()<2000)
        {
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            Rect appRect( boundingRect( Mat(contours_poly[i]) ));
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

//functions used from http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
string trim(const string& str,
            const string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content
    
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    
    return str.substr(strBegin, strRange);
}

string reduce(const string& str,
              const string& fill = " ",
              const string& whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);
    
    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;
        
        result.replace(beginSpace, range, fill);
        
        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }
    
    return result;
}

// function modified & used from - http://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c
string replaceAll( string &s, const string &search, const string &replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos )
            break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
    return s;
}

int main(int argc,char** argv)
{
    //Read
    string filename;
    cout<<"enter file name:";
    cin>>filename;
    graph g;
    string filepath = "/Volumes/PrivetDrive/Copy/UCincy/cchmc/MapNetwork/Image-to-network/cplusplus/images/";
    if(g.isempty(filepath,filename))
    {
        string filename_path = filepath + filename + ".jpg";
        Mat image = imread(filename_path);

        //Detect
        vector<Rect> letterBBoxes=detectLetters(image);
        
        int newsize = (int)letterBBoxes.size();
        vector<node> n(letterBBoxes.size());

        //Display
        for(int i=0; i<letterBBoxes.size(); i++)
        {
            Rect roi = letterBBoxes[i];
            Mat img_roi(image, roi);
            
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
            const  string newline = "\n";
            
            str = replaceAll(str, "\n", " ");
            str = reduce(str);
        
            if(str!="")
            {
                n[i].createnode(str,roi.height,roi.width,roi.x,roi.y);
                //draw rectangles
                //rectangle(image,letterBBoxes[i],Scalar(255,255,255),3,8,0);
                rectangle(image,letterBBoxes[i],Scalar(255,255,255),CV_FILLED);
                filename_path = filepath + "cpp_output/" + filename + ".jpg";
                imwrite( filename_path, image);
            }
            else
            {
                newsize--;
            }
        }
        
        //ignore the warning for now. Create & save the graph
        try
        {
            if(g.creategraph(newsize,n,filepath,filename) == false)
                cout<<"error printing file.";
        }
        catch(Exception e)
        {
            cout<<&e;
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
