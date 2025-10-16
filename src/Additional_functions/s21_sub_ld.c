#include "../s21_decimal.h"

int s21_sub_ld(s21_long_decimal value_1, s21_long_decimal value_2,
               s21_long_decimal *result) {
  // s21_long_decimal dummy;
  s21_long_decimal lresult = {0};

  s21_normalization(&value_1, &value_2);
  lresult.bits[7] = value_1.bits[7];

  int x = s21_swap(&value_1, &value_2);

  unsigned int sign_v1 = s21_get_sign_ldec(value_1) >> 31;
  unsigned int sign_v2 = s21_get_sign_ldec(value_2) >> 31;

  int bit_v1 = 0, bit_v2 = 0, resultx = 0, memo = 0;

  for (int i = 0; i < 7; i++) {
    for (int i2 = 0; i2 < 32; i2++) {
      bit_v1 = (value_1.bits[i] >> i2) & (ACTIVE_FIRST_BIT == 1) ? 1 : 0;
      bit_v2 = (value_2.bits[i] >> i2) & (ACTIVE_FIRST_BIT == 1) ? 1 : 0;

      resultx = bit_v1 - bit_v2 - memo;
      memo = resultx < 0 ? 1 : 0;
      resultx = abs(resultx) == 1 ? 1 : 0;

      s21_set_bit_to_ldec(&lresult, i, i2, resultx);
    }
  }

  if (x && ((sign_v1 && sign_v2) || (!sign_v1 && !sign_v2))) {
    s21_negate_ld(lresult, &lresult);
  }

  *result = lresult;

  return 0;
}