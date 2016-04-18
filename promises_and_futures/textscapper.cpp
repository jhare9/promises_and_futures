//
//  textscapper.cpp
//  promises_and_futures
//
//  Created by jonathon hare on 4/13/16.
//  Copyright © 2016 jonathon hare. All rights reserved.
//

#include<iostream>
#include"textscapper.h"

textscapper::textscapper(){
    mFilepath = "";
}

textscapper::textscapper(std::string filepath){
    mFilepath = filepath;
}

void textscapper::setFileName(std::string fn){
    mFilepath = fn;
}

void textscapper::setDates(){
    
    mInput.open(mFilepath);
    
    if(!mInput.is_open()){
        std::cout<<"error opening the file\n";
        return;
    }
    // regex for date parsing. 
    std::regex reg{R"([0-1][0-9]\/[0-3][0-9]\/\d{4}|[0-1][0-9]\-[0-3][0-9]\-\d{4}|[A-z]+\s+\d{2}\,\s+\d{4}|[A-z]+\s\d{1}\,\s\d{4})"};
    std::string line;
    
    std::smatch match;
    
    //browse the file input stream for matches.
    while(std::getline(mInput,line)){
        while(std::regex_search(line,match,reg)){
            for(auto m:match) mDates.push_back(m);
            line = match.suffix().str();
        }
    }
    mInput.close();
}

void textscapper::setDollarAmounts(){
    mInput.open(mFilepath);
    
    if(!mInput.is_open()){
        std::cout<<"error opening the file\n";
        return;
    }
    
    std::regex reg1{R"(^\$$)"};
    std::regex reg2{R"(-?(?:0|[1-9]\d{0,2}(?:\,?\d{3})*)(?:\.\d+)?\s\w*illion\b|-?(?:0|[1-9]\d{0,2}(?:,?\d{3})*)(?:\.\d+)?)"};
    std::regex reg3{R"(\$-?(?:0|[1-9]\d{0,2}(?:\,?\d{3})*)(?:\.\d+)?\s\w*illion\b|\$-?(?:0|[1-9]\d{0,2}(?:,?\d{3})*)(?:\.\d+)?)"};
    std::smatch match;
    std::string line;
    
    while(getline(mInput,line)){
        
        if(std::regex_search(line,match,reg1)){
            std::string temp = match[0];
            
            getline(mInput,line);
            
            if(std::regex_search(line,match,reg2))
                mDollars.push_back(temp+""+(std::string)match[0]);
            
            
        }else{
            while(std::regex_search(line,match,reg3)){
                for(auto m: match)mDollars.push_back(m);
                
                line = match.suffix().str(); 
            }
        }
        
    }
    mInput.close();
}


void textscapper::setCustomersNames(){
    
    mInput.open(mFilepath);
    
    if(!mInput.is_open()){
        std::cout<<"error opening the file\n";
        return;
    }
    
    std::regex reg{R"((?:customers|Customers))"};
    std::regex reg2 {R"((?:[A-Z][a-z]+|[A-Z][A-Z]+|\-|\s)+(?: Inc\.|Incorporated|Limited|Company|Co\.|Corporation|Ltd\.))"};
    std::smatch match;
    
    std::string line;
    
    while(getline(mInput,line)){
        if(std::regex_search(line,match,reg))
            while(std::regex_search(line,match,reg2)){
                for(auto m:match)mCustomers.push_back(m);
        
                line = match.suffix().str();
            }
        
    }
    mInput.close();
}

void textscapper::setDivisionNames(){
    
    mInput.open(mFilepath);
    
    if(!mInput.is_open()){
        std::cout<<"error opening the file\n";
        return;
    }
    
    std::regex reg{R"(\((?:[A-Z])+[G]\))"};
    std::smatch match;
    
    std::string line;
    
    while(getline(mInput,line))
            while(std::regex_search(line,match,reg)){
                for(auto m:match){
                    long length = m.length() - 2;
                    std::string reg_conv = "((?:[A-Z][a-z]+\\s|[a-z][a-z]+\\s){"+std::to_string(length)+"}\\((?:[A-Z]|\\&)+[G]\\))";
                    std::regex reg2(reg_conv);
                    if(std::regex_search(line,match,reg2))
                        for(auto m:match)mDivisionNames.push_back(m);
                }
                line = match.suffix().str();
            }
    mInput.close();
}

void textscapper::setToTxt(std::vector<std::string> data, std::string filename){
    
    mOutput.open(filename);
    
    if(!mOutput.is_open()){
        std::cout<<"error opening the output file \n";
        return;
    }
    
    for(auto d:data){
        mOutput << d+"\n";
        mOutput.flush();
    }
    mOutput.close();
}

std::vector<std::string> textscapper::getDates(){ return mDates; }
std::vector<std::string> textscapper::getDollarAmounts(){return mDollars;}
std::vector<std::string> textscapper::getCustomerNames(){return mCustomers;}
std::vector<std::string> textscapper::getDivisionNames(){return mDivisionNames;}

