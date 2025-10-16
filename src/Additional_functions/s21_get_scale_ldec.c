#include "../s21_decimal.h"

int s21_get_scale_ldec(s21_long_decimal value) {
  return value.bits[7] << 1 >> 17;
}

int s21_get_scale_dec(s21_decimal value) { return value.bits[3] << 8 >> 24; }