const cmark = require('../')

const assert = require('chai').assert

describe('#renderHtmlSync', () => {
  it('renders HTML synchronously', () => {
    assert.htmlEqual(cmark.renderHtmlSync('# Hi'), '<h1>Hi</h1>')
  })
})

describe('#renderHtml', () => {
  it('renders HTML asynchronously with a callback', (done) => {
    let ticked = false
    cmark.renderHtml('# Hi', (err, html) => {
      assert.notOk(err)
      assert.htmlEqual(html, '<h1>Hi</h1>')
      assert.ok(ticked)
      done()
    })
    ticked = true
  })

  it('renders HTML asynchronously with a promise', (done) => {
    let ticked = false
    const promise = cmark.renderHtml('# Hi')
    promise.then(html => {
      assert.htmlEqual(html, '<h1>Hi</h1>')
      assert.ok(ticked)
      done()
    })
    ticked = true
  })
})
