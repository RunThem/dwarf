

enum en {
  S_INIT,
  S_START,
  S_END,
};

struct st {
  int nems;
  char* msg;
};

typedef struct {
  int a;
  char c;
} st_t;

void boo() {
  enum en e = S_INIT;
}

void foo() {
  boo();
}

int main(int argc, const char** argv) {
  int a   = 0;
  st_t st = {0};

  struct {
    int d;
    union {
      int l;
      int* ptr;
    };
  } anonymity_st = {0};

  foo();

  return 0;
}
