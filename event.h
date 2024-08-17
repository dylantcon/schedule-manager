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
  
#endif
