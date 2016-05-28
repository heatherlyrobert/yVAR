/*===[[ START ]]==============================================================*/
#define    _GNU_SOURCE          /* to allow asprintf()                        */
#include <stdio.h>        /* printf(), snprintf()                             */
#include <stdlib.h>
#include <string.h>
#include <regex.h>        /* regcomp(), regexec(), regfree()                  */
#include "yVAR.h"


char      yVAR_ver     [500];

char*      /* ---- : return library versioning information -------------------*/
yVAR_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yVAR_ver, 100, "%s   %s : %s\n", t, YVAR_VER_NUM, YVAR_VER_TXT);
   return yVAR_ver;
}

/*====================------------------------------------====================*/
/*===----                         regex testing                        ----===*/
/*====================------------------------------------====================*/
static void      o___REGEX___________________o (void) {;}

int        /*----: standard regex pattern testing ----------------------------*/
yVAR_regex         (
      char     *a_format,        /*  requested format for testing             */
      char     *a_value)         /*  variable value to test                   */
{
   /*-----------------------------------------------functional-design-notes---#
    * *> excellent way to get the best regex format testers in one place
    * *> single point of testing and maintenance
    * *> absolutely vital to increasing "cracker resistence" through easy use
    * *> speeds up app-dev and reduces testing time and concerns
    */
   char       its_regex [100];                /* source regex                 */
   int        its_code   = 0;                 /* failure identifier           */
   /*===(string tests)============================================*/
   /* big rule :: avoid the metacharacters `'\"|*?~<>^()[]{}$\n\r */
   if      (strcmp(a_format, "strg_alnum")   == 0) {
      /*-> letters and numbers only                               */
      strcpy(its_regex, "^[a-zA-Z0-9]+$");
      its_code   = 11;
   }
   else if (strcmp(a_format, "strg_basic")   == 0) {
      /*-> str_alnum plus underscore, dash, and space             */
      strcpy(its_regex, "^[A-Za-z0-9][a-zA-Z0-9_ -]*$");
      its_code   = 12;
   }
   else if (strcmp(a_format, "strg_punct")   == 0) {
      /*-> str_basic plus normal writing symbols (? is edgy)      */
      strcpy(its_regex, "^[A-Za-z0-9][A-Za-z0-9_ .,:;!?-]*$");
      its_code   = 13;
   }
   else if (strcmp(a_format, "strg_exten")   == 0) {
      /*-> str_basic plus descriptive characters                  */
      strcpy(its_regex, "^[A-Za-z0-9][A-Za-z0-9_ .,:;@()-]*$");
      its_code   = 14;
   }
   /*===(cgi-post tests)=======================================*/
   else if   (strcmp(a_format, "post_field")   == 0) {
      /*-> cgi field name (and all lower case)                    */
      strcpy(its_regex, "^[a-z][a-z0-9_]{0,10}[a-z0-9]$");
      its_code   = 21;
   }
   else if (strcmp(a_format, "post_string")  == 0) {
      /*-> tbd                                                    */
      strcpy(its_regex, "^[A-Za-z0-9][A-Za-z0-9+=&%][A-Za-z0-9]*$");
      its_code   = 22;
   }
   /*===(integers)=============================================*/
   else if (strcmp(a_format, "intg_byte")    == 0) {
      /*-> a byte number                                          */
      strcpy(its_regex, "^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$");
      its_code   = 31;
   }
   else if (strcmp(a_format, "intg_unsign")  == 0) {
      /*-> a signed integer                                       */
      strcpy(its_regex, "^(0|[1-9][0-9]*)$");
      its_code   = 32;
   }
   else if (strcmp(a_format, "intg_sign")    == 0) {
      /*-> a signed integer                                       */
      strcpy(its_regex, "^(-)?(0|[1-9][0-9]*)$");
      its_code   = 33;
   }
   /*===(real numbers)=========================================*/
   else if (strcmp(a_format, "real_float")   == 0) {
      /*-> floating point                                         */
      strcpy(its_regex, "^(-)?(0|[1-9][0-9]*)([.][0-9]+)?$");
      its_code   = 34;
   }
   else if (strcmp(a_format, "real_pct")     == 0) {
      /*-> 0-100 percentage with optional two decimal places      */
      strcpy(its_regex, "^(-)?(100|[1-9]?[0-9]([.][0-9]{1,2})?)[%]?$");
      its_code   = 35;
   }
   /*===(addresses of various sorts)===========================*/
   else if (strcmp(a_format, "addr_ip")       == 0) {
      /*-> ip4 address                                            */
      strcpy(its_regex,
            "^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
            ".(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
            ".(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
            ".(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$");
      its_code   = 41;
   }
   else if (strcmp(a_format, "addr_email")   == 0) {
      /*-> email address                                          */
      strcpy(its_regex, "^[A-Za-z0-9_.-]+[@][A-Za-z0-9_.-]+.[A-Za-z]{2,4}$");
      its_code   = 42;
   }
   else if (strcmp(a_format, "addr_dir")    == 0) {
      /*-> directory name                                         */
      strcpy(its_regex, "^[/]?[A-Za-z][A-Za-z0-9_./-]$");
      its_code   = 43;
   }
   else if (strcmp(a_format, "addr_file")   == 0) {
      /*-> file name                                              */
      strcpy(its_regex, "^[.]?[A-Za-z][A-Za-z0-9_.-]{0,62}[A-Za-z0-9]$");
      its_code   = 44;
   }
   else if (strcmp(a_format, "addr_phone")   == 0) {
      /*-> US phone number                                        */
      strcpy(its_regex, "^([(]?[2-9][0-9]{2}[)]?[-. ])?[0-9]{3}[-. ][0-9]{4}$");
      its_code   = 45;
   }
   else if (strcmp(a_format, "addr_zip")    == 0) {
      /*-> US zip code                                            */
      strcpy(its_regex, "^[1-9][0-9]{4}([-][0-9]{4})?$");
      its_code   = 46;
   }
   /*===(archive related)======================================*/
   else if (strcmp(a_format, "arch_prefix")    == 0) {
      /*-> role and goal                                          */
      strcpy(its_regex, "^[1-9][a-z]$");
      its_code   = 51;
   }
   else if (strcmp(a_format, "arch_index")    == 0) {
      /*-> role and goal                                          */
      strcpy(its_regex, "^[1-9][a-z][-][1-9][0-9][0-9]$");
      its_code   = 52;
   }
   else if (strcmp(a_format, "arch_desc")    == 0) {
      /*-> role and goal                                           */
      strcpy(its_regex, "^[A-Za-z][A-Za-z0-9_-]*[A-Za-z0-9]$");
      its_code   = 53;
   }
   /*===(program element naming)===============================*/
   else if (strcmp(a_format, "prog_var")     == 0) {
      /*-> c-style variable name                                  */
      strcpy(its_regex, "^(_)*[a-zA-Z][a-zA-Z0-9_]*$");
      its_code   = 61;
   }
   else if (strcmp(a_format, "prog_myvar")   == 0) {
      /*-> c-style variable name                                  */
      strcpy(its_regex, "^([a-z]|[a-z][a-z0-9_]*[a-z0-9])$");
      its_code   = 62;
   }
   else if (strcmp(a_format, "prog_myconst")  == 0) {
      strcpy(its_regex, "^[A-Z][A-Z0-9_]*$");
      its_code   = 63;
   }
   else if (strcmp(a_format, "prog_func")     == 0) {
      strcpy(its_regex, "^[a-z_][a-zA-Z0-9_]*[a-zA-Z0-9]$");
      its_code   = 64;
   }
   /*===(linux specific)=======================================*/
   else if (strcmp(a_format, "path_norm" )   == 0) {
      strcpy (its_regex, "^[\/][\/a-zA-Z0-9_.-]*$");
      its_code   = 65;
   }
   else if (strcmp(a_format, "path_tight")   == 0) {
      strcpy (its_regex, "^[\/][\/a-zA-Z0-9_.]*$");
      its_code   = 65;
   }
   /*===(run it)===========================================*/
   if (its_code > 0) {
      /*---(compile the regex)-----------------------------*/
      int       x_rc = 0;
      regex_t   x_comp;
      x_rc    = regcomp(&x_comp, its_regex, REG_EXTENDED);
      if (x_rc != 0) its_code = -2;  /* could not compile successfully  */
      if (its_code > 0) {
         /*---(conduct test)--------------------------------*/
         x_rc    = regexec(&x_comp, a_value, 0, NULL, 0);
         if (x_rc != 0) its_code = -(its_code);   /* identify the failure */
      }
      regfree(&x_comp);
   }
   /*---(complete)------------------------------*/
   return its_code;                            /* identify success     */
}



