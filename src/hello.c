#include <stdio.h>

// typedef enum en en_e;
// enum en {
//   S_INIT,
//   S_START,
//   S_END,
// };

// static void _dbg_dump_enum_en(enum en* _) {
//   switch (*_) {
//     case S_INIT:
//       puts("(0)S_INIT");
//       break;
//     case S_START:
//       puts("(1)S_START");
//       break;
//     case S_END:
//       puts("(2)S_END");
//       break;
//     default:
//       break;
//   }
// }

struct st {
  int nems;
  char* msg;
};

typedef struct {
  int a;
  char c;

  struct st st;
} st_t;

int main(int argc, const char** argv) {
  // struct {
  //   int d;
  //   char c;
  // } arr[5] = {0};
  //

  st_t st = {0};

  //
  //  enum en e = S_INIT;
  //  en_e _e   = S_END;
  //
  //  _dbg_dump_enum_en(&e);
  //  _dbg_dump_enum_en(&_e);

  return 0;
}
