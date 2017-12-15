{
  "targets": [
    {
      "target_name": "mitie",
      "sources": [
        # dlib
        "deps/MITIE-0.5/dlib/dlib/threads/multithreaded_object_extension.cpp",
        "deps/MITIE-0.5/dlib/dlib/threads/threaded_object_extension.cpp",
        "deps/MITIE-0.5/dlib/dlib/threads/threads_kernel_1.cpp",
        "deps/MITIE-0.5/dlib/dlib/threads/threads_kernel_2.cpp",
        "deps/MITIE-0.5/dlib/dlib/threads/threads_kernel_shared.cpp",
        "deps/MITIE-0.5/dlib/dlib/threads/thread_pool_extension.cpp",
        "deps/MITIE-0.5/dlib/dlib/misc_api/misc_api_kernel_1.cpp",
        "deps/MITIE-0.5/dlib/dlib/misc_api/misc_api_kernel_2.cpp",

        # mitie
        "deps/MITIE-0.5/mitielib/src/mitie.cpp",
        "deps/MITIE-0.5/mitielib/src/named_entity_extractor.cpp",
        "deps/MITIE-0.5/mitielib/src/ner_feature_extraction.cpp",
        "deps/MITIE-0.5/mitielib/src/text_categorizer.cpp",
        "deps/MITIE-0.5/mitielib/src/binary_relation_detector.cpp",
        "deps/MITIE-0.5/mitielib/src/binary_relation_detector_trainer.cpp",
        "deps/MITIE-0.5/mitielib/src/stem.c",
        "deps/MITIE-0.5/mitielib/src/stemmer.cpp",
        "deps/MITIE-0.5/mitielib/src/conll_parser.cpp",
        "deps/MITIE-0.5/mitielib/src/ner_trainer.cpp",
        "deps/MITIE-0.5/mitielib/src/text_categorizer_trainer.cpp",
        "deps/MITIE-0.5/mitielib/src/text_feature_extraction.cpp",

        # binding
        "src/mitie.cc",
        "src/named_entity_extractor.cc",
        "src/total_word_feature_extractor.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "deps/MITIE-0.5/mitielib/include/",
        "deps/MITIE-0.5/dlib/"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions", "-fno-rtti"],
      "conditions": [
        ['OS=="mac"', {
          "xcode_settings": {
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
            "GCC_ENABLE_CPP_RTTI": "YES"
          }
        }]
      ]
    }
  ]
}
