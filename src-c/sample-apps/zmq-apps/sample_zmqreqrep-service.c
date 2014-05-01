/*
 * ZMQ REQ/REP sample program through Edison API
 * Copyright (c) 2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 */


#include <stdio.h>
#include <cJSON.h>
#include <stdbool.h>
#include <sys/types.h>
#include "edisonapi.h"
#include "util.h"

ServiceDescription *serviceDescription = NULL;

void message_callback(void *client, char *message, Context context) {
    fprintf(stderr,"Message received in Server: %s\n", message);
}

void callback(void *handle, int32_t error_code,CommServiceHandle *serviceHandle)
{
        if (serviceHandle != NULL) {
	    void *client;
	    Context context;
	    while(1) {
            serviceHandle->sendTo(client,"train bike car",context);
            serviceHandle->receive(message_callback);
            sleep(2);
        }
        } else {
                    puts("\nComm Handle is NULL\n");
                }
}



int main(void) {

    void *handle;
	puts("Sample program to test the Edison ZMQ req/rep plugin !!");
    serviceDescription = (ServiceDescription *) parseServiceDescription("../serviceSpecs/temperatureServiceZMQREQREP.json");

    if (serviceDescription)
	    handle = advertiseService(serviceDescription, callback);

	return 0;
}

