#include <v8.h>
#include <nan.h>

#include "cmark.h"
#include "markdown.h"

using v8::Local;
using v8::Object;
using v8::Value;
using Nan::Equals;
using Nan::Get;
using Nan::MaybeLocal;
using Nan::New;
using Nan::True;

  v8::Local<v8::Value> bool_val = val.ToLocalChecked();
  return Nan::Equals(bool_val, Nan::True()).FromMaybe(false) ? option_value : 0;
}

int get_option(Local<Object> options_obj, const char* option_name, int option_value) {
  MaybeLocal<Value> val = Get(options_obj, New(option_name).ToLocalChecked());
  if (val.IsEmpty()) return 0;

  Local<Value> bool_val = val.ToLocalChecked();
  return Equals(bool_val, True()).FromMaybe(false) ? option_value : 0;
}

int parse_options(Local<Object> options_obj) {
  int result = CMARK_OPT_DEFAULT;
  result |= get_option(options_obj, "sourcepos", CMARK_OPT_SOURCEPOS);
  result |= get_option(options_obj, "safe", CMARK_OPT_SAFE);
  result |= get_option(options_obj, "nobreaks", CMARK_OPT_NOBREAKS);
  result |= get_option(options_obj, "hardbreaks", CMARK_OPT_HARDBREAKS);
  result |= get_option(options_obj, "normalize", CMARK_OPT_NORMALIZE);
  result |= get_option(options_obj, "validateUtf8", CMARK_OPT_VALIDATE_UTF8);
  result |= get_option(options_obj, "smart", CMARK_OPT_SMART);
  return result;
}

char* markdown_to_html(const char* markdown, const int len) {
  return cmark_markdown_to_html(markdown, len, 0);
}
