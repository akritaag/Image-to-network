//
//  reduce.h
//  BoundedBox
//
//  Created by Akrita Agarwal on 11/1/14.
//  Copyright (c) 2014 Akrita Agarwal. All rights reserved.
//

#ifndef __BoundedBox__reduce__
#define __BoundedBox__reduce__

#include <stdio.h>

#endif /* defined(__BoundedBox__reduce__) */

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
