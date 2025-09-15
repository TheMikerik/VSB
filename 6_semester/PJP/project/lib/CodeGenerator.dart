import 'package:antlr4/antlr4.dart';
import 'MyLangParser.dart';
import 'MyLangBaseVisitor.dart';

enum VarType { intType, floatType, boolType, stringType, fileType }

class CodeGenerator extends MyLangBaseVisitor<void> {
  final StringBuffer _output = StringBuffer();
  final Map<String, VarType> _symbolTable = {};
  int _labelCounter = 0;
  VarType? _lastExpressionType;

  String generate(ProgramContext programCtx) {
    _output.clear();
    visit(programCtx);
    return _output.toString();
  }

  int _nextLabel() => _labelCounter++;

  String _typeToInstructionType(VarType type) {
    switch (type) {
      case VarType.intType:
        return 'I';
      case VarType.floatType:
        return 'F';
      case VarType.stringType:
        return 'S';
      case VarType.boolType:
        return 'B';
      case VarType.fileType:
        return 'S';
    }
  }

  VarType _stringToType(String typeStr) {
    switch (typeStr) {
      case 'int':
        return VarType.intType;
      case 'float':
        return VarType.floatType;
      case 'bool':
        return VarType.boolType;
      case 'string':
        return VarType.stringType;
      case 'file':
        return VarType.fileType;
      default:
        return VarType.intType;
    }
  }

  bool _isNumeric(VarType? type) =>
      type == VarType.intType || type == VarType.floatType;

  @override
  void visitProgram(ProgramContext ctx) {
    ctx.statements().forEach(visit);
  }

  @override
  void visitEmptyStatement(EmptyStatementContext ctx) {}

  @override
  void visitDeclarationStmt(DeclarationStmtContext ctx) {
    final typeStr = ctx.type()?.text;
    final declaredType = _stringToType(typeStr!);

    final identifiers = ctx.variableList()!.Identifiers();
    for (var id in identifiers) {
      final varName = id.text;
      _symbolTable[varName!] = declaredType;

      switch (declaredType) {
        case VarType.intType:
          _output.writeln('push I 0');
          break;
        case VarType.floatType:
          _output.writeln('push F 0.0');
          break;
        case VarType.boolType:
          _output.writeln('push B false');
          break;
        case VarType.stringType:
        case VarType.fileType:
          _output.writeln('push S ""');
          break;
      }
      _output.writeln('save $varName');
    }
  }

  @override
  void visitReadStmt(ReadStmtContext ctx) {
    final identifiers = ctx.variableList()!.Identifiers();
    for (var id in identifiers) {
      final varName = id.text;
      final varType = _symbolTable[varName];
      if (varType != null) {
        final typeChar = _typeToInstructionType(varType);
        _output.writeln('read $typeChar');
        _output.writeln('save $varName');
      } else {
        _output.writeln('// ERROR: Undeclared variable $varName in read');
      }
    }
  }

  @override
  void visitFopenStmt(FopenStmtContext ctx) {
    final varName = ctx.Identifier()!.text;
    final pathToken = ctx.STRING()!.text!;

    _output.writeln('fopen $pathToken');
    _output.writeln('save $varName');
  }

  @override
  void visitWriteStmt(WriteStmtContext ctx) {
    final expressions = ctx.exprList()!.expressions();
    for (var expr in expressions) {
      visit(expr);
    }
    _output.writeln('print ${expressions.length}');
  }

  @override
  void visitIfStmt(IfStmtContext ctx) {
    final elseStmt = ctx.statement(1);
    final elseLabel = _nextLabel();
    final endLabel = _nextLabel();
    visit(ctx.expression() as ParseTree);
    _output.writeln('fjmp $elseLabel');
    visit(ctx.statement(0)!);
    _output.writeln('jmp $endLabel');
    _output.writeln('label $elseLabel');
    if (elseStmt != null) {
      visit(elseStmt);
    }
    _output.writeln('label $endLabel');
  }

  @override
  void visitWhileStmt(WhileStmtContext ctx) {
    final startLabel = _nextLabel();
    final endLabel = _nextLabel();

    // 1. Label for the start of the loop (condition check)
    _output.writeln('label $startLabel');

    // 2. Visit the condition expression
    visit(ctx.expression() as ParseTree); // Leaves boolean on stack

    // 3. Conditional jump out of the loop
    // If condition is false, jump to the end label
    _output.writeln('fjmp $endLabel');

    // 4. Visit the loop body statement
    visit(ctx.statement() as ParseTree);

    // 5. Jump back to the start label (condition check)
    _output.writeln('jmp $startLabel');

    // 6. Label for the end of the loop
    _output.writeln('label $endLabel');
  }

  @override
  void visitBlockStmt(BlockStmtContext ctx) {
    ctx.statements().forEach(visit);
  }

  @override
  void visitExprStmt(ExprStmtContext ctx) {
    visit(ctx.expression() as ParseTree);
    _output.writeln('pop');
  }

