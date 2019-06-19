# ntoskrnl_HT_FIX
fixes hyperthreading for windows 2003 when running on newer cpus

When windows 2003 is installed on newer multicore cpus such as the i7-4790 the kernel does not correctly detect the core topology. In the case of i7-4790 the cpu is detected as having a single core with 8 hyperthreads. Threads are not scheduled efficiently when the core topology is wrong. In the example case the kernel makes no effort to keep a thread on the same core, the thread jumps randomly between cores on every context switch, this murders the cache resulting in somewhat lower performance.

The kernel detects the core topology by way of the instruction cpuid. On older cpus the number of logical cores per physical core is returned in Bits 23-16, of Ebx, when Eax=1. For some reason, intel, at some point changed the meaning of these bits, they no longer reflect the number of logical cores per pysical and instead return some value of unknown meaning which in my case the kernel interprets as as 16 logical cores per pysical cpu.

This problem is corrected by patching the cpuid function in ntoskrnl.exe. The new function replaces Bits 23-16, of Ebx, when Eax=1, With the expected value for an older hyperthreaded cpu. With this patch threads are now scheduled correctly.






