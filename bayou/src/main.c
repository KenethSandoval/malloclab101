#include "../sub/termbox_next/src/termbox.h"
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

  start += len;
  prev_element(bayou, count);
  init_branch(bayou, len, start);

  start += len;
  mh_branch_parent(bayou);
  mh_branch_child(bayou);
  mh_element_set(bayou, count / 2);
  init_branch(bayou, len, start);
}

void rm_branches(struct mh *bayou) {
  mh_branch_root(bayou);
  mh_branch_child(bayou);
  mh_element_set(bayou, 0);
  mh_rm_element(bayou);
  mh_branch_child(bayou);
  mh_branch_child(bayou);
  mh_branch_sibling(bayou);
  mh_element_set(bayou, 0);
  mh_rm_element(bayou);
}

void draw_limits() {
  tb_change_cell(0, 0, limit_left, TB_WHITE, TB_BLACK);
  tb_change_cell(51, 0, limit_right, TB_WHITE, TB_BLACK);

  tb_change_cell(0, 1, limit_left, TB_WHITE, TB_BLACK);
  tb_change_cell(9, 1, limit_right, TB_WHITE, TB_BLACK);
}

bool render_branch(struct mh *bayou, struct mh_branch *selected_branch,
                   void *ptr) {
  for (uint8_t i = 0; i < selected_branch->element_len; i++) {
    tb_change_cell((((uint16_t *)selected_branch->elements) -
                    ((uint16_t *)bayou->pool_elements.buf)) +
                       i + 1,
                   0, slot, TB_WHITE, TB_BLACK);
  }

  tb_change_cell(selected_branch -
                     ((struct mh_branch *)bayou->pool_branches.buf) + 1,
                 1, slot, TB_WHITE, TB_BLACK);

  return true;
}

void draw_tree_mem(struct mh *bayou) {
  draw_limits();
  mh_branch_root(bayou);
  mh_branch_exec(bayou, render_branch, NULL);
}

void defrag_loop(struct mh *bayou) {
  while (mh_should_defrag(bayou)) {
    sleep(1);
    mh_defrag(bayou);

    tb_clear();
    draw_tree_mem(bayou);
    tb_present();
  }
}

int main() {
  struct mh bayou;
  struct mh_hole holes[10];
  struct mh_branch branches[10];
  void *elements[50];

  init_tree(&bayou, holes, branches, elements, 10, 10, 50);

  tb_init();
  tb_clear();
  draw_tree_mem(&bayou);
  tb_present();

  sleep(1);

  rm_branches(&bayou);
  tb_clear();
  draw_tree_mem(&bayou);
  tb_present();

  defrag_loop(&bayou);

  mh_branch_root(&bayou);
  mh_branch_child(&bayou);
  mh_branch_child(&bayou);
  mh_branch_child(&bayou);
  mh_rm_branch(&bayou);

  sleep(1);

  tb_clear();
  draw_tree_mem(&bayou);
  tb_present();

  defrag_loop(&bayou);

  sleep(3);

  tb_shutdown();
  return 0;
}
