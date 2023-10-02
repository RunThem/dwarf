/* clang-format off */
#include <fcntl.h>
#include <string>
#include <typeinfo>

#include <dbg.h>

#include <fmt/core.h>
#include <assert.h>

// #include <lexy/action/parse.hpp>
// #include <lexy/callback.hpp>
// #include <lexy/dsl.hpp>
// #include <lexy/input/argv_input.hpp>
// #include <lexy_ext/report_error.hpp>

#include <libelfin/dwarf/dwarf++.hh>
#include <libelfin/elf/elf++.hh>
#include <libelfin/dwarf/data.hh>
/* clang-format on */

using namespace std;

void dump_enum(const dwarf::die& node) {
  assert(node.tag == dwarf::DW_TAG::enumeration_type);

  fmt::println("static void __dbg_dump_enum_{}(enum {}* _) {{", at_name(node), at_name(node));
  fmt::println("  switch (*_) {{");

  for (auto& child : node) {
    fmt::println(R"(    case {}:
      puts("({}){}"); break;)",
                 at_name(child),
                 at_const_value(child).as_sconstant(),
                 at_name(child));
  }

  fmt::println("    default: break;");
  fmt::println("  }}");
  fmt::println("}}");
}

void dump_struct(const dwarf::die& node) {
  assert(node.tag == dwarf::DW_TAG::structure_type);

  fmt::println("static void __dbg_dump_struct_{}(struct {}* _) {{", at_name(node), at_name(node));



  fmt::println("}}");
}

void foreach_all_die(const dwarf::die& node) {
  switch (node.tag) {
    case dwarf::DW_TAG::enumeration_type:
      dump_enum(node);
      break;
    default:
      break;
  }

  for (auto& child : node) {
    foreach_all_die(child);
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

  auto units = dw.compilation_units();

  for (const auto& cu : units) {
    foreach_all_die(cu.root());
  }

  return 0;
}
