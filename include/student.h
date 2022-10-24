#pragma once
#include "identity.h"
#include <vector>
#include "../include/orderFile.h"
#include "../include/computerRoom.h"

class Student : public Identity
{
public:
    Student();
    Student(int id, string name, string pwd);
    
    //the attribute dedicated to the student.
    int m_Id;

    // define the variable vector to init the computer room information.
    vector<ComputerRoom> vCom;

    //overwrite the function
    virtual void operateMenu();

    //application
    void applyOrder();

    //show the order himself.
    void showMyOrder();

    //show all order
    void showAllOrder();

    // cancle all order
    void cancelOrder();


};
