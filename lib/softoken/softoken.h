/*
 * softoken.h - private data structures and prototypes for the softoken lib
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SOFTOKEN_H_
#define _SOFTOKEN_H_

#include "blapi.h"
#include "lowkeyti.h"
#include "softoknt.h"
#include "secoidt.h"

#include "pkcs11t.h"

SEC_BEGIN_PROTOS

/*
** RSA encryption/decryption. When encrypting/decrypting the output
** buffer must be at least the size of the public key modulus.
*/

/*
** Format some data into a PKCS#1 encryption block, preparing the
** data for RSA encryption.
**	"result" where the formatted block is stored (memory is allocated)
**	"modulusLen" the size of the formatted block
**	"blockType" what block type to use (SEC_RSABlock*)
**	"data" the data to format
*/
extern SECStatus RSA_FormatBlock(SECItem *result,
				 unsigned int modulusLen,
				 RSA_BlockType blockType,
				 SECItem *data);
/*
** Similar, but just returns a pointer to the allocated memory, *and*
** will *only* format one block, even if we (in the future) modify
** RSA_FormatBlock() to loop over multiples of modulusLen.
*/
extern unsigned char *RSA_FormatOneBlock(unsigned int modulusLen,
					 RSA_BlockType blockType,
					 SECItem *data);



/*
 * convenience wrappers for doing single RSA operations. They create the
 * RSA context internally and take care of the formatting
 * requirements. Blinding happens automagically within RSA_Sign and
 * RSA_DecryptBlock.
 */
extern
SECStatus RSA_Sign(NSSLOWKEYPrivateKey *key, unsigned char *output,
		       unsigned int *outputLen, unsigned int maxOutputLen,
		       unsigned char *input, unsigned int inputLen);
extern
SECStatus RSA_HashSign(SECOidTag hashOid,
			NSSLOWKEYPrivateKey *key, unsigned char *sig,
			unsigned int *sigLen, unsigned int maxLen,
			unsigned char *hash, unsigned int hashLen);
extern
SECStatus RSA_SignPSS(CK_RSA_PKCS_PSS_PARAMS *pss_params,
		      NSSLOWKEYPrivateKey *key, 
		      unsigned char *output, unsigned int *output_len, 
		      unsigned int max_output_len, const unsigned char *input,
		      unsigned int input_len);
extern
SECStatus RSA_CheckSign(NSSLOWKEYPublicKey *key, unsigned char *sign,
			    unsigned int signLength, unsigned char *hash,
			    unsigned int hashLength);
extern
SECStatus RSA_HashCheckSign(SECOidTag hashOid,
			    NSSLOWKEYPublicKey *key, unsigned char *sig,
			    unsigned int sigLen, unsigned char *digest,
			    unsigned int digestLen);
extern
SECStatus RSA_CheckSignPSS(CK_RSA_PKCS_PSS_PARAMS *pss_params,
			   NSSLOWKEYPublicKey *key,
			   const unsigned char *sign, unsigned int sign_len,
			   const unsigned char *hash, unsigned int hash_len);
extern
SECStatus RSA_CheckSignRecover(NSSLOWKEYPublicKey *key, unsigned char *data,
    			    unsigned int *data_len,unsigned int max_output_len, 
			    unsigned char *sign, unsigned int sign_len);
extern
SECStatus RSA_EncryptBlock(NSSLOWKEYPublicKey *key, unsigned char *output,
			   unsigned int *outputLen, unsigned int maxOutputLen,
			   unsigned char *input, unsigned int inputLen);
extern
SECStatus RSA_DecryptBlock(NSSLOWKEYPrivateKey *key, unsigned char *output,
			   unsigned int *outputLen, unsigned int maxOutputLen,
			   unsigned char *input, unsigned int inputLen);

extern
SECStatus RSA_EncryptOAEP(CK_RSA_PKCS_OAEP_PARAMS *oaepParams,
                          NSSLOWKEYPublicKey *key,
                          unsigned char *output, unsigned int *outputLen,
                          unsigned int maxOutputLen,
                          const unsigned char *input, unsigned int inputLen);

extern
SECStatus RSA_DecryptOAEP(CK_RSA_PKCS_OAEP_PARAMS *oaepParams,
                          NSSLOWKEYPrivateKey *key,
                          unsigned char *output, unsigned int *outputLen,
                          unsigned int maxOutputLen,
                          const unsigned char *input, unsigned int inputLen);

/*
 * added to make pkcs #11 happy
 *   RAW is RSA_X_509
 */
extern
SECStatus RSA_SignRaw( NSSLOWKEYPrivateKey *key, unsigned char *output,
			 unsigned int *output_len, unsigned int maxOutputLen,
			 unsigned char *input, unsigned int input_len);
