/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is PRIVATE to SSL.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __tls13con_h_
#define __tls13con_h_

#include "sslexp.h"

typedef enum {
    StaticSharedSecret,
    EphemeralSharedSecret
} SharedSecretType;

typedef enum {
    tls13_extension_allowed,
    tls13_extension_disallowed,
    tls13_extension_unknown
} tls13ExtensionStatus;

#define TLS13_MAX_FINISHED_SIZE 64

SECStatus tls13_UnprotectRecord(
    sslSocket *ss, SSL3Ciphertext *cText, sslBuffer *plaintext,
    SSL3AlertDescription *alert);

#if defined(WIN32)
#define __func__ __FUNCTION__
#endif

void tls13_SetHsState(sslSocket *ss, SSL3WaitState ws,
                      const char *func, const char *file, int line);
#define TLS13_SET_HS_STATE(ss, ws) \
    tls13_SetHsState(ss, ws, __func__, __FILE__, __LINE__)

/* Return PR_TRUE if the socket is in one of the given states, else return
 * PR_FALSE. Only call the macro not the function, because the trailing
 * wait_invalid is needed to terminate the argument list. */
PRBool tls13_InHsState(sslSocket *ss, ...);
#define TLS13_IN_HS_STATE(ss, ...) \
    tls13_InHsState(ss, __VA_ARGS__, wait_invalid)

SSLHashType tls13_GetHashForCipherSuite(ssl3CipherSuite suite);
SSLHashType tls13_GetHash(const sslSocket *ss);
unsigned int tls13_GetHashSizeForHash(SSLHashType hash);
unsigned int tls13_GetHashSize(const sslSocket *ss);
CK_MECHANISM_TYPE tls13_GetHkdfMechanism(sslSocket *ss);
SECStatus tls13_ComputeHash(sslSocket *ss, SSL3Hashes *hashes,
                            const PRUint8 *buf, unsigned int len);
SECStatus tls13_ComputeHandshakeHashes(sslSocket *ss,
                                       SSL3Hashes *hashes);
SECStatus tls13_DeriveSecretNullHash(sslSocket *ss, PK11SymKey *key,
                                     const char *label,
                                     unsigned int labelLen,
                                     PK11SymKey **dest);
void tls13_FatalError(sslSocket *ss, PRErrorCode prError,
                      SSL3AlertDescription desc);
SECStatus tls13_SetupClientHello(sslSocket *ss);
SECStatus tls13_MaybeDo0RTTHandshake(sslSocket *ss);
PRInt32 tls13_LimitEarlyData(sslSocket *ss, SSL3ContentType type, PRInt32 toSend);
PRBool tls13_AllowPskCipher(const sslSocket *ss,
                            const ssl3CipherSuiteDef *cipher_def);
PRBool tls13_PskSuiteEnabled(sslSocket *ss);
SECStatus tls13_WriteExtensionsWithBinder(sslSocket *ss, sslBuffer *extensions);
SECStatus tls13_HandleClientHelloPart2(sslSocket *ss,
                                       const SECItem *suites,
                                       sslSessionID *sid,
                                       const PRUint8 *msg,
                                       unsigned int len);
SECStatus tls13_HandleServerHelloPart2(sslSocket *ss);
SECStatus tls13_HandlePostHelloHandshakeMessage(sslSocket *ss, PRUint8 *b,
                                                PRUint32 length);
SECStatus tls13_ConstructHelloRetryRequest(sslSocket *ss,
                                           const sslNamedGroupDef *selectedGroup,
                                           PRUint8 *cookie, unsigned int cookieLen,
                                           sslBuffer *buffer);
SECStatus tls13_HandleHelloRetryRequest(sslSocket *ss, PRUint8 *b,
                                        PRUint32 length);
void tls13_DestroyKeyShareEntry(TLS13KeyShareEntry *entry);
void tls13_DestroyKeyShares(PRCList *list);
SECStatus tls13_CreateKeyShare(sslSocket *ss, const sslNamedGroupDef *groupDef);
void tls13_DestroyEarlyData(PRCList *list);
void tls13_CipherSpecAddRef(ssl3CipherSpec *spec);
void tls13_CipherSpecRelease(ssl3CipherSpec *spec);
void tls13_DestroyCipherSpecs(PRCList *list);
tls13ExtensionStatus tls13_ExtensionStatus(PRUint16 extension,
                                           SSLHandshakeType message);
SECStatus tls13_ProtectRecord(sslSocket *ss,
                              ssl3CipherSpec *cwSpec,
                              SSL3ContentType type,
                              const PRUint8 *pIn,
                              PRUint32 contentLen,
                              sslBuffer *wrBuf);
PRInt32 tls13_Read0RttData(sslSocket *ss, void *buf, PRInt32 len);
SECStatus tls13_HandleEarlyApplicationData(sslSocket *ss, sslBuffer *origBuf);
PRBool tls13_ClientAllow0Rtt(const sslSocket *ss, const sslSessionID *sid);
PRUint16 tls13_EncodeDraftVersion(SSL3ProtocolVersion version);
PRUint16 tls13_EncodeAltDraftVersion(SSL3ProtocolVersion version);
SECStatus tls13_NegotiateVersion(sslSocket *ss,
                                 const TLSExtension *supported_versions);

PRBool tls13_IsReplay(const sslSocket *ss, const sslSessionID *sid);
void tls13_AntiReplayRollover(PRTime now);
SECStatus SSLExp_SetupAntiReplay(PRTime window, unsigned int k,
                                 unsigned int bits);

SECStatus SSLExp_HelloRetryRequestCallback(PRFileDesc *fd,
                                           SSLHelloRetryRequestCallback cb,
                                           void *arg);
SECStatus SSLExp_UseAltServerHelloType(PRFileDesc *fd, PRBool enable);

#endif /* __tls13con_h_ */
