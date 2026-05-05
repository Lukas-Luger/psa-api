.. SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
.. SPDX-License-Identifier: CC-BY-SA-4.0 AND LicenseRef-Patent-license

.. header:: psa/crypto-bs
    :seq: 2

.. _rsa:

RSA blind signatures
====================

.. _rsa_keys:

RSA blind signature keys
------------------------

The |API| supports RSA blind signatures (RSA-BS).

.. macro:: PSA_KEY_TYPE_RSA_KEY_PAIR
    :definition: ((psa_key_type_t)0x7001)

    .. summary::
        RSA key pair: both the private and public key.

    The size of an RSA key is the bit size of the modulus.

    .. subsection:: Compatible algorithms

        .. hlist::

            *   `PSA_ALG_RSA_OAEP`
            *   `PSA_ALG_RSA_PKCS1V15_CRYPT`
            *   `PSA_ALG_RSA_PKCS1V15_SIGN`
            *   `PSA_ALG_RSA_PKCS1V15_SIGN_RAW`
            *   `PSA_ALG_RSA_PSS`
            *   `PSA_ALG_RSA_PSS_ANY_SALT`
            *   `PSA_ALG_RSABSSA`
            *   `PSA_ALG_DETERMINISTIC_RSABSSA`
            *   `PSA_ALG_RSABSSA_FDH`
        
        .. note::

            If a key is used for (RSA Blind Signature with Appendix) RSABSSA it must not be used beyond any other protocol and shall not be reused for different encoding options of RSABSSA.

    .. subsection:: Key format

        The data format for import and export of a key-pair is the non-encrypted DER encoding of the representation defined by in :RFC-title:`8017` as ``RSAPrivateKey``, version ``0``.

        .. code-block:: none

            RSAPrivateKey ::= SEQUENCE {
                version             INTEGER,  -- must be 0
                modulus             INTEGER,  -- n
                publicExponent      INTEGER,  -- e
                privateExponent     INTEGER,  -- d
                prime1              INTEGER,  -- p
                prime2              INTEGER,  -- q
                exponent1           INTEGER,  -- d mod (p-1)
                exponent2           INTEGER,  -- d mod (q-1)
                coefficient         INTEGER,  -- (inverse of q) mod p
            }

        .. note::

            Although it is possible to define an RSA key pair or private key using a subset of these elements, the output from `psa_export_key()` for an RSA key pair must include all of these elements.

        See `PSA_KEY_TYPE_RSA_PUBLIC_KEY` for the data format used when exporting the public key with `psa_export_public_key()`.

    .. subsection:: Key generation

        A call to `psa_generate_key()` will generate an RSA key-pair with the default public exponent of ``65537``. The modulus :math:`n=pq` is a product of two probabilistic primes :math:`p\ \text{and}\ q`, where :math:`2^{r-1} \le n < 2^r` and :math:`r` is the bit size specified in the attributes.

        The exponent can be explicitly specified in non-default production parameters in a call to `psa_generate_key_custom()`. Use the following custom production parameters:

        *   The production parameters structure, ``custom``, must have ``flags`` set to zero.

        *   If ``custom_data_length == 0``, the default exponent value ``65537`` is used.

        *   The additional production parameter buffer ``custom_data`` is the public exponent, in little-endian byte order.

            The exponent must be an odd integer greater than ``1``.
            An implementation must support an exponent of ``65537``, and is recommended to support an exponent of ``3``, and can support other values.

            The maximum supported exponent value is :scterm:`implementation defined`.

        If a key is generated for use with `PSA_ALG_RSABSSA` or `PSA_ALG_DETERMINISTIC_RSABSSA`, it shall be generated according to :cite-title:`FIPS186-5`
    
    .. subsection:: Key derivation

        The method used by `psa_key_derivation_output_key()` to derive an RSA key-pair is :term:`implementation defined`.

.. macro:: PSA_KEY_TYPE_RSA_PUBLIC_KEY
    :definition: ((psa_key_type_t)0x4001)

    .. summary::
        RSA public key.

    The size of an RSA key is the bit size of the modulus.

    .. subsection:: Compatible algorithms

        .. hlist::
            :columns: 1

            *   `PSA_ALG_RSA_OAEP` (encryption only)
            *   `PSA_ALG_RSA_PKCS1V15_CRYPT` (encryption only)
            *   `PSA_ALG_RSA_PKCS1V15_SIGN` (signature verification only)
            *   `PSA_ALG_RSA_PKCS1V15_SIGN_RAW` (signature verification only)
            *   `PSA_ALG_RSA_PSS` (signature verification only)
            *   `PSA_ALG_RSA_PSS_ANY_SALT` (signature verification only)
            *   `PSA_ALG_RSABSSA` (signature verification only)
            *   `PSA_ALG_DETERMINISTIC_RSABSSA` (signature verification only)
            *   `PSA_ALG_RSABSSA_FDH` (signature verification only)

    .. subsection:: Key format

        The data format for import and export of a public key is the DER encoding of the representation defined by :RFC-title:`3279#2.3.1` as ``RSAPublicKey``.

        .. code-block:: none

            RSAPublicKey ::= SEQUENCE {
                modulus            INTEGER,    -- n
                publicExponent     INTEGER  }  -- e

