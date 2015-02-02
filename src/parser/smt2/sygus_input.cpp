/*********************                                                        */
/*! \file sygus_input.cpp
 ** \verbatim
 ** Original author: Christopher L. Conway
 ** Major contributors: Morgan Deters
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2014  New York University and The University of Iowa
 ** See the file COPYING in the top-level source directory for licensing
 ** information.\endverbatim
 **
 ** \brief [[ Add file-specific comments here ]].
 **
 ** [[ Add file-specific comments here ]]
 **/

#include <antlr3.h>

#include "parser/smt2/sygus_input.h"
#include "expr/expr_manager.h"
#include "parser/input.h"
#include "parser/parser.h"
#include "parser/parser_exception.h"
#include "parser/smt2/sygus_input.h"
#include "parser/smt2/generated/Smt2Lexer.h"
#include "parser/smt2/generated/Smt2Parser.h"

namespace CVC4 {
namespace parser {

/* Use lookahead=2 */
SygusInput::SygusInput(AntlrInputStream& inputStream) :
  AntlrInput(inputStream, 2) {

  pANTLR3_INPUT_STREAM input = inputStream.getAntlr3InputStream();
  assert( input != NULL );

  d_pSmt2Lexer = Smt2LexerNew(input);
  if( d_pSmt2Lexer == NULL ) {
    throw ParserException("Failed to create SMT2 lexer.");
  }

  setAntlr3Lexer( d_pSmt2Lexer->pLexer );

  pANTLR3_COMMON_TOKEN_STREAM tokenStream = getTokenStream();
  assert( tokenStream != NULL );

  d_pSmt2Parser = Smt2ParserNew(tokenStream);
  if( d_pSmt2Parser == NULL ) {
    throw ParserException("Failed to create SMT2 parser.");
  }

  setAntlr3Parser(d_pSmt2Parser->pParser);
}

SygusInput::~SygusInput() {
  d_pSmt2Lexer->free(d_pSmt2Lexer);
  d_pSmt2Parser->free(d_pSmt2Parser);
}

Command* SygusInput::parseCommand() {
  return d_pSmt2Parser->parseSygus(d_pSmt2Parser);
}

Expr SygusInput::parseExpr() {
  return d_pSmt2Parser->parseExpr(d_pSmt2Parser);
}

}/* CVC4::parser namespace */
}/* CVC4 namespace */