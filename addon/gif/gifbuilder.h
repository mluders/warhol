#ifndef GIF_BUILDER_H
#define GIF_BUILDER_H

#include <stdint.h>
#include <string>
#include "gifski.h"

class GifBuilder {
 public:
  GifBuilder(uint32_t width, uint32_t height, uint32_t quality, bool fast, std::string outPath); //constructor
  int printSettings(); // print the current settings
 private:
  GifskiSettings _settings;
  std::string _outPath;
};

#endif // GIF_BUILDER_H
