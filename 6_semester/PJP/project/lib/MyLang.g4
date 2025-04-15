grammar MyLang;

// The entry point for the parser.
program: statement* EOF;

// Different types of statements.
statement
    : ';'                               # emptyStatement
    | declarationStmt                   # declarationStatement
    | readStmt                          # readStatement
    | writeStmt                         # writeStatement
    | fwriteStmt                        # fwriteStatement 
    | ifStmt                            # ifStatement
    | whileStmt                         # whileStatement
    | blockStmt                         # blockStatement
    | exprStmt                          # expressionStatement
    ;

// Declaration of variables with a common type.
declarationStmt: type variableList ';';

// List of variable identifiers separated by commas.
variableList: Identifier (',' Identifier)*;

// Read and write statements.
readStmt: 'read' variableList ';';
writeStmt: 'write' exprList ';';
fwriteStmt: 'fwrite' exprList ';';

// Conditional and loop statements.
ifStmt: 'if' '(' expression ')' statement ('else' statement)?;
whileStmt: 'while' '(' expression ')' statement;

// Block of statements.
blockStmt: '{' statement* '}';

// Expression as a statement.
exprStmt: expression ';';

// A list of expressions (for the write statement).
exprList: expression (',' expression)*;

// Expression rules, starting with assignment which is right-associative.
expression: assignment;

assignment: logicOr ( '=' assignment )?;

// Logical OR expression.
logicOr: logicAnd ( '||' logicAnd )*;

// Logical AND expression.
logicAnd: equality ( '&&' equality )*;

// Equality expressions.
equality: relational ( ( '==' | '!=' ) relational )*;

// Relational expressions.
relational: additive ( ( '<' | '>' ) additive )*;

// Additive expressions (including string concatenation with '.').
additive: multiplicative ( ( '+' | '-' | '.' ) multiplicative )*;

// Multiplicative expressions.
multiplicative: unary ( ( '*' | '/' | '%' ) unary )*;

// Unary operators: logical NOT and unary minus.
unary: ( '!' | '-' ) unary
     | primary
     ;

// Primary expressions include literals, identifiers, and parenthesized expressions.
primary
    : IntegerLiteral
    | FloatLiteral
    | BooleanLiteral
    | StringLiteral
    | FileLiteral
    | Identifier
    | '(' expression ')'
    ;

// Type keywords.
type: 'int' | 'float' | 'bool' | 'string' | 'file';

// Literals.
BooleanLiteral: 'true' | 'false';
IntegerLiteral: [0-9]+;
FloatLiteral: [0-9]+'.'[0-9]+;
StringLiteral: '"' (~["\r\n])* '"';
FileLiteral: StringLiteral;

// Identifier: starts with a letter and followed by letters or digits.
Identifier: [a-zA-Z] [a-zA-Z0-9]*;

// Skip whitespace and comments.
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
