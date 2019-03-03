/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"


tLOCAL    its;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

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
   strncpy (t, "[hephaestus ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yVAR_ver, 100, "%s   %s : %s\n", t, P_VERNUM, P_VERTXT);
   return yVAR_ver;
}

char         /*--> set debugging mode --------------------[ ------ [ ------ ]-*/
yVAR_debug         (char a_flag)
{
   /*---(set debug flag)-----------------*/
   if   (a_flag == 'y')  its.debug   = 'y';
   else                  its.debug   = '-';
   /*---(complete)-----------------------*/
   return 0;
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
   /*---(locals)-----------+-----+-----+-*/
   int         x_code      = -666;
   int         rc          =    0;
   int         i           =    0;
   regex_t     x_comp;
   char        x_actual    [LEN_RECD];
   char        x_expect    [LEN_RECD];
   int         x_len       =    0;
   /*---(defenses)-----------------------*/
   if (a_test     == NULL  ) return x_code - 1;
   if (a_expect   == NULL  ) return x_code - 2;
   if (a_actual   == NULL  ) return x_code - 3;
   if (a_expect   <  0x1000) return x_code - 4;
   if (a_actual   <  0x1000) return x_code - 5;
   /*---(block masked areas)-------------*/
   strcpy (x_actual, a_actual);
   strcpy (x_expect, a_expect);
   x_len = strlen (a_actual);
   x_expect [x_len] = '\0';
   for (i = 0; i < x_len; ++i) {
      if (x_expect [i] == NULL || x_actual [i] == NULL)  break;
      if (x_expect [i] == '¬')  x_actual [i] = '¬';
   }
   /*---(normal tests)-------------------*/
   if    (strcmp(a_test, "s_equal")   == 0) {
      x_code   = -10;
      if (strcmp(x_actual, x_expect) == 0)    x_code = -(x_code);
   } else if (strcmp(a_test, "s_not")     == 0) {
      x_code   = -11;
      if (strcmp(x_actual, x_expect) != 0)    x_code = -(x_code);
   } else if (strcmp(a_test, "s_empty")   == 0) {
      x_code   = -12;
      if (strlen(x_actual) == 0 ) x_code = -(x_code);
   } else if (strcmp(a_test, "s_exists")  == 0) {
      x_code   = -13;
      if (strlen(x_actual) > 0 ) x_code = -(x_code);
   } else if (strcmp(a_test, "s_length")  == 0) {
      x_code   = -14;
      if ((int) strlen(x_actual) == atoi(x_expect)) x_code = -(x_code);
   } else if (strcmp(a_test, "s_greater") == 0) {
      x_code   = -15;
      if (strcmp(x_actual, x_expect) > 0)    x_code = -(x_code);
   } else if (strcmp(a_test, "s_lesser")  == 0) {
      x_code   = -16;
      if (strcmp(x_actual, x_expect) < 0)    x_code = -(x_code);
   }
   /*---(search tests)-------------------*/
   else if   (strcmp(a_test, "s_sub")     == 0) {
      x_code   = -17;
      if (strstr(x_actual, x_expect) != NULL) x_code = -(x_code);
   } else if (strcmp(a_test, "s_entry")     == 0) {
      x_code   = -18;
      if (strstr(x_expect, x_actual) != NULL) x_code = -(x_code);
   }
   /*---(regex test)---------------------*/
   else if   (strcmp(a_test, "s_regex")    == 0) {
      x_code   = -19;
      rc    = regcomp(&x_comp, x_expect, REG_EXTENDED);
      if (rc == 0) {
         rc    = regexec(&x_comp, x_actual, 0, NULL, 0);
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
    *    5) i_gtequal      : actual   >= expected
    *    6) i_ltequal      : actual   <= expected
    *    7) i_digits       : actual contains expected number of digits
    *    8) i_exists       : actual not null/empty/zero
    *    9) i_1percent     : actual matches expected +/- 1%
    *   10) i_5percent     : actual matches expected +/- 5%
    *   11) i_PASS         : greater than or equal to zero
    *   12) i_FAIL         : less than zero
    *
    * it is expected that 85% of calls will be s_equal, 10% s_not, then the rest
    */
   /*---(design notes)--------------------------------------------------------#
    * use longs to have maximum flexibility for char, short, int, and long
    * can not use long long as atoll is a C99 thing only
    */
   /*---(locals)-------------------------*/
   int       x_code    = -666;
   char      x_temp[LEN_RECD] = "";
   /*---(defenses)-----------------------*/
   if (a_test     == NULL) return x_code - 1;
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
   } else if (strcmp(a_test, "i_gtequal")  == 0) {
      x_code   = -24;
      if (a_actual >= a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "i_ltequal")  == 0) {
      x_code   = -25;
      if (a_actual <= a_expect)     x_code = -(x_code);
   }
   /*---(specialty tests)----------------*/
   else if   (strcmp(a_test, "i_digits")   == 0) {
      x_code   = -27;
      snprintf(x_temp, LEN_RECD, "%ld", a_actual);
      if ((int) strlen(x_temp) == a_expect)     x_code = -(x_code);
   } else if (strcmp(a_test, "i_zero"  )     == 0) {
      x_code   = -28;
      if (a_actual == 0)           x_code = -(x_code);
   } else if (strcmp(a_test, "i_exists")   == 0) {
      x_code   = -29;
      if (a_actual != 0)           x_code = -(x_code);
   }
   /*---(poximity tests)-----------------*/
   else if   (strcmp(a_test, "i_1pct" ) == 0) {
      x_code   = -30;
      if (a_actual >= a_expect * 0.99 &&
            a_actual <= a_expect * 1.01)  x_code = -(x_code);
   } else if (strcmp(a_test, "i_5pct" ) == 0) {
      x_code   = -30;
      if (a_actual >= a_expect * 0.95 &&
            a_actual <= a_expect * 1.05)  x_code = -(x_code);
   }
   /*---(return code tests)--------------*/
   else if   (strcmp(a_test, "i_pass" )     == 0) {
      x_code   = -25;
      if (a_actual >= 0)           x_code = -(x_code);
   } else if (strcmp(a_test, "i_fail" )     == 0) {
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
      snprintf (yVAR_expstr, 15, "%9.3lf", a_expect);
      snprintf (yVAR_actstr, 15, "%9.3lf", a_actual);
      if (strcmp(yVAR_expstr, yVAR_actstr) == 0)    x_code = -(x_code);
   } else {
      x_code   = -999;
   }
   return x_code;
}




