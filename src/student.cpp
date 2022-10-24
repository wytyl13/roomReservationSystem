#include "../include/student.h"
#include "../include/computerRoom.h"
using namespace std;
#include <iostream>

Student::Student()
{

}

Student::Student(int id, string name, string pwd) 
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    string fileName = "resources/";
    fileName += COMPUTER_FILE;
    // init the computerRoom information.
    ifstream ifs;
    ifs.open(fileName, ios::in);
    ComputerRoom com;
    while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();
}


//overwrite the function, you need not to use the virtual keywork in cpp file.
void Student::operateMenu() 
{
    cout << "欢迎学生代表：" << this->m_Name << "登陆！" << endl;
    cout << "\t\t --------------------------------- \n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           1.申请预约            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           2.查看我的预约        |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           3.查看所有预约        |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           4.取消预约            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           0.注销登陆            |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作：";
}


// application
void Student::applyOrder() 
{
    cout << "机房开放的时间为周一至周五！" << endl;
    cout << "请输入申请预约的时间：" << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;

    int date = 0;// date
    int interval = 0;// time
    int room = 0;// room number

    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "输入有误，请重新输入！" << endl;
    }
    cout << "请输入申请预约时间段：" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;

    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "输入错误，请重新输入！" << endl;
    }
    cout << "请选择机房：" << endl;
    for (long long unsigned int i = 0; i < vCom.size(); i++)
    {
        cout << vCom[i].m_ComId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
    }

    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "输入有误，请重新输入！" << endl;
    }
    cout << "预约成功，审核中！" << endl;

    string fileName = "resources/";
    fileName += ORDER_FILE;
    ofstream ofs;
    ofs.open(fileName, ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs<<"stuName:"<<this->m_Name<<" ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;

    ofs.close();
    system("pause");
    system("cls");
}


// show the order himself.
void Student::showMyOrder() 
{
    // define the class OrderFile, the structor will init the orderFile record.
    OrderFile of;
    // you can also use the of object to get the variable.
    // vector<string> vKey = of.getVKey();
    cout << of.vKey[0] << endl;
    if (of.m_Size == 0)
    {
        cout << "无预约记录！" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        // transform from c++ string to int, you should transform from c++ string
        // to c char, and then used atoi transform char to int in c language.
        if (this->m_Id == atoi(of.m_OrderDate[i]["stuId"].c_str()))
        {
            cout << i + 1 << "、";
            cout << "预约日期：周" << of.m_OrderDate[i][of.vKey[0]];
            cout << " 时间段：" << (of.m_OrderDate[i][of.vKey[1]] == "1" ? "上午" : "下午");
            cout << " 机房号：" << of.m_OrderDate[i][of.vKey[4]];
            string status = " 状态：";
            if (of.m_OrderDate[i][of.vKey[5]] == "1")
            {
                status += "审核中";
            }
            else if (of.m_OrderDate[i][of.vKey[5]] == "2")
            {
                status += "预约成功";
            }
            else if (of.m_OrderDate[i][of.vKey[5]] == "-1")
            {
                status += "预约失败，审核未通过！";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;
        }
    }
}


// show all order
void Student::showAllOrder() 
{
    OrderFile of;
    //  it can works, so we need not to use it.
    // vector<string> vKey = of.getVKey();
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        cout << i + 1 << "、";
        cout << "预约日期：周" << of.m_OrderDate[i][of.vKey[0]];
        cout << " 时间段：" << (of.m_OrderDate[i][of.vKey[1]] == "1" ? "上午" : "下午");
        cout << " 学号：" << of.m_OrderDate[i][of.vKey[2]];
        cout << " 姓名：" << of.m_OrderDate[i][of.vKey[3]];
        cout << " 机房号：" << of.m_OrderDate[i][of.vKey[4]];
        string status = " 状态：";
        if (of.m_OrderDate[i][of.vKey[5]] == "1")
        {
            status += "审核中";
        }
        else if (of.m_OrderDate[i][of.vKey[5]] == "2")
        {
            status += "预约成功";
        }
        else if (of.m_OrderDate[i][of.vKey[5]] == "-1")
        {
            status += "预约失败，审核未通过！";
        }
        else
        {
            status += "预约已取消";
        }
        cout << status << endl;
    }
}

// cancle all order
void Student::cancelOrder()
{
    OrderFile of;
    // 有以下两行代码完全是因为在本项目中我们在类OrderFile中使用构造函数初始化的成员属性
    // m_OrderDate and vKey 我们无法在该文件中的实例化对象所调用。所以我们定义了专门的
    // get方法去接收它。
    // map<int, map<string, string>> m_OrderDate = of.getMOrderDate();
    // vector<string> vKey = of.getVKey();
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "审核中或预约成功的记录可以取消，请输入取消的记录：" << endl;
    vector<int> v;
    int index = 1;
    for (int i = 0; i < of.m_Size; i++)
    {
        // you will can only cancel the order about yourself.
        if (this->m_Id == atoi(of.m_OrderDate[i][of.vKey[2]].c_str()))
        {
            // then you should filter the status.
            if (of.m_OrderDate[i][of.vKey[5]] == "1" || of.m_OrderDate[i][of.vKey[5]] == "2")
            {
                v.push_back(i);// store the index what meet the condition.
                cout << index++ << "、";
                cout << "预约日期：周" << of.m_OrderDate[i][of.vKey[0]];
                cout << " 时间段：" << (of.m_OrderDate[i][of.vKey[1]] == "1" ? "上午" : "下午");
                cout << " 机房号：" << of.m_OrderDate[i][of.vKey[4]];
                string status = " 状态：";
                if (of.m_OrderDate[i][of.vKey[5]] == "1")
                {
                    status += "审核中";
                }
                else if (of.m_OrderDate[i][of.vKey[5]] == "2")
                {
                    status += "预约成功";
                }
                cout << status << endl;
            }
        }
    }
    cout << "请输入取消的记录，0代表返回" << endl;
    int select = 0;
    while (true)
    {
        cin >> select;
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                of.m_OrderDate[v[select - 1]]["status"] = "0";
                of.updateOrder();
                cout << "已取消预约" << endl;
                break;
            }
        }
    }
}
