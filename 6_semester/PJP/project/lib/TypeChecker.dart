import 'package:antlr4/antlr4.dart';
import 'package:my_project/MyLangParser.dart' as MyLangParser;
import 'MyLangBaseListener.dart';
import 'MyLangParser.dart';

enum VarType { intType, floatType, boolType, stringType, fileType }

class SimpleTypeChecker extends MyLangBaseListener {
  final Map<String, VarType> symbolTable = {};
  final List<String> errors = [];
  final Map<ParserRuleContext, VarType> _expressionTypes = {};

  @override
  void exitDeclarationStmt(DeclarationStmtContext ctx) {
    final typeStr = ctx.type()?.text;
    final declaredType = _stringToType(typeStr!);

    // variableList -> list of Identifiers
    final identifiers = ctx.variableList()!.Identifiers();
    for (var varCtx in identifiers) {
      final varName = varCtx.text;
      if (symbolTable.containsKey(varName)) {
        errors.add("Error: Variable '$varName' already declared.");
      } else {
        symbolTable[varName!] = declaredType;
      }
    }
  }

  @override
  void exitPrimary(PrimaryContext ctx) {
    VarType? type;
    if (ctx.INT() != null) {
      type = VarType.intType;
    } else if (ctx.FLOAT() != null) {
      type = VarType.floatType;
    } else if (ctx.BOOL() != null) {
      type = VarType.boolType;
    } else if (ctx.STRING() != null) {
      type = VarType.stringType;
    } else if (ctx.FILE() != null) {
      type = VarType.fileType;
    } else if (ctx.Identifier() != null) {
      final varName = ctx.Identifier()!.text;
      type = symbolTable[varName];
      if (type == null) {
        errors.add("Error: Undefined variable '$varName'");
      }
    } else if (ctx.expression() != null) {
      type = _expressionTypes[ctx.expression()!];
    }

    if (type != null) {
      _expressionTypes[ctx] = type;
    }
  }

  @override
  void exitUnary(UnaryContext ctx) {
    if (ctx.primary() != null) {
      final primaryCtx = ctx.primary()!;
      final primaryType = _expressionTypes[primaryCtx];
      if (primaryType != null) {
        _expressionTypes[ctx] = primaryType;
      }
      return;
    }
    final opChild = ctx.getChild(0);
    if (opChild == null) return;

    final operandCtx = ctx.unary();
    if (operandCtx == null) return;

    final operandType = _expressionTypes[operandCtx];
    if (operandType == null) return;

    final op = opChild.text;
    if (op == '!') {
      if (operandType != VarType.boolType) {
        errors.add("Error: '!' requires boolean operand");
      }
      _expressionTypes[ctx] = VarType.boolType;
    } else if (op == '-') {
      if (!_isNumeric(operandType)) {
        errors.add("Error: Unary '-' requires numeric operand");
      }
      _expressionTypes[ctx] = operandType;
    }
  }

  @override
  void exitMultiplicative(MultiplicativeContext ctx) {
    final unaryCount = ctx.unarys().length;
    if (unaryCount == 0) return;

    VarType? type = _expressionTypes[ctx.unary(0)];

    for (int i = 1; i < unaryCount; i++) {
      final op = ctx.getChild(i * 2 - 1)!.text;
      final rightType = _expressionTypes[ctx.unary(i)];

      if (type == null || rightType == null) continue;

      if (op == '%') {
        if (type != VarType.intType || rightType != VarType.intType) {
          errors.add("Error: Modulo requires integers");
        }
        type = VarType.intType;
      } else {
        if (!_isNumeric(type) || !_isNumeric(rightType)) {
          errors.add("Error: Operator '$op' requires numeric operands");
        }
        type = (type == VarType.floatType || rightType == VarType.floatType)
            ? VarType.floatType
            : VarType.intType;
      }
    }

    if (type != null) {
      _expressionTypes[ctx] = type;
    }
  }

  @override
  void exitAdditive(AdditiveContext ctx) {
    final multiplicativeCount = ctx.multiplicatives().length;
    if (multiplicativeCount == 0) return;

    VarType? type = _expressionTypes[ctx.multiplicative(0)];

    for (int i = 1; i < multiplicativeCount; i++) {
      final op = ctx.getChild(i * 2 - 1)!.text;
      final rightType = _expressionTypes[ctx.multiplicative(i)];

      if (type == null || rightType == null) continue;

      if (op == '+' || op == '-') {
        if (!_isNumeric(type) || !_isNumeric(rightType)) {
          errors.add("Error: Operator '$op' requires numeric operands");
        }
        type = (type == VarType.floatType || rightType == VarType.floatType)
            ? VarType.floatType
            : VarType.intType;
      } else if (op == '.') {
        if (type != VarType.stringType || rightType != VarType.stringType) {
          errors.add("Error: '.' requires string operands");
        }
        type = VarType.stringType;
      }
    }

    if (type != null) {
      _expressionTypes[ctx] = type;
    }
  }

  @override
  void exitRelational(RelationalContext ctx) {
    final additives = ctx.additives();
    if (additives.isEmpty) return;

    if (additives.length == 1) {
      _expressionTypes[ctx] = _expressionTypes[additives[0]]!;
      return;
    }

    if (additives.length >= 2) {
      final leftType = _expressionTypes[additives[0]];
      final rightType = _expressionTypes[additives[1]];
      if (leftType == null || rightType == null) return;

      final op = ctx.getChild(1)!.text; // '<' or '>'
      if (!_isNumeric(leftType) || !_isNumeric(rightType)) {
        errors.add("Error: Operator '$op' requires numeric operands");
      }
      _expressionTypes[ctx] = VarType.boolType;
    }
  }

