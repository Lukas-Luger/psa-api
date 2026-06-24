.. SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
.. SPDX-License-Identifier: CC-BY-SA-4.0 AND LicenseRef-Patent-license

.. header:: psa/crypto-bs
    :seq: 1

Blind signature API reference
=============================

Functions
---------

.. function:: psa_blindsig_user_setup
    .. summary::
        Setting up user side blind signature protocol.

    .. param:: psa_blind_sign_ctx_t *sign_context
        Context for persistent values throughout the protocol.
    
    .. param:: psa_algorithm_t algorithm
        Blind signature algorithm to use.

    .. param:: size_t salt_len
        Length of a salt required by RSABSSA.
    
    .. return:: psa_status_t
        Result status.
    .. retval:: PSA_SUCCESS
        Context got successfully initialized.
    .. retval:: PSA_ERROR_NOT_PERMITTED
        Invalid algorithm or salt length combination.

    This function is used to initialize the sign context for later use.

.. function:: psa_blindsig_signer_setup
    .. summary::
        Setting up server side blind signature protocol and generates public and private randoms.

    .. param:: psa_blind_sign_ctx_t *sign_context
        Context for persistent values throughout the protocol.

    .. param:: psa_algorithm_t algorithm
        Blind signature algorithm to use.

    .. param:: uint8_t *prandom
        Output public random value for user.
    
    .. param:: size_t prandom_size
        Size of public random buffer in bytes.
    
    .. param:: size_t *prandom_length
        On success, the number of bytes of returned public random.
    
    .. return:: psa_status_t
        Result status.
    .. retval:: PSA_SUCCESS
        Random generation was successful prandom_length will be the length of actual random value.
    .. retval:: PSA_ERROR_BUFFER_TOO_SMALL
        Provided buffer was too small.

.. function:: psa_blindsig_blind_message
    .. summary::
        Blind a message for later signing.

    .. param:: psa_blind_sign_ctx_t* sign_context
        Context for persistent values throughout the protocol.

    .. param:: psa_key_id_t key
        Key id containing the public key from the signer.
    
    .. param:: uint8_t *message
        Message to be blinded.

    .. param:: size_t message_len
        Length of message to be blinded.

    .. param:: uint8_t *prandom
        Optional signer public random.

    .. param:: size_t prandom_len
        Length of optional signer public random.

    .. param:: uint8_t *bmessage
        Output blinded message buffer.

    .. param:: size_t bmessage_size
        Size of blinded message buffer in bytes.

    .. param:: size_t *bmessage_length
        On success, the number of bytes of the returned blinded message.

    .. return:: psa_status_t
        Result status.
    .. retval:: PSA_SUCCESS
        Blinding was successful bmesage_length will be the length of actual blinded message.
    .. retval:: PSA_ERROR_BUFFER_TOO_SMALL
        Provided buffer was too small.

.. function:: psa_blindsig_blind_hash
    .. summary::
        Blind a hash for later signing.

    .. param:: psa_blind_sign_ctx_t* sign_context
        Context for persistent values throughout the protocol.

    .. param:: psa_key_id_t key
        Key id containing the public key from the signer.
    
    .. param:: uint8_t *hash
        Hash to be blinded.

    .. param:: size_t hash_len
        Length of hash to be blinded.

    .. param:: uint8_t *prandom
        Optional signer public random.

    .. param:: size_t prandom_len
        Length of optional signer public random.

    .. param:: uint8_t *bhash
        Output blinded hash buffer.

    .. param:: size_t bhash_size
        Size of blinded hash buffer in bytes.

    .. param:: size_t *bhash_length
        On success, the number of bytes of the returned blinded hash.

    .. return:: psa_status_t
        Result status.
    .. retval:: PSA_SUCCESS
        Blinding was successful bhash_length will be the length of actual blinded hash.
    .. retval:: PSA_ERROR_BUFFER_TOO_SMALL
        Provided buffer was too small.

.. function:: psa_blindsig_sign
    .. summary::
        Sign a blind message.
    
    .. param:: psa_blind_sign_ctx_t* sign_context
        Context for persistent values throughout the protocol.
    
    .. param:: psa_key_id_t key
        Private key for signer.

    .. param:: uint8_t *bmessage
        Input blind message or hash to sign.
    
    .. param:: size_t message_len
        Length of blind message to be signed.

    .. param:: uint8_t *bsignature
        Output blind signature buffer.

    .. param:: size_t bsignature_size
        Size of blind signature buffer in bytes.

    .. param:: size_t *bsignature_length
        On success, the number of bytes of the returned blind signature.

    .. return:: psa_status_t
        Result status.
    .. retval:: PSA_SUCCESS
        Blinding was successful bsignature_length will be the length of actual blind signature.
    .. retval:: PSA_ERROR_BUFFER_TOO_SMALL
        Provided buffer was too small.
    

.. function:: psa_blindsig_unblind
    .. summary::
        Unblind a blinded signature.

    .. param:: psa_blind_sign_ctx_t* sign_context
        Context for persistent values throughout the protocol.

    .. param:: psa_key_id_t key
        Public key from signer.

    .. param:: uint8_t *bsignature
        Blinded signature.

    .. param:: size_t bsignature_len
        Length of blinded signature.

    .. param:: uint8_t *signature
        Pointer to output buffer used for unblinded signature.

    .. param:: size_t signature_size
        Size of signature buffer in bytes.

    .. param:: size_t *signature_len
        On success, the number of bytes of the returned signature.

    .. return:: psa_status_t
        Result status.
    .. retval:: PSA_SUCCESS
        Signing was successful signature_length will be the length of signature.
    .. retval:: PSA_ERROR_BUFFER_TOO_SMALL
        Provided buffer was too small.

Macros
------
.. macro:: PSA_ALG_IS_BS
    :definition: /* specification-defined value */

    .. summary::
        Whether the specified algorithm is a blind signature algorithm.

        .. versionadded:: 1.4
    
    .. param:: alg
        Am algorithm identifier: a value of type :code:`psa_algorithm_t`
    
    .. return::
        ``1`` if ``alg`` is a blind signature algorithm, ``0`` otherwise.

        This macro can return either ``0`` or ``1`` if ``alg`` is not a supported algorithm identifier.

.. _algorithm-usage::
    
Usage
-----
Function calls should be performed by two separate instances: the user (U) and the signer (S) in the following order:

U: :code:`psa_blindsig_user_setup`

S: :code:`psa_blindsig_signer_setup`

U: :code:`psa_blindsig_blind_message` or :code:`psa_blindsig_blind_hash`

S: :code:`psa_blindsig_sign`

U: :code:`psa_blindsig_unblind`

U: :code:`psa_verify_message` or :code:`psa_verify_hash`

.. note::
    The initialized context is not shared and is specific to an instance.