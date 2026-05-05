.. SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
.. SPDX-License-Identifier: CC-BY-SA-4.0 AND LicenseRef-Patent-license

.. header:: psa/crypto-bs
    :seq: 3

.. _ffs:

Fair Fiat Shamir blind signatures
=================================

.. _ffs_keys:

Fair Fiat Shamir blind signature keys
-------------------------------------

The |API| supports Fair Fiat Shamir blind signatures (FFS-BS).

.. macro:: PSA_KEY_TYPE_FFS_BS_KEY_PAIR
    :definition: ((psa_key_type_t)0x?????)

    .. summary::
        FFS-BS key pair: both the private and public key.

        .. versionadded:: 1.4
    
    The bit size for a security parameter k (e.g. k > 80) is defined in :cite-title:`FFS`.

    * public key    :``key_bits = rsa public key``
    * private key:  :``key_bits = (k+1) * size of n``

    .. subsection:: Compatible algorithms

        .. hlist::

            *   `PSA_ALG_FFS`
        
    .. subsection:: Key format

        A Fair fiat shamir key pair is the :math:`(pk,sk)` pair of public key and secret key, which are randomly generated and hashed. See `[FFS]` §4.1.
    
        In calls to :code:`psa_import_key()` and :code:`psa_export_key()`, the key-pair data format is the raw public and secret key, separated by 0x00.

        .. rationale::

            The key format is not standardized.

        See `PSA_KEY_TYPE_FFS_BS_PUBLIC_KEY` for the data format used when exporting the public key with :code:`psa_export_public_key()`.

        .. admonition:: Implementation note

            An implementation can optionally compute and store the :math:`(pk,sk)` values, to accelerate operations that use the key.
        
    .. subsection:: Key derivation

        Key derivation is not possible. Public and secret keys must be generated simultaneously.
       
.. macro:: PSA_KEY_TYPE_FFS_BS_PUBLIC_KEY
    :definition: ((psa_key_type_t)0x????)

    .. summary::
        FFS-BS public key.

        .. versionadded:: 1.4

    The bit size for n is not specified.

    .. subsection:: Compatible algorithms

        .. hlist::

            *   `PSA_ALG_FFS`
    
    .. subsection:: Key format

        A fair fiat shamir public key is defined as :math:`pk = (n, y)`, where :math:`n` is a public modulus and :math:`y` a random number. See `[FFS]` §4.1.

        In calls to :code:`psa_import_key()`, :code:`psa_export_key()`, and :code:`psa_export_public_key()`, the public-key data format is :math:`pk`.

        .. rationale::

            The key format is not standardized.

        The size of the public key is related to the size of n.

.. macro:: PSA_KEY_TYPE_IS_FFS_BS
    :definition: /* specification-defined value */

    .. summary::
        Whether a key type is FFS-BS key, either a key pair or public key.

        .. versionadded:: 1.4
    
    .. param:: type
        A key type: a value of type :code:`psa_key_type_t`

.. _lat-bs-algorithms::

Fair fiat shamir blind signature algorithm
------------------------------------------

This algorithm utilizes fair one-out-of-two oblivious transfer.

The FFS-BS scheme is defined by Stadler et al. in :cite-title:`FFS`.

.. macro:: PSA_ALG_FFS
    :definition: ((psa_algorithm_t)0x?????)

    .. summary::
        Fair fiat shamir blind signature algorithm based on Stadler et al.:cite-title:`FFS`

        .. versionadded:: 1.4
    
    This algorithm can only be used with the blind signature commitment generation, message blinding, blind signing, signature unblinding and signature verification functions.

    .. subsection:: Compatible key types

        | :code:`PSA_KEY_TYPE_FFS_BS_KEY_PAIR`
        | :code:`PSA_KEY_TYPE_FFS_BS_PUBLIC_KEY` (signature verification only)