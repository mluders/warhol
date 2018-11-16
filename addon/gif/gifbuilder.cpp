#include "gifbuilder.h"

GifBuilder::GifBuilder(uint32_t width, uint32_t height, uint32_t quality, bool fast, std::string outPath) {
  this->_settings.width = width;
  this->_settings.height = height;
  this->_settings.quality = quality;
  this->_settings.fast = fast;
  this->_outPath = outPath;
}

int GifBuilder::printSettings()
{
  printf("Width:    %d\n", _settings.width);
  printf("Height:   %d\n", _settings.height);
  printf("Quality:  %d\n", _settings.quality);
  printf("Fast:     %s\n", _settings.fast ? "true" : "false");
  printf("Out path: %s\n", _outPath.c_str());
  return 0;
}
