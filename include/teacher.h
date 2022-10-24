#pragma once
#include "identity.h"

class Teacher : public Identity
{
public:
    Teacher();
    Teacher(int empId, string name, string pwd);

    // the empId dedicated to the teacher.
    int m_EmpId;

    virtual void operateMenu();

    //show all the order
    void showAllOrder();

    //valid all the order
    void validOrder();
};