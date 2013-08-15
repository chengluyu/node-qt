// Copyright (c) 2013, Cheng Luyu
// All rights reserved.
//
// Author(s): Cheng Luyu <chengluyu@live.cn>
//
// You may use this file under the terms of the New BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Artur Adib nor the
//       names of contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL ARTUR ADIB BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "qrect.h"

using namespace v8;

Persistent<Function> QRectWrap::constructor;

QRectWrap::QRectWrap() : q_(NULL) {
  // Standalone constructor not implemented
  // Use SetWrapped() 
}

QRectWrap::~QRectWrap() {
  delete q_;
}

void QRectWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QRect"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("left"),
      FunctionTemplate::New(Left)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("top"),
      FunctionTemplate::New(Top)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("x"),
      FunctionTemplate::New(X)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("y"),
      FunctionTemplate::New(Y)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("width"),
      FunctionTemplate::New(Width)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("height"),
      FunctionTemplate::New(Height)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QRect"), constructor);
}

Handle<Value> QRectWrap::New(const Arguments& args) {
  HandleScope scope;

  QRectWrap * w = new QRectWrap();
  w->Wrap(args.This());

  if (args[0]->IsNumber() && args[1]->IsNumber() &&
      args[2]->IsNumber() && args[3]->IsNumber())
    w->SetWrapped(QRect(args[0]->IntegerValue(), args[1]->IntegerValue(),
        args[2]->IntegerValue(), args[3]->IntegerValue()));

  return args.This();
}

Handle<Value> QRectWrap::NewInstance(QRect q) {
  HandleScope scope;
  
  Local<Object> instance = constructor->NewInstance(0, NULL);
  QRectWrap * w = node::ObjectWrap::Unwrap<QRectWrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}

// Prototype

Handle<Value> QRectWrap::X(const Arguments& args) {
  HandleScope scope;

  QRectWrap * w = ObjectWrap::Unwrap<QRectWrap>(args.This());
  QRect * q = w->GetWrapped();

  return scope.Close(Number::New(q->x()));
}

Handle<Value> QRectWrap::Y(const Arguments& args) {
  HandleScope scope;

  QRectWrap * w = ObjectWrap::Unwrap<QRectWrap>(args.This());
  QRect * q = w->GetWrapped();

  return scope.Close(Number::New(q->y()));
}

Handle<Value> QRectWrap::Left(const Arguments& args) {
  HandleScope scope;

  QRectWrap * w = ObjectWrap::Unwrap<QRectWrap>(args.This());
  QRect * q = w->GetWrapped();

  return scope.Close(Number::New(q->left()));
}

Handle<Value> QRectWrap::Top(const Arguments& args) {
  HandleScope scope;

  QRectWrap * w = ObjectWrap::Unwrap<QRectWrap>(args.This());
  QRect * q = w->GetWrapped();

  return scope.Close(Number::New(q->top()));
}

Handle<Value> QRectWrap::Width(const Arguments& args) {
  HandleScope scope;

  QRectWrap * w = ObjectWrap::Unwrap<QRectWrap>(args.This());
  QRect * q = w->GetWrapped();

  return scope.Close(Number::New(q->width()));
}

Handle<Value> QRectWrap::Height(const Arguments& args) {
  HandleScope scope;

  QRectWrap * w = ObjectWrap::Unwrap<QRectWrap>(args.This());
  QRect * q = w->GetWrapped();

  return scope.Close(Number::New(q->height()));
}
