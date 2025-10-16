#include "../s21_decimal.h"

unsigned int s21_get_sign_ldec(s21_long_decimal value) {
  return value.bits[7] >> 31 << 31;
}

unsigned int s21_get_sign_dec(s21_decimal value) { return value.bits[3] >> 31; }