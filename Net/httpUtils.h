// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include "OSMisc.h"
#include "OSNet.h"

inline int sendsimplehttpgetreq(SOCKET sock, char* url)
{
	int ret = EXIT_FAILURE;
	char* sendbuf = NULL;
	int sendbuflen = 0;
	char* address = NULL;
	int count = 0;
	char* ptr = NULL;

	sendbuf = (char*)calloc(strlen(url)+256, 1);
	if (sendbuf == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("sendhttpgetreq error (%s) : %s(sock=%d, url=%s)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY],
			(int)sock, url));
		return EXIT_OUT_OF_MEMORY;
	}

	ptr = strchr(url+strlen("http://"), '/');
	if (ptr == NULL) ptr = url+strlen(url);
	count = ptr-url-strlen("http://");
	if (count <= 0)
	{
		PRINT_DEBUG_ERROR_OSNET(("sendhttpgetreq error (%s) : %s(sock=%d, url=%s)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_INVALID_PARAMETER],
			(int)sock, url));
		free(sendbuf);
		return EXIT_INVALID_PARAMETER;
	}

	address = (char*)calloc(count+1, 1);
	if (address == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("sendhttpgetreq error (%s) : %s(sock=%d, url=%s)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY],
			(int)sock, url));
		free(sendbuf);
		return EXIT_OUT_OF_MEMORY;
	}

	memcpy(address, url+strlen("http://"), count);
	sprintf(sendbuf,
		"GET %s HTTP/1.1\r\n"
		"Host: %s\r\n"
//		"Accept: text/html\r\n"
		"\r\n",
		url+strlen("http://")+strlen(address), address);
	free(address);
	sendbuflen = (int)strlen(sendbuf);
	ret = sendall(sock, sendbuf, sendbuflen);
	if (ret != EXIT_SUCCESS)
	{
		free(sendbuf);
		return ret;
	}

	free(sendbuf);

	return EXIT_SUCCESS;
}

/*

Need free(*pszStatus), free(*pContentType), free(*pContent)...

*/
inline int recvsimplehttpresp(SOCKET sock, int* pStatus, char** pszStatus, char** pContentType, int* pContentLength, char** pContent, int maxrecvbuflen, int* pBytesReceived)
{
	int ret = EXIT_FAILURE;
	char* recvbuf = NULL;
	char* ptr = NULL;
	char* ptr2 = NULL;
	int count = 0;
	double httpver = 0;

	*pStatus = 0;
	*pszStatus = NULL;
	*pContentType = NULL;
	*pContentLength = 0;
	*pContent = NULL;
	*pBytesReceived = 0;

	recvbuf = (char*)calloc(maxrecvbuflen+1, 1);
	if (recvbuf == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		return EXIT_OUT_OF_MEMORY;
	}

	// Should enable other line endings...

	ret = recvuntilstr(sock, recvbuf, "\r\n\r\n", maxrecvbuflen, pBytesReceived);
	if (ret != EXIT_SUCCESS)
	{
		free(recvbuf);
		return ret;
	}

	ptr = strstr(recvbuf, "HTTP/");
	if (ptr == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_INVALID_DATA],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		free(recvbuf);
		return EXIT_INVALID_DATA;
	}

	*pszStatus = (char*)calloc(256, 1);
	if (*pszStatus == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		free(recvbuf);
		return EXIT_OUT_OF_MEMORY;
	}

	if (sscanf(ptr, "HTTP/%lf %d %[^\r\n]255s", &httpver, pStatus, *pszStatus) != 3)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_INVALID_DATA],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		free(*pszStatus);
		free(recvbuf);
		return EXIT_INVALID_DATA;
	}

	if (strstrbeginend(ptr, "Content-Type: ", "\r\n", &ptr2, &count) == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_INVALID_DATA],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		free(*pszStatus);
		free(recvbuf);
		return EXIT_INVALID_DATA;
	}

	*pContentType = (char*)calloc(count+1, 1);
	if (*pContentType == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		free(*pszStatus);
		free(recvbuf);
		return EXIT_OUT_OF_MEMORY;
	}

	memcpy(*pContentType, ptr2, count);

	ptr = strstr(recvbuf, "Content-Length: ");
	if (ptr == NULL)
	{
		free(*pContentType);
		free(*pszStatus);
		free(recvbuf);
		return EXIT_SUCCESS;
	}
	
	if ((sscanf(ptr, "Content-Length: %d", pContentLength) != 1)||(*pContentLength < 0))
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_INVALID_DATA],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		free(*pContentType);
		free(*pszStatus);
		free(recvbuf);
		return EXIT_INVALID_DATA;
	}
	
	free(recvbuf);

	*pContent = (char*)calloc(*pContentLength+1, 1);
	if (*pContent == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehttpresp error (%s) : %s"
			"(sock=%d, *pStatus=%d, *pszStatus=%s, *pContentType=%s, *pContentLength=%d, *pContent=%#x, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY],
			(int)sock, *pStatus, *pszStatus, *pContentType, *pContentLength, *pContent, maxrecvbuflen, *pBytesReceived));
		free(*pContentType);
		free(*pszStatus);
		return EXIT_OUT_OF_MEMORY;
	}

	ret = recvall(sock, *pContent, *pContentLength);
	if (ret != EXIT_SUCCESS)
	{
		free(*pContent);
		free(*pContentType);
		free(*pszStatus);
		return ret;
	}

	*pBytesReceived += *pContentLength;

	return EXIT_SUCCESS;
}

