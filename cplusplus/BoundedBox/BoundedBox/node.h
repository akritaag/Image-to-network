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

#endif /* defined(__BoundedBox__node__) */

class node
{
public:
    
    //members
    std::string data;
    int height,width,x,y;
    
    //functions
    void createnode (std::string d,int h,int w,int x,int y);
    bool isempty(std::string data);

};

class graph
{
    int size = NULL;
public:
    
    bool isempty(std::string filepath,std::string filename);
    
    //write the graph to file
    bool creategraph(int size,node* n,std::string filepath,std::string filename);
    node* loadgraph(std::string filepath,std::string filename);
    int getsize(void);
    
};