grammar MyLang;

/
program: statement* EOF;

statement
    : ';'                               # emptyStatement
    | declarationStmt                   # declarationStatement
    | readStmt                          # readStatement
    | writeStmt                         # writeStatement
    | ifStmt                            # ifStatement
    | whileStmt                         # whileStatement
    | blockStmt                         # blockStatement
    | fopenStmt                         # fopenStatement
    | exprStmt                          # expressionStatement
    ;

declarationStmt: type variableList ';';
fopenStmt: 'fopen' Identifier STRING ';';
readStmt: 'read' variableList ';';
writeStmt: 'write' exprList ';';
ifStmt: 'if' '(' expression ')' statement ('else' statement)?;
whileStmt: 'while' '(' expression ')' statement;
blockStmt: '{' statement* '}';
exprStmt: expression ';';

variableList: Identifier (',' Identifier)*;
exprList: expression (',' expression)*;
expression: assignment;
assignment: logicOr ( '=' assignment )?;
logicOr: logicAnd ( '||' logicAnd )*;
logicAnd: equality ( '&&' equality )*;
equality: relational ( ( '==' | '!=' ) relational )*;
relational: additive ( ( '<' | '>' ) additive )*;
additive: multiplicative ( ( '+' | '-' | '.' ) multiplicative )*;
multiplicative: appendExpr ( ( '*' | '/' | '%' ) appendExpr )*;
appendExpr: unary ('<<' unary)*;

unary: ( '!' | '-' ) unary
     | primary
     ;

primary
    : INT
    | FLOAT
    | BOOL
    | STRING
    | FILE
    | Identifier
    | '(' expression ')'
    ;

type: 'int' | 'float' | 'bool' | 'string' | 'file';

BOOL: 'true' | 'false';
INT: [0-9]+;
FLOAT: [0-9]+'.'[0-9]+;
STRING: '"' (~["\r\n])* '"';
FILE: STRING;

Identifier: [a-zA-Z] [a-zA-Z0-9]*;

WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
