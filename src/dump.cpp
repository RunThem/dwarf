#include <fcntl.h>
#include <string>
#include <typeinfo>

/* deps */
#include <dbg.h>
#include <fmt/core.h>
#include <lexy/action/parse.hpp>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/argv_input.hpp>
#include <lexy_ext/report_error.hpp>
#include <libelfin/dwarf/dwarf++.hh>
#include <libelfin/elf/elf++.hh>

using namespace std;

void dump_tree(const dwarf::die& node, int depth = 0) {
  if (to_string(node.tag) == "DW_TAG_variable") {
    fmt::println("{}<{}> {}", depth, node.get_section_offset(), to_string(node.tag));

    for (auto& attr : node.attributes()) {
      fmt::println("{}      {} {}",
                   string(depth, ' '),
                   to_string(attr.first),
                   to_string(attr.second));
    }
  }

  for (auto& child : node) {
    dump_tree(child, depth + 1);
  }
}

int main(int argc, const char* argv[]) {
#if 0
  std::int32_t fd = 0;

  fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
    return -1;
  }

  elf::elf ef(elf::create_mmap_loader(fd));
  dwarf::dwarf dw(dwarf::elf::create_loader(ef));

  for (const auto& cu : dw.compilation_units()) {
    fmt::println("--- <{}>", cu.get_section_offset());

    dump_tree(cu.root());
  }
#endif

  return 0;
}
