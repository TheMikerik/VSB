import 'dart:io';
import 'package:antlr4/antlr4.dart';
import 'MyLangLexer.dart';
import 'MyLangParser.dart';
import 'MyErrorListener.dart';
import 'TypeChecker.dart'; // Assuming TypeChecker uses Listener is fine
import 'CodeGenerator.dart'; // Import the Visitor-based generator

void main(List<String> args) {
  final inputFile = args[0];
  final outputFile = args[1];

  try {
    // ... (reading file, lexer, token stream, parser setup remains the same) ...
    final source = File(inputFile).readAsStringSync();
    final inputStream = InputStream.fromString(source);
    final lexer = MyLangLexer(inputStream);
    final tokenStream = CommonTokenStream(lexer);
    final parser = MyLangParser(tokenStream);

    final errorListener = MyErrorListener();
    parser.removeErrorListeners();
    parser.addErrorListener(errorListener);

    final tree = parser.program();

    if (errorListener.hasErrors) {
      print("Syntax errors found:");
      errorListener.errors.forEach(print);
      return;
    }

    // Type checking (can still use the Listener here)
    final typeChecker = SimpleTypeChecker();
    ParseTreeWalker.DEFAULT.walk(typeChecker, tree); // Use walker for listener

    if (typeChecker.errors.isNotEmpty) {
      print("Type errors found:");
      typeChecker.errors.forEach(print);
      return;
    }

    // --- Code generation using Visitor ---
    final codeGenerator = CodeGenerator();
    // Directly call visit on the generator instance for the tree root
    final generatedCode = codeGenerator.generate(
      tree,
    ); // Or call generator.visit(tree) and get code from generator._output

    File(outputFile).writeAsStringSync(generatedCode);

    print("Code generation completed successfully.");
    print("Generated code written to $outputFile.");
  } catch (e) {
    print("An error occurred: $e");
  }
}
