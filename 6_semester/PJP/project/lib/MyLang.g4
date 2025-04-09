grammar MyLang;
program: statement* EOF;
statement
    : ';'                               # emptyStatement
    | declarationStmt                   # declarationStatement
    | readStmt                          # readStatement
    | writeStmt                         # writeStatement
    | ifStmt                            # ifStatement
    | whileStmt                         # whileStatement
    | blockStmt                         # blockStatement
    | exprStmt                          # expressionStatement
    ;
    
declarationStmt: type variableList ';';
variableList: Identifier (',' Identifier)*;
readStmt: 'read' variableList ';';
writeStmt: 'write' exprList ';';
ifStmt: 'if' '(' expression ')' statement ('else' statement)?;
whileStmt: 'while' '(' expression ')' statement;
blockStmt: '{' statement* '}';
exprStmt: expression ';';
exprList: expression (',' expression)*;
expression: assignment;

assignment: logicOr ( '=' assignment )?;
logicOr: logicAnd ( '||' logicAnd )*;
logicAnd: equality ( '&&' equality )*;
equality: relational ( ( '==' | '!=' ) relational )*;
relational: additive ( ( '<' | '>' ) additive )*;
additive: multiplicative ( ( '+' | '-' | '.' ) multiplicative )*;
multiplicative: unary ( ( '*' | '/' | '%' ) unary )*;
unary: ( '!' | '-' ) unary
     | primary
     ;
primary
    : IntegerLiteral
    | FloatLiteral
    | BooleanLiteral
    | StringLiteral
    | FileLiteral
    | Identifier
    | '(' expression ')'
    ;
type: 'int' | 'float' | 'bool' | 'string' | 'FILE';
BooleanLiteral: 'true' | 'false';
IntegerLiteral: [0-9]+;
FloatLiteral: [0-9]+'.'[0-9]+;
StringLiteral: '"' (~["\r\n])* '"';
FileLiteral: StringLiteral;
Identifier: [a-zA-Z] [a-zA-Z0-9]*;
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
