/**
 * \file ifx_tf_psa_crypto_config.h
 * \brief TF-PSA-Crypto configuration for this application.
 *
 * Selected through TF_PSA_CRYPTO_CONFIG_FILE in the project Makefile, so it
 * fully replaces the library default psa/crypto_config.h. It therefore has to
 * carry both the PSA_WANT_xxx feature selection and the MBEDTLS_xxx core
 * options of the TF-PSA-Crypto build.
 *
 * Infineon driver switches (IFX_PSA_xxx_PRESENT) live in the user
 * configuration file ifx_tf_psa_crypto_user_config.h.
 */

#ifndef PSA_CRYPTO_CONFIG_H
#define PSA_CRYPTO_CONFIG_H

/* Oldest TF-PSA-Crypto release this configuration is written against. */
#define TF_PSA_CRYPTO_CONFIG_VERSION 0x01000000

/*----------------------------------------------------------------------------
 * PSA cryptographic mechanisms
 *--------------------------------------------------------------------------*/

//#define PSA_WANT_ALG_CBC_MAC                    1
#define PSA_WANT_ALG_CBC_NO_PADDING             1
#define PSA_WANT_ALG_CBC_PKCS7                  1
#define PSA_WANT_ALG_CCM                        1
//#define PSA_WANT_ALG_CCM_STAR_NO_TAG            1
//#define PSA_WANT_ALG_CMAC                       1
//#define PSA_WANT_ALG_CFB                        1
//#define PSA_WANT_ALG_CHACHA20_POLY1305          1
#define PSA_WANT_ALG_CTR                        1
#define PSA_WANT_ALG_DETERMINISTIC_ECDSA        1
//#define PSA_WANT_ALG_ECB_NO_PADDING             1
#define PSA_WANT_ALG_ECDH                       1
//#define PSA_WANT_ALG_FFDH                       1
#define PSA_WANT_ALG_ECDSA                      1
//#define PSA_WANT_ALG_JPAKE                      1
//#define PSA_WANT_ALG_GCM                        1
#define PSA_WANT_ALG_HKDF                       1
#define PSA_WANT_ALG_HKDF_EXTRACT               1
#define PSA_WANT_ALG_HKDF_EXPAND                1
#define PSA_WANT_ALG_HMAC                       1
//#define PSA_WANT_ALG_MD5                        1
//#define PSA_WANT_ALG_OFB                        1
//#define PSA_WANT_ALG_PBKDF2_HMAC                1
//#define PSA_WANT_ALG_PBKDF2_AES_CMAC_PRF_128    1
//#define PSA_WANT_ALG_RIPEMD160                  1
//#define PSA_WANT_ALG_RSA_OAEP                   1
//#define PSA_WANT_ALG_RSA_PKCS1V15_CRYPT         1
//#define PSA_WANT_ALG_RSA_PKCS1V15_SIGN          1
//#define PSA_WANT_ALG_RSA_PSS                    1
//#define PSA_WANT_ALG_SHA_1                      1
#define PSA_WANT_ALG_SHA_224                    1
#define PSA_WANT_ALG_SHA_256                    1
//#define PSA_WANT_ALG_SHA_384                    1
//#define PSA_WANT_ALG_SHA_512                    1
//#define PSA_WANT_ALG_SHA3_224                   1
//#define PSA_WANT_ALG_SHA3_256                   1
//#define PSA_WANT_ALG_SHA3_384                   1
//#define PSA_WANT_ALG_SHA3_512                   1
//#define PSA_WANT_ALG_SHAKE128                   1
//#define PSA_WANT_ALG_SHAKE256                   1
//#define PSA_WANT_ALG_STREAM_CIPHER              1
//#define PSA_WANT_ALG_TLS12_PRF                  1
//#define PSA_WANT_ALG_TLS12_PSK_TO_MS            1
//#define PSA_WANT_ALG_TLS12_ECJPAKE_TO_PMS       1

//#define PSA_WANT_ECC_BRAINPOOL_P_R1_256         1
//#define PSA_WANT_ECC_BRAINPOOL_P_R1_384         1
//#define PSA_WANT_ECC_BRAINPOOL_P_R1_512         1
//#define PSA_WANT_ECC_MONTGOMERY_255             1
//#define PSA_WANT_ECC_MONTGOMERY_448             1
//#define PSA_WANT_ECC_SECP_K1_256                1
/* Required by ECDH/ECDSA above; also the only curve the MXCRYPTO PSA
 * transparent driver is configured for in this application. */
#define PSA_WANT_ECC_SECP_R1_256                1
//#define PSA_WANT_ECC_SECP_R1_384                1
//#define PSA_WANT_ECC_SECP_R1_521                1

//#define PSA_WANT_DH_RFC7919_2048                1
//#define PSA_WANT_DH_RFC7919_3072                1
//#define PSA_WANT_DH_RFC7919_4096                1
//#define PSA_WANT_DH_RFC7919_6144                1
//#define PSA_WANT_DH_RFC7919_8192                1

#define PSA_WANT_KEY_TYPE_DERIVE                1
//#define PSA_WANT_KEY_TYPE_PASSWORD              1
//#define PSA_WANT_KEY_TYPE_PASSWORD_HASH         1
#define PSA_WANT_KEY_TYPE_HMAC                  1
#define PSA_WANT_KEY_TYPE_AES                   1
//#define PSA_WANT_KEY_TYPE_ARIA                  1
//#define PSA_WANT_KEY_TYPE_CAMELLIA              1
//#define PSA_WANT_KEY_TYPE_CHACHA20              1
#define PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY        1
//#define PSA_WANT_KEY_TYPE_DH_PUBLIC_KEY         1
#define PSA_WANT_KEY_TYPE_RAW_DATA              1
//#define PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY        1

#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC    1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT   1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT   1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_GENERATE 1
#define PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_DERIVE   1

//#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC    1
//#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT   1
//#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT   1
//#define PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE 1

//#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_BASIC     1
//#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_IMPORT    1
//#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_EXPORT    1
//#define PSA_WANT_KEY_TYPE_DH_KEY_PAIR_GENERATE  1

/*----------------------------------------------------------------------------
 * TF-PSA-Crypto core options
 *
 * Bare-metal target: no filesystem, no wall clock, no host entropy source.
 *--------------------------------------------------------------------------*/

#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PSA_CRYPTO_C
#define MBEDTLS_PSA_KEY_STORE_DYNAMIC

/* The built-in entropy sources are Unix/Windows only. Route entropy through
 * mbedtls_platform_get_entropy(), implemented by the application. */
#define MBEDTLS_PSA_DRIVER_GET_ENTROPY

#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_MD_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PK_PARSE_EC_EXTENDED
#define MBEDTLS_PK_PARSE_EC_COMPRESSED
#define MBEDTLS_ECP_NIST_OPTIM

#endif /* PSA_CRYPTO_CONFIG_H */
