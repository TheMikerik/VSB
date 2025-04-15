// Generated from MyLang.g4 by ANTLR 4.13.1
// ignore_for_file: unused_import, unused_local_variable, prefer_single_quotes
import 'package:antlr4/antlr4.dart';

import 'MyLangParser.dart';

/// This abstract class defines a complete generic visitor for a parse tree
/// produced by [MyLangParser].
///
/// [T] is the eturn type of the visit operation. Use `void` for
/// operations with no return type.
abstract class MyLangVisitor<T> extends ParseTreeVisitor<T> {
  /// Visit a parse tree produced by [MyLangParser.program].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitProgram(ProgramContext ctx);

  /// Visit a parse tree produced by the {@code emptyStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitEmptyStatement(EmptyStatementContext ctx);

  /// Visit a parse tree produced by the {@code declarationStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitDeclarationStatement(DeclarationStatementContext ctx);

  /// Visit a parse tree produced by the {@code readStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitReadStatement(ReadStatementContext ctx);

  /// Visit a parse tree produced by the {@code writeStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitWriteStatement(WriteStatementContext ctx);

  /// Visit a parse tree produced by the {@code fwriteStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitFwriteStatement(FwriteStatementContext ctx);

  /// Visit a parse tree produced by the {@code ifStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitIfStatement(IfStatementContext ctx);

  /// Visit a parse tree produced by the {@code whileStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitWhileStatement(WhileStatementContext ctx);

  /// Visit a parse tree produced by the {@code blockStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitBlockStatement(BlockStatementContext ctx);

  /// Visit a parse tree produced by the {@code expressionStatement}
  /// labeled alternative in {@link MyLangParser#statement}.
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitExpressionStatement(ExpressionStatementContext ctx);

  /// Visit a parse tree produced by [MyLangParser.declarationStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitDeclarationStmt(DeclarationStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.variableList].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitVariableList(VariableListContext ctx);

  /// Visit a parse tree produced by [MyLangParser.readStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitReadStmt(ReadStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.writeStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitWriteStmt(WriteStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.fwriteStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitFwriteStmt(FwriteStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.ifStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitIfStmt(IfStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.whileStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitWhileStmt(WhileStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.blockStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitBlockStmt(BlockStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.exprStmt].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitExprStmt(ExprStmtContext ctx);

  /// Visit a parse tree produced by [MyLangParser.exprList].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitExprList(ExprListContext ctx);

  /// Visit a parse tree produced by [MyLangParser.expression].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitExpression(ExpressionContext ctx);

  /// Visit a parse tree produced by [MyLangParser.assignment].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitAssignment(AssignmentContext ctx);

  /// Visit a parse tree produced by [MyLangParser.logicOr].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitLogicOr(LogicOrContext ctx);

  /// Visit a parse tree produced by [MyLangParser.logicAnd].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitLogicAnd(LogicAndContext ctx);

  /// Visit a parse tree produced by [MyLangParser.equality].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitEquality(EqualityContext ctx);

  /// Visit a parse tree produced by [MyLangParser.relational].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitRelational(RelationalContext ctx);

  /// Visit a parse tree produced by [MyLangParser.additive].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitAdditive(AdditiveContext ctx);

  /// Visit a parse tree produced by [MyLangParser.multiplicative].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitMultiplicative(MultiplicativeContext ctx);

  /// Visit a parse tree produced by [MyLangParser.unary].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitUnary(UnaryContext ctx);

  /// Visit a parse tree produced by [MyLangParser.primary].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitPrimary(PrimaryContext ctx);

  /// Visit a parse tree produced by [MyLangParser.type].
  /// [ctx] the parse tree.
  /// Return the visitor result.
  T? visitType(TypeContext ctx);
}