// Generated from /Users/michalrucka/Desktop/VSB/6_semester/PJP/project/lib/MyLang.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link MyLangParser}.
 */
public interface MyLangListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link MyLangParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(MyLangParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(MyLangParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by the {@code emptyStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatement(MyLangParser.EmptyStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code emptyStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatement(MyLangParser.EmptyStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code declarationStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterDeclarationStatement(MyLangParser.DeclarationStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code declarationStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitDeclarationStatement(MyLangParser.DeclarationStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code readStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterReadStatement(MyLangParser.ReadStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code readStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitReadStatement(MyLangParser.ReadStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code writeStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterWriteStatement(MyLangParser.WriteStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code writeStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitWriteStatement(MyLangParser.WriteStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code fwriteStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterFwriteStatement(MyLangParser.FwriteStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code fwriteStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitFwriteStatement(MyLangParser.FwriteStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ifStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(MyLangParser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ifStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(MyLangParser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code whileStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(MyLangParser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code whileStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(MyLangParser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code blockStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterBlockStatement(MyLangParser.BlockStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code blockStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitBlockStatement(MyLangParser.BlockStatementContext ctx);
	/**
	 * Enter a parse tree produced by the {@code expressionStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterExpressionStatement(MyLangParser.ExpressionStatementContext ctx);
	/**
	 * Exit a parse tree produced by the {@code expressionStatement}
	 * labeled alternative in {@link MyLangParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitExpressionStatement(MyLangParser.ExpressionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#declarationStmt}.
	 * @param ctx the parse tree
	 */
	void enterDeclarationStmt(MyLangParser.DeclarationStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#declarationStmt}.
	 * @param ctx the parse tree
	 */
	void exitDeclarationStmt(MyLangParser.DeclarationStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#variableList}.
	 * @param ctx the parse tree
	 */
	void enterVariableList(MyLangParser.VariableListContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#variableList}.
	 * @param ctx the parse tree
	 */
	void exitVariableList(MyLangParser.VariableListContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#readStmt}.
	 * @param ctx the parse tree
	 */
	void enterReadStmt(MyLangParser.ReadStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#readStmt}.
	 * @param ctx the parse tree
	 */
	void exitReadStmt(MyLangParser.ReadStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#writeStmt}.
	 * @param ctx the parse tree
	 */
	void enterWriteStmt(MyLangParser.WriteStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#writeStmt}.
	 * @param ctx the parse tree
	 */
	void exitWriteStmt(MyLangParser.WriteStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#fwriteStmt}.
	 * @param ctx the parse tree
	 */
	void enterFwriteStmt(MyLangParser.FwriteStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#fwriteStmt}.
	 * @param ctx the parse tree
	 */
	void exitFwriteStmt(MyLangParser.FwriteStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void enterIfStmt(MyLangParser.IfStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void exitIfStmt(MyLangParser.IfStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void enterWhileStmt(MyLangParser.WhileStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void exitWhileStmt(MyLangParser.WhileStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#blockStmt}.
	 * @param ctx the parse tree
	 */
	void enterBlockStmt(MyLangParser.BlockStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#blockStmt}.
	 * @param ctx the parse tree
	 */
	void exitBlockStmt(MyLangParser.BlockStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#exprStmt}.
	 * @param ctx the parse tree
	 */
	void enterExprStmt(MyLangParser.ExprStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#exprStmt}.
	 * @param ctx the parse tree
	 */
	void exitExprStmt(MyLangParser.ExprStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#exprList}.
	 * @param ctx the parse tree
	 */
	void enterExprList(MyLangParser.ExprListContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#exprList}.
	 * @param ctx the parse tree
	 */
	void exitExprList(MyLangParser.ExprListContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(MyLangParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(MyLangParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterAssignment(MyLangParser.AssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitAssignment(MyLangParser.AssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#logicOr}.
	 * @param ctx the parse tree
	 */
	void enterLogicOr(MyLangParser.LogicOrContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#logicOr}.
	 * @param ctx the parse tree
	 */
	void exitLogicOr(MyLangParser.LogicOrContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#logicAnd}.
	 * @param ctx the parse tree
	 */
	void enterLogicAnd(MyLangParser.LogicAndContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#logicAnd}.
	 * @param ctx the parse tree
	 */
	void exitLogicAnd(MyLangParser.LogicAndContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#equality}.
	 * @param ctx the parse tree
	 */
	void enterEquality(MyLangParser.EqualityContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#equality}.
	 * @param ctx the parse tree
	 */
	void exitEquality(MyLangParser.EqualityContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#relational}.
	 * @param ctx the parse tree
	 */
	void enterRelational(MyLangParser.RelationalContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#relational}.
	 * @param ctx the parse tree
	 */
	void exitRelational(MyLangParser.RelationalContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#additive}.
	 * @param ctx the parse tree
	 */
	void enterAdditive(MyLangParser.AdditiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#additive}.
	 * @param ctx the parse tree
	 */
	void exitAdditive(MyLangParser.AdditiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#multiplicative}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicative(MyLangParser.MultiplicativeContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#multiplicative}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicative(MyLangParser.MultiplicativeContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#unary}.
	 * @param ctx the parse tree
	 */
	void enterUnary(MyLangParser.UnaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#unary}.
	 * @param ctx the parse tree
	 */
	void exitUnary(MyLangParser.UnaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#primary}.
	 * @param ctx the parse tree
	 */
	void enterPrimary(MyLangParser.PrimaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#primary}.
	 * @param ctx the parse tree
	 */
	void exitPrimary(MyLangParser.PrimaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link MyLangParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(MyLangParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link MyLangParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(MyLangParser.TypeContext ctx);
}