/*====================------------------------------------====================*/
/*===----                     numbers in strings                       ----===*/
/*====================------------------------------------====================*/
static void      o___ROUNDING________________o (void) {;}

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
   char      x_expect[LEN_RECD], x_actual[LEN_RECD];
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
         strncpy(x_expect, "", LEN_RECD);
         strncpy(x_actual, "", LEN_RECD);
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
         strncat(x_expect, "\0", LEN_RECD);
         strncat(x_actual, "\0", LEN_RECD);
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


static   int   s_range            = 0;
static   int   s_explen           = 0;
static   int   s_actlen           = 0;
static   int   s_nmods            = 0;

static   regex_t     s_regex;                  /* REGEX structure                     */
static   regmatch_t  s_match   [1];            /* REGEX match structure               */
static   char        s_expsub  [100];
static   char        s_actsub  [100];
static   int         s_lensub  = 0;
static   int         s_offset  = 0;
static   s_beg       = 0;
static   s_end       = 0;
static   s_len       = 0;
static   s_dec       = 0;


char
yVAR__save         (
      const char *a_test,              /*  name of the test                   */
      const char *a_expect,            /*  expected result                    */
      const char *a_actual)            /*  actual result                      */
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* generic return code            */
   int         i           = 0;             /* generic iterator               */
   /*---(header)-------------------------*/
   DEBUG_YVAR   printf ("\n");
   DEBUG_YVAR   printf ("yVAR_round begin with three arguments\n");
   DEBUG_YVAR   printf ("a_test      = <<%s>>\n" , a_test);
   DEBUG_YVAR   printf ("a_expect    = <<%s>>\n" , a_expect);
   DEBUG_YVAR   printf ("a_actual    = <<%s>>\n" , a_actual);
   /*---(basic defenses)-----------------*/
   --rce;  if (a_test     == NULL)                    return rce;
   --rce;  if (a_expect   == NULL)                    return rce;
   --rce;  if (a_actual   == NULL)                    return rce;
   /*---(test type)----------------------*/
   --rce;  if (strlen  (a_test) != 9)                 return rce;
   --rce;  if (strncmp (a_test, "u_round/", 8) != 0)  return rce;
   if (a_test [8] == 'z')  s_range = 0;
   else                    s_range = a_test[8] - '0';
   --rce;  if (s_range < 0 || s_range > 9)            return rce;
   DEBUG_YVAR   printf ("range is    = */- %d\n", s_range);
   /*---(make local copies)--------------*/
   s_explen  = strlen (a_expect);
   s_actlen  = strlen (a_actual);
   --rce;  if (s_explen >= 500)                       return -604;
   --rce;  if (s_actlen >= 500)                       return -605;
   strncpy (yVAR_expstr, a_expect, 500);
   strncpy (yVAR_actstr, a_actual, 500);
   /*---(initialize)---------------------*/
   s_nmods     = 0;
   s_offset    = 0;
   /*---(fix actual's new lines)---------*/
   if (yVAR_actstr [s_actlen - 1] == '\n') {
      yVAR_actstr [--s_actlen] = '\0';
      ++s_nmods;
   }
   for (i = 0; i < s_actlen; ++i) {
      if (yVAR_actstr [i] == '\n') {
         yVAR_actstr [i] = ' ';
         ++s_nmods; 
      }
   }
   /*---(check lengths)------------------*/
   --rce;  if (s_actlen == 0)                         return -606;
   --rce;  if (s_explen == 0)                         return -607;
   --rce;  if (s_explen != s_actlen)                  return -608;
   /*---(initialize modded string)-------*/
   for (i = 0; i < s_explen; ++i) {
      yVAR_modstr [i] = ' ';
   }
   yVAR_modstr [s_explen] = '\0';
   /*---(create the regex)-------------------*/
   /*> rc = regcomp(&s_regex, "[- ](0|[1-9][0-9]*)([.][0-9]+)?", REG_EXTENDED);        <*/
   rc = regcomp (&s_regex, "[ ]*[- ](0|[1-9][0-9]*)([.][0-9]+)?", REG_EXTENDED);
   --rce;  if (rc != 0)                               return rce;
   /*---(complete)-----------------------*/
   return 0;
}

