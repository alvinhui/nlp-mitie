export interface IEntity {
  entity: string;
  start: number;
  end: number;
  score: number;
}

export interface IIntent {
  intent: string;
  score: number;
}

declare class TotalWordFeatureExtractor {
  constructor(feFilePath?: string);
  numberDimensions: Array<any>;
  getFeatureVector(text: string): any;
}

declare class TextCategorizer {
  constructor(filePath: string, feFilePath?: string);
  classify(tokens: string[], featureExtractor?: TotalWordFeatureExtractor): IIntent[];
  saveToDisk(path: string, pureModel?: boolean): boolean;
}

declare class TextCategorizerTrainer {
  constructor(feFilePath?: string);
  add(tokens: string[], label: string): void;
  train(): TextCategorizer;;
  numThreads: number;
}

declare class NamedEntityExtractor {
  constructor(filePath?: string, feFilePath?: string);
  extractEntities(tokens: string[], featureExtractor?: TotalWordFeatureExtractor): IEntity[];
  saveToDisk(path: string, pureModel?: boolean): boolean;
  getPossibleTags(): string[];
}

declare class NerTrainingInstance {
  constructor(tokens: string[]);
  addEntity(start: number, length: number, entity: string): void;
}

declare class NerTrainer {
  constructor(feFilePath?: string);
  add(instance: NerTrainingInstance): void;
  train(): NamedEntityExtractor;
  numThreads: number;
}