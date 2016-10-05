#include <node.h>
#include <v8.h>
#include <uv.h>
#include <nan.h>

#include "markdown.h"
#include "sync.h"
#include "async.h"

using Nan::New;
using v8::FunctionTemplate;
using v8::Local;
using v8::Object;

void init(Local<Object> exports) {
  exports->Set(New("renderHtmlSync").ToLocalChecked(), New<FunctionTemplate>(render_html_sync)->GetFunction());
  exports->Set(New("renderHtml").ToLocalChecked(), New<FunctionTemplate>(render_html_async)->GetFunction());
}

NODE_MODULE(binding, init)
