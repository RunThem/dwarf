/* clang-format off */
#include <fcntl.h>
#include <string>
#include <typeinfo>

#include <dbg.h>

#include <fmt/core.h>

#include <lexy/action/parse.hpp>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/argv_input.hpp>
#include <lexy_ext/report_error.hpp>

#include <libelfin/dwarf/dwarf++.hh>
#include <libelfin/elf/elf++.hh>
#include <libelfin/dwarf/data.hh>
/* clang-format on */

using namespace std;

void dump_tree(const dwarf::die& node, int depth = 0) {
  if (node.tag == dwarf::DW_TAG::structure_type) {
    fmt::println("{} <{:x}> {}", depth, node.get_section_offset(), to_string(node.tag));

    auto sib = node[dwarf::DW_AT::sibling];
    fmt::println("sib is <{:x}> {}", sib.get_section_offset(), to_string(sib));

    auto ref = sib.as_reference();
    fmt::println("ref is <{:x}> {}", ref.get_section_offset(), to_string(ref.tag));
  }

  for (auto& child : node) {
    dump_tree(child, depth + 1);
  }
}

int main(int argc, const char* argv[]) {
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

  return 0;
}
