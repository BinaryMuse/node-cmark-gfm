#include <v8.h>
#include <nan.h>
#include <uv.h>

#include "cmark.h"
#include "markdown.h"
#include "async.h"

using std::vector;
using std::string;
using Nan::Callback;
using Nan::FunctionCallbackInfo;
using Nan::New;
using Nan::ThrowTypeError;
using Nan::Utf8String;
using v8::Function;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

RenderWork::RenderWork(Utf8String* markdown, Callback* callback, const int options, vector<string>* extension_names) {
  Local<Function> cb = callback->GetFunction();
  this->markdown = markdown;
  this->callback.Reset(cb);
  this->extension_names = extension_names;
  this->options = options;
};

void render_html_async(const FunctionCallbackInfo<Value>& args) {
  if (args.Length() < 1) {
    ThrowTypeError("Missing argument 'markdown'");
    return;
  }

  if (!args[0]->IsString()) {
    ThrowTypeError("Expected argument 'markdown' to be a string");
    return;
  }

  if (args.Length() < 3) {
    ThrowTypeError("Missing argument 'callback'");
    return;
  }

  if (!args[1]->IsObject()) {
    ThrowTypeError("Expected argument 'options' to be an object");
    return;
  }

  if(!args[2]->IsFunction()) {
    ThrowTypeError("Expected argument 'callback' to be a function");
    return;
  }

  vector<string>* extension_names = new vector<string>;
  Local<Object> opts_obj = args[1]->ToObject();
  int options = parse_options(opts_obj);
  populate_extension_names(opts_obj, extension_names);
  Callback callback(args[2].As<Function>());
  Utf8String* markdown = new Utf8String(args[0]);

  RenderWork* work = new RenderWork(markdown, &callback, options, extension_names);
  work->request.data = work;

  uv_queue_work(uv_default_loop(), &work->request, do_render, after_render);
}

void do_render(uv_work_t* request) {
  RenderWork* work = static_cast<RenderWork*>(request->data);
  Utf8String* markdown = work->markdown;
  vector<string>* extension_names = work->extension_names;
  char* result = markdown_to_html(**markdown, markdown->length(), work->options, extension_names);
  work->result = result;
}

void after_render(uv_work_t* request, int status) {
  Nan::HandleScope scope;
  RenderWork* work = static_cast<RenderWork*>(request->data);
  char* result = work->result;
  Local<Value> argv[] = { New<String>(result).ToLocalChecked() };
  work->callback.Call(1, argv);

  work->callback.Reset();
  delete work->markdown;
  delete work->extension_names;
  cmark_mem* default_mem = cmark_get_default_mem_allocator();
  default_mem->free(work->result);
  delete work;
}
