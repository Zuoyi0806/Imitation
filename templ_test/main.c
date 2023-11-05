#include <stdio.h>

#include "args.h"

int main(int argc, char **argv)
{
	i32 i = 0, ret = -1;

	parse_args(argc, argv);

	for (i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			ret = invoke_action(argv[i]);
			if (ret != 0) {
				break;
			}
		}
	}

	destroy_args();
	return 0;
}
