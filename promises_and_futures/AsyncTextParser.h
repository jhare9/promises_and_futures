//
//  AsyncTextParser.h
//  promises_and_futures
//
//  Created by jonathon hare on 4/17/16.
//  Copyright © 2016 jonathon hare. All rights reserved.
// used to parse a text file async.

#ifndef AsyncTextParser_h
#define AsyncTextParser_h
#include "textscapper.h"
#include<future>
#include<mutex>

namespace AsyncTextParser{

textscapper ts = textscapper();
// global variables need for the async interface.
std::vector<std::shared_future<void>> thread;
std::mutex mew;
std::future<std::vector<std::string>>dateFuture;
std::future<std::vector<std::string>>dollarFuture;
std::future<std::vector<std::string>>customerFuture;
std::future<std::vector<std::string>>divisionFuture;

// set the file path of the textscaper class.
void setFileName(std::string fn){
    ts.setFileName(fn);
}

// critical section for setting the date in the textscapper class.
void setDate(){
    mew.lock();
    std::promise<std::vector<std::string>> p;
    dateFuture = p.get_future();
    ts.setDates();
    p.set_value(ts.getDates());
    mew.unlock();
}

//critical section for getting the date in the textscapper class.
void getDate(){
    while(true){
        if(dateFuture.valid()){
            mew.lock();
            ts.setToTxt(dateFuture.get(),"dates.txt");
            mew.unlock();
            return;
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
}

//critialal section for setting the dollar amounts in the textscapper class.
void setDollars(){
    mew.lock();
    std::promise<std::vector<std::string>> p;
    dollarFuture = p.get_future();
    ts.setDollarAmounts();
    p.set_value(ts.getDollarAmounts());
    mew.unlock(); 
}

//critical section for getting the dollar amounts in the textscapper class.
void getDollars(){
    while(true)
        if(dollarFuture.valid()){
            mew.lock();
            ts.setToTxt(dollarFuture.get(),"dollars.txt");
            mew.unlock();
            return;
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
}

//critical section for setting the customers in the textscapper class.
void setCustomers(){
    mew.lock();
    std::promise<std::vector<std::string>> p;
    customerFuture = p.get_future();
    ts.setCustomersNames();
    p.set_value(ts.getCustomerNames());
    mew.unlock();
}

//critical section for getting the customers in the textscapper class.
void getCustomers(){
    while(true)
        if(customerFuture.valid()){
            mew.lock();
            ts.setToTxt(customerFuture.get(),"customers.txt");
            mew.unlock();
            return;
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
}

//critical section for setting the divisions in the textscapper class.
void setDivision(){
    mew.lock();
    std::promise<std::vector<std::string>> p;
    divisionFuture = p.get_future();
    ts.setDivisionNames();
    p.set_value(ts.getDivisionNames());
    mew.unlock();
}

//critical section for getting the divison in the textscapper class.
void getDivision(){
    while(true)
        if(divisionFuture.valid()){
            mew.lock();
            ts.setToTxt(divisionFuture.get(),"divisions.txt");
            mew.unlock();
            return;
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
}

// functions used to get the and set the data async/////////////

void asyncSetDate(){
    thread.push_back(std::async(std::launch::async,setDate));
}


void asyncGetDate(){
    thread.push_back(std::async(std::launch::async,getDate));
}
void asyncSetDollarAmount(){
    thread.push_back(std::async(std::launch::async,setDollars));
}


void asyncGetDollarAmount(){
    thread.push_back(std::async(std::launch::async,getDollars));
}

void asyncSetCustomerNames(){
    thread.push_back(std::async(std::launch::async,setCustomers));
}

void asyncGetCustomerNames(){
    thread.push_back(std::async(std::launch::async,getCustomers));
}

void asyncSetDivisionNames(){
    thread.push_back(std::async(std::launch::async,setDivision));
}

void asyncGetDivisionNames(){
    thread.push_back(std::async(std::launch::async,getDivision));
}

/////////////////////////////////////////////////////////////////

// function to join the threads back to the main thread. 
void getThreads(){
    for(auto threads:thread)
        threads.get();
}
    
}

#endif /* AsyncTextParser_h */
