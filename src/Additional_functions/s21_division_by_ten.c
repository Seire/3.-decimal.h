#include "../s21_decimal.h"

int s21_division_by_ten_ldec(s21_long_decimal *value) {
  unsigned long int remainder = 0;
  unsigned long int temp = 0;

  for (int i = 6; i >= 0; i--) {
    temp = (remainder << 32) | value->bits[i];

    remainder = temp % 10;

    value->bits[i] = temp / 10;
  }
  return remainder;
}

int s21_division_by_ten_dec(s21_decimal *value) {
  unsigned long int remainder = 0;
  unsigned long int temp = 0;
  for (int i = 2; i >= 0; i--) {
    temp = ((unsigned long int)remainder << 32) | value->bits[i];

    value->bits[i] = temp / 10;

    remainder = temp % 10;
  }
  return remainder;
}