/*

Need free(*pTagParams), free(*pTagData)...

*/
inline int gethtmltagdata(char* str, char* tag, char** pTagParams, char** pTagData)
{
	char* ptr = NULL;
	char* ptr2 = NULL;
	int count = 0;
	char* tagbegin = NULL;
	char* tagend = NULL;

	tagbegin = (char*)calloc(strlen(tag)+2, 1);
	if (tagbegin == NULL)
	{
		return EXIT_OUT_OF_MEMORY;
	}

	tagbegin[0] = '<';
	strcat(tagbegin, tag);

	if (stristrbeginend(str, tagbegin, ">", &ptr, &count) == NULL)
	{
		free(tagbegin);
		return EXIT_INVALID_DATA;
	}

	*pTagParams = (char*)calloc(count+1, 1);
	if (*pTagParams == NULL)
	{
		free(tagbegin);
		return EXIT_OUT_OF_MEMORY;
	}
	
	memcpy(*pTagParams, ptr, count);

	tagend = (char*)calloc(strlen(tag)+4, 1);
	if (tagend == NULL)
	{
		free(*pTagParams);
		free(tagbegin);
		return EXIT_OUT_OF_MEMORY;
	}

	tagend[0] = '<';
	tagend[1] = '/';
	strcat(tagend, tag);
	strcat(tagend, ">");

	ptr2 = stristr(str, tagend);
	if (ptr2 == NULL)
	{
		free(tagend);
		free(*pTagParams);
		free(tagbegin);
		return EXIT_INVALID_DATA;
	}

	count = ptr2-ptr;
	if (count < 0)
	{
		free(tagend);
		free(*pTagParams);
		free(tagbegin);
		return EXIT_INVALID_DATA;
	}

	*pTagData = (char*)calloc(count+1, 1);
	if (*pTagData == NULL)
	{
		free(tagend);
		free(*pTagParams);
		free(tagbegin);
		return EXIT_OUT_OF_MEMORY;
	}
	
	memcpy(*pTagData, ptr2, count);

	free(tagend);
	free(tagbegin);

	return EXIT_SUCCESS;
}

/*

Need free(*pTitle), free(*pBody)...?

*/
inline int recvsimplehtml(SOCKET sock, char** pTitle, char** pBody, int maxrecvbuflen, int* pBytesReceived)
{
	int status = 0;
	char* szstatus = NULL;
	char* contenttype = NULL;
	int contentlength = 0;
	char* content = NULL;
	int ret = 0;
	char* titleparams = NULL;
	char* bodyparams = NULL;

	*pTitle = NULL;
	*pBody = NULL;

	ret = recvsimplehttpresp(sock, &status, &szstatus, &contenttype, &contentlength, &content, maxrecvbuflen, pBytesReceived);
	if (ret != EXIT_SUCCESS)
	{
		free(szstatus);
		free(contenttype);
		free(content);
		return ret;
	}

	if (strncmp(contenttype, "text/html", strlen("text/html")) != 0)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehtml error (%s) : %s"
			"(sock=%d, title=%s, body=%s, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_INVALID_DATA],
			(int)sock, *pTitle, *pBody, maxrecvbuflen, *pBytesReceived));
		free(szstatus);
		free(contenttype);
		free(content);
		return EXIT_INVALID_DATA;
	}

	if (gethtmltagdata(content, "title", &titleparams, pTitle) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehtml error (%s) : %s"
			"(sock=%d, title=%s, body=%s, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_FAILURE],
			(int)sock, *pTitle, *pBody, maxrecvbuflen, *pBytesReceived));
		free(szstatus);
		free(contenttype);
		free(content);
		return EXIT_FAILURE;
	}

	if (gethtmltagdata(content, "body", &bodyparams, pBody) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvsimplehtml error (%s) : %s"
			"(sock=%d, title=%s, body=%s, maxrecvbuflen=%d, *pBytesReceived=%d)\n",
			strtime_m(),
			szOSUtilsErrMsgs[EXIT_FAILURE],
			(int)sock, *pTitle, *pBody, maxrecvbuflen, *pBytesReceived));
		free(titleparams);
		free(szstatus);
		free(contenttype);
		free(content);
		return EXIT_FAILURE;
	}

	free(bodyparams);
	free(titleparams);

	free(szstatus);
	free(contenttype);
	free(content);
	
	return EXIT_SUCCESS;
}

#endif // !HTTPUTILS_H
