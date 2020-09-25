/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TGLTOK.h
 * PURPOSE     : Tough Graphics Language project.
 *               TOK class declaration module.
 * PROGRAMMER  : CGSG'2018.
 * LAST UPDATE : 16.10.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _TGLTOK_H_
#define _TGLTOK_H_

#include <vector>
#include <map>
#include "tglcontainer.h"
#include "tgl.h"

/* TGL namespace */
namespace tgl
{
  // 
  /* TOK class defenition */
  class tok
  {
  public:
    /* TOK type enum */
    enum tok_type
    {
      Name, Number, Operator, KeyWord, Symbol
    } Type;

    // Symbol class
    class symb
    {
    public:
      std::string Symb; // string with symbols of symbols

      /* Default symbol class constructor.
       * ARGUMENTS: None.
       */
      symb( VOID )
      {
      } /* End of 'symb' function */

      /* Symbol class constructor.
       * ARGUMENTS:
       *   - symbols:
       *       std::string Symb;
       */
      symb( std::string Symb ) : Symb(Symb)
      {
      } /* End of 'symb' function */
    }; /* End of 'symb' class */

    // Operator class defenition
    class oper
    {
    public:
      std::string Symbols; // Symbols of operator
      INT Prior;           // Prioritet of operation
      INT NumOfArgs;       // Number of operands
      BOOL IsFunc;         // Function flag

      /* Get arguments for operator poinet on function.
       * ARGUMENTS:
       *   - stack with tokens of arguments for operator:
       *       container::stack<tok> &Stack;
       *   - symbols of operator:
       *       std::string OpSymb;
       *   - map with variables:
       *       std::map<std::string, tok> Variables;
       * RETURNS:
       *   (std::vector<tok>) vector with arguments.
       */
      std::vector<tok> (*GetArgs)( container::stack<tok> &Stack, std::string OpSymb,
        std::map<std::string, tok> &Variables );

      /* Evaluation by operator pointer on function.
       * ARGUMENTS:
       *   - vector with tokens for evaluation:
       *       std::vector<tok> Args;
       *   - map with variables:
       *       std::map<std::string, tok> Variables;
       * RETURNS:
       *  (tok) result of evaluation.
       */
      tok (*Eval)( std::vector<tok> &Args, std::map<std::string, tok> &Variables );

      /* Operator class default constructor.
       * ARGUMENTS: None.
       */
      oper( VOID )
      {
      } /* End of 'oper' function */

      /* Operator class constructor.
       * ARGUMENTS:
       *   - is operator implement function:
       *       BOOL IsFunc;
       *   - number of arguments:
       *       INT NumOfArg;
       *   - prioritet of operator:
       *       INT Prior;
       *   - symbols of operator:
       *       std::string Symbols;
       *   - pointer on function for evaluation:
       *       tok (*Eval)( std::vector<tok> Args, std::map<std::string, tok> Variables );
       */
      oper( BOOL IsFunc, INT NumOfArgs, INT Prior, std::string Symbols,
            tok (*Eval)( std::vector<tok> &Args, std::map<std::string, tok> &Variables))
          : IsFunc(IsFunc), NumOfArgs(NumOfArgs), Prior(Prior), Symbols(Symbols), Eval(Eval)
      {
      } /* End of 'oper' function */
    }; /* End of 'oper' class */

    /* Keywords enum type */
    enum kw_type
    {
      IF, ELSE, WHILE
    };

    // TOK value union
    struct value
    {
      symb Symb;        // Symbol
      kw_type KeyW;     // Key words
      oper Operator;    // Math sign
      std::string Name; // Name
      FLT Num;          // Number

      /* Value union destructor.
       * ARGUMENTS: None.
       */
      ~value( VOID )
      {
      } /* End of '~value' function */
    } Value;

    /* Default tok class constructor.
     * ARGUMENTS: None.
     */
    tok( VOID );

    /* Copy tok class constructor.
     * ARGUMENTS:
     *   - tok for copy:
     *       const tok &T;
     */
    tok( const tok &T );

    /* Class constructor.
     * ARGUMENTS:
     *   - iterator on current char and end of string:
     *       std::string::const_iterator c, end;
     */
    tok( std::string::const_iterator &c, std::string::const_iterator end );
  }; /* End of 'tok' class */
} /* end of 'tgl' namespace */
#endif /* _TGLTOK_H_ */
/* END OF 'TGLTOK.h' FILE */