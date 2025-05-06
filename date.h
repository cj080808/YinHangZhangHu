// data.h

#ifndef _DATE_H
#define _DATE_H
#include<iostream>
class Date {
private:
	int m_year;
	int m_month;
	int m_day;

public:
	int getDay() { return m_day; }
	int getMonth() { return m_month; }
	int getYear() { return m_year; }
	Date(int year, int month, int day) :m_year(year), m_month(month), m_day(day) {}  //构造函数
	void showTime() const{	//显示当时时间
		std::cout << m_year << "-" << m_month << "-" << m_day;
	}
	int timeOfGap(Date date);	//计算时间间隔
	bool isLeapYear(int year) {	//	判断是否为闰年
		if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0) {
			return true;
		}
		else {
			return false;
		}
	}

};