  @override
  void visitExpression(ExpressionContext ctx) {
    visit(ctx.assignment() as ParseTree);
  }

  @override
  void visitAssignment(AssignmentContext ctx) {
    if (ctx.assignment() != null) {
      final lhs = ctx.logicOr()!;
      final rhs = ctx.assignment()!;
      String? varName;
      ParserRuleContext? current = lhs;
      while (varName == null && current != null) {
        if (current is PrimaryContext && current.Identifier() != null) {
          varName = current.Identifier()!.text;
        } else if (current.childCount == 1 &&
            current.getChild(0) is ParserRuleContext) {
          current = current.getChild(0) as ParserRuleContext?;
        } else {
          break;
        }
      }

      if (varName != null) {
        final varType = _symbolTable[varName];
        visit(rhs);
        if (varType == VarType.floatType &&
            _lastExpressionType == VarType.intType) {
          _output.writeln('itof');
        }
        _output.writeln('save $varName');
        _output.writeln('load $varName');
        _lastExpressionType = varType;
      } else {
        _output.writeln("// ERROR: Invalid LHS in assignment");
        visit(rhs);
        _lastExpressionType = VarType.intType;
      }
    } else {
      visit(ctx.logicOr() as ParseTree);
    }
  }

  @override
  void visitLogicOr(LogicOrContext ctx) {
    if (ctx.logicAnds().length > 1) {
      visit(ctx.logicAnd(0)!);
      for (int i = 1; i < ctx.logicAnds().length; i++) {
        visit(ctx.logicAnd(i)!);
        _output.writeln('or');
        _lastExpressionType = VarType.boolType;
      }
    } else {
      visit(ctx.logicAnd(0)!);
    }
  }

  @override
  void visitLogicAnd(LogicAndContext ctx) {
    if (ctx.equalitys().length > 1) {
      visit(ctx.equality(0)!);
      for (int i = 1; i < ctx.equalitys().length; i++) {
        visit(ctx.equality(i)!);
        _output.writeln('and');
        _lastExpressionType = VarType.boolType;
      }
    } else {
      visit(ctx.equality(0)!);
    }
  }

  @override
  void visitEquality(EqualityContext ctx) {
    if (ctx.relationals().length > 1) {
      visit(ctx.relational(0)!);
      final leftType = _lastExpressionType;
      visit(ctx.relational(1)!);
      final rightType = _lastExpressionType;

      final op = ctx.getChild(1)!.text;

      VarType resultType = leftType!;
      if (_isNumeric(leftType) && _isNumeric(rightType)) {
        if (leftType == VarType.floatType || rightType == VarType.floatType) {
          resultType = VarType.floatType;
          if (rightType == VarType.intType) {
            _output.writeln('itof');
          }
        } else {
          resultType = VarType.intType; // Both are int
        }
      }
      // Assume strings/bools are compared directly if types match (ensured by type checker)

      final typeChar = _typeToInstructionType(resultType);
      _output.writeln('eq $typeChar'); // Perform equality check

      if (op == '!=') {
        _output.writeln('not'); // Negate result for !=
      }
      _lastExpressionType = VarType.boolType; // Result is boolean
    } else {
      visit(ctx.relational(0)!); // Only one operand
    }
  }

  // RELATIONAL < > (Left Associative)

  @override
  void visitRelational(RelationalContext ctx) {
    if (ctx.additives().length > 1) {
      visit(ctx.additive(0)!); // Visit left operand
      final leftType = _lastExpressionType;
      visit(ctx.additive(1)!); // Visit right operand
      final rightType = _lastExpressionType;

      final op = ctx.getChild(1)!.text; // '<' or '>'

      // Determine comparison type (handle int/float comparison)
      VarType cmpType = leftType!; // Default
      if (_isNumeric(leftType) && _isNumeric(rightType)) {
        if (leftType == VarType.floatType || rightType == VarType.floatType) {
          cmpType = VarType.floatType;
          // Add itof if needed (stack: left, right)
          if (rightType == VarType.intType) {
            _output.writeln('itof');
          }
        } else {
          cmpType = VarType.intType;
        }
      } else {
        // Type checker should prevent non-numeric relational ops
        _output.writeln("// ERROR: Non-numeric relational");
      }

      final typeChar = _typeToInstructionType(cmpType);
      if (op == '<') {
        _output.writeln('lt $typeChar');
      } else {
        // '>'
        _output.writeln('gt $typeChar');
      }
      _lastExpressionType = VarType.boolType; // Result is boolean
    } else {
      visit(ctx.additive(0)!); // Only one operand
    }
  }

