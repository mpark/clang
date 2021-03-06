// RUN: %clang_cc1 -x c -triple x86_64-pc-linux-gnu -dwarf-version=4 -fsyntax-only -verify %s

const void *invalid1(const int *arg) {
  return __builtin_preserve_access_index(&arg[1], 1); // expected-error {{too many arguments to function call, expected 1, have 2}}
}

const void *invalid2(const int *arg) {
  return __builtin_preserve_access_index(1); // expected-error {{__builtin_preserve_access_index argument must a pointer type instead of 'int'}}
}

void *invalid3(const int *arg) {
  return __builtin_preserve_access_index(&arg[1]); // expected-warning {{returning 'const int *' from a function with result type 'void *' discards qualifiers}}
}

const void *invalid4(volatile const int *arg) {
  return __builtin_preserve_access_index(arg); // expected-warning {{returning 'const volatile int *' from a function with result type 'const void *' discards qualifiers}}
}

int *valid5(int *arg) {
  return __builtin_preserve_access_index(arg);
}

int valid6(const volatile int *arg) {
  return *__builtin_preserve_access_index(arg);
}

struct s { int a; int b; };

int valid7(struct s *arg) {
  return *__builtin_preserve_access_index(&arg->b);
}
