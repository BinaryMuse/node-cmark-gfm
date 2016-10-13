#include <v8.h>
#include <nan.h>

#include "cmark.h"
#include "markdown.h"
#include "parser.h"
#include "registry.h"
#include "syntax_extension.h"
#include "core-extensions.h"

using std::vector;
using std::string;
using v8::Array;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using Nan::Equals;
using Nan::Get;
using Nan::MaybeLocal;
using Nan::New;
using Nan::ThrowTypeError;
using Nan::True;

void node_cmark_init() {
  cmark_register_plugin(core_extensions_registration);
}

void populate_extension_names(Local<Object> options_obj, vector<string>* extension_names) {
  Local<String> name = New("extensions").ToLocalChecked();
  MaybeLocal<Value> val = Get(options_obj, name);
  if (val.IsEmpty()) return;

  Local<Array> exts = Local<Array>::Cast(val.ToLocalChecked());
  for(uint32_t i = 0; i < exts->Length(); i++) {
    Local<Value> ext_name = exts->Get(i);
    if (!ext_name->IsString()) {
      string bad_ext_name(*Nan::Utf8String(ext_name->ToString()));
      string err_msg = "'" + bad_ext_name + "' is not a valid extension name.";
      ThrowTypeError(err_msg.c_str());
      return;
    }
    Nan::Utf8String ext(ext_name);
    cmark_syntax_extension* stx_ext = cmark_find_syntax_extension(*ext);
    if (stx_ext == NULL) {
      string bad_ext_name(*ext);
      string err_msg = "'" + bad_ext_name + "' is not a valid extension name.";
      ThrowTypeError(err_msg.c_str());
      return;
    }
    extension_names->push_back(*ext);
  }
}

int get_option(Local<Object> options_obj, const char* option_name, int option_mask) {
  Local<String> name = New(option_name).ToLocalChecked();
  MaybeLocal<Value> val = Get(options_obj, name);
  if (val.IsEmpty()) return 0;

  Local<Value> bool_val = val.ToLocalChecked();
  return Equals(bool_val, True()).FromMaybe(false) ? option_mask : 0;
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

cmark_parser* prepare_parser(const int options, vector<string>* extension_names) {
  cmark_parser* parser = cmark_parser_new(options);

  for(vector<string>::size_type i = 0; i < extension_names->size(); i++) {
    string ext_name = extension_names->at(i);
    cmark_syntax_extension* ext = cmark_find_syntax_extension(ext_name.c_str());
    if (ext != NULL) {
      cmark_parser_attach_syntax_extension(parser, ext);
    }
  }

  return parser;
}

char* markdown_to_html(const char* markdown, const int len, const int options, vector<string>* extension_names) {
  cmark_parser* parser = prepare_parser(options, extension_names);
  cmark_parser_feed(parser, markdown, len);
  cmark_node* document = cmark_parser_finish(parser);
  char* html = cmark_render_html(document, options, parser->syntax_extensions);
  cmark_parser_free(parser);
  return html;
}
