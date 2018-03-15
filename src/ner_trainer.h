#ifndef NER_TRAINER_H
#define NER_TRAINER_H

#include <nan.h>
#include <string>
#include <mitie/ner_trainer.h>
#include "ner_training_instance.h"
#include "named_entity_extractor.h"

class NerTrainer : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> exports);
    mitie::ner_trainer* GetWrapped() const;

  private:
    explicit NerTrainer(string filename);
    ~NerTrainer();

    static Nan::Persistent<v8::Function> constructor;
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void Add(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void Train(const Nan::FunctionCallbackInfo<v8::Value>& info);

    // Wrapped object
    mitie::ner_trainer* pointer_;
};

#endif
