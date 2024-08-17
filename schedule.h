// schedule.h

#include <event.h>

class Schedule
{
public:

  Schedule();
  ~Schedule();
  
  bool newEvents( ifstream& input );
  bool makeEventRecurring( const Date& enddate, const bool* daysMarked );
  bool removeEventInstance( const Date& whichDate, const std::string& whichString );
  bool removeEventsRange( const Date& from, const Date& to );

private:

  // uses user-defined comparison operator overload to sort
  // in ascending chronological order
  void heapsortSchedule();
  void resizeSchedule( int numEvents );

  Event* schedule_list;
  int schedule_length;
  int s_ptr;

};
