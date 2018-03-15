#include <nan.h>
#include "named_entity_extractor.h"
#include "ner_trainer.h"
#include "ner_training_instance.h"
#include "total_word_feature_extractor.h"

void InitAll(v8::Local<v8::Object> exports) {
  NamedEntityExtractor::Init(exports);
  NerTrainer::Init(exports);
  NerTrainingInstance::Init(exports);
  TotalWordFeatureExtractor::Init(exports);
}

NODE_MODULE(binding, InitAll)
