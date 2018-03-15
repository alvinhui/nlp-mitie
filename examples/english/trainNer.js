const { NerTrainer, NerTrainingInstance, NamedEntityExtractor } = require('../../lib/index');
const path =  require('path');

const sample  = new NerTrainingInstance(["My", "name", "is", "Davis", "King", "and", "I", "work", "for", "MIT", "."]);
sample.addEntity(3, 2, "person");
sample.addEntity(9, 1, "org");

const sample2 = new NerTrainingInstance(["The", "other", "day", "at", "work", "I", "saw", "Brian", "Smith", "from", "CMU", "."])
sample2.addEntity(7, 2, "person")
sample2.addEntity(10, 1, "org")

const feFilePath = path.join(__dirname, '../../models/english/total_word_feature_extractor.dat');
const trainer = new NerTrainer(feFilePath);
trainer.add(sample);
trainer.add(sample2);
const ner = trainer.train();
console.log(`ner: ${ner}`);

if (ner) {
  const filePath = path.join(__dirname, "new_ner_model.dat");
  const tags = ner.getPossibleTags();
  console.log(`NER Tags: ${tags}`);
  const saveResult = ner.saveToDisk(filePath, true);
  console.log(`Save model result is: ${saveResult}`);

  if (saveResult) {
    const newNer = new NamedEntityExtractor(filePath, feFilePath);
    const tokens = ["I", "met", "with", "John", "Becker", "at", "HBU", "."]
    const entities = newNer.extractEntities(tokens, true);
    console.log(`entities: ${entities}`);
    console.log(`entities json: ${JSON.stringify(entities)}`);
  }
}