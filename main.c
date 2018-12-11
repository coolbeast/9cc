#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "9cc.h"

// 関数プロトタイプ宣言
Node *mul(), *term();

void program();

// pが指している文字列をトークンに分割してtokensに保存する
void tokenize();

//int pos=0;

void gen();

Node *code[100];

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }

  // トークナイズしてパースする
  tokenize(argv[1]);

  program();

  // アセンブリの前半部分を出力する
  printf(".intel_syntax noprefix\n");
  printf(".global _main\n");
  printf("_main:\n");

  // プロローグ
  // 変数26個分の領域を確保する
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, 208\n");

  // 先頭の式から順にコード生成
  for (int i=0; code[i]; i++) {
    //    printf("===> %d\n", i);
    gen(code[i]);
    //　式の評価結果としてスタックに弼の値が残っているはずなので、
    //  スタックが盛れないよにポップしておく
    printf("  pop rax\n");
  }
  // エピローグ
  // スタックトップに式全体の値が残っているはずなので
  // それをRAXにロードして関数からの返り値とする
  printf("  mov rsp, rbp\n" );
  printf("  pop rbp\n");
  printf("  ret\n");

  return 0;

}
