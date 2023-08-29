<p align="center">
<!--
  <a href="https://github.com/RunThem/dwarf/">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
-->

  <h3 align="center">dwarf</h3>
  <p align="center">快速开始你的项目!</p>
</p>
<br />

 熟悉调试数据格式(DWARF)
 
### DWARF
`DWARF` 是一种广泛使用的标准化调试数据格式, 是与 `ELF` 一起设计的, 该名称没有正式的含义, 仅有
"Debugging With Arbitrary Record Formats(使用任意记录格式调试)" 这个非正式含义

编译器产生调试信息(-g)后, 会有一些调试信息加入到可执行文件中, 以 `DWARF` 为例.
```shell
$ objdump -h hello
hello:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
 25 .comment      0000001e  0000000000000000  0000000000000000  00003028  2**0
                  CONTENTS, READONLY
 26 .debug_aranges 00000030  0000000000000000  0000000000000000  00003046  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 27 .debug_info   00000192  0000000000000000  0000000000000000  00003076  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 28 .debug_abbrev 00000133  0000000000000000  0000000000000000  00003208  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 29 .debug_line   00000066  0000000000000000  0000000000000000  0000333b  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 30 .debug_str    000000cf  0000000000000000  0000000000000000  000033a1  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
```

有这以 `debug_` 开头的几个段, 这些就是加入的调试信息了.

还有其他的调试数据格式吗? 有, `STABS`, 古老的格式, `tcc` 产生的调试信息就是这个格式的.

如何查看调试信息呢? 有两种手段, `gcc` vs `llvm`

### GCC
```shell
$ objdump --dwarf=info hello

hello:     file format elf64-x86-64

Contents of the .debug_info section:

  Compilation Unit @ offset 0x0:
   Length:        0x18e (32-bit)
   Version:       4
   Abbrev Offset: 0x0
   Pointer Size:  8
 <2><f2>: Abbrev Number: 7 (DW_TAG_structure_type)
    <f3>   DW_AT_byte_size   : 16
    <f4>   DW_AT_decl_file   : 1
    <f5>   DW_AT_decl_line   : 31
    <f6>   DW_AT_decl_column : 3
    <f7>   DW_AT_sibling     : <0x10d>
 <3><fb>: Abbrev Number: 8 (DW_TAG_member)
    <fc>   DW_AT_name        : d
    <fe>   DW_AT_decl_file   : 1
    <ff>   DW_AT_decl_line   : 32
    <100>   DW_AT_decl_column : 9
    <101>   DW_AT_type        : <0x58>
    <105>   DW_AT_data_member_location: 0
 <3><106>: Abbrev Number: 13 (DW_TAG_member)
    <107>   DW_AT_type        : <0x10d>
    <10b>   DW_AT_data_member_location: 8
 <3><10c>: Abbrev Number: 0
 <2><10d>: Abbrev Number: 14 (DW_TAG_union_type)
    <10e>   DW_AT_byte_size   : 8
    <10f>   DW_AT_decl_file   : 1
    <110>   DW_AT_decl_line   : 33
    <111>   DW_AT_decl_column : 5
    <112>   DW_AT_sibling     : <0x12d>
 <3><116>: Abbrev Number: 15 (DW_TAG_member)
    <117>   DW_AT_name        : l
    <119>   DW_AT_decl_file   : 1
    <11a>   DW_AT_decl_line   : 34
    <11b>   DW_AT_decl_column : 11
    <11c>   DW_AT_type        : <0x58>
 <3><120>: Abbrev Number: 15 (DW_TAG_member)
    <121>   DW_AT_name        : ptr
    <125>   DW_AT_decl_file   : 1
    <126>   DW_AT_decl_line   : 35
    <127>   DW_AT_decl_column : 12
    <128>   DW_AT_type        : <0x149>
```

### LLVM
```shell
$ llvm-dwarfdump hello --debug-info
hello:  file format elf64-x86-64

.debug_info contents:
0x00000000: Compile Unit: length = 0x0000018e, format = DWARF32, version = 0x0004, abbr_offset = 0x0000, addr_size = 0x08 (next unit at 0x00000192)

0x000000f2:     DW_TAG_structure_type
                  DW_AT_byte_size       (0x10)
                  DW_AT_decl_file       ("/home/iccy/dwarf/src/hello.c")
                  DW_AT_decl_line       (31)
                  DW_AT_decl_column     (0x03)
                  DW_AT_sibling (0x0000010d)

0x000000fb:       DW_TAG_member
                    DW_AT_name  ("d")
                    DW_AT_decl_file     ("/home/iccy/dwarf/src/hello.c")
                    DW_AT_decl_line     (32)
                    DW_AT_decl_column   (0x09)
                    DW_AT_type  (0x00000058 "int")
                    DW_AT_data_member_location  (0x00)

0x00000106:       DW_TAG_member
                    DW_AT_type  (0x0000010d "union ")
                    DW_AT_data_member_location  (0x08)

0x0000010c:       NULL

0x0000010d:     DW_TAG_union_type
                  DW_AT_byte_size       (0x08)
                  DW_AT_decl_file       ("/home/iccy/dwarf/src/hello.c")
                  DW_AT_decl_line       (33)
                  DW_AT_decl_column     (0x05)
                  DW_AT_sibling (0x0000012d)

0x00000116:       DW_TAG_member
                    DW_AT_name  ("l")
                    DW_AT_decl_file     ("/home/iccy/dwarf/src/hello.c")
                    DW_AT_decl_line     (34)
                    DW_AT_decl_column   (0x0b)
                    DW_AT_type  (0x00000058 "int")

0x00000120:       DW_TAG_member
                    DW_AT_name  ("ptr")
                    DW_AT_decl_file     ("/home/iccy/dwarf/src/hello.c")
                    DW_AT_decl_line     (35)
                    DW_AT_decl_column   (0x0c)
                    DW_AT_type  (0x00000149 "int *")

```

### 作者

<a href="mailto:iccy.fun@outlook.com">RunThem</a>

### 版权说明

该项目签署了 `MIT` 授权许可, 详情请参阅 [LICENSE](https://github.com/RunThem/dwarf/blob/master/LICENSE)

### 鸣谢

- [xmake](https://github.com/xmake-io/xmake)
- [cc](https://github.com/JacksonAllan/CC)
- [sds](https://github.com/antirez/sds)
- [mimalloc](https://github.com/microsoft/mimalloc)
- [dbg-macro](https://github.com/eerimoq/dbg-macro)
