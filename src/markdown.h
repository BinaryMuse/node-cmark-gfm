#ifndef NODE_CMARK_MARKDOWN_H
#define NODE_CMARK_MARKDOWN_H

#include "napi.h"

void node_cmark_init(void);
int parse_options(Napi::Object options_obj);
void populate_extension_names(Napi::Object options_obj, std::vector<std::string>* extension_names);
char* markdown_to_html(const char* markdown, const int len, const int options, std::vector<std::string>* extension_names);

#endif
