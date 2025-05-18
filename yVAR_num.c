/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"

char      yVAR_expstr   [500];
char      yVAR_actstr   [500];
char      yVAR_modstr   [500];


/*
 * options are...
 *    1) i_equal        = : actual   == expected
 *    2) i_not          ! : actual   != expected
 *    3) i_greater      > : actual   >  expected
 *    4) i_lesser       < : actual   <  expected
 *    5) i_gtequal      Þ : actual   >= expected
 *    6) i_ltequal      Ý : actual   <= expected
 *    7) i_digits       9 : actual contains expected number of digits
 *    8) i_exists       å : actual not null/empty/zero
 *    9) i_pct/?        % : actual matches expected +/- a percent
 *   10) i_round/?      r : rounded in ones place
 *   11) i_PASS         p : greater than or equal to zero
 *   12) i_FAIL         f : less than zero
 *
 * it is expected that 90% is i_equal and i_lesser
 */


char
yVAR_char               (char a_test [LEN_TERSE], uchar a_expect, uchar a_actual)
{
   /*---(design notes)--------------------------------------------------------#
    * use longs to have maximum flexibility for char, short, int, and long
    * can not use long long as atoll is a C99 thing only
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char        t           [LEN_RECD] = "";
   float       a           =  0.0;
   /*---(defenses)-----------------------*/
   --rce;  if (a_test     == NULL) return rce;
   /*---(normal tests)-------------------*/
   if        (strcmp(a_test, "c_equal")    == 0) {
      rc = -('e');
      if (a_actual == a_expect)    rc *= -1;
   } else if (strcmp(a_test, "c_not"    )      == 0) {
      rc = -('n');
      if (a_actual != a_expect)    rc *= -1;
   } else if (strcmp(a_test, "c_greater")  == 0) {
      rc = -('g');
      if (a_actual >  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "c_gequal" )  == 0) {
      rc = -('G');
      if (a_actual >= a_expect)    rc *= -1;
   } else if (strcmp(a_test, "c_lesser" )   == 0) {
      rc = -('l');
      if (a_actual <  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "c_lequal" )  == 0) {
      rc = -('L');
      if (a_actual <= a_expect)    rc *= -1;
   } else if (strcmp(a_test, "c_any"    )  == 0) {
      rc = 'a';
   }
   /*---(inclusion - common)-------------*/
   else if   (strcmp(a_test, "c_number" )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_NUMBER, a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_lower"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_LOWER , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_upper"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_UPPER , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_greek"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_GREEK , a_actual) != NULL)    rc *= -1;
   }
   /*---(inclusion - lesser)-------------*/
   else if   (strcmp(a_test, "c_alpha"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_ALPHA , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_alnum"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_ALNUM , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_write"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_WRITE , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_extend" )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_EXTEN , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_files"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_FILES , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_control")  == 0) {
      if (a_actual >= 0 && a_actual <= 31)           rc *= -1;
      if (a_actual == 127)                           rc *= -1;
   } else if (strcmp(a_test, "c_core"   )  == 0) {
      if (a_actual >= 32 && a_actual <= 126)         rc *= -1;
   } else if (strcmp(a_test, "c_print"  )   == 0) {
      if (a_actual >= 32  && a_actual <= 126)        rc *= -1;
      if (a_actual >= 161 && a_actual <= 255)        rc *= -1;
   }
   /*---(inclusion -- numeric)-----------*/
   else if   (strcmp(a_test, "c_binary" )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_BINPLUS, a_actual) != NULL)   rc *= -1;
   } else if (strcmp(a_test, "c_octal"  )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_OCTAL , a_actual) != NULL)    rc *= -1;
   } else if (strcmp(a_test, "c_hex"    )   == 0) {
      if (a_actual == 0)                             rc *= -1;
      if (strchr (YSTR_HEXUP , a_actual) != NULL)    rc *= -1;
   }
   /*---(bad test)-----------------------*/
   else {
      rc = '¢';
   }
   /*---(complete)-----------------------*/
   return rc;
}

char yVAR_chars   (char a_test [LEN_TERSE], uchar a_actual) { return yVAR_char (a_test, 0, a_actual); }

