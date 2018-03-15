{
  "targets": [
    {
      "target_name": "binding",
      "sources": [
        "src/mitie.cc",
        "src/named_entity_extractor.cc",
        "src/text_categorizer.cc",
        "src/ner_trainer.cc",
        "src/ner_training_instance.cc",
        "src/total_word_feature_extractor.cc",
        "src/text_categorizer_trainer.cc",
      ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [
          '-std=c++11'
        ],
        'MACOSX_DEPLOYMENT_TARGET': '10.7',
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "GCC_ENABLE_CPP_RTTI": "YES"
      },
      'include_dirs': [
        '<!(node -e "require(\'nan\')")',
      ],
      'dependencies': [
        'src/libmitie.gyp:libmitie',
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions", "-fno-rtti"],
      "conditions": [
        ['OS!="win"', {
          'cflags_cc+': [
            '-std=c++0x'
          ]
        }],
      ]
    }
  ]
}
