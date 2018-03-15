#include "ner_trainer.h"

Nan::Persistent<v8::Function> NerTrainer::constructor;

NerTrainer::NerTrainer(string filename) {
  pointer_ = new mitie::ner_trainer(filename);
}

NerTrainer::~NerTrainer() {
  delete pointer_;
}

void NerTrainer::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("NerTrainer").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "add", Add);
  Nan::SetPrototypeMethod(tpl, "train", Train);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("NerTrainer").ToLocalChecked(), tpl->GetFunction());
}

void NerTrainer::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new NerTrainer(...)`
    v8::String::Utf8Value arg0(info[0]->ToString());
    string filename = std::string(*arg0);
    NerTrainer* obj = new NerTrainer(filename);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `NerTrainer(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

mitie::ner_trainer* NerTrainer::GetWrapped() const { 
  return pointer_; 
};

void NerTrainer::Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NerTrainer* obj = Nan::ObjectWrap::Unwrap<NerTrainer>(info.Holder());
  mitie::ner_trainer* pointer = obj->GetWrapped();

  if (!info[0]->IsObject())
    return Nan::ThrowTypeError("NerTrainer:Add: bad arguments");

  NerTrainingInstance* ner_training_instance_ = Nan::ObjectWrap::Unwrap<NerTrainingInstance>(info[0]->ToObject());
  mitie::ner_training_instance* m_instance = ner_training_instance_->GetWrapped();

  pointer->add(*m_instance);
  
  info.GetReturnValue().SetUndefined();
}

void NerTrainer::Train(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NerTrainer* obj = Nan::ObjectWrap::Unwrap<NerTrainer>(info.Holder());
  mitie::ner_trainer* pointer = obj->GetWrapped();
  mitie::named_entity_extractor m = pointer->train();

  v8::Local<v8::Object> ner = NamedEntityExtractor::NewInstance(m);
  info.GetReturnValue().Set(ner);
}