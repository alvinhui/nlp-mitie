#ifndef NER_TRAINING_INSTANCE_H
#define NER_TRAINING_INSTANCE_H

#include <nan.h>
#include <string>
#include <mitie/ner_trainer.h>

class NerTrainingInstance : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> exports);
    mitie::ner_training_instance* GetWrapped() const { return pointer_; };

  private:
    explicit NerTrainingInstance(std::vector<std::string> tokens);
    ~NerTrainingInstance();

    static Nan::Persistent<v8::Function> constructor;
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void AddEntity(const Nan::FunctionCallbackInfo<v8::Value>& info);

    // Wrapped object
    mitie::ner_training_instance* pointer_;
};

#endif
