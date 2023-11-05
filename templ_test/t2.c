#include "args.h"
#include <stdio.h>


static int
do_c(int argc, const char **argv)
{
	printf("do a !\n");
	return 0;
}

ADD_ACTION("-c", "[ balabala c]", do_c, "helpmsg balabala c");


