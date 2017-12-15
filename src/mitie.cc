#include <nan.h>
#include "named_entity_extractor.h"
#include "total_word_feature_extractor.h"

void InitAll(v8::Local<v8::Object> exports) {
  NamedEntityExtractor::Init(exports);
  TotalWordFeatureExtractor::Init(exports);
}

NODE_MODULE(mitie, InitAll)
