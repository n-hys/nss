/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is the Netscape security libraries.
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are 
 * Copyright (C) 1994-2000 Netscape Communications Corporation.  All
 * Rights Reserved.
 * 
 * Contributor(s):
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 or later (the
 * "GPL"), in which case the provisions of the GPL are applicable 
 * instead of those above.  If you wish to allow use of your 
 * version of this file only under the terms of the GPL and not to
 * allow others to use your version of this file under the MPL,
 * indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by
 * the GPL.  If you do not delete the provisions above, a recipient
 * may use your version of this file under either the MPL or the
 * GPL.
 */

#ifndef _SECOIDT_H_
#define _SECOIDT_H_
/*
 * secoidt.h - public data structures for ASN.1 OID functions
 *
 * $Id$
 */

#include "secitem.h"

typedef struct SECOidDataStr SECOidData;
typedef struct SECAlgorithmIDStr SECAlgorithmID;

/*
** An X.500 algorithm identifier
*/
struct SECAlgorithmIDStr {
    SECItem algorithm;
    SECItem parameters;
};

/*
 * Misc object IDs - these numbers are for convenient handling.
 * They are mapped into real object IDs
 *
 * NOTE: the order of these entries must mach the array "oids" of SECOidData
 * in util/secoid.c.
 */
