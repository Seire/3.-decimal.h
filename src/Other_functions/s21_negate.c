#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result || s21_is_decimal_correct(value)) {
    return 1;
  }

  unsigned int mask = 1U << 31;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  result->bits[3] ^= mask;
  return 0;
}

int s21_negate_ld(s21_long_decimal value, s21_long_decimal *result) {
  *result = value;

  if (value.bits[7] >= SIGN_MINUS)
    result->bits[7] = value.bits[7] << 1 >> 1;
  else
    result->bits[7] = value.bits[7] | SIGN_MINUS;

  return 0;
}
