/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TGLTOK.cpp
 * PURPOSE     : Tough Graphics Language project.
 *               TOK class implementation module.
 * PROGRAMMER  : CGSG'2018.
 * LAST UPDATE : 16.10.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "tgltok.h"

/* TGL namespace */
namespace tgl
{
  /* Default tok class constructor.
   * ARGUMENTS: None.
   */
  tok::tok( VOID )
  {
  } /* End of 'tok::tok' function */

  /* Copy tok class constructor.
   * ARGUMENTS:
   *   - tok for copy:
   *       const tok &T;
   */
  tok::tok( const tok &T )
  {
    Type = T.Type;
    Value = T.Value;
  } /* End of 'tok::tok' function */

  /* Class constructor.
   * ARGUMENTS:
   *   - iterator on current char and end of string:
   *       std::string::const_iterator c, end;
   */
  tok::tok( std::string::const_iterator &c, std::string::const_iterator end )
  {
    std::string Simb("");
    BOOL flag = TRUE, ExitFromWhile = FALSE;

    while (flag && c != end && !ExitFromWhile)
      switch (*c)
      {
      case ' ':
        c++;
        continue;
      case '\n':
        c++;
        continue;
      case '\r':
        c++;
        continue;
      case '\t':
        c++;
        continue;
      case '+':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 2, 4, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = V[0].Value.Num + V[1].Value.Num;
          return Res;
        });
        flag = FALSE;
        c++;
        break;
      case '-':;
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 2, 4, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = V[0].Value.Num - V[1].Value.Num;
          return Res;
        });
        flag = FALSE;
        c++;
        break;
      case '*':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 2, 5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = V[0].Value.Num * V[1].Value.Num;
          return Res;
        });
        flag = FALSE;
        c++;
        break;
      case '/':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 2, 5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = V[0].Value.Num / V[1].Value.Num;
          return Res;
        });
        flag = FALSE;
        c++;
        break;
      case '%':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 2, 5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = fmod(V[0].Value.Num, V[1].Value.Num);
          return Res;
        });
        flag = FALSE;
        c++;
        break;
      case '^':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 2, 6, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = pow(V[0].Value.Num, V[1].Value.Num);
          return Res;
        });
        flag = FALSE;
        c++;
        break;
      case '(':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 0, 0, Simb, nullptr);
        flag = FALSE;
        c++;
        break;
      case ')':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 0, 1, Simb, nullptr);
        flag = FALSE;
        c++;
        break;
      case '=':
        if (*(c + 1) != '=')
        {
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 2, 3, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;
          
            Variables[V[0].Value.Name] = V[1];
            Res.Type = tok::tok_type::Number;
            Res.Value.Num = V[1].Value.Num;
            return Res;
          });
          flag = FALSE;
          c++;
        }
        else
        {
          Simb += *c++;
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 2, 2.5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;

            Res.Type = tok::tok_type::Number;
            Res.Value.Num = V[1].Value.Num == V[0].Value.Num;
            return Res;
          });
          flag = FALSE;
          c++;
        }
        break;
      case ',':
        Simb += *c;
        Type = Operator;
        Value.Operator = oper(FALSE, 2, 2, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = V[1].Value.Num;
          return Res;
        });// nullptr);
        flag = FALSE;
        c++;
        break;
      case ';':
        Simb += *c;
        Type = Symbol;
        Value.Symb = symb(Simb);
        flag = FALSE;
        c++;
        break;
      case '{':
        Simb += *c;
        Type = Symbol;
        Value.Symb = symb(Simb);
        flag = FALSE;
        c++;
        break;
      case '}':
        Simb += *c;
        Type = Symbol;
        Value.Symb = symb(Simb);
        flag = FALSE;
        c++;
        break;
      case '!':
        if (*(c + 1) != '=')
        {
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 1, 8, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;

            Res.Type = tok::tok_type::Number;
            Res.Value.Num = !V[0].Value.Num;
            return Res;
          });
          flag = FALSE;
          c++;
        }
        else
        {
          Simb += *c++;
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 2, 2.5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;

            Res.Type = tok::tok_type::Number;
            Res.Value.Num = (V[1].Value.Num != V[0].Value.Num);
            return Res;
          });
          flag = FALSE;
          c++;
        }
        break;
      case '>':
        if (*(c + 1) != '=')
        {
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 2, 2.5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;

            Res.Type = tok::tok_type::Number;
            Res.Value.Num = (V[0].Value.Num > V[1].Value.Num);
            return Res;
          });
          flag = FALSE;
          c++;
        }
        else
        {
          Simb += *c++;
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 2, 2.5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;

            Res.Type = tok::tok_type::Number;
            Res.Value.Num = (V[0].Value.Num >= V[1].Value.Num);
            return Res;
          });
          flag = FALSE;
          c++;
        }
        break;
      case '<':
        if (*(c + 1) != '=')
        {
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 2, 2.5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;

            Res.Type = tok::tok_type::Number;
            Res.Value.Num = (V[0].Value.Num < V[1].Value.Num);
            return Res;
          });
          flag = FALSE;
          c++;
        }
        else
        {
          Simb += *c++;
          Simb += *c;
          Type = Operator;
          Value.Operator = oper(FALSE, 2, 2.5, Simb, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
          {
            tok Res;

            Res.Type = tok::tok_type::Number;
            Res.Value.Num = (V[0].Value.Num <= V[1].Value.Num);
            return Res;
          });
          flag = FALSE;
          c++;
        }
        break;
      default:
        ExitFromWhile = TRUE;
        break;
      }

    if (!flag || c == end)
      return;

    if (*c >= '0' && *c <= '9')
    {
      INT LenOfNum = 0;

      Type = Number;
      while ((c + LenOfNum) != end && *(c + LenOfNum) >= '0' && *(c + LenOfNum) <= '9')
        LenOfNum++;
      Value.Num = 0;
      for (INT i = 1; i <= LenOfNum; i++)
      {
        Value.Num += pow(10, LenOfNum - i) * (*c - '0');
        if (c + 1 != end)
          c++;
        else
        {
          c++;
          return;
        }
      }
      if (*c == '.')
      {
        LenOfNum = -1;
        while (*(c + 1) >= '0' && *(c + 1) <= '9')
        {
          Value.Num += pow(10, (LenOfNum--)) * (*(c + 1) - '0');
          if (c + 2 != end)
            c++;
          else
          {
            c += 2;
            return;
          }
        }
        c++;
      }
      return;
    }

    if ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z') || *c == '_')
    {
      std::string Name("");

      while ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z') || (*c >= '0' && *c <= '9') || *c == '_')
      {
        Name += *(c);
        if (c + 1 != end)
          c++;
        else
        {
          c++;
          break;
        }
      }

      struct
      {
        std::string Name; // keyword string value
        kw_type KeyW;     // keyword constant value
      } Kws[] =
      {
        {"if", IF},
        {"else", ELSE},
        {"while", WHILE}
      };

      for (INT i = 0; i < sizeof(Kws) / sizeof(Kws[0]); i++)
        if (Name == Kws[i].Name)
        {
          Type = KeyWord;
          Value.KeyW = Kws[i].KeyW;
          return;
        }

      if (Name == "sin")
      {
        Type = Operator;
        Value.Operator = oper(TRUE, 1, 7, Name, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = sin(V[0].Value.Num);
          return Res;
        });
        return;
      }
      else if (Name == "cos")
      {
        Type = Operator;
        Value.Operator = oper(TRUE, 1, 7, Name, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
        {
          tok Res;

          Res.Type = tok::tok_type::Number;
          Res.Value.Num = cos(V[0].Value.Num);
          return Res;
        });
        return;
      }
      //else if (Name == "print")
      //{
      //  Type = Operator;
      //  Value.Operator = oper(TRUE, 1, 7, Name, []( std::vector<tok> &V, std::map<std::string, tok> &Variables )->tok
      //  {
      //    tok Res;
      //
      //    Res.Type = tok::tok_type::Number;
      //    Res.Value.Num = cos(V[0].Value.Num);
      //    return Res;
      //  });
      //  return;
      //}
      else
      {
        Value.Name = Name;
        Type = tok_type::Name;
        return;
      }
    }
    std::string Error = "Unexpected simbol " + *c + '\n';
    throw std::exception(Error.c_str());
  } /* End of 'tok::tok' function */
} /* end of 'tgl' namespace */

/* END OF 'TGLTOK.cpp' FILE */
