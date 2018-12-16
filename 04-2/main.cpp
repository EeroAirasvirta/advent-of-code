#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Time {
  unsigned int hour;
  unsigned int minute;
};

struct Event {
  Time time;
  int guardId;

  enum Type {
    SHIFT_BEGIN,
    WAKE_UP,
    FALL_ASLEEP
  };
  Type type;
};

void parseRow(const std::string& row, int& currentGuard, Event& event);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return 1;
  }

  const std::string filename = argv[1];
  std::ifstream istream(filename);

  std::vector<std::string> log;
  std::string line;
  while (std::getline(istream, line) ) {
    log.push_back(line);
  }
  istream.close();

  std::sort(log.begin(), log.end());

  std::map<int, std::vector<int>> guards;
  auto currentGuard{0};
  Event prevEvent;
  for (const auto& row : log) {
    Event event;
    parseRow(row, currentGuard, event);
    if (event.type == Event::Type::SHIFT_BEGIN ||
        event.type == Event::Type::FALL_ASLEEP) {
      prevEvent = event;
      continue;
    }

    if (prevEvent.type != Event::Type::FALL_ASLEEP ||
        prevEvent.time.hour != 0) {
      std::cout << "ERROR" << std::endl;
      abort();
    }

    if (guards.count(event.guardId) == 0) {
      std::vector<int> sleepMinutes(60, 0);
      guards[event.guardId] = sleepMinutes;
    }

    auto& sleepingMinutes = guards[event.guardId];
    for (unsigned int i = prevEvent.time.minute; i < event.time.minute; ++i) {
      sleepingMinutes.at(i)++;
    }

    prevEvent = event;
  }

  int numberOfMostSleptMinutes{0};
  int mostSleptGuardId{0};
  for (const auto& guard : guards) {
    for (const auto& minute : guard.second) {
      if (minute > numberOfMostSleptMinutes) {
        numberOfMostSleptMinutes = minute;
        mostSleptGuardId = guard.first;
      }
    }
  }


  auto mostSleptGuard = guards.at(mostSleptGuardId);
  auto bestMinute = std::distance(
        mostSleptGuard.begin(),
        std::max_element(mostSleptGuard.begin(), mostSleptGuard.end()));


  std::cout << "Guard " << mostSleptGuardId << " sleeps usually on minute "
            << bestMinute << ". Answer is: " << mostSleptGuardId * bestMinute
            << std::endl;

  return 0;
}

void parseRow(const std::string& row,
              int& currentGuard,
              Event& event) {

  const auto timestampEnd = row.find(']');
  const auto timestamp = row.substr(timestampEnd - 5, 5 );
  std::istringstream is(timestamp);
  char separator;

  Time time;
  if (is >> time.hour >> separator >> time.minute) {
    event.time = time;
  } else {
    std::cerr << "Failed parsing timestamp" << std::endl;
    return;
  }

  const auto message =
    row.substr(timestampEnd + 2, row.length() - timestampEnd - 2);

  if (message == "falls asleep") {
    event.type = Event::Type::FALL_ASLEEP;
    event.guardId = currentGuard;
    return;
  }

  if (message == "wakes up") {
    event.type = Event::Type::WAKE_UP;
    event.guardId = currentGuard;
    return;
  }

  const auto idBegin = message.find('#');
  const auto idEnd = message.find(' ', idBegin);
  currentGuard = std::stoi(message.substr(idBegin + 1, idEnd - idBegin - 1));

  event.type = Event::Type::SHIFT_BEGIN;
  event.guardId = currentGuard;
}
