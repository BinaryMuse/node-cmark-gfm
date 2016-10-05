#ifndef NODE_CMARK_ASYNC_H
#define NODE_CMARK_ASYNC_H

#include <v8.h>
#include <nan.h>

void render_html_async(const Nan::FunctionCallbackInfo<v8::Value>& info);

#endif
