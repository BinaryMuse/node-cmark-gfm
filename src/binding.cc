#include "napi.h"

#include "cmark-gfm.h"
#include "markdown.h"
#include "sync.h"
#include "async.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  node_cmark_init();

  exports.Set("renderHtmlSync", Napi::Function::New(env, render_html_sync));
  exports.Set("renderHtml", Napi::Function::New(env, render_html_async));
  exports.Set("cmark_version", Napi::String::New(env, cmark_version_string()));

  return exports;
}

NODE_API_MODULE(binding, Init)
