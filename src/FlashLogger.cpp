#include "FlashLogger.h"




int FlashLogger::begin() {

  flash.begin();
  return 0;
}

void FlashLogger::log(String line) {
  // gives rolling log functionality
  buffer[writeIndex] = line;
  writeIndex = (writeIndex + 1) % MAX_ENTRIES;
}

bool FlashLogger::dumpToSD(File& sdFile) {
  if (!sdFile) return false;
  for (size_t i = 0; i < MAX_ENTRIES; ++i) {
    size_t idx = (writeIndex + i) % MAX_ENTRIES;
    if (buffer[idx].length() > 0) {
      sdFile.println(buffer[idx]);
    }
  }
  sdFile.flush();
  return true;
}