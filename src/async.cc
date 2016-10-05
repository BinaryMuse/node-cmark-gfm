#include <v8.h>
#include <nan.h>
#include <uv.h>

#include "markdown.h"
#include "async.h"

using Nan::Callback;
using Nan::FunctionCallbackInfo;
using Nan::New;
using Nan::ThrowTypeError;
using Nan::Utf8String;
using v8::Function;
using v8::Local;
using v8::String;
using v8::Value;

class RenderWork {
public:
  RenderWork(Utf8String* markdown, Callback* callback);
  uv_work_t request;
  Utf8String* markdown;
  Callback callback;
  char* result;
};

RenderWork::RenderWork(Utf8String* markdown, Callback* callback) {
  Local<Function> cb = callback->GetFunction();
  this->markdown = markdown;
  this->callback.Reset(cb);
};

void do_render(uv_work_t* request) {
  RenderWork* work = static_cast<RenderWork*>(request->data);
  Utf8String* markdown = work->markdown;
  char* result = markdown_to_html(**markdown, markdown->length());
  work->result = result;
}

void after_render(uv_work_t* request, int status) {
  Nan::HandleScope scope;
  RenderWork* work = static_cast<RenderWork*>(request->data);
  char* result = work->result;
  Local<Value> argv[] = { New<String>(result).ToLocalChecked() };
  work->callback.Call(1, argv);
}

void render_html_async(const Nan::FunctionCallbackInfo<Value>& args) {
  if (args.Length() < 1) {
    ThrowTypeError("Missing argument 'markdown' at position 0");
    return;
  }

  if (!args[0]->IsString()) {
    ThrowTypeError("Expected argument 'markdown' at position 0 to be a string");
    return;
  }

  if (args.Length() < 2) {
    ThrowTypeError("Missing argument 'callback' at position 1");
    return;
  }

  if(!args[1]->IsFunction()) {
    ThrowTypeError("Expected argument 'callback' at position 1 to be a function");
    return;
  }

  Utf8String* markdown = new Utf8String(args[0]);
  Callback callback(args[1].As<Function>());
  RenderWork* work = new RenderWork(markdown, &callback);
  work->request.data = work;

  uv_queue_work(uv_default_loop(), &work->request, do_render, after_render);
}