char
yVAR__match        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* generic return code            */
   int         i           = 0;             /* generic iterator               */
   int         x_pos       = 0;
   int         x_isdec     = '-';
   char        ch          = ' ';
   /*---(execute regex)------------------*/
   /*  zero = successful match   */
   rc = regexec(&s_regex, yVAR_expstr + s_offset, 1, s_match, 0);
   --rce;  if (rc != 0)                               return rce;
   /*---(get match information)-----------*/
   s_beg   = s_match [0].rm_so;
   s_end   = s_match [0].rm_eo;
   s_len   = s_end - s_beg;
   DEBUG_YVAR   printf ("   found match from %d to %d, len %d -----------------------\n", s_beg, s_end, s_len);
   DEBUG_YVAR   printf ("   yVAR_expstr = <<%s>>\n" , yVAR_expstr);
   DEBUG_YVAR   printf ("   yVAR_actstr = <<%s>>\n" , yVAR_actstr);
   DEBUG_YVAR   printf ("                   ");
   for (i = 0; i < s_beg + s_offset; ++i) { 
      DEBUG_YVAR   printf (" ");
   }
   for (i = 0; i < s_len; ++i) { 
      DEBUG_YVAR   printf ("-");
   }
   DEBUG_YVAR   printf ("\n");
   /*---(process the match)---------------*/
   strncpy (s_expsub, "", 100);
   strncpy (s_actsub, "", 100);
   s_dec = 0;
   for (i = 0; i < s_len; ++i) {
      x_pos = s_beg + s_offset + i;
      ch = yVAR_expstr [x_pos];
      if (x_isdec == 'y') ++s_dec;
      if (ch == '.') {
         x_isdec = 'y';
         s_dec = 0;
      }
      /*> DEBUG_YVAR   printf("%c", yVAR_expstr[s_beg + x_off + i]);                  <*/
      s_expsub [i] = yVAR_expstr [x_pos];
      s_actsub [i] = yVAR_actstr [x_pos];
   }
   DEBUG_YVAR   printf ("   s_len = %d, decs = %d\n", s_len, s_dec);
   strncat (s_expsub, "\0", 100);
   strncat (s_actsub, "\0", 100);
   DEBUG_YVAR   printf ("   expsub      = <<%s>>\n", s_expsub);
   DEBUG_YVAR   printf ("   actsub      = <<%s>>\n", s_actsub);
   /*---(complete)-----------------------*/
   return 0;
}

