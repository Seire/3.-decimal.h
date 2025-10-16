#include "../s21_decimal.h"

void s21_normalization(s21_long_decimal *value_1, s21_long_decimal *value_2) {
  int v1_scale, v2_scale, v1_sign, v2_sign, variance;

  v1_sign = s21_get_sign_ldec(*value_1);
  v2_sign = s21_get_sign_ldec(*value_2);

  v1_scale = s21_get_scale_ldec(*value_1);
  v2_scale = s21_get_scale_ldec(*value_2);

  if (v1_scale > v2_scale) {
    variance = v1_scale - v2_scale;
    value_2->bits[7] = (v1_scale << 16) | v2_sign;
    for (int i = 0; i < variance; i++) {
      s21_multiplication_by_ten(value_2);
    }
  }
  if (v1_scale < v2_scale) {
    variance = v2_scale - v1_scale;
    value_1->bits[7] = (v2_scale << 16) | v1_sign;
    for (int i = 0; i < variance; i++) {
      s21_multiplication_by_ten(value_1);
    }
  }
}