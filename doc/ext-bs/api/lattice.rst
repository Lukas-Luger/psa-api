.. SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
.. SPDX-License-Identifier: CC-BY-SA-4.0 AND LicenseRef-Patent-license

.. header:: psa/crypto-bs
    :seq: 4

.. _lattice:

Lattice-based blind signatures
=====================================

.. _lattice_keys:

Lattice-based blind signature keys
-----------------------------------------

The |API| supports Lattice-based blind signatures (L-BS).

.. macro:: PSA_KEY_TYPE_LAT_BS_KEY_PAIR
    :definition: ((psa_key_type_t)0x?????)

    .. summary::
        LAT-BS key pair: both the private and public key.

        .. versionadded:: 1.4
    
    The bit size for 100-bit security is defined in :cite-title:`LAT`.

    * public key  : ``key_bits = 6 816 000``
    * private key : ``key_bits = 46 920 000``

    See also Table 3 in `[LAT]`.

    .. subsection:: Compatible algorithms

        .. hlist::

            *   `PSA_ALG_LATTICE`
    
    .. subsection:: Key format

        A Lattice key pair is the :math:`(pk,sk)` pair of public key and secret key, which are randomly generated and hashed. See `[LAT]` §4.1.

        In calls to :code:`psa_import_key()` and :code:`psa_export_key()`, the key-pair data format is the raw public and secret key, separated by 0x00.

        .. rationale::

            The key format is not standardized.

        See `PSA_KEY_TYPE_LAT_BS_PUBLIC_KEY` for the data format used when exporting the public key with :code:`psa_export_public_key()`.

        .. admonition:: Implementation note

            An implementation can optionally compute and store the :math:`(pk,sk)` values, to accelerate operations that use the key.
        
    .. subsection:: Key derivation

        Key derivation is not possible. Public and secret keys must be generated simultaneously.
    
.. macro:: PSA_KEY_TYPE_LAT_BS_PUBLIC_KEY
    :definition: ((psa_key_type_t)0x????)

    .. summary::
        LAT-BS public key.

        .. versionadded:: 1.4

    The bit size for 100-bit security is defined in :cite-title:`LAT`.

    .. subsection:: Compatible algorithms

        .. hlist::

            *   `PSA_ALG_LATTICE`
    
    .. subsection:: Key format

        A Lattice public key is defined as :math:`pk = (p, a)`, where :math:`a` is a polynomial vector and :math:`p = h_a(s)`, where :math:`h_a` is a hash function and :math:`s` is part of the secret key. See `[LAT]` §4.1.

        In calls to :code:`psa_import_key()`, :code:`psa_export_key()`, and :code:`psa_export_public_key()`, the public-key data format is :math:`pk`.

        .. rationale::

            The key format is not standardized.

        The size of the public key is fixed to 6 816 000 bits.

.. macro:: PSA_KEY_TYPE_IS_LAT_BS
    :definition: /* specification-defined value */

    .. summary::
        Whether a key type is LAT-BS key, either a key pair or public key.

        .. versionadded:: 1.4
    
    .. param:: type
        A key type: a value of type :code:`psa_key_type_t`

.. _lat-bs-algorithms::

Lattice-based blind signature algorithm
---------------------------------------

This algorithm utilizes rejection sampling and a trapdoor function, to sample short gaussian vectors such that :math:`h_a(v) = 0 mod q`.

The LAT-BS scheme is defined by Bouaziz-Ermann et al. in :cite-title:`LAT`.

.. macro:: PSA_ALG_LATTICE
    :definition: ((psa_algorithm_t)0x?????)

    .. summary::
        Lattice-based blind signature algorithm based on Bouaziz-Ermann et al.:cite-title:`LAT`

        .. versionadded:: 1.4
    
    This algorithm can only be used with the blind signature commitment generation, message blinding, blind signing, signature unblinding and signature verification functions.

    .. subsection:: Compatible key types

        | :code:`PSA_KEY_TYPE_LAT_BS_KEY_PAIR`
        | :code:`PSA_KEY_TYPE_LAT_BS_PUBLIC_KEY` (signature verification only)

