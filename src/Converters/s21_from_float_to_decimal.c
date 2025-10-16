#include "../s21_decimal.h"

int get_meaningful_numbers_and_exp(long double src, int *exp);
void multiply_to_exp(s21_decimal *dst, int *exp);
void remove_trailing_zeroes(unsigned int *val, int *exp);
void rounding(int *res, long double src);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else if (isinf(src) || isnan(src)) {
    res = 1;
  } else if (fabsf(src) > MAX_FLOAT ||
             (fabsf(src) < MIN_FLOAT && fabsf(src) > 0)) {
    res = 1;
  } else {
    s21_clear_decimal(dst);
    if (src < 0) {
      s21_negate(*dst, dst);
      src = -src;
    }
    int exp = 0;
    dst->bits[0] = get_meaningful_numbers_and_exp(src, &exp);
    if (exp > 0)
      remove_trailing_zeroes(&dst->bits[0], &exp);
    else if (exp < 0)
      multiply_to_exp(dst, &exp);
    s21_set_power(dst, exp);
  }

  if (res && dst) {
    s21_clear_decimal(dst);
  }
  return res;
}

void remove_trailing_zeroes(unsigned int *val, int *exp) {
  while (*val % 10 == 0 && *exp) {
    *val /= 10;
    (*exp)--;
  }
}

void multiply_to_exp(s21_decimal *dst, int *exp) {
  s21_long_decimal temp = s21_conversion_from_dec_to_ldec(*dst);
  while (*exp < 0) {
    s21_multiplication_by_ten(&temp);
    (*exp)++;
  }
  s21_bank_rounding(&temp);
  *dst = s21_conversion_from_ldec_to_dec(temp);
}

int get_meaningful_numbers_and_exp(long double src, int *exp) {
  if (src == 0) return 0;
  int res = 0;
  *exp = 6 - (int)floor(log10(src));
  if (*exp > 28) *exp = 28;
  src *= powl(10, *exp);
  res = (int)src;

  rounding(&res, src - res);

  return res;
}

void rounding(int *res, long double src) {
  while ((int)src) src /= 10;
  src = roundl(src);

  if (src >= 1 && (int)src) {
    (*res)++;
  }
}