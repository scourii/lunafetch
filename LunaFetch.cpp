#include <stdlib.h>
#include <time.h>
#include <sys/utsname.h>
#include <iostream>
#include <pwd.h>
#include <vector>
#include <cstdlib>
#include <pwd.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fstream>
#include <chrono>


struct dist {
	char *col1, *col2, *col3, *col4, *col5, *col6, *col7, *col8, *col9, *col10, *col11;
	char *getPkgCount;
};

struct utsname uname_info;
char *username, *shellname, *pkgcount;
long uptimeHour, uptimeMin;
struct dist info = { 
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

static std::string *name()
{
    username = cuserid(username);
    std::cout << "User:     " << username << std::endl;
    return 0;
}

static std::string *shell()
{
    char* shellname = getpwuid(geteuid())->pw_shell;
    char* slash = strrchr(shellname, '/');
	if (slash) {
		shellname = slash + 1;
	}
    std::cout << "Shell:    " << shellname << std::endl;
    return 0;
}

static std::string *get_os() {
    struct utsname os;
    if(uname(&os)) exit(-1);
    std::cout << "OS:       " << os.sysname << " " << os.machine << std::endl;
    return 0;
}
static std::string *kernel()
{
    struct utsname kernel;
    if(uname(&kernel)) exit(-1);
    std::cout << "Kernel:   " << kernel.release << std::endl;
    return 0;
}

int main() {
    std::cout << info.col1 << std::endl;
    std::cout << info.col2 << std::endl;
    std::cout << info.col3 << std::endl;
    std::cout << info.col4 << std::endl;
    std::cout << info.col5 << std::endl;
    std::cout << info.col6 << std::endl;
    std::cout << info.col7 << std::endl;
    std::cout << info.col8 << std::endl;
    std::cout << info.col9 << std::endl;
    std::cout << info.col10 << std::endl;
    std::cout << info.col11 << std::endl;
    name();
    get_os();
    shell();
    uptime();
    kernel();
    return 0;
}
