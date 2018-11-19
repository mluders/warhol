#include "gifwrapper.h"
#include <napi.h>
#include <node.h>
#include <node_buffer.h>


Napi::FunctionReference GifWrapper::constructor;

Napi::Object GifWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "GifWrapper", {
    InstanceMethod("printSettings", &GifWrapper::printSettings),
    InstanceMethod("addFrame", &GifWrapper::addFrame),
    InstanceMethod("render", &GifWrapper::render),
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

void GifWrapper::printSettings(const Napi::CallbackInfo& info) {
  _gifBuilder->printSettings();
}

void GifWrapper::addFrame(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  unsigned char* pixels = Napi::Buffer<unsigned char>(env, info[0]).Data();
  Napi::Number delay = info[1].As<Napi::Number>(); 
  _gifBuilder->addFrame(pixels, delay);
}

void GifWrapper::render(const Napi::CallbackInfo& info) {
  _gifBuilder->render();
}
