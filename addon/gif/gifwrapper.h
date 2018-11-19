#ifndef GIF_WRAPPER_H
#define GIF_WRAPPER_H

#include <napi.h>
#include "gifbuilder.h"

class GifWrapper : public Napi::ObjectWrap<GifWrapper> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports); // Init function for setting the export key to JS
  GifWrapper(const Napi::CallbackInfo& info); // Constructor to initialize

private:
  static Napi::FunctionReference constructor; // Reference to store the class definition that needs to be exported to JS
  void printSettings(const Napi::CallbackInfo& info); // Wrapped printSettings function
  void addFrame(const Napi::CallbackInfo& info);
  void render(const Napi::CallbackInfo& info);

  GifBuilder *_gifBuilder; // Internal instance of GifBuilder used to perform actual operations.
};

#endif // GIF_WRAPPER_H
