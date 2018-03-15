# MITIE

This project is a node binding for the [MIT Information Extraction library](https://github.com/mit-nlp/MITIE). It's written in C++ and js.

If you use MITIE, you already know how to use nlp-mitie.

Supported platforms: **Mac OS X** | **Linux**

## Installing

```
$ tnpm install nlp-mitie --save
```

## Quick Start

```
$ git clone git@github.com:alvinhui/nlp-mitie.git
$ cd nlp-mitie
$ tnpm install
$ node examples/english/ner.js
```

## Examples

### Named Entity Extractor(NER)

```
import { NerTrainer, NerTrainingInstance } from 'nlp-mitie';

const sample  = new NerTrainingInstance(['My', 'name', 'is', 'Davis', 'King', 'and', 'I', 'work', 'for', 'MIT', '.']);
sample.addEntity(3, 2, 'person');
sample.addEntity(9, 1, 'org');

const sample2 = new NerTrainingInstance(['The', 'other', 'day', 'at', 'work', 'I', 'saw', 'Brian', 'Smith', 'from', 'CMU', '.'])
sample2.addEntity(7, 2, 'person')
sample2.addEntity(10, 1, 'org')

const trainer = new NerTrainer('models/english/total_word_feature_extractor.dat');
trainer.add(sample);
trainer.add(sample2);
const ner = trainer.train();

const tokens = ['I', 'met', 'with', 'John', 'Becker', 'at', 'HBU', '.']
const entities = ner.extractEntities(tokens, true);
console.log(entities);
// [ {'score': 0.8662716633696536,'entity': 'org','start': 6,'end': 7} ]
```