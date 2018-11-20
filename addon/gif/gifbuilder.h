#ifndef GIF_BUILDER_H
#define GIF_BUILDER_H

#include <stdint.h>
#include <string>
#include <thread>
#include "gifski.h"

class GifBuilder {
public:
  GifBuilder(uint32_t width, uint32_t height, uint32_t quality, bool fast, std::string outPath); //constructor
  void printSettings(); // print the current settings
  void addFrame(unsigned char *pixels, uint32_t delay);
  void writeFrames();
  void render();
  std::string getOutPath() { return _outPath; }
private:
  void resetState();

  GifskiSettings _settings;
  std::string _outPath;
  gifski *_g;
  std::thread _writerThread;
  uint32_t _currentFrame = 0;
  bool _hasError = false;
};

#endif // GIF_BUILDER_H
