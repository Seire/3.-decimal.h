#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return 4;

  if (s21_decimal_check(value_1)) return s21_decimal_check(value_1);
  if (s21_decimal_check(value_2)) return s21_decimal_check(value_2);

  s21_long_decimal my_ldec_v1 = s21_conversion_from_dec_to_ldec(value_1);
  s21_long_decimal my_ldec_v2 = s21_conversion_from_dec_to_ldec(value_2);

  s21_normalization(&my_ldec_v1, &my_ldec_v2);

  unsigned int remainder = 0;
  unsigned long int lbits;

  unsigned int sign_v1 = s21_get_sign_ldec(my_ldec_v1) >> 31;
  unsigned int sign_v2 = s21_get_sign_ldec(my_ldec_v2) >> 31;

  if ((sign_v1 && !sign_v2) || (!sign_v1 && sign_v2)) {
    s21_sub_ld(my_ldec_v1, my_ldec_v2, &my_ldec_v1);
  } else {
    for (int i = 0; i < 4; i++) {
      lbits = my_ldec_v1.bits[i];
      my_ldec_v1.bits[i] = lbits + my_ldec_v2.bits[i] + remainder;
      remainder = (lbits + my_ldec_v2.bits[i] + remainder) >> 32;
    }
  }

  int errcode = s21_bank_rounding(&my_ldec_v1);

  if (!errcode) *result = s21_conversion_from_ldec_to_dec(my_ldec_v1);

  return errcode;
}