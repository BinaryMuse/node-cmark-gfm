# node-cmark

node-cmark is a Node.js wrapper around [cmark](https://github.com/jgm/cmark), the reference implementation of [CommonMark](http://commonmark.org/) in C by John MacFarlane.

## Usage

**`html = renderHtmlSync(markdown[, options])`**

  * `markdown` - a string containing Markdown to render to HTML
  * `options` - a hash of options (see *Options*, below)

**`renderHtmlSync(markdown[, options], callback)`**

  * `markdown` - a string containing Markdown to render to HTML
  * `options` - a hash of options (see *Options*, below)
  * `callback` - a function to call with the resulting HTML once the Markdown has been rendered
    * `html` - the resulting HTML

**Options**

You can control the behavior of node-cmark by passing options to the rendering functions. The available options are:

  * `sourepos` - if `true`, adds a `data-sourcepos` attribute to all block elements that TODO??
  * `safe` - if `true`, suppresses raw HTML and unsafe links (`javascript:`, `vbscript:`, `file:`, and `data:` except for `image/png`, `image/gif`, `image/jpeg`, or `image/webp` mime types). Raw HTML is replaced by a placeholder HTML comment. Unsafe links are replaced with empty strings.
  * `nobreaks` - if `true`, renders softbreak elements as spaces
  * `hardbreaks` - if `true`, renders softbreak elements as hard line breaks
  * `normalize` - if `true`, adjacent text nodes are consolidated
  * `validateUtf8` - if `true`, replaces illegal UTF-8 sequences with `U+FFFD`
  * `smart` - if `true`, replaces straight quotes with curly ones, turns `---` into em dashes, and `--` into en dashes
  * `extensions` - an array of extensions to enable. Valid extensions are:
    * `"table"` - render tables
    * `"strikethrough"` - strikethrough
    * `"taglist"` - whitelist something
    * `"autolink"` - automatically turn URLs into links

### Rendering to HTML

You can turn a string containing Markdown into HTML either synchronously:

```javascript
const cmark = require('node-cmark')

const markdown = '# Hello World'
const options = {}
const html = cmark.renderHtmlSync(markdown, options)
console.log(html)
```

or asynchronously

```javascript
const cmark = require('node-cmark')

const markdown = '# Hello World'
const options = {}
cmark.renderHtml(markdown, options, (html) => {
  console.log(html)
})
```

Note that `options` may be omitted in either invocation.
