class Flashcard {
  String id;
  String question;
  String answer;
  DateTime createdAt;

  Flashcard({
    required this.id,
    required this.question,
    required this.answer,
    required this.createdAt,
  });

  @override
  String toString() {
    return 'Flashcard ID: $id\nQuestion: $question\nAnswer: $answer\nCreated At: ${createdAt.toLocal()}';
  }
}
