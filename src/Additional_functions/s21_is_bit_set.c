#include "../s21_decimal.h"

int s21_is_bit_set(s21_decimal value, int ind) {
  return !!(value.bits[ind / 32] & (1U << ind % 32));
}