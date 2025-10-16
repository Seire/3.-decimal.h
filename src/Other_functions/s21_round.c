#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (!result) {
    res = 1;
  } else if (s21_is_decimal_correct(value)) {
    res = 1;
  } else {
    s21_decimal truncated_val, fractional_part, zerofive;
    s21_clear_decimal(&truncated_val);
    s21_clear_decimal(&fractional_part);
    s21_truncate(value, &truncated_val);
    s21_sub(value, truncated_val, &fractional_part);
    s21_from_int_to_decimal(5, &zerofive);
    s21_set_power(&zerofive, 1);
    if (s21_get_sign_dec(fractional_part)) {
      s21_negate(fractional_part, &fractional_part);
    }
    if (s21_is_greater_or_equal(fractional_part, zerofive)) {
      s21_add_one(&truncated_val);
    }

    *result = truncated_val;
  }
  return res;
}