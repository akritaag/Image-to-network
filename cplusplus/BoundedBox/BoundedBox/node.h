//
//  node.h
//  BoundedBox
//
//  Created by Akrita Agarwal on 10/16/14.
//  Copyright (c) 2014 Akrita Agarwal. All rights reserved.
//

#ifndef __BoundedBox__node__
#define __BoundedBox__node__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#endif /* defined(__BoundedBox__node__) */

using namespace std;

class node
{
public:
    
    //members
    string data;
    int height,width,x,y;
    
    //functions
    void createnode (string d,int h,int w,int x,int y);
    bool isempty(string data);

};

class graph
{
    int size;
public:
    
    bool isempty(string filepath,string filename);
    
    //write the graph to file
    bool creategraph(int size,vector<node> n,string filepath,string filename);
    void loadgraph(string filepath,string filename);
    int getsize(void);
    
};