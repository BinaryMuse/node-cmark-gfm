#ifndef NODE_CMARK_ASYNC_H
#define NODE_CMARK_ASYNC_H

#include "napi.h"

Napi::Value render_html_async(const Napi::CallbackInfo& info);

#endif
