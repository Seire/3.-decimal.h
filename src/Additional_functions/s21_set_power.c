#include "../s21_decimal.h"

void s21_set_power(s21_decimal *value, int power) {
  s21_decimal_union deconstruct;
  deconstruct.number = *value;
  deconstruct.parts.exponent = power;
  *value = deconstruct.number;
}