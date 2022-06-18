#include <memoryhandles/mh.h>
#include <stdint.h>
#include <unistd.h>

uint32_t limit_left = '[';
uint32_t limit_right = ']';
uint32_t slot = 0x2588; // '█'

static void prev_element(struct mh *bayou, uint16_t count) {
  for (uint16_t i = 0; i < count; ++i) {
    mh_element_prev(bayou);
  }
}

static void init_branch(struct mh *bayou, uint16_t len, uint16_t start) {
  uint8_t *el;
  for (uint8_t i = 0; i < len; ++i) {
    el = mh_add_element(bayou);

    if (el != NULL) {
      *((uint16_t *)el) = i + start;
    }
  }
}

static void init_tree(struct mh *bayou, struct mh_hole *holes,
                      struct mh_branch *branches, void **elements,
                      uint16_t holes_len, uint16_t branches_len,
                      uint16_t elements_len) {

  mh_init(bayou, branches, branches_len, 10, branches_len, elements,
          elements_len, 20, elements_len, sizeof(uint16_t), holes, holes_len,
          30, holes_len);

  uint16_t start = 0;
  const uint16_t len = 10;
  const uint16_t count = 5;

  init_branch(bayou, len, start);

  start += len;
  prev_element(bayou, count);
  init_branch(bayou, len, start);

  start += len;
  mh_branch_parent(bayou);
  mh_branch_child(bayou);
  mh_element_set(bayou, count / 2);
  init_branch(bayou, len, start);
}

int main() { return 0; }
