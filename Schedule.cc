// Wow its Schedule.cc
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "translate.h"
#include "Event.h"
#include "Schedule.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

bool sorthelp(Event i, Event j){
        if(i.year() == j.year()){
                if(i.month() == j.month()){
                        if(i.day() == j.day()){
                                return true;
                        }else if(i.day() < j.day()){
                                return true;
                        }else{
                                return false;
                        }
                }else if(i.month() < j.month()){
                	return true;
                }else{
                	return false;
                }
        }else if(i.year() < j.year()){
                return true;
        }else{
                return false;
    }
}
Schedule::Schedule(istream& strm){
	read(strm);
}
Schedule::Schedule(const char *str) : Schedule(string(str)){}
Schedule::Schedule(string str){
	ifstream ifs(str);
	if(ifs.rdstate() & ios::failbit){
		throw runtime_error("ERROR: Could not open file -> " + str);
	}
	read(ifs);
}
void Schedule::read(istream& strm){
	string evt;
	while(strm >> evt){
		try{
			Event tent(evt);
			vents.push_back(tent);
		}catch(const std::exception& e){
			strm.setstate(ios::failbit);
			throw runtime_error(e.what());
			break;
		}
	}
	sort(vents.begin(), vents.end(), sorthelp);
}
void Schedule::clear(){
	vents.clear();
}
size_t Schedule::size() const{
	return vents.size();
}
bool Schedule::empty(){
	return vents.empty();
}
const Event& Schedule::operator[](size_t szt) const{
	if(szt > vents.size()-1){
		string err("ERROR: Index out of range -> Provided Index: " + to_string(szt));
		string err2(" # of events: " + to_string(vents.size()));
		err.append(err2);
		throw range_error(err); 
	}
	return vents.at(szt);
}

Schedule::iterator Schedule::begin() const{
	return vents.begin();
}
Schedule::iterator Schedule::end() const{
	return vents.end();
}

ostream& operator<<(ostream& oStrm, const Event& eve){
	ostringstream ss;
	ss <<setfill('0')<<setw(4)<<eve.year()<<'-'
                <<setfill('0')<<setw(2)<<eve.month()<<'-'<<setfill('0')<<setw(2)<<eve.day();
	string fin(ss.str());
	oStrm << fin;
	return oStrm;
}
ostream& operator<<(ostream& oStrm, const Schedule& sch){
	for(int i = 0; i < int(sch.size()); i++){
		ostringstream ss;
		ss <<setfill('0')<<setw(4)<<sch[i].year()<<'-'
                        <<setfill('0')<<setw(2)<<sch[i].month()<<'-'
                        <<setfill('0')<<setw(2)<<sch[i].day()<<'\n';
		string fin(ss.str());
		oStrm << fin;
	}
	return oStrm;
}




