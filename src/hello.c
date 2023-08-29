
void boo() {
}

void foo() {
  boo();
}

typedef struct {
  int a;
  char c;
} st_t;

int main(int argc, const char** argv) {
  int a   = 0;
  st_t st = {0};

  foo();

  return 0;
}
