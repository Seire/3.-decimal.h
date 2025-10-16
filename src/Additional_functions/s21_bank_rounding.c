#include "../s21_decimal.h"

int s21_bank_rounding(s21_long_decimal *value) {
  s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};

  int exp = value->bits[7] << 1 >> 17, remainder = 0, remainder_sum = 0,
      errcode = 0;

  unsigned int sign = s21_get_sign_ldec(*value) >> 31;

  for (int i = 6; i >= 3; i--) {
    while (value->bits[i] != 0) {
      exp -= 1;
      if (exp < 0) {
        i = 0;
        if (sign)
          errcode = 2;
        else
          errcode = 1;
        break;
      }
      remainder = s21_division_by_ten_ldec(value);
      remainder_sum += remainder;
    }
  }

  while (exp > 28) {
    exp -= 1;
    remainder = s21_division_by_ten_ldec(value);
    remainder_sum += remainder;
  }

  if (remainder_sum > remainder && remainder == 5) {
    remainder++;
  }

  if (exp >= 0) {
    value->bits[7] = exp << 16 | (sign << 31);

    if ((value->bits[0] & ACTIVE_FIRST_BIT && remainder == 5) ||
        remainder > 5) {
      s21_add_ld(*value, one, value);
      if (value->bits[3] > 0) {
        errcode = s21_bank_rounding(value);
      }
    }
  }

  return errcode;
}