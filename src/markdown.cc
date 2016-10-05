#include "markdown.h"
#include "cmark.h"

char* markdown_to_html(const char* markdown, const int len) {
  return cmark_markdown_to_html(markdown, len, 0);
}
