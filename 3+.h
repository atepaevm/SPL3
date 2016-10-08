#ifndef _ASSEMBLER_GEN_
#define _ASSEMBLER_GEN_


#include <stdint.h>

size_t gen_push_rbp(char* const ptr);
size_t gen_mov_rbp_rsp(char* const ptr);
size_t gen_xor_rax_rax(char* const ptr);
size_t gen_add_rax_rdi(char* const ptr);
size_t gen_add_rax_rdi_offset(char* const ptr,const int a);
size_t gen_mov_rsp_rbp(char* const ptr);
size_t gen_pop_rbp(char* const ptr);
size_t gen_ret(char* const ptr);

#endif