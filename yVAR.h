/*===[[ START HDOC ]]=========================================================*/
/*===[[ HEADER ]]==================================================#

 *   focus         : (PS) programming support
 *   niche         : (de) defense
 *   application   : yVAR
 *   purpose       : provide simple, consistent variable testing services
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : gnu/ansi-c  (right, just, best, standard, and everlasting)
 *   dependencies  : none
 *   size goal     : small (less than 1,000 slocL)
 *
 *   author        : the_heatherlys
 *   created       : 2008-07 (from bash versions of 2007-05)
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 *
 */
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


/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YVAR_HGUARD
#define YVAR_HGUARD loaded


/*===[[ VERSION ]]========================================*/
/* rapidly evolving version number to aid with visual change confirmation     */
#define YVAR_VER_NUM   "1.0e"
#define YVAR_VER_TXT   "unit testing complete (again) on int, str, round"


char      yVAR_expstr   [500];
char      yVAR_actstr   [500];
char      yVAR_modstr   [500];
typedef   const char  cchar;

/*===[[ FUNCTION PROTOTYPES ]]================================================*/

char*      /* ---- : return library versioning information -------------------*/
yVAR_version       (void);

char
yVAR_debug         (char a_flag);


int        /*----: standard regex pattern testing ----------------------------*/
yVAR_regx (        /*  PURPOSE = STANDARD STRING REGEX PATTERN TESTING        */
      char     *a_format,        /*  requested format for testing             */
      char     *a_value)         /*  variable value to test                   */
;

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_string (      /*  PURPOSE = STANDARD STRING TESTING (for yUNIT+)         */
      char     *a_test,          /*  name of the test                         */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
;

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_ustring (     /*  PURPOSE = complex string testing for yUNIT             */
      char     *a_test,          /*  name of the test                         */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
;

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_round   (     /*  PURPOSE = complex string testing for yUNIT             */
      cchar    *a_test,          /*  name of the test                         */
      cchar    *a_expect,        /*  expected result                          */
      cchar    *a_actual)        /*  actual result                            */
;

char*      /*----: return the modified expected string -----------------------*/
yVAR_modded        (void);

char*      /*----: return the modified expected string -----------------------*/
yVAR_actual        (void);

char*      /*----: return the modified expected string -----------------------*/
yVAR_expect        (void);

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_integer(      /*  PURPOSE = STANDARD INTEGER TESTING (for yUNIT+)        */
      char     *a_test,          /*  name of the test                         */
      long      a_expect,        /*  expected result                          */
      long      a_actual)        /*  actual result                            */
;

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_pointer(      /*  PURPOSE = STANDARD POINTER TESTING (for yUNIT+)        */
      char     *a_test,          /*  name of the test                         */
      void     *a_expect,        /*  expected result                          */
      void     *a_actual)        /*  actual result                            */
;

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_real (        /*  PURPOSE = STANDARD REAL NUM TESTING (for yUNIT+)       */
      char     *a_test,          /*  name of the test                         */
      double    a_expect,        /*  expected result                          */
      double    a_actual)        /*  actual result                            */
;

void
yVAR_hex (
      int       a_range,         /*  how far off can it be                    */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
;

#endif
/*===[[ END ]]================================================================*/
