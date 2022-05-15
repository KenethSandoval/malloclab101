#ifndef C_TESTS
#define C_TESTS

#include "../src/bayou.h"
#include "../sub/testoasterror/src/testoasterror.h"
#include <signal.h>
#include <stdio.h>

static void prev_element(struct bayou *bayou, uint16_t count) {
  for (uint16_t i = 0; i < count; ++i) {
    bayou_element_prev(bayou);
  }
}

#endif
