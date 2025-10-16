#include "../s21_decimal.h"

void s21_multiplication_by_ten(s21_long_decimal *value) {
  unsigned int remainder = 0;
  unsigned long int lbits;

  for (int i = 0; i < 7; i++) {
    lbits = value->bits[i];
    value->bits[i] = (lbits << 3) + (lbits << 1) + remainder;
    lbits = (lbits << 3) + (lbits << 1) + remainder;
    remainder = lbits >> 32;
  }
}