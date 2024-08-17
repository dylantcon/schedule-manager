#include <iostream>
#include <string>

class Date
{

  friend bool operator<( const Date& lhs, const Date& rhs );
  friend bool operator>( const Date& lhs, const Date& rhs );
  friend bool operator<=( const Date& lhs, const Date& rhs );
  friend bool operator>=( const Date& lhs, const Date& rhs );
  friend bool operator==( const Date& lhs, const Date& rhs );
  friend bool operator!=( const Date& lhs, const Date& rhs );

public:

 /* -- Date Memory Management --
  *
  * (1) Default constructor, initializes Date object to 1/1/2000
  * (2) 3 parameter constructor, initializes to date passed by const ref.
  * (3) Copy constructor
  * (4) Copy assignment operator overload
  * (5) Move constructor
  * (6) Move assignment operator overload
  * (7) Destructor
  *
  *
  * -- Methods --
  *
  * [mutators]
  * (1) Set: Sets date to specified parameters, does input validation
  * (2) Increment: Increments date by 'n' days
  * (3) getLeap: Modifies a Date's leap boolean based off year calculation, returns result
  * 
  * [accessors]
  * (1) getMonth
  * (2) getDay
  * (3) getYear
  * (4) dayOfWeek
  *
  * [comparison]
  * ( as friend functions, above)
  * { all boolean OO's }
  *
  */

  Date();
  Date( const int& month, const int& day, const int& year );
  Date( const Date& other );
  Date& operator=( const Date& rhs );
  Date( Date&& other );
  Date& operator=( Date&& rhs );
  ~Date();

  bool Set( const int& m, const int& d, const int& y );
  void Increment( int n );
  bool getLeap( const int& y );

  int getMonth() const;
  int getDay() const;
  int getYear() const;
  std::string dayOfWeek() const;

private:

  int month, day, year;
  bool leap;

  int monthEnd( const int& m ) const;

};
