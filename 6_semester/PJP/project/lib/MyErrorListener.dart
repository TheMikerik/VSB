import 'package:antlr4/antlr4.dart';

class MyErrorListener extends BaseErrorListener {
  final List<String> errors = [];

  @override
  void syntaxError(
    Recognizer recognizer,
    Object? offendingSymbol,
    int? line,
    int charPositionInLine,
    String msg,
    RecognitionException? e,
  ) {
    errors.add("Line ${line ?? 0}:$charPositionInLine -> $msg");
  }

  bool get hasErrors => errors.isNotEmpty;
}
