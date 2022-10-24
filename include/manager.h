#pragma once
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include <vector>
#include "computerRoom.h"

class Manager : public Identity
{
public:
    Manager();
    
    Manager(string name, string pwd);

    virtual void operateMenu();

    void addPerson();

    void showPerson();

    void showComputer();

    void cleanFile();

    //初始化容器，来保存从磁盘中读取的数据
    void initVector();

    bool checkRepeat(int id, int type);

    vector<Student> vStu;

    vector<Teacher> vTea;

    vector<ComputerRoom> vCom;
};