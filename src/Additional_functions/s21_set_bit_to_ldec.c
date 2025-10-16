#include "../s21_decimal.h"

void s21_set_bit_to_ldec(s21_long_decimal *value, int num_e, int num_pos,
                         int bit) {
  value->bits[num_e] = value->bits[num_e] | (bit << num_pos);
}