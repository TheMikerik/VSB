// Generated from MyLang.g4 by ANTLR 4.13.1
// ignore_for_file: unused_import, unused_local_variable, prefer_single_quotes
import 'package:antlr4/antlr4.dart';

import 'MyLangListener.dart';
import 'MyLangBaseListener.dart';
const int RULE_program = 0, RULE_statement = 1, RULE_declarationStmt = 2, 
          RULE_variableList = 3, RULE_readStmt = 4, RULE_writeStmt = 5, 
          RULE_fwriteStmt = 6, RULE_ifStmt = 7, RULE_whileStmt = 8, RULE_blockStmt = 9, 
          RULE_exprStmt = 10, RULE_exprList = 11, RULE_expression = 12, 
          RULE_assignment = 13, RULE_logicOr = 14, RULE_logicAnd = 15, RULE_equality = 16, 
          RULE_relational = 17, RULE_additive = 18, RULE_multiplicative = 19, 
          RULE_unary = 20, RULE_primary = 21, RULE_type = 22;
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
                   TOKEN_T__30 = 31, TOKEN_BooleanLiteral = 32, TOKEN_IntegerLiteral = 33, 
                   TOKEN_FloatLiteral = 34, TOKEN_StringLiteral = 35, TOKEN_FileLiteral = 36, 
                   TOKEN_Identifier = 37, TOKEN_WS = 38, TOKEN_COMMENT = 39;

  @override
  final List<String> ruleNames = [
    'program', 'statement', 'declarationStmt', 'variableList', 'readStmt', 
    'writeStmt', 'fwriteStmt', 'ifStmt', 'whileStmt', 'blockStmt', 'exprStmt', 
    'exprList', 'expression', 'assignment', 'logicOr', 'logicAnd', 'equality', 
    'relational', 'additive', 'multiplicative', 'unary', 'primary', 'type'
  ];

  static final List<String?> _LITERAL_NAMES = [
      null, "';'", "','", "'read'", "'write'", "'fwrite'", "'if'", "'('", 
      "')'", "'else'", "'while'", "'{'", "'}'", "'='", "'||'", "'&&'", "'=='", 
      "'!='", "'<'", "'>'", "'+'", "'-'", "'.'", "'*'", "'/'", "'%'", "'!'", 
      "'int'", "'float'", "'bool'", "'string'", "'file'"
  ];
  static final List<String?> _SYMBOLIC_NAMES = [
      null, null, null, null, null, null, null, null, null, null, null, 
      null, null, null, null, null, null, null, null, null, null, null, 
      null, null, null, null, null, null, null, null, null, null, "BooleanLiteral", 
      "IntegerLiteral", "FloatLiteral", "StringLiteral", "FileLiteral", 
      "Identifier", "WS", "COMMENT"
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
      state = 49;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 274812898554) != 0)) {
        state = 46;
        statement();
        state = 51;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
      state = 52;
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
      state = 63;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_T__0:
        _localctx = EmptyStatementContext(_localctx);
        enterOuterAlt(_localctx, 1);
        state = 54;
        match(TOKEN_T__0);
        break;
      case TOKEN_T__26:
      case TOKEN_T__27:
      case TOKEN_T__28:
      case TOKEN_T__29:
      case TOKEN_T__30:
        _localctx = DeclarationStatementContext(_localctx);
        enterOuterAlt(_localctx, 2);
        state = 55;
        declarationStmt();
        break;
      case TOKEN_T__2:
        _localctx = ReadStatementContext(_localctx);
        enterOuterAlt(_localctx, 3);
        state = 56;
        readStmt();
        break;
      case TOKEN_T__3:
        _localctx = WriteStatementContext(_localctx);
        enterOuterAlt(_localctx, 4);
        state = 57;
        writeStmt();
        break;
      case TOKEN_T__4:
        _localctx = FwriteStatementContext(_localctx);
        enterOuterAlt(_localctx, 5);
        state = 58;
        fwriteStmt();
        break;
      case TOKEN_T__5:
        _localctx = IfStatementContext(_localctx);
        enterOuterAlt(_localctx, 6);
        state = 59;
        ifStmt();
        break;
      case TOKEN_T__9:
        _localctx = WhileStatementContext(_localctx);
        enterOuterAlt(_localctx, 7);
        state = 60;
        whileStmt();
        break;
      case TOKEN_T__10:
        _localctx = BlockStatementContext(_localctx);
        enterOuterAlt(_localctx, 8);
        state = 61;
        blockStmt();
        break;
      case TOKEN_T__6:
      case TOKEN_T__20:
      case TOKEN_T__25:
      case TOKEN_BooleanLiteral:
      case TOKEN_IntegerLiteral:
      case TOKEN_FloatLiteral:
      case TOKEN_StringLiteral:
      case TOKEN_FileLiteral:
      case TOKEN_Identifier:
        _localctx = ExpressionStatementContext(_localctx);
        enterOuterAlt(_localctx, 9);
        state = 62;
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
      state = 65;
      type();
      state = 66;
      variableList();
      state = 67;
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
    enterRule(_localctx, 6, RULE_variableList);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 69;
      match(TOKEN_Identifier);
      state = 74;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__1) {
        state = 70;
        match(TOKEN_T__1);
        state = 71;
        match(TOKEN_Identifier);
        state = 76;
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

  ReadStmtContext readStmt() {
    dynamic _localctx = ReadStmtContext(context, state);
    enterRule(_localctx, 8, RULE_readStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 77;
      match(TOKEN_T__2);
      state = 78;
      variableList();
      state = 79;
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
      state = 81;
      match(TOKEN_T__3);
      state = 82;
      exprList();
      state = 83;
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
      state = 85;
      match(TOKEN_T__4);
      state = 86;
      exprList();
      state = 87;
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
      state = 89;
      match(TOKEN_T__5);
      state = 90;
      match(TOKEN_T__6);
      state = 91;
      expression();
      state = 92;
      match(TOKEN_T__7);
      state = 93;
      statement();
      state = 96;
      errorHandler.sync(this);
      switch (interpreter!.adaptivePredict(tokenStream, 3, context)) {
      case 1:
        state = 94;
        match(TOKEN_T__8);
        state = 95;
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
      state = 98;
      match(TOKEN_T__9);
      state = 99;
      match(TOKEN_T__6);
      state = 100;
      expression();
      state = 101;
      match(TOKEN_T__7);
      state = 102;
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
      state = 104;
      match(TOKEN_T__10);
      state = 108;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 274812898554) != 0)) {
        state = 105;
        statement();
        state = 110;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
      state = 111;
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
      state = 113;
      expression();
      state = 114;
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

  ExprListContext exprList() {
    dynamic _localctx = ExprListContext(context, state);
    enterRule(_localctx, 22, RULE_exprList);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 116;
      expression();
      state = 121;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__1) {
        state = 117;
        match(TOKEN_T__1);
        state = 118;
        expression();
        state = 123;
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
    enterRule(_localctx, 24, RULE_expression);
    try {
      enterOuterAlt(_localctx, 1);
      state = 124;
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
    enterRule(_localctx, 26, RULE_assignment);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 126;
      logicOr();
      state = 129;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      if (_la == TOKEN_T__12) {
        state = 127;
        match(TOKEN_T__12);
        state = 128;
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
    enterRule(_localctx, 28, RULE_logicOr);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 131;
      logicAnd();
      state = 136;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__13) {
        state = 132;
        match(TOKEN_T__13);
        state = 133;
        logicAnd();
        state = 138;
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
    enterRule(_localctx, 30, RULE_logicAnd);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 139;
      equality();
      state = 144;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__14) {
        state = 140;
        match(TOKEN_T__14);
        state = 141;
        equality();
        state = 146;
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
    enterRule(_localctx, 32, RULE_equality);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 147;
      relational();
      state = 152;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__15 || _la == TOKEN_T__16) {
        state = 148;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__15 || _la == TOKEN_T__16)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 149;
        relational();
        state = 154;
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
    enterRule(_localctx, 34, RULE_relational);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 155;
      additive();
      state = 160;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__17 || _la == TOKEN_T__18) {
        state = 156;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__17 || _la == TOKEN_T__18)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 157;
        additive();
        state = 162;
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
    enterRule(_localctx, 36, RULE_additive);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 163;
      multiplicative();
      state = 168;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 7340032) != 0)) {
        state = 164;
        _la = tokenStream.LA(1)!;
        if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 7340032) != 0))) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 165;
        multiplicative();
        state = 170;
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
    enterRule(_localctx, 38, RULE_multiplicative);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 171;
      unary();
      state = 176;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 58720256) != 0)) {
        state = 172;
        _la = tokenStream.LA(1)!;
        if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 58720256) != 0))) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 173;
        unary();
        state = 178;
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
    enterRule(_localctx, 40, RULE_unary);
    int _la;
    try {
      state = 182;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_T__20:
      case TOKEN_T__25:
        enterOuterAlt(_localctx, 1);
        state = 179;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__20 || _la == TOKEN_T__25)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 180;
        unary();
        break;
      case TOKEN_T__6:
      case TOKEN_BooleanLiteral:
      case TOKEN_IntegerLiteral:
      case TOKEN_FloatLiteral:
      case TOKEN_StringLiteral:
      case TOKEN_FileLiteral:
      case TOKEN_Identifier:
        enterOuterAlt(_localctx, 2);
        state = 181;
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
    enterRule(_localctx, 42, RULE_primary);
    try {
      state = 194;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_IntegerLiteral:
        enterOuterAlt(_localctx, 1);
        state = 184;
        match(TOKEN_IntegerLiteral);
        break;
      case TOKEN_FloatLiteral:
        enterOuterAlt(_localctx, 2);
        state = 185;
        match(TOKEN_FloatLiteral);
        break;
      case TOKEN_BooleanLiteral:
        enterOuterAlt(_localctx, 3);
        state = 186;
        match(TOKEN_BooleanLiteral);
        break;
      case TOKEN_StringLiteral:
        enterOuterAlt(_localctx, 4);
        state = 187;
        match(TOKEN_StringLiteral);
        break;
      case TOKEN_FileLiteral:
        enterOuterAlt(_localctx, 5);
        state = 188;
        match(TOKEN_FileLiteral);
        break;
      case TOKEN_Identifier:
        enterOuterAlt(_localctx, 6);
        state = 189;
        match(TOKEN_Identifier);
        break;
      case TOKEN_T__6:
        enterOuterAlt(_localctx, 7);
        state = 190;
        match(TOKEN_T__6);
        state = 191;
        expression();
        state = 192;
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
    enterRule(_localctx, 44, RULE_type);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 196;
      _la = tokenStream.LA(1)!;
      if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 4160749568) != 0))) {
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
      4,1,39,199,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,
      2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,
      14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,
      2,21,7,21,2,22,7,22,1,0,5,0,48,8,0,10,0,12,0,51,9,0,1,0,1,0,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,64,8,1,1,2,1,2,1,2,1,2,1,3,1,3,1,
      3,5,3,73,8,3,10,3,12,3,76,9,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,
      1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,97,8,7,1,8,1,8,1,8,1,8,
      1,8,1,8,1,9,1,9,5,9,107,8,9,10,9,12,9,110,9,9,1,9,1,9,1,10,1,10,1,
      10,1,11,1,11,1,11,5,11,120,8,11,10,11,12,11,123,9,11,1,12,1,12,1,13,
      1,13,1,13,3,13,130,8,13,1,14,1,14,1,14,5,14,135,8,14,10,14,12,14,138,
      9,14,1,15,1,15,1,15,5,15,143,8,15,10,15,12,15,146,9,15,1,16,1,16,1,
      16,5,16,151,8,16,10,16,12,16,154,9,16,1,17,1,17,1,17,5,17,159,8,17,
      10,17,12,17,162,9,17,1,18,1,18,1,18,5,18,167,8,18,10,18,12,18,170,
      9,18,1,19,1,19,1,19,5,19,175,8,19,10,19,12,19,178,9,19,1,20,1,20,1,
      20,3,20,183,8,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
      3,21,195,8,21,1,22,1,22,1,22,0,0,23,0,2,4,6,8,10,12,14,16,18,20,22,
      24,26,28,30,32,34,36,38,40,42,44,0,6,1,0,16,17,1,0,18,19,1,0,20,22,
      1,0,23,25,2,0,21,21,26,26,1,0,27,31,202,0,49,1,0,0,0,2,63,1,0,0,0,
      4,65,1,0,0,0,6,69,1,0,0,0,8,77,1,0,0,0,10,81,1,0,0,0,12,85,1,0,0,0,
      14,89,1,0,0,0,16,98,1,0,0,0,18,104,1,0,0,0,20,113,1,0,0,0,22,116,1,
      0,0,0,24,124,1,0,0,0,26,126,1,0,0,0,28,131,1,0,0,0,30,139,1,0,0,0,
      32,147,1,0,0,0,34,155,1,0,0,0,36,163,1,0,0,0,38,171,1,0,0,0,40,182,
      1,0,0,0,42,194,1,0,0,0,44,196,1,0,0,0,46,48,3,2,1,0,47,46,1,0,0,0,
      48,51,1,0,0,0,49,47,1,0,0,0,49,50,1,0,0,0,50,52,1,0,0,0,51,49,1,0,
      0,0,52,53,5,0,0,1,53,1,1,0,0,0,54,64,5,1,0,0,55,64,3,4,2,0,56,64,3,
      8,4,0,57,64,3,10,5,0,58,64,3,12,6,0,59,64,3,14,7,0,60,64,3,16,8,0,
      61,64,3,18,9,0,62,64,3,20,10,0,63,54,1,0,0,0,63,55,1,0,0,0,63,56,1,
      0,0,0,63,57,1,0,0,0,63,58,1,0,0,0,63,59,1,0,0,0,63,60,1,0,0,0,63,61,
      1,0,0,0,63,62,1,0,0,0,64,3,1,0,0,0,65,66,3,44,22,0,66,67,3,6,3,0,67,
      68,5,1,0,0,68,5,1,0,0,0,69,74,5,37,0,0,70,71,5,2,0,0,71,73,5,37,0,
      0,72,70,1,0,0,0,73,76,1,0,0,0,74,72,1,0,0,0,74,75,1,0,0,0,75,7,1,0,
      0,0,76,74,1,0,0,0,77,78,5,3,0,0,78,79,3,6,3,0,79,80,5,1,0,0,80,9,1,
      0,0,0,81,82,5,4,0,0,82,83,3,22,11,0,83,84,5,1,0,0,84,11,1,0,0,0,85,
      86,5,5,0,0,86,87,3,22,11,0,87,88,5,1,0,0,88,13,1,0,0,0,89,90,5,6,0,
      0,90,91,5,7,0,0,91,92,3,24,12,0,92,93,5,8,0,0,93,96,3,2,1,0,94,95,
      5,9,0,0,95,97,3,2,1,0,96,94,1,0,0,0,96,97,1,0,0,0,97,15,1,0,0,0,98,
      99,5,10,0,0,99,100,5,7,0,0,100,101,3,24,12,0,101,102,5,8,0,0,102,103,
      3,2,1,0,103,17,1,0,0,0,104,108,5,11,0,0,105,107,3,2,1,0,106,105,1,
      0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,1,0,0,0,109,111,1,0,
      0,0,110,108,1,0,0,0,111,112,5,12,0,0,112,19,1,0,0,0,113,114,3,24,12,
      0,114,115,5,1,0,0,115,21,1,0,0,0,116,121,3,24,12,0,117,118,5,2,0,0,
      118,120,3,24,12,0,119,117,1,0,0,0,120,123,1,0,0,0,121,119,1,0,0,0,
      121,122,1,0,0,0,122,23,1,0,0,0,123,121,1,0,0,0,124,125,3,26,13,0,125,
      25,1,0,0,0,126,129,3,28,14,0,127,128,5,13,0,0,128,130,3,26,13,0,129,
      127,1,0,0,0,129,130,1,0,0,0,130,27,1,0,0,0,131,136,3,30,15,0,132,133,
      5,14,0,0,133,135,3,30,15,0,134,132,1,0,0,0,135,138,1,0,0,0,136,134,
      1,0,0,0,136,137,1,0,0,0,137,29,1,0,0,0,138,136,1,0,0,0,139,144,3,32,
      16,0,140,141,5,15,0,0,141,143,3,32,16,0,142,140,1,0,0,0,143,146,1,
      0,0,0,144,142,1,0,0,0,144,145,1,0,0,0,145,31,1,0,0,0,146,144,1,0,0,
      0,147,152,3,34,17,0,148,149,7,0,0,0,149,151,3,34,17,0,150,148,1,0,
      0,0,151,154,1,0,0,0,152,150,1,0,0,0,152,153,1,0,0,0,153,33,1,0,0,0,
      154,152,1,0,0,0,155,160,3,36,18,0,156,157,7,1,0,0,157,159,3,36,18,
      0,158,156,1,0,0,0,159,162,1,0,0,0,160,158,1,0,0,0,160,161,1,0,0,0,
      161,35,1,0,0,0,162,160,1,0,0,0,163,168,3,38,19,0,164,165,7,2,0,0,165,
      167,3,38,19,0,166,164,1,0,0,0,167,170,1,0,0,0,168,166,1,0,0,0,168,
      169,1,0,0,0,169,37,1,0,0,0,170,168,1,0,0,0,171,176,3,40,20,0,172,173,
      7,3,0,0,173,175,3,40,20,0,174,172,1,0,0,0,175,178,1,0,0,0,176,174,
      1,0,0,0,176,177,1,0,0,0,177,39,1,0,0,0,178,176,1,0,0,0,179,180,7,4,
      0,0,180,183,3,40,20,0,181,183,3,42,21,0,182,179,1,0,0,0,182,181,1,
      0,0,0,183,41,1,0,0,0,184,195,5,33,0,0,185,195,5,34,0,0,186,195,5,32,
      0,0,187,195,5,35,0,0,188,195,5,36,0,0,189,195,5,37,0,0,190,191,5,7,
      0,0,191,192,3,24,12,0,192,193,5,8,0,0,193,195,1,0,0,0,194,184,1,0,
      0,0,194,185,1,0,0,0,194,186,1,0,0,0,194,187,1,0,0,0,194,188,1,0,0,
      0,194,189,1,0,0,0,194,190,1,0,0,0,195,43,1,0,0,0,196,197,7,5,0,0,197,
      45,1,0,0,0,15,49,63,74,96,108,121,129,136,144,152,160,168,176,182,
      194
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
}

class MultiplicativeContext extends ParserRuleContext {
  List<UnaryContext> unarys() => getRuleContexts<UnaryContext>();
  UnaryContext? unary(int i) => getRuleContext<UnaryContext>(i);
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
}

class PrimaryContext extends ParserRuleContext {
  TerminalNode? IntegerLiteral() => getToken(MyLangParser.TOKEN_IntegerLiteral, 0);
  TerminalNode? FloatLiteral() => getToken(MyLangParser.TOKEN_FloatLiteral, 0);
  TerminalNode? BooleanLiteral() => getToken(MyLangParser.TOKEN_BooleanLiteral, 0);
  TerminalNode? StringLiteral() => getToken(MyLangParser.TOKEN_StringLiteral, 0);
  TerminalNode? FileLiteral() => getToken(MyLangParser.TOKEN_FileLiteral, 0);
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
}