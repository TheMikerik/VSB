import 'dart:io';
import 'dart:collection';
import 'dart:convert';

class Interpreter {
  final Queue<dynamic> _stack = Queue<dynamic>();
  final Map<String, dynamic> _variables = {};
  final Map<int, int> _labels = {};
  int _instr = 0;

  void run(String filename) {
    final lines = File(filename).readAsLinesSync();
    final instructions = _preprocess(lines);

    _instr = 0;
    while (_instr < instructions.length) {
      final instruction = instructions[_instr];
      _executeInstruction(instruction);
      _instr++;
    }
  }

  List<String> _preprocess(List<String> lines) {
    final cleanLines = <String>[];
    int lineNumber = 0;

    for (var line in lines) {
      line = line.trim();
      if (line.isEmpty || line.startsWith('//')) {
        continue;
      }

      if (line.startsWith('label ')) {
        final labelNum = int.parse(line.substring(6));
        _labels[labelNum] = lineNumber;
      } else {
        cleanLines.add(line);
        lineNumber++;
      }
    }

    return cleanLines;
  }

  // Execute a single instruction
  void _executeInstruction(String instruction) {
    final parts = instruction.split(' ');
    final op = parts[0];

    switch (op) {
      case 'push':
        _handlePush(parts);
        break;
      case 'pop':
        _stack.removeFirst();
        break;
      case 'load':
        final id = parts[1];
        _stack.addFirst(_variables[id]);
        break;
      case 'save':
        final id = parts[1];
        if (_stack.isEmpty) {
          throw Exception('Stack underflow for save operation');
        }
        // Consume the value from the stack
        _variables[id] = _stack.removeFirst();
        break; // Add break if it wasn't there implicitly
      case 'add':
        _handleBinaryOp('add', parts[1]);
        break;
      case 'sub':
        _handleBinaryOp('sub', parts[1]);
        break;
      case 'mul':
        _handleBinaryOp('mul', parts[1]);
        break;
      case 'div':
        _handleBinaryOp('div', parts[1]);
        break;
      case 'mod':
        final b = _stack.removeFirst() as int;
        final a = _stack.removeFirst() as int;
        _stack.addFirst(a % b);
        break;
      case 'uminus':
        _handleUnaryMinus(parts[1]);
        break;
      case 'concat':
        final b = _stack.removeFirst() as String;
        final a = _stack.removeFirst() as String;
        _stack.addFirst('$a$b');
        break;
      case 'and':
        final b = _stack.removeFirst() as bool;
        final a = _stack.removeFirst() as bool;
        _stack.addFirst(a && b);
        break;
      case 'or':
        final b = _stack.removeFirst() as bool;
        final a = _stack.removeFirst() as bool;
        _stack.addFirst(a || b);
        break;
      case 'gt':
        _handleComparison('gt', parts[1]);
        break;
      case 'lt':
        _handleComparison('lt', parts[1]);
        break;
      case 'eq':
        _handleComparison('eq', parts[1]);
        break;
      case 'not':
        final a = _stack.removeFirst() as bool;
        _stack.addFirst(!a);
        break;
      case 'itof':
        final a = _stack.removeFirst() as int;
        _stack.addFirst(a.toDouble());
        break;
      case 'jmp':
        final labelNum = int.parse(parts[1]);
        if (_labels.containsKey(labelNum)) {
          _instr = _labels[labelNum]! - 1;
        } else {
          throw Exception('Label $labelNum not found');
        }
        break;
      case 'fjmp':
        final labelNum = int.parse(parts[1]);
        final condition = _stack.removeFirst() as bool;
        if (!condition && _labels.containsKey(labelNum)) {
          _instr = _labels[labelNum]! - 1;
        }
        break;
      case 'print':
        final count = int.parse(parts[1]);
        final values = <dynamic>[];
        for (var i = 0; i < count; i++) {
          values.add(_stack.removeFirst());
        }
        for (var v in values.reversed) {
          stdout.write('$v ');
        }
        stdout.writeln();
        break;
      case 'fopen':
        final varName = parts[1];
        final filePath = _stack.removeFirst() as String;
        final file = File(filePath);
        file.createSync(recursive: true);
        _variables[varName] = file;
        break;
      case 'fappend':
        final value = _stack.removeFirst();
        final file = _stack.removeFirst() as File;
        file.writeAsStringSync('$value', mode: FileMode.append);
        break;
      case 'read':
        final type = parts[1];
        final input = stdin.readLineSync(encoding: utf8);

        switch (type) {
          case 'I':
            _stack.addFirst(int.parse(input!));
            break;
          case 'F':
            _stack.addFirst(double.parse(input!));
            break;
          case 'S':
            _stack.addFirst(input);
            break;
          case 'B':
            _stack.addFirst(input?.toLowerCase() == 'true');
            break;
        }
        break;
    }
  }

