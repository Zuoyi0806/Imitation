#ifndef _TEST_ARGS_H_
#define _TEST_ARGS_H_

#include "basetype.h"

typedef int (* FUNCP)();

/* func declare */
void register_action(const char *module, const char *name,
		const char *args, FUNCP act, const char *helpmsg);

i32 parse_args(int argc, const char **argv);

int  invoke_action(char *argc);

void destroy_args(void);

/* compile __auto_register__ used to registe some func */

#define __COMBINE_TOKENS(t1, t2) t1##t2
#define ___COMBINE_TOKENS(t1, t2) __COMBINE_TOKENS(t1, t2)
#define UNIQUE_TOKEN()  ___COMBINE_TOKENS(__auto_register__, __LINE__)

#define ADD_ACTION(name, args, func, helpmsg) \
		__attribute__((constructor)) static void UNIQUE_TOKEN()() \
	{ \
		register_action("normal", name, args, (FUNCP)func, helpmsg);\
	}


#define ADD_CUSTOM_ACTION(module, name, args, func, helpmsg) \
		__attribute__((constructor)) static void UNIQUE_TOKEN()() \
	{ \
		register_action(module, name, args, (FUNCP)func, helpmsg);\
	}



#endif