extern
SECStatus RSA_CheckSignRaw( NSSLOWKEYPublicKey *key, unsigned char *sign, 
			    unsigned int sign_len, unsigned char *hash, 
			    unsigned int hash_len);
extern
SECStatus RSA_CheckSignRecoverRaw( NSSLOWKEYPublicKey *key, unsigned char *data,
			    unsigned int *data_len, unsigned int max_output_len,
			    unsigned char *sign, unsigned int sign_len);
extern
SECStatus RSA_EncryptRaw( NSSLOWKEYPublicKey *key, unsigned char *output,
			    unsigned int *output_len,
			    unsigned int max_output_len, 
			    unsigned char *input, unsigned int input_len);
extern
SECStatus RSA_DecryptRaw(NSSLOWKEYPrivateKey *key, unsigned char *output,
			     unsigned int *output_len,
    			     unsigned int max_output_len,
			     unsigned char *input, unsigned int input_len);
#ifdef NSS_ENABLE_ECC
/*
** pepare an ECParam structure from DEREncoded params
 */
extern SECStatus EC_FillParams(PRArenaPool *arena,
                               const SECItem *encodedParams, ECParams *params);
extern SECStatus EC_DecodeParams(const SECItem *encodedParams, 
				ECParams **ecparams);
extern SECStatus EC_CopyParams(PRArenaPool *arena, ECParams *dstParams,
              			const ECParams *srcParams);
#endif


/*
** Prepare a buffer for padded CBC encryption, growing to the appropriate 
** boundary, filling with the appropriate padding.
**
** blockSize must be a power of 2.
**
** We add from 1 to blockSize bytes -- we *always* grow.
** The extra bytes contain the value of the length of the padding:
** if we have 2 bytes of padding, then the padding is "0x02, 0x02".
**
** NOTE: If arena is non-NULL, we re-allocate from there, otherwise
** we assume (and use) PR memory (re)allocation.
*/
extern unsigned char * CBC_PadBuffer(PRArenaPool *arena, unsigned char *inbuf, 
                                     unsigned int inlen, unsigned int *outlen,
				     int blockSize);


/****************************************/
/*
** Power-Up selftests required for FIPS and invoked only
** under PKCS #11 FIPS mode.
*/
extern CK_RV sftk_fipsPowerUpSelfTest( void ); 

/*
** make known fixed PKCS #11 key types to their sizes in bytes
*/	
unsigned long sftk_MapKeySize(CK_KEY_TYPE keyType);

/*
** FIPS 140-2 auditing
*/
extern PRBool sftk_audit_enabled;

extern void sftk_LogAuditMessage(NSSAuditSeverity severity, 
				 NSSAuditType, const char *msg);

extern void sftk_AuditCreateObject(CK_SESSION_HANDLE hSession,
			CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount,
			CK_OBJECT_HANDLE_PTR phObject, CK_RV rv);

extern void sftk_AuditCopyObject(CK_SESSION_HANDLE hSession,
			CK_OBJECT_HANDLE hObject,
			CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount,
			CK_OBJECT_HANDLE_PTR phNewObject, CK_RV rv);

extern void sftk_AuditDestroyObject(CK_SESSION_HANDLE hSession,
			CK_OBJECT_HANDLE hObject, CK_RV rv);

extern void sftk_AuditGetObjectSize(CK_SESSION_HANDLE hSession,
			CK_OBJECT_HANDLE hObject, CK_ULONG_PTR pulSize,
			CK_RV rv);

extern void sftk_AuditGetAttributeValue(CK_SESSION_HANDLE hSession,
			CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate,
			CK_ULONG ulCount, CK_RV rv);

extern void sftk_AuditSetAttributeValue(CK_SESSION_HANDLE hSession,
			CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate,
			CK_ULONG ulCount, CK_RV rv);

extern void sftk_AuditCryptInit(const char *opName,
			CK_SESSION_HANDLE hSession,
			CK_MECHANISM_PTR pMechanism,
			CK_OBJECT_HANDLE hKey, CK_RV rv);

extern void sftk_AuditGenerateKey(CK_SESSION_HANDLE hSession,
			CK_MECHANISM_PTR pMechanism,
			CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount,
			CK_OBJECT_HANDLE_PTR phKey, CK_RV rv);

extern void sftk_AuditGenerateKeyPair(CK_SESSION_HANDLE hSession,
			CK_MECHANISM_PTR pMechanism,
			CK_ATTRIBUTE_PTR pPublicKeyTemplate,
			CK_ULONG ulPublicKeyAttributeCount,
			CK_ATTRIBUTE_PTR pPrivateKeyTemplate,
			CK_ULONG ulPrivateKeyAttributeCount,
			CK_OBJECT_HANDLE_PTR phPublicKey,
			CK_OBJECT_HANDLE_PTR phPrivateKey, CK_RV rv);

