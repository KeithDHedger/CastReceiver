
//Mon 31 Jul 2006 12:30:55 BST 
//
//castreceiver
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#define VERSION "0.0.0"
#define UNKNOWNARG -100

struct option long_options[] =
	{
		{"long1",1,0,'l'},
		{"version",0,0,'v'},
		{"help",0,0,'?'},
		{0, 0, 0, 0}
	};

void printhelp(void)
{
printf("Usage: castreceiver [OPTION]\n"
	"A CLI application\n"
	" -l, --long1	Do somthing good\n"
	" -v, --version	output version information and exit\n"
	" -h, -?, --help	print this help\n\n"
	"Report bugs to kdhedger@yahoo.co.uk\n"
	);
}

int main(int argc, char **argv)
{
	int c;
	while (1)
		{
		int option_index = 0;
		c = getopt_long (argc, argv, "v?h:l:",long_options, &option_index);
		if (c == -1)
			break;

		switch (c)
			{
			case 'l':
				printf("Arg=%s\n",optarg);
				break;
		
			case 'v':
				printf("castreceiver %s\n",VERSION);
				return 0;
				break;

			case '?':
			case 'h':
				printhelp();
				return 0;
				break;

			default:
				fprintf(stderr,"?? Unknown argument ??\n");
				return UNKNOWNARG;
			break;
			}
		}
	
	if (optind < argc)
		{
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
		}
	
	printf("%s\n","Hello World");
	return 0;
}

