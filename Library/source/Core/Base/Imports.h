/*
           #################################
          ###                          #####
        ###     ######################### ##
      ###     ###                   ##### ##
    ####     ########################  ## ##
  ####                          ###    ## ##
####                          ####     ## ##
################################ #     ## ##
##                     #     ##  #  ## ## ##
##                     #     ##  #  ## ## ##
##                     #     ##  #  ##### ##
##                     #     ##  # ###### ##
##                     #     ##  # #  ### ##
##                     #     ##  ###  ### ##
##                     #     ##  ##    ## ##
##########             #     ##  ##    #  ##
##       #             #     ##  ##      ###
##       #             #     ##  #      ### 
##       #             #     ##       ###   
##       ###############     ##     ####    
##                           ##   ####      
##                           ## ####        
##                           #####          
################################            

############# [J][C]ube[W]are ##############
#   Be responsible. Code for the future.   #
#         (c) 2025-2026, JCubeWare         #
############################################
*/

#pragma once

#ifndef JCUBECODE_CORE_BASE_IMPORTS_H
#define JCUBECODE_CORE_BASE_IMPORTS_H

/*##====[ DESCRIPTION ]====##*/
/*
 * This file handles all the common imports so you don't have to struggle your
 * ass off in "which file to include now"?
 */

/*##====[ IMPORTS ]====##*/

#include "Target.h"

/*##====[ STANDARD LIBRARIES ]====##*/

#ifdef LIB_C
	#include <assert.h>
	#include <complex.h>
	#include <ctype.h>
	#include <errno.h>
	#include <float.h>
	#include <limits.h>
	#include <locale.h>
	#include <math.h>
	#include <setjmp.h>
	#include <signal.h>
	#include <stdarg.h>
	#include <stddef.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	#include <wchar.h>
	#include <wctype.h>

	#ifdef __STDC_VERSION__
		#include <stdbool.h>
		#include <stdint.h>
		#include <inttypes.h>
		#include <tgmath.h>
		#include <fenv.h>
		#include <iso646.h>
	#endif

#endif

/*##====[ POSIX INCLUDES ]====##*/
/*
 * Right now, not smart enough to know which includes exist.
 * If you have a problem with any include, just comment it out. :D
 */

#ifdef API_POSIX
	#include <aio.h>
	#include <arpa/inet.h>
	#include <assert.h>
	#include <complex.h>
	#include <cpio.h>
	#include <ctype.h>
	#include <dirent.h>
	#include <dlfcn.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <fenv.h>
	#include <float.h>
	#include <fmtmsg.h>
	#include <fnmatch.h>
	#include <ftw.h>
	#include <glob.h>
	#include <grp.h>
	#include <iconv.h>
	#include <inttypes.h>
	#include <iso646.h>
	#include <langinfo.h>
	#include <libgen.h>
	#include <limits.h>
	#include <locale.h>
	#include <math.h>
	#include <monetary.h>
	#include <mqueue.h>
	/* #include <ndbm.h> */
	#include <net/if.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <nl_types.h>
	#include <poll.h>
	#include <pthread.h>
	#include <pwd.h>
	#include <regex.h>
	#include <sched.h>
	#include <search.h>
	#include <semaphore.h>
	#include <setjmp.h>
	#include <signal.h>
	#include <spawn.h>
	#include <stdarg.h>
	#include <stdbool.h>
	#include <stddef.h>
	#include <stdint.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <strings.h>
	/* #include <stropts.h> */
	#include <sys/ipc.h>
	#include <sys/mman.h>
	#include <sys/msg.h>
	#include <sys/resource.h>
	#include <sys/select.h>
	#include <sys/sem.h>
	#include <sys/shm.h>
	#include <sys/socket.h>
	#include <sys/stat.h>
	#include <sys/statvfs.h>
	#include <sys/time.h>
	#include <sys/times.h>
	#include <sys/types.h>
	#include <sys/uio.h>
	#include <sys/un.h>
	#include <sys/utsname.h>
	#include <sys/wait.h>
	#include <syslog.h>
	#include <tar.h>
	#include <termios.h>
	#include <tgmath.h>
	#include <time.h>
	/* #include <trace.h> */
	#include <ulimit.h>
	#include <unistd.h>
	#include <utime.h>
	#include <utmpx.h>
	#include <wchar.h>
	#include <wctype.h>
	#include <wordexp.h>
#elif defined(API_WINDOWS)
	/*#include <winsock.h>*/
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <direct.h>
	#include <uxtheme.h>

	#if WINDOWS_OLD
		#include <tmschema.h> 
	#else
		#include <vssym32.h>
	#endif

	#include <commctrl.h>
	#include <windows.h>
#endif

#endif
