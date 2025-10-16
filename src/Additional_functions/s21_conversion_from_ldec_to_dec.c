#include "../s21_decimal.h"

s21_decimal s21_conversion_from_ldec_to_dec(s21_long_decimal value) {
  s21_decimal my_dec;
  my_dec.bits[0] = value.bits[0];
  my_dec.bits[1] = value.bits[1];
  my_dec.bits[2] = value.bits[2];
  my_dec.bits[3] = value.bits[7];
  return my_dec;
}