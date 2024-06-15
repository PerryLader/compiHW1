%{
/* Declaration Section */
#include "tokens.hpp"
#include <stdio.h>
%}

%option yylineno
%option noyywrap
%x STR

letter           ([A-Za-z])

hex              (x[0-7][0-9a-fA-F])
digitnozero      ([1-9])
whitespace       ([\n\t\r ])
escape           ([\\ntr\"0])
string           ([ !\]-~#-\[	])
digit            ([0-9])
digithex         ([0-9a-fA-F])
stringprefix     ({string}|\\{hex}|\\{escape})


%%
int                                                                                 return INT;
byte                                                                                return BYTE;
b                                                                                   return B;
bool                                                                                return BOOL;
and                                                                                 return AND;
or                                                                                  return OR;
not                                                                                 return NOT;
true                                                                                return TRUE;
false                                                                               return FALSE;
return                                                                              return RETURN;
if                                                                                  return IF;
else                                                                                return ELSE;
while                                                                               return WHILE;
break                                                                               return BREAK;
continue                                                                            return CONTINUE;
;                                                                                   return SC;
\(                                                                                  return LPAREN;
\)                                                                                  return RPAREN;
\{                                                                                  return LBRACE;
\}                                                                                  return RBRACE;
=                                                                                   return ASSIGN;
[<!=>]=|>|<                                                                         return RELOP;
[*-/+]                                                                              return BINOP;
\/\/[^\n\r]*                                                                        return COMMENT;
{letter}[a-zA-Z0-9]*                                                                return ID;
({digitnozero}+{digit}*)|0                                                          return NUM;
(0+{digitnozero}+)											                        return ERROR;
\"{stringprefix}*\"                                                                 return STRING;
\"{stringprefix}*                                                                   return UNCLOSED_STR;
\"{stringprefix}*\\[^{escape}]                                                      return INV_ESC;
\"{stringprefix}*\\x([^{digithex}]|[^0-7][^{digithex}]|[0-7][^{digithex}]|[^0-7][{digithex}]) return INV_HEX;
{whitespace}                                                                        ;
.                                                                                   return ERROR;
