#include <windows.h>

typedef struct _CPU_INFO {
    ULONG Eax;
    ULONG Ebx;
    ULONG Ecx;
    ULONG Edx;
} CPU_INFO, *PCPU_INFO;

extern "C"
VOID KiCpuId (ULONG Function,
	ULONG Index, PCPU_INFO CpuInfo
	)
{
	int EAX, EBX, ECX, EDX;
	asm("cpuid" : "=a"(EAX), "=b"(EBX), "=c"(ECX), 
		"=d"(EDX) : "a"(Function), "c"(Index));
	if(Function == 1) {
		EBX = (EBX & 0xFF00FFFF) | 0x00020000; }
	CpuInfo->Eax = EAX;	CpuInfo->Ebx = EBX;
	CpuInfo->Ecx = ECX; CpuInfo->Edx = EDX;
}
