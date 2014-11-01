//
//  node.cpp
//  BoundedBox
//
//  Created by Akrita Agarwal on 10/16/14.
//  Copyright (c) 2014 Akrita Agarwal. All rights reserved.
//

#include "node.h"
#include "opencv2/opencv.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;
using namespace cv;
void node::createnode(std::string d,int h,int w,int x,int y)
{
    this->data.assign(d);
    this->height = h;
    this->width = w;
    this->x = x;
    this->y = y;
}
    
bool node::isempty(std::string data)
{
    if (data.compare("") == 0)
        return true;
    return false;
}

bool graph::isempty(std::string filepath,std::string filename)
{
    std::ifstream ifile(filepath+filename+".csv");
    if(ifile)
        return false;
    return true;
}
    
//write the graph to file
bool graph::creategraph(int size,vector<node> n,std::string filepath,std::string filename)
{
    this->size = size;
    if (this->isempty(filepath,filename))
    {
        std::ofstream myfile(filepath+filename+".csv");
        if (myfile.is_open())
        {
            for(int i=0;i<size;i++)
            {
                try {
                    //myfile <<n[i].data<<","<<n[i].height<<","<<n[i].width<<","<<n[i].x<<","<<n[i].y<<"\n";
                    myfile<<n[i].data<<","<<n[i].height<<n[i].width<<","<<n[i].x<<","<<n[i].y<<"\n";
                }
                catch(cv::Exception e)
                {
                    std::cout<<"something went wrong"<<&e;
                }
            }
            
        }
        myfile.close();
        return true;
    }
    return false;
}
    
void graph::loadgraph(std::string filepath,std::string filename)
{
    //node* n;
    /*
    try
    {
        if(!graph::isempty(filepath,filename))
        {
            //read .csv file
        }
    }
    catch(cv::Exception e)
    {
        std::cout<< &e;
    }
     */
    //return NULL;
}

int graph::getsize(void)
{
    return this->size;
}

