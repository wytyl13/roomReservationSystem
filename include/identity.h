#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "globalFile.h"

class Identity
{
public:

    //operate the menu, you should use the keywork virtual.
    //if the father class use the virtual for function, then child class must rewrite
    //this function, or child class can not instantiate objects.
    virtual void operateMenu() = 0;

    string m_Name;
    string m_Pwd;
    string fileName = "resources/";
};
