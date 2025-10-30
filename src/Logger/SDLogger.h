#ifndef SDLOGGER_H
#define SDLOGGER_H

#include <SD.h>
#include <string>

class SDLogger {
public:
  int begin(const char* FileLog, const char* FileEvent);
  void log(String line);
  void logEvent(String event);
  File getFile(const char* filename);

private:
  const char* FileLog;
  const char* FileEvent;
  File logFile;
  void listFiles(File dir, int numTabs);
};

#endif