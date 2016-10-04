#include <node.h>
#include <v8.h>
#include <uv.h>
#include <nan.h>

#include "cmark.h"

using namespace v8;
using namespace node;
using Nan::New;
using Nan::ThrowTypeError;

struct RenderWork {
  uv_work_t request;
  Nan::Utf8String markdown;
  char* result;
  Persistent<Function> callback;
};

// struct render_baton {
//   uv_work_t req;
//   const char* markdown;
//   char* result;
//   Persistent<Function> callback;
// };

void render_sync(const Nan::FunctionCallbackInfo<Value>& args) {
  if (args.Length() < 1) {
    ThrowTypeError("Missing argument 'markdown' at position 0");
    return;
  }

  if (!args[0]->IsString()) {
    ThrowTypeError("Expected argument 'markdown' at position 0 to be a string");
    return;
  }

  Nan::Utf8String markdown(args[0]);
  const char* result = cmark_markdown_to_html(*markdown, markdown.length(), 0);
  args.GetReturnValue().Set(New<String>(result).ToLocalChecked());
}

// void do_render(uv_work_t* req) {
//   render_baton* baton = static_cast<render_baton*>(req->data);
//   const char* markdown = baton->markdown;
//   char* result = cmark_markdown_to_html(markdown, strlen(markdown), 0);
//   baton->result = result;
// }
//
// void after_render(uv_work_t *req, int status) {
//   Isolate* isolate = Isolate::GetCurrent();
//   HandleScope handleScope(isolate);
//   const render_baton* baton = (render_baton*) req->data;
//   const char* result = baton->result;
//   Local<Value> argv[] = { String::NewFromUtf8(isolate, result) };
//   Local<Function> cb = Local<Function>::New(isolate, baton->callback);
//   cb->Call(isolate->GetCurrentContext()->Global(), 1, argv);
//   baton->callback.Reset(isolate, cb);
// }
//
// void render(const FunctionCallbackInfo<Value>& args) {
//   if (!check_args(args, 2)) return;
//   const char* markdown = to_c_string(args[0]);
//   Isolate* isolate = args.GetIsolate();
//
//   render_baton* baton = new render_baton();
//   baton->req.data = baton;
//   baton->markdown = markdown;
//   baton->callback.Reset(isolate, args[1]);
//   uv_queue_work(uv_default_loop(), &baton->req, do_render, after_render);
// }

void init(Local<Object> exports) {
  exports->Set(New("renderSync").ToLocalChecked(), New<FunctionTemplate>(render_sync)->GetFunction());
  // NODE_SET_METHOD(exports, "render", render);
}

NODE_MODULE(binding, init)
