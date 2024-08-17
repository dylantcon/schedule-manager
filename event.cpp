  /* // event.h
// event.h
#ifndef _EVENT_H
#define _EVENT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "date.h"
#include "time.h"

enum class eventType { LECTURE, COURSEWORK, NONE };

class Event
// Event is abstract, no instantiation
{
public:

  virtual void showInfo() const = 0;
  virtual bool parseTypeData( std::ifstream& input ) = 0;

  std::string getTitle() const;
  Date getDate() const;
  Time getTime() const;
  eventType getType() const;

  virtual ~Event();

  static std::unordered_map<std::string, eventType>& getEventMap();

protected:

  std::string event_title;
  Date event_date;
  Time event_time;
  eventType event_category;

  Event() = default;
  Event( const std::string& title, 
         const Date&        date,
         const Time&        time,
         const eventType&   category );
  Event( const Event& other );
  Event& operator=( const Event& other );

};

class Coursework : public Event
{
public:

  Coursework() = default;
  Coursework( const Coursework& other );
  Coursework& operator=( const Coursework& other );
  Coursework( const std::string& title,
              const Date&        date,
              const Time&        time,
              const eventType&   category,
              const std::string& info,
              const int&         points );
  
  void showInfo() const override;
  bool parseTypeData( std::ifstream& input ) override;

private:

  std::string coursework_info;
  int coursework_points;

};

class Lecture : public Event
{
public:

  Lecture() = default;
  Lecture( const Lecture& other );
  Lecture& operator=( const Lecture& other );
  Lecture( const std::string& title,
           const Date&        date,
           const Time&        time,
           const eventType&   category,
           const std::string& location );

  void showInfo() const override;
  bool parseTypeData( std::ifstream& input ) override;

private:

  std::string lecture_location;

};
*/

#include "event.h"
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

std::string Event::getTitle() const
{
  return event_title;
}

Date Event::getDate() const
{
  return event_date;
}

Time Event::getTime() const
{
  return event_time;
}

eventType Event::getType() const
{
  return event_category;
}

Event::~Event() {}

Event::Event( const std::string& title, const Date& date, 
              const Time& time, const eventType& category = NONE )
{
  event_title = title;
  event_date = date;
  event_time = time;
  event_category = category;
}

Event::Event( const Event& other ) 
    : event_title( other.event_title ),
      event_date( other.event_date ),
      event_time( other.event_time ),
      event_category( other.event_category ) {}

Event& Event::operator=( const Event& other )
{
  if ( this != &other )
  {
    event_title = other.event_title;
    event_date = other.event_date;
    event_time = other.event_time;
    event_category = other.event_category;
  }
  return *this;
}


void Coursework::showInfo() const
{
  std::string information = coursework_info;
  const std::string bullet = "\n  - ";
  cout << "  ##### Coursework Information #####'\n'"
       << bullet << event_title << bullet << "Due "
       << event_date.dayOfWeek() << ", " << event_date << " at " 
       << event_time << '\n' << bullet 
       << "Assignment information:'\n'" << '\n';

  int linelength = 0;
  int index = n;
  bool needIndent = false;
  
  while ( index < information.length && information.at( index ) )
  {
    linelength++;
    
    if ( linelength == 48 )
      needIndent = true;
      
    if ( needIndent && isspace( information[ index ] ) )
    {
      needIndent = false;
      coursework_info.at( index - 1 ) = '\n';
      linelength = 0;
    }

    index++;
  }
  cout << information << '\n' << '\n' << '\t' << "Total Points: " << coursework_points << '\n'
}

Coursework::Coursework( const std::string& title, 
                        const Date&        date, 
                        const Time&        time, 
                        const eventType&   category,
                        const std::string& info, 
                        const int&         points 
                    ) : Student( title, date, time, COURSEWORK )
{
  coursework_info = info;
  coursework_points = points;
}

Coursework::Coursework( const Coursework& other )
    : Event( other ),
      coursework_info( other.coursework_info ),
      coursework_points( other.coursework_points ) {}

Coursework& Coursework::operator=( const Coursework& other )
{
  if ( this != &other )
  {
    Event::operator=( other );
    coursework_info = other.coursework_info;
    coursework_points = other.coursework_points;
  }
  return *this;
}

void Lecture::showInfo() const
{
  const std::string bullet = "\n  - ";
  cout << "  ##### Lecture Information #####'\n'" << bullet << event_title
       << bullet << event_date.dayOfWeek() << ", " << event_date << " at "
       << event_time << bullet << "Located at " << lecture_location << '\n';
}

Lecture::Lecture( const std::string& title, 
                  const Date&        date, 
                  const Time&        time, 
                  const eventType&   category,
                  const std::string& location                  
              ) : Student( title, date, time, LECTURE )
{
  lecture_location = location;
}

Lecture::Lecture( const Lecture& other )
    : Event( other ),
      lecture_location( other.lecture_location ) {}

Lecture& Lecture::operator=( const Lecture& other )
{
  if ( this != &other )
  {
    Event::operator=( other );
    lecture_location = other.lecture_location;
  }
  return *this;
}

std::unordered_map<std::string, eventType>& Event::getEventMap()
{
  static std::unordered_map<std::string, eventType> eventMap = {
        { "LECTURE", eventType::LECTURE },
        { "COURSEWORK", eventType::COURSEWORK },
        { "NONE", eventType::NONE }
  };
  return eventMap;
}
