# cmark-gfm

cmark-gfm is a Node.js wrapper around GitHub's [GFM-enhanced](https://github.github.com/gfm/) fork of [cmark](https://github.com/github/cmark-gfm), the reference implementation of [CommonMark](http://commonmark.org/) in C by John MacFarlane. You can find GitHub's fork at https://github.com/github/cmark-gfm.

## Installation

```
npm install cmark-gfm
```

## Usage

**`html = renderHtmlSync(markdown[, options])`**

  * `markdown` - a string containing Markdown to render to HTML
  * `options` - a hash of options (see *Options*, below)

**`renderHtml(markdown[, options], callback)`**

  * `markdown` - a string containing Markdown to render to HTML
  * `options` - a hash of options (see *Options*, below)
  * `callback` - a function to call with the resulting HTML once the Markdown has been rendered
    * `html` - the resulting HTML

**Options**

You can control the behavior of cmark-gfm by passing options to the rendering functions. The available options are:

  * `sourepos` - if `true`, adds a `data-sourcepos` attribute to all block elements that TODO??
  * `hardbreaks` - if `true`, renders softbreak elements as hard line breaks
  * `nobreaks` - if `true`, renders softbreak elements as spaces
  * `validateUtf8` - if `true`, replaces illegal UTF-8 sequences with `U+FFFD`
  * `smart` - if `true`, replaces straight quotes with curly ones, turns `---` into em dashes, and `--` into en dashes
  * `githubPreLang` - if `true`, uses GitHub style `<pre lang="x">` tags for code blocks
  * `liberalHtmltag` - if `true`, allows non-well-formed HTML tags to be parsed as HTML (e.g. `< div>` instead of `<div>`)
  * `footnotes` - if `true`, enables footnote parsing and rendering
  * `strikethroughDoubleTilde` - if `true`, the `strikethrough` extension will only render text as strikethrough if it is surrounded by `~~two tildes~~`
  * `fullInfoString` - if `true`, adds additional code block info as an additional attribute on the resulting HTML element
  * `unsafe` - if `true`, allows raw HTML and unsafe links (`javascript:`, `vbscript:`, `file:`, and `data:` except for `image/png`, `image/gif`, `image/jpeg`, or `image/webp` mime types). Otherwise, raw HTML is replaced by a placeholder HTML comment, and unsafe links are replaced with empty strings.
  * `extensions` - an array of extensions to enable. Valid extensions are:
    * `"table"` - render tables
    * `"strikethrough"` - strikethrough
    * `"tagfilter"` - whitelist something
    * `"autolink"` - automatically turn URLs into links
    * `"tasklist"` - renders GitHub style task lists

### Rendering to HTML

You can turn a string containing Markdown into HTML either synchronously:

```javascript
const cmark = require('cmark-gfm')

const markdown = '# Hello World'
const options = {}
const html = cmark.renderHtmlSync(markdown, options)
console.log(html)
```

or asynchronously

```javascript
const cmark = require('cmark-gfm')

const markdown = '# Hello World'
const options = {}
cmark.renderHtml(markdown, options, (html) => {
  console.log(html)
})
```

Note that `options` may be omitted in either invocation.
