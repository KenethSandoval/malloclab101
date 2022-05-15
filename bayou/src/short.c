#include "short.h"
#include "def.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// branches manipulation

bool bayou_branch_parent(struct bayou *bayou) {
  if (bayou->selected_branch->parent != NULL) {
    bayou->selected_branch = bayou->selected_branch->parent;
    return true;
  }
  return false;
}
