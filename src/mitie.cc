#include <nan.h>
#include "named_entity_extractor.h"
#include "ner_trainer.h"
#include "ner_training_instance.h"
#include "total_word_feature_extractor.h"
#include "text_categorizer.h"
#include "text_categorizer_trainer.h"

void InitAll(v8::Local<v8::Object> exports) {
  NamedEntityExtractor::Init(exports);
  TextCategorizer::Init(exports);
  NerTrainer::Init(exports);
  NerTrainingInstance::Init(exports);
  TotalWordFeatureExtractor::Init(exports);
  TextCategorizerTrainer::Init(exports);
}

NODE_MODULE(binding, InitAll)
