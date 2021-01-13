/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"

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
    * it is expected that 85% of calls will be s_equal, 10% s_not, then the rest
    */


char
yVAR_integer            (char *a_test, llong a_expect, llong a_actual)
{
   /*---(design notes)--------------------------------------------------------#
    * use longs to have maximum flexibility for char, short, int, and long
    * can not use long long as atoll is a C99 thing only
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD] = "";
   float       a           =  0.0;
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
   }
   /*---(specialty tests)----------------*/
   else if   (strcmp(a_test, "i_digits")   == 0) {
      rc = -('d');
      snprintf (t, LEN_RECD, "%ld", a_actual);
      if (strlen (t) == a_expect)   rc *= -1;
   } else if (strcmp(a_test, "i_zero"  )   == 0) {
      rc = -('z');
      if (a_actual == 0)           rc *= -1;
   } else if (strcmp(a_test, "i_exists")   == 0) {
      rc = -('x');
      if (a_actual != 0)           rc *= -1;
   }
   /*---(poximity tests)-----------------*/
   else if   (strlen (a_test) == 7 && strncmp (a_test, "i_pct/", 6) == 0) {
      rc = -('p');
      if (strchr ("123456789", a_test [6]) == NULL)  return -('P');
      a = (float) (a_test [6] - '0') / 100.0;
      if (a_actual < a_expect * (1.00 - a))    return rc *= -1;
      if (a_actual > a_expect * (1.00 + a))    return rc *= -1;
   }
   else if   (strlen (a_test) == 9 && strncmp (a_test, "i_round/", 8) == 0) {
      rc = -('r');
      if (strchr ("123456789", a_test [8]) == NULL)  return -('R');
      a = a_test [8] - '0';
      if (a_actual < a_expect - a)    return rc *= -1;
      if (a_actual > a_expect + a)    return rc *= -1;
   }
   /*---(return code tests)--------------*/
   else if   (strcmp(a_test, "i_pass" )     == 0) {
      rc = -('G');
      if (a_actual >= 0)           rc *= -1;
   } else if (strcmp(a_test, "i_fail" )     == 0) {
      rc = -('B');
      if (a_actual <  0)           rc *= -1;
   }
   /*---(bad test)-----------------------*/
   else {
      rc = '¢';
   }
   /*---(complete)-----------------------*/
   return rc;
}

char       /*----: standard pointer testing for yUNIT ------------------------*/
yVAR_pointer       (char *a_test, void *a_expect, void *a_actual)
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
      if (a_actual != a_expect)    rc *= -1;
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


char               /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_real (        /*  PURPOSE = STANDARD REAL NUM TESTING (for yUNIT+)       */
      char     *a_test,          /*  name of the test                         */
      double    a_expect,        /*  expected result                          */
      double    a_actual)        /*  actual result                            */
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD] = "";
   float       a           =  0.0;
   /*---(defenses)-----------------------*/
   --rce;  if (a_test     == NULL) return rce;
   /*---(design notes)--------------------------------------------------------#
    * use longs to have maximum flexibility for char, short, int, and long
    * can not use long long as atoll is a C99 thing only
    */
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
   } else if (strcmp(a_test, "r_norm93")       == 0) {
      rc = -('s');
      snprintf (yVAR_expstr, 15, "%9.3lf", a_expect);
      snprintf (yVAR_actstr, 15, "%9.3lf", a_actual);
      if (strcmp(yVAR_expstr, yVAR_actstr) == 0)    rc *= -1;
   } else {
      rc = '¢';
   }
   return rc;
}


