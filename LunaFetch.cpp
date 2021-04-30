#include <stdlib.h>
#include <time.h>
#include <sys/utsname.h>
#include <iostream>
#include <pwd.h>
#include <vector>
#include <cstdlib>
#include <pwd.h>
#include <cmath>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fstream>
#include <chrono>
#include <utmp.h>

struct dist {
	char *col1, *col2, *col3, *col4, *col5, *col6, *col7, *col8, *col9, *col10, *col11;
};

struct utsname uname_info;
char *username, *shellname;
long uptimeHour, uptimeMin;
std::string info[] = { 
"            ~+",
"",
"                 *       +",
"           '                  |",
"       ()    .-.,='``'=.    - o -",
"             '=/_       \\     |",
"          *   |  '=._    |",
"               \\     `=./`,        '",
"            .   '=.__.=' `='      *",
"   +                         +",
"        O      *        '       .",
"                    .",
};

void printout(std::string array[], int size)
{
    static int i;
    if (i == size)
    {
        i = 0;
        std::cout << std::endl;
        return;
    }
    std::cout << array[i] << "\n";
    i++;
    printout(array, size);
}
static std::string *name()
{
    username = cuserid(username);
    std::cout << "User:     " << username << std::endl;
    return 0;
}

static std::string *shell()
{
    shellname = getpwuid(geteuid())->pw_shell;
    char* slash = strrchr(shellname, '/');
	if (slash) {
		shellname = slash + 1;
	}
    std::cout << "Shell:    " << shellname << std::endl;
    return 0;
}

static std::string *get_os() 
{
    struct utsname uname_info;
    if(uname(&uname_info)) exit(-1);
    std::cout << "OS:       " << uname_info.sysname << " " << uname_info.machine << std::endl;
    return 0;
}
static std::string *kernel()
{
    struct utsname uname_info;
    if(uname(&uname_info)) exit(-1);
    std::cout << "Kernel:   " << uname_info.release << std::endl;
    return 0;
}
static void uptime()
{
    FILE *file = fopen("/proc/uptime", "r");
    if (!file)
        perror("Couldn't open /proc/uptime'");
    
    double uptime;
    fscanf(file, "%lf", &uptime);
    fclose(file);
    std::cout << "Uptime:   " << round(uptime / 60) << " mins" << std::endl;
}

int main() {
    int size = sizeof(info) / sizeof(info[0]);
    printout(info, size);
    name();
    get_os();
    kernel();
    shell();
    uptime();
    return 0;
}
