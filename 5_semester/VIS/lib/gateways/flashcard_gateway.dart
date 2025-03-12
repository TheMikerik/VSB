// ignore_for_file: avoid_print

import 'package:test_flutter/models/flashcard.dart';

class FlashcardGateway {
  static final List<Flashcard> _flashcards = [];

  void insert(Flashcard flashcard) {
    _flashcards.add(flashcard);
    print('Flashcard ${flashcard.id} inserted.');
  }

  Flashcard? find(String id) {
    return _flashcards.firstWhere(
      (flashcard) => flashcard.id == id,
      orElse: () => throw Exception('Flashcard with ID $id not found.'),
    );
  }

  List<Flashcard> findAll() {
    return List.unmodifiable(_flashcards);
  }

  void update(Flashcard updatedFlashcard) {
    for (int i = 0; i < _flashcards.length; i++) {
      if (_flashcards[i].id == updatedFlashcard.id) {
        _flashcards[i] = updatedFlashcard;
        print('Flashcard ${updatedFlashcard.id} updated.');
        return;
      }
    }
    throw Exception('Flashcard with ID ${updatedFlashcard.id} not found.');
  }

  void delete(String id) {
    int initialLength = _flashcards.length;
    _flashcards.removeWhere((flashcard) => flashcard.id == id);
    if (_flashcards.length < initialLength) {
      print('Flashcard $id deleted.');
    } else {
      throw Exception('Flashcard with ID $id not found.');
    }
  }
}
