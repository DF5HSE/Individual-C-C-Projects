/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TGLLANGCL.h
 * PURPOSE     : Tough Graphics Language project.
 *               Language class declaration module.
 * PROGRAMMER  : CGSG'2018.
 * LAST UPDATE : 21.10.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _TGLLANGCL_H_
#define _TGLLANGCL_H_

#include <map>
#include <string>
#include "tglcontainer.h"
#include "tgltok.h"

/* TGL namespace */
namespace tgl
{
  /* Scanner class declaration */
  class language
  {
  public:
    DBL ResultOfCalc;                     // Result of calculating
    std::map<std::string, tok> Variables; // Map of variables
    container::queue<tok> TokQueue;       // Queue of tokens
    tok TokCurrent;                       // Current tokken
    BOOL IsEOTQ;                          // Flag of end of tokens queue
    container::stack<tok> Stack1, Stack2; // Stack 1 with all and 2 with operators

    /* Language class default constructor.
     * ARGUMENTS: None.
     */
    language( VOID );

    /* Scanner code function.
     * ARGUMENTS:
     *   - string for scanning:
     *       const std::string &Str;
     * RETURNS: None.
     */
    VOID Scanner( const std::string &Str );

    /* Display scanned code function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Display( VOID );

    /* Calculating from code function.
     * ARGUMENTS:
     *   - queue with expression:
     *       container::queue &Expr;
     * RETURNS:
     *   (FLT) result of calculating.
     */
    DBL Calc( container::queue<tok> &Expr );

    /* Check association of operations function.
     * ARGUMENTS:
     *   - operations:
     *       tok::oper Op1, Op2;
     * RETURNS:
     *   (BOOL) if Op1 more prior then Op2 - true, else - false.
     */
     BOOL CheckAssoc( tok::oper Op1, tok::oper Op2 );

    /* Drop operations to stack function.
     * ARGUMENTS:
     *   - operation:
     *       tok::oper Op;
     * RETURNS: None.
     */
    VOID DropOpers( tok::oper Op );

    /* Command class declaration */
    class CMD
    {
    public:
      // Command enum type
      enum cmd_type
      {
        EXPR, IF, WHILE
      };

      cmd_type Type;              // type of command
      container::queue<tok> Expr; // expression, condition for 'if' or 'while'
      CMD
        *C1,                      // 1st command for 'if' or 'while'
        *C2,                      // 2st command for 'else'
        *Next;                    // pointer on next command

      /* Command class default constructor.
       * ARGUMENTS: None.
       */
      CMD( VOID )
      {
      } /* End of 'CMD' function*/

      /* Command class constructor.
       * ARGUMENTS:
       *    - type of command:
       *        cmd_type Type;
       *    - pointer on commands for 'if' (1st and 2nd), 'while' and next command:
       *        CMD C1, C2, Next;
       */
      CMD( cmd_type Type, CMD *C1, CMD *C2, CMD *Next ) : Type(Type), C1(C1), C2(C2), Next(Next)
      {
      } /* End of 'CMD' function */

      /* Command class destructor.
       * ARGUMENTS: None.
       */
      ~CMD( VOID )
      {
        delete C1;
        delete C2;
        delete Next;
      } /* End of '~CMD' function */
    }; /* End of 'CMD' class */

    /* Go to the next token in queue function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Next( VOID )
    {
      if (IsEOTQ)
        throw std::exception("Unexcpected end-of-data\n");
      else
        IsEOTQ = !TokQueue.Get(&TokCurrent);
    } /* End of 'Next' function */

    /* Is current tok any operation function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) true - yes, false - no.
     */
    BOOL IsTokAnyOp( VOID )
    {
      return (!IsEOTQ && TokCurrent.Type == tok::tok_type::Operator);
    } /* End of 'IsTokAnyOp' function */

    /* Is current tok any symbol function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) true - yes, false - no.
     */
    BOOL IsTokAnySym( VOID )
    {
      return (!IsEOTQ && TokCurrent.Type == tok::tok_type::Symbol);
    } /* End of 'IsTokAnySym' function */

    /* Is current tok any number function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) true - yes, false - no.
     */
    BOOL IsTokAnyNum( VOID )
    {
      return (!IsEOTQ && TokCurrent.Type == tok::tok_type::Number);
    } /* End of 'IsTokAnyNum' function */

    /* Is current tok any name function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) true - yes, false - no.
     */
    BOOL IsTokAnyName( VOID )
    {
      return (!IsEOTQ && TokCurrent.Type == tok::tok_type::Name);
    } /* End of 'IsTokAnyName' function */

    /* Is current tok certain operation function.
     * ARGUMENTS:
     *   - symbol of certain operation:
     *       const std::string &OpSym;
     * RETURNS:
     *   (BOOL) true - yes, false - no.
     */
    BOOL IsTokOp( const std::string &OpSym )
    {
      return (IsTokAnyOp() && TokCurrent.Value.Operator.Symbols == OpSym);
    } /* End of 'IsTokOp' function */

