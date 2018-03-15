#ifndef ENTITY_EXTRACTOR_H
#define ENTITY_EXTRACTOR_H

#include <nan.h>
#include <cstdlib>
#include <string>
#include <mitie.h>
#include <mitie/named_entity_extractor.h>
#include "total_word_feature_extractor.h"
#include "template.h"

class NamedEntityExtractor : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> exports);
    static v8::Local<v8::Object> NewInstance(mitie::named_entity_extractor obj);
    mitie::named_entity_extractor* GetWrapped() const;
    void SetWrapped(mitie::named_entity_extractor obj);

  private:
    explicit NamedEntityExtractor(const Nan::FunctionCallbackInfo<v8::Value>& info);
    ~NamedEntityExtractor();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void ExtractEntities(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void GetPossibleTags(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void SaveToDisk(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static Nan::Persistent<v8::Function> constructor;

    // Wrapped object
    mitie::named_entity_extractor* pointer_;
};

#endif
