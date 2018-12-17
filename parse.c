#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "9cc.h"

// エラーを報告するための関数
void error(char *p, char *input) {
  fprintf(stderr, "%s: %s\n", p, input);
  exit(1);
}

int pos=0;
int line=0;

Node *new_node(int op, Node *lhs, Node *rhs) {
  Node *node = malloc(sizeof(Node));
  node->ty = op;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node *new_node_num(int val) {
  Node *node = malloc(sizeof(Node));
  node->ty = ND_NUM;
  node->val = val;
  return node;
}

Node *new_node_name(char name) {
  Node *node = malloc(sizeof(Node));
  node->ty = ND_IDENT;
  node->name = name;
  return node;
}

Node *new_node_biop(char op, Node *lhs, Node *rhs) {
  Node *node = malloc(sizeof(Node));
  node->ty = ND_BIOP;
  node->name = op;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}


// 関数プロトタイプ宣言
Node *assign(), *expr(), *mul(), *term();

void program() {
  code[line++] = assign();

  if (tokens[pos].ty == TK_EOF) {
    code[line] = NULL;
  } else {
    program();
  }
}

Node *assign() {
  Node *lhs = expr();

  if (tokens[pos].ty == ';') {
    pos++;
//    Node *lhs = assign();
    return lhs;
  }
/*
  if (tokens[pos].ty == TK_BIOP) {
    if (tokens[pos].input[0] == '=') {
      pos++;
      return new_node_biop('=', lhs, expr());
    } else {
      pos++;
      return new_node_biop('!', lhs, expr());
    }
  }
*/
  if (tokens[pos].ty == '=') {
     pos++;
     return new_node('=', lhs, assign());
   }
  return lhs;
}

Node *expr() {
  Node *lhs = mul();

  if (tokens[pos].ty == '+') {
    pos++;
    return new_node('+', lhs, expr());
  }
  if (tokens[pos].ty == '-') {
    pos++;
    return new_node('-', lhs, expr());
  }
  if (tokens[pos].ty == TK_BIOP) {
    if (tokens[pos].input[0] == '=') {
      pos++;
      return new_node_biop('=', lhs, expr());
    } else {
      pos++;
      return new_node_biop('!', lhs, expr());
    }
  }
  return lhs;
}

Node *mul() {
  Node *lhs = term();

  if (tokens[pos].ty == '*') {
    pos++;
    return new_node('*', lhs, mul());
  }
  if (tokens[pos].ty == '/') {
    pos++;
    return new_node('/', lhs, mul());
  }
  return lhs;
}

Node *term() {
  if (tokens[pos].ty == TK_NUM)
    return new_node_num(tokens[pos++].val);
  if (tokens[pos].ty == TK_IDENT)
    return new_node_name(tokens[pos++].input[0]);

  if (tokens[pos].ty == '(') {
    pos++;
    Node *node = expr();
    if (tokens[pos].ty != ')')
      error("開きカッコに対応する閉じカッコがありません:",
            tokens[pos].input);
    pos++;
    return node;
  }
  error("数値でも開きカッコでもないトークンです:",
        tokens[pos].input);
}
