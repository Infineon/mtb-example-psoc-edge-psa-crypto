[Click here](../README.md) to view the README.

## Design and implementation

The design of this application is minimalistic to get started with code examples on PSOC&trade; Edge MCU devices. All PSOC&trade; Edge E84 MCU applications have a dual-CPU three-project structure to develop code for the CM33 and CM55 cores. The CM33 core has two separate projects for the secure processing environment (SPE) and non-secure processing environment (NSPE). A project folder consists of various subfolders, each denoting a specific aspect of the project. The three project folders are as follows:

This code example shows how to use PSA crypto APIs on PSOC&trade; Edge MCU. The PSA Cryptographic API (Crypto API) is an important PSA component that provides a portable interface to cryptographic operations on a wide range of hardware. The interface is user-friendly and provides access to the low-level primitives used in modern cryptography.

Up to Mbed TLS v3.x, this API was implemented inside the Mbed TLS library itself. From Mbed TLS v4.x onwards, the cryptography implementation has been split into a separate project called **TF-PSA-Crypto**, and Mbed TLS keeps only the TLS and X.509 layers on top of it. This example therefore takes the PSA crypto API from TF-PSA-Crypto.

To demonstrate how to use PSA APIs, this example uses single-part hashing and single-part AEAD cipher functions. The SHA-256 scheme is chosen for hashing while the AES-128 CCM scheme is chosen for cipher operations. The cryptographic operations are performed in the proj_cm33_ns project. The project uses hardware cryptographic accelerator SHA256 digest calculation, AES operation, and TRNG generation. Here, TRNG is used for nonce generation, which is required input for the AEAD AES-128 CCM scheme.

> **Note:** The cryptographic operations here are performed in the non-secure M33 project, which is not isolated by TrustZone.

**Table 1. Application projects**

Project | Description
--------|------------------------
*proj_cm33_s* | Project for CM33 secure processing environment (SPE)
*proj_cm33_ns* | Project for CM33 non-secure processing environment (NSPE)
*proj_cm55* | CM55 project

<br>

In this code example, at device reset, the secure boot process starts from the ROM boot with the secure enclave (SE) as the root of trust (RoT). From the secure enclave, the boot flow is passed on to the system CPU subsystem where the secure CM33 application starts. After all necessary secure configurations, the flow is passed on to the non-secure CM33 application. Resource initialization for this example is performed by this CM33 non-secure project. It configures the system clocks, pins, clock to peripheral connections, and other platform resources. It then enables the CM55 core using the `Cy_SysEnableCM55()` function and the CM55 core is subsequently put to DeepSleep mode.

The non-secure CM33 project then performs the cryptographic operation using the PSA APIs, which are used to calculate SHA-256 digest of data. The same data is encrypted and decrypted using the AEAD AES-128 CCM. The output of the crypto operations is printed on the UART terminal.
