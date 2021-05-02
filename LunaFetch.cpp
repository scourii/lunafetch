#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <iostream>
#include <pwd.h>
#include <cmath>
#include <unistd.h>
#include <string.h>
#include <fstream>

// Terminal Colors
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

struct utsname uname_info;
char *username, *shellname;
long uptimeHour, uptimeMin;

void printout(std::string array[], int size)
{
    static int i;
    if (i == size)
    {
        i = 0;
        std::cout << std::endl;
        return;
    }
    std::cout << array[i] << std::endl;
    i++;
    printout(array, size);
}
static std::string *name()
{
    username = cuserid(username);
    std::cout.width(50); std::cout << std::left << CYAN << "User:     " <<  WHITE << username << std::endl;
    return 0;
}

static std::string *shell()
{
    shellname = getpwuid(geteuid())->pw_shell;
    char* slash = strrchr(shellname, '/');
	if (slash) {
		shellname = slash + 1;
	}
    std::cout.width(50); std::cout << std::left << CYAN << "Shell:    " << WHITE << shellname << std::endl;
    return 0;
}
static std::string *editor()
{
    const char* editor = std::getenv("EDITOR");
    if (editor && *editor) editor = basename(editor);
        std::cout.width(50); std::cout << std::left << CYAN << "Editor:   " << WHITE << editor << std::endl;
    return 0;
}

static std::string *get_os() 
{
    struct utsname uname_info;
    if(uname(&uname_info)) exit(-1);
     std::cout.width(50); std::cout << std::left << CYAN << "OS:       " << WHITE << uname_info.sysname << " " << uname_info.machine << std::endl;
    return 0;
}
static std::string *kernel()
{
    struct utsname uname_info;
    if(uname(&uname_info)) exit(-1);
     std::cout.width(50); std::cout << std::left << CYAN << "Kernel:   " << WHITE << uname_info.release << std::endl;
    return 0;
}
size_t ram()
{
    char* ram;

    FILE* fp = fopen("/proc/meminfo", "r");

    char tmp[128];
    char* token, *ptr;
    size_t total_mem = 0, free_mem = 0, buffers = 0, cached = 0;

    while (fgets(tmp, sizeof(tmp) - 1, fp) != NULL && !(total_mem && free_mem)) {
        token = strtok(tmp, " ");

        if (!strcmp(token, "MemTotal:")){
            token = strtok(NULL, " ");
            total_mem = strtol(token, &ptr, 10);
        } else if (!strcmp(token, "MemAvailable:")){
            token = strtok(NULL, " ");
            free_mem = strtol(token, &ptr, 10);
        } 
    }

    asprintf(&ram, "%zi/%zi mib",
            (total_mem - free_mem - buffers) / 1024, total_mem / 1024);
    
    fclose(fp);

     std::cout.width(50); std::cout << std::left << CYAN << "Ram:      " << WHITE << ram << std::endl;

    return 0;
}

static void uptime()
{
    FILE* file = fopen("/proc/uptime", "r");
    if (file == NULL)
        return;
    double uptime;
    fscanf(file, "%lf", &uptime);
    fclose(file);
    std::cout.width(50); std::cout << std::left << CYAN << "\x1b[" << "Uptime:   " <<  WHITE << round(uptime / 60) << " mins" << std::endl;
}

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
"                    .\t",
};

int main() {
    int size = sizeof(info) / sizeof(info[0]);
    printout(info, size);
    name();
    get_os();
    kernel();
    ram();
    editor();
    shell();
    uptime();
    return 0;
}
