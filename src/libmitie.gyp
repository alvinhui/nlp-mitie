{
  'targets': [
    {
      'target_name': 'libmitie',
      'win_delay_load_hook': 'false',
      'type': 'static_library',
      'sources': [
        # dlib
        "libmitie/dlib/dlib/threads/multithreaded_object_extension.cpp",
        "libmitie/dlib/dlib/threads/threaded_object_extension.cpp",
        "libmitie/dlib/dlib/threads/threads_kernel_1.cpp",
        "libmitie/dlib/dlib/threads/threads_kernel_2.cpp",
        "libmitie/dlib/dlib/threads/threads_kernel_shared.cpp",
        "libmitie/dlib/dlib/threads/thread_pool_extension.cpp",
        "libmitie/dlib/dlib/misc_api/misc_api_kernel_1.cpp",
        "libmitie/dlib/dlib/misc_api/misc_api_kernel_2.cpp",

        # mitie
        "libmitie/mitielib/src/mitie.cpp",
        "libmitie/mitielib/src/named_entity_extractor.cpp",
        "libmitie/mitielib/src/ner_feature_extraction.cpp",
        "libmitie/mitielib/src/text_categorizer.cpp",
        "libmitie/mitielib/src/binary_relation_detector.cpp",
        "libmitie/mitielib/src/binary_relation_detector_trainer.cpp",
        "libmitie/mitielib/src/stem.c",
        "libmitie/mitielib/src/stemmer.cpp",
        "libmitie/mitielib/src/conll_parser.cpp",
        "libmitie/mitielib/src/ner_trainer.cpp",
        "libmitie/mitielib/src/text_categorizer_trainer.cpp",
        "libmitie/mitielib/src/text_feature_extraction.cpp",
      ],
      'cflags!': [
        '-fno-rtti',
        '-fno-exceptions'
      ],
      'cflags_cc!': [
        '-fno-rtti',
        '-fno-exceptions'
      ],
      'cflags_cc': [
        '-fexceptions',
        '-frtti',
      ],
      'include_dirs': [ 
        "libmitie/mitielib/include/",
        "libmitie/dlib/"
       ],
      'direct_dependent_settings': {
        'include_dirs': [ 
            "libmitie/mitielib/include/",
            "libmitie/dlib/"
         ],
      },
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'GCC_ENABLE_CPP_RTTI': 'YES'
          }
        }],
        ['OS!="win"', {
          'cflags_cc+': [
            '-std=c++0x'
          ]
        }]
      ]
    }
  ]
}
