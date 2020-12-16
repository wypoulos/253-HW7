//Wow its translate.h

#ifndef translate_included
#define translate_included
#include <string>
std::string formatIt(std::string outFmt, int year, int day, int mnth = -1);
std::string decipher(std::string str);
std::string localDays(std::string fmt, std::string outFmt);
std::string isoFmter(std::string fmt, std::string outFmt);
std::string dotDay(std::string str, std::string outFmt);
bool isValidForm(std::string str);
std::string strToLower(std::string str);
bool isLepYr(int year);
#endif
