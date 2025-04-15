import 'interpreter.dart'; // Assuming interpreter code is in interpreter.dart
import 'dart:io';

void main(List<String> args) {
  if (args.isEmpty) {
    print('Usage: dart run_interpreter.dart <instruction_file>');
    exit(1);
  }

  final instructionFile = args[0];

  if (!File(instructionFile).existsSync()) {
    print('Error: Instruction file "$instructionFile" not found.');
    exit(1);
  }

  print('--- Running Interpreter on $instructionFile ---');
  try {
    final interpreter = Interpreter();
    interpreter.run(instructionFile);
    print('\n--- Interpreter finished ---');
  } catch (e) {
    print('\n--- Interpreter Error ---');
    print(e);
    print('-------------------------');
    exit(1);
  }
}
