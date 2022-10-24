#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "../include/globalFile.h"

// use this code, you can drop the scope of the class what you want to use.
using namespace std; 

class OrderFile
{
public:
    OrderFile();

    // update the order record.
    void updateOrder();

    // the recode size.
    int m_Size;

    // define the container to store the order information.
    // it will not have the repeat id if used the map.
    map<int, map<string, string>> m_OrderDate;

    // you can use this-> to call this variable.
    vector<string> vKey;

    // you can define the vector<string> to store the content read from the orderFile.txt
    vector<string> vCon;

    // define the fileName
    string fileName;

    // why we need to define the two get function? beacause we can not get
    // this variable in another file. this is why?
    // define the get method to use the vKey out of the class.
    // but it works nothing define the get function when I restart this vscode.
    // so it is the system error not the code error.
    // so we can define it, but you can also do not use it.
    // this two get function need not to define if the variable you want to get is public,
    // and you should define it if your variable is private. but we define it at here
    // is beacause we can not call the variable used this instance object of this class, 
    // this is a try, but we have handled it after we restart this vscode. so you can ignore
    // it.
    vector<string> getVKey();

    map<int, map<string, string>> getMOrderDate();
};
