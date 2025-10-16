#include "../s21_decimal.h"

int s21_swap(s21_long_decimal *value_1, s21_long_decimal *value_2) {
  s21_long_decimal dummy;
  int x = 0;

  for (int i = 2; i > -1; i--) {
    if (value_1->bits[i] > value_2->bits[i]) {
      break;
    }
    if (value_2->bits[i] > value_1->bits[i]) {
      dummy = *value_2;
      *value_2 = *value_1;
      *value_1 = dummy;
      x++;
      break;
    }
  }
  return x;
}