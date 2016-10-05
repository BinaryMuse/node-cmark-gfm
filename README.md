# node-cmark

node-cmark is a Node.js wrapper around [cmark](https://github.com/jgm/cmark), the reference implementation of [CommonMark](http://commonmark.org/) in C by John MacFarlane.

## Usage

You can turn a string containing Markdown into HTML either synchronously:

```javascript
const cmark = require('node-cmark')

const markdown = '# Hello World'
const html = cmark.renderHtmlSync(markdown)
console.log(html)
```

or asynchronously

```javascript
const cmark = require('node-cmark')

const markdown = '# Hello World'
cmark.renderHtml(markdown, (html) => {
  console.log(html)
})
```
