// SPDX-FileCopyrightText: Copyright 2018-2026 Arm Limited and/or its affiliates <open-source-office@arm.com>
// SPDX-License-Identifier: Apache-2.0

/* This file contains reference definitions for implementation of the
 * PSA Certified Crypto API v1.4 Blind Signature Extension
 *
 * These definitions must be embedded in, or included by, psa/crypto.h
 */

/**
 * @brief Randomized RSA blind signature scheme with appendix (RSABSSA).
 */
#define PSA_ALG_RSABSSA

/**
 * @brief Deterministic RSA blind signature scheme with appendix (RSABSSA).
 */
#define PSA_ALG_DETERMINISTIC_RSABSSA

/**
 * @brief Deterministic RSA blind signature scheme with appendix (RSABSSA) and full domain hash.
 */
#define PSA_ALG_RSABSSA_FDH

/**
 * @brief Clause blind schnorr blind signature algorithm.
 */
#define PSA_ALG_CBS

/**
 * @brief Fair fiat shamir blind signature algorithm.
 */
#define PSA_ALG_FFS

/**
 * @brief Lattice based blind signature algorithm.
 */
#define PSA_ALG_LATTICE

typedef struct psa_blind_sign_ctx_t {
    psa_algorithm_t algo;
    uint8_t signer_pubrandom[??];
    uint8_t signer_privrandom[??];
    uint8_t user_inverse[??];
}psa_blind_sign_ctx_t;
typedef struct {
    uint8_t inv[512];
    size_t inv_size;
} psa_blind_sign_rsa_ctx_t;

typedef union {
    psa_blind_sign_rsa_ctx_t rsa;
} psa_bs_context_t;

struct psa_blind_sign_ctx_s {
    psa_algorithm_t algo;
    psa_bs_context_t ctx;
};

typedef struct psa_blind_sign_ctx_s psa_blind_sign_ctx_t;
/**
 * @brief User setup blind signature protocol.
 * 
 * @param sign_context      Context for persistent values throughout the protocol.
 * @param algorithm         Blind signature algorithm to use.
 * @param salt_len          Length of a salt required by RSABSSA.
 */
psa_status_t psa_blindsig_user_setup(psa_blind_sign_ctx_t* sign_context,
                                  psa_algorithm_t algorithm, size_t salt_len);

/**
 * @brief Signer setup and generate public and private randoms (randomized only).
 * 
 * @param sign_context      Context for persistent values throughout the protocol.
 * @param algorithm         Blind signature algorithm to use.
 * @param prandom           Public random value for user.
 * @param prandom_size      Size of public random buffer in bytes.
 * @param prandom_length    On success, the number of bytes of returned public random.
 */
psa_status_t psa_blindsig_signer_setup(psa_blind_sign_ctx_t* sign_context,
                                 psa_algorithm_t algorithm,
                                 uint8_t *prandom, size_t prandom_size,
                                 size_t *prandom_length);

/**
 * @brief Blind a message.
 * 
 * @param sign_context      Context for persistant values throughout the protocol.
 * @param key               Public key from signer.
 * @param message           Message to be blinded.
 * @param message_len       Length of message to be blinded.
 * @param prandom           Optional signer public random.
 * @param prandom_len       Length of optional signer public random in bytes.
 * @param bmessage          Blinded message.
 * @param bmessage_size     Size of blinded message buffer in bytes.
 * @param bmessage_length   On success, the number of bytes of the returned blinded message.
 */
psa_status_t psa_blindsig_blind_message(psa_blind_sign_ctx_t* sign_context, psa_key_id_t key,
                                          uint8_t *message, size_t message_len,
                                          uint8_t *prandom, size_t prandom_len,
                                          uint8_t *bmessage, size_t bmessage_size,
                                          size_t *bmessage_length);

/**
 * @brief Blind a hash.
 * 
 * @param sign_context      Context for persistant values throughout the protocol.
 * @param key               Public key from signer.
 * @param hash              Hash to be blinded.
 * @param hash_len          Length of hash to be blinded.
 * @param prandom           Optional signer public random.
 * @param prandom_len       Length of optional signer public random in bytes.
 * @param bmessage          Blinded message.
 * @param bmessage_size     Size of blinded message buffer in bytes.
 * @param bmessage_length   On success, the number of bytes of the returned blinded message.
 */
psa_status_t psa_blindsig_blind_hash(psa_blind_sign_ctx_t* sign_context, psa_key_id_t key,
                                     const uint8_t *hash, size_t hash_len,
                                     const uint8_t *prandom, size_t prandom_len,
                                     const uint8_t *bmessage, size_t bmessage_size,
                                     size_t *bmessage_length);

/**
 * @brief Sign a blinded message or hash.
 * 
 * @param sign_context      Context for persistant values throughout the protocol.
 * @param key               Private key for signer.
 * @param input             Blinded message.
 * @param input_length      Length of blinded message.
 * @param signature         Blinded signature.
 * @param signature_size    Size of blinded signature buffer in bytes.
 * @param signature_length  On success, the number of bytes of returned blind signature.
 */
psa_status_t psa_blindsig_sign(psa_blind_sign_ctx_t *sign_context,
                               psa_key_id_t key,
                               const uint8_t *input,
                               size_t input_length,
                               uint8_t *signature,
                               size_t signature_size,
                               size_t *signature_length);

/**
 * @brief Unblind a signature.
 * 
 * @param sign_context      Context for persistant values throughout the protocol.
 * @param key               Public key from signer.
 * @param bsignature        Blinded signature.
 * @param bsignature_len    Length of blinded signature.
 * @param signature         Unblinded signature.
 * @param signature_size    Size of signature buffer in bytes.
 * @param signature_length  On success, the number of bytes of the returned signature.
 */
psa_status_t psa_blindsig_unblind(psa_blind_sign_ctx_t* sign_context, psa_key_id_t key,
                                    uint8_t *bsignature, size_t bsignature_len,
                                    uint8_t *signature, size_t signature_size,
                                    size_t *signature_len);
