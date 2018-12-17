#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "9cc.h"

Token tokens[100];

// pが指している文字列をトークンに分割してtokensに保存する
void tokenize(char *p) {
  int i = 0;
  while (*p) {
    // 空白文字をスキップ
    if (isspace(*p)) {
      p++;
      continue;
    }

    // 追加演算子　＝＝　！＝
    if (*p == '=' || *p == '!') {
      p++;
      if (*p == '=') {
        tokens[i].ty = TK_BIOP;
        tokens[i].input = (p-1);
        p++;
        i++;
        continue;
      }
      p--;
    }

    if (*p == '+' || *p == '-' ||
        *p == '*' || *p == '/' ||
        *p == '(' || *p == ')' ||
        *p == '=' || *p == ';') {
      tokens[i].ty = *p;
      tokens[i].input = p;
      i++;
      p++;
      continue;
    }
    if ('a' <= *p && *p <= 'z') {
      tokens[i].ty = TK_IDENT;
      tokens[i].input = p;
      i++;
      p++;
      continue;
    }
    if (isdigit(*p)) {
      tokens[i].ty = TK_NUM;
      tokens[i].input = p;
      tokens[i].val = strtol(p, &p, 10);
      i++;
      continue;
    }

    fprintf(stderr, "トークナイズできません: %s\n", p);
    exit(1);
  }

  tokens[i].ty = TK_EOF;
  tokens[i].input = p;
/*
  printf("begin ==============================\n" );
  for (int k=0; k <= i; k++) {
    printf("%d: %d: %s\n", tokens[k].ty, tokens[k].val, tokens[k].input);
  }
  printf("end ==============================\n" );
*/
}
