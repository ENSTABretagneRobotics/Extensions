#ifndef MISC_H
#define MISC_H

#include "OSMisc.h"
#include <vector>
#include <deque>

// Make template class instead of void*...
struct PROVIDER
{
	std::vector< std::deque<void*> > userslist;
	int maxdatasize;
};
typedef struct PROVIDER PROVIDER;

void InitProvider(PROVIDER p, int maxdatasize){
	p.userslist.clear();
	p.maxdatasize = maxdatasize;
}
void RegisterToProvider(PROVIDER p, std::deque<void*> user){
	p.userslist.push_back(user);
}
BOOL IsRegisteredToProvider(PROVIDER p, std::deque<void*> user){
	return (std::find(p.userslist.begin(), p.userslist.end(), user) != p.userslist.end());
}
int UnregisterToProvider(PROVIDER p, std::deque<void*> user){
	if (p.userslist.erase(std::find(p.userslist.begin(), p.userslist.end(), user)) != p.userslist.end())
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}
void UpdateProvider(PROVIDER p, void* data){
	for (unsigned int i = 0; i < p.userslist.size(); i++)
	{
		p.userslist[i].push_back(data);
		if (p.userslist[i].size() > p.maxdatasize) p.userslist[i].pop_front();
	}
}
// Useless...
int PopDataFromProvider(PROVIDER p, std::deque<void*> user, void** &pData)
{
	if (user.size() > 0)
	{
		*pData = user[0];
		user.pop_front();
		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}

/*
void testrtcm(){
	RTCMuserslist.push_back(RTCMusers[0]);



	for (unsigned int i = 0; i < RTCMuserslist.size(); i++)
	{
		unsigned char* data = (unsigned char*)calloc(MAX_NB_BYTES_RTCM_PART, sizeof(unsigned char));
		memcpy(data, rtcmdata, MAX_NB_BYTES_RTCM_PART);
		RTCMuserslist[i].push_back(data);
		if (RTCMuserslist[i].size() > MAX_NB_RTCM_PARTS) RTCMuserslist[i].pop_front();
	}


	unsigned char* data = RTCMusers[0][0];
	RTCMusers[0].pop_front();
	memcpy(rtcmdata, data, MAX_NB_BYTES_RTCM_PART);
	free(data);
}

void testrtcm2(){
	RTCMuserslist.push_back(RTCMusers[0]);



	unsigned char rtcmbyte = 00;
	for (unsigned int i = 0; i < RTCMuserslist.size(); i++)
	{
		RTCMuserslist[i].push_back(rtcmbyte);
		if (RTCMuserslist[i].size() > MAX_NB_BYTES_RTCM_PARTS) RTCMuserslist[i].pop_front();
	}


	unsigned char rtcmbyte = RTCMusers[0][0];
	RTCMusers[0].pop_front();
}
*/

#endif // !MISC_H
