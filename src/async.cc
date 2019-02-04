#include "napi.h"

#include "cmark-gfm.h"
#include "markdown.h"
#include "async.h"

using std::vector;
using std::string;

class RenderWorker : public Napi::AsyncWorker {
public:
  RenderWorker(Napi::Function& callback, const string markdown, const int options, vector<string>* extension_names)
    : Napi::AsyncWorker(callback), markdown(markdown), options(options), extension_names(extension_names) {}
  ~RenderWorker() {
    delete extension_names;
    cmark_mem* default_mem = cmark_get_default_mem_allocator();
    default_mem->free(result);
  }

  void Execute() {
    result = markdown_to_html(markdown.c_str(), markdown.length(), options, extension_names);
  }

  void OnOK() {
    Napi::HandleScope scope(Env());
    Callback().Call({ Napi::String::New(Env(), result) });
  }

private:
  const string markdown;
  char* result;
  const int options;
  vector<string>* extension_names;
};

Napi::Value render_html_async(const Napi::CallbackInfo& args) {
  if (args.Length() < 1) {
    Napi::Error::New(args.Env(), "Missing argument 'markdown'").ThrowAsJavaScriptException();
    return args.Env().Undefined();
  }

  if (!args[0].IsString()) {
    Napi::Error::New(args.Env(), "Expected argument 'markdown' to be a string").ThrowAsJavaScriptException();
    return args.Env().Undefined();
  }

  if (args.Length() < 3) {
    Napi::Error::New(args.Env(), "Missing argument 'callback'").ThrowAsJavaScriptException();
    return args.Env().Undefined();
  }

  if (!args[1].IsObject()) {
    Napi::Error::New(args.Env(), "Expected argument 'options' to be an object").ThrowAsJavaScriptException();
    return args.Env().Undefined();
  }

  if(!args[2].IsFunction()) {
    Napi::Error::New(args.Env(), "Expected argument 'callback' to be a function").ThrowAsJavaScriptException();
    return args.Env().Undefined();
  }

  vector<string>* extension_names = new vector<string>;
  Napi::Object opts_obj = args[1].As<Napi::Object>();
  int options = parse_options(opts_obj);
  populate_extension_names(opts_obj, extension_names);
  Napi::Function callback = args[2].As<Napi::Function>();
  string markdown = args[0].As<Napi::String>().Utf8Value();

  RenderWorker* worker = new RenderWorker(callback, markdown, options, extension_names);
  worker->Queue();

  return args.Env().Undefined();
}
