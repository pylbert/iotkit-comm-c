/*
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
* @file iotkit-comm_mdns.h
* @brief Header file of iotkit-comm MDNS.
*
* DataStructure of DiscoverContext and ServiceCache.
*/

#ifndef __IOTKIT_COMM_MDNS_H
#define __IOTKIT_COMM_MDNS_H

#include "iotkit-comm.h"

#ifndef DEBUG
    #define DEBUG 0
#endif

#define LOCAL_ADDRESS "127.0.0.1"
#define MAX_PROPERTIES 128

#define LONG_TIME 100000000
#define SHORT_TIME 10000

static uint32_t opinterface = kDNSServiceInterfaceIndexAny;
static volatile int timeOut = LONG_TIME;
int stopBlockingState = 0;

static char lastError[256];

/** Discover context to be passed around, which contains function pointers to
 * callback and user filter callback methods.
 */
typedef struct _DiscoverContext {
    bool (*userFilterCB) (ServiceQuery *);
    void (*callback) (void *, int32_t, void *);
    void *serviceSpec;
    CommHandle *commHandle;
} DiscoverContext;


/** Service cache to hold list of services discovered via DNS.
*/
typedef struct _ServiceCache {
    char *servicename;
    char *address;
    struct ServiceCache *next;
} ServiceCache;


ServiceCache *serviceCache = NULL;
int myaddressesCount = 0;
char **myaddresses = NULL;


bool serviceQueryFilter(ServiceQuery *srvQry, char *fullname, uint16_t PortAsNumber, uint16_t txtLen, const unsigned char *txtRecord);
char* serviceAddressFilter(ServiceQuery *srvQry, const char *hosttarget, const char *fullname, uint16_t portAsNumber);
bool extractNameFromServiceRecord(char *fullservicename, char *servicename);
bool isServiceLocal(const char *address);
bool setMyAddresses(void);

#endif
