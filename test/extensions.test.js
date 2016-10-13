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
})
