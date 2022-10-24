#include "../include/orderFile.h"
using namespace std;
/**
 * here, we can review the static keyword.
 * 1 static modified the global variable.
 *      only visible for the function in the same file.
 * 2 static modified the local variable.
 *      this variable will not end beacause the end of this function.
 * 3 static modified the function
 *      this function can only be used in the same file.
 * 4 static modified a member attribute in a class.
 *      it means this attribute will be shared for all instantiate objects of this class.
 * 5 static modified the function for one class.
 *      it means this global fucntion will can only use the static or global varaible.
*/

// define a vector to store all the key, it is dedicated to this file.
// the next code used the static keyword to modified the global variable vkey. this variable
// will can only be used in this file.
// static vector<string> vKey;

// you can also define it in the OrderFile class


// the constructor function
OrderFile::OrderFile() 
{
    // define the variable in class, and init it in structor.
    // involved the string fileName and vector<string> vKey.
    // init the fileName.
    this->fileName = "resources/";
    this->fileName += ORDER_FILE;

    // init the vKey to store the variable.
    this->vKey.push_back("date");
    this->vKey.push_back("interval");
    this->vKey.push_back("stuId");
    this->vKey.push_back("stuName");
    this->vKey.push_back("roomId");
    this->vKey.push_back("status");


    // you should init the vector first, or you will can not use the >> operation
    // to read the file and store the content used the vCon variavle.
    this->vCon.push_back("date");
    this->vCon.push_back("interval");
    this->vCon.push_back("stuId");
    this->vCon.push_back("stuName");
    this->vCon.push_back("roomId");
    this->vCon.push_back("status");

    // you should get all recode from the orderfile
    ifstream ifs;
    ifs.open(fileName, ios::in);
    this->m_Size = 0;
    while (ifs >> vCon[0] && ifs >> vCon[1] && ifs >> vCon[2] && 
        ifs >> vCon[3] && ifs >> vCon[4] && ifs >> vCon[5])
    {
        // cout << date << endl;
        // cout << interval << endl;
        // cout << stuId << endl;
        // cout << stuName << endl;
        // cout << roomId << endl;
        // cout << status << endl;
        // cout << endl;

        // then we will use the string sub function to get the key and value.
        string key;
        string value;
        map<string, string> m;

        // return the position of the ":" in date string.
        int pos;
        string str_key;
        for (vector<string>::iterator it = vCon.begin(); it != vCon.end(); it++)
        {
            str_key = *it;
            pos = str_key.find(":");
            if (pos != -1)
            {
                key = str_key.substr(0, pos);
                value = str_key.substr(pos + 1, str_key.size() - (pos + 1));
                // you should use make_pair to create a ket-value, and then insert it into
                // the map<int, map<string, string>> m_OrderDate.
                m.insert(make_pair(key, value));
            }
        }
        // input this little vevtor m into big vector m_OrderDate
        m_OrderDate.insert(make_pair(this->m_Size, m));
        this->m_Size++;
    }
    ifs.close();
}

void OrderFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        return;
    }

    ofstream ofs(this->fileName, ios::out | ios::trunc);
    for (int i = 0; i < this->m_Size; i++)
    {
        for (int j = 0; j < this->vKey.size(); j++)
        {
            ofs << this->vKey[j] << ":" << this->m_OrderDate[i][this->vKey[j]] << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

vector<string> OrderFile::getVKey()
{
    return this->vKey;
}

map<int, map<string, string>> OrderFile::getMOrderDate() 
{
    return this->m_OrderDate;
}
