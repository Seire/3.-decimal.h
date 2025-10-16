#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  if (s21_is_decimal_correct(value1) || s21_is_decimal_correct(value2)) {
    return -1;
  }
  s21_long_decimal lvalue1 = s21_conversion_from_dec_to_ldec(value1);
  s21_long_decimal lvalue2 = s21_conversion_from_dec_to_ldec(value2);
  s21_normalization(&lvalue1, &lvalue2);
  int res = 1;
  res = s21_compare(lvalue1, lvalue2);
  if (res != 1) {
    res = 0;
  }
  return res;
}

int s21_is_greater_ld(s21_long_decimal value1, s21_long_decimal value2) {
  // s21_normalization(&value1, &value2);
  int res = 1;
  res = s21_compare(value1, value2);
  if (res != 1) {
    res = 0;
  }
  return res;
}