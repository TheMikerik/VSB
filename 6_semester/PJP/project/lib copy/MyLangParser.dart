// Generated from MyLang.g4 by ANTLR 4.13.1
// ignore_for_file: unused_import, unused_local_variable, prefer_single_quotes
import 'package:antlr4/antlr4.dart';

import 'MyLangListener.dart';
import 'MyLangBaseListener.dart';
import 'MyLangVisitor.dart';
import 'MyLangBaseVisitor.dart';
const int RULE_program = 0, RULE_statement = 1, RULE_declarationStmt = 2, 
          RULE_fopenStmt = 3, RULE_readStmt = 4, RULE_writeStmt = 5, RULE_fwriteStmt = 6, 
          RULE_ifStmt = 7, RULE_whileStmt = 8, RULE_blockStmt = 9, RULE_exprStmt = 10, 
          RULE_variableList = 11, RULE_exprList = 12, RULE_expression = 13, 
          RULE_assignment = 14, RULE_logicOr = 15, RULE_logicAnd = 16, RULE_equality = 17, 
          RULE_relational = 18, RULE_additive = 19, RULE_multiplicative = 20, 
          RULE_appendExpr = 21, RULE_unary = 22, RULE_primary = 23, RULE_type = 24;
class MyLangParser extends Parser {
  static final checkVersion = () => RuntimeMetaData.checkVersion('4.13.1', RuntimeMetaData.VERSION);
  static const int TOKEN_EOF = IntStream.EOF;

  static final List<DFA> _decisionToDFA = List.generate(
      _ATN.numberOfDecisions, (i) => DFA(_ATN.getDecisionState(i), i));
  static final PredictionContextCache _sharedContextCache = PredictionContextCache();
  static const int TOKEN_T__0 = 1, TOKEN_T__1 = 2, TOKEN_T__2 = 3, TOKEN_T__3 = 4, 
                   TOKEN_T__4 = 5, TOKEN_T__5 = 6, TOKEN_T__6 = 7, TOKEN_T__7 = 8, 
                   TOKEN_T__8 = 9, TOKEN_T__9 = 10, TOKEN_T__10 = 11, TOKEN_T__11 = 12, 
                   TOKEN_T__12 = 13, TOKEN_T__13 = 14, TOKEN_T__14 = 15, 
                   TOKEN_T__15 = 16, TOKEN_T__16 = 17, TOKEN_T__17 = 18, 
                   TOKEN_T__18 = 19, TOKEN_T__19 = 20, TOKEN_T__20 = 21, 
                   TOKEN_T__21 = 22, TOKEN_T__22 = 23, TOKEN_T__23 = 24, 
                   TOKEN_T__24 = 25, TOKEN_T__25 = 26, TOKEN_T__26 = 27, 
                   TOKEN_T__27 = 28, TOKEN_T__28 = 29, TOKEN_T__29 = 30, 
                   TOKEN_T__30 = 31, TOKEN_T__31 = 32, TOKEN_T__32 = 33, 
                   TOKEN_BOOL = 34, TOKEN_INT = 35, TOKEN_FLOAT = 36, TOKEN_STRING = 37, 
                   TOKEN_FILE = 38, TOKEN_Identifier = 39, TOKEN_WS = 40, 
                   TOKEN_COMMENT = 41;

  @override
  final List<String> ruleNames = [
    'program', 'statement', 'declarationStmt', 'fopenStmt', 'readStmt', 
    'writeStmt', 'fwriteStmt', 'ifStmt', 'whileStmt', 'blockStmt', 'exprStmt', 
    'variableList', 'exprList', 'expression', 'assignment', 'logicOr', 'logicAnd', 
    'equality', 'relational', 'additive', 'multiplicative', 'appendExpr', 
    'unary', 'primary', 'type'
  ];

  static final List<String?> _LITERAL_NAMES = [
      null, "';'", "'fopen'", "'read'", "'write'", "'fwrite'", "'if'", "'('", 
      "')'", "'else'", "'while'", "'{'", "'}'", "','", "'='", "'||'", "'&&'", 
      "'=='", "'!='", "'<'", "'>'", "'+'", "'-'", "'.'", "'*'", "'/'", "'%'", 
      "'<<'", "'!'", "'int'", "'float'", "'bool'", "'string'", "'file'"
  ];
  static final List<String?> _SYMBOLIC_NAMES = [
      null, null, null, null, null, null, null, null, null, null, null, 
      null, null, null, null, null, null, null, null, null, null, null, 
      null, null, null, null, null, null, null, null, null, null, null, 
      null, "BOOL", "INT", "FLOAT", "STRING", "FILE", "Identifier", "WS", 
      "COMMENT"
  ];
  static final Vocabulary VOCABULARY = VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

