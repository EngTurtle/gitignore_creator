#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

static char *dont_ignore_list[] = {".", "..", ".gitignore"};

static int
one (const struct dirent *unused)
{
    return 1;
}

bool
string_in_argv(char *string, char *argv[], int argc)
{
    for(argc--; argc>0; argc--)
    {
        if(! strcmp (string, argv[argc]))
            return true;
    }
    return false;
}

bool
dont_ignore(char *filename)
{
    int i;

    for (i = 0; i < 3 ; ++i)
    {
        if(!strcmp(filename, dont_ignore_list[i]))
            return true;
    }
    return false;
}

int
main (int argc, char *argv[])
{
    struct dirent **eps;
    int n;
    FILE *ignore = fopen(".gitignore", "w");

    n = scandir ("./", &eps, one, alphasort);
    if (n >= 0)
    {
        int cnt;
        for (cnt = 0; cnt < n; ++cnt)
        {
            if(!dont_ignore(eps[cnt]->d_name))
            {
                if(!string_in_argv(eps[cnt]->d_name, argv, argc))
                {
                    fprintf(ignore, eps[cnt]->d_name);
                    if(eps[cnt]->d_type == DT_DIR)
                        fprintf (ignore, "/*");
                    fprintf(ignore, "\n");
                }
            }
        }

    }
    return 0;
}
