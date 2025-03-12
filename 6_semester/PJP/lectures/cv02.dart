import 'dart:io';

List<String> tokenize(String expr) {
  List<String> tokens = [];

  expr = expr.replaceAll(" ", "");

  for (int i = 0; i < expr.length; i++) {
    String currentToken = "";

    currentToken = expr[i];

    tokens.add(currentToken);
  }

  return tokens;
}

void main() {
  int n = int.parse(stdin.readLineSync()!);

  for (int i = 0; i < n; i++) {
    try {
      String expression = stdin.readLineSync()!;
      List<String> result = tokenize(expression);
      print(result);
    } catch (e) {
      print("ERROR");
    }
  }
}
