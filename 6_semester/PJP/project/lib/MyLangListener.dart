// Generated from MyLang.g4 by ANTLR 4.13.1
// ignore_for_file: unused_import, unused_local_variable, prefer_single_quotes
import 'package:antlr4/antlr4.dart';

import 'MyLangParser.dart';

/// This abstract class defines a complete listener for a parse tree produced by
/// [MyLangParser].
abstract class MyLangListener extends ParseTreeListener {
  /// Enter a parse tree produced by [MyLangParser.program].
  /// [ctx] the parse tree
  void enterProgram(ProgramContext ctx);
  /// Exit a parse tree produced by [MyLangParser.program].
  /// [ctx] the parse tree
  void exitProgram(ProgramContext ctx);

  /// Enter a parse tree produced by the [emptyStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterEmptyStatement(EmptyStatementContext ctx);
  /// Exit a parse tree produced by the [emptyStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitEmptyStatement(EmptyStatementContext ctx);

  /// Enter a parse tree produced by the [declarationStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterDeclarationStatement(DeclarationStatementContext ctx);
  /// Exit a parse tree produced by the [declarationStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitDeclarationStatement(DeclarationStatementContext ctx);

  /// Enter a parse tree produced by the [readStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterReadStatement(ReadStatementContext ctx);
  /// Exit a parse tree produced by the [readStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitReadStatement(ReadStatementContext ctx);

  /// Enter a parse tree produced by the [writeStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterWriteStatement(WriteStatementContext ctx);
  /// Exit a parse tree produced by the [writeStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitWriteStatement(WriteStatementContext ctx);

  /// Enter a parse tree produced by the [fwriteStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterFwriteStatement(FwriteStatementContext ctx);
  /// Exit a parse tree produced by the [fwriteStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitFwriteStatement(FwriteStatementContext ctx);

  /// Enter a parse tree produced by the [ifStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterIfStatement(IfStatementContext ctx);
  /// Exit a parse tree produced by the [ifStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitIfStatement(IfStatementContext ctx);

  /// Enter a parse tree produced by the [whileStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterWhileStatement(WhileStatementContext ctx);
  /// Exit a parse tree produced by the [whileStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitWhileStatement(WhileStatementContext ctx);

  /// Enter a parse tree produced by the [blockStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterBlockStatement(BlockStatementContext ctx);
  /// Exit a parse tree produced by the [blockStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitBlockStatement(BlockStatementContext ctx);

  /// Enter a parse tree produced by the [expressionStatement]
  /// labeled alternative in [file.parserName>.statement].
  /// [ctx] the parse tree
  void enterExpressionStatement(ExpressionStatementContext ctx);
  /// Exit a parse tree produced by the [expressionStatement]
  /// labeled alternative in [MyLangParser.statement].
  /// [ctx] the parse tree
  void exitExpressionStatement(ExpressionStatementContext ctx);

  /// Enter a parse tree produced by [MyLangParser.declarationStmt].
  /// [ctx] the parse tree
  void enterDeclarationStmt(DeclarationStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.declarationStmt].
  /// [ctx] the parse tree
  void exitDeclarationStmt(DeclarationStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.variableList].
  /// [ctx] the parse tree
  void enterVariableList(VariableListContext ctx);
  /// Exit a parse tree produced by [MyLangParser.variableList].
  /// [ctx] the parse tree
  void exitVariableList(VariableListContext ctx);

  /// Enter a parse tree produced by [MyLangParser.readStmt].
  /// [ctx] the parse tree
  void enterReadStmt(ReadStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.readStmt].
  /// [ctx] the parse tree
  void exitReadStmt(ReadStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.writeStmt].
  /// [ctx] the parse tree
  void enterWriteStmt(WriteStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.writeStmt].
  /// [ctx] the parse tree
  void exitWriteStmt(WriteStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.fwriteStmt].
  /// [ctx] the parse tree
  void enterFwriteStmt(FwriteStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.fwriteStmt].
  /// [ctx] the parse tree
  void exitFwriteStmt(FwriteStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.ifStmt].
  /// [ctx] the parse tree
  void enterIfStmt(IfStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.ifStmt].
  /// [ctx] the parse tree
  void exitIfStmt(IfStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.whileStmt].
  /// [ctx] the parse tree
  void enterWhileStmt(WhileStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.whileStmt].
  /// [ctx] the parse tree
  void exitWhileStmt(WhileStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.blockStmt].
  /// [ctx] the parse tree
  void enterBlockStmt(BlockStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.blockStmt].
  /// [ctx] the parse tree
  void exitBlockStmt(BlockStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.exprStmt].
  /// [ctx] the parse tree
  void enterExprStmt(ExprStmtContext ctx);
  /// Exit a parse tree produced by [MyLangParser.exprStmt].
  /// [ctx] the parse tree
  void exitExprStmt(ExprStmtContext ctx);

