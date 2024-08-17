#include "time.h"
#include <iomanip>

Time::Time() : hours(12), minutes(0), pm(false) {}

Time::Time(const int& hours, const int& minutes, const bool& is_pm)
{
    if (!Set(hours, minutes, is_pm))
        *this = Time();
}

Time::Time(const Time& other)
    : hours(other.hours), minutes(other.minutes), pm(other.pm) {}

Time& Time::operator=(const Time& rhs)
{
    if (this != &rhs)
    {
        this->hours = rhs.hours;
        this->minutes = rhs.minutes;
        this->pm = rhs.pm;
    }
    return *this;
}

Time::Time(Time&& other)
    : hours(other.hours), minutes(other.minutes), pm(other.pm) {}

Time& Time::operator=(Time&& rhs)
{
    if (this != &rhs)
    {
        this->hours = rhs.hours;
        this->minutes = rhs.minutes;
        this->pm = rhs.pm;
    }
    return *this;
}

Time::~Time() {}

bool Time::Set(const int& h, const int& m, const bool& is_pm)
{
    if (h < 1 || h > 12 || m < 0 || m >= 60)
        return false;

    this->hours = h;
    this->minutes = m;
    this->pm = is_pm;
    return true;
}

const int Time::getHours() const
{
    return this->hours;
}

const int Time::getMinutes() const
{
    return this->minutes;
}

const bool Time::isPM() const
{
    return this->pm;
}

bool operator<(const Time& lhs, const Time& rhs)
{
    if (lhs.pm != rhs.pm)
        return lhs.pm < rhs.pm;

    if (lhs.hours != rhs.hours)
        return lhs.hours < rhs.hours;

    return lhs.minutes < rhs.minutes;
}

bool operator>(const Time& lhs, const Time& rhs)
{
    return rhs < lhs;
}

bool operator<=(const Time& lhs, const Time& rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const Time& lhs, const Time& rhs)
{
    return !(lhs < rhs);
}

bool operator==(const Time& lhs, const Time& rhs)
{
    return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes && lhs.pm == rhs.pm;
}

bool operator!=(const Time& lhs, const Time& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
    os << std::setw(2) << std::setfill('0') << time.hours << ":"
       << std::setw(2) << std::setfill('0') << time.minutes << " "
       << (time.pm ? "PM" : "AM");
    return os;
}
