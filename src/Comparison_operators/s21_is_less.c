#include "../s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  if (s21_is_decimal_correct(value1) || s21_is_decimal_correct(value2)) {
    return -1;
  }
  s21_long_decimal lvalue1 = s21_conversion_from_dec_to_ldec(value1);
  s21_long_decimal lvalue2 = s21_conversion_from_dec_to_ldec(value2);
  s21_normalization(&lvalue1, &lvalue2);
  int res = 1;
  if (s21_compare(lvalue1, lvalue2) != 2) {
    res = 0;
  }
  return res;
}