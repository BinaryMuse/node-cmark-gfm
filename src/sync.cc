#include <v8.h>
#include <nan.h>

#include "cmark.h"
#include "markdown.h"
#include "sync.h"

using std::string;
using std::vector;
using Nan::FunctionCallbackInfo;
using Nan::New;
using Nan::ThrowTypeError;
using Nan::Utf8String;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void render_html_sync(const FunctionCallbackInfo<Value>& args) {
  if (args.Length() < 1) {
    ThrowTypeError("Missing argument 'markdown'");
    return;
  }

  if (!args[0]->IsString()) {
    ThrowTypeError("Expected argument 'markdown' to be a string");
    return;
  }

  int options = CMARK_OPT_DEFAULT;
  vector<string>* extension_names = new vector<string>;
  if (args.Length() >= 2 && args[1]->IsObject()) {
    Local<Object> opts_obj = args[1]->ToObject();
    options = parse_options(opts_obj);
    populate_extension_names(opts_obj, extension_names);
  }

  Utf8String markdown(args[0]);
  char* result = markdown_to_html(*markdown, markdown.length(), options, extension_names);
  args.GetReturnValue().Set(New<String>(result).ToLocalChecked());
  free(result);
  delete extension_names;
}
