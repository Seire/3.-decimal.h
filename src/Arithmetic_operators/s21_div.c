#include "../s21_decimal.h"

void s21_integer_division(s21_long_decimal *my_ldec_v1,
                          s21_long_decimal *my_ldec_v2,
                          s21_long_decimal *lresult);
void s21_residue_division(s21_long_decimal *my_ldec_v1,
                          s21_long_decimal *my_ldec_v2,
                          s21_long_decimal *lresult, int *scale_res);
int s21_search_first_high_bit(s21_long_decimal *my_ldec_v1);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return 4;

  if (s21_decimal_check(value_1)) return s21_decimal_check(value_1);
  if (s21_decimal_check(value_2)) return s21_decimal_check(value_2);

  if (s21_decimal_zero_check(value_2)) return 3;

  s21_long_decimal my_ldec_v1 = s21_conversion_from_dec_to_ldec(value_1);
  s21_long_decimal my_ldec_v2 = s21_conversion_from_dec_to_ldec(value_2);
  s21_long_decimal lresult = {0};

  int scale_v1 = s21_get_scale_ldec(my_ldec_v1),
      scale_v2 = s21_get_scale_ldec(my_ldec_v2),
      scale_res = scale_v1 - scale_v2,

      errcode = 0,

      sign = ((int)my_ldec_v1.bits[7] * (int)my_ldec_v2.bits[7]) >> 31;

  my_ldec_v1.bits[7] = 0;
  my_ldec_v2.bits[7] = 0;

  s21_integer_division(&my_ldec_v1, &my_ldec_v2, &lresult);

  s21_residue_division(&my_ldec_v1, &my_ldec_v2, &lresult, &scale_res);

  while (scale_res < 0) {
    scale_res++;
    s21_multiplication_by_ten(&lresult);
  }

  lresult.bits[7] = (scale_res << 16) | sign;

  errcode = s21_bank_rounding(&lresult);
  if (!errcode) *result = s21_conversion_from_ldec_to_dec(lresult);

  return errcode;
}

void s21_integer_division(s21_long_decimal *my_ldec_v1,
                          s21_long_decimal *my_ldec_v2,
                          s21_long_decimal *lresult) {
  s21_long_decimal my_dummy_v2 = *my_ldec_v2;
  s21_long_decimal result = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal result_one = {{1, 0, 0, 0, 0, 0, 0, 0}};

  int pointer_v1 = 0, pointer_v2 = 0, difference = 0;

  while (s21_is_greater_or_equal_ld(*my_ldec_v1, *my_ldec_v2)) {
    pointer_v1 = s21_search_first_high_bit(my_ldec_v1);
    pointer_v2 = s21_search_first_high_bit(my_ldec_v2);

    difference = pointer_v1 - pointer_v2;

    for (int x4 = difference; x4 > 0; x4--) {
      s21_left_shift(my_ldec_v2);
    }

    if (s21_is_greater_ld(*my_ldec_v2, *my_ldec_v1)) {
      difference--;
      s21_right_shift(my_ldec_v2);
    }

    s21_sub_ld(*my_ldec_v1, *my_ldec_v2, my_ldec_v1);

    for (; difference != 0; difference--) {
      s21_left_shift(&result);
    }

    s21_add_ld(*lresult, result, lresult);

    result = result_one;
    *my_ldec_v2 = my_dummy_v2;
  }
}

void s21_residue_division(s21_long_decimal *my_ldec_v1,
                          s21_long_decimal *my_ldec_v2,
                          s21_long_decimal *lresult, int *scale_res) {
  s21_long_decimal my_dummy_v2 = *my_ldec_v2;
  s21_long_decimal result = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal result_one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal dec_zero = {0};

  int pointer_v1 = 0, pointer_v2 = 0, difference = 0;

  int exit_residue_d = 0;

  while (s21_is_equal_ld(*my_ldec_v1, dec_zero) != 1 && lresult->bits[6] == 0) {
    s21_multiplication_by_ten(my_ldec_v1);

    *scale_res += 1;

    if (s21_is_greater_or_equal_ld(*my_ldec_v1, *my_ldec_v2)) {
      s21_multiplication_by_ten(lresult);
    }

    while (s21_is_greater_or_equal_ld(*my_ldec_v1, *my_ldec_v2)) {
      pointer_v1 = s21_search_first_high_bit(my_ldec_v1);
      pointer_v2 = s21_search_first_high_bit(my_ldec_v2);

      difference = pointer_v1 - pointer_v2;

      for (int x4 = difference; x4 > 0; x4--) {
        s21_left_shift(my_ldec_v2);
      }

      if (s21_is_greater_ld(*my_ldec_v2, *my_ldec_v1)) {
        difference--;
        s21_right_shift(my_ldec_v2);
      }

      s21_sub_ld(*my_ldec_v1, *my_ldec_v2, my_ldec_v1);

      for (; difference != 0; difference--) {
        s21_left_shift(&result);
      }

      s21_add_ld(*lresult, result_one, lresult);

      result = result_one;
      *my_ldec_v2 = my_dummy_v2;

      exit_residue_d++;
    }
    if (!exit_residue_d) {
      s21_multiplication_by_ten(lresult);
    }
    exit_residue_d = 0;
  }
}

int s21_search_first_high_bit(s21_long_decimal *my_ldec_v1) {
  int pointer = 96;

  for (int i = 2; i >= 0; i--) {
    if (my_ldec_v1->bits[i] == 0) {
      pointer -= 32;
      continue;
    }
    for (int i2 = 31; i2 >= 0; i2--, pointer--) {
      if (ACTIVE_FIRST_BIT << i2 & my_ldec_v1->bits[i]) {
        i = -1;
        i2 = -1;
      }
    }
  }

  return pointer;
}