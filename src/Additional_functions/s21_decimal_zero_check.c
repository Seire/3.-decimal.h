#include "../s21_decimal.h"

int s21_decimal_zero_check(s21_decimal value) {
  int i2 = 0, exit = 0;

  for (int i = 0; i < 3; i++) {
    if (value.bits[i] == 0) i2++;
  }
  if (i2 == 3) {
    exit = 1;
  }
  return exit;
}