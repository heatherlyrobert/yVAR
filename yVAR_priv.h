/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YVAR_priv_hguard
#define YVAR_priv_hguard loaded



/*===[[ ONE_LINERS ]]=========================================================*/
/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "de (data defenses)"
#define     P_SUBJECT   "variable testing services"
#define     P_PURPOSE   "provide simple, consistent variable testing services"

#define     P_NAMESAKE  "keres-psychostasia (judgement)"
#define     P_HERITAGE  "female spirits of violent and cruel death, choosing righteous"
#define     P_IMAGERY   "fanged, taloned women in bloody garments, flying over the battlefield"
#define     P_REASON    "keres look into the soul and render final judgement"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "libyVAR.so"
#define     P_FULLPATH  "/usr/local/lib64/libyVAR.so"
#define     P_SUFFIX    "n/a"
#define     P_CONTENT   "n/a"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2008-07"

#define     P_VERMAJOR  "1.--, production improvements"
#define     P_VERMINOR  "1.1-, unit testing build out"
#define     P_VERNUM    "1.1a"
#define     P_VERTXT    "yVAR_string equal, yVAR_round unit testing and improvement"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"


#define     P_SUMMARY   \
   "yVAR is a set of shared functions for variable existance, typing, and value¦" \
   "testing services for use by the calling program, making a tedious and¦" \
   "neglected task into a systematic, shared, easy to maintain, and safer one.¦"



/*===[[ START HDOC ]]=========================================================*/
/*===[[ SUMMARY ]]=================================================#

 *   yVAR is a set of shared functions for variable existance, typing, and value
 *   testing services for use by the calling program.  it is designed to take
 *   a repetative, tedious, haphazard, neglected, and cracker vulnerable task 
 *   and make it systematic, shared, easy to maintain, and safer.
 */

/*===[[ PURPOSE ]]=================================================#
 *
 *   CRITICAL : this library will simplify the plugging of a top cracker
 *   backdoor -- unchecked input variables.  unchecked input variables can be
 *   used to inject code, cause crashes, overrun buffers, etc.
 * 
 *   yVAR focuses on improving the defensive capabilities of programs...
 *      - test variable contents for type (strg, intg, real, etc)
 *      - test variable contents for format (range, size, length, regex, etc)
 *      - verify variable existance/definition
 *   this can not replace a program's own defensiveness, just supplement it
 * 
 *   many existing libraries and utilities have been built by better programmers
 *   that are likely superior in speed, size, capability, and reliability; BUT,
 *   i would not have learned nearly as much using them, so follow the adage...
 * 
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 * 
 */
/*===[[ DECISION -- STANDARD TESTING OR NOT ]]=====================#

 *   SITUATION (s)
 *      as a programmer, i develop a great deal of custom code that executes
 *      either continuously, frequently, or at least at critical times.  this
 *      code is both for unique purposes as well as to replace existing tools to
 *      enhance and validate my skills.  bottom line, big code base, bigger
 *      plans, and one programmer to keep it all moving.
 *
 *   COMPLICATION (c)
 *      most of these programs have some sensitivity to malformed data and
 *      inputs.  because some of the data type checks can be complicated or
 *      numerous, i can sometimes assume, procrastinate, or partially address
 *      the problems.  huge issue in the long run.  unacceptable.  examples...
 *      -- numerical rounding before comparison (close enough)
 *      -- numerical acceptable ranges (close enough especially on doubles)
 *      -- intelligent strings such as urls, zipcodes, file names, etc
 *      -- check numbers embedded in larger strings
 *      -- expanded comparisons to support unit testing
 *      -- and many i haven't dealt with or heard of yet ;)
 *
 *   QUESTION (q)
 *      is there a simply way to make variable testing standard and reusable?
 *
 *   ANSWER (a)
 *      create a shared library of the less common and more complex variable
 *      testing methods so that the calling programs can remain more simple.
 * 
 *   BENEFITS (b)
 *      -- provides and encourages defensive coding practices
 *      -- causes variable defenses to be built "with" the code rather than appended
 *      -- makes formal testing (and educating testers) much more productive
 *      -- re-enforces a disciplined development culture
 *      -- allows program defenses to be built quickly
 *      -- all tests only need to be tested and debugged once
 *      -- ensures that the security is not slackened when the rush hits
 *      -- means one place to add best practices
 * 
 *   DISADVANTAGES (d)
 *      -- can distract when nothing is wrong
 *      -- is one more thing that can go wrong
 *      -- has to be built ahead of time
 *      -- since its shared, changes can effect all programs
 *      -- drive a monovision or a single method of thinking
 *      -- adds a speed penalty by having extra tests
 *
 *   OBJECTIVES (o)
 *      a) allow programs to use variable defenses without significant effort
 *      b) maximize reuse by using clear standards
 *      c) simple so that it does not require huge learning curve
 *      d) minimal so it can be inserted into templates directly
 *      e) rapid and easy to add new tests
 *      f) i learn a great deal
 * 
 *   ALTERNATIVES (a)
 *      -- ---desc-----------------------  a b c d e f      ---summary----------
 *      1) do nothing                      - - - - - -      retarded
 *      2) custom code in each program     - - - - - -      also retarded
 *      3) use a standard library          y y y y - -      would handle it
 *      4) custom library                  y y y y y y      of course
 * 
 *   JUDGEMENT (j)
 *      only a rookie, cocky sob, hacker or idiot simply 'trusts' program and
 *      function input.  build a small, shared library that can be reused
 *      fully and ported easily across languages
 * 
 *      this is not a strategic element, or even exciting, so why code it
 *      more than once or take the chance on leaving things out of
 *      later versions
 * 
 */
/*===((END DOC))==============================================================*/




#include    <ySTR_solo.h>
#include    <yCOLOR_solo.h>




#define    _GNU_SOURCE          /* to allow asprintf()                        */
#include <stdio.h>        /* printf(), snprintf()                             */
#include <stdlib.h>
#include <string.h>
#include <regex.h>        /* regcomp(), regexec(), regfree()                  */


#include    <yLOG.h>                    /* heatherly program logger            */
#include    <yURG.h>                    /* heatherly debugging filter          */
#include    "yVAR.h"


#define     LEN_LABEL        20
#define     LEN_DESC         50
#define     LEN_RECD       2000


extern char        s_test      [LEN_LABEL];
extern char        s_exp       [LEN_RECD];
extern char        u_exp       [LEN_RECD];
extern char        s_act       [LEN_RECD];
extern char        u_act       [LEN_RECD];
extern char        s_mod       [LEN_RECD];
extern char        s_fancy     [LEN_RECD];
extern int         s_len;


typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char        debug;
   int         logger;
};
extern  tLOCAL myVAR;
#define     DEBUG_YVAR     if (myVAR.debug == 'y')

extern char        unit_answer [LEN_RECD];


char        yVAR_testquiet     (void);
char        yVAR_testloud      (void);
char*       yVAR_getter        (char *a_question, int a_num);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yvar_string_prep        (cchar *a_test, cchar *a_expect, cchar *a_actual);
char*       yvar_string__unit       (char *a_question);



#endif
