//data.cpp
#include"date.h"
int Date::timeOfGap(Date lastdate) {	
	int Month[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	int days1 = Month[lastdate.getMonth() - 1] + lastdate.getDay();
	if (lastdate.getMonth() > 2 && isLeapYear(lastdate.getYear())) {
		days1++;
	}
	int days2 = Month[getMonth() - 1] + getDay();
	if (getMonth() > 2 && isLeapYear(getYear())) {
		days2++;
	}


	for (int y = 1; y < lastdate.getYear(); y++) {
		days1 += 365;
		if (isLeapYear(y)) {
			days1++;
		}
	}
	for (int y = 1; y < getYear(); y++) {
		days2 += 365;
		if (isLeapYear(y)) {
			days2++;
		}
	}

	int dayOfGap = days2 - days1;
	return dayOfGap;
}
