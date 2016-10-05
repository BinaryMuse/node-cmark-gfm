#include <v8.h>
#include <nan.h>

#include "markdown.h"
#include "sync.h"

using Nan::FunctionCallbackInfo;
using Nan::New;
using Nan::ThrowTypeError;
using Nan::Utf8String;
using v8::String;
using v8::Value;

void render_html_sync(const FunctionCallbackInfo<Value>& args) {
  if (args.Length() < 1) {
    ThrowTypeError("Missing argument 'markdown' at position 0");
    return;
  }

  if (!args[0]->IsString()) {
    ThrowTypeError("Expected argument 'markdown' at position 0 to be a string");
    return;
  }

  Utf8String markdown(args[0]);
  char* result = markdown_to_html(*markdown, markdown.length());
  args.GetReturnValue().Set(New<String>(result).ToLocalChecked());
  free(result);
}