  @override
  Vocabulary get vocabulary {
    return VOCABULARY;
  }

  @override
  String get grammarFileName => 'MyLang.g4';

  @override
  List<int> get serializedATN => _serializedATN;

  @override
  ATN getATN() {
   return _ATN;
  }

  MyLangParser(TokenStream input) : super(input) {
    interpreter = ParserATNSimulator(this, _ATN, _decisionToDFA, _sharedContextCache);
  }

  ProgramContext program() {
    dynamic _localctx = ProgramContext(context, state);
    enterRule(_localctx, 0, RULE_program);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 53;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 1099247389950) != 0)) {
        state = 50;
        statement();
        state = 55;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
      state = 56;
      match(TOKEN_EOF);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  StatementContext statement() {
    dynamic _localctx = StatementContext(context, state);
    enterRule(_localctx, 2, RULE_statement);
    try {
      state = 68;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_T__0:
        _localctx = EmptyStatementContext(_localctx);
        enterOuterAlt(_localctx, 1);
        state = 58;
        match(TOKEN_T__0);
        break;
      case TOKEN_T__28:
      case TOKEN_T__29:
      case TOKEN_T__30:
      case TOKEN_T__31:
      case TOKEN_T__32:
        _localctx = DeclarationStatementContext(_localctx);
        enterOuterAlt(_localctx, 2);
        state = 59;
        declarationStmt();
        break;
      case TOKEN_T__2:
        _localctx = ReadStatementContext(_localctx);
        enterOuterAlt(_localctx, 3);
        state = 60;
        readStmt();
        break;
      case TOKEN_T__3:
        _localctx = WriteStatementContext(_localctx);
        enterOuterAlt(_localctx, 4);
        state = 61;
        writeStmt();
        break;
      case TOKEN_T__4:
        _localctx = FwriteStatementContext(_localctx);
        enterOuterAlt(_localctx, 5);
        state = 62;
        fwriteStmt();
        break;
      case TOKEN_T__5:
        _localctx = IfStatementContext(_localctx);
        enterOuterAlt(_localctx, 6);
        state = 63;
        ifStmt();
        break;
      case TOKEN_T__9:
        _localctx = WhileStatementContext(_localctx);
        enterOuterAlt(_localctx, 7);
        state = 64;
        whileStmt();
        break;
      case TOKEN_T__10:
        _localctx = BlockStatementContext(_localctx);
        enterOuterAlt(_localctx, 8);
        state = 65;
        blockStmt();
        break;
      case TOKEN_T__1:
        _localctx = FopenStatementContext(_localctx);
        enterOuterAlt(_localctx, 9);
        state = 66;
        fopenStmt();
        break;
      case TOKEN_T__6:
      case TOKEN_T__21:
      case TOKEN_T__27:
      case TOKEN_BOOL:
      case TOKEN_INT:
      case TOKEN_FLOAT:
      case TOKEN_STRING:
      case TOKEN_FILE:
      case TOKEN_Identifier:
        _localctx = ExpressionStatementContext(_localctx);
        enterOuterAlt(_localctx, 10);
        state = 67;
        exprStmt();
        break;
      default:
        throw NoViableAltException(this);
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  DeclarationStmtContext declarationStmt() {
    dynamic _localctx = DeclarationStmtContext(context, state);
    enterRule(_localctx, 4, RULE_declarationStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 70;
      type();
      state = 71;
      variableList();
      state = 72;
      match(TOKEN_T__0);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  FopenStmtContext fopenStmt() {
    dynamic _localctx = FopenStmtContext(context, state);
    enterRule(_localctx, 6, RULE_fopenStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 74;
      match(TOKEN_T__1);
      state = 75;
      match(TOKEN_Identifier);
      state = 76;
      match(TOKEN_STRING);
      state = 77;
      match(TOKEN_T__0);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  ReadStmtContext readStmt() {
    dynamic _localctx = ReadStmtContext(context, state);
    enterRule(_localctx, 8, RULE_readStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 79;
      match(TOKEN_T__2);
      state = 80;
      variableList();
      state = 81;
      match(TOKEN_T__0);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  WriteStmtContext writeStmt() {
    dynamic _localctx = WriteStmtContext(context, state);
    enterRule(_localctx, 10, RULE_writeStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 83;
      match(TOKEN_T__3);
      state = 84;
      exprList();
      state = 85;
      match(TOKEN_T__0);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  FwriteStmtContext fwriteStmt() {
    dynamic _localctx = FwriteStmtContext(context, state);
    enterRule(_localctx, 12, RULE_fwriteStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 87;
      match(TOKEN_T__4);
      state = 88;
      exprList();
      state = 89;
      match(TOKEN_T__0);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  IfStmtContext ifStmt() {
    dynamic _localctx = IfStmtContext(context, state);
    enterRule(_localctx, 14, RULE_ifStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 91;
      match(TOKEN_T__5);
      state = 92;
      match(TOKEN_T__6);
      state = 93;
      expression();
      state = 94;
      match(TOKEN_T__7);
      state = 95;
      statement();
      state = 98;
      errorHandler.sync(this);
      switch (interpreter!.adaptivePredict(tokenStream, 2, context)) {
      case 1:
        state = 96;
        match(TOKEN_T__8);
        state = 97;
        statement();
        break;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  WhileStmtContext whileStmt() {
    dynamic _localctx = WhileStmtContext(context, state);
    enterRule(_localctx, 16, RULE_whileStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 100;
      match(TOKEN_T__9);
      state = 101;
      match(TOKEN_T__6);
      state = 102;
      expression();
      state = 103;
      match(TOKEN_T__7);
      state = 104;
      statement();
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  BlockStmtContext blockStmt() {
    dynamic _localctx = BlockStmtContext(context, state);
    enterRule(_localctx, 18, RULE_blockStmt);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 106;
      match(TOKEN_T__10);
      state = 110;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 1099247389950) != 0)) {
        state = 107;
        statement();
        state = 112;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
      state = 113;
      match(TOKEN_T__11);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  ExprStmtContext exprStmt() {
    dynamic _localctx = ExprStmtContext(context, state);
    enterRule(_localctx, 20, RULE_exprStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 115;
      expression();
      state = 116;
      match(TOKEN_T__0);
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  VariableListContext variableList() {
    dynamic _localctx = VariableListContext(context, state);
    enterRule(_localctx, 22, RULE_variableList);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 118;
      match(TOKEN_Identifier);
      state = 123;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__12) {
        state = 119;
        match(TOKEN_T__12);
        state = 120;
        match(TOKEN_Identifier);
        state = 125;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  ExprListContext exprList() {
    dynamic _localctx = ExprListContext(context, state);
    enterRule(_localctx, 24, RULE_exprList);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 126;
      expression();
      state = 131;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__12) {
        state = 127;
        match(TOKEN_T__12);
        state = 128;
        expression();
        state = 133;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  ExpressionContext expression() {
    dynamic _localctx = ExpressionContext(context, state);
    enterRule(_localctx, 26, RULE_expression);
    try {
      enterOuterAlt(_localctx, 1);
      state = 134;
      assignment();
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  AssignmentContext assignment() {
    dynamic _localctx = AssignmentContext(context, state);
    enterRule(_localctx, 28, RULE_assignment);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 136;
      logicOr();
      state = 139;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      if (_la == TOKEN_T__13) {
        state = 137;
        match(TOKEN_T__13);
        state = 138;
        assignment();
      }

    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  LogicOrContext logicOr() {
    dynamic _localctx = LogicOrContext(context, state);
    enterRule(_localctx, 30, RULE_logicOr);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 141;
      logicAnd();
      state = 146;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__14) {
        state = 142;
        match(TOKEN_T__14);
        state = 143;
        logicAnd();
        state = 148;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  LogicAndContext logicAnd() {
    dynamic _localctx = LogicAndContext(context, state);
    enterRule(_localctx, 32, RULE_logicAnd);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 149;
      equality();
      state = 154;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__15) {
        state = 150;
        match(TOKEN_T__15);
        state = 151;
        equality();
        state = 156;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  EqualityContext equality() {
    dynamic _localctx = EqualityContext(context, state);
    enterRule(_localctx, 34, RULE_equality);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 157;
      relational();
      state = 162;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__16 || _la == TOKEN_T__17) {
        state = 158;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__16 || _la == TOKEN_T__17)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 159;
        relational();
        state = 164;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  RelationalContext relational() {
    dynamic _localctx = RelationalContext(context, state);
    enterRule(_localctx, 36, RULE_relational);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 165;
      additive();
      state = 170;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__18 || _la == TOKEN_T__19) {
        state = 166;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__18 || _la == TOKEN_T__19)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 167;
        additive();
        state = 172;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  AdditiveContext additive() {
    dynamic _localctx = AdditiveContext(context, state);
    enterRule(_localctx, 38, RULE_additive);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 173;
      multiplicative();
      state = 178;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 14680064) != 0)) {
        state = 174;
        _la = tokenStream.LA(1)!;
        if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 14680064) != 0))) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 175;
        multiplicative();
        state = 180;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  MultiplicativeContext multiplicative() {
    dynamic _localctx = MultiplicativeContext(context, state);
    enterRule(_localctx, 40, RULE_multiplicative);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 181;
      appendExpr();
      state = 186;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 117440512) != 0)) {
        state = 182;
        _la = tokenStream.LA(1)!;
        if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 117440512) != 0))) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 183;
        appendExpr();
        state = 188;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  AppendExprContext appendExpr() {
    dynamic _localctx = AppendExprContext(context, state);
    enterRule(_localctx, 42, RULE_appendExpr);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 189;
      unary();
      state = 194;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__26) {
        state = 190;
        match(TOKEN_T__26);
        state = 191;
        unary();
        state = 196;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  UnaryContext unary() {
    dynamic _localctx = UnaryContext(context, state);
    enterRule(_localctx, 44, RULE_unary);
    int _la;
    try {
      state = 200;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_T__21:
      case TOKEN_T__27:
        enterOuterAlt(_localctx, 1);
        state = 197;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__21 || _la == TOKEN_T__27)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 198;
        unary();
        break;
      case TOKEN_T__6:
      case TOKEN_BOOL:
      case TOKEN_INT:
      case TOKEN_FLOAT:
      case TOKEN_STRING:
      case TOKEN_FILE:
      case TOKEN_Identifier:
        enterOuterAlt(_localctx, 2);
        state = 199;
        primary();
        break;
      default:
        throw NoViableAltException(this);
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  PrimaryContext primary() {
    dynamic _localctx = PrimaryContext(context, state);
    enterRule(_localctx, 46, RULE_primary);
    try {
      state = 212;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_INT:
        enterOuterAlt(_localctx, 1);
        state = 202;
        match(TOKEN_INT);
        break;
      case TOKEN_FLOAT:
        enterOuterAlt(_localctx, 2);
        state = 203;
        match(TOKEN_FLOAT);
        break;
      case TOKEN_BOOL:
        enterOuterAlt(_localctx, 3);
        state = 204;
        match(TOKEN_BOOL);
        break;
      case TOKEN_STRING:
        enterOuterAlt(_localctx, 4);
        state = 205;
        match(TOKEN_STRING);
        break;
      case TOKEN_FILE:
        enterOuterAlt(_localctx, 5);
        state = 206;
        match(TOKEN_FILE);
        break;
      case TOKEN_Identifier:
        enterOuterAlt(_localctx, 6);
        state = 207;
        match(TOKEN_Identifier);
        break;
      case TOKEN_T__6:
        enterOuterAlt(_localctx, 7);
        state = 208;
        match(TOKEN_T__6);
        state = 209;
        expression();
        state = 210;
        match(TOKEN_T__7);
        break;
      default:
        throw NoViableAltException(this);
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  TypeContext type() {
    dynamic _localctx = TypeContext(context, state);
    enterRule(_localctx, 48, RULE_type);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 214;
      _la = tokenStream.LA(1)!;
      if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 16642998272) != 0))) {
      errorHandler.recoverInline(this);
      } else {
        if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
        errorHandler.reportMatch(this);
        consume();
      }
    } on RecognitionException catch (re) {
      _localctx.exception = re;
      errorHandler.reportError(this, re);
      errorHandler.recover(this, re);
    } finally {
      exitRule();
    }
    return _localctx;
  }

  static const List<int> _serializedATN = [
      4,1,41,217,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,
      2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,
      14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,
      2,21,7,21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,5,0,52,8,0,10,0,12,0,55,
      9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,69,8,1,1,2,
      1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,
      6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,99,8,7,1,8,1,8,1,8,1,
      8,1,8,1,8,1,9,1,9,5,9,109,8,9,10,9,12,9,112,9,9,1,9,1,9,1,10,1,10,
      1,10,1,11,1,11,1,11,5,11,122,8,11,10,11,12,11,125,9,11,1,12,1,12,1,
      12,5,12,130,8,12,10,12,12,12,133,9,12,1,13,1,13,1,14,1,14,1,14,3,14,
      140,8,14,1,15,1,15,1,15,5,15,145,8,15,10,15,12,15,148,9,15,1,16,1,
      16,1,16,5,16,153,8,16,10,16,12,16,156,9,16,1,17,1,17,1,17,5,17,161,
      8,17,10,17,12,17,164,9,17,1,18,1,18,1,18,5,18,169,8,18,10,18,12,18,
      172,9,18,1,19,1,19,1,19,5,19,177,8,19,10,19,12,19,180,9,19,1,20,1,
      20,1,20,5,20,185,8,20,10,20,12,20,188,9,20,1,21,1,21,1,21,5,21,193,
      8,21,10,21,12,21,196,9,21,1,22,1,22,1,22,3,22,201,8,22,1,23,1,23,1,
      23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,213,8,23,1,24,1,24,1,24,
      0,0,25,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
      44,46,48,0,6,1,0,17,18,1,0,19,20,1,0,21,23,1,0,24,26,2,0,22,22,28,
      28,1,0,29,33,220,0,53,1,0,0,0,2,68,1,0,0,0,4,70,1,0,0,0,6,74,1,0,0,
      0,8,79,1,0,0,0,10,83,1,0,0,0,12,87,1,0,0,0,14,91,1,0,0,0,16,100,1,
      0,0,0,18,106,1,0,0,0,20,115,1,0,0,0,22,118,1,0,0,0,24,126,1,0,0,0,
      26,134,1,0,0,0,28,136,1,0,0,0,30,141,1,0,0,0,32,149,1,0,0,0,34,157,
      1,0,0,0,36,165,1,0,0,0,38,173,1,0,0,0,40,181,1,0,0,0,42,189,1,0,0,
      0,44,200,1,0,0,0,46,212,1,0,0,0,48,214,1,0,0,0,50,52,3,2,1,0,51,50,
      1,0,0,0,52,55,1,0,0,0,53,51,1,0,0,0,53,54,1,0,0,0,54,56,1,0,0,0,55,
      53,1,0,0,0,56,57,5,0,0,1,57,1,1,0,0,0,58,69,5,1,0,0,59,69,3,4,2,0,
      60,69,3,8,4,0,61,69,3,10,5,0,62,69,3,12,6,0,63,69,3,14,7,0,64,69,3,
      16,8,0,65,69,3,18,9,0,66,69,3,6,3,0,67,69,3,20,10,0,68,58,1,0,0,0,
      68,59,1,0,0,0,68,60,1,0,0,0,68,61,1,0,0,0,68,62,1,0,0,0,68,63,1,0,
      0,0,68,64,1,0,0,0,68,65,1,0,0,0,68,66,1,0,0,0,68,67,1,0,0,0,69,3,1,
      0,0,0,70,71,3,48,24,0,71,72,3,22,11,0,72,73,5,1,0,0,73,5,1,0,0,0,74,
      75,5,2,0,0,75,76,5,39,0,0,76,77,5,37,0,0,77,78,5,1,0,0,78,7,1,0,0,
      0,79,80,5,3,0,0,80,81,3,22,11,0,81,82,5,1,0,0,82,9,1,0,0,0,83,84,5,
      4,0,0,84,85,3,24,12,0,85,86,5,1,0,0,86,11,1,0,0,0,87,88,5,5,0,0,88,
      89,3,24,12,0,89,90,5,1,0,0,90,13,1,0,0,0,91,92,5,6,0,0,92,93,5,7,0,
      0,93,94,3,26,13,0,94,95,5,8,0,0,95,98,3,2,1,0,96,97,5,9,0,0,97,99,
      3,2,1,0,98,96,1,0,0,0,98,99,1,0,0,0,99,15,1,0,0,0,100,101,5,10,0,0,
      101,102,5,7,0,0,102,103,3,26,13,0,103,104,5,8,0,0,104,105,3,2,1,0,
      105,17,1,0,0,0,106,110,5,11,0,0,107,109,3,2,1,0,108,107,1,0,0,0,109,
      112,1,0,0,0,110,108,1,0,0,0,110,111,1,0,0,0,111,113,1,0,0,0,112,110,
      1,0,0,0,113,114,5,12,0,0,114,19,1,0,0,0,115,116,3,26,13,0,116,117,
      5,1,0,0,117,21,1,0,0,0,118,123,5,39,0,0,119,120,5,13,0,0,120,122,5,
      39,0,0,121,119,1,0,0,0,122,125,1,0,0,0,123,121,1,0,0,0,123,124,1,0,
      0,0,124,23,1,0,0,0,125,123,1,0,0,0,126,131,3,26,13,0,127,128,5,13,
      0,0,128,130,3,26,13,0,129,127,1,0,0,0,130,133,1,0,0,0,131,129,1,0,
      0,0,131,132,1,0,0,0,132,25,1,0,0,0,133,131,1,0,0,0,134,135,3,28,14,
      0,135,27,1,0,0,0,136,139,3,30,15,0,137,138,5,14,0,0,138,140,3,28,14,
      0,139,137,1,0,0,0,139,140,1,0,0,0,140,29,1,0,0,0,141,146,3,32,16,0,
      142,143,5,15,0,0,143,145,3,32,16,0,144,142,1,0,0,0,145,148,1,0,0,0,
      146,144,1,0,0,0,146,147,1,0,0,0,147,31,1,0,0,0,148,146,1,0,0,0,149,
      154,3,34,17,0,150,151,5,16,0,0,151,153,3,34,17,0,152,150,1,0,0,0,153,
      156,1,0,0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,33,1,0,0,0,156,154,
      1,0,0,0,157,162,3,36,18,0,158,159,7,0,0,0,159,161,3,36,18,0,160,158,
      1,0,0,0,161,164,1,0,0,0,162,160,1,0,0,0,162,163,1,0,0,0,163,35,1,0,
      0,0,164,162,1,0,0,0,165,170,3,38,19,0,166,167,7,1,0,0,167,169,3,38,
      19,0,168,166,1,0,0,0,169,172,1,0,0,0,170,168,1,0,0,0,170,171,1,0,0,
      0,171,37,1,0,0,0,172,170,1,0,0,0,173,178,3,40,20,0,174,175,7,2,0,0,
      175,177,3,40,20,0,176,174,1,0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,
      178,179,1,0,0,0,179,39,1,0,0,0,180,178,1,0,0,0,181,186,3,42,21,0,182,
      183,7,3,0,0,183,185,3,42,21,0,184,182,1,0,0,0,185,188,1,0,0,0,186,
      184,1,0,0,0,186,187,1,0,0,0,187,41,1,0,0,0,188,186,1,0,0,0,189,194,
      3,44,22,0,190,191,5,27,0,0,191,193,3,44,22,0,192,190,1,0,0,0,193,196,
      1,0,0,0,194,192,1,0,0,0,194,195,1,0,0,0,195,43,1,0,0,0,196,194,1,0,
      0,0,197,198,7,4,0,0,198,201,3,44,22,0,199,201,3,46,23,0,200,197,1,
      0,0,0,200,199,1,0,0,0,201,45,1,0,0,0,202,213,5,35,0,0,203,213,5,36,
      0,0,204,213,5,34,0,0,205,213,5,37,0,0,206,213,5,38,0,0,207,213,5,39,
      0,0,208,209,5,7,0,0,209,210,3,26,13,0,210,211,5,8,0,0,211,213,1,0,
      0,0,212,202,1,0,0,0,212,203,1,0,0,0,212,204,1,0,0,0,212,205,1,0,0,
      0,212,206,1,0,0,0,212,207,1,0,0,0,212,208,1,0,0,0,213,47,1,0,0,0,214,
      215,7,5,0,0,215,49,1,0,0,0,16,53,68,98,110,123,131,139,146,154,162,
      170,178,186,194,200,212
  ];

  static final ATN _ATN =
      ATNDeserializer().deserialize(_serializedATN);
}
class ProgramContext extends ParserRuleContext {
  TerminalNode? EOF() => getToken(MyLangParser.TOKEN_EOF, 0);
  List<StatementContext> statements() => getRuleContexts<StatementContext>();
  StatementContext? statement(int i) => getRuleContext<StatementContext>(i);
  ProgramContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_program;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterProgram(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitProgram(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitProgram(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class StatementContext extends ParserRuleContext {
  StatementContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_statement;
 
  @override
  void copyFrom(ParserRuleContext ctx) {
    super.copyFrom(ctx);
  }
}

class DeclarationStmtContext extends ParserRuleContext {
  TypeContext? type() => getRuleContext<TypeContext>(0);
  VariableListContext? variableList() => getRuleContext<VariableListContext>(0);
  DeclarationStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_declarationStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterDeclarationStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitDeclarationStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitDeclarationStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class FopenStmtContext extends ParserRuleContext {
  TerminalNode? Identifier() => getToken(MyLangParser.TOKEN_Identifier, 0);
  TerminalNode? STRING() => getToken(MyLangParser.TOKEN_STRING, 0);
  FopenStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_fopenStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterFopenStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitFopenStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitFopenStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class ReadStmtContext extends ParserRuleContext {
  VariableListContext? variableList() => getRuleContext<VariableListContext>(0);
  ReadStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_readStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterReadStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitReadStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitReadStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class WriteStmtContext extends ParserRuleContext {
  ExprListContext? exprList() => getRuleContext<ExprListContext>(0);
  WriteStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_writeStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterWriteStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitWriteStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitWriteStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class FwriteStmtContext extends ParserRuleContext {
  ExprListContext? exprList() => getRuleContext<ExprListContext>(0);
  FwriteStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_fwriteStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterFwriteStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitFwriteStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitFwriteStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class IfStmtContext extends ParserRuleContext {
  ExpressionContext? expression() => getRuleContext<ExpressionContext>(0);
  List<StatementContext> statements() => getRuleContexts<StatementContext>();
  StatementContext? statement(int i) => getRuleContext<StatementContext>(i);
  IfStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_ifStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterIfStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitIfStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitIfStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class WhileStmtContext extends ParserRuleContext {
  ExpressionContext? expression() => getRuleContext<ExpressionContext>(0);
  StatementContext? statement() => getRuleContext<StatementContext>(0);
  WhileStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_whileStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterWhileStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitWhileStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitWhileStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class BlockStmtContext extends ParserRuleContext {
  List<StatementContext> statements() => getRuleContexts<StatementContext>();
  StatementContext? statement(int i) => getRuleContext<StatementContext>(i);
  BlockStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_blockStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterBlockStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitBlockStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitBlockStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class ExprStmtContext extends ParserRuleContext {
  ExpressionContext? expression() => getRuleContext<ExpressionContext>(0);
  ExprStmtContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_exprStmt;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterExprStmt(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitExprStmt(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitExprStmt(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class VariableListContext extends ParserRuleContext {
  List<TerminalNode> Identifiers() => getTokens(MyLangParser.TOKEN_Identifier);
  TerminalNode? Identifier(int i) => getToken(MyLangParser.TOKEN_Identifier, i);
  VariableListContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_variableList;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterVariableList(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitVariableList(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitVariableList(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class ExprListContext extends ParserRuleContext {
  List<ExpressionContext> expressions() => getRuleContexts<ExpressionContext>();
  ExpressionContext? expression(int i) => getRuleContext<ExpressionContext>(i);
  ExprListContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_exprList;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterExprList(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitExprList(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitExprList(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class ExpressionContext extends ParserRuleContext {
  AssignmentContext? assignment() => getRuleContext<AssignmentContext>(0);
  ExpressionContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_expression;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterExpression(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitExpression(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitExpression(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class AssignmentContext extends ParserRuleContext {
  LogicOrContext? logicOr() => getRuleContext<LogicOrContext>(0);
  AssignmentContext? assignment() => getRuleContext<AssignmentContext>(0);
  AssignmentContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_assignment;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterAssignment(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitAssignment(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitAssignment(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class LogicOrContext extends ParserRuleContext {
  List<LogicAndContext> logicAnds() => getRuleContexts<LogicAndContext>();
  LogicAndContext? logicAnd(int i) => getRuleContext<LogicAndContext>(i);
  LogicOrContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_logicOr;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterLogicOr(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitLogicOr(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitLogicOr(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class LogicAndContext extends ParserRuleContext {
  List<EqualityContext> equalitys() => getRuleContexts<EqualityContext>();
  EqualityContext? equality(int i) => getRuleContext<EqualityContext>(i);
  LogicAndContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_logicAnd;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterLogicAnd(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitLogicAnd(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitLogicAnd(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class EqualityContext extends ParserRuleContext {
  List<RelationalContext> relationals() => getRuleContexts<RelationalContext>();
  RelationalContext? relational(int i) => getRuleContext<RelationalContext>(i);
  EqualityContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_equality;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterEquality(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitEquality(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitEquality(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class RelationalContext extends ParserRuleContext {
  List<AdditiveContext> additives() => getRuleContexts<AdditiveContext>();
  AdditiveContext? additive(int i) => getRuleContext<AdditiveContext>(i);
  RelationalContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_relational;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterRelational(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitRelational(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitRelational(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class AdditiveContext extends ParserRuleContext {
  List<MultiplicativeContext> multiplicatives() => getRuleContexts<MultiplicativeContext>();
  MultiplicativeContext? multiplicative(int i) => getRuleContext<MultiplicativeContext>(i);
  AdditiveContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_additive;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterAdditive(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitAdditive(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitAdditive(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class MultiplicativeContext extends ParserRuleContext {
  List<AppendExprContext> appendExprs() => getRuleContexts<AppendExprContext>();
  AppendExprContext? appendExpr(int i) => getRuleContext<AppendExprContext>(i);
  MultiplicativeContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_multiplicative;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterMultiplicative(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitMultiplicative(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitMultiplicative(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class AppendExprContext extends ParserRuleContext {
  List<UnaryContext> unarys() => getRuleContexts<UnaryContext>();
  UnaryContext? unary(int i) => getRuleContext<UnaryContext>(i);
  AppendExprContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_appendExpr;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterAppendExpr(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitAppendExpr(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitAppendExpr(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class UnaryContext extends ParserRuleContext {
  UnaryContext? unary() => getRuleContext<UnaryContext>(0);
  PrimaryContext? primary() => getRuleContext<PrimaryContext>(0);
  UnaryContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_unary;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterUnary(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitUnary(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitUnary(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class PrimaryContext extends ParserRuleContext {
  TerminalNode? INT() => getToken(MyLangParser.TOKEN_INT, 0);
  TerminalNode? FLOAT() => getToken(MyLangParser.TOKEN_FLOAT, 0);
  TerminalNode? BOOL() => getToken(MyLangParser.TOKEN_BOOL, 0);
  TerminalNode? STRING() => getToken(MyLangParser.TOKEN_STRING, 0);
  TerminalNode? FILE() => getToken(MyLangParser.TOKEN_FILE, 0);
  TerminalNode? Identifier() => getToken(MyLangParser.TOKEN_Identifier, 0);
  ExpressionContext? expression() => getRuleContext<ExpressionContext>(0);
  PrimaryContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_primary;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterPrimary(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitPrimary(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitPrimary(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class TypeContext extends ParserRuleContext {
  TypeContext([ParserRuleContext? parent, int? invokingState]) : super(parent, invokingState);
  @override
  int get ruleIndex => RULE_type;
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterType(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitType(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitType(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class DeclarationStatementContext extends StatementContext {
  DeclarationStmtContext? declarationStmt() => getRuleContext<DeclarationStmtContext>(0);
  DeclarationStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterDeclarationStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitDeclarationStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitDeclarationStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class WhileStatementContext extends StatementContext {
  WhileStmtContext? whileStmt() => getRuleContext<WhileStmtContext>(0);
  WhileStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterWhileStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitWhileStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitWhileStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class EmptyStatementContext extends StatementContext {
  EmptyStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterEmptyStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitEmptyStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitEmptyStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class WriteStatementContext extends StatementContext {
  WriteStmtContext? writeStmt() => getRuleContext<WriteStmtContext>(0);
  WriteStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterWriteStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitWriteStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitWriteStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class BlockStatementContext extends StatementContext {
  BlockStmtContext? blockStmt() => getRuleContext<BlockStmtContext>(0);
  BlockStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterBlockStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitBlockStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitBlockStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class FopenStatementContext extends StatementContext {
  FopenStmtContext? fopenStmt() => getRuleContext<FopenStmtContext>(0);
  FopenStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterFopenStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitFopenStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitFopenStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class FwriteStatementContext extends StatementContext {
  FwriteStmtContext? fwriteStmt() => getRuleContext<FwriteStmtContext>(0);
  FwriteStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterFwriteStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitFwriteStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitFwriteStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class ReadStatementContext extends StatementContext {
  ReadStmtContext? readStmt() => getRuleContext<ReadStmtContext>(0);
  ReadStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterReadStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitReadStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitReadStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class ExpressionStatementContext extends StatementContext {
  ExprStmtContext? exprStmt() => getRuleContext<ExprStmtContext>(0);
  ExpressionStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterExpressionStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitExpressionStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitExpressionStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}

class IfStatementContext extends StatementContext {
  IfStmtContext? ifStmt() => getRuleContext<IfStmtContext>(0);
  IfStatementContext(StatementContext ctx) { copyFrom(ctx); }
  @override
  void enterRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.enterIfStatement(this);
  }
  @override
  void exitRule(ParseTreeListener listener) {
    if (listener is MyLangListener) listener.exitIfStatement(this);
  }
  @override
  T? accept<T>(ParseTreeVisitor<T> visitor) {
    if (visitor is MyLangVisitor<T>) {
     return visitor.visitIfStatement(this);
    } else {
    	return visitor.visitChildren(this);
    }
  }
}