  // ADDITIVE + - . (Left Associative)
  @override
  void visitAdditive(AdditiveContext ctx) {
    if (ctx.multiplicatives().length > 1) {
      visit(ctx.multiplicative(0)!); // Visit first operand
      VarType currentType = _lastExpressionType!;

      for (int i = 1; i < ctx.multiplicatives().length; i++) {
        final op = ctx.getChild(i * 2 - 1)!.text; // +, -, .
        visit(ctx.multiplicative(i)!); // Visit next operand
        final rightType = _lastExpressionType!;

        if (op == '.') {
          // String concatenation
          _output.writeln('concat');
          currentType = VarType.stringType;
        } else {
          // Arithmetic + or -
          VarType resultType = VarType.intType; // Default
          if (_isNumeric(currentType) && _isNumeric(rightType)) {
            if (currentType == VarType.floatType ||
                rightType == VarType.floatType) {
              resultType = VarType.floatType;
              // Add itof if needed (stack: left, right)
              if (rightType == VarType.intType) {
                _output.writeln('itof');
              }
            } else {
              resultType = VarType.intType;
            }
          } else {
            _output.writeln("// ERROR: Non-numeric add/sub");
          }

          final typeChar = _typeToInstructionType(resultType);
          if (op == '+') {
            _output.writeln('add $typeChar');
          } else {
            // '-'
            _output.writeln('sub $typeChar');
          }
          currentType = resultType;
        }
      }
      _lastExpressionType = currentType; // Store type of final result
    } else {
      visit(ctx.multiplicative(0)!); // Only one operand
    }
  }

  // MULTIPLICATIVE * / % (Left Associative)
  @override
  void visitMultiplicative(MultiplicativeContext ctx) {
    if (ctx.unarys().length > 1) {
      visit(ctx.unary(0)!); // Visit first operand
      VarType currentType = _lastExpressionType!;

      for (int i = 1; i < ctx.unarys().length; i++) {
        final op = ctx.getChild(i * 2 - 1)!.text; // *, /, %
        visit(ctx.unary(i)!); // Visit next operand
        final rightType = _lastExpressionType!;

        if (op == '%') {
          // Modulo - requires integers
          _output.writeln('mod');
          currentType = VarType.intType;
        } else {
          // Arithmetic * or /
          VarType resultType = VarType.intType; // Default
          if (_isNumeric(currentType) && _isNumeric(rightType)) {
            if (currentType == VarType.floatType ||
                rightType == VarType.floatType) {
              resultType = VarType.floatType;
              // Add itof if needed (stack: left, right)
              if (rightType == VarType.intType) {
                _output.writeln('itof');
              }
            } else {
              resultType = VarType.intType;
            }
          } else {
            _output.writeln("// ERROR: Non-numeric mul/div");
          }

          final typeChar = _typeToInstructionType(resultType);
          if (op == '*') {
            _output.writeln('mul $typeChar');
          } else {
            // '/'
            _output.writeln('div $typeChar');
          }
          currentType = resultType;
        }
      }
      _lastExpressionType = currentType;
    } else {
      visit(ctx.unary(0)!); // Only one operand
    }
  }

  // UNARY ! -
  @override
  void visitUnary(UnaryContext ctx) {
    if (ctx.primary() != null) {
      visit(ctx.primary() as ParseTree); // Just visit the primary expression
    } else {
      // Has a unary operator '!' or '-'
      visit(ctx.unary()!); // Visit the operand first
      final op = ctx.getChild(0)!.text;
      final operandType = _lastExpressionType;

      if (op == '!') {
        _output.writeln('not');
        _lastExpressionType = VarType.boolType;
      } else {
        // Unary '-'
        final typeChar = _typeToInstructionType(operandType!);
        _output.writeln('uminus $typeChar');
        _lastExpressionType = operandType; // Type doesn't change
      }
    }
  }

  // PRIMARY: Literals, Identifier, ( expression )
  @override
  void visitPrimary(PrimaryContext ctx) {
    if (ctx.INT() != null) {
      _output.writeln('push I ${ctx.INT()!.text}');
      _lastExpressionType = VarType.intType;
    } else if (ctx.FLOAT() != null) {
      _output.writeln('push F ${ctx.FLOAT()!.text}');
      _lastExpressionType = VarType.floatType;
    } else if (ctx.BOOL() != null) {
      _output.writeln('push B ${ctx.BOOL()!.text}');
      _lastExpressionType = VarType.boolType;
    } else if (ctx.STRING() != null) {
      final text = ctx.STRING()!.text!;
      final strValue = text
          .substring(1, text.length - 1)
          .replaceAll('""', '"'); // Handle escaped quotes if needed
      _output.writeln(
        'push S "$strValue"',
      ); // Ensure quotes are kept for string instruction
      _lastExpressionType = VarType.stringType;
    } else if (ctx.FILE() != null) {
      final text = ctx.FILE()!.text!;
      final strValue = text.substring(1, text.length - 1).replaceAll('""', '"');
      _output.writeln(
        'push S "$strValue"',
      ); // Treat file literal as string path
      _lastExpressionType = VarType.fileType;
    } else if (ctx.Identifier() != null) {
      final varName = ctx.Identifier()!.text;
      _output.writeln('load $varName');
      _lastExpressionType =
          _symbolTable[varName]; // Type is known from declaration
    } else if (ctx.expression() != null) {
      // Parenthesized expression: just visit the inner expression
      visit(ctx.expression()!);
    }
  }
}
