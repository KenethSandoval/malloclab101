#include <stdint.h>
#include <unistd.h>

uint32_t limit_left = '[';
uint32_t limit_right = ']';
uint32_t slot = 0x2588; // '█'

static void init_branch(struct bayou *bayou, uint16_t len, uint16_t start) {
  uint8_t *el;
  for (uint8_t i = 0; i < len; ++i) {
    el = bayou_add_element(bayou);
  }
}

int main() { return 0; }
