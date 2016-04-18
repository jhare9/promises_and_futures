//
//  main.cpp
//  promises_and_futures
//
//  Created by jonathon hare on 4/13/16.
//  Copyright © 2016 jonathon hare. All rights reserved.
//

#include <iostream>
#include "AsyncTextParser.h"

int main(int argc, const char * argv[]) {
    
    AsyncTextParser::setFileName("10.txt");
    AsyncTextParser::asyncSetCustomerNames();
    AsyncTextParser::asyncSetDivisionNames();
    AsyncTextParser::asyncGetDivisionNames();
    AsyncTextParser::asyncSetDate();
    AsyncTextParser::asyncGetDate();
    AsyncTextParser::asyncSetDollarAmount();
    AsyncTextParser::asyncGetDollarAmount();
    AsyncTextParser::asyncGetCustomerNames();
    
    
    
    int count = 1;
    for(int i = 1; i < 10; i++){
        count *=i;
        std::cout<<"count as it muiltplys in slow motion\n";
        std::cout<<count<<"\n";
        sleep(1);
    }
    
    std::cout<<"final result: "<<count<<"\n";
    
    
    AsyncTextParser::getThreads();
    std::cout<<"threads are done check the files\n"; 
    return 0;
}
