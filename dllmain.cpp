// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

struct eZ80pages{
void** pageptr[5];
UINT32 pagesize[5];
UINT32 (*eZ80mac[5])(int, int, int);
};

eZ80pages page;

#ifdef __cplusplus
extern "C" {
#endif
    __declspec(dllexport) eZ80pages* get_eZ80pages() { return &page; }
    __declspec(dllexport) UINT32 eZ80memaccess(int prm_0, int prm_1, int prm_2) {
        if ((prm_2 > 1) || (page.pageptr[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0][prm_0 / page.pagesize[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0]] == 0)) { return page.eZ80mac[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0](prm_0,prm_1,prm_2); }
        else {
            switch (prm_2 & 1) {
            case 0:
                ((char*)page.pageptr[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0][prm_0 / page.pagesize[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0]])[prm_0 % page.pagesize[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0]] = (UINT8)(prm_1&0xFF);
                return 0;
                break;
            case 1:
                return (((char*)page.pageptr[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0][prm_0 / page.pagesize[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0]])[prm_0 % page.pagesize[(prm_2 & 0x80000000) ? (1 + ((prm_2 >> 24) & 0x3)) : 0]]) & 0xFF;
                break;
            }
        }
    }
#ifdef __cplusplus
}
#endif