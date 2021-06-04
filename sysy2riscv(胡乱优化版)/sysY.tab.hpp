/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_S2E_SYSY_TAB_HPP_INCLUDED
# define YY_S2E_SYSY_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef S2EDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define S2EDEBUG 1
#  else
#   define S2EDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define S2EDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined S2EDEBUG */
#if S2EDEBUG
extern int s2edebug;
#endif

/* Token type.  */
#ifndef S2ETOKENTYPE
# define S2ETOKENTYPE
  enum s2etokentype
  {
    TYPE_INT = 258,
    TYPE_VOID = 259,
    TYPE_CONST = 260,
    MAIN = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    BREAK = 265,
    CONTINUE = 266,
    RETURN = 267,
    LOWER_THAN_ELSE = 268,
    ASSIGN = 269,
    ADD = 270,
    MINUS = 271,
    MUL = 272,
    DIV = 273,
    MOD = 274,
    NOT = 275,
    LESS = 276,
    MORE = 277,
    LEQ = 278,
    GEQ = 279,
    EQUAL = 280,
    AND = 281,
    OR = 282,
    NEQ = 283,
    LPR = 284,
    RPR = 285,
    LBRK = 286,
    RBRK = 287,
    LBRAC = 288,
    RBRAC = 289,
    COMMA = 290,
    SEMCOL = 291,
    INT_CONST = 292,
    ID = 293,
    ERROR = 294
  };
#endif

/* Value type.  */
#if ! defined S2ESTYPE && ! defined S2ESTYPE_IS_DECLARED
typedef int S2ESTYPE;
# define S2ESTYPE_IS_TRIVIAL 1
# define S2ESTYPE_IS_DECLARED 1
#endif


extern S2ESTYPE s2elval;

int s2eparse (void);

#endif /* !YY_S2E_SYSY_TAB_HPP_INCLUDED  */
