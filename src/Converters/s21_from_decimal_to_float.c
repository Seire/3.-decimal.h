#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else if (s21_is_decimal_correct(src)) {
    res = 1;
  } else {
    long double tmp = 0.0;
    *dst = 0.0;
    for (int i = 0; i < 96; i++) {
      if (s21_is_bit_set(src, i)) {
        tmp += powl(2.0, i);
      }
    }
    tmp /= powf(10.0, s21_get_scale_dec(src));

    if (s21_get_sign_dec(src)) {
      tmp = -tmp;
    }
    *dst = tmp;
  }
  return res;
}