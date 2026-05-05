.. SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
.. SPDX-License-Identifier: CC-BY-SA-4.0 AND LicenseRef-Patent-license

.. header:: psa/crypto-bs
    :seq: 2

.. _cbs:

Clause blind schnorr signatures
===============================

.. _cbs_keys:

Clause blind schnorr signature keys
-----------------------------------

The |API| supports Clause blind schnorr signatures (CBS-BS).

.. macro:: PSA_KEY_TYPE_CBS_KEY_PAIR
    :definition: ((psa_key_type_t)0x????)

    .. summary::
        Clause blind schnorr key pair: both private and public key.
    
    .. subsection:: Compatible algorithms

        .. hlist::
            
            *   `PSA_ALG_CBS`
    
    .. subsection:: Key format
    .. subsection:: Key generation
    .. subsection:: Key derivation

.. macro:: PSA_KEY_TYPE_CBS_PUBLIC_KEY
    :definition: ((psa_key_type_t)0x?????)

    .. summary::
        Clause blind schnorr public key.

    .. subsection:: Compatible algorithms

        .. hlist::
            
            *   `PSA_ALG_CBS`
    
    .. subsection:: Key format

.. macro:: PSA_KEY_TYPE_IS_CBS
    :definition: /* specification-defined value */

    .. summary::
        Whether a key type is an Clause blind schnorr key. This includes both key pairs and public keys.

    .. param:: type
        A key type: a value of type `psa_key_type_t`.

.. _cbs-bs-algorithms:

Clause blind schnorr signature algorithm
----------------------------------------

This algorithm extends those defined in :cite-title:`PSA-CRYPT` §10.7 *Asymmetric signature*, for use with signature functions.

.. macro:: PSA_ALG_CBS
    :definition: ((psa_algorithm_t)0x????)

    .. summary::
        Clause blind schnorr signature scheme.

        .. versionadded:: 1.4

    This algorithm can be used with blind signature functions and signature verify functions.

    .. subsection:: Usage

        This is a blind signature algorithm. See algorithm-usage_.

    .. subsection:: Compatible key types

        | :code:`PSA_KEY_TYPE_CBS_KEY_PAIR`
        | :code:`PSA_KEY_TYPE_CBS_PUBLIC_KEY` (signature verification only)