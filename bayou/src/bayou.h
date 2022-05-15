// n-tree memory pool
#ifndef H_BAYOU
#define H_BAYOU

#include "def.h"
#include "short.h"

// insert after the currently pointed element
void *bayou_add_element(struct bayou *bayou);

bool bayou_init();

#endif
