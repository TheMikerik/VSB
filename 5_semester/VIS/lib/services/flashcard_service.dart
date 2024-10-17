import 'package:test_flutter/gateways/flashcard_gateway.dart';
import 'package:test_flutter/models/flashcard.dart';
import 'package:test_flutter/utils/uuid_generator.dart';

class FlashcardService {
  final FlashcardGateway _gateway = FlashcardGateway();

  void createFlashcard(String question, String answer) {
    String id = UUIDGenerator.generateUUID();
    Flashcard flashcard = Flashcard(
      id: id,
      question: question,
      answer: answer,
      createdAt: DateTime.now(),
    );
    _gateway.insert(flashcard);
  }

  Flashcard getFlashcard(String id) {
    return _gateway.find(id)!;
  }

  List<Flashcard> getAllFlashcards() {
    return _gateway.findAll();
  }

  void updateFlashcard(String id, {String? question, String? answer}) {
    Flashcard? flashcard = _gateway.find(id);
    if (flashcard != null) {
      Flashcard updatedFlashcard = Flashcard(
        id: flashcard.id,
        question: question ?? flashcard.question,
        answer: answer ?? flashcard.answer,
        createdAt: flashcard.createdAt,
      );
      _gateway.update(updatedFlashcard);
    }
  }

  void deleteFlashcard(String id) {
    _gateway.delete(id);
  }
}