typedef enum {
    SEC_OID_UNKNOWN,
    SEC_OID_MD2,
    SEC_OID_MD4,
    SEC_OID_MD5,
    SEC_OID_SHA1,
    SEC_OID_RC2_CBC,
    SEC_OID_RC4,
    SEC_OID_DES_EDE3_CBC,
    SEC_OID_RC5_CBC_PAD,
    SEC_OID_DES_ECB,
    SEC_OID_DES_CBC,
    SEC_OID_DES_OFB,
    SEC_OID_DES_CFB,
    SEC_OID_DES_MAC,
    SEC_OID_DES_EDE,
    SEC_OID_ISO_SHA_WITH_RSA_SIGNATURE,
    SEC_OID_PKCS1_RSA_ENCRYPTION,
    SEC_OID_PKCS1_MD2_WITH_RSA_ENCRYPTION,
    SEC_OID_PKCS1_MD4_WITH_RSA_ENCRYPTION,
    SEC_OID_PKCS1_MD5_WITH_RSA_ENCRYPTION,
    SEC_OID_PKCS1_SHA1_WITH_RSA_ENCRYPTION,
    SEC_OID_PKCS5_PBE_WITH_MD2_AND_DES_CBC,
    SEC_OID_PKCS5_PBE_WITH_MD5_AND_DES_CBC,
    SEC_OID_PKCS5_PBE_WITH_SHA1_AND_DES_CBC,
    SEC_OID_PKCS7,
    SEC_OID_PKCS7_DATA,
    SEC_OID_PKCS7_SIGNED_DATA,
    SEC_OID_PKCS7_ENVELOPED_DATA,
    SEC_OID_PKCS7_SIGNED_ENVELOPED_DATA,
    SEC_OID_PKCS7_DIGESTED_DATA,
    SEC_OID_PKCS7_ENCRYPTED_DATA,
    SEC_OID_PKCS9_EMAIL_ADDRESS,
    SEC_OID_PKCS9_UNSTRUCTURED_NAME,
    SEC_OID_PKCS9_CONTENT_TYPE,
    SEC_OID_PKCS9_MESSAGE_DIGEST,
    SEC_OID_PKCS9_SIGNING_TIME,
    SEC_OID_PKCS9_COUNTER_SIGNATURE,
    SEC_OID_PKCS9_CHALLENGE_PASSWORD,
    SEC_OID_PKCS9_UNSTRUCTURED_ADDRESS,
    SEC_OID_PKCS9_EXTENDED_CERTIFICATE_ATTRIBUTES,
    SEC_OID_PKCS9_SMIME_CAPABILITIES,
    SEC_OID_AVA_COMMON_NAME,
    SEC_OID_AVA_COUNTRY_NAME,
    SEC_OID_AVA_LOCALITY,
    SEC_OID_AVA_STATE_OR_PROVINCE,
    SEC_OID_AVA_ORGANIZATION_NAME,
    SEC_OID_AVA_ORGANIZATIONAL_UNIT_NAME,
    SEC_OID_AVA_DN_QUALIFIER,
    SEC_OID_AVA_DC,

    SEC_OID_NS_TYPE_GIF,
    SEC_OID_NS_TYPE_JPEG,
    SEC_OID_NS_TYPE_URL,
    SEC_OID_NS_TYPE_HTML,
    SEC_OID_NS_TYPE_CERT_SEQUENCE,
    SEC_OID_MISSI_KEA_DSS_OLD,
    SEC_OID_MISSI_DSS_OLD,
    SEC_OID_MISSI_KEA_DSS,
    SEC_OID_MISSI_DSS,
    SEC_OID_MISSI_KEA,
    SEC_OID_MISSI_ALT_KEA,

    /* Netscape private certificate extensions */
    SEC_OID_NS_CERT_EXT_NETSCAPE_OK,
    SEC_OID_NS_CERT_EXT_ISSUER_LOGO,
    SEC_OID_NS_CERT_EXT_SUBJECT_LOGO,
    SEC_OID_NS_CERT_EXT_CERT_TYPE,
    SEC_OID_NS_CERT_EXT_BASE_URL,
    SEC_OID_NS_CERT_EXT_REVOCATION_URL,
    SEC_OID_NS_CERT_EXT_CA_REVOCATION_URL,
    SEC_OID_NS_CERT_EXT_CA_CRL_URL,
    SEC_OID_NS_CERT_EXT_CA_CERT_URL,
    SEC_OID_NS_CERT_EXT_CERT_RENEWAL_URL,
    SEC_OID_NS_CERT_EXT_CA_POLICY_URL,
    SEC_OID_NS_CERT_EXT_HOMEPAGE_URL,
    SEC_OID_NS_CERT_EXT_ENTITY_LOGO,
    SEC_OID_NS_CERT_EXT_USER_PICTURE,
    SEC_OID_NS_CERT_EXT_SSL_SERVER_NAME,
    SEC_OID_NS_CERT_EXT_COMMENT,
    SEC_OID_NS_CERT_EXT_LOST_PASSWORD_URL,
    SEC_OID_NS_CERT_EXT_CERT_RENEWAL_TIME,
    SEC_OID_NS_KEY_USAGE_GOVT_APPROVED,

    /* x.509 v3 Extensions */
    SEC_OID_X509_SUBJECT_DIRECTORY_ATTR,
    SEC_OID_X509_SUBJECT_KEY_ID,
    SEC_OID_X509_KEY_USAGE,
    SEC_OID_X509_PRIVATE_KEY_USAGE_PERIOD,
    SEC_OID_X509_SUBJECT_ALT_NAME,
    SEC_OID_X509_ISSUER_ALT_NAME,
    SEC_OID_X509_BASIC_CONSTRAINTS,
    SEC_OID_X509_NAME_CONSTRAINTS,
    SEC_OID_X509_CRL_DIST_POINTS,
    SEC_OID_X509_CERTIFICATE_POLICIES,
    SEC_OID_X509_POLICY_MAPPINGS,
    SEC_OID_X509_POLICY_CONSTRAINTS,
    SEC_OID_X509_AUTH_KEY_ID,
    SEC_OID_X509_EXT_KEY_USAGE,
    SEC_OID_X509_AUTH_INFO_ACCESS,

    SEC_OID_X509_CRL_NUMBER,
    SEC_OID_X509_REASON_CODE,
    SEC_OID_X509_INVALID_DATE,
    /* End of x.509 v3 Extensions */    

    SEC_OID_X500_RSA_ENCRYPTION,

    /* alg 1485 additions */
    SEC_OID_RFC1274_UID,
    SEC_OID_RFC1274_MAIL,

    /* PKCS 12 additions */
    SEC_OID_PKCS12,
    SEC_OID_PKCS12_MODE_IDS,
    SEC_OID_PKCS12_ESPVK_IDS,
    SEC_OID_PKCS12_BAG_IDS,
    SEC_OID_PKCS12_CERT_BAG_IDS,
    SEC_OID_PKCS12_OIDS,
    SEC_OID_PKCS12_PBE_IDS,
    SEC_OID_PKCS12_SIGNATURE_IDS,
    SEC_OID_PKCS12_ENVELOPING_IDS,
   /* SEC_OID_PKCS12_OFFLINE_TRANSPORT_MODE,
    SEC_OID_PKCS12_ONLINE_TRANSPORT_MODE, */
    SEC_OID_PKCS12_PKCS8_KEY_SHROUDING,
    SEC_OID_PKCS12_KEY_BAG_ID,
    SEC_OID_PKCS12_CERT_AND_CRL_BAG_ID,
    SEC_OID_PKCS12_SECRET_BAG_ID,
    SEC_OID_PKCS12_X509_CERT_CRL_BAG,
    SEC_OID_PKCS12_SDSI_CERT_BAG,
    SEC_OID_PKCS12_PBE_WITH_SHA1_AND_128_BIT_RC4,
    SEC_OID_PKCS12_PBE_WITH_SHA1_AND_40_BIT_RC4,
    SEC_OID_PKCS12_PBE_WITH_SHA1_AND_TRIPLE_DES_CBC,
    SEC_OID_PKCS12_PBE_WITH_SHA1_AND_128_BIT_RC2_CBC,
    SEC_OID_PKCS12_PBE_WITH_SHA1_AND_40_BIT_RC2_CBC,
    SEC_OID_PKCS12_RSA_ENCRYPTION_WITH_128_BIT_RC4,
    SEC_OID_PKCS12_RSA_ENCRYPTION_WITH_40_BIT_RC4,
    SEC_OID_PKCS12_RSA_ENCRYPTION_WITH_TRIPLE_DES,
    SEC_OID_PKCS12_RSA_SIGNATURE_WITH_SHA1_DIGEST,
    /* end of PKCS 12 additions */

    /* DSA signatures */
    SEC_OID_ANSIX9_DSA_SIGNATURE,
    SEC_OID_ANSIX9_DSA_SIGNATURE_WITH_SHA1_DIGEST,
    SEC_OID_BOGUS_DSA_SIGNATURE_WITH_SHA1_DIGEST,

    /* Verisign OIDs */
    SEC_OID_VERISIGN_USER_NOTICES,

    /* PKIX OIDs */
    SEC_OID_PKIX_CPS_POINTER_QUALIFIER,
    SEC_OID_PKIX_USER_NOTICE_QUALIFIER,
    SEC_OID_PKIX_OCSP,
    SEC_OID_PKIX_OCSP_BASIC_RESPONSE,
    SEC_OID_PKIX_OCSP_NONCE,
    SEC_OID_PKIX_OCSP_CRL,
    SEC_OID_PKIX_OCSP_RESPONSE,
    SEC_OID_PKIX_OCSP_NO_CHECK,
    SEC_OID_PKIX_OCSP_ARCHIVE_CUTOFF,
    SEC_OID_PKIX_OCSP_SERVICE_LOCATOR,
    SEC_OID_PKIX_REGCTRL_REGTOKEN,
    SEC_OID_PKIX_REGCTRL_AUTHENTICATOR,
    SEC_OID_PKIX_REGCTRL_PKIPUBINFO,
    SEC_OID_PKIX_REGCTRL_PKI_ARCH_OPTIONS,
    SEC_OID_PKIX_REGCTRL_OLD_CERT_ID,
    SEC_OID_PKIX_REGCTRL_PROTOCOL_ENC_KEY,
    SEC_OID_PKIX_REGINFO_UTF8_PAIRS,
    SEC_OID_PKIX_REGINFO_CERT_REQUEST,
    SEC_OID_EXT_KEY_USAGE_SERVER_AUTH,
    SEC_OID_EXT_KEY_USAGE_CLIENT_AUTH,
    SEC_OID_EXT_KEY_USAGE_CODE_SIGN,
    SEC_OID_EXT_KEY_USAGE_EMAIL_PROTECT,
    SEC_OID_EXT_KEY_USAGE_TIME_STAMP,
    SEC_OID_OCSP_RESPONDER,

    /* Netscape Algorithm OIDs */
    SEC_OID_NETSCAPE_SMIME_KEA,

    /* Skipjack OID -- ### mwelch temporary */
    SEC_OID_FORTEZZA_SKIPJACK,

    /* PKCS 12 V2 oids */
    SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_128_BIT_RC4,
    SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_40_BIT_RC4,
    SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_3KEY_TRIPLE_DES_CBC,
    SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_2KEY_TRIPLE_DES_CBC,
    SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_128_BIT_RC2_CBC,
    SEC_OID_PKCS12_V2_PBE_WITH_SHA1_AND_40_BIT_RC2_CBC,
    SEC_OID_PKCS12_SAFE_CONTENTS_ID,
    SEC_OID_PKCS12_PKCS8_SHROUDED_KEY_BAG_ID,

    SEC_OID_PKCS12_V1_KEY_BAG_ID,
    SEC_OID_PKCS12_V1_PKCS8_SHROUDED_KEY_BAG_ID,
    SEC_OID_PKCS12_V1_CERT_BAG_ID,
    SEC_OID_PKCS12_V1_CRL_BAG_ID,
    SEC_OID_PKCS12_V1_SECRET_BAG_ID,
    SEC_OID_PKCS12_V1_SAFE_CONTENTS_BAG_ID,
    SEC_OID_PKCS9_X509_CERT,
    SEC_OID_PKCS9_SDSI_CERT,
    SEC_OID_PKCS9_X509_CRL,
    SEC_OID_PKCS9_FRIENDLY_NAME,
    SEC_OID_PKCS9_LOCAL_KEY_ID,
    SEC_OID_PKCS12_KEY_USAGE,

    /*Diffe Helman OIDS */
    SEC_OID_X942_DIFFIE_HELMAN_KEY,

    /* Netscape other name types */
    SEC_OID_NETSCAPE_NICKNAME,

    /* Cert Server OIDS */
    SEC_OID_NETSCAPE_RECOVERY_REQUEST,

    /* New PSM certificate management OIDs */
    SEC_OID_CERT_RENEWAL_LOCATOR,
    SEC_OID_NS_CERT_EXT_SCOPE_OF_USE,
    
    /* CMS (RFC2630) OIDs */
    SEC_OID_CMS_EPHEMERAL_STATIC_DIFFIE_HELLMAN,
    SEC_OID_CMS_3DES_KEY_WRAP,
    SEC_OID_CMS_RC2_KEY_WRAP,

    /* SMIME attributes */
    SEC_OID_SMIME_ENCRYPTION_KEY_PREFERENCE,

    SEC_OID_TOTAL
} SECOidTag;

/* fake OID for DSS sign/verify */
#define SEC_OID_SHA SEC_OID_MISS_DSS

typedef enum {
    INVALID_CERT_EXTENSION,
    UNSUPPORTED_CERT_EXTENSION,
    SUPPORTED_CERT_EXTENSION
} SECSupportExtenTag;

struct SECOidDataStr {
    SECItem oid;
    SECOidTag offset;
    char *desc;
    unsigned long mechanism;
    SECSupportExtenTag supportedExtension;	/* only used for x.509 v3 extensions, so
						   that we can print the names of those
						   extensions that we don't even support */
};

#endif /* _SECOIDT_H_ */
