#include <stdio.h>
#include <openssl/bn.h>

#define NBITS 256

void printBN(char *msg, BIGNUM * a)
{
   /* Use BN_bn2hex(a) for hex string
    * Use BN_bn2dec(a) for decimal string */
   char * number_str = BN_bn2hex(a);
   printf("%s %s\n", msg, number_str);
   OPENSSL_free(number_str);
}

int main ()
{
  BN_CTX *ctx = BN_CTX_new();

//Changes start
  BIGNUM *n = BN_new();
  BIGNUM *e = BN_new();
  BIGNUM *plain = BN_new();
  BIGNUM *cipher = BN_new();
  
  
  BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
  BN_dec2bn(&e, "65537");
  BN_hex2bn(&plain, "4120746f702073656372657421");


  BN_mod_exp(cipher, plain, e, n, ctx);
  printBN("Encrypted message", cipher);
//Changes end



  return 0;
}