.. macro:: PSA_KEY_TYPE_IS_RSA
    :definition: /* specification-defined value */

    .. summary::
        Whether a key type is an RSA key. This includes both key pairs and public keys.

    .. param:: type
        A key type: a value of type `psa_key_type_t`.

.. _rsa-bs-algorithms:

RSA blind signature algorithms
------------------------------

These algorithms extend those defined in :cite-title:`PSA-CRYPT` §10.7 *Asymmetric signature*, for use with signature functions.

The RSA blind signature scheme is defined in :RFC-title:`9474`.

All RSA blind signature variants utilize SHA-384 as the hash option, as well as the mask generation function (MGF) for EMSA-PSS (Encoding Methods for Signatures with Appendix - Probabilistic Signature Scheme) defined in :RFC-title:`8017`.

:RFC-title:`9474` defines four variants, two of which are `PSA_ALG_RSABSSA` with salt length of zero and 48 bytes, while the remaining two are `PSA_ALG_DETERMINISTIC_RSABSSA` with salt length of zero and 48 bytes respectively.
All four variants use Probabilistic Signature Scheme (PSS) RSA encoding functions. To utilize the full domain hash encoding function, `PSA_ALG_RSABSSA_FDH` is provided.

.. _rsa-deterministic-bs:

.. rubric:: Randomized and deterministic blind signatures

A deterministic RSA blind signature will blind a given message unaltered.

A randomized RSA blind signature prepends a 32 byte random value to a given message.

.. rubric:: Salt length

.. macro:: PSA_ALG_RSABSSA
    :definition: ((psa_algorithm_t) 0x??????)

    .. summary::
        Randomized RSA blind signature scheme with appendix (RSABSSA).

        .. versionadded:: 1.4
    
    This algorithm can be used with blind signature functions and signature verify functions.

    This algorithm is randomized: a 32 byte random will be prepended to the input message. See :RFC-title:`9474` §4.1.

    The allowed salt length is either zero or 48 bytes as defined in :RFC-title:`9474`

    .. note::

        The prepended random number is stored in the :code:`psa_blind_sign_ctx_t`.
    
    .. subsection:: Usage

        This is a blind signature algorithm. See algorithm-usage_.

    .. subsection:: Compatible key types

        | :code:`PSA_KEY_TYPE_RSA_KEY_PAIR`
        | :code:`PSA_KEY_TYPE_RSA_PUBLIC_KEY` (signature verification only)

.. macro:: PSA_ALG_DETERMINISTIC_RSABSSA
    :definition: ((psa_algorithm_t) 0x??????)

    .. summary::
        Deterministic RSA blind signature scheme with appendix (RSABSSA).

        .. versionadded:: 1.4
    
    This algorithm can be used with blind signature functions and signature verify functions.

    This algorithm is deterministic: the input message will not be prepended. See :RFC-title:`9474` §4.1.

    The allowed salt length is either zero or 48 bytes as defined in :RFC-title:`9474`

    .. subsection:: Usage

        This is a blind signature algorithm. See algorithm-usage_.
    
    .. subsection:: Compatible key types

        | :code:`PSA_KEY_TYPE_RSA_KEY_PAIR`
        | :code:`PSA_KEY_TYPE_RSA_PUBLIC_KEY` (signature verification only)

.. macro:: PSA_ALG_RSABSSA_FDH
    :definition: ((psa_algorithm_t) 0x??????)

    .. summary::
        Deterministic RSA blind signature scheme with appendix (RSABSSA) and full domain hash.

        .. versionadded:: 1.4
    
    This algorithm can be used with blind signature functions and signature verify functions.

    This algorithm is deterministic: the input message will not be prepended. See :RFC-title:`9474` §7.6.

    The allowed salt length is either zero or 48 bytes as defined in :RFC-title:`9474`

    .. subsection:: Usage

        This is a blind signature algorithm. See algorithm-usage_.
    
    .. subsection:: Compatible key types

        | :code:`PSA_KEY_TYPE_RSA_KEY_PAIR`
        | :code:`PSA_KEY_TYPE_RSA_PUBLIC_KEY` (signature verification only)