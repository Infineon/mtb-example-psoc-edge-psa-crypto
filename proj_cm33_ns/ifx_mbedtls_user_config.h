/**
 * \file ifx_mbedtls_user_config.h
 *
 * \brief Mbed TLS (TLS/X.509 layer) configuration overlay for this
 *        application. Selected through MBEDTLS_USER_CONFIG_FILE and applied
 *        by mbedtls/build_info.h after the default mbedtls_config.h.
 *
 * Note this is a separate chain from the TF-PSA-Crypto configuration
 * (ifx_tf_psa_crypto_config.h / ifx_tf_psa_crypto_user_config.h).
 */

#ifndef IFX_MBEDTLS_USER_CONFIG_H
#define IFX_MBEDTLS_USER_CONFIG_H

/* Bare-metal adjustments shipped by the mbedtls-pal porting layer
 * (no filesystem, no sockets, no wall clock). */
#include "mbedtls_user_config.h"

/* The TLS debug layer calls mbedtls_ssl_states_str(),
 * mbedtls_ssl_sig_alg_to_str() and mbedtls_ssl_named_group_to_str(), which
 * upstream emits into library/ssl_debug_helpers_generated.c from
 * framework/scripts/generate_ssl_debug_helpers.py during its CMake/Make
 * configure step. ModusToolbox has no configure step and mbedtls-pal does not
 * pre-generate that file, so the symbols are never defined and armlink fails
 * with L6218E. GCC only hides this because --gc-sections drops the unreachable
 * TLS code before relocation.
 *
 * Disabling MBEDTLS_DEBUG_C turns every MBEDTLS_SSL_DEBUG_xxx into
 * `do { } while (0)`, so the arguments are not evaluated and the references
 * disappear. This application never installs a debug callback
 * (mbedtls_ssl_conf_dbg), so nothing is lost. */
#undef MBEDTLS_DEBUG_C

#endif /* IFX_MBEDTLS_USER_CONFIG_H */
