// ignore_for_file: avoid_print

import 'package:test_flutter/models/flashcard.dart';
import 'package:test_flutter/services/flashcard_service.dart';

void main() {
  FlashcardService service = FlashcardService();

  service.createFlashcard('What is the capital of France?', 'Paris');
  service.createFlashcard(
      'What is the largest planet in our Solar System?', 'Jupiter');

  print('\nAll Flashcards:');
  service.getAllFlashcards().forEach((cards) => print(cards));

  String firstId = service.getAllFlashcards().first.id;
  print('\nFinding Flashcard $firstId:');
  try {
    Flashcard found = service.getFlashcard(firstId);
    print(found);
  } catch (e) {
    print(e);
  }

  service.updateFlashcard(firstId, question: 'EDIT: What is fifo?');

  print('\nUpdated Flashcard $firstId:');
  print(service.getFlashcard(firstId));

  if (service.getAllFlashcards().length > 1) {
    String secondId = service.getAllFlashcards()[1].id;
    service.deleteFlashcard(secondId);
  }

  print('\nAttempting to find deleted Flashcard:');
  try {
    String deletedId =
        service.getAllFlashcards().isNotEmpty ? 'non-existent-id' : 'fc002';
    Flashcard deleted = service.getFlashcard(deletedId);
    print(deleted);
  } catch (e) {
    print(e);
  }
  print('\nFinal Flashcards:');
  service.getAllFlashcards().forEach((fc) => print(fc));
}