char
yVAR_integer            (char a_test [LEN_TERSE], llong a_expect, llong a_actual)
{
   /*---(design notes)--------------------------------------------------------#
    * use longs to have maximum flexibility for char, short, int, and long
    * can not use long long as atoll is a C99 thing only
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -0;
   char        x_act       [LEN_LABEL] = "";
   char        x_exp       [LEN_LABEL] = "";
   float       a           =  0.0;
   char        n           =    0;
   ldouble     x_lo        =  0.0;
   ldouble     x_hi        =  0.0;
   float       x_nudge     =  0.001;
   /*---(defenses)-----------------------*/
   --rce;  if (a_test     == NULL) return rce;
   /*---(normal tests)-------------------*/
   if        (strcmp(a_test, "i_equal")    == 0) {
      rc = -('e');
      if (a_actual == a_expect)    rc *= -1;
   } else if (strcmp(a_test, "i_not")      == 0) {
      rc = -('n');
      if (a_actual != a_expect)    rc *= -1;
   } else if (strcmp(a_test, "i_greater")  == 0) {
      rc = -('g');
      if (a_actual >  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "i_gequal" )  == 0) {
      rc = -('G');
      if (a_actual >= a_expect)    rc *= -1;
   } else if (strcmp(a_test, "i_lesser")   == 0) {
      rc = -('l');
      if (a_actual <  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "i_lequal" )  == 0) {
      rc = -('L');
      if (a_actual <= a_expect)    rc *= -1;
   } else if (strcmp(a_test, "i_any"    )  == 0) {
      rc = 'a';
   }
   /*---(specialty tests)----------------*/
   else if   (strcmp(a_test, "i_digits")   == 0) {
      rc = -('d');
      snprintf (x_act, LEN_LABEL, "%ld", a_actual);
      if (strlen (x_act) == a_expect)   rc *= -1;
   } else if (strcmp(a_test, "i_zero"  )   == 0) {
      rc = -('z');
      if (a_actual == 0)           rc *= -1;
   } else if (strcmp(a_test, "i_exists")   == 0) {
      rc = -('x');
      if (a_actual != 0)           rc *= -1;
   }
   /*---(poximity tests)-----------------*/
   else if   (strlen (a_test) == 7 && strncmp (a_test, "i_pct/", 6) == 0) {
      rc = 'p';
      if (strchr ("0123456789", a_test [6]) == NULL)  return -rc;
      a = ((float) (a_test [6] - '0') * 1000.0) / 100000.00;
      x_lo = a_expect * (1.00 - a);
      x_hi = a_expect * (1.00 + a);
      if ((ldouble) a_actual + x_nudge < x_lo)    return rc *= -1;
      if ((ldouble) a_actual - x_nudge > x_hi)    return rc *= -1;
   }
   else if   (strlen (a_test) == 7 && strncmp (a_test, "i_sig/"  , 6) == 0) {
      rc = -('r');
      if (strchr ("123456789", a_test [6]) == NULL)  return rc;
      a = a_test [6] - '0';
      snprintf (x_act, LEN_LABEL, "%ld", a_actual);
      snprintf (x_exp, LEN_LABEL, "%ld", a_expect);
      if      (x_act [0] == '-' && x_exp [0] == '-')  n = 1;
      else if (x_act [0] != '-' && x_exp [0] != '-')  n = 0;
      else   return  rc;
      if (strlen (x_act) == strlen (x_exp)) {
         if (strncmp (x_act + n, x_exp + n, a) == 0)   return rc *= -1;
      }
   }
   else if   (strlen (a_test) == 9 && strncmp (a_test, "i_round/", 8) == 0) {
      rc = 'r';
      if (strchr ("0123456789", a_test [8]) == NULL)  return -rc;
      a = a_test [8] - '0';
      if (a_actual < a_expect - a)    return rc *= -1;
      if (a_actual > a_expect + a)    return rc *= -1;
   }
   /*---(return code tests)--------------*/
   else if   (strcmp(a_test, "i_pass" )     == 0) {
      rc = -('p');
      if (a_actual >= 0)           rc *= -1;
   } else if (strcmp(a_test, "i_fail" )     == 0) {
      rc = -('f');
      if (a_actual <  0)           rc *= -1;
   }
   /*---(bad test)-----------------------*/
   else {
      rc = '¢';
   }
   /*---(complete)-----------------------*/
   return rc;
}

char yVAR_ints    (char a_test [LEN_TERSE], llong a_actual) { return yVAR_integer (a_test, 0, a_actual); }

