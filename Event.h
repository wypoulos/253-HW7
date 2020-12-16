// Wow its Event.h

#ifndef event_included
#define event_included
#include <string>
#include <iostream>
class Event{
	int yr;
	int dy;
	int mth;
	public:
	Event() =  delete;
	Event(const char* str);
	Event(const std::string &str);
	Event(const Event &evt) = default;
	Event &operator=(const Event &rhs) = default;
	~Event() = default;
	void set(int year, int month, int day);
	int year() const;
	int month() const;
	int day() const;
	std::string fmt(std::string outfmt = "%04Y-%m-%d")const;
	void adjust(int val);
	Event operator++();
	Event operator++(int);
	Event operator--();
	Event operator--(int);
	bool operator==(const Event &rhs) const;
	bool operator!=(const Event &rhs) const;
	bool operator<=(const Event &rhs) const;
	bool operator>=(const Event &rhs) const;
	bool operator<(const Event &rhs) const;
	bool operator>(const Event &rhs) const;	
};

#endif

