#ifndef NODE_CMARK_SYNC_H
#define NODE_CMARK_SYNC_H

#include <v8.h>
#include <nan.h>

void render_html_sync(const Nan::FunctionCallbackInfo<v8::Value>& info);

#endif
