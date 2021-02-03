/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TGLLANGCL.cpp
 * PURPOSE     : Tough Graphics Language project.
 *               Language class implementation module.
 * PROGRAMMER  : CGSG'2018.
 * LAST UPDATE : 21.10.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <algorithm>
#include "tgllangcl.h"


/* TGL namespace */
namespace tgl
{
  /* Language class default constructor.
  * ARGUMENTS: None.
  */
  language::language( VOID )
  {
  } /* End of 'language::language' function */

  /* Scanner code function.
   * ARGUMENTS:
   *   - string for scanning:
   *       const std::string &Str;
   * RETURNS: None.
   */
  VOID language::Scanner( const std::string &Str )
  {
    auto c = Str.begin();
    while (c < Str.end())
    {
      tok Data(c, Str.end());
      TokQueue.Put(Data);
    }
  } /* End of 'language::Scanner' function */

  /* Display scanned code function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID language::Display( VOID )
  {
    container::queue<tok>::queue_entry *tmp = TokQueue.Start;

    while (tmp != nullptr)
    {
      if (tmp->Data.Type == tok::tok_type::Name)
        std::cout << tmp->Data.Value.Name.c_str() << " ";
      else if (tmp->Data.Type == tok::tok_type::Number)
        std::cout << tmp->Data.Value.Num << " ";
      else if (tmp->Data.Type == tok::tok_type::Operator)
        std::cout << tmp->Data.Value.Operator.Symbols << " ";
      tmp = tmp->Next;
    }
  } /* End of 'language::Display' function */

  /* Calculating from code function.
   * ARGUMENTS:
   *   - queue with expression:
   *       container::queue &Expr;
   * RETURNS:
   *   (FLT) result of calculating.
   */
  DBL language::Calc( container::queue<tok> &Expr )
  {
    container::stack<tok> Stack;
    container::queue<tok>::queue_entry *Start = Expr.Start;
    tok Get, Res, n;

    while (Start != nullptr)
    {
      Get = Start->Data;

      if (Get.Type == tok::tok_type::Number || Get.Type == tok::tok_type::Name)
        Stack.Push(Get);
      else
      {
        std::vector<tok> Args;
        for (INT i = 0; i < Get.Value.Operator.NumOfArgs; i++)
        {
          if (!Stack.Pop(&n))
          {
            std::string Error = "Wrong number of arguments" + '\n';
            throw std::exception(Error.c_str());
          }
          else
            if (n.Type == tok::tok_type::Name && !(i == Get.Value.Operator.NumOfArgs - 1 &&
                                                  Get.Value.Operator.Symbols == "="))
              if (Variables.find(n.Value.Name) != Variables.end())
                n.Value.Num = Variables[n.Value.Name].Value.Num;
              else
              {
                std::string Error = "Undefined variable " + std::string(n.Value.Name) + '\n';
                throw std::exception(Error.c_str());
              }
          Args.push_back(n);
        }
        std::vector<tok> Args1;
        std::reverse(Args.begin(), Args.end());

        Res = Get.Value.Operator.Eval(Args, Variables);
        Stack.Push(Res);
        Args.clear();
      }
      Start = Start->Next;
    }

    if (Stack.Start != nullptr)
      Res.Value.Num = Stack.Start->Data.Value.Num;
    return Res.Value.Num;
  } /* End of 'language::Calc' function */

  /* Check association of operations function.
   * ARGUMENTS:
   *   - operations:
   *       tok::oper Op1, Op2;
   * RETURNS:
   *   (BOOL) if Op1 more prior then Op2 - true, else - false.
   */
  BOOL language::CheckAssoc( tok::oper Op1, tok::oper Op2 )
  {
    INT P1 = Op1.Prior, P2 = Op2.Prior;

    if (Op2.Symbols == "=")
      return P1 > P2;
    return P1 >= P2;
  } /* End of 'language::CheckAssoc' function */

  /* Drop operations to stack function.
   * ARGUMENTS:
   *   - operation:
   *       tok::oper Op;
   * RETURNS: None.
   */
  VOID language::DropOpers( tok::oper Op )
  {
    while (Stack2.Start != nullptr &&
           CheckAssoc(Stack2.Start->Data.Value.Operator, Op))
    {
      tok T;

      Stack2.Pop(&T);
      Stack1.Push(T);
    }
  } /* End of 'language::DropOpers' function */

