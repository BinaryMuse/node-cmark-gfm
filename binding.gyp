{
  'targets': [
    {
      'target_name': 'binding',
      'defines': [
        'NAPI_DISABLE_CPP_EXCEPTIONS'
      ],
      'dependencies': [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      'cflags': [
        '-std=c99'
      ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")",
        'src',
        'vendor/cmark'
      ],
      'sources': [
        'src/markdown.cc',
        'src/sync.cc',
        'src/streaming_parser.cc',
        'src/binding.cc',
        'vendor/cmark/arena.c',
        'vendor/cmark/blocks.c',
        'vendor/cmark/buffer.c',
        'vendor/cmark/cmark.c',
        'vendor/cmark/cmark_ctype.c',
        'vendor/cmark/commonmark.c',
        'vendor/cmark/footnotes.c',
        'vendor/cmark/houdini_href_e.c',
        'vendor/cmark/houdini_html_e.c',
        'vendor/cmark/houdini_html_u.c',
        'vendor/cmark/html.c',
        'vendor/cmark/inlines.c',
        'vendor/cmark/iterator.c',
        'vendor/cmark/latex.c',
        'vendor/cmark/linked_list.c',
        'vendor/cmark/man.c',
        'vendor/cmark/map.c',
        'vendor/cmark/node.c',
        'vendor/cmark/plaintext.c',
        'vendor/cmark/plugin.c',
        'vendor/cmark/references.c',
        'vendor/cmark/registry.c',
        'vendor/cmark/render.c',
        'vendor/cmark/scanners.c',
        'vendor/cmark/syntax_extension.c',
        'vendor/cmark/utf8.c',
        'vendor/cmark/xml.c',
        'vendor/cmark/autolink.c',
        'vendor/cmark/core-extensions.c',
        'vendor/cmark/ext_scanners.c',
        'vendor/cmark/strikethrough.c',
        'vendor/cmark/table.c',
        'vendor/cmark/tagfilter.c',
        'vendor/cmark/tasklist.c',
      ],
      'xcode_settings': {
        'MACOSX_DEPLOYMENT_TARGET': '10.8',
        'CLANG_CXX_LIBRARY': 'libc++',
        'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
        'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0'
      }
    }
  ]
}
