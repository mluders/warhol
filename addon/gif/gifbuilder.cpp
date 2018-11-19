#include "gifbuilder.h"



GifBuilder::GifBuilder(uint32_t width, uint32_t height, uint32_t quality, bool fast, std::string outPath) {
  _settings.width = width;
  _settings.height = height;
  _settings.quality = quality;
  _settings.fast = fast;
  _outPath = outPath;

  printf("Creating a GIF\n");
  printf("    Width:    %d\n", _settings.width);
  printf("    Height:   %d\n", _settings.height);
  printf("    Quality:  %d\n", _settings.quality);
  printf("    Fast:     %s\n", _settings.fast ? "true" : "false");
  printf("    Out path: %s\n", _outPath.c_str());

  _g = gifski_new(&_settings);
  _writerThread = std::thread(&GifBuilder::writeFrames, this);
}

void GifBuilder::printSettings()
{
  printf("Width:    %d\n", _settings.width);
  printf("Height:   %d\n", _settings.height);
  printf("Quality:  %d\n", _settings.quality);
  printf("Fast:     %s\n", _settings.fast ? "true" : "false");
  printf("Out path: %s\n", _outPath.c_str());
}

void GifBuilder::addFrame(unsigned char *pixels, uint32_t delay) {
  gifski_add_frame_rgba(_g, _currentFrame, _settings.width, _settings.height, pixels, delay);
  _currentFrame++;
}

void GifBuilder::writeFrames() {
  printf("Writing frames\n");

  gifski_write(_g, _outPath.c_str());
  gifski_drop(_g);
  // Call on encoder thread:
  //if (_hasError == false) gifski_write(_g, _outPath.c_str());
  //gifski_drop(_g);
}

void GifBuilder::render() {
  gifski_end_adding_frames(_g);
  _writerThread.join();
  resetState();
}

void GifBuilder::resetState() {
  _hasError = false;
  _currentFrame = 0;
}