#include "date.h"
using namespace std;

Date::Date()
{
  month = 1;
  day = 1;
  year = 2000;
  leap = true;
}
  
Date::Date( const int& month, const int& day, const int& year )
{
  if ( !Set( month, day, year ) )
    *this = Date();
}

Date::Date( const Date& other )
{
  this->month = other.month;
  this->day = other.day;
  this->year = other.year;
  this->leap = other.leap;
}

Date& Date::operator=( const Date& rhs )
{
  if ( this != &rhs )
  {
    this->month = rhs.month;
    this->day = rhs.day;
    this->year = rhs.year;
    this->leap = rhs.leap;
  }
  return *this;
}

Date::Date( Date&& other )
{
  this->month = other.month;
  this->day = other.day;
  this->year = other.year;
  this->leap = other.leap;
}

Date& Date::operator=( Date&& rhs )
{
  if ( this != &rhs )
  {
    this->month = rhs.month;
    this->day = rhs.day;
    this->year = rhs.year;
    this->leap = rhs.leap;
  }
  return *this;
}

Date::~Date() {}

bool Date::Set( const int& m, const int& d, const int& y )
{
  if ( y < 1 )
    return false;
    
  else
  {
    if ( m > 12 || m < 1 )
      return false;

    // month/year is checked, now ascertain leapness
   bool temp = this->getLeap( y );

    if ( d > monthEnd( m ) || d < 1 )
    {
      leap = temp;
      return false;
    }
  }
  // input now validated; change data and return true
  this->month = m;
  this->day = d;
  this->year = y;

  return true;
}

void Date::Increment( int n )
{
  if ( n > 0 )
  {
    for ( int i = 0; i < n; n-- )
    {
      if ( !Set( month, ++day, year ) )
      { 
        day = 1;
        if ( !Set( ++month, day, year ) )
        {
          month = 1;
          ++year;
          getLeap( year );
        }
      }
    }
  } 
}

bool Date::getLeap( const int& y )
{
  if ( ( y % 4 == 0 && !( y % 100 == 0 ) ) || y % 400 == 0 )
    leap = true;
    
  else
    leap = false;
    
  return leap;
}

int Date::getMonth() const
{
  return this->month;
}

int Date::getDay() const
{
  return this->day;
}

int Date::getYear() const
{
  return this->year;
}

std::string Date::dayOfWeek() const
{
  int m = month;
  int d = day;
  int y = year;

  // adjust for Zeller's Congruence if necessary;
  // years start in March, end in February
  if ( m < 3 )
  {
    m += 12;
    y--;
  }

  // K is y's value down from the tenths place (Year of century)
  // J is y's value up from the hundreds place (Zero based century)
  int K = y % 100;
  int J = y / 100;
  
  // Zeller's Congruence formula
  int f = d + ( 13 * ( m + 1 ) ) / 5 + K + ( K / 4 ) + ( J / 4 ) + 5 * J;
  int day = f % 7;

  switch ( day )
  {
    case 0:
      return "Saturday";
    case 1:
      return "Sunday";
    case 2:
      return "Monday";
    case 3:
      return "Tuesday";
    case 4:
      return "Wednesday";
    case 5:
      return "Thursday";
    case 6:
      return "Friday";
    default:
      return "Unknown";
  }    
}

bool operator<( const Date& lhs, const Date& rhs )
{
  if ( lhs.year < rhs.year )
    return true;

  else if ( lhs.month < rhs.month )
    return true;

  else if ( lhs.day < rhs.day )
    return true;
    
  else
    return false;
}  

bool operator>( const Date& lhs, const Date& rhs )
{
  if ( lhs.year > rhs.year )
    return true;

  else if ( lhs.month > rhs.month )
    return true;

  else if ( lhs.day > rhs.day )
    return true;

  else
    return false;
}

bool operator<=( const Date& lhs, const Date& rhs )
{
  return !( lhs > rhs );
}

bool operator>=( const Date& lhs, const Date& rhs )
{
  return !( lhs < rhs );
}   

bool operator==( const Date& lhs, const Date& rhs )
{
  return ( !( lhs < rhs ) && !( rhs > lhs ) );
}

int Date::monthEnd( const int& m ) const
// object must enter function with 'm' in valid semantic state
{
  switch ( m )
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      return 31;
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
    case 2:
      if ( this->leap )
        return 28;
      return 29;
    // default case should never happen
    default:
      throw ( int() );
      return -1;
  }
}
