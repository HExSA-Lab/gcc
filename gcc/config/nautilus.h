/* Useful if you wish to make target-specific gcc changes. */
#undef TARGET_NAUTILUS
#define TARGET_NAUTILUS 1

#undef  CPP_SPEC
#define CPP_SPEC "%(cpp_cpu) %{pthread:-D_REENTRANT}"

#undef LIB_SPEC
#define LIB_SPEC "-lc -lg -lm -lnosys" /* link against C standard library */

/* Switch into a generic section.  */
#define TARGET_ASM_NAMED_SECTION  default_elf_asm_named_section

/* Additional predefined macros. */
#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()      \
  do {                                \
    builtin_define ("__nautilus__");      \
    builtin_define ("__unix__");      \
    builtin_assert ("system=nautilus");   \
    builtin_assert ("system=unix");   \
    builtin_assert ("system=posix");   \
  } while(0);

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crt0.o%s crti.o%s crtbegin.o%s"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"
