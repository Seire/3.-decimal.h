#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else {
    s21_clear_decimal(dst);
    if (src < 0) {
      s21_negate(*dst, dst);
      src = ~src + 1;
    }
    dst->bits[0] = src;
  }
  return res;
}