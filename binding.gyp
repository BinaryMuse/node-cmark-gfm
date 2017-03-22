{
  'targets': [
    {
      'target_name': 'binding',
      'include_dirs': [
        '<!(node -e "require(\'nan\')")',
        'src',
        'cmark/src',
        'cmark/extensions',
        'cmark/build/extensions',
        'cmark/build/src'
      ],
      'sources': [
        'src/markdown.cc',
        'src/sync.cc',
        'src/async.cc',
        'src/binding.cc',
        'cmark/src/arena.c',
        'cmark/src/blocks.c',
        'cmark/src/buffer.c',
        'cmark/src/cmark.c',
        'cmark/src/cmark_ctype.c',
        'cmark/src/commonmark.c',
        'cmark/src/houdini_href_e.c',
        'cmark/src/houdini_html_e.c',
        'cmark/src/houdini_html_u.c',
        'cmark/src/html.c',
        'cmark/src/inlines.c',
        'cmark/src/iterator.c',
        'cmark/src/latex.c',
        'cmark/src/linked_list.c',
        'cmark/src/main.c',
        'cmark/src/man.c',
        'cmark/src/node.c',
        'cmark/src/plugin.c',
        'cmark/src/references.c',
        'cmark/src/registry.c',
        'cmark/src/render.c',
        'cmark/src/scanners.c',
        'cmark/src/syntax_extension.c',
        'cmark/src/utf8.c',
        'cmark/src/xml.c',
        'cmark/extensions/autolink.c',
        'cmark/extensions/core-extensions.c',
        'cmark/extensions/ext_scanners.c',
        'cmark/extensions/strikethrough.c',
        'cmark/extensions/table.c',
        'cmark/extensions/tagfilter.c'
      ]
    }
  ]
}
