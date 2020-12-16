#include <time.h>
#include <unistd.h>
#include <string>
#include "translate.h"
#include <stdexcept>

using namespace std;

string formatIt(string outFmt, int year, int day, int mnth){
        struct tm timeinfo = {};
        char buff[1000];
        if(mnth != -1){
                timeinfo.tm_mon = mnth;
        }
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mday = day;                                                                                      
        mktime(&timeinfo);
        strftime(buff,1000,outFmt.c_str(),&timeinfo);
        outFmt = buff;
        return outFmt;
}
string strToLower(string str){                                                                                               for(int i = 0; i < int(str.size()); i++){
                str[i] = tolower(str[i]);
        }
        return str;
}
string decipher(string strIn){
        string fmt = "%04Y-%m-%d";
        string orig = strIn;
        strIn = strToLower(strIn);
        if(strIn.size() < 3){
                throw runtime_error("ERROR: data entry incomplete in line -> " + strIn);
        }
        if(strIn.compare("today") == 0 || strIn.compare("yesterday") == 0 || strIn.compare("tomorrow") == 0){
                return localDays(strIn, fmt);
        }
        if(strIn.size() == 10 && strIn[4] == '-' && strIn[7] == '-'){
                return isoFmter(orig, fmt);
        }
        return dotDay(orig, fmt);
}
string localDays(string fmt, string outFmt){
        time_t rawtime;
        struct tm timeinfo;
        time (&rawtime);
        timeinfo = *localtime (&rawtime);
        if(fmt.compare("today")==0){
                return formatIt(outFmt, timeinfo.tm_year + 1900, timeinfo.tm_yday + 1);
        }
        if(fmt.compare("yesterday")==0){
                return formatIt(outFmt, timeinfo.tm_year + 1900, timeinfo.tm_yday);
        }
        if(fmt.compare("tomorrow")==0){
                return formatIt(outFmt, timeinfo.tm_year + 1900, timeinfo.tm_yday + 2);
        }
        return fmt;
}
string isoFmter(string fmt, string outFmt){
        int day, mnth, year;
        for(int i = 0; i < int(fmt.size()); i++){
                if(!(isdigit(fmt[i]) || fmt[i] == '-')){
                        throw runtime_error("ERROR: invalid iso input format in this line -> " + fmt);
                }
        }
        try{
                day = stoi(fmt.substr(8,10));
                mnth = stoi(fmt.substr(5,7));
                year = stoi(fmt.substr(0,4));
        }catch(const std::exception& e){
                throw runtime_error("ERROR: invalid iso input format in this line -> " + fmt);
        }
        if(mnth > 12 || mnth < 1){
                throw runtime_error("ERROR: invalid iso input(month out of range) format in this line -> " + fmt);
        }
        if(year > 9999 || year < 1){
                throw runtime_error("ERROR: invalid iso input(year out of range) format in this line -> " + fmt);
        }
        int leap = 0;
        if(isLepYr(year)){leap = 1;}
        int mnthNum[] = {31,28+leap,31,30,31,30,31,31,30,31,30,31};
        if(mnthNum[mnth - 1] < day || day < 0){
                throw runtime_error("ERROR: invalid iso input(day out of range for month) format in this line -> " + fmt);
        }

        return formatIt(outFmt, year, day, mnth - 1);
}
string dotDay(string str, string outFmt){
        int year, day, leap;
        if(!(isValidForm(str))){
                throw runtime_error("ERROR: invalid year.day input format in this line -> " + str);
        }
        size_t index = str.find('.');
        try{
                year = stoi(str.substr(0, index));
                day = stoi(str.substr(index + 1, str.size()));
        }catch(const std::exception& e){
                throw runtime_error("ERROR: invalid year.day input format in this line -> " + str);
        }
        if(year > 9999 || year < 1){
                throw runtime_error("ERROR: year out of range in this line -> " + str);
        }
        leap = 0;
        if(isLepYr(year)){
                leap = 1;
        }
        if(day > 365 + leap || day < 1){
                throw runtime_error("ERROR: day out of range in this line -> " + str);
        }
        return formatIt(outFmt, year, day);
}
bool isValidForm(string str){
        int dotCnt = 0;
        size_t search = str.find('.');
        if(search == string::npos){return false;}
        for(int i = 0; i < int(str.length()); i++){
                char s = str[i];
                if(!((s >= '0' && s <= '9') || s == '.')){
                        return false;
                }if(s == '.'){
                        dotCnt++;
                }
        }
        if(dotCnt > 1){                                                                                                              return false;
        }
        return true;
}
bool isLepYr(int year){
        if(year%4 == 0){
                if(year%100 == 0){                                                                                                           if(year%400 == 0){
                                return true;
                        }
                        return false;
                }
                return true;
        }                                                                                                                    return false;
}
