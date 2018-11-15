#include <node.h>
#include <node_buffer.h>
#include <nan.h>
#include <pthread.h>
#include "gifski.h"

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Exception;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Boolean;
using v8::Value;
using v8::Function;
using v8::Persistent;

gifski *g;
GifskiSettings settings;
pthread_t writerThread;
bool hasError = false;
int currentFrame = 0;

void reset_state() {
  hasError = false;
  currentFrame = 0;
}

void abort_gif() {
  hasError = true;
  gifski_end_adding_frames(g);
  pthread_join(writerThread, NULL);
  reset_state();
  printf("GIF was aborted\n");

}

static void *write_frames(void*) {
  // Call on encoder thread:
  if (hasError == false) gifski_write(g, "./hello.gif");
  gifski_drop(g);
}

bool throw_exception(Isolate* isolate, const char * message) {
  isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, message)));
  return false;
}

bool create_gif_args(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if (args.Length() != 4)             return throw_exception(isolate, "Wrong number of arguments");
  if (args[0]->IsInt32() == false)    return throw_exception(isolate, "Expected 'width' to be an integer");
  if (args[1]->IsInt32() == false)    return throw_exception(isolate, "Expected 'height' to be an integer");
  if (args[2]->IsInt32() == false)    return throw_exception(isolate, "Expected 'quality' to be an integer");
  if (args[3]->IsBoolean() == false)  return throw_exception(isolate, "Expected 'fast' to be a boolean");
  return true;
}

void create_gif(const FunctionCallbackInfo<Value>& args) { // width, height, quality, fast
  if (create_gif_args(args) == false) return;
  currentFrame = 0;
  hasError = false;

  settings.width = args[0]->IntegerValue();
  settings.height = args[1]->IntegerValue();
  settings.quality = args[2]->IntegerValue();
  settings.once = false;
  settings.fast = args[3]->BooleanValue();

  printf("Creating a GIF\n");
  printf("    width:   %d\n", settings.width);
  printf("    height:  %d\n", settings.height);
  printf("    quality: %d\n", settings.quality);
  printf("    fast:    %s\n", settings.fast ? "true" : "false");

  g = gifski_new(&settings);
  pthread_create(&writerThread, NULL, write_frames, NULL);
}

void add_frame(const FunctionCallbackInfo<Value>& args) {
  unsigned char *arr = reinterpret_cast<unsigned char *>(node::Buffer::Data(args[0]));

  /*if (bufferLength < settings.width * settings.height * 4) {
    throw_exception(isolate, "Unexpected buffer length");
    abort_gif();
    return;
  }*/
  printf("Current frame: %d\n", currentFrame);
  gifski_add_frame_rgba(g, currentFrame, settings.width, settings.height, arr, 10);
  currentFrame++;
}

void end_adding_frames(const FunctionCallbackInfo<Value>& args) {
  gifski_end_adding_frames(g);
  pthread_join(writerThread, NULL);
  //printf("Gif was rendered successfully\n");
  reset_state();

  v8::Persistent<v8::Function> r_call;
  Isolate* isolate = args.GetIsolate();
  v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[0]);
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { v8::String::NewFromUtf8(isolate, "Render complete") };
  func->Call(v8::Null(isolate), argc, argv);
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "create_gif", create_gif);
  NODE_SET_METHOD(exports, "add_frame", add_frame);
  NODE_SET_METHOD(exports, "end_adding_frames", end_adding_frames);

}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo
