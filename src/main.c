#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>

#include "dump.h"
#include "cpuid.h"

struct settings {
	// valid if not -1
	int64_t	eax;
	int64_t	ecx;
	bool	dump;
	bool	dump_all;
};

void parse_args(struct settings *s, int argc, char *argv[]);

int main(int argc, char *argv[])
{
	struct cpuid_regs regs;
	char cpustr[13];

	if (!has_cpuid()) {
		puts("CPUID not supported");
		return 1;
	}

	struct settings s;
	parse_args(&s, argc, argv);

	// dump everythin if --dump-all passed or if eax and ecx were unspecified
	if (s.dump_all || ((s.eax == -1) && (s.ecx == -1))) {
		puts("CPUID.EAX=0x0");
		puts("=============");
		c00(cpustr, sizeof(cpustr));

		puts("CPUID.EAX=0x1");
		puts("=============");
		c01(cpustr, g_feat_01_amd_ecx, g_feat_01_amd_edx);

		// Reserved on AMD
		c02();

		return 0;
	}

	// if not dumping everything and eax, ecx are uninitialized, set them to 0
	if (s.eax == -1)
		s.eax = 0;
	if (s.ecx == -1)
		s.ecx = 0;

	regs.eax = s.eax;
	regs.ecx = s.ecx;

	printf("CPUID(EAX=%08x,ECX=%08x)\n", regs.eax, regs.ecx);
	cpuid(&regs);
	printf("EAX=%08x, EBX=%08x, ECX=%08x, EDX=%08x\n",
		regs.eax, regs.ebx, regs.ecx, regs.edx);

	return 0;
}

void usage()
{
	puts("cpuid usage:");
	printf("\t--eax eax_value\n");
	printf("\t--ecx ecx_value\n");
	printf("\t-d interpret register values and display information\n");
	printf("\t\tWithout -d, the raw register values are displayed\n");
	printf("\t--dump-all display all information about cpu (not everything is supported)\n");
	printf("\t--help display this help\n");
	exit(0);
}

void parse_args(struct settings *s, int argc, char *argv[])
{
	const int eax_index = 0;
	const int ecx_index = 1;
	static struct option long_options[] = {
		{"eax", required_argument, 0, 0},
		{"ecx", required_argument, 0, 0},
		{"dump-all", no_argument, 0, 0},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};


	s->eax = s->ecx = -1;
	s->dump = false;
	while (true) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "dh", long_options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 0:
			if (optarg) {
				uint32_t val = strtoul(optarg, NULL, 0);
				switch (option_index) {
				case 0:
					s->eax = val;
					break;
				case 1:
					s->ecx = val;
					break;
				}
			} else {
				/* dump_info */
				if (option_index == 2)
					s->dump_all = true;
			}
			break;
		case 'd':
			s->dump = true;
			break;
		case 'h':
			usage();
			// does not return
			break;
		case '?':
			break;
		}
	}
}
