// account.h

#ifndef _ACCOUNT_H
#define _ACCOUNT_H
#include<iostream>
#include <string>
#include "date.h"
class SavingsAccount {
private:
	std::string m_id;		//账户id
	double m_balance = 0;		//余额
	double m_rate = 0;		//年利率
	Date m_lastDate;		//上一次操作时间
	double m_accumulation = 0;		//距离上次余额变化到现在 余额日积累
	static double total;
public:
	SavingsAccount(Date date, std::string id, double rate);		//初始化账户1
	std::string getId(){ return m_id; }
	double getBalance() { return m_balance; }
	double getRate(){ return m_rate; }
	void record(Date date, double amount, std::string massage);		//余额变动时记录
	double accumulate(Date date);		//计算余额日积累
	void show() { std::cout << m_id << "	Balance:  " << m_balance; }		//显示账户信息1
	
	void deposit(Date date, double amount, std::string massage);		//存款
	void withdraw(Date date, double amount, std::string massage);		//取款
	void settle(Date date);		//结算利息
	static double getTotal() { return total; }
};
#endif 
