#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return 4;

  if (s21_decimal_check(value_1)) return s21_decimal_check(value_1);
  if (s21_decimal_check(value_2)) return s21_decimal_check(value_2);

  if (s21_decimal_zero_check(value_2)) {
    *result = value_1;
    return 0;
  }

  s21_long_decimal my_ldec_v1 = s21_conversion_from_dec_to_ldec(value_1);
  s21_long_decimal my_ldec_v2 = s21_conversion_from_dec_to_ldec(value_2);
  s21_long_decimal lresult = {0};

  s21_normalization(&my_ldec_v1, &my_ldec_v2);
  lresult.bits[7] = my_ldec_v1.bits[7];

  int x = s21_swap(&my_ldec_v1, &my_ldec_v2);
  int errcode = 0;

  unsigned int sign_v1 = s21_get_sign_ldec(my_ldec_v1) >> 31;
  unsigned int sign_v2 = s21_get_sign_ldec(my_ldec_v2) >> 31;

  if ((sign_v1 && !sign_v2) || (!sign_v1 && sign_v2)) {
    s21_add_ld(my_ldec_v1, my_ldec_v2, &lresult);
    if (x && (sign_v1 || sign_v2)) {
      s21_negate_ld(lresult, &lresult);
    }
  } else {
    int bit_v1 = 0, bit_v2 = 0, bit_result = 0, memo = 0;

    for (int i = 0; i < 7; i++) {
      for (int i2 = 0; i2 < 32; i2++) {
        bit_v1 = (my_ldec_v1.bits[i] >> i2) & (ACTIVE_FIRST_BIT == 1) ? 1 : 0;
        bit_v2 = (my_ldec_v2.bits[i] >> i2) & (ACTIVE_FIRST_BIT == 1) ? 1 : 0;

        bit_result = bit_v1 - bit_v2 - memo;
        memo = bit_result < 0 ? 1 : 0;
        bit_result = abs(bit_result) == 1 ? 1 : 0;

        s21_set_bit_to_ldec(&lresult, i, i2, bit_result);
      }
    }
    if (x && ((sign_v1 && sign_v2) || (!sign_v1 && !sign_v2))) {
      s21_negate_ld(lresult, &lresult);
    }
  }

  errcode = s21_bank_rounding(&lresult);

  if (!errcode) *result = s21_conversion_from_ldec_to_dec(lresult);

  return errcode;
}