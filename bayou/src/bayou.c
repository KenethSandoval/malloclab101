#include "bayou.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void *bayou_add_element(struct bayou *bayou) {
  struct bayou_pool *pool_elements = &(bayou->pool_elements);

  if (pool_elements->cur == pool_elements->len) {
    return NULL;
  }

  struct bayou_branch *selected_branch = bayou->selected_branch;
}
