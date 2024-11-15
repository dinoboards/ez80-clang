
typedef union {
  float         value;
  unsigned long bits;
} Ieee754;

enum { //  The IEEE 754 format is:
       //  SEEEEEEE EMMMMMMM MMMMMMMM MMMMMMMM
       //  (with an implicit mantissa high-order 1-bit.)
  mastissa_shift = 0,
  mastissa_bits  = 23,
  exponent_bits  = 8,
  exponent_shift = mastissa_shift + mastissa_bits,
  sign_shift     = exponent_shift + exponent_bits,
  exponent_mask  = (1 << exponent_bits) - 1, // shifted = 0x7F800000
  exponent_max   = (1 << exponent_bits) - 1,
  exponent_base  = 127,
  exponent_min   = 0
};
