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


//General changes: replaced varible names from sample to fit the lab description

//Changes start
  BIGNUM *p = BN_new();
  BIGNUM *q = BN_new();
  BIGNUM *e = BN_new();
  BIGNUM *d = BN_new();
  BIGNUM *res = BN_new();
  BIGNUM *phi = BN_new();
  BIGNUM *n = BN_new();
  BIGNUM *p1 = BN_new();
  BIGNUM *q1 = BN_new();
  
  BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
  BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
  BN_hex2bn(&e, "0D88C3");


  // n = p*q
  BN_mul(n, p, q, ctx);

  
  
  //phi(m) = (p-1)*(q-1)
  BN_sub(p1, p, BN_value_one());
  BN_sub(q1, q, BN_value_one());
  BN_mul(phi, p1, q1, ctx);
  
  BN_gcd(res, phi, e, ctx);
  if (!BN_is_one(res))
  {
  	printf("Error: GCD of phi and e not 1 \n ");
        exit(0);
    }
  
  //Calculate and print the private key
  BN_mod_inverse(d, e, phi, ctx);
  printBN("private key", d);
//Changes end


  // res = a^b mod n
  //BN_mod_exp(res, p, q, n, ctx);
  //printBN("a^c mod n = ", res);

  return 0;
}

