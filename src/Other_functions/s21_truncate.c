#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (!result) {
    res = 1;
  } else if (s21_is_decimal_correct(value)) {
    res = 1;
  } else {
    s21_decimal_union deconstruct;
    for (deconstruct.number = value; deconstruct.parts.exponent > 0;
         deconstruct.parts.exponent--)
      s21_division_by_ten_dec(&deconstruct.number);
    *result = deconstruct.number;
  }

  return res;
}