  /// Enter a parse tree produced by [MyLangParser.exprList].
  /// [ctx] the parse tree
  void enterExprList(ExprListContext ctx);
  /// Exit a parse tree produced by [MyLangParser.exprList].
  /// [ctx] the parse tree
  void exitExprList(ExprListContext ctx);

  /// Enter a parse tree produced by [MyLangParser.expression].
  /// [ctx] the parse tree
  void enterExpression(ExpressionContext ctx);
  /// Exit a parse tree produced by [MyLangParser.expression].
  /// [ctx] the parse tree
  void exitExpression(ExpressionContext ctx);

  /// Enter a parse tree produced by [MyLangParser.assignment].
  /// [ctx] the parse tree
  void enterAssignment(AssignmentContext ctx);
  /// Exit a parse tree produced by [MyLangParser.assignment].
  /// [ctx] the parse tree
  void exitAssignment(AssignmentContext ctx);

  /// Enter a parse tree produced by [MyLangParser.logicOr].
  /// [ctx] the parse tree
  void enterLogicOr(LogicOrContext ctx);
  /// Exit a parse tree produced by [MyLangParser.logicOr].
  /// [ctx] the parse tree
  void exitLogicOr(LogicOrContext ctx);

  /// Enter a parse tree produced by [MyLangParser.logicAnd].
  /// [ctx] the parse tree
  void enterLogicAnd(LogicAndContext ctx);
  /// Exit a parse tree produced by [MyLangParser.logicAnd].
  /// [ctx] the parse tree
  void exitLogicAnd(LogicAndContext ctx);

  /// Enter a parse tree produced by [MyLangParser.equality].
  /// [ctx] the parse tree
  void enterEquality(EqualityContext ctx);
  /// Exit a parse tree produced by [MyLangParser.equality].
  /// [ctx] the parse tree
  void exitEquality(EqualityContext ctx);

  /// Enter a parse tree produced by [MyLangParser.relational].
  /// [ctx] the parse tree
  void enterRelational(RelationalContext ctx);
  /// Exit a parse tree produced by [MyLangParser.relational].
  /// [ctx] the parse tree
  void exitRelational(RelationalContext ctx);

  /// Enter a parse tree produced by [MyLangParser.additive].
  /// [ctx] the parse tree
  void enterAdditive(AdditiveContext ctx);
  /// Exit a parse tree produced by [MyLangParser.additive].
  /// [ctx] the parse tree
  void exitAdditive(AdditiveContext ctx);

  /// Enter a parse tree produced by [MyLangParser.multiplicative].
  /// [ctx] the parse tree
  void enterMultiplicative(MultiplicativeContext ctx);
  /// Exit a parse tree produced by [MyLangParser.multiplicative].
  /// [ctx] the parse tree
  void exitMultiplicative(MultiplicativeContext ctx);

  /// Enter a parse tree produced by [MyLangParser.unary].
  /// [ctx] the parse tree
  void enterUnary(UnaryContext ctx);
  /// Exit a parse tree produced by [MyLangParser.unary].
  /// [ctx] the parse tree
  void exitUnary(UnaryContext ctx);

  /// Enter a parse tree produced by [MyLangParser.primary].
  /// [ctx] the parse tree
  void enterPrimary(PrimaryContext ctx);
  /// Exit a parse tree produced by [MyLangParser.primary].
  /// [ctx] the parse tree
  void exitPrimary(PrimaryContext ctx);

  /// Enter a parse tree produced by [MyLangParser.type].
  /// [ctx] the parse tree
  void enterType(TypeContext ctx);
  /// Exit a parse tree produced by [MyLangParser.type].
  /// [ctx] the parse tree
  void exitType(TypeContext ctx);
}