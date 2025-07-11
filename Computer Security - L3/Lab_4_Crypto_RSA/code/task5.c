#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>

int verify_signature(const char *hex_message, const char *hex_signature, BIGNUM *e, BIGNUM *n) {
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *M = BN_new();
    BIGNUM *S = BN_new();
    BIGNUM *M_prime = BN_new();

    // Convert the hex values to BIGNUM
    BN_hex2bn(&M, hex_message);
    BN_hex2bn(&S, hex_signature);

    // Calculate M' = S^e mod n
    BN_mod_exp(M_prime, S, e, n, ctx);

    // Compare M' with M
    if (BN_cmp(M_prime, M) == 0) {
        printf("Signature is valid.\n");
    } else {
        printf("Signature is invalid.\n");
    }

    // Free memory
    BN_free(M);
    BN_free(S);
    BN_free(M_prime);
    BN_CTX_free(ctx);
    return 0;
}

int main() {
    // Initialize keys
    BIGNUM *e = BN_new();
    BIGNUM *n = BN_new();

    // Set the public key values
    BN_hex2bn(&e, "010001"); 
    BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");

    // Original message in hex
    const char *message = "4C61756E63682061206D697373696C652E"; // Hex value of "Launch a missile."
    const char *signature = "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F";

    // Verify the signature
    verify_signature(message, signature, e, n);

    // Free keys
    BN_free(e);
    BN_free(n);
    return 0;
}

