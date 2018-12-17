// トークンの型を表す値
enum {
  TK_NUM = 256, // 整数トークン
  TK_IDENT,     // 識別子
  TK_BIOP,      //二項演算子
  TK_EOF,       // 入力の終わりを表すトークン
};

enum {
  ND_NUM = 256,
  ND_IDENT,     // 識別子のノードの型
  ND_BIOP,      //二項演算子
};

// トークンの型
typedef struct {
  int ty;      // トークンの型
  int val;     // tyがTK_NUMの場合、その数値
  char *input; // トークン文字列（エラーメッセージ用）
} Token;


// トークナイズした結果のトークン列はこの配列に保存する
// 100個以上のトークンは来ないものとする
extern Token tokens[];


//extern int pos;

typedef struct Node {
  int ty;           // 演算子かND_NUM,ND_BIOP
  struct Node *lhs; // 左辺
  struct Node *rhs; // 右辺
  int val;          // tyがND_NUMの場合のみ使う
  char name;        // tyがND_IDENT,ND_BIOPの場合

extern Node *code[];
