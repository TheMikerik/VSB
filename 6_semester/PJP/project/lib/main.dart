import 'dart:io';
import 'package:antlr4/antlr4.dart';
import 'MyLangLexer.dart';
import 'MyLangParser.dart';
import 'MyErrorListener.dart';
import 'TypeChecker.dart';

void main(List<String> args) {
  final source = File('test.txt').readAsStringSync();

  final inputStream = InputStream.fromString(source);
  final lexer = MyLangLexer(inputStream);
  final tokenStream = CommonTokenStream(lexer);
  final parser = MyLangParser(tokenStream);

  final errorListener = MyErrorListener();
  parser.removeErrorListeners();
  parser.addErrorListener(errorListener);

  final tree = parser.program();
  if (errorListener.hasErrors) {
    print("Syntax Errors Found:");
    errorListener.errors.forEach(print);
    return;
  }
  print("No syntax errors found.");

  final typeChecker = SimpleTypeChecker();
  ParseTreeWalker.DEFAULT.walk(typeChecker, tree);

  if (typeChecker.errors.isNotEmpty) {
    print("Type Errors Found:");
    typeChecker.errors.forEach(print);
    return;
  }
  print("Parsing and type checking OK");
}