char
yVAR__check        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          = 0;             /* generic return code            */
   int         i           = 0;             /* generic iterator               */
   int         j           = 0;             /* generic iterator               */
   double      x_base      = 0.0;
   double      x_inc       = 0.0;
   double      x_new       = 0.0;
   char        x_chksub    [100];
   char        x_negsub    [100];
   char        x_finsub    [100];
   /*---(quick check)--------------------*/
   if (strcmp (s_expsub, s_actsub) == 0) {
      DEBUG_YVAR   printf ("   already matches, done\n");
      return 0;
   }
   /*---(initialize)---------------------*/
   x_base    = atof (s_expsub);
   DEBUG_YVAR   printf ("   ranging   = %d to %d\n", -s_range, s_range);
   /*---(check each in range)------------*/
   for (i = -s_range; i <= s_range; ++i) {
      x_new = atof (s_expsub);
      /*---(create options)---------------*/
      x_inc = i;
      for (j = 0; j < s_dec; ++j)  x_inc /= 10;
      x_new = x_base + x_inc;
      DEBUG_YVAR   printf ("   dec = %d, chg = %2d, base = %10lf, inc = %10lf, new = %10lf\n", s_dec, i, x_base, x_inc, x_new);
      snprintf (x_chksub, 100, "%*.*lf", s_len, s_dec, x_new);
      snprintf (x_negsub, 100, "%*.*lf", s_len, s_dec, x_new - 0.000000001);
      DEBUG_YVAR   printf ("   checking  = <<%s>>  :: ", x_chksub);
      /*---(test the options)-------------*/
      strncpy (x_finsub, "", 100);
      if (strcmp (x_chksub, s_actsub) == 0) {
         DEBUG_YVAR   printf ("match\n");
         strncpy (x_finsub, x_chksub, 100);
         break;
      } else if (strcmp(x_negsub, s_actsub) == 0) {
         DEBUG_YVAR   printf ("match neg zero\n");
         strncpy (x_finsub, x_negsub, 100);
         break;
      } else {
         DEBUG_YVAR   printf ("not a match\n");
      }

   }
   --rce;  if (strcmp (x_finsub, "") == 0) {
      DEBUG_YVAR   printf ("NO MATCH\n");
      return rce;
   }
   /*---(update expect)------------------*/
   for (i = 0; i < s_len; ++i) {
      yVAR_expstr [s_beg + s_offset + i] = x_finsub [i];
   }
   DEBUG_YVAR   printf ("   MODDED    = <<%s>>\n", yVAR_expstr);
   /*> s_offset += s_end;                                                             <*/
   /*> DEBUG_YVAR   printf ("   s_offset now %d\n", s_offset);                        <*/
   /*---(complete)-----------------------*/
   return 0;
}


/*  rc = 0 perfect match, neg = fail, pos = modified to match                 */
int        /*----: strings that allow numbers to be rounded ------------------*/
yVAR_round (
      const char *a_test,              /*  name of the test                   */
      const char *a_expect,            /*  expected result                    */
      const char *a_actual)            /*  actual result                      */
{
   /*---(locals)-----------+-----------+-*/
   int       i         = 0;            /* loop iterator -- characters         */
   int       rc        = 0;            /* generic return code                 */
   char      mods_str[20] = "";
   /*---(locals)--------+--------------+-*/
   char        rce      = -20;
   /*---(header)-------------------------*/
   rc = yVAR__save   (a_test, a_expect, a_actual);
   if (rc < 0)                                        return rc;
   /*---(quick shortcut check)----------------------------*/
   if (strcmp (yVAR_actstr, yVAR_expstr) == 0) {
      DEBUG_YVAR   printf ("   already equal, no mods required (shortcut)\n");
      return 0;
   }
   /*---(initial RE run)---------------------*/
   rc = yVAR__match  ();
   if (rc < 0)                                        return rc;
   /*---(process matches)--------------------*/
   while (rc == 0) {
      rc = yVAR__check ();
      if (rc < 0)               return rc;
      s_offset += s_end;
      rc = yVAR__match  ();
      if (rc < 0)               break;
      if (s_offset >= s_explen) break;
   }
   DEBUG_YVAR   printf ("done\n\n");
   regfree (&s_regex);
   /*---(finish)---------------------------------------*/
   for (i = 0; i < s_explen; ++i) {
      if (yVAR_expstr[i] != a_expect[i]) {
         ++s_nmods;
         yVAR_modstr[i] = yVAR_expstr[i];
         if (yVAR_expstr[i] <= ' ')  yVAR_modstr[i] = '*';
         if (yVAR_expstr[i] >  'z')  yVAR_modstr[i] = '*';
      }
   }
   snprintf (mods_str, 20, ">> (%1d) ", s_nmods);
   strncat  (yVAR_modstr, mods_str, 499);
   /*---(complete)-------------------------------------*/
   if (strcmp(yVAR_actstr, yVAR_expstr) == 0) return s_nmods;
   return -30;
}



/*====================------------------------------------====================*/
/*===----                           special                            ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIAL_________________o (void) {;}

char*      /*----: return the modified string mask ---------------------------*/
yVAR_modded        (void)
{
   return yVAR_modstr;
}

char*      /*----: return the modified expected ------------------------------*/
yVAR_expect        (void)
{
   return yVAR_expstr;
}

char*      /*----: return the modified actual --------------------------------*/
yVAR_actual        (void)
{
   return yVAR_actstr;
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
