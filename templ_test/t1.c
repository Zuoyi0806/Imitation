#include "args.h"
#include <stdio.h>

static int
do_a(int argc, const char **argv)
{
	printf("do a !\n");
	return 0;
}

static int
do_b(int argc, const char **argv)
{
	printf("do b !\n");
	return 0;
}

ADD_ACTION("-a", "[ balabala a]", do_a, "helpmsg balabala a");

ADD_ACTION("-b", "[ balabala b]", do_b, "helpmsg balabala b");