  /* Language parse expression function.
   * ARGUMENTS:
   *   - queue of expression:
   *       container::queue<tok> &Expr;
   * RETURNS: None.
   */
  VOID language::ParseExpr( container::queue<tok> &Expr )
  {
    BOOL IsFuncPrev = FALSE, IsFirstTok = TRUE;
    tok T;

    enum
    {
      Prefix, Suffix, Done, End
    } state = Prefix;

    while (state != End)
    {
      if (state <= Suffix)
        if (!IsFirstTok)
        {
         if (!TokQueue.Watch(&T))
           if (state == Suffix)
             state = Done;
           else
             throw std::exception("Unexpected end of expression\n");
        }
        else
          T = TokCurrent;

      switch (state)
      {
      case Prefix:
        if (IsFuncPrev && (T.Type != tok::tok_type::Operator || T.Value.Operator.Symbols != "("))
          throw std::exception("Expect '(' \n");
        else
        {
          IsFuncPrev = FALSE;
          if (T.Type == tok::tok_type::Number)
          {
            Stack1.Push(T);
            state = Suffix;
          }
          else if (T.Type == tok::tok_type::Name)
          {
            Stack1.Push(T);
            state = Suffix;
          }
          else if (T.Type == tok::tok_type::Operator && T.Value.Operator.Symbols == "(")
            Stack2.Push(T);
          else if (T.Type == tok::tok_type::Operator && T.Value.Operator.Symbols == "!")
            Stack2.Push(T);
          else if (T.Type == tok::tok_type::Operator && T.Value.Operator.Symbols == "-")
          {
            T.Value.Operator = tok::oper(FALSE, 1, 7, "@", []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
            {
              tok Res;
          
              Res.Type = tok::tok_type::Number;
              Res.Value.Num = -V[0].Value.Num;
              return Res;
            });
            Stack2.Push(T);
          }
          else if (T.Type == tok::tok_type::Operator && T.Value.Operator.IsFunc)
          {
            IsFuncPrev = TRUE;
            Stack2.Push(T);
          }
          else
            throw std::exception("Expect number or '(' \n");
        }
        if (!IsFirstTok)
          Next();
        else
          IsFirstTok = FALSE;
        break;
      case Done:
        DropOpers(tok::oper(FALSE, 0, 1, ")", nullptr));
        if (Stack2.Start != nullptr)
          throw std::exception("Expect ')'\n");
        Next();
        state = End;
        break;
      case Suffix:
        if (T.Type == tok::tok_type::Operator && T.Value.Operator.Symbols == ")")
        {
          DropOpers(tok::oper(FALSE, 0, 1, ")", nullptr));
          if (!Stack2.Pop(nullptr))
            state = Done; //throw std::exception("Expect ')'\n");
          else
            Next();
        }
        else if (T.Type == tok::tok_type::Operator)
        {
          DropOpers(T.Value.Operator);
          Stack2.Push(T);
          state = Prefix;
          Next();
        }
        else
          state = Done; //throw std::exception("Expect ')'\n");
        break;
      }
    }

    container::stack<tok> St;

    while (Stack1.Pop(&T))
      St.Push(T);
    while (St.Pop(&T))
      Expr.Put(T); // TokQueue.Put(T);
  } /* End of 'language::Parser' function */

  /* Parse command function.
   * ARGUMENTS:
   *   - pointer on pointer on command:
   *       CMD **C;
   * RETURNS: None.
   */
  VOID language::ParseCmd( CMD **C )
  {
    *C = nullptr;

    if (IsTokKw(tok::IF))
    {
      *C = new CMD(CMD::IF, nullptr, nullptr, nullptr);
      ParseKw(tok::IF);
      ParseOp("(");
      ParseExpr((*C)->Expr);
      ParseOp(")");
      ParseCmd(&(*C)->C1);
      if (IsTokKw(tok::ELSE))
      {
        ParseKw(tok::ELSE);
        ParseCmd(&(*C)->C2);
      }
    }
    else if (IsTokKw(tok::WHILE))
    {
      *C = new CMD(CMD::WHILE, nullptr, nullptr, nullptr);
      ParseKw(tok::WHILE);
      ParseOp("(");
      ParseExpr((*C)->Expr);
      ParseOp(")");
      ParseCmd(&(*C)->C1);
    }
    else if (IsTokSym(tok::symb("{")))
    {
      ParseSym(tok::symb("{"));
      while(!IsTokSym(tok::symb("}")))
      {
        ParseCmd(C);
        C = &(*C)->Next;
      }
      ParseSym(tok::symb("}"));
    }
    else
    {
      *C = new CMD(CMD::EXPR, nullptr, nullptr, nullptr);
      ParseExpr((*C)->Expr);
      ParseSym(tok::symb(";"));
    }
  } /* End of 'language::ParseCmd' function */

  /* Parse program function.
   * ARGUMENTS:
   *   - pointer on pointer on start command of program:
   *       CMD **Proga;
   * RETURNS: None.
   */
  VOID language::ParseProgram( CMD **Proga )
  {
    CMD **cmd = Proga;

    Next();
    while (!IsEOTQ)
    {
      language::ParseCmd(cmd);
      cmd = &(*cmd)->Next;
    }
  } /* End of 'language::ParseProgram' function */

  /* Do commands function.
   * ARGUMENTS:
   *   - pointer on command:
   *       CMD *C;
   * RETURNS: None.
   */
  VOID language::DoCmd( CMD *C )
  {
    while (C != nullptr)
    {
      if (C->Type == language::CMD::EXPR)
        ResultOfCalc = Calc(C->Expr);
      else if (C->Type == language::CMD::IF)
        if (Calc(C->Expr))
          DoCmd(C->C1);
        else
          DoCmd(C->C2);
      else if (C->Type == language::CMD::WHILE)
        while (Calc(C->Expr))
          DoCmd(C->C1);
      C = C->Next;
    }
  } /* End of 'language::DoCmd' function */
} /* end of 'tgl' namespace */

/* END OF 'TGLSCANNER.CPP' FILE */
