#ifndef NODE_CMARK_ASYNC_H
#define NODE_CMARK_ASYNC_H

#include <v8.h>
#include <nan.h>
#include <uv.h>

class RenderWork {
public:
  RenderWork(Nan::Utf8String* markdown, Nan::Callback* callback, const int options);
  uv_work_t request;
  Nan::Utf8String* markdown;
  Nan::Callback callback;
  int options;
  char* result;
};

void render_html_async(const Nan::FunctionCallbackInfo<v8::Value>& info);
void do_render(uv_work_t* request);
void after_render(uv_work_t* request, int status);

#endif
