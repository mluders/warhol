#include "gifwrapper.h"

Napi::FunctionReference GifWrapper::constructor;

Napi::Object GifWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "GifWrapper", {
    InstanceMethod("printSettings", &GifWrapper::printSettings),
    InstanceMethod("printSettingsVoid", &GifWrapper::printSettings),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("GifWrapper", func);
  return exports;
}

GifWrapper::GifWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<GifWrapper>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  /*int length = info.Length();
  if (length != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }*/

  Napi::Number width = info[0].As<Napi::Number>();
  Napi::Number height = info[1].As<Napi::Number>();
  Napi::Number quality = info[2].As<Napi::Number>();
  Napi::Boolean fast = info[3].As<Napi::Boolean>();
  Napi::String outPath = info[4].As<Napi::String>();

  
  this->_gifBuilder = new GifBuilder(width, height, quality, fast, outPath);
}

Napi::Value GifWrapper::printSettings(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::EscapableHandleScope scope(env);

  int err = this->_gifBuilder->printSettings();
  return scope.Escape(Napi::Number::New(env, err));
}

void GifWrapper::printSettingsVoid() {
  this->_gifBuilder->printSettings();
}
