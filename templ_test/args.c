#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "args.h"

#define STR_EQUAL(s1, s2) (strcmp(s1, s2) == 0)

struct action {
	const char *module;  /* action belong to   */
	const char *name;    /* action's name      */
	const char *args;    /* args uses in FUNCP when we invoke this action*/
	const char *helpmsg; /* some help messages  */
	FUNCP action;
};

struct cmditem {
	i32 argc;
	char **argv;
	struct action *action;
};

struct cmdline {
	struct cmditem *cmd;
	i32 cmdline_size;
};

static struct cmdline g_cmdline = {0};

static i32
unknown_action_instance(i32 argc, const char **argv)
{
	printf("unknown argument, skipped :%s \n", argv[0]);

	return 0;
}

struct action unknown_action  = {
	.module  = "unknown",
	.name    = "unknown",
	.args    = "",
	.helpmsg = "NONE",
	.action  = unknown_action_instance,
};

#define MAX_ACTION_N 256
static struct action support_actions[MAX_ACTION_N]={0};
static i32 g_nr_action = 0;

void safefree(void *ptr)
{
	if (ptr) {
		free(ptr);
	}
}

i32 parse_args(i32 argc, const char **argv)
{
	i32 nr_cmdline = 0;
	unknown_action.action(argc);
	for (i32 i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-')
			nr_cmdline++;
	}
	g_cmdline.cmdline_size = nr_cmdline;
	g_cmdline.cmd = (struct cmditem *)malloc(sizeof(struct cmditem) * nr_cmdline);

	for (i32 i = 0, k = 0; i < argc; i++)
	{
		/*when meet a '-', creat an instance of cmditem*/
		if (argv[i][0] == '-') 
		{
			struct cmditem *cmd;
		    i32 cmdargc = 1;
			for (i32 j = i + 1; j < argc && argv[j][0] != '-'; j++) {
				cmdargc++;
			}
			cmd = &g_cmdline.cmd[k];
			cmd->argc = cmdargc;
			cmd->argv = (char **)malloc(cmd->argc * sizeof(char *));
			/* copy argv i32o cmd->argv */
			for (i32 j = 0; j < cmdargc; j++)
			{
				cmd->argv[j] = strdup(argv[i + j]);
				if (!cmd->argv[j]) 
				{
					fprintf(stderr, "failed to dup argv,cmd posion %d\n",(i+j));
					return 1;
				}
			}
			/* set action */
			cmd->action = &unknown_action;
			for (i32 j = 0; j < g_nr_action; j++) {
				if (STR_EQUAL(cmd->argv[0], support_actions[j].name)) {
					cmd->action = &support_actions[j];
					break;
				}
			}
			k++;
			/*reach the next '-'*/
			i += cmd->argc - 1;
		}
	}
	printf("parsing args SUCCESS \n");
	return 0;
}

void destroy_args(void)
{
	/* free mem for store argc */
	for ( i32 i = 0; i < g_cmdline.cmdline_size; i++)
	{
		struct cmditem *cmd = &g_cmdline.cmd[i];
		for (i32 j = 0; j < cmd->argc; j++) 
			safefree(cmd->argv[j]);
		safefree(cmd->argv);
	}
	/* free mem for sotre cmd item */
	safefree(g_cmdline.cmd);

	g_cmdline.cmd          = NULL;
	g_cmdline.cmdline_size = 0;
}

i32 invoke_action(char *argc)
{
	for (i32 i = 0; i < g_cmdline.cmdline_size; i++)
	{
		struct cmditem *cmd = &g_cmdline.cmd[i];
		if (STR_EQUAL(argc, cmd->argv[0]))
		{
			if (cmd->action && cmd->action->action) 
				return cmd->action->action(cmd->argc, cmd->argv);
		}
	}
	return 0;

}
void register_action(const char *module, const char *name,
		const char *args, FUNCP act, const char *helpmsg)
{
	if (g_nr_action >= MAX_ACTION_N) 
	{
		fprintf(stderr, "maximum actions reached %d, reset the limit\n", g_nr_action);
		return ;
	}

	support_actions[g_nr_action].module  = module;
	support_actions[g_nr_action].name    = name;
	support_actions[g_nr_action].args    = args;
	support_actions[g_nr_action].helpmsg = helpmsg;
	support_actions[g_nr_action].action = act;
	g_nr_action++;
}
