import 'interpreter.dart'; // Assuming interpreter code is in interpreter.dart
import 'dart:io';

void main(List<String> args) {
  final instructionFile = args[0];

  try {
    final interpreter = Interpreter();
    interpreter.run(instructionFile);
  } catch (e) {
    print(e);
    exit(1);
  }
}
