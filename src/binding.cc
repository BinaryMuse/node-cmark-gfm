#include <node.h>
#include <v8.h>
#include <uv.h>
#include <nan.h>

#include "cmark.h"
#include "markdown.h"
#include "sync.h"
#include "async.h"

using Nan::New;
using v8::Function;
using v8::Local;
using v8::Object;

void init(Local<Object> exports) {
  node_cmark_init();

  exports->Set(New("renderHtmlSync").ToLocalChecked(), New<Function>(render_html_sync));
  exports->Set(New("renderHtml").ToLocalChecked(), New<Function>(render_html_async));
  exports->Set(New("cmark_version").ToLocalChecked(), New(cmark_version_string()).ToLocalChecked());
}

NODE_MODULE(binding, init)
