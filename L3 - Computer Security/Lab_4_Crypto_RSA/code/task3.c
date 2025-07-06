#include <stdio.h>
#include <openssl/bn.h>

int main() {
    BN_CTX *ctx = BN_CTX_new();
    
    // Public and private keys
    BIGNUM *n = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *C = BN_new();
    BIGNUM *M = BN_new();

    // Initialize n, d, and C with the hexadecimal values
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
    BN_hex2bn(&C, "8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");

    // Calculate M = C^d mod n
    BN_mod_exp(M, C, d, n, ctx);
    
    // Print the decrypted message in hexadecimal
    char *msg = BN_bn2hex(M);
    printf("Decrypted message (hex): %s\n", msg);
    

    OPENSSL_free(msg);
    BN_free(n);
    BN_free(d);
    BN_free(C);
    BN_free(M);
    BN_CTX_free(ctx);
    return 0;
}

