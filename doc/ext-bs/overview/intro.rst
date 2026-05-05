.. SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
.. SPDX-License-Identifier: CC-BY-SA-4.0 AND LicenseRef-Patent-license

Introduction
============

About Platform Security Architecture
------------------------------------

This document is one of a set of resources provided by Arm that can help organizations develop products that meet the security requirements of GlobalPlatform's PSA Certified evaluation scheme on Arm-based platforms.
The PSA Certified scheme provides a framework and methodology that helps silicon manufacturers, system software providers and OEMs to develop more secure products.
Arm resources that support PSA Certified range from threat models, standard architectures that simplify development and increase portability, and open-source partnerships that provide ready-to-use software.
You can read more about PSA Certified here at :url:`www.psacertified.org` and find more Arm resources here at :url:`developer.arm.com/platform-security-resources` and :url:`www.trustedfirmware.org`.

About the |API| BS Extension
-----------------------------

This document defines an extension to the :cite-title: `PSA-CRYPT` specification, to provide support for :term:`Blind Signature` (BS) algorithms.
Specifically, for commonly used schemes RSA-FDH, Clause-Blind-Schnorr, Lattice-based and Elgamal.

This specification must be read and implemented in conjunction with `[PSA-CRYPT]`.
All of the conventions, design considerations, and implementation considerations that are described in `[PSA-CRYPT]` apply to this specification.

Objectives for the BS Extension
--------------------------------

Background
~~~~~~~~~~

The justification for developing blind signature schemes due to their usage in electronic cash and voting systems, but also in authentication systems.

Selection of algorithms
~~~~~~~~~~~~~~~~~~~~~~~

RSA
^^^

The RSA blind signature is defined in :rfc-title:`9474` as RSABSSA (RSA Blind Signature with Appendix) with the following variants:

*   RSABSSA-SHA384-PSS-Randomized
*   RSABSSA-SHA384-PSSZERO-Randomized
*   RSABSSA-SHA384-PSS-Deterministic
*   RSABSSA-SHA384-PSSZERO-Deterministic

PSS in this case stands for Probabilistic signature scheme, while PSSZERO defines the salt length of zero. RSA full domain hash (RSA-FDH) is mentioned as an additional variant.

Clause-Blind-Schnorr
^^^^^^^^^^^^^^^^^^^^

In :cite-title:`CBS`, Fuchsbauer et al. proposed the Clause-Blind-Schnorr Scheme. For security reasons, the signer provides two commitments and the user computes two blinded messages from a single input message.
At the final step, the signer has to choose randomly which one to sign and send the index long with the generated signature.

Fair Fiat Shamir
^^^^^^^^^^^^^^^^

Stadler et al. proposed variations of the blind signature scheme, to allow third parties to link parts of the protocol together in order to trace back malicious users.
The additional entity is referred to as judge. :cite-title:`FSS`

Lattice BS
^^^^^^^^^^

Lattice based cryptography is known for being post-quantum resistant. Most lattice based blind signature schemes require intermediate checks and full protocol restart, which makes them difficult to integrate into a unified API.
Bouaziz et al. solved this issue, by integrating granular checks in each step which avoid interruption of the protocol.:cite-title:`LAT`
