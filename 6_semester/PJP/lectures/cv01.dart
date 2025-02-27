import 'dart:io';

int calculate(String expr) {
  expr = expr.replaceAll(" ", "");

  while (expr.contains("(")) {
    int openIndex = expr.lastIndexOf("(");
    int closeIndex = findClose(expr, openIndex);

    String innerExpr = expr.substring(openIndex + 1, closeIndex);
    int innerResult = computeTwoNumbers(innerExpr);

    expr = expr.replaceRange(openIndex, closeIndex + 1, innerResult.toString());
  }

  return computeTwoNumbers(expr);
}

int findClose(String expr, int openIndex) {
  int count = 1;
  for (int i = openIndex + 1; i < expr.length; i++) {
    if (expr[i] == '(') count++;
    if (expr[i] == ')') count--;
    if (count == 0) return i;
  }
  return -1;
}

int computeTwoNumbers(String expr) {
  List<String> parts = [];
  String currentNum = "";
  String operators = "+-*/";

  for (int i = 0; i < expr.length; i++) {
    if (operators.contains(expr[i])) {
      if (currentNum.isNotEmpty) {
        parts.add(currentNum);
        currentNum = "";
      }
      parts.add(expr[i]);
    } else {
      currentNum += expr[i];
    }
  }
  if (currentNum.isNotEmpty) {
    parts.add(currentNum);
  }

  for (int i = 1; i < parts.length - 1; i++) {
    if (parts[i] == "*") {
      int left = int.parse(parts[i - 1]);
      int right = int.parse(parts[i + 1]);
      parts[i - 1] = (left * right).toString();
      parts.removeRange(i, i + 2);
      i--;
    } else if (parts[i] == "/") {
      int left = int.parse(parts[i - 1]);
      int right = int.parse(parts[i + 1]);
      if (right == 0) throw Exception("Division by zero");
      parts[i - 1] = (left ~/ right).toString();
      parts.removeRange(i, i + 2);
      i--;
    }
  }

  int result = int.parse(parts[0]);
  for (int i = 1; i < parts.length - 1; i += 2) {
    String op = parts[i];
    int nextNum = int.parse(parts[i + 1]);

    if (op == "+") {
      result += nextNum;
    } else if (op == "-") {
      result -= nextNum;
    }
  }

  return result;
}

void main() {
  int n = int.parse(stdin.readLineSync()!);

  for (int i = 0; i < n; i++) {
    try {
      String expression = stdin.readLineSync()!;
      int result = calculate(expression);
      print(result);
    } catch (e) {
      print("ERROR");
    }
  }
}
