// Wow its Event.cc
#include "Event.h"
#include "translate.h"
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fstream>

using namespace std;
Event::Event(const char* str) : Event(string(str)){}

Event::Event(const string &str){
	string strx = str;
	strx = decipher(strx);
	try{
		dy = stoi(strx.substr(8, 10));
		mth = stoi(strx.substr(5, 7));
		yr = stoi(strx.substr(0, 4));
	}catch(const std::exception& e){
		throw runtime_error("Error: invalid Event with this time stamp -> " + strx);
	}
	
}
void Event::set(int year, int month, int day){
	if(month > 12 || month < 1){
                throw runtime_error("ERROR: invalid(month out of range) trying to set value to -> " + month);
        }
        if(year > 9999 || year < 1){
                throw runtime_error("ERROR: invalid(year out of range) trying to set value to -> " + year);
        }
	int leap = 0;
        if(isLepYr(year)){leap = 1;}
        int mnthNum[] = {31,28+leap,31,30,31,30,31,31,30,31,30,31};
        if(mnthNum[month - 1] < day || day < 0){
                throw runtime_error("ERROR: invalid(day out of range for month) format in this line -> " + day);
        }
	yr = year;
	dy = day;
	mth = month;
}
int Event::year() const{
        return yr;
}
int Event::month() const{
        return mth;
}
int Event::day() const{
        return dy;
}

string Event::fmt(string outFmt) const{
        struct tm timeinfo = {};
        char buff[1000];
        if(mth != -1){
                timeinfo.tm_mon = mth - 1;
        }
        timeinfo.tm_year = yr - 1900;
        timeinfo.tm_mday = dy;
        mktime(&timeinfo);
        strftime(buff,1000,outFmt.c_str(),&timeinfo);
        outFmt = buff;
        return outFmt;
}
void Event::adjust(int val){
	struct tm timeinfo = {};
        if(mth != -1){
                timeinfo.tm_mon = mth - 1;
        }
        timeinfo.tm_year = yr - 1900;
        timeinfo.tm_mday = dy + val;
        mktime(&timeinfo);
	int year = timeinfo.tm_year + 1900;
	int month = timeinfo.tm_mon + 1;
	int dayOfMon = timeinfo.tm_mday;
	if(year < 1 || year > 9999){
		throw runtime_error("ERROR: invalid(year out of range) when performing year when trying to get -> " + year);
	}
	yr = year;
	mth = month;
	dy = dayOfMon;
}
//Pre-inc
Event Event::operator++(){
	adjust(1);
	return *this;
}
//Post-inc
Event Event::operator++(int){
	Event temp = *this;
	adjust(1);
	return temp;
}
//Pre-dec
Event Event::operator--(){
	adjust(-1);
	return *this;
}
//Post-dec
Event Event::operator--(int){
	Event temp = *this;
	adjust(-1);
	return temp;
}
bool Event::operator==(const Event &rhs) const{
	if(yr == rhs.year()){
		if(mth == rhs.month()){
			if(dy == rhs.day()){
				return true;
			}
		}
	}
	return false;
}
bool Event::operator!=(const Event &rhs) const{
	if(yr == rhs.year()){
                if(mth == rhs.month()){
                        if(dy == rhs.day()){
                                return false;                                                                                                }
                }
        }
        return true;		
}
bool Event::operator<=(const Event &rhs) const{
	if(yr <= rhs.year()){
		if(mth <= rhs.month()){
			if(dy <= rhs.day()){
				return true;
			}
			return true;
		}
		return true;
	}
	return false;
}
bool Event::operator>=(const Event &rhs) const{
	if(yr >= rhs.year()){
		if(mth >= rhs.month()){
			if(dy >= rhs.day()){
				return true;
			}
			return true;
		}
		return true;
	}
	return false;
}
bool Event::operator<(const Event &rhs) const{
	if(yr <= rhs.year()){
		if(yr == rhs.year()){
			if(mth <= rhs.month()){
				if(mth == rhs.month()){
					if(dy <= rhs.day()){
						if(dy == rhs.day()){
							return false;
						}
						return true;
					}
					return false;
				}
				return true;
			}
			return false; 
		}
		return true;
	}
	return false;

}
bool Event::operator>(const Event &rhs) const{
	if(yr >= rhs.year()){
		if(yr == rhs.year()){
			if(mth >= rhs.month()){
				if(mth == rhs.month()){
					if(dy >= rhs.day()){
						if(dy == rhs.day()){
							return false;
						}
						return true;
					}
					return false;
				}
				return true;
			}
			return false; 
		}
		return true;
	}
	return false;
}



