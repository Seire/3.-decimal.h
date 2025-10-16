#include "../s21_decimal.h"

s21_long_decimal s21_conversion_from_dec_to_ldec(s21_decimal value) {
  s21_long_decimal my_ldec;
  my_ldec.bits[0] = value.bits[0];
  my_ldec.bits[1] = value.bits[1];
  my_ldec.bits[2] = value.bits[2];
  my_ldec.bits[3] = 0;
  my_ldec.bits[4] = 0;
  my_ldec.bits[5] = 0;
  my_ldec.bits[6] = 0;
  my_ldec.bits[7] = value.bits[3];
  return my_ldec;
}