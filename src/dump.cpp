#include <cinttypes>
#include <fcntl.h>
#include <libelfin/dwarf/dwarf++.hh>
#include <libelfin/elf/elf++.hh>

using namespace std;

void dump_line_table(const dwarf::line_table& lt) {
  for (auto& line : lt) {
    if (line.end_sequence) {
      printf("\n");
    } else {
      printf("%-40s%8d%#20" PRIx64 "\n", line.file->path.c_str(), line.line, line.address);
    }
  }
}

void dump_tree(const dwarf::die& node, int depth = 0) {
  printf("%*.s<%" PRIx64 "> %s\n",
         depth,
         "",
         node.get_section_offset(),
         to_string(node.tag).c_str());

  for (auto& attr : node.attributes())
    printf("%*.s      %s %s\n",
           depth,
           "",
           to_string(attr.first).c_str(),
           to_string(attr.second).c_str());

  for (auto& child : node)
    dump_tree(child, depth + 1);
}

int main(int argc, const char* argv[]) {
  int fd = 0;

  fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
    return -1;
  }

  elf::elf ef(elf::create_mmap_loader(fd));
  dwarf::dwarf dw(dwarf::elf::create_loader(ef));

  // for (const auto& cu : dw.compilation_units()) {
  //   printf("--- <%x>\n", (uint32_t)cu.get_section_offset());

  // dump_line_table(cu.get_line_table());

  // printf("\n");
  // }

#if 1 /* syms */
  for (auto& sec : ef.sections()) {
    if (sec.get_hdr().type != elf::sht::symtab && sec.get_hdr().type != elf::sht::dynsym) {
      continue;
    }

    printf("Symbol table '%s':\n", sec.get_name().c_str());
    printf("%6s: %-16s %-5s %-7s %-7s %-5s %s\n",
           "Num",
           "Value",
           "Size",
           "Type",
           "Binding",
           "Index",
           "Name");

    int i = 0;
    for (auto sym : sec.as_symtab()) {
      auto& d = sym.get_data();
      printf("%6d: %016" PRIx64 " %5" PRId64 " %-7s %-7s %5s %s\n",
             i++,
             d.value,
             d.size,
             to_string(d.type()).c_str(),
             to_string(d.binding()).c_str(),
             to_string(d.shnxd).c_str(),
             sym.get_name().c_str());
    }
  }
#endif

#if 0 /* segments */
  printf("  %-16s  %-16s   %-16s   %s\n", "Type", "Offset", "VirtAddr", "PhysAddr");
  printf("  %-16s  %-16s   %-16s  %6s %5s\n", " ", "FileSiz", "MemSiz", "Flags", "Align");
  for (auto& seg : ef.segments()) {
    auto& hdr = seg.get_hdr();

    printf("   %-16s 0x%016" PRIx64 " 0x%016" PRIx64 " 0x%016" PRIx64 "\n",
           to_string(hdr.type).c_str(),
           hdr.offset,
           hdr.vaddr,
           hdr.paddr);
    printf("   %-16s 0x%016" PRIx64 " 0x%016" PRIx64 " %-5s %-5" PRIx64 "\n",
           "",
           hdr.filesz,
           hdr.memsz,
           to_string(hdr.flags).c_str(),
           hdr.align);
  }
#endif

#if 0 /* tree */
  for (const auto& cu : dw.compilation_units()) {
    printf("--- <%" PRIx64 ">\n", cu.get_section_offset());

    dump_tree(cu.root());
  }
#endif

  return 0;
}
