# MITIE

This project is a node binding for the [MIT Information Extraction library](https://github.com/mit-nlp/MITIE). It's written in C++ and js.

If you use MITIE, you already know how to use nlp-mitie.

Supported platforms: **Mac OS X** | **Linux**

## Installing

```
$ npm install nlp-mitie --save
```

## Quick Start

```
$ git clone https://github.com/alvinhui/nlp-mitie.git
$ cd nlp-mitie
$ npm install
$ node examples/english/ner.js
```

## Examples

### Named Entity Extractor(NER)

```
const { NamedEntityExtractor, TotalWordFeatureExtractor } = require('nlp-mitie');
const path =  require('path');

const totalWordFeatureExtractor = new TotalWordFeatureExtractor(path.join(__dirname, './models/english/total_word_feature_extractor.dat'));
const namedEntityExtractor = new NamedEntityExtractor(path.join(__dirname, './models/english/entity_extractor.dat'));
const tokens = ['show', 'me', 'chinese', 'restaurants'];

console.log(`NER: ${namedEntityExtractor}`);

const tags = namedEntityExtractor.getPossibleTags();
console.log(`Tags: ${tags}`);

const entities = namedEntityExtractor.extractEntities(tokens, totalWordFeatureExtractor);
console.log(`Entities: ${JSON.stringify(entities)}`);
```