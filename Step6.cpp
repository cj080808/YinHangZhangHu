//step6.cpp

#include"Account.h"
#include"Accumulator.h"
#include"Date.h"
#include"SavingsAccount.h"
#include"CreditAccount.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdio> // 添加这个头文件

using namespace std;

struct deleter {
    template <class T> void operator () (T* p) { delete p; }
};

// 读取、执行txt
void executeCommandsFromFile(Date& date, vector<Account*>& accounts) {
    ifstream file("commands.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            char cmd;
            iss >> cmd;

            char type;
            int index, day;
            double amount, credit, rate, fee;
            string id, desc;
            Account* account;
            Date date1, date2;

            switch (cmd) {
            case 'a': // 添加账户
                iss >> type >> id;
                if (type == 's') {
                    iss >> rate;
                    account = new SavingsAccount(date, id, rate);
                }
                else {
                    iss >> credit >> rate >> fee;
                    account = new CreditAccount(date, id, credit, rate, fee);
                }
                accounts.push_back(account);
                break;
            case 'd': // 存款
                iss >> index >> amount;
                getline(iss >> ws, desc);
                accounts[index]->deposit(date, amount, desc);
                break;
            case 'w': // 取款
                iss >> index >> amount;
                getline(iss >> ws, desc);
                accounts[index]->withdraw(date, amount, desc);
                break;
            case 's': // 查询所有账户信息
                for (size_t i = 0; i < accounts.size(); i++) {
                    cout << "[" << i << "] ";
                    accounts[i]->show();
                    cout << endl;
                }
                break;
            case 'c': // 改变日期
                iss >> day;
                if (day < date.getDay())
                    cout << "You cannot specify a previous day";
                else if (day > date.getMaxDay())
                    cout << "Invalid day";
                else
                    date = Date(date.getYear(), date.getMonth(), day);
                break;
            case 'n': // 进入下一个月
                if (date.getMonth() == 12)
                    date = Date(date.getYear() + 1, 1, 1);
                else
                    date = Date(date.getYear(), date.getMonth() + 1, 1);
                for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
                    (*iter)->settle(date);
                break;
            case 'q': // 查询一段时间内的账目
                date1 = Date::read();
                date2 = Date::read();
                Account::query(date1, date2);
                break;
            }
        }
        file.close();
    }
}

// 添加txt
void addCommandToFile(const string& command) {
    ofstream file("commands.txt", ios::app);
    if (file.is_open()) {
        file << command << endl;
        file.close();
    }
}

// 清除txt
void clearAllRecords(Date& date, vector<Account*>& accounts) {
    // 删除txt
    if (std::remove("commands.txt") == 0) {
        cout << "所有记录已清除" << endl;
    }
    else {
        cout << "清除记录失败，文件可能不存在或被占用" << endl;
    }

    // 重置账户数据
    for_each(accounts.begin(), accounts.end(), deleter());
    accounts.clear();
    Account::setTotal(0); 
    date = Date(2008, 11, 1); 
}

int main() {
    Date date(2008, 11, 1); 
    vector<Account*> accounts; 

    // 执行txt
    executeCommandsFromFile(date, accounts);

    cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit (r)reset" << endl;

    char cmd;
    do {
        // 显示日期和总金额
        date.showTime();
        cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";

        char type;
        int index, day;
        double amount, credit, rate, fee;
        string id, desc;
        Account* account;
        Date date1, date2;

        cin >> cmd;
        string command;
        command += cmd;

        switch (cmd) {
        case 'a': // 添加账户
            cin >> type >> id;
            command += " " + string(1, type) + " " + id;
            if (type == 's') {
                cin >> rate;
                command += " " + to_string(rate);
                account = new SavingsAccount(date, id, rate);
            }
            else {
                cin >> credit >> rate >> fee;
                command += " " + to_string(credit) + " " + to_string(rate) + " " + to_string(fee);
                account = new CreditAccount(date, id, credit, rate, fee);
            }
            accounts.push_back(account);
            break;
        case 'd': // 存款
            cin >> index >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, desc);
            command += " " + to_string(index) + " " + to_string(amount) + desc;
            accounts[index]->deposit(date, amount, desc);
            break;
        case 'w': // 取款
            cin >> index >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, desc);
            command += " " + to_string(index) + " " + to_string(amount) + desc;
            accounts[index]->withdraw(date, amount, desc);
            break;
        case 's': // 查询所有账户信息
            for (size_t i = 0; i < accounts.size(); i++) {
                cout << "[" << i << "] ";
                accounts[i]->show();
                cout << endl;
            }
            break;
        case 'c': // 改变日期
            cin >> day;
            command += " " + to_string(day);
            if (day < date.getDay())
                cout << "You cannot specify a previous day";
            else if (day > date.getMaxDay())
                cout << "Invalid day";
            else
                date = Date(date.getYear(), date.getMonth(), day);
            break;
        case 'n': // 进入下一个月
            if (date.getMonth() == 12)
                date = Date(date.getYear() + 1, 1, 1);
            else
                date = Date(date.getYear(), date.getMonth() + 1, 1);
            for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
                (*iter)->settle(date);
            command += "";
            break;
        case 'q': // 查询一段时间内的账目
            date1 = Date::read();
            date2 = Date::read();
            Account::query(date1, date2);
            command += " " + to_string(date1.getYear()) + "/" + to_string(date1.getMonth()) + "/" + to_string(date1.getDay()) + " "
                + to_string(date2.getYear()) + "/" + to_string(date2.getMonth()) + "/" + to_string(date2.getDay());
            break;
        case 'r': // 清除所有记录
            clearAllRecords(date, accounts);
            command = ""; // 不保存重置命令
            break;
        }

        if (cmd != 's' && cmd != 'e' && cmd != 'r') {
            addCommandToFile(command);
        }
        

    } while (cmd != 'e');

    for_each(accounts.begin(), accounts.end(), deleter());
    return 0;
}
