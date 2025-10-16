#ifndef s21_dec
#define s21_dec

#include <math.h>
#include <stdlib.h>

#define ACTIVE_FIRST_BIT 0x00000001
#define SIGN_MINUS 0x80000000

#define MAX_FLOAT 79228162514264337593543950335.0
#define MIN_FLOAT 1e-28

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_long_decimal;

typedef union {
  s21_decimal number;
  struct {
    int bits[3];
    unsigned int useless1 : 16;
    unsigned int exponent : 8;
    unsigned int useless2 : 7;
    unsigned int sign : 1;
  } parts;
} s21_decimal_union;

// Comparison operators
int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_ld(s21_long_decimal value1, s21_long_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal_ld(s21_long_decimal value1,
                               s21_long_decimal value2);

// Arithmetic operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Additional functions
unsigned int s21_get_sign_ldec(s21_long_decimal value);
unsigned int s21_get_sign_dec(s21_decimal value);
int s21_get_scale_ldec(s21_long_decimal value);
int s21_get_scale_dec(s21_decimal value);
int s21_add_ld(s21_long_decimal value_1, s21_long_decimal value_2,
               s21_long_decimal *result);
int s21_sub_ld(s21_long_decimal value_1, s21_long_decimal value_2,
               s21_long_decimal *result);
int s21_swap(s21_long_decimal *value_1, s21_long_decimal *value_2);
int s21_bank_rounding(s21_long_decimal *value);
int s21_decimal_check(s21_decimal value);
int s21_division_by_ten_ldec(s21_long_decimal *value);
int s21_division_by_ten_dec(s21_decimal *value);
int s21_decimal_zero_check(s21_decimal value);
void s21_clear_decimal(s21_decimal *dst);
void s21_normalization(s21_long_decimal *value_1, s21_long_decimal *value_2);
void s21_multiplication_by_ten(s21_long_decimal *value);
void s21_left_shift(s21_long_decimal *value);
void s21_right_shift(s21_long_decimal *value);
void s21_set_bit_to_ldec(s21_long_decimal *value, int num_e, int num_pos,
                         int bit);
s21_long_decimal s21_conversion_from_dec_to_ldec(s21_decimal value);
s21_decimal s21_conversion_from_ldec_to_dec(s21_long_decimal value);

// Other functions
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_negate_ld(s21_long_decimal value, s21_long_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

// Converstion
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

int s21_compare(s21_long_decimal value1, s21_long_decimal value2);
int s21_is_bit_set(s21_decimal value, int ind);
int s21_is_decimal_correct(s21_decimal value);
int s21_is_equal_ld(s21_long_decimal lvalue1, s21_long_decimal lvalue2);
void s21_set_power(s21_decimal *value, int power);
void s21_add_one(s21_decimal *val);

#endif