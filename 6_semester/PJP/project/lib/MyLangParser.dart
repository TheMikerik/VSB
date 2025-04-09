// Generated from MyLang.g4 by ANTLR 4.13.1
// ignore_for_file: unused_import, unused_local_variable, prefer_single_quotes
import 'package:antlr4/antlr4.dart';

import 'MyLangListener.dart';
import 'MyLangBaseListener.dart';
const int RULE_program = 0, RULE_statement = 1, RULE_declarationStmt = 2, 
          RULE_variableList = 3, RULE_readStmt = 4, RULE_writeStmt = 5, 
          RULE_ifStmt = 6, RULE_whileStmt = 7, RULE_blockStmt = 8, RULE_exprStmt = 9, 
          RULE_exprList = 10, RULE_expression = 11, RULE_assignment = 12, 
          RULE_logicOr = 13, RULE_logicAnd = 14, RULE_equality = 15, RULE_relational = 16, 
          RULE_additive = 17, RULE_multiplicative = 18, RULE_unary = 19, 
          RULE_primary = 20, RULE_type = 21;
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
                   TOKEN_BooleanLiteral = 31, TOKEN_IntegerLiteral = 32, 
                   TOKEN_FloatLiteral = 33, TOKEN_StringLiteral = 34, TOKEN_FileLiteral = 35, 
                   TOKEN_Identifier = 36, TOKEN_WS = 37, TOKEN_COMMENT = 38;

  @override
  final List<String> ruleNames = [
    'program', 'statement', 'declarationStmt', 'variableList', 'readStmt', 
    'writeStmt', 'ifStmt', 'whileStmt', 'blockStmt', 'exprStmt', 'exprList', 
    'expression', 'assignment', 'logicOr', 'logicAnd', 'equality', 'relational', 
    'additive', 'multiplicative', 'unary', 'primary', 'type'
  ];

  static final List<String?> _LITERAL_NAMES = [
      null, "';'", "','", "'read'", "'write'", "'if'", "'('", "')'", "'else'", 
      "'while'", "'{'", "'}'", "'='", "'||'", "'&&'", "'=='", "'!='", "'<'", 
      "'>'", "'+'", "'-'", "'.'", "'*'", "'/'", "'%'", "'!'", "'int'", "'float'", 
      "'bool'", "'string'", "'FILE'"
  ];
  static final List<String?> _SYMBOLIC_NAMES = [
      null, null, null, null, null, null, null, null, null, null, null, 
      null, null, null, null, null, null, null, null, null, null, null, 
      null, null, null, null, null, null, null, null, null, "BooleanLiteral", 
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
      state = 47;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 137406449274) != 0)) {
        state = 44;
        statement();
        state = 49;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
      state = 50;
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
      state = 60;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_T__0:
        _localctx = EmptyStatementContext(_localctx);
        enterOuterAlt(_localctx, 1);
        state = 52;
        match(TOKEN_T__0);
        break;
      case TOKEN_T__25:
      case TOKEN_T__26:
      case TOKEN_T__27:
      case TOKEN_T__28:
      case TOKEN_T__29:
        _localctx = DeclarationStatementContext(_localctx);
        enterOuterAlt(_localctx, 2);
        state = 53;
        declarationStmt();
        break;
      case TOKEN_T__2:
        _localctx = ReadStatementContext(_localctx);
        enterOuterAlt(_localctx, 3);
        state = 54;
        readStmt();
        break;
      case TOKEN_T__3:
        _localctx = WriteStatementContext(_localctx);
        enterOuterAlt(_localctx, 4);
        state = 55;
        writeStmt();
        break;
      case TOKEN_T__4:
        _localctx = IfStatementContext(_localctx);
        enterOuterAlt(_localctx, 5);
        state = 56;
        ifStmt();
        break;
      case TOKEN_T__8:
        _localctx = WhileStatementContext(_localctx);
        enterOuterAlt(_localctx, 6);
        state = 57;
        whileStmt();
        break;
      case TOKEN_T__9:
        _localctx = BlockStatementContext(_localctx);
        enterOuterAlt(_localctx, 7);
        state = 58;
        blockStmt();
        break;
      case TOKEN_T__5:
      case TOKEN_T__19:
      case TOKEN_T__24:
      case TOKEN_BooleanLiteral:
      case TOKEN_IntegerLiteral:
      case TOKEN_FloatLiteral:
      case TOKEN_StringLiteral:
      case TOKEN_FileLiteral:
      case TOKEN_Identifier:
        _localctx = ExpressionStatementContext(_localctx);
        enterOuterAlt(_localctx, 8);
        state = 59;
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
      state = 62;
      type();
      state = 63;
      variableList();
      state = 64;
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
      state = 66;
      match(TOKEN_Identifier);
      state = 71;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__1) {
        state = 67;
        match(TOKEN_T__1);
        state = 68;
        match(TOKEN_Identifier);
        state = 73;
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
      state = 74;
      match(TOKEN_T__2);
      state = 75;
      variableList();
      state = 76;
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
      state = 78;
      match(TOKEN_T__3);
      state = 79;
      exprList();
      state = 80;
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
    enterRule(_localctx, 12, RULE_ifStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 82;
      match(TOKEN_T__4);
      state = 83;
      match(TOKEN_T__5);
      state = 84;
      expression();
      state = 85;
      match(TOKEN_T__6);
      state = 86;
      statement();
      state = 89;
      errorHandler.sync(this);
      switch (interpreter!.adaptivePredict(tokenStream, 3, context)) {
      case 1:
        state = 87;
        match(TOKEN_T__7);
        state = 88;
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
    enterRule(_localctx, 14, RULE_whileStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 91;
      match(TOKEN_T__8);
      state = 92;
      match(TOKEN_T__5);
      state = 93;
      expression();
      state = 94;
      match(TOKEN_T__6);
      state = 95;
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
    enterRule(_localctx, 16, RULE_blockStmt);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 97;
      match(TOKEN_T__9);
      state = 101;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 137406449274) != 0)) {
        state = 98;
        statement();
        state = 103;
        errorHandler.sync(this);
        _la = tokenStream.LA(1)!;
      }
      state = 104;
      match(TOKEN_T__10);
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
    enterRule(_localctx, 18, RULE_exprStmt);
    try {
      enterOuterAlt(_localctx, 1);
      state = 106;
      expression();
      state = 107;
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
    enterRule(_localctx, 20, RULE_exprList);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 109;
      expression();
      state = 114;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__1) {
        state = 110;
        match(TOKEN_T__1);
        state = 111;
        expression();
        state = 116;
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
    enterRule(_localctx, 22, RULE_expression);
    try {
      enterOuterAlt(_localctx, 1);
      state = 117;
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
    enterRule(_localctx, 24, RULE_assignment);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 119;
      logicOr();
      state = 122;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      if (_la == TOKEN_T__11) {
        state = 120;
        match(TOKEN_T__11);
        state = 121;
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
    enterRule(_localctx, 26, RULE_logicOr);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 124;
      logicAnd();
      state = 129;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__12) {
        state = 125;
        match(TOKEN_T__12);
        state = 126;
        logicAnd();
        state = 131;
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
    enterRule(_localctx, 28, RULE_logicAnd);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 132;
      equality();
      state = 137;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__13) {
        state = 133;
        match(TOKEN_T__13);
        state = 134;
        equality();
        state = 139;
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
    enterRule(_localctx, 30, RULE_equality);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 140;
      relational();
      state = 145;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__14 || _la == TOKEN_T__15) {
        state = 141;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__14 || _la == TOKEN_T__15)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 142;
        relational();
        state = 147;
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
    enterRule(_localctx, 32, RULE_relational);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 148;
      additive();
      state = 153;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while (_la == TOKEN_T__16 || _la == TOKEN_T__17) {
        state = 149;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__16 || _la == TOKEN_T__17)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 150;
        additive();
        state = 155;
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
    enterRule(_localctx, 34, RULE_additive);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 156;
      multiplicative();
      state = 161;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 3670016) != 0)) {
        state = 157;
        _la = tokenStream.LA(1)!;
        if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 3670016) != 0))) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 158;
        multiplicative();
        state = 163;
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
    enterRule(_localctx, 36, RULE_multiplicative);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 164;
      unary();
      state = 169;
      errorHandler.sync(this);
      _la = tokenStream.LA(1)!;
      while ((((_la) & ~0x3f) == 0 && ((1 << _la) & 29360128) != 0)) {
        state = 165;
        _la = tokenStream.LA(1)!;
        if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 29360128) != 0))) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 166;
        unary();
        state = 171;
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
    enterRule(_localctx, 38, RULE_unary);
    int _la;
    try {
      state = 175;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_T__19:
      case TOKEN_T__24:
        enterOuterAlt(_localctx, 1);
        state = 172;
        _la = tokenStream.LA(1)!;
        if (!(_la == TOKEN_T__19 || _la == TOKEN_T__24)) {
        errorHandler.recoverInline(this);
        } else {
          if ( tokenStream.LA(1)! == IntStream.EOF ) matchedEOF = true;
          errorHandler.reportMatch(this);
          consume();
        }
        state = 173;
        unary();
        break;
      case TOKEN_T__5:
      case TOKEN_BooleanLiteral:
      case TOKEN_IntegerLiteral:
      case TOKEN_FloatLiteral:
      case TOKEN_StringLiteral:
      case TOKEN_FileLiteral:
      case TOKEN_Identifier:
        enterOuterAlt(_localctx, 2);
        state = 174;
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
    enterRule(_localctx, 40, RULE_primary);
    try {
      state = 187;
      errorHandler.sync(this);
      switch (tokenStream.LA(1)!) {
      case TOKEN_IntegerLiteral:
        enterOuterAlt(_localctx, 1);
        state = 177;
        match(TOKEN_IntegerLiteral);
        break;
      case TOKEN_FloatLiteral:
        enterOuterAlt(_localctx, 2);
        state = 178;
        match(TOKEN_FloatLiteral);
        break;
      case TOKEN_BooleanLiteral:
        enterOuterAlt(_localctx, 3);
        state = 179;
        match(TOKEN_BooleanLiteral);
        break;
      case TOKEN_StringLiteral:
        enterOuterAlt(_localctx, 4);
        state = 180;
        match(TOKEN_StringLiteral);
        break;
      case TOKEN_FileLiteral:
        enterOuterAlt(_localctx, 5);
        state = 181;
        match(TOKEN_FileLiteral);
        break;
      case TOKEN_Identifier:
        enterOuterAlt(_localctx, 6);
        state = 182;
        match(TOKEN_Identifier);
        break;
      case TOKEN_T__5:
        enterOuterAlt(_localctx, 7);
        state = 183;
        match(TOKEN_T__5);
        state = 184;
        expression();
        state = 185;
        match(TOKEN_T__6);
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
    enterRule(_localctx, 42, RULE_type);
    int _la;
    try {
      enterOuterAlt(_localctx, 1);
      state = 189;
      _la = tokenStream.LA(1)!;
      if (!((((_la) & ~0x3f) == 0 && ((1 << _la) & 2080374784) != 0))) {
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
      4,1,38,192,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,
      2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,
      14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,
      2,21,7,21,1,0,5,0,46,8,0,10,0,12,0,49,9,0,1,0,1,0,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,3,1,61,8,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,5,3,70,8,3,
      10,3,12,3,73,9,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,
      6,1,6,1,6,3,6,90,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,5,8,100,8,8,10,
      8,12,8,103,9,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,5,10,113,8,10,10,
      10,12,10,116,9,10,1,11,1,11,1,12,1,12,1,12,3,12,123,8,12,1,13,1,13,
      1,13,5,13,128,8,13,10,13,12,13,131,9,13,1,14,1,14,1,14,5,14,136,8,
      14,10,14,12,14,139,9,14,1,15,1,15,1,15,5,15,144,8,15,10,15,12,15,147,
      9,15,1,16,1,16,1,16,5,16,152,8,16,10,16,12,16,155,9,16,1,17,1,17,1,
      17,5,17,160,8,17,10,17,12,17,163,9,17,1,18,1,18,1,18,5,18,168,8,18,
      10,18,12,18,171,9,18,1,19,1,19,1,19,3,19,176,8,19,1,20,1,20,1,20,1,
      20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,188,8,20,1,21,1,21,1,21,0,0,
      22,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,0,
      6,1,0,15,16,1,0,17,18,1,0,19,21,1,0,22,24,2,0,20,20,25,25,1,0,26,30,
      195,0,47,1,0,0,0,2,60,1,0,0,0,4,62,1,0,0,0,6,66,1,0,0,0,8,74,1,0,0,
      0,10,78,1,0,0,0,12,82,1,0,0,0,14,91,1,0,0,0,16,97,1,0,0,0,18,106,1,
      0,0,0,20,109,1,0,0,0,22,117,1,0,0,0,24,119,1,0,0,0,26,124,1,0,0,0,
      28,132,1,0,0,0,30,140,1,0,0,0,32,148,1,0,0,0,34,156,1,0,0,0,36,164,
      1,0,0,0,38,175,1,0,0,0,40,187,1,0,0,0,42,189,1,0,0,0,44,46,3,2,1,0,
      45,44,1,0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,50,1,0,
      0,0,49,47,1,0,0,0,50,51,5,0,0,1,51,1,1,0,0,0,52,61,5,1,0,0,53,61,3,
      4,2,0,54,61,3,8,4,0,55,61,3,10,5,0,56,61,3,12,6,0,57,61,3,14,7,0,58,
      61,3,16,8,0,59,61,3,18,9,0,60,52,1,0,0,0,60,53,1,0,0,0,60,54,1,0,0,
      0,60,55,1,0,0,0,60,56,1,0,0,0,60,57,1,0,0,0,60,58,1,0,0,0,60,59,1,
      0,0,0,61,3,1,0,0,0,62,63,3,42,21,0,63,64,3,6,3,0,64,65,5,1,0,0,65,
      5,1,0,0,0,66,71,5,36,0,0,67,68,5,2,0,0,68,70,5,36,0,0,69,67,1,0,0,
      0,70,73,1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,7,1,0,0,0,73,71,1,0,
      0,0,74,75,5,3,0,0,75,76,3,6,3,0,76,77,5,1,0,0,77,9,1,0,0,0,78,79,5,
      4,0,0,79,80,3,20,10,0,80,81,5,1,0,0,81,11,1,0,0,0,82,83,5,5,0,0,83,
      84,5,6,0,0,84,85,3,22,11,0,85,86,5,7,0,0,86,89,3,2,1,0,87,88,5,8,0,
      0,88,90,3,2,1,0,89,87,1,0,0,0,89,90,1,0,0,0,90,13,1,0,0,0,91,92,5,
      9,0,0,92,93,5,6,0,0,93,94,3,22,11,0,94,95,5,7,0,0,95,96,3,2,1,0,96,
      15,1,0,0,0,97,101,5,10,0,0,98,100,3,2,1,0,99,98,1,0,0,0,100,103,1,
      0,0,0,101,99,1,0,0,0,101,102,1,0,0,0,102,104,1,0,0,0,103,101,1,0,0,
      0,104,105,5,11,0,0,105,17,1,0,0,0,106,107,3,22,11,0,107,108,5,1,0,
      0,108,19,1,0,0,0,109,114,3,22,11,0,110,111,5,2,0,0,111,113,3,22,11,
      0,112,110,1,0,0,0,113,116,1,0,0,0,114,112,1,0,0,0,114,115,1,0,0,0,
      115,21,1,0,0,0,116,114,1,0,0,0,117,118,3,24,12,0,118,23,1,0,0,0,119,
      122,3,26,13,0,120,121,5,12,0,0,121,123,3,24,12,0,122,120,1,0,0,0,122,
      123,1,0,0,0,123,25,1,0,0,0,124,129,3,28,14,0,125,126,5,13,0,0,126,
      128,3,28,14,0,127,125,1,0,0,0,128,131,1,0,0,0,129,127,1,0,0,0,129,
      130,1,0,0,0,130,27,1,0,0,0,131,129,1,0,0,0,132,137,3,30,15,0,133,134,
      5,14,0,0,134,136,3,30,15,0,135,133,1,0,0,0,136,139,1,0,0,0,137,135,
      1,0,0,0,137,138,1,0,0,0,138,29,1,0,0,0,139,137,1,0,0,0,140,145,3,32,
      16,0,141,142,7,0,0,0,142,144,3,32,16,0,143,141,1,0,0,0,144,147,1,0,
      0,0,145,143,1,0,0,0,145,146,1,0,0,0,146,31,1,0,0,0,147,145,1,0,0,0,
      148,153,3,34,17,0,149,150,7,1,0,0,150,152,3,34,17,0,151,149,1,0,0,
      0,152,155,1,0,0,0,153,151,1,0,0,0,153,154,1,0,0,0,154,33,1,0,0,0,155,
      153,1,0,0,0,156,161,3,36,18,0,157,158,7,2,0,0,158,160,3,36,18,0,159,
      157,1,0,0,0,160,163,1,0,0,0,161,159,1,0,0,0,161,162,1,0,0,0,162,35,
      1,0,0,0,163,161,1,0,0,0,164,169,3,38,19,0,165,166,7,3,0,0,166,168,
      3,38,19,0,167,165,1,0,0,0,168,171,1,0,0,0,169,167,1,0,0,0,169,170,
      1,0,0,0,170,37,1,0,0,0,171,169,1,0,0,0,172,173,7,4,0,0,173,176,3,38,
      19,0,174,176,3,40,20,0,175,172,1,0,0,0,175,174,1,0,0,0,176,39,1,0,
      0,0,177,188,5,32,0,0,178,188,5,33,0,0,179,188,5,31,0,0,180,188,5,34,
      0,0,181,188,5,35,0,0,182,188,5,36,0,0,183,184,5,6,0,0,184,185,3,22,
      11,0,185,186,5,7,0,0,186,188,1,0,0,0,187,177,1,0,0,0,187,178,1,0,0,
      0,187,179,1,0,0,0,187,180,1,0,0,0,187,181,1,0,0,0,187,182,1,0,0,0,
      187,183,1,0,0,0,188,41,1,0,0,0,189,190,7,5,0,0,190,43,1,0,0,0,15,47,
      60,71,89,101,114,122,129,137,145,153,161,169,175,187
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