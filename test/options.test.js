const cmark = require('../')

const assert = require('chai').assert
const dedent = require('dedent')

describe('options', () => {
  describe('sourcepos', () => {
    it('adds data-sourcepos attributes to block-level elements', () => {
      const markdown = dedent`
      # Hello

      This is a test.

      \`\`\`javascript
      whee
      \`\`\`
      `.trim()

      const html = `
      <h1 data-sourcepos="1:1-1:7">Hello</h1>
      <p data-sourcepos="3:1-3:15">This is a test.</p>
      <pre data-sourcepos="5:1-7:3">
        <code class="language-javascript">whee</code>
      </pre>
      `
      const rendered = cmark.renderHtmlSync(markdown, {sourcepos: true})
      assert.htmlEqual(rendered, html)
    })
  })

  describe('safe', () => {
    it('strips HTML and unsafe links', () => {
      const markdown = dedent`
      ![img](data:image/gif;base64,abccdefgh)

      <div>hello!</div>

      [link](javascript:alert('omg'))
      `.trim()

      const html = `
      <p><img alt="img" src="data:image/gif;base64,abccdefgh"></p>
      <!-- raw HTML omitted -->
      <p><a href="">link</a></p>
      `

      const rendered = cmark.renderHtmlSync(markdown, {safe: true})
      assert.htmlEqual(rendered, html)
    })
  })

  describe('nobreaks', () => {
    it('renders softbreak elements as spaces', () => {
      const markdown = dedent`
      abc
      def
      `.trim()

      const html = `
      <p>abc def</p>
      `

      const rendered = cmark.renderHtmlSync(markdown, {nobreaks: true})
      assert.htmlEqual(rendered, html)
    })
  })

  describe('hardbreaks', () => {
    it('renders softbreak elements as hard line breaks', () => {
      const markdown = dedent`
      abc
      def
      `.trim()

      const html = dedent`
      <p>abc<br>\ndef</p>
      `.trim()

      const rendered = cmark.renderHtmlSync(markdown, {hardbreaks: true})
      assert.htmlEqual(rendered, html)
    })
  })

  describe('normalize', () => {
    xit('consolidates adjacent text nodes', () => {
      // TODO: how to test? does this even matter in HTML? Text nodes have no wrapper.
    })
  })

  describe('validateUtf8', () => {
    xit('replaces illegal UTF-8 sequences', () => {
      // TODO: doesn't fail when option is false
      const markdown = "abc" + '\u0000' + "def"

      const html = "<p>abc" + '\uFFFD' + "def</p>"

      const rendered = cmark.renderHtmlSync(markdown, {validateUtf8: false})
      console.log(rendered)
      assert.htmlEqual(rendered, html)
    })
  })

  describe('smart', () => {
    it('makes punctuation fancy', () => {
      // TODO: doesn't fail when option is false
      const markdown = dedent`
      "Good morning," said the man. "Wait -- maybe it's 'afternoon'." --- Someone Famous
      `.trim()

      const html = `
      <p>“Good morning,” said the man. “Wait – maybe it’s ‘afternoon’.” — Someone Famous</p>
      `.trim()

      const rendered = cmark.renderHtmlSync(markdown, {smart: true})
      assert.htmlEqual(rendered, html)
    })
  })
})
