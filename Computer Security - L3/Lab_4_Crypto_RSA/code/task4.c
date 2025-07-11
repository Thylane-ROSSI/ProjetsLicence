#include <stdio.h>
#include <openssl/bn.h>

void sign_message(const char *hex_message, BIGNUM *d, BIGNUM *n) {
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *M = BN_new();
    BIGNUM *S = BN_new();

    // Convert the hex message to a BIGNUM
    BN_hex2bn(&M, hex_message);

    // Calculate S = M^d mod n
    BN_mod_exp(S, M, d, n, ctx);

    // Print the signature in hexadecimal
    char *sig_hex = BN_bn2hex(S);
    printf("Signature (hex): %s\n", sig_hex);

    // Free memory
    OPENSSL_free(sig_hex);
    BN_free(M);
    BN_free(S);
    BN_CTX_free(ctx);
}

int main() {
    // Initialize keys
    BIGNUM *d = BN_new();
    BIGNUM *n = BN_new();

    // Set the private key and modulus
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");

    // Original message in hex
    const char *message = "49206f776520796f752024333030302e"; // Hex value of "I owe you $2000." Then I'll change to  “I owe you $3000.”

    // Sign the message
    sign_message(message, d, n);

    // Free keys
    BN_free(d);
    BN_free(n);
    return 0;
}

