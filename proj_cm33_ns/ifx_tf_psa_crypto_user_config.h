/**
 * \file ifx_tf_psa_crypto_user_config.h
 *
 * \brief Configuration options (set of defines)
 *
 *  This set of compile-time options may be used to enable
 *  or disable platform specific features.
 *
 *******************************************************************************
 * \copyright
 * Copyright 2022, Cypress Semiconductor Corporation (an Infineon company).
 * All rights reserved.
 * You may use this file only in accordance with the license, terms, conditions,
 * disclaimers, and limitations in the end user license agreement accompanying
 * the software package with which this file was provided.
 ******************************************************************************/

#ifndef IFX_TF_PSA_CRYPTO_USER_CONFIG_H
#define IFX_TF_PSA_CRYPTO_USER_CONFIG_H

/* *** DO NOT CHANGE ANY SETTINGS IN THIS SECTION *** */

/* Enable the Infineon PSA transparent/opaque driver hooks in
   psa/crypto_driver_contexts_*.h and psa_crypto_driver_wrappers.h */
#define MBEDTLS_PSA_CRYPTO_DRIVERS

/* Enable SE RT Services crypto driver */
//#define IFX_PSA_SE_DPA_PRESENT

/* Enable MXCRYPTO transparent driver */
#define IFX_PSA_MXCRYPTO_PRESENT

/* Enable CRYPTOLITE transparent driver */
//#define IFX_PSA_CRYPTOLITE_PRESENT

/* Use SE RT Services to calculate SHA256 digest */
//#define IFX_PSA_SHA256_BY_SE_DPA

/* Use SE RT Services to generate random values */
//#define IFX_PSA_RANDOM_BY_SE_DPA

/* Use SE RT Services builtin keys */
//#define IFX_PSA_CRYPTO_BUILTIN_KEYS

/* Enable support for platform built-in keys.
   Built-in keys are stored in SE RT Services */
//#define MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS

//#define MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT

#endif /* IFX_TF_PSA_CRYPTO_USER_CONFIG_H */
