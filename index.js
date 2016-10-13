var bindings = require('bindings')('binding.node')
module.exports = {
  renderHtmlSync: function (markdown, options) {
    return bindings.renderHtmlSync(markdown, options || {})
  },
  renderHtml: function (markdown, options, callback) {
    if (!callback) {
      callback = options
      options = {}
    }
    return bindings.renderHtml(markdown, options, callback)
  }
}