char       /*----: standard pointer testing for yUNIT ------------------------*/
yVAR_pointer       (char a_test [LEN_TERSE], void *a_expect, void *a_actual)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(defenses)-----------------------*/
   --rce;  if (a_test     == NULL) return rce;
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
   /*---(normal tests)-------------------*/
   if        (strcmp(a_test, "p_equal")    == 0) {
      rc = -('e');
      if (a_actual == a_expect)    rc *= -1;
   } else if (strcmp(a_test, "p_not")      == 0) {
      rc = -('e');
      if      (a_actual == NULL)        ;
      else if (a_expect == NULL)        ;
      else if (a_actual != a_expect)    rc *= -1;
   } else if (strcmp(a_test, "p_greater")  == 0) {
      rc = -('g');
      if (a_actual >  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "p_lesser")   == 0) {
      rc = -('l');
      if (a_actual <  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "p_null")     == 0) {
      rc = -('n');
      if (a_actual == 0       )    rc *= -1;
   } else if (strcmp(a_test, "p_exists")   == 0) {
      rc = -('x');
      if (a_actual != 0       )    rc *= -1;
   } else if (strcmp(a_test, "p_any")      == 0) {
      rc = 'a';
   }
   /*---(bad test)-----------------------*/
   else {
      rc = '¢';
   }
   /*---(complete)-----------------------*/
   return rc;
}

char
yVAR_real               (char a_test [LEN_TERSE], ldouble a_expect, ldouble a_actual)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_act       [LEN_TITLE] = "";
   char        x_exp       [LEN_TITLE] = "";
   float       a           =  0.0;
   ldouble     x_lo        =  0.0;
   ldouble     x_hi        =  0.0;
   float       x_nudge     =  0.001;
   /*---(defenses)-----------------------*/
   --rce;  if (a_test     == NULL) return rce;
   /*---(basic)--------------------------*/
   if  (strcmp(a_test, "r_equal")    == 0) {
      rc = -('e');
      if (a_actual == a_expect)    rc *= -1;
   } else if (strcmp(a_test, "r_not")      == 0) {
      rc = -('n');
      if (a_actual != a_expect)    rc *= -1;
   } else if (strcmp(a_test, "r_greater")  == 0) {
      rc = -('g');
      if (a_actual >  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "r_gequal" )  == 0) {
      rc = -('G');
      if (a_actual >= a_expect)    rc *= -1;
   } else if (strcmp(a_test, "r_lesser" )  == 0) {
      rc = -('l');
      if (a_actual <  a_expect)    rc *= -1;
   } else if (strcmp(a_test, "r_lequal" )  == 0) {
      rc = -('L');
      if (a_actual <= a_expect)    rc *= -1;
   }
   /*---(tproximity)---------------------*/
   else if   (strlen (a_test) == 7 && strncmp (a_test, "r_pct/", 6) == 0) {
      rc = 'p';
      if (strchr ("0123456789", a_test [6]) == NULL)  return -rc;
      a = ((float) (a_test [6] - '0') * 1000.0) / 100000.00;
      x_lo = a_expect * (1.00 - a);
      x_hi = a_expect * (1.00 + a);
      if (a_actual + x_nudge < x_lo)    return rc *= -1;
      if (a_actual - x_nudge > x_hi)    return rc *= -1;
   }
   /*---(truncated)----------------------*/
   else if   (strcmp(a_test, "r_norm93")   == 0) {
      rc = -('s');
      snprintf (x_exp, LEN_TITLE, "%9.3llf", a_expect);
      snprintf (x_act, LEN_TITLE, "%9.3llf", a_actual);
      /*> printf ("x_exp = å%sæ\n", x_exp);                                           <*/
      /*> printf ("x_act = å%sæ\n", x_act);                                           <*/
      if (strcmp (x_exp, x_act) == 0)    rc *= -1;
   } else if (strcmp (a_test, "r_norm97")  == 0) {
      rc = -('s');
      snprintf (x_exp, LEN_TITLE, "%9.7llf", a_expect);
      snprintf (x_act, LEN_TITLE, "%9.7llf", a_actual);
      if (strcmp (x_exp, x_act) == 0)    rc *= -1;
   }
   /*---(bad test)-----------------------*/
   else {
      rc = '¢';
   }
   /*---(complete)-----------------------*/
   return rc;
}


