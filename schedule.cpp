/*
// schedule.h

#include <event.h>

class Schedule
{
public:

  Schedule();
  ~Schedule();
  
  bool newEvent( ifstream& input );
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
*/

#include <schedule.h>
#include <string>


Schedule::Schedule()
{
  schedule_list = nullptr;
  schedule_length = 0;
  s_ptr = 0;
}

Schedule::~Schedule()
{
  for ( int i = 0; i < next_index; i++ )
    delete schedule_list[i];
  delete [] schedule_list;
}

bool Schedule::newEvents( std::string filename )
{
  std::string linedata;
  ifstream input;
  
  if ( input.open( filename ) )
  {
    while ( std::getline( input, linedata )
    {
      if ( linedata.find("NEW_EVENT:") != std::string::npos )
      {
        std::string evstr = linedata.substr( linedata.find( ":" ) + 1 );
        auto eventTypeMap = Event::getEventMap();

        auto it = eventTypeMap.find( evstr );
        if ( it == eventTypeMap.end() )
        {
          std::cerr << "Unknown event type: " << evstr << std::endl;
          return false;
        }
        // pull enum from unordered_map
        eventType category = it->second;

        // use category to create appropriate object
        Event* newEvent = nullptr;

        switch ( category )
        {
          case eventType::LECTURE:
            newEvent = new Lecture();
            break;
          case eventType::COURSEWORK:
            newEvent = new Coursework();
            break;
          default:
            return false;
        }

        // this check also covers case where schedule_list is null
        if ( s_ptr == schedule_length )
          resizeSchedule( 2 * ( schedule_length + 1 ) );
          

        if ( newEvent )
        {
          schedule_list[s_ptr] = newEvent;
          newEvent->parseTypeData( input );
          newEvent->parseSharedData( input );
          sptr_++;
        }
      }    
    }
    return true;
  }
  else return false;
}
