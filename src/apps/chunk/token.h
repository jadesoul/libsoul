#ifndef TOKEN_H_1357304143_15
#define TOKEN_H_1357304143_15
/**
 * File: token.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-04 20:55:43.151000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "indexer.h"

//a token is the string expression a word
typedef str Token;
typedef uint TokenID;
typedef indexer<Token, TokenID> TokenIndexer;

const Token TOKEN_NULL="<NULL>";
const TokenID TOKEN_ID_NULL=0;

const Token TOKEN_BOS="<BOS>";
const TokenID TOKEN_ID_BOS=1;

const Token TOKEN_BOP="<BOP>";
const TokenID TOKEN_ID_BOP=2;

#endif /* TOKEN_H_1357304143_15 */
