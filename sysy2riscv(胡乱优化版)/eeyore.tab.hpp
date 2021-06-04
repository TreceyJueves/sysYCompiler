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

#ifndef YY_E2T_EEYORE_TAB_HPP_INCLUDED
# define YY_E2T_EEYORE_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef E2TDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define E2TDEBUG 1
#  else
#   define E2TDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define E2TDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined E2TDEBUG */
#if E2TDEBUG
extern int e2tdebug;
#endif

/* Token type.  */
#ifndef E2TTOKENTYPE
# define E2TTOKENTYPE
  enum e2ttokentype
  {
    VAR = 258,
    CALL = 259,
    PARAM = 260,
    RETURN = 261,
    END = 262,
    IF = 263,
    GOTO = 264,
    ENTER = 265,
    VARIABLE = 266,
    FUNC = 267,
    LABEL = 268,
    CONST_INT = 269,
    LBRK = 270,
    RBRK = 271,
    ASSIGN = 272,
    ADD = 273,
    MINUS = 274,
    MUL = 275,
    DIV = 276,
    MOD = 277,
    NOT = 278,
    LESS = 279,
    MORE = 280,
    LEQ = 281,
    GEQ = 282,
    EQUAL = 283,
    AND = 284,
    OR = 285,
    NEQ = 286,
    COL = 287
  };
#endif

/* Value type.  */
#if ! defined E2TSTYPE && ! defined E2TSTYPE_IS_DECLARED
typedef int E2TSTYPE;
# define E2TSTYPE_IS_TRIVIAL 1
# define E2TSTYPE_IS_DECLARED 1
#endif


extern E2TSTYPE e2tlval;

int e2tparse (void);

#endif /* !YY_E2T_EEYORE_TAB_HPP_INCLUDED  */
