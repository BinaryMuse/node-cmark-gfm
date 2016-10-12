#include <v8.h>
#include <nan.h>

#include "cmark.h"
#include "markdown.h"

int get_option(v8::Local<v8::Object> options_obj, const char* option_name, int option_value) {
  Nan::MaybeLocal<v8::Value> val = Nan::Get(options_obj, Nan::New<v8::String>(option_name).ToLocalChecked());
  if (val.IsEmpty()) return false;

  v8::Local<v8::Value> bool_val = val.ToLocalChecked();
  return Nan::Equals(bool_val, Nan::True()).FromMaybe(false) ? option_value : 0;
}

int parse_options(v8::Local<v8::Object> options_obj) {
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
