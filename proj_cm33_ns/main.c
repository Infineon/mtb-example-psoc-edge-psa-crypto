/*****************************************************************************
* File Name        : main.c
*
* Description      : This source file contains the main routine for non-secure
*                    application in the CM33 CPU
*
* Related Document : See README.md
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


/*******************************************************************************
* Header Files
*******************************************************************************/

#include "cybsp.h"
#include "cy_pdl.h"


#include "retarget_io_init.h"
#include "psa/crypto.h"
#include "crypto_common.h"


/*******************************************************************************
* Macros
*******************************************************************************/

/* The timeout value in microsecond used to wait for core to be booted */
#define CM55_BOOT_WAIT_TIME_USEC          (10U)

#define CRYPTO_IO_BUFF_SIZE               (32U)

#define NONCE_SIZE                        (12U)

#define AES_KEY_SIZE                      (128U)

#define SHA256_DIGEST_SIZE                (32U)
#define CM55_APP_BOOT_ADDR          (CYMEM_CM33_0_m55_nvm_START + \
                                        CYBSP_MCUBOOT_HEADER_SIZE)
/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function of the CM33 non-secure application.
*
* It initializes PSA Crypto interface to..
* 1. Calculate SHA256 digest of message
* 2. Encrypt message
* 3. Decrypt message
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    psa_status_t status;
    const uint8_t input_data[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
    uint8_t additional_data[] = {0x01, 0x02};
    uint8_t hash[SHA256_DIGEST_SIZE] = {0};
    uint8_t enc_data[CRYPTO_IO_BUFF_SIZE] = {0};
    uint8_t dec_data[CRYPTO_IO_BUFF_SIZE] = {0};
    uint8_t nonce[NONCE_SIZE] = {0};
    size_t enc_data_len = 0;
    size_t dec_data_len = 0;
    size_t hash_len = 0;
    int len = 0;
    psa_key_id_t aead_key_id = 0;
    cy_cmgr_crypto_hw_t hw_ctx = {0};

    psa_key_attributes_t aead_key_attributes = PSA_KEY_ATTRIBUTES_INIT;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board initialization failed. Stop program execution */
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io middleware */
    init_retarget_io();

   
    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "PSoC Edge MCU: MBEDTLS PSA Crypto "
           "****************** \r\n\n");

    /* Enable CM55. */
    /* CY_CM55_APP_BOOT_ADDR must be updated if CM55 memory layout is changed.*/
    Cy_SysEnableCM55(MXCM55, CM55_APP_BOOT_ADDR, CM55_BOOT_WAIT_TIME_USEC);


    (void)cy_hw_crypto_reserve(&hw_ctx, CY_CMGR_CRYPTO_COMMON);

    /* Crypto library initialization */
    status = psa_crypto_init();
    if(PSA_SUCCESS != status)
    {
        printf("Failed to initialize crypto library. Error code: %ld\r\n", (unsigned long) status);
        CY_ASSERT(0);
    }

    printf("Input data: ");
    for(len = 0; len < sizeof(input_data); len++)
    {
        printf("%x ", input_data[len]);
    }
    printf("\r\n");

    /* SHA256 */
    printf("\r\nCalculating SHA256 of input data...\r\n");
    status = psa_hash_compute(PSA_ALG_SHA_256, input_data, sizeof(input_data), hash, sizeof(hash), &hash_len);
    if(status != PSA_SUCCESS)
    {
        printf("Failed to calculate SHA256. Error code: %ld\r\n", (unsigned long) status);
        CY_ASSERT(0);
    }

    printf("SHA256 of data: ");
    for(len = 0; len < hash_len; len++)
    {
        printf("%02x ", hash[len]);
    }
    printf("\r\n");

    /* End of SHA256 */

    /* AEAD AES-128 CCM */

    /* Set key attributes */
    psa_set_key_usage_flags(&aead_key_attributes, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&aead_key_attributes, PSA_ALG_CCM);
    psa_set_key_lifetime(&aead_key_attributes, PSA_KEY_LIFETIME_VOLATILE);
    psa_set_key_type(&aead_key_attributes, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&aead_key_attributes, AES_KEY_SIZE);

    /* Generate key for AEAD CCM encryption/decryption */
    printf("\r\nGenerating AES key...\r\n");
    status = psa_generate_key(&aead_key_attributes, &aead_key_id);
    if(status != PSA_SUCCESS)
    {
        printf("Failed to generate AES key. Error code: %ld\r\n", (unsigned long) status);
        CY_ASSERT(0);
    }

    /* Generate a random number for nonce */
    status = psa_generate_random(nonce, sizeof(nonce));
    if(status != PSA_SUCCESS)
    {
        printf("Failed to generate nonce. Error code: %ld\r\n",(unsigned long) status);
        CY_ASSERT(0);
    }

    printf("Encrypting data with AEAD AES-128 CCM...\r\n");

    /* Encrypt data with AEAD single part cipher */
    status = psa_aead_encrypt(aead_key_id, PSA_ALG_CCM, nonce, sizeof(nonce), additional_data,
                                sizeof(additional_data), input_data, sizeof(input_data), enc_data,
                                sizeof(enc_data), &enc_data_len);
    if(status != PSA_SUCCESS)
    {
        printf("Failed to encrypt data with AEAD AES-128 CCM. Error code: %ld\r\n",(unsigned long) status);
        CY_ASSERT(0);
    }

    printf("Encrypted data: ");
    for(len = 0; len < enc_data_len; len++)
    {
        printf("%02x ", enc_data[len]);
    }
    printf("\r\n");

    /* Decrypt data with AEAD single part cipher */
    printf("Decrypting data with AEAD AES-128 CCM......\r\n");
    status = psa_aead_decrypt(aead_key_id, PSA_ALG_CCM, nonce, sizeof(nonce),
                                additional_data, sizeof(additional_data), enc_data, enc_data_len,
                                dec_data, sizeof(dec_data), &dec_data_len);
    if(status != PSA_SUCCESS)
    {
        printf("Failed to decrypt data with AEAD AES-128 CCM. Error code: %ld\r\n",(unsigned long) status);
        CY_ASSERT(0);
    }

    printf("Decrypted data: ");
    for(len = 0; len < dec_data_len; len++)
    {
        printf("%x ", dec_data[len]);
    }
    printf("\r\n");

    /* End of AES-128 CCM */

    for(;;)
    {}
}


/* [] END OF FILE */
