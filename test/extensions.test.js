const cmark = require('../')

const assert = require('chai').assert
const dedent = require('dedent')

describe('extensions', () => {
  describe('table', () => {
    it('renders tables', () => {
      const markdown = dedent`
      |Header|
      |------|
      |Hello |
      `.trim()

      const html = `
      <table>
        <thead>
          <tr>
            <th>Header</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td>Hello</td>
          </tr>
        </tbody>
      </table>
      `
      const rendered = cmark.renderHtmlSync(markdown, {extensions: ['table']})
      assert.htmlEqual(rendered, html)
    })
  })

  describe('strikethrough', () => {
    it('enables strikethrough', () => {
      const markdown = dedent`
      It's all about ~CoffeeScript~ ES2016
      `.trim()

      const html = `
      <p>It's all about <del>CoffeeScript</del> ES2016</p>
      `
      const rendered = cmark.renderHtmlSync(markdown, {extensions: ['strikethrough']})
      assert.htmlEqual(rendered, html)
    })
  })

  describe('whitelist', () => {
    it('only allows certain HTML tags to be rendered as raw HTML', () => {
      const markdown = dedent`
      <div>What a weird <xmp> tag</div>
      `.trim()

      const html = `
      <div>What a weird &lt;xmp> tag</div>
      `

      const rendered = cmark.renderHtmlSync(markdown, {extensions: ['whitelist']})
      assert.htmlEqual(rendered, html)
    })
  })

  describe('autolink', () => {
    it('turns URLs into links', () => {
      const markdown = dedent`
      Visit us at https://github.com!
      `.trim()

      const html = `
      <p>Visit us at <a href="https://github.com">https://github.com</a>!</p>
      `

      const rendered = cmark.renderHtmlSync(markdown, {extensions: ['autolink']})
      assert.htmlEqual(rendered, html)
    })
  })
})
