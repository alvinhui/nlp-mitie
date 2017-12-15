#include "named_entity_extractor.h"

Nan::Persistent<v8::Function> NamedEntityExtractor::constructor;

NamedEntityExtractor::NamedEntityExtractor(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info[0]->IsString()) {
    v8::String::Utf8Value arg0(info[0]->ToString());
    string filename = std::string(*arg0);

    string classname;
    dlib::deserialize(filename) >> classname;
    if (classname == "mitie::named_entity_extractor_pure_model"
      || classname == "mitie::named_entity_extractor_pure_model_with_version") {
      if (info[1]->IsString()) { // mitie_load_named_entity_extractor_pure_model
        v8::String::Utf8Value arg1(info[1]->ToString());
        string fe_filename = std::string(*arg1);
        pointer_ = allocate<mitie::named_entity_extractor>(filename, fe_filename);
      } else { // mitie_load_named_entity_extractor_pure_model_without_feature_extractor
        pointer_ = allocate<mitie::named_entity_extractor>(filename);
      }
    } else { // mitie_load_named_entity_extractor
      pointer_ = allocate<mitie::named_entity_extractor>();
      if (classname != "mitie::named_entity_extractor")
        Nan::ThrowTypeError("This file does not contain a mitie::named_entity_extractor");
        
      dlib::deserialize(filename) >> classname >> *pointer_;
    }
  }
}

NamedEntityExtractor::~NamedEntityExtractor() {
  delete pointer_;
}

void NamedEntityExtractor::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("NamedEntityExtractor").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "extractEntities", ExtractEntities);
  Nan::SetPrototypeMethod(tpl, "getPossibleTags", GetPossibleTags);
  Nan::SetPrototypeMethod(tpl, "saveToDisk", SaveToDisk);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("NamedEntityExtractor").ToLocalChecked(), tpl->GetFunction());
}

void NamedEntityExtractor::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new NamedEntityExtractor(...)`
    NamedEntityExtractor* obj = new NamedEntityExtractor(info);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `NamedEntityExtractor(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

mitie::named_entity_extractor* NamedEntityExtractor::GetWrapped() const { 
  return pointer_; 
};

void NamedEntityExtractor::SetWrapped(mitie::named_entity_extractor obj) {
  if (pointer_) delete pointer_; 
  pointer_ = allocate<mitie::named_entity_extractor>(obj); 
};

v8::Local<v8::Object> NamedEntityExtractor::NewInstance(mitie::named_entity_extractor obj) {
  Nan::EscapableHandleScope scope;

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::Undefined() };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  NamedEntityExtractor* w = Nan::ObjectWrap::Unwrap<NamedEntityExtractor>(instance);
  w->SetWrapped(obj);

  return scope.Escape(instance);
}

void NamedEntityExtractor::ExtractEntities(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NamedEntityExtractor* obj = Nan::ObjectWrap::Unwrap<NamedEntityExtractor>(info.Holder());
  mitie::named_entity_extractor* pointer_ = obj->GetWrapped();

  v8::Local<v8::Array> data = v8::Local<v8::Array>::Cast(info[0]);
  std::vector<std::string> tokens;
  for (unsigned int i = 0; i < data->Length(); i++ ) {
    if (Nan::Has(data, i).FromJust()) {
      v8::String::Utf8Value value(Nan::Get(data, i).ToLocalChecked());
      string token = std::string(*value);
      tokens.push_back(token);
    }
  }

  vector<pair<unsigned long, unsigned long>> chunks;
  vector<unsigned long> chunk_tags;
  vector<double> chunk_scores;

  std::vector<std::string> tagstr_ = pointer_->get_tag_name_strings();
  // cout << "The tagger supports "<< tagstr_.size() <<" tags:" << endl;
  // for (unsigned int i = 0; i < tagstr_.size(); ++i)
  //     cout << "   " << tagstr_[i] << endl;

  if (info[1]->IsObject()) {
    TotalWordFeatureExtractor* total_word_feature_extractor = Nan::ObjectWrap::Unwrap<TotalWordFeatureExtractor>(info[1]->ToObject());
    mitie::total_word_feature_extractor* m_instance = total_word_feature_extractor->GetWrapped();
    const mitie::total_word_feature_extractor& fe_temp = checked_cast<mitie::total_word_feature_extractor>(m_instance);
    pointer_->predict(tokens, chunks, chunk_tags, chunk_scores, fe_temp);
  } else {
    pointer_->predict(tokens, chunks, chunk_tags, chunk_scores);
  }

  v8::Local<v8::Array> tags = Nan::New<v8::Array>(chunks.size());

  for (unsigned int i = 0; i < chunks.size(); ++i) {
    v8::Local<v8::Object> tag = Nan::New<v8::Object>();

    tag->Set(Nan::New("score").ToLocalChecked(), Nan::New<v8::Number>(chunk_scores[i]));

    string chunktag_string(tagstr_[chunk_tags[i]]);

    tag->Set(Nan::New("entity").ToLocalChecked(),  Nan::New<v8::String>(chunktag_string).ToLocalChecked());

    unsigned long start = chunks[i].first; 
    unsigned long end = chunks[i].second;
    tag->Set(Nan::New("start").ToLocalChecked(), Nan::New<v8::Number>(start));
    tag->Set(Nan::New("end").ToLocalChecked(), Nan::New<v8::Number>(end));

    tags->Set(i, tag);
  }

  info.GetReturnValue().Set(tags);
}

void NamedEntityExtractor::GetPossibleTags(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NamedEntityExtractor* obj = Nan::ObjectWrap::Unwrap<NamedEntityExtractor>(info.Holder());

  mitie::named_entity_extractor* pointer_ = obj->GetWrapped();
  std::vector<std::string> tagstr_ = pointer_->get_tag_name_strings();
  v8::Local<v8::Array> tags = Nan::New<v8::Array>(tagstr_.size());
  for (unsigned int i = 0; i < tagstr_.size(); ++i)
    tags->Set(i, Nan::New<v8::String>(tagstr_[i]).ToLocalChecked());

  info.GetReturnValue().Set(tags);
}

void NamedEntityExtractor::SaveToDisk(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NamedEntityExtractor* obj = Nan::ObjectWrap::Unwrap<NamedEntityExtractor>(info.Holder());
  mitie::named_entity_extractor* pointer_ = obj->GetWrapped();

  v8::String::Utf8Value arg0(info[0]->ToString());
  string filename = std::string(*arg0);

  const mitie::named_entity_extractor& ner = checked_cast<mitie::named_entity_extractor>(pointer_);
  int result = 0;

  try {
    if (info[1]->IsBoolean() && info[1]->ToBoolean()->BooleanValue()) { //pure_model
      dlib::serialize(filename) 
      << "mitie::named_entity_extractor_pure_model_with_version"
      << ner.get_max_supported_pure_model_version()
      << ner.get_df()
      << ner.get_segmenter()
      << ner.get_tag_name_strings()
      << ner.get_total_word_feature_extractor().get_fingerprint();
    } else {
      dlib::serialize(filename) << "mitie::named_entity_extractor" << ner;
    }
    result = 1;
  }
  catch (std::exception& e) {
#ifndef NDEBUG
    cerr << "Error saving MITIE model file: " << filename << "\n" << e.what() << endl;
#endif
    result = 0;
  }
  catch (...) {
#ifndef NDEBUG
    cerr << "Error saving MITIE model file: " << filename << endl;
#endif
    result = 0;
  }

  info.GetReturnValue().Set(result == 0 ? Nan::False() : Nan::True());
}