const { NamedEntityExtractor, TotalWordFeatureExtractor } = require('../../lib/index');
const path =  require('path');

// 1. mitie::named_entity_extractor
// const namedEntityExtractor = new NamedEntityExtractor(path.join(__dirname, '../models/english/ner_model.dat'));
// const tokens = ['A', 'Pegasus', 'Airlines', 'plane', 'landed', 'at', 'an', 'Istanbul', 'airport', 'Friday', 'after', 'a', 'passenger', '"', 'said', 'that', 'there', 'was', 'a', 'bomb', 'on', 'board', '"', 'and', 'wanted', 'the', 'plane', 'to', 'land', 'in', 'Sochi', ',', 'Russia', ',', 'the', 'site', 'of', 'the', 'Winter', 'Olympics', ',', 'said', 'officials', 'with', 'Turkey', "'s", 'Transportation', 'Ministry', '.', 'Meredith', 'Vieira', 'will', 'become', 'the', 'first', 'woman', 'to', 'host', 'Olympics', 'primetime', 'coverage', 'on', 'her', 'own', 'when', 'she', 'fills', 'on', 'Friday', 'night', 'for', 'the', 'ailing', 'Bob', 'Costas', ',', 'who', 'is', 'battling', 'a', 'continuing', 'eye', 'infection', '.', '"', 'It', "'s", 'an', 'honor', 'to', 'fill', 'in', 'for', 'him', ',', '"', 'Vieira', 'said', 'on', 'TODAY', 'Friday', '.', '"', 'You', 'think', 'about', 'the', 'Olympics', ',', 'and', 'you', 'think', 'the', 'athletes', 'and', 'then', 'Bob', 'Costas', '.', '"', '"', 'Bob', "'s", 'eye', 'issue', 'has', 'improved', 'but', 'he', "'s", 'not', 'quite', 'ready', 'to', 'do', 'the', 'show', ',', '"', 'NBC', 'Olympics', 'Executive', 'Producer', 'Jim', 'Bell', 'told', 'TODAY', '.', 'com', 'from', 'Sochi', 'on', 'Thursday', '.', 'From', 'wikipedia', 'we', 'learn', 'that', 'Josiah', 'Franklin', "'s", 'son', ',', 'Benjamin', 'Franklin', 'was', 'born', 'in', 'Boston', '.', 'Since', 'wikipedia', 'allows', 'anyone', 'to', 'edit', 'it', ',', 'you', 'could', 'change', 'the', 'entry', 'to', 'say', 'that', 'Philadelphia', 'is', 'the', 'birthplace', 'of', 'Benjamin', 'Franklin', '.', 'However', ',', 'that', 'would', 'be', 'a', 'bad', 'edit', 'since', 'Benjamin', 'Franklin', 'was', 'definitely', 'born', 'in', 'Boston', '.'];

// 2. mitie::named_entity_extractor_pure_model
const totalWordFeatureExtractor = new TotalWordFeatureExtractor(path.join(__dirname, '../../models/english/total_word_feature_extractor.dat'));
const namedEntityExtractor = new NamedEntityExtractor(path.join(__dirname, '../../models/english/entity_extractor.dat'));
const tokens = ['show', 'me', 'chinese', 'restaurants'];

console.log(`NER: ${namedEntityExtractor}`);

const tags = namedEntityExtractor.getPossibleTags();
console.log(`Tags: ${tags}`);

// 1. mitie::named_entity_extractor
// const entities = namedEntityExtractor.extractEntities(tokens);

// 2. mitie::named_entity_extractor_pure_model
const entities = namedEntityExtractor.extractEntities(tokens, totalWordFeatureExtractor);
console.log(`Entities: ${JSON.stringify(entities)}`);