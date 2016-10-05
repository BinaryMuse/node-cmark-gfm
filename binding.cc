#include <node.h>
#include <v8.h>
#include <uv.h>
#include <nan.h>

#include "cmark.h"

using namespace v8;
using namespace node;
using Nan::New;
using Nan::ThrowTypeError;

class RenderWork {
public:
  RenderWork(Nan::Utf8String* markdown, Nan::Callback* callback);
  uv_work_t request;
  Nan::Utf8String* markdown;
  Nan::Callback callback;
  char* result;
};

RenderWork::RenderWork(Nan::Utf8String* markdown, Nan::Callback* callback) {
  Local<Function> cb = callback->GetFunction();
  this->markdown = markdown;
  this->callback.Reset(cb);
};

void render_sync(const Nan::FunctionCallbackInfo<Value>& args) {
  if (args.Length() < 1) {
    ThrowTypeError("Missing argument 'markdown' at position 0");
    return;
  }

  if (!args[0]->IsString()) {
    ThrowTypeError("Expected argument 'markdown' at position 0 to be a string");
    return;
  }

  Nan::Utf8String markdown(args[0]);
  const char* result = cmark_markdown_to_html(*markdown, markdown.length(), 0);
  args.GetReturnValue().Set(New<String>(result).ToLocalChecked());
}

void do_render(uv_work_t* request) {
  RenderWork* work = static_cast<RenderWork*>(request->data);
  Nan::Utf8String* markdown = work->markdown;
  char* result = cmark_markdown_to_html(**markdown, markdown->length(), 0);
  work->result = result;
}

void after_render(uv_work_t* request, int status) {
  Nan::HandleScope scope;
  RenderWork* work = static_cast<RenderWork*>(request->data);
  char* result = work->result;
  Local<Value> argv[] = { New<String>(result).ToLocalChecked() };
  work->callback.Call(1, argv);
}

void render_async(const Nan::FunctionCallbackInfo<Value>& args) {
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

  Nan::Utf8String* markdown = new Nan::Utf8String(args[0]);
  Nan::Callback callback(args[1].As<Function>());
  RenderWork* work = new RenderWork(markdown, &callback);
  work->request.data = work;

  uv_queue_work(uv_default_loop(), &work->request, do_render, after_render);
}

void init(Local<Object> exports) {
  exports->Set(New("renderSync").ToLocalChecked(), New<FunctionTemplate>(render_sync)->GetFunction());
  exports->Set(New("render").ToLocalChecked(), New<FunctionTemplate>(render_async)->GetFunction());
}

NODE_MODULE(binding, init)
