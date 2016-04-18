//
//  textscapper.h
//  promises_and_futures
//
//  Created by jonathon hare on 4/13/16.
//  Copyright © 2016 jonathon hare. All rights reserved.
//  class used to parse data in a text file specfic to one text file. 

#ifndef textscapper_h
#define textscapper_h
#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include<vector>

class textscapper{
private:
    //variables need to get the data and write the data to and from a text file.
    std::string mFilepath;
    std::ifstream mInput;
    std::ofstream mOutput;
    std::vector<std::string> mDates;
    std::vector<std::string> mDollars;
    std::vector<std::string> mCustomers;
    std::vector<std::string> mDivisionNames;
    
public:
    //default constructor
    textscapper();
    //intilizer constructor 
    textscapper(std::string filepath);
    void setFileName(std::string fn);
    //can be used to parse dates from any text file .
    void setDates();
    //can be used to parse dollar amounts from any text file.
    void setDollarAmounts();
    //can be used to get customers names only used for the included text file.
    void setCustomersNames();
    //can be used to get customers names only used for the included text file.
    void setDivisionNames();
    // used to send the data to a text file.
    void setToTxt(std::vector<std::string> data, std::string filename);
    //getters.
    std::vector<std::string>getDates();
    std::vector<std::string>getDollarAmounts();
    std::vector<std::string>getCustomerNames();
    std::vector<std::string>getDivisionNames();
};



#endif /* textscapper_h */
