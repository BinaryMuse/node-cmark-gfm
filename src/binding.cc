#include "napi.h"

#include "cmark.h"
#include "markdown.h"
#include "sync.h"
#include "async.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  node_cmark_init();

  exports.Set(Napi::String::New(env, "renderHtmlSync"), Napi::Function::New(env, render_html_sync));
  exports.Set(Napi::String::New(env, "renderHtml"), Napi::Function::New(env, render_html_async));
  exports.Set(Napi::String::New(env, "smark_version"), Napi::String::New(env, cmark_version_string()));

  return exports;
}

NODE_API_MODULE(binding, Init)
