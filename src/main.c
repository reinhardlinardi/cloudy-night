/*
 * Brightsouls
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fallback/main.h>

#define APP_NAME     "Brightsouls"
#define APP_VERSION  "v0.1"

int
main (int argc,
      char** argv)
{
	int retval = 1;

	bool cn = true;
	char op;
    /*
	App app;
	App_Create (&app);
    */
	while (cn && ((op = getopt (argc, argv, "v")) != -1))
	{
		switch (op)
		{
		case 'v':
			fprintf (stderr, APP_NAME " " APP_VERSION "\n");
			retval = 0;
			cn = false;
			break;

		case '?':
			fprintf (stderr, "Usage: %s [-v]\n", argv[0]);
			cn = false;
			break;

		default:
			abort ();
		}
	}

	retval = Fallback_Main ();
	/*if (cn)
	{
		if (App_Prepare (&app))
			App_Run (&app);
		else
			retval = 1;
	}*/

	return retval;
}
