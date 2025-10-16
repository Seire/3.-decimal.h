#include "../s21_decimal.h"

int s21_add_ld(s21_long_decimal value_1, s21_long_decimal value_2,
               s21_long_decimal *result) {
  unsigned int remainder = 0;
  unsigned long int lbits;

  for (int i = 0; i < 6; i++) {
    lbits = value_1.bits[i];
    value_1.bits[i] = lbits + value_2.bits[i] + remainder;
    remainder = (lbits + value_2.bits[i] + remainder) >> 32;
  }

  *result = value_1;

  return 0;
}