/*====================------------------------------------====================*/
/*===----                         normal testing                       ----===*/
/*====================------------------------------------====================*/
static void      o___NORMAL__________________o (void) {;}

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_string (      /*  PURPOSE = STANDARD STRING TESTING (for yUNIT+)         */
      char     *a_test,          /*  name of the test                         */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
{
   /*
    * options are...
    *    1) s_equal        : actual   == expected
    *    2) s_not          : actual   != expected
    *    3) s_sub          : expected contained in actual
    *    4) s_entry        : actual string contained in a larger expected one
    *    5) s_regex        : do regex matching on expected using actual
    *    6) s_length       : check for a certain number of characters
    *    7) s_empty        : actual string is null/empty
    *    8) s_exists       : actual string is not null/empty
    *    9) s_greater      : actual string sorts greater than expected
    *   10) s_lesser       : actual string sorts lesser  than expected
    *
    * it is expected that 85% of calls will be s_equal, 10% s_not, then the rest
    * so, put them in that order to make as few strcmp as possible for speed
    */
   /*---(locals)-------------------------*/
   int       x_code    = -666;
   int       rc        = 0;
   regex_t   x_comp;
   /*---(defenses)-----------------------*/
   if (a_expect   == NULL) return x_code - 1;
   if (a_actual   == NULL) return x_code - 1;
   /*---(normal tests)-------------------*/
   if    (strcmp(a_test, "s_equal")   == 0) {
      x_code   = -10;
      if (strcmp(a_actual, a_expect) == 0)    x_code = -(x_code);
   } else if (strcmp(a_test, "s_not")     == 0) {
      x_code   = -11;
      if (strcmp(a_actual, a_expect) != 0)    x_code = -(x_code);
   } else if (strcmp(a_test, "s_empty")   == 0) {
      x_code   = -12;
      if (strlen(a_actual) == 0 ) x_code = -(x_code);
   } else if (strcmp(a_test, "s_exists")  == 0) {
      x_code   = -13;
      if (strlen(a_actual) > 0 ) x_code = -(x_code);
   } else if (strcmp(a_test, "s_length")  == 0) {
      x_code   = -14;
      if ((int) strlen(a_actual) != atoi(a_expect)) x_code = -(x_code);
   } else if (strcmp(a_test, "s_greater") == 0) {
      x_code   = -15;
      if (strcmp(a_actual, a_expect) > 0)    x_code = -(x_code);
   } else if (strcmp(a_test, "s_lesser")  == 0) {
      x_code   = -16;
      if (strcmp(a_actual, a_expect) < 0)    x_code = -(x_code);
   }
   /*---(search tests)-------------------*/
   else if   (strcmp(a_test, "s_sub")     == 0) {
      x_code   = -17;
      if (strstr(a_actual, a_expect) != NULL) x_code = -(x_code);
   } else if (strcmp(a_test, "s_entry")     == 0) {
      x_code   = -18;
      if (strstr(a_expect, a_actual) != NULL) x_code = -(x_code);
   }
   /*---(regex test)---------------------*/
   else if   (strcmp(a_test, "s_regex")    == 0) {
      x_code   = -19;
      rc    = regcomp(&x_comp, a_expect, REG_EXTENDED);
      if (rc == 0) {
         rc    = regexec(&x_comp, a_actual, 0, NULL, 0);
         if (rc == 0) x_code = -(x_code);
      }
      regfree(&x_comp);
   }
   /*---(complete)-----------------------*/
   return x_code;
}

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_integer (     /*  PURPOSE = STANDARD INTEGER TESTING (for yUNIT+)        */
      char     *a_test,          /*  name of the test                         */
      long      a_expect,        /*  expected result                          */
      long      a_actual)        /*  actual result                            */
{
   /*
    * options are...
    *    1) i_equal        : actual   == expected
    *    2) i_not          : actual   != expected
    *    3) i_greater      : actual   >  expected
    *    4) i_lesser       : actual   <  expected
    *    5) i_digits       : actual contains expected number of digits
    *    6) i_exists       : actual not null/empty/zero
    *    7) i_1percent     : actual matches expected +/- 1%
    *    8) i_5percent     : actual matches expected +/- 5%
    *    9) i_PASS         : greater than or equal to zero
    *   10) i_FAIL         : less than zero
    *
    * it is expected that 85% of calls will be s_equal, 10% s_not, then the rest
    */
   /*---(design notes)--------------------------------------------------------#
    * use longs to have maximum flexibility for char, short, int, and long
    * can not use long long as atoll is a C99 thing only
    */
   /*---(locals)-------------------------*/
   int       x_code    = -666;
   char      x_temp[100] = "";
   /*---(normal tests)-------------------*/
   if        (strcmp(a_test, "i_equal")    == 0) {
      x_code   = -21;
      if (a_actual == a_expect)    x_code = -(x_code);
   } else if (strcmp(a_test, "i_not")      == 0) {
      x_code   = -24;
      if (a_actual != a_expect)    x_code = -(x_code);
   } else if (strcmp(a_test, "i_greater")  == 0) {
      x_code   = -22;
      if (a_actual > a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "i_lesser")   == 0) {
      x_code   = -23;
      if (a_actual < a_expect)     x_code = -(x_code);
   }
   /*---(specialty tests)----------------*/
   else if   (strcmp(a_test, "i_digits")   == 0) {
      x_code   = -27;
      snprintf(x_temp, 100, "%ld", a_actual);
      if ((int) strlen(x_temp) == a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "i_null")     == 0) {
      x_code   = -28;
      if (a_actual == 0)           x_code = -(x_code);
   } else if (strcmp(a_test, "i_exists")   == 0) {
      x_code   = -29;
      if (a_actual != 0)           x_code = -(x_code);
   }
   /*---(poximity tests)-----------------*/
   else if   (strcmp(a_test, "i_1percent") == 0) {
      x_code   = -30;
      if (a_actual >= a_expect * 0.99 &&
            a_actual <= a_expect * 1.01)  x_code = -(x_code);
   } else if (strcmp(a_test, "i_5percent") == 0) {
      x_code   = -30;
      if (a_actual >= a_expect * 0.95 &&
            a_actual <= a_expect * 1.05)  x_code = -(x_code);
   }
   /*---(return code tests)--------------*/
   else if   (strcmp(a_test, "i_PASS")     == 0) {
      x_code   = -25;
      if (a_actual >= 0)           x_code = -(x_code);
   } else if (strcmp(a_test, "i_FAIL")     == 0) {
      x_code   = -26;
      if (a_actual < 0)            x_code = -(x_code);
   }
   /*---(complete)-----------------------*/
   return x_code;
}

int        /*----: standard pointer testing for yUNIT ------------------------*/
yVAR_pointer       (char *a_test, void *a_expect, void *a_actual)
{
   /*
    * options are...
    *    1) p_equal        : actual   == expected
    *    2) p_not          : actual   != expected
    *    3) p_greater      : actual   >  expected
    *    4) p_lesser       : actual   <  expected
    *    5) p_null         : actual null/empty/zero
    *    6) p_exists       : actual not null/empty/zero
    *
    * it is expected that 90% of calls will be p_exists and p_null
    */
   /*---(locals)-------------------------*/
   int   x_code = -666;
   /*---(normal tests)-------------------*/
   if        (strcmp(a_test, "p_equal")    == 0) {
      x_code   = -41;
      if (a_actual == a_expect)    x_code = -(x_code);
   } else if (strcmp(a_test, "p_not")      == 0) {
      x_code   = -42;
      if (a_actual != a_expect)    x_code = -(x_code);
   } else if (strcmp(a_test, "p_greater")  == 0) {
      x_code   = -43;
      if (a_actual > a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "p_lesser")   == 0) {
      x_code   = -44;
      if (a_actual < a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "p_null")     == 0) {
      x_code   = -45;
      if (a_actual == 0)           x_code = -(x_code);
   } else if (strcmp(a_test, "p_exists")   == 0) {
      x_code   = -46;
      if (a_actual != 0)           x_code = -(x_code);
   } else if (strcmp(a_test, "p_any")      == 0) {
      x_code   =  47;
   }
   /*---(complete)-----------------------*/
   return x_code;
}


int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_real (        /*  PURPOSE = STANDARD REAL NUM TESTING (for yUNIT+)       */
      char     *a_test,          /*  name of the test                         */
      double    a_expect,        /*  expected result                          */
      double    a_actual)        /*  actual result                            */
{
   /*---(design notes)--------------------------------------------------------#
    * use longs to have maximum flexibility for char, short, int, and long
    * can not use long long as atoll is a C99 thing only
    */
   int x_code = 0;
   if  (strcmp(a_test, "r_equal")    == 0) {
      x_code   = -21;
      if (a_actual == a_expect)    x_code = -(x_code);
   } else if (strcmp(a_test, "r_greater")  == 0) {
      x_code   = -22;
      if (a_actual > a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "r_lesser")   == 0) {
      x_code   = -23;
      if (a_actual < a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "r_not")      == 0) {
      x_code   = -24;
      if (a_actual != a_expect)    x_code = -(x_code);
   } else if (strcmp(a_test, "r_norm93")       == 0) {
      x_code   = -25;
      snprintf (yVAR_one, 15, "%9.3lf", a_expect);
      snprintf (yVAR_two, 15, "%9.3lf", a_actual);
      if (strcmp(yVAR_one, yVAR_two) == 0)    x_code = -(x_code);
   } else {
      x_code   = -999;
   }
   return x_code;
}




/*====================------------------------------------====================*/
/*===----                       specialty testing                      ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIAL_________________o (void) {;}

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_ustring (     /*  PURPOSE = complex string tests for yUNIT               */
      char     *a_test,          /*  name of the test                         */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
{
   /*---(locals)------------------------------------------*/
   int nl = 0;
   int   len_exp  = 0;
   int   len_act  = 0;
   int       i;                 /* loop counter */
   int       s, e, len;
   int       x_off     = 0;
   char      ch        = ' ';
   int       is_dec    = 0;
   int       decs      = 0;
   int       nums      = 0;
   int       pos;
   int       mods      = 0;
   char      mods_str[20] = "";
   char      x_expect[100], x_actual[100];
   int       rc        = 0;
   int   x_code   = 0;
   int  x_range = 1;
   regex_t     x_comp;
   regmatch_t  x_pmatch[1];
   char x_act[5];
   /*---(fix new lines)-----------------------------------*/
   i = strlen(a_actual) - 1;
   if (a_actual[i] == '\n') {
      a_actual[i] = '\0';
      ++nl;
   }
   for (i = 0; i < (int) strlen(a_actual); ++i) {
      if (a_actual[i] == '\n') {
         a_actual[i] = ' ';
         ++nl;
      }
   }
   /*---(defensive logic)---------------------------------*/
   len_exp  = strlen(a_expect);
   len_act  = strlen(a_actual);
   if (len_exp != len_act)   return -1;
   if (len_act == 0)         return -2;
   if (strlen(a_test) < 4)   return -3;
   if (a_test[0] != 'u')     return -4;
   if (a_test[1] != '_')     return -5;
   /*---(local variables)---------------------------------*/
   /*===[[ UNIT TEST SPECIALTIES ]]==========================================*/
   if   (strcmp(a_test, "u_round")     == 0 ||
         strcmp(a_test, "u_round2")    == 0 ||
         strcmp(a_test, "u_round5")    == 0 ||
         strcmp(a_test, "u_round9")    == 0) {
      if      (strcmp(a_test, "u_round2")    == 0) x_range = 2;
      else if (strcmp(a_test, "u_round5")    == 0) x_range = 5;
      else if (strcmp(a_test, "u_round9")    == 0) x_range = 9;
      x_code   = -30;
      /*---(check for agreement early)---------------*/
      if (strcmp(a_actual, a_expect) == 0) {
         x_code = -(x_code);
         return x_code;
      }
      /*---(attempt to round)------------------------*/
      /*---(create the RE)----------------------*/
      rc = regcomp(&x_comp, " (-)?(0|[1-9][0-9]*)([.][0-9]+)?", REG_EXTENDED);
      if (rc != 0) return -7;
      /*---(initial RE run)---------------------*/
      rc = regexec(&x_comp, a_expect, 1, x_pmatch, 0);
      /*---(process matches)--------------------*/
      while (rc == 0) {
         /*---(get match information)-----------*/
         s   = x_pmatch[0].rm_so;
         e   = x_pmatch[0].rm_eo;
         len = e - s;
         /*---(prepare for substring)-----------*/
         nums = decs = is_dec = 0;
         strncpy(x_expect, "", 100);
         strncpy(x_actual, "", 100);
         /*---(process the substring)-----------*/
         for (i = 0; i < len; ++i) {
            pos = s + x_off + i;
            ch = a_expect[pos];
            if (is_dec == 1) ++decs;
            if (ch == '.')   is_dec = 1;
            if (ch != ' ')   ++nums;
            /*> printf("%c", a_expect[s + x_off + i]);                                <*/
            x_expect[i] = a_expect[pos];
            x_actual[i] = a_actual[pos];
         }
         /*---(clean up the substring)----------*/
         strncat(x_expect, "\0", 100);
         strncat(x_actual, "\0", 100);
         /*---(deal with differences)-----------*/
         if (strcmp(x_expect, x_actual) != 0) {
            float val_one = atof(x_expect);
            float val_inc = 1;
            char  x_top[100], x_bot[100], x_neg[100], x_fin[100];
            /*---(create options)---------------*/
            for (i = 0; i < decs; ++i) val_inc /= 10;
            snprintf(x_top, 100, " %*.*f", nums, decs, val_one + val_inc);
            snprintf(x_bot, 100, " %*.*f", nums, decs, val_one - val_inc);
            snprintf(x_neg, 100, " %*.*f", nums, decs, val_one - 0.00001);
            /*---(test the options)-------------*/
            strncpy(x_fin, "", 100);
            if (strcmp(x_top, x_actual) == 0) {
               ++mods;
               strncpy(x_fin, x_top, 100);
            } else if (strcmp(x_bot, x_actual) == 0) {
               ++mods;
               strncpy(x_fin, x_bot, 100);
            } else if (strcmp(x_neg, x_actual) == 0) {
               ++mods;
               strncpy(x_fin, x_neg, 100);
            }
            /*---(change expected)---------------*/
            for (i = 0; i < (int) strlen(x_fin); ++i) a_expect[s + x_off + i] = x_fin[i];
         }
         /*---(setup for next)------------------*/
         x_off += e;
         if (x_off >= len_exp) break;
         rc = regexec(&x_comp, a_expect + x_off, 1, x_pmatch, 0);
      }
      regfree(&x_comp);
      /*---(mask off color hexs)--------------------------*/
      rc = regcomp(&x_comp, "#[0-9a-fA-F]{6}", REG_EXTENDED);
      if (rc != 0) return -7;
      rc = regexec(&x_comp, a_expect, 1, x_pmatch, 0);
      x_off = 0;
      while (rc == 0) {
         s   = x_pmatch[0].rm_so + 1;   /* go over " #" */
         for (i = 0; i < 5; i += 2) {
            char x_exp[5];
            x_exp[0] = a_expect[x_off + s + i];
            x_exp[1] = a_expect[x_off + s + i + 1];
            x_exp[2] = '\0';
            x_act[0] = a_actual[x_off + s + i];
            x_act[1] = a_actual[x_off + s + i + 1];
            x_act[2] = '\0';
            if (strcmp(x_act, x_exp) == 0) continue;
            yVAR_hex(x_range, x_exp, x_act);
            if (strcmp(x_act, x_exp) != 0) continue;
            a_expect[x_off + s + i]     = x_exp[0];
            a_expect[x_off + s + i + 1] = x_exp[1];
            ++mods;
         }
         /*---(prepare for next)----------------------*/
         x_off += s + 2;
         if (x_off >= len_exp) break;
         rc = regexec(&x_comp, a_expect + x_off, 1, x_pmatch, 0);
      }
      regfree(&x_comp);
      /*---(finish)---------------------------------------*/
      if (strcmp(a_actual, a_expect) == 0) x_code = -(x_code);
      if (mods > 0) {
         snprintf(mods_str, 20, ">> FIX=%1d ", mods);
         strncat(a_expect, mods_str, 499);
      }
      if (nl   > 0) {
         snprintf(mods_str, 20, ">> NL=%1d ", nl);
         strncat(a_actual, mods_str, 499);
      }
      /*===============================================================================*/
   }
   else {
      x_code   = -999;
   }
   return x_code;
}

int        /*----: strings that allow numbers to be rounded ------------------*/
yVAR_round (
      const char *a_test,              /*  name of the test                   */
      const char *a_expect,            /*  expected result                    */
      const char *a_actual)            /*  actual result                      */
{
   /*---(design notes)-------------------*/
   /*
    * - numbers must have a leading space to insure they're not just imbedded
    * - numbers are converted to floats so are limited in precision
    *
    */
   /*> printf("yVAR_round\n");                                                        <*/
   /*---(local variables)---------------------------------*/
   char      x_expect[500]  = "";      /* working version of expected string  */
   char      x_actual[500]  = "";      /* working version of actual string    */
   int       len_exp   = 0;            /* length of expected string           */
   int       len_act   = 0;            /* length of actual string             */
   int       x_range   = 1;            /* rounding value, i.e. +/-            */
   int       i         = 0;            /* loop iterator -- characters         */
   int       j         = 0;            /* loop iterator -- decimals           */
   regex_t   x_comp;                   /* REGEX structure                     */
   regmatch_t  x_pmatch[1];            /* REGEX match structure               */
   int       s, e, len;                /* REGEX position markers              */
   int       rc        = 0;            /* generic return code                 */
   int       x_off     = 0;
   char      ch        = ' ';
   int       is_dec    = 0;
   int       decs      = 0;
   int       nums      = 0;
   int       pos;
   int       mods      = 0;
   char      mods_str[20] = "";
   char      x_expsub[100], x_actsub[100];
   double    val_bas = 0.0;
   double    val_inc = 1.0;
   double    val_new = 0.0;
   char      x_top[100], x_zero[100], x_neg[100], x_fin[100];
   /*> printf("\n");                                                                  <*/
   /*> printf("yVAR_round begin with three arguments\n");                             <*/
   /*> printf("a_test    = %s\n", a_test);                                            <*/
   /*> printf("a_expect  = %s\n", a_expect);                                          <*/
   /*> printf("a_actual  = %s\n", a_actual);                                          <*/
   /*---(defensive logic)---------------------------------*/
   if (strlen(a_test) != 8)                 return -601;
   if (strncmp(a_test, "u_round", 7) != 0)  return -602;
   if (a_test[7] == 'z')  x_range = 0;
   else                   x_range = a_test[7] - '0';
   /*> printf("range is  = +/- %d\n", x_range);                                       <*/
   if (x_range < 0 || x_range > 9)          return -603;
   /*---(make local copies)-------------------------------*/
   len_exp  = strlen(a_expect);
   len_act  = strlen(a_actual);
   if (len_exp >= 500)                      return -604;
   if (len_act >= 500)                      return -605;
   strncpy(x_expect, a_expect, 500);
   strncpy(x_actual, a_actual, 500);
   /*---(fix actual's new lines)--------------------------*/
   if (x_actual[len_act - 1] == '\n') { x_actual[--len_act] = '\0'; ++mods; }
   for (i = 0; i < len_act; ++i) if (x_actual[i] == '\n') { x_actual[i] = ' '; ++mods; }
   if (len_act == 0)                        return -606;
   if (len_exp == 0)                        return -607;
   if (len_exp != len_act)                  return -608;
   /*---(initialize modded string)------------------------*/
   for (i = 0; i < len_exp; ++i) yVAR_modded[i] = ' ';
   yVAR_modded[len_exp] = '\0';
   /*---(quick shortcut check)----------------------------*/
   if (strcmp(x_actual, x_expect) == 0) {
      /*> printf("   already equal, no mods required (shortcut)\n");                  <*/
      return 0;
   }
   /*---(create the regex)-------------------*/
   rc = regcomp(&x_comp, "[- ](0|[1-9][0-9]*)([.][0-9]+)?", REG_EXTENDED);
   if (rc != 0)                             return -609;
   /*---(initial RE run)---------------------*/
   rc = regexec(&x_comp, x_expect, 1, x_pmatch, 0);
   if (rc != 0)                             return -610;
   /*---(process matches)--------------------*/
   while (rc == 0) {
      /*> printf("identifying numbers in the string... \n");                          <*/
      /*---(get match information)-----------*/
      s   = x_pmatch[0].rm_so;
      e   = x_pmatch[0].rm_eo;
      len = e - s;
      /*> printf("   found match from %d to %d, len %d-----------------------\n", s, e, len);   <*/
      /*---(process the match)---------------*/
      nums = decs = is_dec = 0;
      strncpy(x_expsub, "", 100);
      strncpy(x_actsub, "", 100);
      for (i = 0; i < len; ++i) {
         pos = s + x_off + i;
         ch = x_expect[pos];
         if (is_dec == 1) ++decs;
         if (ch == '.')   is_dec = 1;
         if (ch != ' ' && ch != '-')   ++nums;
         /*> printf("%c", x_expect[s + x_off + i]);                                   <*/
         x_expsub[i] = x_expect[pos];
         x_actsub[i] = x_actual[pos];
      }
      /*> printf("   nums=%d, decs=%d\n", nums, decs);                                <*/
      strncat(x_expsub, "\0", 100);
      strncat(x_actsub, "\0", 100);
      /*> printf("   expsub    = <<%s>>\n", x_expsub);                                <*/
      /*> printf("   expact    = <<%s>>\n", x_actsub);                                <*/
      val_bas   = atof(x_expsub);
      snprintf(x_zero, 100, " %*.*f",  nums, decs, 0.0);
      snprintf(x_neg , 100, "-%*.*f",  nums, decs, 0.0);
      /*---(deal with differences)-----------*/
      /*> printf("   ranging   = %d to %d\n", -x_range, x_range);                     <*/
      for (i = -x_range; i <= x_range; ++i) {
         /*---(prepare)-----------------------*/
         val_inc   = i;
         strncpy(x_fin, "", 100);
         for (j = 0; j < decs; ++j) val_inc /= 10;
         val_new = val_bas + val_inc;
         /*> printf("   %d, val_bas=%11.7lf, val_inc=%11.7lf, val_new=%12.8lf\n", i, val_bas, val_inc, val_new);   <*/
         /*---(generate)----------------------*/
         if (val_new >= 0) snprintf(x_top, 100, " %*.*f", nums, decs, val_new);
         else              snprintf(x_top, 100, "%*.*f",  nums, decs, val_new);
         /*---(test)--------------------------*/
         /*> printf("   test      = <<%s>> : ", x_top);                               <*/
         if (strcmp(x_top, x_actsub) != 0) {
            /*> printf("missed");                                                     <*/
            if (strcmp(x_top, x_zero) == 0) {
               /*> printf(", trying neg zero : ");                                    <*/
               if (strcmp(x_neg , x_actsub) != 0) {
                  /*> printf("nope\n");                                               <*/
                  continue;
               }
               strcpy(x_top, x_neg );
            } else if (strcmp(x_top, x_neg ) == 0) {
               /*> printf(", trying pos zero : ");                                    <*/
               if (strcmp(x_zero, x_actsub) != 0) { 
                  /*> printf("nope\n");                                               <*/
                  continue;
               }
               strcpy(x_top, x_zero);
            } else {
               /*> printf("\n");                                                      <*/
               continue;
            }
         }
         /*---(change expected)---------------*/
         /*> printf("found\n");                                                       <*/
         strncpy(x_fin, x_top, 100);
         for (i = 0; i < (int) strlen(x_fin); ++i) x_expect[s + x_off + i] = x_fin[i];
         break;
      }
      /*---(setup for next)------------------*/
      x_off += e;
      if (x_off >= len_exp) break;
      rc = regexec(&x_comp, x_expect + x_off, 1, x_pmatch, 0);
   }
   regfree(&x_comp);
   /*---(finish)---------------------------------------*/
   for (i = 0; i < len_exp; ++i) {
      if (x_expect[i] != a_expect[i]) {
         ++mods;
         yVAR_modded[i] = x_expect[i];
         if (x_expect[i] <= ' ')  yVAR_modded[i] = '*';
         if (x_expect[i] >  'z')  yVAR_modded[i] = '*';
      }
   }
   snprintf(mods_str, 20, ">> (%1d) ", mods);
   strncat(yVAR_modded, mods_str, 499);
   /*---(complete)-------------------------------------*/
   if (strcmp(x_actual, x_expect) == 0) return mods;
   return -30;
}



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*      /*----: return the modified string mask ---------------------------*/
yVAR_mod           (void)
{
   return yVAR_modded;
}

char*      /*----: return the modified expected ------------------------------*/
yVAR_expect        (void)
{
   return yVAR_one;
}

char*      /*----: return the modified actual --------------------------------*/
yVAR_actual        (void)
{
   return yVAR_two;
}

void
yVAR_hex (
      int       a_range,         /*  how far off can it be +/-                */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
{
   /*> printf("entering yVAR_hex\n");                                                <* 
    *> printf("   text   :: %se, %sa\n", a_expect, a_actual);                         <*/
   /*---(locals)--------------------------------*/
   int   len_exp  = 0;
   int   len_act  = 0;
   int   x_exp = 0;
   int   x_act = 0;
   int x_fin = 0;
   int i = 0;
   /*---(defense)-------------------------------*/
   len_exp  = strlen(a_expect);
   len_act  = strlen(a_actual);
   /*> printf("   len    :: %de, %da\n", len_exp, len_act);                           <*/
   if (len_exp != len_act)   return;
   if (len_act <  2)         return;
   /*---(convert to number)---------------------*/
   sscanf(a_expect, "%x", &x_exp);
   sscanf(a_actual, "%x", &x_act);
   /*> printf("   values :: %de, %da\n", x_exp, x_act);                               <*/
   if (x_exp == x_act) return;
   /*---(try up and down)-----------------------*/
   x_fin = x_exp;
   for (i = -a_range; i <= a_range; ++i) if (x_act == x_exp + i) x_fin = x_act;
   /*> if        (x_act == x_exp + 1) {                                               <* 
    *>    x_fin = x_exp + 1;                                                          <* 
    *> } else if (x_act == x_exp - 1) {                                               <* 
    *>    x_fin = x_exp - 1;                                                          <* 
    *> }                                                                              <*/
   /*> printf("   before :: %d\n", x_fin);                                            <*/
   if (x_fin > 255) x_fin = 255;
   if (x_fin < 0)   x_fin = 0;
   /*> printf("   after  :: %d\n", x_fin);                                            <*/
   snprintf(a_expect, 500, "%02x", x_fin);
   /*> printf("   return :: %s\n", a_expect);                                         <*/
   /*---(complete)------------------------------*/
   /*> printf("exiting yVAR_hex\n");                                                 <*/
   return;
}


/*===[[ END ]]================================================================*/
