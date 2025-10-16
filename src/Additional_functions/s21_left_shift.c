#include "../s21_decimal.h"

void s21_left_shift(s21_long_decimal *value) {
  int dummy[7];

  for (int i = 0; i < 7; i++) {
    dummy[i] = (value->bits[i] & SIGN_MINUS) >> 31;
    value->bits[i] = value->bits[i] << 1;
  }

  for (int i = 1, i2 = 0; i < 7; i++, i2++) {
    value->bits[i] = value->bits[i] | dummy[i2];
  }
}

void s21_right_shift(s21_long_decimal *value) {
  int dummy[7];

  for (int i = 6; i >= 0; i--) {
    dummy[i] = (value->bits[i] & ACTIVE_FIRST_BIT) << 31;
    value->bits[i] = value->bits[i] >> 1;
  }

  for (int i = 5, i2 = 6; i >= 0; i--, i2--) {
    value->bits[i] = value->bits[i] | dummy[i2];
  }
}