#include <stdint.h>
#include "bits.h"


struct bits8 {
  struct bit b0; // Least significant bit
  struct bit b1;
  struct bit b2;
  struct bit b3;
  struct bit b4;
  struct bit b5;
  struct bit b6;
  struct bit b7;
};

// Convert integer to bits8
struct bits8 bits8_from_int(unsigned int x){
  struct bits8 b;
  b.b0 = bit_from_int(x & 1);
  b.b1 = bit_from_int((x >> 1) & 1);
  b.b2 = bit_from_int((x >> 2) & 1);
  b.b3 = bit_from_int((x >> 3) & 1);
  b.b4 = bit_from_int((x >> 4) & 1);
  b.b5 = bit_from_int((x >> 5) & 1);
  b.b6 = bit_from_int((x >> 6) & 1);
  b.b7 = bit_from_int((x >> 7) & 1);
  return b;
}

// explanation for 9:
// 000000000 or 00000001 = 000000001
// We have that 1 << 3 == 1000 which is 8 in binary
// 000000001 or 00001000 = 00001001 which is 9 in binary
unsigned int bits8_to_int(struct bits8 x){
  unsigned int y = 0;
  y = y | bit_to_int(x.b0);
  y = y | (bit_to_int(x.b1) << 1);
  y = y | (bit_to_int(x.b2) << 2);
  y = y | (bit_to_int(x.b3) << 3);
  y = y | (bit_to_int(x.b4) << 4);
  y = y | (bit_to_int(x.b5) << 5);
  y = y | (bit_to_int(x.b6) << 6);
  y = y | (bit_to_int(x.b7) << 7);

  return y;
}

void bits8_print(struct bits8 v){
  bit_print(v.b7);
  bit_print(v.b6);
  bit_print(v.b5);
  bit_print(v.b4);
  bit_print(v.b3);
  bit_print(v.b2);
  bit_print(v.b1);
  bit_print(v.b0);
}

// used formular from assignment
struct bits8 bits8_add(struct bits8 x, struct bits8 y){
  struct bits8 z;
  struct bit c = bit_from_int(0);
  z.b0 = bit_xor(bit_xor(x.b0, y.b0), c);
  c = bit_or(bit_and(x.b0, y.b0), bit_and(bit_xor(x.b0, y.b0), c));
  z.b1 = bit_xor(bit_xor(x.b1, y.b1), c);
  c = bit_or(bit_and(x.b1, y.b1), bit_and(bit_xor(x.b1, y.b1), c));
  z.b2 = bit_xor(bit_xor(x.b2, y.b2), c);
  c = bit_or(bit_and(x.b2, y.b2), bit_and(bit_xor(x.b2, y.b2), c));
  z.b3 = bit_xor(bit_xor(x.b3, y.b3), c);
  c = bit_or(bit_and(x.b3, y.b3), bit_and(bit_xor(x.b3, y.b3), c));
  z.b4 = bit_xor(bit_xor(x.b4, y.b4), c);
  c = bit_or(bit_and(x.b4, y.b4), bit_and(bit_xor(x.b4, y.b4), c));
  z.b5 = bit_xor(bit_xor(x.b5, y.b5), c);
  c = bit_or(bit_and(x.b5, y.b5), bit_and(bit_xor(x.b5, y.b5), c));
  z.b6 = bit_xor(bit_xor(x.b6, y.b6), c);
  c = bit_or(bit_and(x.b6, y.b6), bit_and(bit_xor(x.b6, y.b6), c));
  z.b7 = bit_xor(bit_xor(x.b7, y.b7), c);
  c = bit_or(bit_and(x.b7, y.b7), bit_and(bit_xor(x.b7, y.b7), c));
  return z;
}

// Negate bits8 as the arithmetic operation multiplying by -1 
// Bitwise negation and then add 1
struct bits8 bits8_negate(struct bits8 x){
  struct bits8 y;
  y.b0 = bit_not(x.b0);
  y.b1 = bit_not(x.b1);
  y.b2 = bit_not(x.b2);
  y.b3 = bit_not(x.b3);
  y.b4 = bit_not(x.b4);
  y.b5 = bit_not(x.b5);
  y.b6 = bit_not(x.b6);
  y.b7 = bit_not(x.b7);
  return bits8_add(y, bits8_from_int(1));
}

// switches bits8 to left by n bits
struct bits8 l_shift(struct bits8 x, int n){
  return bits8_from_int(bits8_to_int(x) << n);
}

//Function that returns an empty bits8 if bit_arg is 0, otherwise returns x
struct bits8 bits8_if(struct bits8 x, struct bit bit_arg){
  struct bits8 y;
  y.b0 = bit_and(bit_arg, x.b0);
  y.b1 = bit_and(bit_arg, x.b1);
  y.b2 = bit_and(bit_arg, x.b2);
  y.b3 = bit_and(bit_arg, x.b3);
  y.b4 = bit_and(bit_arg, x.b4);
  y.b5 = bit_and(bit_arg, x.b5);
  y.b6 = bit_and(bit_arg, x.b6);
  y.b7 = bit_and(bit_arg, x.b7);
  return y;
}

struct bits8 bits8_mul(struct bits8 x, struct bits8 y){
  struct bits8 a = x;
  struct bits8 b = y;
  struct bits8 c;

  c = b;
  c = bits8_add(c, bits8_if(l_shift(b, 1), a.b1));
  c = bits8_add(c, bits8_if(l_shift(b, 2), a.b2));
  c = bits8_add(c, bits8_if(l_shift(b, 3), a.b3));
  c = bits8_add(c, bits8_if(l_shift(b, 4), a.b4));
  c = bits8_add(c, bits8_if(l_shift(b, 5), a.b5));
  c = bits8_add(c, bits8_if(l_shift(b, 6), a.b6));
  c = bits8_add(c, bits8_if(l_shift(b, 7), a.b7));
  return c;
}

