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
#include "../QtCore/qsize.h"
#include "qtextedit.h"
#include "qwidget.h"


using namespace v8;

Persistent<Function> QTextEditWrap::constructor;

//
// QTextEditImpl
//

QTextEditImpl::QTextEditImpl(QWidget * parent, const QString & text) 
    : QTextEdit(text, parent) {
}

QTextEditImpl::~QTextEditImpl() {
}

//
// QTextEditWrap
//

QTextEditWrap::QTextEditWrap(QWidget * parent, const QString & text) {
  q_ = new QTextEditImpl(parent, text);
}

QTextEditWrap::~QTextEditWrap() {
  delete q_;
}

void QTextEditWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QTextEdit"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Methods
  tpl->PrototypeTemplate()->Set(String::NewSymbol("resize"),
      FunctionTemplate::New(Resize)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("size"),
      FunctionTemplate::New(Size)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("width"),
      FunctionTemplate::New(Width)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("height"),
      FunctionTemplate::New(Height)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("parent"),
      FunctionTemplate::New(Parent)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("move"),
      FunctionTemplate::New(Move)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("x"),
      FunctionTemplate::New(X)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("y"),
      FunctionTemplate::New(Y)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("toPlainText"),
      FunctionTemplate::New(ToPlainText)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPlainText"),
      FunctionTemplate::New(SetPlainText)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setText"),
      FunctionTemplate::New(SetText)->GetFunction());

  // Events

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QTextEdit"), constructor);
}

// Supported versions:
// new QTextEdit(parent)
// new QTextEdit(parent, text)
Handle<Value> QTextEditWrap::New(const Arguments& args) {
  HandleScope scope;
  QWidget * q_parent = NULL;
  QString q_text;

  if (args.Length() > 0) {
    QWidgetWrap * w_parent = node::ObjectWrap::Unwrap<QWidgetWrap>(args[0]->ToObject());
    q_parent = w_parent->GetWrapped();

    if (args.Length() > 1) {
      q_text = qt_v8::ToQString(args[1]->ToString());
    }
  }

  QTextEditWrap * w = new QTextEditWrap(q_parent, q_text);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QTextEditWrap::Resize(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  q->resize(args[0]->NumberValue(), args[1]->NumberValue());

  return scope.Close(Undefined());
}

Handle<Value> QTextEditWrap::Size(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  return scope.Close( QSizeWrap::NewInstance(q->size()) );
}

Handle<Value> QTextEditWrap::Width(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  return scope.Close( Integer::New(q->width()) );
}

Handle<Value> QTextEditWrap::Height(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  return scope.Close( Integer::New(q->height()) );
}

//
// QUIRK:
// Here: Parent() returns the parent's name
// Qt: Parent() returns QObject
// Intended mostly for sanity checks
//
Handle<Value> QTextEditWrap::Parent(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  return scope.Close(qt_v8::FromQString(q->parent()->objectName()));
}

// Supported implementations:
//    move (int x, int y)
Handle<Value> QTextEditWrap::Move(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  q->move(args[0]->IntegerValue(), args[1]->IntegerValue());

  return scope.Close(Undefined());
}

Handle<Value> QTextEditWrap::X(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  return scope.Close(Integer::New(q->x()));
}

Handle<Value> QTextEditWrap::Y(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  return scope.Close(Integer::New(q->y()));
}

Handle<Value> QTextEditWrap::ToPlainText(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  return scope.Close(qt_v8::FromQString(q->toPlainText()));
}

Handle<Value> QTextEditWrap::SetPlainText(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  if (args[0]->IsString() || args[0]->IsStringObject()) {
    QString text = qt_v8::ToQString(args[0]->ToString());
    q->setPlainText(text);
  }

  return scope.Close(Undefined());
}

Handle<Value> QTextEditWrap::SetText(const Arguments& args) {
  HandleScope scope;

  QTextEditWrap* w = node::ObjectWrap::Unwrap<QTextEditWrap>(args.This());
  QTextEditImpl* q = w->GetWrapped();

  if (args[0]->IsString() || args[0]->IsStringObject()) {
    QString text = qt_v8::ToQString(args[0]->ToString());
    q->setText(text);
  }

  return scope.Close(Undefined());
}