  // Handle push instruction for different types
  void _handlePush(List<String> parts) {
    final type = parts[1];
    final valueStr = parts.sublist(2).join(' ');

    switch (type) {
      case 'I':
        _stack.addFirst(int.parse(valueStr));
        break;
      case 'F':
        _stack.addFirst(double.parse(valueStr));
        break;
      case 'S':
        // Remove quotes if present
        var str = valueStr;
        if (str.startsWith('"') && str.endsWith('"')) {
          str = str.substring(1, str.length - 1);
        }
        _stack.addFirst(str);
        break;
      case 'B':
        _stack.addFirst(valueStr == 'true');
        break;
    }
  }

  // Handle binary arithmetic operations
  // Handle binary arithmetic operations
  void _handleBinaryOp(String op, String type) {
    if (_stack.length < 2) throw Exception('Stack underflow for $op $type');
    var b = _stack.removeFirst();
    var a = _stack.removeFirst();

    // Implicit conversion for float operations
    if (type == 'F') {
      if (a is int) a = a.toDouble();
      if (b is int) b = b.toDouble();
      // Ensure they are actually doubles now for safety
      if (a is! double || b is! double) {
        throw Exception(
          'Type error during implicit conversion for $op F: Operands are $a (${a.runtimeType}) and $b (${b.runtimeType})',
        );
      }
    } else if (type == 'I') {
      if (a is! int || b is! int) {
        throw Exception(
          'Type error for $op I: Operands must be int, got $a (${a.runtimeType}) and $b (${b.runtimeType})',
        );
      }
    }

    switch (op) {
      case 'add':
        _stack.addFirst(a + b);
        break;
      case 'sub':
        _stack.addFirst(a - b);
        break;
      case 'mul':
        _stack.addFirst(a * b);
        break;
      case 'div':
        // Check for division by zero (both int and float)
        if ((type == 'I' && b == 0) || (type == 'F' && b == 0.0)) {
          throw Exception('Division by zero');
        }

        if (type == 'F') {
          _stack.addFirst(a / b); // Float division
        } else {
          // type == 'I'
          _stack.addFirst(a ~/ b); // USE INTEGER DIVISION operator ~/
        }
        break; // Ensure break is here
    }
  }

  // Handle comparison operations
  void _handleComparison(String op, String type) {
    if (_stack.length < 2) throw Exception('Stack underflow for $op $type');
    var b = _stack.removeFirst();
    var a = _stack.removeFirst();

    // Implicit conversion for float comparisons
    if (type == 'F') {
      if (a is int) a = a.toDouble();
      if (b is int) b = b.toDouble();
      if (a is! double || b is! double) {
        throw Exception(
          'Type error during implicit conversion for $op F: Operands are $a (${a.runtimeType}) and $b (${b.runtimeType})',
        );
      }
    } else if (type == 'I') {
      if (a is! int || b is! int) {
        throw Exception(
          'Type error for $op I: Operands must be int, got $a (${a.runtimeType}) and $b (${b.runtimeType})',
        );
      }
    } else if (type == 'S') {
      if (a is! String || b is! String) {
        throw Exception(
          'Type error for $op S: Operands must be String, got $a (${a.runtimeType}) and $b (${b.runtimeType})',
        );
      }
    } // Add 'B' if boolean comparison needed for eq

    // Use Comparable interface for gt/lt to handle different types correctly
    // Note: Dart's built-in operators > < == work across num types due to promotion.
    bool result;
    switch (op) {
      case 'gt':
        // result = (a as Comparable).compareTo(b) > 0; // More robust way
        result = a > b; // Simpler way relying on Dart's > for num
        break;
      case 'lt':
        // result = (a as Comparable).compareTo(b) < 0;
        result = a < b; // Simpler way relying on Dart's < for num
        break;
      case 'eq':
        result = (a == b);
        break;
      default: // Should not happen
        throw Exception("Unknown comparison op: $op");
    }
    _stack.addFirst(result);
  }

  // Handle unary minus
  void _handleUnaryMinus(String type) {
    if (type == 'I') {
      final value = _stack.removeFirst() as int;
      _stack.addFirst(-value);
    } else if (type == 'F') {
      final value = _stack.removeFirst() as double;
      _stack.addFirst(-value);
    }
  }
}
