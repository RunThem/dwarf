enum en {
  S_INIT,
  S_START,
  S_END,
};

struct st {
  int nems;
  char* msg;
  enum en e;
};

typedef struct {
  int a;
  char c;

  struct st st;
} st_t;

int main(int argc, const char** argv) {
  struct {
    int d;
    st_t st;
  } anonymity_st = {0};

  return 0;
}
