// Wow is Schedule.h
#ifndef schedule_included
#define schedule_included
#include <iostream>
#include <string>
#include <vector>
#include "Event.h"

class Schedule{
	std::vector<Event> vents;
	public:
	typedef std::vector<Event>::const_iterator iterator;
	Schedule() = default;
	Schedule(std::istream& strm);
	Schedule(const char *str);
	Schedule(std::string str);
	Schedule(const Schedule &sch) = default;
	Schedule &operator=(const Schedule &sch) = default;
	~Schedule() = default;
	void read(std::istream& strm);
	void clear();
	size_t size() const;
	bool empty();
	const Event& operator[](size_t szt) const;

	iterator begin() const;
	iterator end() const;
};
bool sorthelp(Event i, Event j);
std::ostream& operator<<(std::ostream& oStrm, const Event& eve);
std::ostream& operator<<(std::ostream& oStrm, const Schedule& sch);

#endif

