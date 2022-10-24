#include "../include/manager.h"
#include <algorithm>

Manager::Manager() 
{
    
}

Manager::Manager(string name, string pwd) 
{
    this->m_Name = name;
    this->m_Pwd = pwd;
    this->initVector();

    // init the computerRoom object
    ifstream ifs;

    // notice, you should use the program name as the current dir.
    // it is different from the include file path, this reason is that the include path is during compilering,
    // and the reading file is during the executive. it means the current path is include for former, and 
    // is program name roomReservationSystem for last. so include should us the path ../include/, and the 
    // read path should use the resources/ directly. you need only to known, you should use the current dir
    // if you want to include a file, and should use the program name as the relative path if you want to
    // read a file.
    string fileName = "resources/";
    fileName += COMPUTER_FILE;
    ifs.open(fileName, ios::in);

    ComputerRoom com;
    while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();
    cout << "机房的数量为：" << vCom.size() << endl;
}

void Manager::operateMenu() 
{
    cout << "欢迎管理员：" << this->m_Name << "登陆！" << endl;
    cout << "\t\t --------------------------------- \n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           1.添加账号            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           2.查看账号            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           3.查看机房            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           4.清空预约            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           0.注销登陆            |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作：";
}

void Manager::addPerson() 
{
    cout << "请输入添加账号的类型：" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加老师" << endl;

    string fileName;
    string tip; // id号类型提示
    string errorTip;// error repeat 提示
    ofstream ofs;//文件操作对象,fstream head file.

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        fileName = STUDENT_FILE;
        tip = "请输入学号：";
        errorTip = "学号重复，请重新输入";
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "请输入职工号：";
        errorTip = "职工号重复，请重新输入";
    }

    string fileName1 = "resources/";
    fileName1 += fileName;
    // write and append the content to fileName.
    ofs.open(fileName1, ios::out | ios::app);

    int id;
    string name;
    string pwd;

    //check id
    while (true)
    {
        cout << tip << endl;
        cin >> id;
        bool ret = checkRepeat(id, select);
        if (ret)
        {
            // repeat
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }

    cout << "请输入姓名：" << endl;
    cin >> name;

    cout << "请输入密码：" << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << endl;//append content to fileName.
    cout << "添加成功" << endl;
    system("pause");
    system("cls");

    ofs.close();

    // 当程序执行的过程中，每更新一次数据，可能是添加也可能是删除
    // 就需要初始化当前容器一次。因为我们添加和删除都是直接操作的
    // 文件，而容器中保存的是程序刚开始执行读取的数据，所以每凑操作一次
    // io就要初始化一次容器，但是我们也完全可以在程序执行的过程中
    // 仅对容器进行添加和删除操作，然后在程序结束的时候再进行io操作。就是使用
    // 容器去同步本地文件。当然这个效率是最高的，减少了io的频繁操作
    // 这里使用的办法是每次进行的管理操作都进行IO，然后每次IO完成后同步下容器。
    this->initVector();//这样就可以解决在同一个程序运行阶段重复检验错误的问题。
}

void printStudent(Student &s) 
{
    cout << s.m_Id << "\t" << s.m_Name << "\t" << s.m_Pwd << endl;
}

void printTeacher(Teacher &t) 
{
    cout << t.m_EmpId << "\t" << t.m_Name << "\t" << t.m_Pwd << endl;
}

void Manager::showPerson() 
{
    cout << "请选择查看的内容：" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有老师" << endl;

    int select = 0;
    cin >> select;
    if (select == 1)
    {
        cout << "所有学生信息如下：" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else
    {
        cout << "所有老师信息如下：" << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
        
    }
    system("pause");
    system("cls");
}

void Manager::showComputer() 
{
    cout << "机房信息如下：" << endl;
    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << it->m_ComId << "\t" << it->m_MaxNum << endl;
    }
    system("pause");
    system("cls");
}

void Manager::cleanFile() 
{
    string fileName = "resources/";
    fileName += ORDER_FILE; 
    // you should write this file used truncate method if you want to clear it.
    // so you should use the function ofstream.
    ofstream ofs(fileName, ios::trunc);
    ofs.close();
    cout << "清空成功！" << endl;
    system("pause");
    system("cls");
}

void Manager::initVector() 
{
    vStu.clear();
    vTea.clear();

    //读取信息 student
    ifstream ifs;
    string fileName = "resources/";
    fileName += STUDENT_FILE;
    ifs.open(fileName, ios::in);

    if (!ifs.is_open())
    {
        cout << "文件读取失败！" << endl;
        return;
    }

    Student s;
    while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
    {
        vStu.push_back(s);
    }

    cout << "当前学生数量为：" << vStu.size() << endl;
    ifs.close();

    //读取信息 teacher
    fileName = "resources/";
    fileName += TEACHER_FILE;
    ifs.open(fileName, ios::in);
    Teacher t;
    while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    cout << "当前老师数量为：" << vTea.size() << endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type) 
{
    if (type == 1)
    {
        //cheack student
        for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            if (id == it->m_Id)
                return true;
        }
    }
    else
    {
        // check teacher
        for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            if (id == it->m_EmpId)
                return true;
        }
    }
    return false;
}