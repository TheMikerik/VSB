import 'package:antlr4/antlr4.dart';
import 'MyLangParser.dart';
// Change the import if your visitor base class name is different
// Usually it's generated as MyLangVisitor or MyLangBaseVisitor
import 'MyLangBaseVisitor.dart'; // Make sure this import is correct

// Define VarType enum here or import it if it's in a separate file
enum VarType { intType, floatType, boolType, stringType, fileType }

// Extend the generated BaseVisitor class
class CodeGenerator extends MyLangBaseVisitor<void> {
  final StringBuffer _output = StringBuffer();
  // Keep track of declared variables and their types during generation
  final Map<String, VarType> _symbolTable = {};
  int _labelCounter = 0;

  // Helper to store the deduced type of the most recently visited expression
  // We need this because the visitor doesn't automatically propagate types like the listener example tried to.
  // You might need a more robust way (like re-running type analysis or storing types more globally)
  // For simplicity here, we'll try to deduce on the fly or assume correctness based on type checking phase.
  VarType? _lastExpressionType;

  String generate(ProgramContext programCtx) {
    _output.clear();
    visit(programCtx); // Start visiting from the root
    return _output.toString();
  }

  // Helper to generate unique label numbers
  int _nextLabel() => _labelCounter++;

  // Helper to convert our VarType to instruction type signature
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
      // Decide how to handle file type in instructions. Often treated as string path.
      case VarType.fileType:
        return 'S';
    }
  }

  // Helper to convert string type to VarType
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
        return VarType.intType; // fallback, should not happen after type check
    }
  }

  bool _isNumeric(VarType? type) =>
      type == VarType.intType || type == VarType.floatType;

  // --- Visitor Methods (Replaced exit... methods) ---

  @override
  void visitProgram(ProgramContext ctx) {
    // Visit all statements in the program
    ctx.statements().forEach(visit);
  }

  // STATEMENTS

  @override
  void visitEmptyStatement(EmptyStatementContext ctx) {
    // Do nothing for empty statements
  }

  @override
  void visitDeclarationStatement(DeclarationStatementContext ctx) {
    visit(ctx.declarationStmt() as ParseTree);
  }

  @override
  void visitDeclarationStmt(DeclarationStmtContext ctx) {
    final typeStr = ctx.type()?.text;
    final declaredType = _stringToType(typeStr!);

    final identifiers = ctx.variableList()!.Identifiers();
    for (var id in identifiers) {
      final varName = id.text;
      // Store type for later use (e.g., in load/save, expression type checking)
      _symbolTable[varName!] = declaredType;

      // Initialize with default value
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
          break; // Initialize files as empty strings?
      }
      _output.writeln('save $varName');
      // Don't need pop here, declaration doesn't leave value on stack
    }
  }

  @override
  void visitReadStatement(ReadStatementContext ctx) {
    visit(ctx.readStmt() as ParseTree);
  }

  @override
  void visitReadStmt(ReadStmtContext ctx) {
    final identifiers = ctx.variableList()!.Identifiers();
    for (var id in identifiers) {
      final varName = id.text;
      final varType = _symbolTable[varName]; // Assume type checker passed
      if (varType != null) {
        final typeChar = _typeToInstructionType(varType);
        _output.writeln('read $typeChar');
        _output.writeln('save $varName');
      } else {
        // Should not happen after type checking
        _output.writeln('// ERROR: Undeclared variable $varName in read');
      }
    }
  }

  @override
  void visitWriteStatement(WriteStatementContext ctx) {
    visit(ctx.writeStmt() as ParseTree);
  }

  @override
  void visitWriteStmt(WriteStmtContext ctx) {
    final expressions = ctx.exprList()!.expressions();
    for (var expr in expressions) {
      visit(expr); // Visit each expression to generate its code
    }
    _output.writeln('print ${expressions.length}');
  }

  // Fwrite statement - adapt as needed for file handling semantics
  @override
  void visitFwriteStatement(FwriteStatementContext ctx) {
    visit(ctx.fwriteStmt() as ParseTree);
  }

  @override
  void visitFwriteStmt(FwriteStmtContext ctx) {
    // Example: Assuming first expr is file path (string), rest are data
    final expressions = ctx.exprList()!.expressions();
    if (expressions.isNotEmpty) {
      // Visit file path expression
      visit(expressions[0]);
      // Visit data expressions
      for (int i = 1; i < expressions.length; i++) {
        visit(expressions[i]);
      }
      // Placeholder for actual file write instruction
      _output.writeln('// FWRITE operation with ${expressions.length} args');
      // Example instruction (you need to define FWRITE in interpreter)
      // _output.writeln('fwrite ${expressions.length - 1}'); // Num data items
    }
    // Clean up stack if fwrite doesn't consume args
    // for (int i = 0; i < expressions.length; i++) {
    //   _output.writeln('pop');
    // }
  }

  @override
  void visitIfStatement(IfStatementContext ctx) {
    visit(ctx.ifStmt() as ParseTree);
  }

  @override
  void visitIfStmt(IfStmtContext ctx) {
    final elseStmt = ctx.statement(1);
    final elseLabel = _nextLabel();
    final endLabel =
        (elseStmt != null)
            ? _nextLabel()
            : _nextLabel(); // Always create endLabel
    visit(ctx.expression() as ParseTree);
    _output.writeln('fjmp $elseLabel');
    visit(ctx.statement(0)!);
    _output.writeln('jmp $endLabel'); // Add even if no else
    _output.writeln('label $elseLabel');
    if (elseStmt != null) {
      visit(elseStmt);
    }
    _output.writeln('label $endLabel'); // Always add end label
  }

  @override
  void visitWhileStatement(WhileStatementContext ctx) {
    visit(ctx.whileStmt() as ParseTree);
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
  void visitBlockStatement(BlockStatementContext ctx) {
    visit(ctx.blockStmt() as ParseTree);
  }

  @override
  void visitBlockStmt(BlockStmtContext ctx) {
    // Visit each statement within the block
    ctx.statements().forEach(visit);
  }

  @override
  void visitExpressionStatement(ExpressionStatementContext ctx) {
    visit(ctx.exprStmt() as ParseTree);
  }

  @override
  void visitExprStmt(ExprStmtContext ctx) {
    // Visit the expression to generate its code
    visit(ctx.expression() as ParseTree);
    // Expression statements discard the result
    _output.writeln('pop');
  }

  // EXPRESSIONS (Order matters!)

  @override
  void visitExpression(ExpressionContext ctx) {
    // The top-level expression rule just delegates
    visit(ctx.assignment() as ParseTree);
  }

  // @override
  // void visitAssignment(AssignmentContext ctx) {
  //   // Assignment is right-associative: =
  //   // logicOr ( = assignment )?
  //   if (ctx.assignment() != null) {
  //     // This is an assignment: IDENTIFIER = expression
  //     final lhs = ctx.logicOr()!;
  //     final rhs = ctx.assignment()!;

  //     // Find the variable name on the LHS (must be an identifier)
  //     String? varName;
  //     ParserRuleContext? current = lhs;
  //     while (varName == null && current != null) {
  //       if (current is PrimaryContext && current.Identifier() != null) {
  //         varName = current.Identifier()!.text;
  //       } else if (current.childCount == 1 &&
  //           current.getChild(0) is ParserRuleContext) {
  //         current = current.getChild(0) as ParserRuleContext?;
  //       } else {
  //         // This shouldn't happen if type checking passed LHS validation
  //         break;
  //       }
  //     }

  //     if (varName != null) {
  //       final varType = _symbolTable[varName]; // Get variable's declared type

  //       // 1. Visit the right-hand side expression FIRST
  //       visit(rhs); // Leaves the value on the stack

  //       // 2. Check for implicit int-to-float conversion
  //       final rhsType = _lastExpressionType; // Type of value computed by RHS
  //       if (varType == VarType.floatType && rhsType == VarType.intType) {
  //         _output.writeln('itof'); // Convert value on stack to float
  //       }
  //       // Type checking should prevent float -> int assignment attempt

  //       // --- START CHANGE ---
  //       // 3. Save the value directly
  //       _output.writeln('save $varName'); // Save the value from the stack

  //       // 4. Load the saved value back onto the stack
  //       //    (Assignments evaluate to the assigned value)
  //       _output.writeln('load $varName');
  //       // --- END CHANGE ---

  //       _lastExpressionType =
  //           varType; // Assignment result type is variable's type
  //     } else {
  //       _output.writeln("// ERROR: Invalid LHS in assignment");
  //       // Still visit RHS to potentially catch errors there
  //       visit(rhs);
  //       // Let the parent ExprStmt handle popping the RHS value if needed
  //       // _output.writeln('pop'); // NO pop here
  //       _lastExpressionType = VarType.intType; // Placeholder
  //     }
  //   } else {
  //     // Not an assignment, just visit the logical OR expression
  //     visit(ctx.logicOr() as ParseTree);
  //   }
  // }
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
        visit(rhs); // Compute RHS, leave value on stack
        if (varType == VarType.floatType &&
            _lastExpressionType == VarType.intType) {
          _output.writeln('itof');
        }
        _output.writeln('save $varName'); // Save value to variable
        _output.writeln('load $varName'); // Reload value as expression result
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

  // Helper to get type, needed for binary ops with potential itof
  // NOTE: This relies on _lastExpressionType being set correctly by visiting primaries/sub-expressions
  // A more robust approach involves a dedicated type map populated during a separate pass or integrated visitor
  VarType? _getExprType(ParserRuleContext ctx) {
    // Simple guess based on structure - THIS IS LIMITED
    if (ctx is PrimaryContext) {
      if (ctx.IntegerLiteral() != null) return VarType.intType;
      if (ctx.FloatLiteral() != null) return VarType.floatType;
      if (ctx.BooleanLiteral() != null) return VarType.boolType;
      if (ctx.StringLiteral() != null) return VarType.stringType;
      if (ctx.FileLiteral() != null) return VarType.fileType;
      if (ctx.Identifier() != null) return _symbolTable[ctx.Identifier()!.text];
    }
    // Fallback or requires looking deeper / using a type map
    return _lastExpressionType; // Use the last recorded type as a guess
  }

  // LOGICAL OR || (Left Associative)
  @override
  void visitLogicOr(LogicOrContext ctx) {
    if (ctx.logicAnds().length > 1) {
      visit(ctx.logicAnd(0)!); // Visit first operand
      for (int i = 1; i < ctx.logicAnds().length; i++) {
        // Short circuit might be complex here, basic version:
        visit(ctx.logicAnd(i)!); // Visit next operand
        _output.writeln('or'); // Perform OR (assumes interpreter handles bools)
        _lastExpressionType = VarType.boolType;
      }
    } else {
      visit(ctx.logicAnd(0)!); // Only one operand
    }
  }

  // LOGICAL AND && (Left Associative)
  @override
  void visitLogicAnd(LogicAndContext ctx) {
    if (ctx.equalitys().length > 1) {
      visit(ctx.equality(0)!); // Visit first operand
      for (int i = 1; i < ctx.equalitys().length; i++) {
        // Short circuit might be complex here, basic version:
        visit(ctx.equality(i)!); // Visit next operand
        _output.writeln('and'); // Perform AND
        _lastExpressionType = VarType.boolType;
      }
    } else {
      visit(ctx.equality(0)!); // Only one operand
    }
  }

  // EQUALITY == != (Left Associative)
  @override
  void visitEquality(EqualityContext ctx) {
    if (ctx.relationals().length > 1) {
      visit(ctx.relational(0)!); // Visit left operand
      final leftType = _lastExpressionType; // Type of left operand
      visit(ctx.relational(1)!); // Visit right operand
      final rightType = _lastExpressionType; // Type of right operand

      final op = ctx.getChild(1)!.text; // '==' or '!='

      // Determine comparison type (handle int/float comparison)
      VarType resultType = leftType!;
      if (_isNumeric(leftType) && _isNumeric(rightType)) {
        // Promote to float if either is float
        if (leftType == VarType.floatType || rightType == VarType.floatType) {
          resultType = VarType.floatType; // Operation will be float
          // Add itof if needed (stack: left, right)
          if (rightType == VarType.intType) {
            // Convert right
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
    if (ctx.IntegerLiteral() != null) {
      _output.writeln('push I ${ctx.IntegerLiteral()!.text}');
      _lastExpressionType = VarType.intType;
    } else if (ctx.FloatLiteral() != null) {
      _output.writeln('push F ${ctx.FloatLiteral()!.text}');
      _lastExpressionType = VarType.floatType;
    } else if (ctx.BooleanLiteral() != null) {
      _output.writeln('push B ${ctx.BooleanLiteral()!.text}');
      _lastExpressionType = VarType.boolType;
    } else if (ctx.StringLiteral() != null) {
      final text = ctx.StringLiteral()!.text!;
      final strValue = text
          .substring(1, text.length - 1)
          .replaceAll('""', '"'); // Handle escaped quotes if needed
      _output.writeln(
        'push S "$strValue"',
      ); // Ensure quotes are kept for string instruction
      _lastExpressionType = VarType.stringType;
    } else if (ctx.FileLiteral() != null) {
      final text = ctx.FileLiteral()!.text!;
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
      // _lastExpressionType is set by visiting the inner expression
    }
  }

  // --- Need visit methods for other grammar rules if they weren't covered ---
  // e.g., type, variableList, exprList should be visited implicitly
  // when visiting their parent rules. Add overrides if specific action needed.

  @override
  void visitVariableList(VariableListContext ctx) {
    // Usually don't need specific code here, handled by parent (declaration/read)
    visitChildren(ctx);
  }

  @override
  void visitExprList(ExprListContext ctx) {
    // Usually don't need specific code here, handled by parent (write/fwrite)
    visitChildren(ctx);
  }

  @override
  void visitType(TypeContext ctx) {
    // No code generation needed for the type node itself
  }
}
