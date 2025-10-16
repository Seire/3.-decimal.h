#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return 4;

  if (s21_decimal_check(value_1)) return s21_decimal_check(value_1);
  if (s21_decimal_check(value_2)) return s21_decimal_check(value_2);

  s21_long_decimal my_ldec_v1 = s21_conversion_from_dec_to_ldec(value_1);
  s21_long_decimal my_ldec_v2 = s21_conversion_from_dec_to_ldec(value_2);
  s21_long_decimal lresult = {0};

  unsigned int sign_v1 = s21_get_sign_ldec(my_ldec_v1) >> 31;
  unsigned int sign_v2 = s21_get_sign_ldec(my_ldec_v2) >> 31;

  lresult.bits[7] = my_ldec_v1.bits[7] + my_ldec_v2.bits[7];

  for (int i = 0; i < 3; i++) {
    for (int i2 = 0; i2 < 32; i2++) {
      if (ACTIVE_FIRST_BIT << i2 & my_ldec_v2.bits[i])
        s21_add_ld(lresult, my_ldec_v1, &lresult);

      s21_left_shift(&my_ldec_v1);
    }
  }

  int errcode = s21_bank_rounding(&lresult);

  if (sign_v1 || sign_v2) lresult.bits[7] = lresult.bits[7] | SIGN_MINUS;
  if (sign_v1 && sign_v2) lresult.bits[7] = lresult.bits[7] << 1 >> 1;

  if (!errcode) {
    *result = s21_conversion_from_ldec_to_dec(lresult);
  } else {
    s21_clear_decimal(result);
  }

  return errcode;
}