extern void sftk_AuditWrapKey(CK_SESSION_HANDLE hSession,
			CK_MECHANISM_PTR pMechanism,
			CK_OBJECT_HANDLE hWrappingKey, CK_OBJECT_HANDLE hKey,
			CK_BYTE_PTR pWrappedKey,
			CK_ULONG_PTR pulWrappedKeyLen, CK_RV rv);

extern void sftk_AuditUnwrapKey(CK_SESSION_HANDLE hSession,
			CK_MECHANISM_PTR pMechanism,
			CK_OBJECT_HANDLE hUnwrappingKey,
			CK_BYTE_PTR pWrappedKey, CK_ULONG ulWrappedKeyLen,
			CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulAttributeCount,
			CK_OBJECT_HANDLE_PTR phKey, CK_RV rv);

extern void sftk_AuditDeriveKey(CK_SESSION_HANDLE hSession,
			CK_MECHANISM_PTR pMechanism,
			CK_OBJECT_HANDLE hBaseKey,
			CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulAttributeCount,
			CK_OBJECT_HANDLE_PTR phKey, CK_RV rv);

extern void sftk_AuditDigestKey(CK_SESSION_HANDLE hSession,
			CK_OBJECT_HANDLE hKey, CK_RV rv);

/*
** FIPS 140-2 Error state
*/
extern PRBool sftk_fatalError;

/*
** macros to check for forked child process after C_Initialize
*/
#if defined(XP_UNIX) && !defined(NO_FORK_CHECK)

#ifdef DEBUG

#define FORK_ASSERT() \
    { \
        char* forkAssert = getenv("NSS_STRICT_NOFORK"); \
        if ( (!forkAssert) || (0 == strcmp(forkAssert, "1")) ) { \
            PORT_Assert(0); \
        } \
    }

#else

#define FORK_ASSERT()

#endif

/* we have 3 methods of implementing the fork checks :
 * - Solaris "mixed" method
 * - pthread_atfork method
 * - getpid method
 */

#if !defined (CHECK_FORK_MIXED) && !defined(CHECK_FORK_PTHREAD) && \
    !defined (CHECK_FORK_GETPID)

/* Choose fork check method automatically unless specified
 * This section should be updated as more platforms get pthread fixes
 * to unregister fork handlers in dlclose.
 */

#ifdef SOLARIS

/* Solaris 8, s9 use PID checks, s10 uses pthread_atfork */

#define CHECK_FORK_MIXED

#elif defined(LINUX)

#define CHECK_FORK_PTHREAD

#else

/* Other Unix platforms use only PID checks. Even if pthread_atfork is
 * available, the behavior of dlclose isn't guaranteed by POSIX to
 * unregister the fork handler. */

#define CHECK_FORK_GETPID

#endif

#endif

#if defined(CHECK_FORK_MIXED)

extern PRBool usePthread_atfork;
#include <unistd.h>
extern pid_t myPid;
extern PRBool forked;

#define PARENT_FORKED() (usePthread_atfork ? forked : (myPid && myPid != getpid()))

#elif defined(CHECK_FORK_PTHREAD)

extern PRBool forked;

#define PARENT_FORKED() forked

#elif defined(CHECK_FORK_GETPID)

#include <unistd.h>
extern pid_t myPid;

#define PARENT_FORKED() (myPid && myPid != getpid())
    
#endif

extern PRBool parentForkedAfterC_Initialize;
extern PRBool sftkForkCheckDisabled;

#define CHECK_FORK() \
    do { \
        if (!sftkForkCheckDisabled && PARENT_FORKED()) { \
            FORK_ASSERT(); \
            return CKR_DEVICE_ERROR; \
        } \
    } while (0)

#define SKIP_AFTER_FORK(x) if (!parentForkedAfterC_Initialize) x

#define ENABLE_FORK_CHECK() \
    { \
        char* doForkCheck = getenv("NSS_STRICT_NOFORK"); \
        if ( doForkCheck && !strcmp(doForkCheck, "DISABLED") ) { \
            sftkForkCheckDisabled = PR_TRUE; \
        } \
    }


#else

/* non-Unix platforms, or fork check disabled */

#define CHECK_FORK()
#define SKIP_AFTER_FORK(x) x
#define ENABLE_FORK_CHECK()

#ifndef NO_FORK_CHECK
#define NO_FORK_CHECK
#endif

#endif


SEC_END_PROTOS

#endif /* _SOFTOKEN_H_ */
