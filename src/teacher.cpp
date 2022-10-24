#include "../include/teacher.h"
#include "../include/orderFile.h"

Teacher::Teacher() 
{
    
}
Teacher::Teacher(int empId, string name, string pwd) 
{
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

void Teacher::operateMenu() 
{
    cout << "欢迎教师：" << this->m_Name << "登陆！" << endl;
    cout << "\t\t --------------------------------- \n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           1.查看所有预约        |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           2.审核预约            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|           0.注销登陆            |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作：";
}

//show all the order
void Teacher::showAllOrder() 
{
    OrderFile of;
    // it is show all order
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

//valid all the order
void Teacher::validOrder() 
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }

    vector<int> v;
    int index = 0;
    cout << "待审核的预约记录如下：" << endl;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_OrderDate[i]["status"] == "1")
        {
            v.push_back(i);
            cout << ++index << "、";
            cout << "预约日期：周" << of.m_OrderDate[i][of.vKey[0]];
            cout << " 时间段：" << (of.m_OrderDate[i][of.vKey[1]] == "1" ? "上午" : "下午");
            cout << " 学号：" << of.m_OrderDate[i][of.vKey[2]];
            cout << " 姓名：" << of.m_OrderDate[i][of.vKey[3]];
            cout << " 机房号：" << of.m_OrderDate[i][of.vKey[4]];
            string status = " 状态：审核中";
            cout << status << endl;
        }
    }
    cout << "请输入审核的预约记录，0代表返回" << endl;
    int select = 0;
    int ret = 0;
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
                cout<<"请输入审核结果"<<endl;
                cout << "1、通过" << endl;
                cout << "2、不通过" << endl;
                cin >> ret;
                // status : 1/2/-1  审核中/通过/不通过
                if (ret == 1)
                {
                    // pass
                    of.m_OrderDate[v[select - 1]]["status"] = "2";
                }
                else
                {
                    // no pass
                    of.m_OrderDate[v[select - 1]]["status"] = "-1";
                }
                of.updateOrder();
                cout << "审核完毕！" << endl;
                return;
            }
        }
        cout << "输入有误，请重新输入" << endl;
    }
    system("pause");
    system("cls");
}