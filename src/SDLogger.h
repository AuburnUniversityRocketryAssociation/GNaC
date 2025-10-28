#ifndef SDLOGGER_H
#define SDLOGGER_H

#include <SD.h>
#include <string>

class SDLogger {
public:
  int begin();
  void log(String line);
  File getLogFile();

private:
  File logFile;
};

#endif