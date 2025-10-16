#include "../s21_decimal.h"

int decimal_to_int_check(s21_decimal *truncated);

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else if (s21_is_decimal_correct(src)) {
    res = 1;
    *dst = 0;
  } else {
    s21_decimal truncated;
    s21_clear_decimal(&truncated);
    s21_truncate(src, &truncated);
    if (decimal_to_int_check(&truncated)) {
      res = 1;
      *dst = 0;
    } else {
      s21_long_decimal lsrc = s21_conversion_from_dec_to_ldec(src);
      for (unsigned int exp = s21_get_scale_dec(src); exp > 0; exp--) {
        s21_division_by_ten_ldec(&lsrc);
      }

      *dst = lsrc.bits[0];
      if (s21_get_sign_dec(src)) {
        *dst = -(*dst);
      }
    }
  }
  return res;
}

int decimal_to_int_check(s21_decimal *truncated) {
  int res = 0;
  if (truncated->bits[1] || truncated->bits[2]) {
    res = 1;
  }
  if (truncated->bits[0] > 2147483647 + s21_get_sign_dec(*truncated)) {
    res = 1;
  }
  return res;
}