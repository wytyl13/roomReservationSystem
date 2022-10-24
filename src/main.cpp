#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include "../include/student.h"
#include "../include/teacher.h"
#include "../include/manager.h"

#include "../include/globalFile.h"
#include "../include/identity.h"

/**
 * @Author: weiyutao
 * @Date: 2022-10-22 20:59:46
 * @Parameters: 
 * @Return: 
 * @Description: student menu
 */
void studentMenu(Identity *&student) 
{
    while (true)
    {
        // call the student sub menu function
        // this param student is the Identity type object, pointing to the Student type.
        // this is the application of polymorphism.
        student->operateMenu();

        Student * stu = (Student *)student;
        int select = 0;
        cin >> select;
        if (select == 1)
        {
            // apply for the order
            stu->applyOrder();
        }
        else if (select == 2)
        {
            // show the order by yourself.
            stu->showMyOrder();
        }
        else if (select == 3)
        {
            // show all order
            stu->showAllOrder();
        }
        else if (select == 4)
        {
            // cancle all the order.
            stu->cancelOrder();
        }
        else
        {
            // login out
            delete student;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");

            return;
        }
    }
}

void teacherMenu(Identity *&teacher) 
{
    while (true)
    {
        teacher->operateMenu();
        Teacher *tea = (Teacher *)teacher;
        int select = 0;
        cin >> select;

        if (select == 1)
        {   
            tea->showAllOrder();
        }
        else if (select == 2)
        {
            tea->validOrder();
        }
        else
        {
            // login out
            delete teacher;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

/**
 * @Author: weiyutao
 * @Date: 2022-10-20 13:36:52
 * @Parameters: 
 * @Return: 
 * @Description: 管理员子菜单界面.注意这里使用了引用数据类型修饰传递的指针参数。该参数传递的应该
 * 是一个父类数据类型的指针Identity指向的子类的对象manager.我们在堆区new的Manager对象
 */
void managerMenu(Identity *&manager) 
{
    while (true)
    {
        //使用Manager对象调用管理员子菜单界面
        manager->operateMenu();
        // 强转父类指针指向子类对象为子类的数据类型指针。因为我们要调用子类专用的接口了
        Manager *man = (Manager *)manager;

        int select = 0;
        //接收用户的选择
        cin >> select;
        if (select == 1)
        {
            // add admin
            man->addPerson();
        }
        else if (select == 2)
        {
            // show the admin
            man->showPerson();
        }
        else if (select == 3)
        {
            // show the room
            man->showComputer();
        }
        else if (select == 4)
        {
            // clear the order
            man->cleanFile();
        }
        else
        {
            // else select == 0, need to login out.
            delete manager;//销毁堆区new的内存，此处因为manager指向的是堆区的内存
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

void LoginIn(string fileName, int type)
{
    // define a father pointer, point to the child object.
    // inheritance, rewrite, a father pointer pointing to child object. only via this, 
    // can you realize the function polymorphism.
    Identity *person = NULL;
    string fileName1 = "resources/";
    fileName1 += fileName;
    // use the fstream package to read local file.
    ifstream ifs;
    ifs.open(fileName1, ios::in);// read a file.
    // do a judge, if the file is exist?
    if (!ifs.is_open())
    {
        cout << "file is not exist!" << endl;
        ifs.close();
        return;
    }
    //define the variable to accept the user input.
    int id = 0;
    string name;
    string pwd;
    // do d judge
    if (type == 1)
    {   
        cout<<"请输入你的学号："<<endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout<<"请输入你的职工号："<<endl;
        cin >> id;
    }
    // manager need not to login, beacause has no id.
    cout << "请输入你的姓名：" << endl;
    cin >> name;
    cout << "请输入你的密码：" << endl;
    cin >> pwd;

    if (type == 1)
    {
        // check the student identity
        int fId;
        string fName;
        string fPwd;
        cout << id << endl;
        cout << name << endl;
        cout << pwd << endl;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {

                cout << "学生验证登陆成功！" << endl;
                system("pause");
                system("cls");
                
                person = new Student(id, name, pwd);

                // the you should enter the studentMenu if success login in
                studentMenu(person);

                return;
            }
        }
        cout << "验证不通过！请重新输入！" << endl;
        return;
    }
    else if (type == 2)
    {
        // chech the teacher identity
        int fId;
        string fName;
        string fPwd;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "教师验证登陆成功" << endl;
                system("pause");
                system("cls");

                person = new Teacher(id, name, pwd);
                teacherMenu(person);
                return;
            }
        }
        cout << "验证不通过！请重新输入！" << endl;
        return;
    }
    else if (type == 3)
    {
        // chech the manager identity
        string fName;
        string fPwd;
        while (ifs >> fName && ifs >> fPwd)
        {
            if (fName == name && fPwd == pwd)
            {
                cout << "管理员登陆成功" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, pwd);
                managerMenu(person);

                return;
            }

        }
        cout << "验证不通过！请重新输入！" << endl;
        return;
    }

    cout << "登陆成功！" << endl;
    system("pause");
    system("cls");

    return;
}

int main(int argc, char const *argv[])
{

    int select = 0;

    while (true)
    {
        cout << "=================  欢迎使用机房预约系统 ====================" << endl;
        cout << endl
            << "请输入您的选择：" << endl;
        cout<<"\t\t --------------------------------- \n";
        cout<<"\t\t|                                 |\n";
        cout<<"\t\t|           1.学生代表            |\n";
        cout<<"\t\t|                                 |\n";
        cout<<"\t\t|           2.老师                |\n";
        cout<<"\t\t|                                 |\n";
        cout<<"\t\t|           3.管理员              |\n";
        cout<<"\t\t|                                 |\n";
        cout<<"\t\t|           0.退出                |\n";
        cout<<"\t\t ---------------------------------\n";
        cout<<"请输入您的选择：";
        cin >> select;
        switch (select)
        {
        case 1://student
            LoginIn(STUDENT_FILE, 1);
            break;
        case 2://teacher
            LoginIn(TEACHER_FILE, 2);
            break;
        case 3://admin
            LoginIn(ADMIN_FILE, 3);
            break;
        case 0://exit
            cout << "欢迎下次使用！" << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    system("pause");
    return 0;
}



