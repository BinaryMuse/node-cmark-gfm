#ifndef NODE_CMARK_MARKDOWN_H
#define NODE_CMARK_MARKDOWN_H

#include <v8.h>
#include <nan.h>

int parse_options(v8::Local<v8::Object> options_obj);
char* markdown_to_html(const char* markdown, const int len, const int options);

#endif
