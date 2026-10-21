/*****************************************************************************
* File Name        : psa_entropy.c
*
* Description      : TF-PSA-Crypto platform entropy hook for the CM33
*                    non-secure application.
*
*                    The application configuration selects
*                    MBEDTLS_PSA_DRIVER_GET_ENTROPY, because the built-in
*                    entropy sources of TF-PSA-Crypto are Unix/Windows only.
*                    ifx-tf-psa-port provides a weak, fail-closed stub for the
*                    hook; this file overrides it with the Crypto block TRNG.
*
*******************************************************************************
* (c) 2023-2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

#include <string.h>

#include "cy_pdl.h"
#include "tf-psa-crypto/build_info.h"
#include "mbedtls/platform.h"
#include "psa/crypto.h"

#if defined(MBEDTLS_PSA_DRIVER_GET_ENTROPY)

/* Number of random bits requested per TRNG transaction. */
#define TRNG_BITS_PER_WORD                (32U)

int mbedtls_platform_get_entropy(psa_driver_get_entropy_flags_t flags,
                                 size_t *estimate_bits,
                                 unsigned char *output, size_t output_size)
{
    size_t generated = 0U;

    if (0U != flags)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    while (generated < output_size)
    {
        uint32_t random_word = 0U;
        size_t chunk = output_size - generated;

        if (CY_CRYPTO_SUCCESS != Cy_Crypto_Core_Trng_Ext(CRYPTO,
                                                         TRNG_BITS_PER_WORD,
                                                         &random_word))
        {
            return PSA_ERROR_INSUFFICIENT_ENTROPY;
        }

        if (chunk > sizeof(random_word))
        {
            chunk = sizeof(random_word);
        }

        (void)memcpy(&output[generated], &random_word, chunk);
        generated += chunk;
    }

    /* The TRNG is a full-entropy source. */
    *estimate_bits = output_size * 8U;

    return 0;
}

#endif /* MBEDTLS_PSA_DRIVER_GET_ENTROPY */
