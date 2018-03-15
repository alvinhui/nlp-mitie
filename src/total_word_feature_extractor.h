#ifndef TOTAL_WORD_FEATURE_EXTRACTOR_H
#define TOTAL_WORD_FEATURE_EXTRACTOR_H

#include <nan.h>
#include <cstdlib>
#include <string>
#include <mitie/total_word_feature_extractor.h>
#include "template.h"

class TotalWordFeatureExtractor : public Nan::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> exports);
    static v8::Local<v8::Object> NewInstance(mitie::total_word_feature_extractor obj);
    mitie::total_word_feature_extractor* GetWrapped() const;
    void SetWrapped(mitie::total_word_feature_extractor obj);

  private:
    explicit TotalWordFeatureExtractor(const Nan::FunctionCallbackInfo<v8::Value>& info);
    ~TotalWordFeatureExtractor();

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static Nan::Persistent<v8::Function> constructor;

    // Wrapped object
    mitie::total_word_feature_extractor* pointer_;
};

#endif
