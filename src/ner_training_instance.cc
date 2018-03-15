#include "ner_training_instance.h"

Nan::Persistent<v8::Function> NerTrainingInstance::constructor;

NerTrainingInstance::NerTrainingInstance(std::vector<std::string> tokens) {
  pointer_ = new mitie::ner_training_instance(tokens);
}

NerTrainingInstance::~NerTrainingInstance() {
  delete pointer_;
}

void NerTrainingInstance::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("NerTrainingInstance").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "addEntity", AddEntity);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("NerTrainingInstance").ToLocalChecked(), tpl->GetFunction());
}

void NerTrainingInstance::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new NerTrainingInstance(...)`
    v8::Local<v8::Array> data = v8::Local<v8::Array>::Cast(info[0]);
    std::vector<std::string> tokens;
    for (unsigned int i = 0; i < data->Length(); i++ ) {
      if (Nan::Has(data, i).FromJust()) {
        v8::String::Utf8Value value(Nan::Get(data, i).ToLocalChecked());
        string token = std::string(*value);
        tokens.push_back(token);
      }
    }

    NerTrainingInstance* obj = new NerTrainingInstance(tokens);

    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `NerTrainingInstance(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void NerTrainingInstance::AddEntity(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NerTrainingInstance* obj = Nan::ObjectWrap::Unwrap<NerTrainingInstance>(info.Holder());
  mitie::ner_training_instance* pointer = obj->GetWrapped();

  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsString())
    return Nan::ThrowTypeError("NerTrainingInstance:AddEntity: bad arguments");
  
  double start_ = Nan::To<double>(info[0]).FromJust();
  long start = static_cast<long>(start_);
  double length_ = Nan::To<double>(info[1]).FromJust();
  long length = static_cast<long>(length_);
  v8::String::Utf8Value label(info[2]->ToString());
  pointer->add_entity(start, length, *label);

  info.GetReturnValue().SetUndefined();
}