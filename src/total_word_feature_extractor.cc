#include "total_word_feature_extractor.h"

Nan::Persistent<v8::Function> TotalWordFeatureExtractor::constructor;

TotalWordFeatureExtractor::TotalWordFeatureExtractor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info[0]->IsString()) {
    v8::String::Utf8Value arg0(info[0]->ToString());
    string filename = std::string(*arg0);
    string classname;
    pointer_ = allocate<mitie::total_word_feature_extractor>();
    dlib::deserialize(filename) >> classname;
    if (classname != "mitie::total_word_feature_extractor")
      Nan::ThrowTypeError("This file does not contain a mitie::total_word_feature_extractor");
    dlib::deserialize(filename) >> classname >> *pointer_;
  } else {
    Nan::ThrowTypeError("TotalWordFeatureExtractor:new: bad arguments");
  }
}

TotalWordFeatureExtractor::~TotalWordFeatureExtractor() {
  delete pointer_;
}

void TotalWordFeatureExtractor::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("TotalWordFeatureExtractor").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("TotalWordFeatureExtractor").ToLocalChecked(), tpl->GetFunction());
}

void TotalWordFeatureExtractor::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new TotalWordFeatureExtractor(...)`
    TotalWordFeatureExtractor* obj = new TotalWordFeatureExtractor(info);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `TotalWordFeatureExtractor(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

mitie::total_word_feature_extractor* TotalWordFeatureExtractor::GetWrapped() const { 
  return pointer_; 
};

void TotalWordFeatureExtractor::SetWrapped(mitie::total_word_feature_extractor obj) {
  if (pointer_) delete pointer_; 
  pointer_ = allocate<mitie::total_word_feature_extractor>(obj); 
};

v8::Local<v8::Object> TotalWordFeatureExtractor::NewInstance(mitie::total_word_feature_extractor obj) {
  Nan::EscapableHandleScope scope;

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::Undefined() };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  TotalWordFeatureExtractor* w = Nan::ObjectWrap::Unwrap<TotalWordFeatureExtractor>(instance);
  w->SetWrapped(obj);

  return scope.Escape(instance);
}