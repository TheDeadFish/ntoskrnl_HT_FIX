
extern "C"
void __stdcall CPUID(int a1, int* a2, int* a3, int* a4, int* a5)
{
	int EAX, EBX, ECX, EDX;
	asm("cpuid" : "=a"(EAX), "=b"(EBX),
		"=c"(ECX), "=d"(EDX) : "a"(a1));
	if(a1 == 1) {
		EBX = (EBX & 0xFF00FFFF) | 0x00020000; }
	*a2 = EAX; *a3 = EBX;
	*a4 = ECX; *a5 = EDX;
}
