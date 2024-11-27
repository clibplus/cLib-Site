#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../main.h"

void DocHandler(cWS *web, cWR *r, WebRoute *route, int socket) {
	String template = DesignDoc(web, r, route, socket);

	if(template.idx < 2)
		printf("Failed\n");

	char num[100] = {0};
	sprintf(num, "%ld", template.idx);

	Map new_headers = NewMap();
    new_headers.Append(&new_headers, "Content-Type", "text/html; charset=UTF-8");
	new_headers.Append(&new_headers, "Content-Length", (const char *)&num);
    new_headers.Append(&new_headers, "Connection", "close");

	SendResponse(web, socket, OK, new_headers, ((Map){}), template.data);
	template.Destruct(&template);
}