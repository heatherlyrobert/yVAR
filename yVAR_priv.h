/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YVAR_priv_hguard
#define YVAR_priv_hguard loaded



#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "de (data defenses)"
#define     P_PURPOSE   "provide simple, consistent variable testing services"

#define     P_NAMESAKE  "keres-psychostasia (judgement)"
#define     P_HERITAGE  "female spirits of violent and cruel death, choosing righteous"
#define     P_IMAGERY   "fanged, taloned women in bloody garments, flying over the battlefield"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2008-07"
#define     P_DEPENDS   "none"

#define     P_VERNUM    "1.0n"
#define     P_VERTXT    "upgraded yVAR_integer to long long to handle gregg testing"





#define    _GNU_SOURCE          /* to allow asprintf()                        */
#include <stdio.h>        /* printf(), snprintf()                             */
#include <stdlib.h>
#include <string.h>
#include <regex.h>        /* regcomp(), regexec(), regfree()                  */


#include    <yURG.h>                    /* heatherly debugging filter          */
#include    <yLOG.h>                    /* heatherly program logger            */
#include    "yVAR.h"




typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char        debug;
   int         logger;
};
extern  tLOCAL its;
#define     DEBUG_YVAR     if (its.debug == 'y')

#define     LEN_RECD       2000


char        yVAR_testquiet     (void);
char        yVAR_testloud      (void);
char*       yVAR_getter        (char *a_question, int a_num);





#endif
