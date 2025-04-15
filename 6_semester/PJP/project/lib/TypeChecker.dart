import 'package:antlr4/antlr4.dart';
import 'package:my_project/MyLangParser.dart' as MyLangParser;
import 'MyLangBaseListener.dart';
import 'MyLangParser.dart';

enum VarType { intType, floatType, boolType, stringType, fileType }

class SimpleTypeChecker extends MyLangBaseListener {
  final Map<String, VarType> symbolTable = {};
  final List<String> errors = [];

  // Maps each expression node to its deduced type
  final Map<ParserRuleContext, VarType> _expressionTypes = {};

  /* ----------------------------------------------------------------------
   *  1. Declaration
   * -------------------------------------------------------------------- */
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

  /* ----------------------------------------------------------------------
   *  2. Primary Expressions
   * -------------------------------------------------------------------- */
  @override
  void exitPrimary(PrimaryContext ctx) {
    VarType? type;
    if (ctx.IntegerLiteral() != null) {
      type = VarType.intType;
    } else if (ctx.FloatLiteral() != null) {
      type = VarType.floatType;
    } else if (ctx.BooleanLiteral() != null) {
      type = VarType.boolType;
    } else if (ctx.StringLiteral() != null) {
      type = VarType.stringType;
    } else if (ctx.FileLiteral() != null) {
      type = VarType.fileType;
    } else if (ctx.Identifier() != null) {
      final varName = ctx.Identifier()!.text;
      type = symbolTable[varName];
      if (type == null) {
        errors.add("Error: Undefined variable '$varName'");
      }
    } else if (ctx.expression() != null) {
      // Parenthesized expression: use child expression's type
      type = _expressionTypes[ctx.expression()!];
    }

    if (type != null) {
      _expressionTypes[ctx] = type;
    }
  }

  /* ----------------------------------------------------------------------
   *  3. Unary Expressions
   * -------------------------------------------------------------------- */
  @override
  void exitUnary(UnaryContext ctx) {
    if (ctx.primary() != null) {
      // Inherit the primary expression's type
      final primaryCtx = ctx.primary()!;
      final primaryType = _expressionTypes[primaryCtx];
      if (primaryType != null) {
        _expressionTypes[ctx] = primaryType;
      }
      return;
    }

    // It's a unary operator: '!' or '-'
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

  /* ----------------------------------------------------------------------
   *  4. Multiplicative & Additive
   * -------------------------------------------------------------------- */
  @override
  void exitMultiplicative(MultiplicativeContext ctx) {
    final unaryCount = ctx.unarys().length;
    if (unaryCount == 0) return;

    // Start from the type of the first unary
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
        // '*' or '/'
        if (!_isNumeric(type) || !_isNumeric(rightType)) {
          errors.add("Error: Operator '$op' requires numeric operands");
        }
        // If either side is float -> result is float, else int
        type =
            (type == VarType.floatType || rightType == VarType.floatType)
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
        // numeric check
        if (!_isNumeric(type) || !_isNumeric(rightType)) {
          errors.add("Error: Operator '$op' requires numeric operands");
        }
        // If either side is float -> result is float, else int
        type =
            (type == VarType.floatType || rightType == VarType.floatType)
                ? VarType.floatType
                : VarType.intType;
      } else if (op == '.') {
        // string concatenation
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

  /* ----------------------------------------------------------------------
   *  5. Relational & Equality
   * -------------------------------------------------------------------- */
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

  /* ----------------------------------------------------------------------
   *  6. Assignment
   * -------------------------------------------------------------------- */
  @override
  void exitAssignment(AssignmentContext ctx) {
    // If it's just a single expression, propagate the type from its child.
    if (ctx.assignment() == null) {
      final childExpr = ctx.logicOr();
      if (childExpr != null && _expressionTypes.containsKey(childExpr)) {
        _expressionTypes[ctx] = _expressionTypes[childExpr]!;
      }
      return;
    }

    // Process assignments with '='
    final lhs = ctx.logicOr()!; // left-hand side
    final rhs = ctx.assignment()!; // right-hand side

    // Ensure LHS is a valid variable
    if (!_isVariable(lhs)) {
      errors.add("Error: Left-hand side must be a variable");
      return;
    }

    // Extract the variable name from the LHS parse subtree
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
      // Expression type couldn't be determined; likely a previous error.
      return;
    }

    // Check type compatibility (allow assigning int -> float)
    if (varType != exprType &&
        !(varType == VarType.floatType && exprType == VarType.intType)) {
      errors.add("Error: Type mismatch for '$varName'");
    }

    // Propagate the type of the assignment (which is the type of the LHS)
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

    // Multiple operands with logical OR
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

    // Multiple operands with logical AND
    bool allBool = true;
    for (var equality in equalities) {
      final operandType = _expressionTypes[equality];
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

  /* ----------------------------------------------------------------------
   *  7. Control Structures (if / while / read)
   * -------------------------------------------------------------------- */
  @override
  void exitIfStmt(IfStmtContext ctx) {
    final condExpr = ctx.expression();
    if (condExpr == null) return;

    // First make sure we propagate the type from the expression
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

    // First make sure we propagate the type from the expression
    exitExpression(condExpr);

    final condType = _expressionTypes[condExpr];
    if (condType != VarType.boolType) {
      errors.add("Error: 'while' condition must be boolean.");
    }
  }

  // Helper method to ensure expression types are propagated
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
    for (var varCtx in vars) {
      final varName = varCtx.text;
      if (!symbolTable.containsKey(varName)) {
        errors.add("Error: Variable '$varName' is not declared.");
      }
    }
  }

  @override
  void exitFwriteStmt(FwriteStmtContext ctx) {
    final exprList = ctx.exprList();
    if (exprList == null || exprList.expressions().isEmpty) {
      errors.add("Error: fwrite requires at least one argument.");
      return;
    }

    final firstExpr = exprList.expression(0);
    if (firstExpr == null) return;

    // Make sure we have the type correctly
    exitExpression(firstExpr);

    final fileExprType = _expressionTypes[firstExpr];
    if (fileExprType != VarType.fileType) {
      errors.add("Error: The first argument of fwrite must be of type file.");
    }
  }

  /* ----------------------------------------------------------------------
   *  8. Helper Methods
   * -------------------------------------------------------------------- */
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
        return VarType.intType; // fallback
    }
  }

  bool _isNumeric(VarType? type) =>
      type == VarType.intType || type == VarType.floatType;

  /// Returns true if the parse subtree eventually leads to a primary
  /// with an Identifier, i.e., a simple variable reference.
  bool _isVariable(ParserRuleContext ctx) {
    final primaryCtx = _getPrimary(ctx);
    if (primaryCtx == null) return false;
    return primaryCtx.Identifier() != null;
  }

  /// Recursively find the underlying PrimaryContext within an expression parse tree.
  MyLangParser.PrimaryContext? _getPrimary(ParserRuleContext ctx) {
    if (ctx is MyLangParser.PrimaryContext) {
      return ctx;
    }
    // Check children one by one. We'll return the first PrimaryContext we find.
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
