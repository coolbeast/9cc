#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "9cc.h"

// トークンの型を表す値

void gen_lval(Node *node) {
  if (node->ty == ND_IDENT) {
   printf("  mov rax, rbp\n");
   printf("  sub rax, %d\n",
          ('z' - node->name + 1) * 8);
   printf("  push rax\n");
   return;
 }
 error("代入の左辺値が変数ではありません",&node->name);
}
void gen(Node *node) {
  if (node->ty == ND_NUM) {
    printf("  push %d\n", node->val);
    return;
  }

  if (node->ty == ND_IDENT) {
    gen_lval(node);
    printf("  POP rax\n");
    printf("  mov rax, [rax]\n");
    printf("  push rax\n");
    return;
  }
/*
  if (node->ty == ND_BIOP && node->name == '=') {
  //  gen_lval(node->lhs);
    gen(node->rhs);

    printf("  POP rax\n");
    printf("  POP rdi\n");
    printf("  cmp rdi, rax\n");
    printf("  sete al\n");
    printf("  movzx rax, al\n");
    printf("  push rax\n");
    return;
  }
  if (node->ty == ND_BIOP && node->name == '!') {
  //  gen_lval(node->lhs);
    gen(node->rhs);

    printf("  POP rax\n");
    printf("  POP rdi\n");
    printf("  cmp rdi, rax\n");
    printf("  setne al\n");
    printf("  movzx rax, al\n");
    printf("  push rax\n");
    return;
  }
*/
  if (node->ty == '=') {
    gen_lval(node->lhs);
    gen(node->rhs);

    printf("  POP rdi\n");
    printf("  POP rax\n");
    printf("  mov [rax], rdi\n");
    printf("  push rdi\n");
    return;
  }

  gen(node->lhs);
  gen(node->rhs);

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->ty) {
  case '+':
    printf("  add rax, rdi\n");
    break;
  case '-':
    printf("  sub rax, rdi\n");
    break;
  case '*':
    printf("  mul rdi\n");
    break;
  case '/':
    printf("  mov rdx, 0\n");
    printf("  div rdi\n");
  }

  if (node->ty == ND_BIOP && node->name == '=') {
  //  gen_lval(node->lhs);
//    gen(node->rhs);

//    printf("  POP rax\n");
//    printf("  POP rdi\n");
    printf("  cmp rdi, rax\n");
    printf("  sete al\n");
    printf("  movzx rax, al\n");
//    printf("  push rax\n");
//    return;
  }
  if (node->ty == ND_BIOP && node->name == '!') {
  //  gen_lval(node->lhs);
//    gen(node->rhs);

//    printf("  POP rax\n");
//    printf("  POP rdi\n");
    printf("  cmp rdi, rax\n");
    printf("  setne al\n");
    printf("  movzx rax, al\n");
//    printf("  push rax\n");
//    return;
  }


  printf("  push rax\n");
}
