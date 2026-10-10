// SPDX-License-Identifier: MIT
//
// passt calls __builtin_cpu_supports("avx2") to switch to passt.avx2, which
// references __cpu_model from compiler-rt. zig's compiler-rt does not provide
// it, so define the minimum needed for the AVX2 check here.

#if defined(__x86_64__)

#include <cpuid.h>

#define FEATURE_AVX2 10

struct __processor_model {
	unsigned int __cpu_vendor;
	unsigned int __cpu_type;
	unsigned int __cpu_subtype;
	unsigned int __cpu_features[1];
} __cpu_model;

__attribute__((constructor(101)))
static void cpu_model_init(void)
{
	unsigned int a, b, c, d, lo, hi;

	if (!__get_cpuid(1, &a, &b, &c, &d))
		return;

	// OSXSAVE and AVX
	if (!(c & (1U << 27)) || !(c & (1U << 28)))
		return;

	// XMM and YMM state enabled by OS
	__asm__("xgetbv" : "=a"(lo), "=d"(hi) : "c"(0));
	if ((lo & 0x6) != 0x6)
		return;

	if (__get_cpuid_count(7, 0, &a, &b, &c, &d) && (b & (1U << 5)))
		__cpu_model.__cpu_features[0] |= 1U << FEATURE_AVX2;
}

#endif
