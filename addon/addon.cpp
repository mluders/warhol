/* cppsrc/main.cpp */
#include <napi.h>
#include "gif/gifwrapper.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return GifWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)