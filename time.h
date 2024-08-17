// time.h
#include <iostream>

class Time
{
    friend bool operator<(const Time& lhs, const Time& rhs);
    friend bool operator>(const Time& lhs, const Time& rhs);
    friend bool operator<=(const Time& lhs, const Time& rhs);
    friend bool operator>=(const Time& lhs, const Time& rhs);
    friend bool operator==(const Time& lhs, const Time& rhs);
    friend bool operator!=(const Time& lhs, const Time& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Time& time);

public:
    Time();
    Time(const int& hours, const int& minutes, const bool& is_pm);
    Time(const Time& other);
    Time& operator=(const Time& rhs);
    Time(Time&& other);
    Time& operator=(Time&& rhs);
    ~Time();

    bool Set(const int& h, const int& m, const bool& is_pm);
    const int getHours() const;
    const int getMinutes() const;
    const bool isPM() const;

private:
    int hours;
    int minutes;
    bool pm;
};