    /* Is current tok certain symbol function.
     * ARGUMENTS:
     *   - certain symbol:
     *       tok::symb Sym;
     * RETURNS:
     *   (BOOL) true - yes, false - no.
     */
    BOOL IsTokSym( tok::symb Sym )
    {
      return (IsTokAnySym() && TokCurrent.Value.Symb.Symb == Sym.Symb);
    } /* End of 'IsTokSym' function */

    /* Is current tok certain keyword function.
     * ARGUMENTS:
     *   - certain keyword:
     *       tok::kw_type kw;
     * RETURNS:
     *   (BOOL) true - yes, false - no.
     */
    BOOL IsTokKw( tok::kw_type kw )
    {
      return (!IsEOTQ && TokCurrent.Type == tok::tok_type::KeyWord && TokCurrent.Value.KeyW == kw);
    } /* End of 'IsTokKw' function */

    /* Parse any tok function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
     VOID ParseAnyTok( VOID )
     {
       Next();
     } /* End of 'ParseAnyTok' function */

     /* Parse any operation function.
      * ARGUMENTS: None.
      * RETURNS: None.
      */
     VOID ParseAnyOp( VOID )
     {
       IsTokAnyOp() ? Next() : throw std::exception("Expected any operator\n");
     } /* End of 'ParseAnyOp' function */

     /* Parse certain operation function.
      * ARGUMENTS:
      *   - symbols of certain operation:
      *       const std::string &OpSym;
      * RETURNS: None.
      */
     VOID ParseOp( const std::string &OpSym )
     {
       std::string Error("");
       Error += "Expected operator " + OpSym + "\n";
       IsTokOp(OpSym) ? Next() : throw std::exception(Error.c_str());
     } /* End of 'ParseOp' function */

     /* Parse certain symbol function.
      * ARGUMENTS:
      *   - certain symbol:
      *       tok::symb Sym;
      * RETURNS: None.
      */
     VOID ParseSym( tok::symb Sym )
     {
       std::string Error("");
       Error += "Expected symbol " + Sym.Symb + "\n";
       IsTokSym(Sym) ? Next() : throw std::exception(Error.c_str());
     } /* End of 'ParseSym' function */

    /* Parse number function.
      * ARGUMENTS:
      *   - number to save:
      *       DBL &Num;
      * RETURNS: None.
      */
     VOID ParseNum( DBL &Num )
     {
       std::string Error("");
       Error += "Expected number\n"; /* + std::to_string(Num) */
       IsTokAnyNum() ? Num = TokCurrent.Value.Num, Next() : throw std::exception(Error.c_str());
     } /* End of 'ParseNum' function */

     /* Parse certain keyword function.
      * ARGUMENTS:
      *   - certain keyword:
      *       tok::kw_type Kw;
      * RETURNS: None.
      */
     VOID ParseKw( tok::kw_type Kw )
     {
       std::string Error(""), Kword("");

       Kw == tok::kw_type::WHILE ? Kword = "'while'" :
       Kw == tok::kw_type::IF ? Kword = "'if'" : Kword = "'else'";

       Error += "Expected keyword " + Kword + "\n";
       IsTokKw(Kw) ? Next() : throw std::exception(Error.c_str());
     } /* End of 'ParseKw' function */

     /* Parse name function.
      * ARGUMENTS:
      *   - name:
      *       std::string &Name;
      * RETURNS: None.
      */
     VOID ParseName( std::string &Name )
     {
       IsTokAnyName() ? Name = TokCurrent.Value.Name, Next() : throw std::exception("Expected variable\n");
     } /* End of 'ParseName' function */

     /* Language parse expression function.
      * ARGUMENTS:
      *   - queue of expression:
      *       container::queue<tok> &Expr;
      * RETURNS: None.
      */
     VOID ParseExpr( container::queue<tok> &Expr );

    /* Parse command function.
     * ARGUMENTS:
     *   - pointer on pointer on command:
     *       CMD **C;
     * RETURNS: None.
     */
    VOID ParseCmd( CMD **C );

    /* Parse program function.
     * ARGUMENTS:
     *   - pointer on pointer on start command of program:
     *       CMD **Proga;
     * RETURNS: None.
     */
    VOID ParseProgram( CMD **Proga );

    /* Do commands function.
     * ARGUMENTS:
     *   - pointer on command:
     *       CMD *C;
     * RETURNS: None.
     */
    VOID DoCmd( CMD *C );
  }; /* End of 'language' class */
} /* end of 'tgl' namespace */

#endif /* _TGLLANGCL_H_ */

/* END OF 'TGLLANGCL.h' FILE */