  @override
  void exitEquality(EqualityContext ctx) {
    final relationals = ctx.relationals();
    if (relationals.isEmpty) return;

    if (relationals.length == 1) {
      _expressionTypes[ctx] = _expressionTypes[relationals[0]]!;
      return;
    }

    if (relationals.length >= 2) {
      final leftType = _expressionTypes[relationals[0]];
      final rightType = _expressionTypes[relationals[1]];
      if (leftType == null || rightType == null) return;

      final op = ctx.getChild(1)!.text; // '==' or '!='
      if (leftType != rightType &&
          !(_isNumeric(leftType) && _isNumeric(rightType))) {
        errors.add("Error: Operator '$op' type mismatch");
      }
      _expressionTypes[ctx] = VarType.boolType;
    }
  }

  @override
  void exitAssignment(AssignmentContext ctx) {
    if (ctx.assignment() == null) {
      final childExpr = ctx.logicOr();
      if (childExpr != null && _expressionTypes.containsKey(childExpr)) {
        _expressionTypes[ctx] = _expressionTypes[childExpr]!;
      }
      return;
    }

    final lhs = ctx.logicOr()!;
    final rhs = ctx.assignment()!;

    if (!_isVariable(lhs)) {
      errors.add("Error: Left-hand side must be a variable");
      return;
    }

    final primaryCtx = _getPrimary(lhs);
    if (primaryCtx?.Identifier() == null) {
      errors.add("Error: Invalid assignment target");
      return;
    }

    final varName = primaryCtx!.Identifier()!.text;
    final varType = symbolTable[varName];
    final exprType = _expressionTypes[rhs];

    if (varType == null) {
      errors.add("Error: Undefined variable '$varName'");
      return;
    }
    if (exprType == null) {
      return;
    }

    if (varType != exprType &&
        !(varType == VarType.floatType && exprType == VarType.intType)) {
      errors.add("Error: Type mismatch for '$varName'");
    }

    _expressionTypes[ctx] = varType;
  }

  @override
  void exitLogicOr(LogicOrContext ctx) {
    final logicAnds = ctx.logicAnds();
    if (logicAnds.isEmpty) return;

    if (logicAnds.length == 1) {
      _expressionTypes[ctx] = _expressionTypes[logicAnds[0]]!;
      return;
    }

    bool allBool = true;
    for (var logicAnd in logicAnds) {
      final operandType = _expressionTypes[logicAnd];
      if (operandType != VarType.boolType) {
        errors.add("Error: '||' requires boolean operands");
        allBool = false;
        break;
      }
    }

    if (allBool) {
      _expressionTypes[ctx] = VarType.boolType;
    }
  }

  @override
  void exitLogicAnd(LogicAndContext ctx) {
    final equalities = ctx.equalitys();
    if (equalities.isEmpty) return;

    if (equalities.length == 1) {
      _expressionTypes[ctx] = _expressionTypes[equalities[0]]!;
      return;
    }

    bool allBool = true;
    for (var part in equalities) {
      final operandType = _expressionTypes[part];
      if (operandType != VarType.boolType) {
        errors.add("Error: '&&' requires boolean operands");
        allBool = false;
        break;
      }
    }

    if (allBool) {
      _expressionTypes[ctx] = VarType.boolType;
    }
  }

  @override
  void exitIfStmt(IfStmtContext ctx) {
    final condExpr = ctx.expression();
    if (condExpr == null) return;

    exitExpression(condExpr);

    final condType = _expressionTypes[condExpr];
    if (condType != VarType.boolType) {
      errors.add("Error: 'if' condition must be boolean.");
    }
  }

  @override
  void exitWhileStmt(WhileStmtContext ctx) {
    final condExpr = ctx.expression();
    if (condExpr == null) return;

    exitExpression(condExpr);

    final condType = _expressionTypes[condExpr];
    if (condType != VarType.boolType) {
      errors.add("Error: 'while' condition must be boolean.");
    }
  }

  @override
  void exitExpression(ExpressionContext ctx) {
    final assignment = ctx.assignment();
    if (assignment != null && _expressionTypes.containsKey(assignment)) {
      _expressionTypes[ctx] = _expressionTypes[assignment]!;
    }
  }

  @override
  void exitReadStmt(ReadStmtContext ctx) {
    final vars = ctx.variableList()!.Identifiers();
    for (var part in vars) {
      final varName = part.text;
      if (!symbolTable.containsKey(varName)) {
        errors.add("Error: Variable '$varName' is not declared.");
      }
    }
  }

  @override
  void exitFopenStmt(FopenStmtContext ctx) {
    final varName = ctx.Identifier()!.text;
    if (!symbolTable.containsKey(varName)) {
      errors.add("Error: Variable '$varName' not declared.");
    } else if (symbolTable[varName] != VarType.fileType) {
      errors.add("Error: Variable '$varName' must be of type 'file'.");
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
        errors.add("Error: Unknown type '$typeStr'.");
        return VarType.intType;
    }
  }

  bool _isNumeric(VarType? type) =>
      type == VarType.intType || type == VarType.floatType;

  bool _isVariable(ParserRuleContext ctx) {
    final primaryCtx = _getPrimary(ctx);
    if (primaryCtx == null) return false;
    return primaryCtx.Identifier() != null;
  }

  MyLangParser.PrimaryContext? _getPrimary(ParserRuleContext ctx) {
    if (ctx is MyLangParser.PrimaryContext) {
      return ctx;
    }
    for (int i = 0; i < ctx.childCount; i++) {
      final child = ctx.getChild(i);
      if (child is ParserRuleContext) {
        final result = _getPrimary(child);
        if (result != null) {
          return result;
        }
      }
    }
    return null;
  }
}
