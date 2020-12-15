/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"


char        s_scrp      = 0;
int         s_all       = 0;
int         s_good      = 0;
int         s_tall      = 0;
int         s_tgood     = 0;



/*====================------------------------------------====================*/
/*===----                       comparing results                      ----===*/
/*====================------------------------------------====================*/
static void      o___COMPARE_________________o (void) {;}

char
check_char              (int s, char *a_desc, char a_act, char a_exp)
{
   char        x_res       =  '-';
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   ++s_all;
   ++s_tall;
   if (a_act == a_exp) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_good;
      ++s_tgood;
   }
   printf ("%02d) %-40.40s  %c                    %c                    %c\n", s, a_desc, a_act, a_exp, x_res);
   printf ("  %s%02d) %-6.6s%s : %-40.40s\n", x_on, s, t, BACK_OFF, a_desc);
   printf ("      expect : %c\n", a_exp);
   printf ("      actual : %c\n", a_act);
   printf ("\n");
   return 0;
}

char
check_value             (int s, char *a_desc, int a_act, int a_exp)
{
   char        x_res       =  '-';
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   ++s_all;
   ++s_tall;
   if (a_act == a_exp) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_good;
      ++s_tgood;
   }
   if (a_act < 0 && a_exp == -999) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_good;
      ++s_tgood;
   }
   printf ("  %s%02d) %-6.6s%s : %-40.40s\n", x_on, s, t, BACK_OFF, a_desc);
   printf ("      expect : %d\n", a_exp);
   printf ("      actual : %d\n", a_act);
   printf ("\n");
   return 0;
}

char
check_string            (int s, char *a_desc, char *a_act, char *a_exp)
{
   char        x_res       =  '-';
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   ++s_all;
   ++s_tall;
   if (strcmp (a_act, a_exp) == 0) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
      x_res = 'Y';
      ++s_good;
      ++s_tgood;
   }
   printf ("  %s%02d) %-6.6s%s : %-40.40s\n", x_on, s, t, BACK_OFF, a_desc);
   printf ("      expect : %2d[%s]\n", strlen (a_exp), a_exp);
   printf ("      actual : %2d[%s]\n", strlen (a_act), a_act);
   printf ("\n");
   return 0;
}

char scrp  (char n, char *a_desc)
{
   char        t           [LEN_RECD]  = "";
   sprintf (t, "%s ==============================================================================", a_desc);
   printf ("SCRP [%02d] %70.70s\n", n, t);
   printf ("\n");
   return 0;
}

char focus  (char *a_desc)
{
   char        t           [LEN_RECD]  = "";
   sprintf (t, "  %s ----------------------------------------------------------------------------", a_desc);
   printf ("  FOCUS %72.72s\n", t);
   printf ("\n");
   return 0;
}

char
summ                    (void)
{
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   if (s_all == s_good) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
   }
   printf ("  %sPRCS  test %4d, pass %4d, fail %4d ========================================%s\n", x_on, s_all, s_good, s_all - s_good, BACK_OFF);
   printf ("\n\n");
   return 0;
}

char
tinu                    (void)
{
   char        t           [10] = "FAIL";
   char        x_on        [10] = BACK_RED;
   if (s_tall == s_tgood) {
      strcpy (t   , "PASS");
      strcpy (x_on, BACK_GRN);
   }
   printf ("%sTINU  test %4d, pass %4d, fail %4d ==========================================%s\n", x_on, s_tall, s_tgood, s_tall - s_tgood, BACK_OFF);
   printf ("\n\n");
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       unit test scripts                      ----===*/
/*====================------------------------------------====================*/
static void      o___SCRIPTS_________________o (void) {;}

char
yvar_script_string_prep (void)
{
   int         n           =    0;
   scrp (++s_scrp, "yvar_string_prep");
   focus ("simple defense and saving values");
   n = s_all = s_good = 0;
   check_value  (++n, "call string prep"                   , yvar_string_prep ("s_equal"   , "123456789-123456789-123456789-123456789-", "-987654321-987654321-987654321-987654321"), 0);
   check_string (++n, "... check test"                     , s_test                  , "s_equal"                                 );
   check_string (++n, "... check expect"                   , s_exp                   , "123456789-123456789-123456789-123456789-");
   check_string (++n, "... check actual"                   , s_act                   , "-987654321-987654321-987654321-987654321");
   check_string (++n, "... check expect for use"           , u_exp                   , "123456789-123456789-123456789-123456789-");
   check_string (++n, "... check actual for use"           , u_act                   , "-987654321-987654321-987654321-987654321");
   check_string (++n, "... check mod"                      , s_mod                   , "                                        ");
   check_value  (++n, "call string prep"                   , yvar_string_prep ("s_lesser"  , "test"                                    , "another"                                 ), 0);
   check_string (++n, "... check test"                     , s_test                  , "s_lesser"                                );
   check_string (++n, "... check expect"                   , s_exp                   , "test"                                    );
   check_string (++n, "... check actual"                   , s_act                   , "another"                                 );
   check_string (++n, "... check expect for use"           , u_exp                   , "test"                                    );
   check_string (++n, "... check actual for use"           , u_act                   , "another"                                 );
   check_string (++n, "... check mod"                      , s_mod                   , "       "                                 );
   check_value  (++n, "call with nulls"                    , yvar_string_prep (NULL        , "test"                                    , "another"                                 ), -1);
   check_value  (++n, "call with nulls"                    , yvar_string_prep ("s_round"   , NULL                                      , "another"                                 ), -2);
   check_value  (++n, "call with nulls"                    , yvar_string_prep ("s_round"   , "test"                                    , NULL                                      ), -3);
   summ ();
   focus ("verify mask transfer, trunc, extend");
   n = s_all = s_good = 0;
   check_value  (++n, "no masking"                         , yvar_string_prep ("s_equal"   , "chupacabras are a very creepy proto-human", "chupacabras are a very creepy proto-human"), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "chupacabras are a very creepy proto-human");
   check_string (++n, "... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   check_string (++n, "... check expect for use"           , u_exp                   , "chupacabras are a very creepy proto-human");
   check_string (++n, "... check actual for use"           , u_act                   , "chupacabras are a very creepy proto-human");
   check_string (++n, "... check mod"                      , s_mod                   , "                                         ");
   check_value  (++n, "... check length"                   , s_len                   , 41);
   check_value  (++n, "equal length, mask in middle"       , yvar_string_prep ("s_equal"   , "chupacabras are ¬¬¬¬¬¬¬¬¬¬¬¬¬ proto-human", "chupacabras are a very creepy proto-human"), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "chupacabras are ¬¬¬¬¬¬¬¬¬¬¬¬¬ proto-human");
   check_string (++n, "... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   check_string (++n, "... check expect for use"           , u_exp                   , "chupacabras are ¬¬¬¬¬¬¬¬¬¬¬¬¬ proto-human");
   check_string (++n, "... check actual for use"           , u_act                   , "chupacabras are ¬¬¬¬¬¬¬¬¬¬¬¬¬ proto-human");
   check_string (++n, "... check mod"                      , s_mod                   , "                                         ");
   check_value  (++n, "... check length"                   , s_len                   , 41);
   check_value  (++n, "actual longer, exp not tail masked" , yvar_string_prep ("s_equal"   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬b"            , "chupacabras are a very creepy proto-human"), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬b");
   check_string (++n, "... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   check_string (++n, "... check expect for use"           , u_exp                   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬b");
   check_string (++n, "... check actual for use"           , u_act                   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬y proto-human");
   check_string (++n, "... check mod"                      , s_mod                   , "                                         ");
   check_value  (++n, "... check length"                   , s_len                   , 41);
   check_value  (++n, "actual longer, exp tail masked"     , yvar_string_prep ("s_equal"   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬¬"            , "chupacabras are a very creepy proto-human"), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬¬");
   check_string (++n, "... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   check_string (++n, "... check expect for use"           , u_exp                   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬");
   check_string (++n, "... check actual for use"           , u_act                   , "chupacabras are a ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬");
   check_string (++n, "... check mod"                      , s_mod                   , "                                         ");
   check_value  (++n, "... check length"                   , s_len                   , 41);
   check_value  (++n, "expected longer, exp not tail mask" , yvar_string_prep ("s_equal"   , "chupacabras are a very ¬¬¬¬¬¬¬¬¬¬¬¬-human", "chupacabras are a proto-human"), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "chupacabras are a very ¬¬¬¬¬¬¬¬¬¬¬¬-human");
   check_string (++n, "... check actual"                   , s_act                   , "chupacabras are a proto-human");
   check_string (++n, "... check expect for use"           , u_exp                   , "chupacabras are a very ¬¬¬¬¬¬¬¬¬¬¬¬-human");
   check_string (++n, "... check actual for use"           , u_act                   , "chupacabras are a proto¬¬¬¬¬¬");
   check_string (++n, "... check mod"                      , s_mod                   , "                                         ");
   check_value  (++n, "... check length"                   , s_len                   , 41);
   check_value  (++n, "expected longer, exp tail masked"   , yvar_string_prep ("s_equal"   , "chupacabras are a very ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", "chupacabras are a proto-human"), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "chupacabras are a very ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬");
   check_string (++n, "... check actual"                   , s_act                   , "chupacabras are a proto-human");
   check_string (++n, "... check expect for use"           , u_exp                   , "chupacabras are a very ¬¬¬¬¬¬");
   check_string (++n, "... check actual for use"           , u_act                   , "chupacabras are a proto¬¬¬¬¬¬");
   check_string (++n, "... check mod"                      , s_mod                   , "                             ");
   check_value  (++n, "... check length"                   , s_len                   , 29);
   summ ();
   return 0;
}

char
yvar_script_string_equal (void)
{
   int         n           =    0;
   scrp (++s_scrp, "yVAR_string");
   focus ("verify unmasked comparisons");
   n = s_all = s_good = 0;
   check_value  (++n, "equal strings"                      , yVAR_string      ("s_equal"   , "testing123"                              , "testing123"                              ), 0);
   check_string (++n, "... check modded value"             , s_mod                   , "          "                              );
   check_string (++n, "... check fancy"                    , s_fancy                 , "testing123"                              );
   check_value  (++n, "expect longer"                      , yVAR_string      ("s_equal"   , "testing123456789-"                       , "testing123"                              ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "          <<<<<<<"                       );
   check_string (++n, "... check fancy"                    , s_fancy                 , "testing123" BOLD_RED "£££££££" BOLD_OFF);
   check_value  (++n, "actual longer"                      , yVAR_string      ("s_equal"   , "testing123"                              , "testing123abcd"                          ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "          >>>>"                          );
   check_string (++n, "... check fancy"                    , s_fancy                 , "testing123" BOLD_RED "abcd" BOLD_OFF);
   summ ();
   focus ("verify masked comparisons");
   n = s_all = s_good = 0;
   check_value  (++n, "equal strings, middle masked"       , yVAR_string      ("s_equal"   , "tes¬¬¬¬123"                              , "testing123"                              ), 0);
   check_string (++n, "... check modded value"             , s_mod                   , "   ¬¬¬¬   "                              );
   check_string (++n, "... check fancy"                    , s_fancy                 , "tes" BOLD_MAG "¬¬¬¬" BOLD_OFF "123");
   check_value  (++n, "expect longer"                      , yVAR_string      ("s_equal"   , "tes¬¬¬¬123456789-"                       , "testing123"                              ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "   ¬¬¬¬   <<<<<<<"                       );
   check_string (++n, "... check fancy"                    , s_fancy                 , "tes" BOLD_MAG "¬¬¬¬" BOLD_OFF "123" BOLD_RED "£££££££" BOLD_OFF);
   check_value  (++n, "actual longer"                      , yVAR_string      ("s_equal"   , "tes¬¬¬¬123"                              , "testing123abcd"                          ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "   ¬¬¬¬   >>>>"                          );
   check_string (++n, "... check fancy"                    , s_fancy                 , "tes" BOLD_MAG "¬¬¬¬" BOLD_OFF "123" BOLD_RED "abcd" BOLD_OFF);
   check_value  (++n, "actual longer, tail masked"         , yVAR_string      ("s_equal"   , "tes¬"                                    , "testing123abcd"                          ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "tes¬");
   check_string (++n, "... check actual"                   , s_act                   , "testing123abcd");
   check_string (++n, "... check expect for use"           , u_exp                   , "tes¬¬¬¬¬¬¬¬¬¬¬");
   check_string (++n, "... check actual for use"           , u_act                   , "tes¬¬¬¬¬¬¬¬¬¬¬");
   check_string (++n, "... check modded value"             , s_mod                   , "   ¬¬¬¬¬¬¬¬¬¬¬"                       );
   check_string (++n, "... check fancy"                    , s_fancy                 , "tes" BOLD_MAG "¬¬¬¬¬¬¬¬¬¬¬" BOLD_OFF);
   summ ();
   focus ("verify trouble marking");
   n = s_all = s_good = 0;
   check_value  (++n, "different strings"                  , yVAR_string      ("s_equal"   , "testing123"                              , "testingabs"                              ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "       xxx"                              );
   check_string (++n, "... check fancy"                    , s_fancy                 , "testing" BOLD_RED "abs" BOLD_OFF);
   check_value  (++n, "different strings"                  , yVAR_string      ("s_equal"   , "hosty"                                   , "testingabs"                              ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "xx  x>>>>>"                              );
   check_string (++n, "... check fancy"                    , s_fancy                 , BOLD_RED "te" BOLD_OFF "st" BOLD_RED "ingabs" BOLD_OFF);
   summ ();
   return 0;
}

char
yvar_script_round        (void)
{
   int         n           =    0;
   scrp (++s_scrp, "yVAR_round");
   focus ("verify non-numeric comparisons (same as s_equal");
   n = s_all = s_good = 0;
   check_value  (++n, "equal strings"                      , yVAR_round       ("u_round/1" , "testing123"                              , "testing123"                              ), 0);
   check_string (++n, "... check modded value"             , s_mod                   , "          "                              );
   check_value  (++n, "expect longer"                      , yVAR_round       ("u_round/1" , "testing123456789-"                       , "testing123"                              ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "          <<<<<<<"                       );
   check_value  (++n, "actual longer"                      , yVAR_round       ("u_round/1" , "testing123"                              , "testing123abcd"                          ), -10);
   check_string (++n, "... check modded value"             , s_mod                   , "          >>>>"                          );
   summ ();
   focus ("simple numbers");
   n = s_all = s_good = 0;
   check_value  (++n, "outside low"                        , yVAR_round       ("u_round/1" , "   -2      "                               , "    0      "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "   -2      ");
   check_string (++n, "... check actual"                   , s_act                   , "    0      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "   -2      ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0      ");
   check_string (++n, "... check modded value"             , s_mod                   , "   xx      ");
   check_value  (++n, "lowest match"                       , yVAR_round       ("u_round/1" , "   -1      "                               , "    0      "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "   -1      ");
   check_string (++n, "... check actual"                   , s_act                   , "    0      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    0      ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0      ");
   check_string (++n, "... check modded value"             , s_mod                   , "   rr      ");
   check_value  (++n, "exact match"                        , yVAR_round       ("u_round/1" , "    0      "                               , "    0      "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "    0      ");
   check_string (++n, "... check actual"                   , s_act                   , "    0      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    0      ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0      ");
   check_string (++n, "... check modded value"             , s_mod                   , "           "                             );
   check_value  (++n, "highest match"                      , yVAR_round       ("u_round/1" , "    1      "                               , "    0      "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "    1      ");
   check_string (++n, "... check actual"                   , s_act                   , "    0      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    0      ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0      ");
   check_string (++n, "... check modded value"             , s_mod                   , "    r      ");
   check_value  (++n, "outside high"                       , yVAR_round       ("u_round/1" , "    2      "                               , "    0      "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "    2      ");
   check_string (++n, "... check actual"                   , s_act                   , "    0      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    2      ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0      ");
   check_string (++n, "... check modded value"             , s_mod                   , "    x      ");
   check_value  (++n, "negative"                           , yVAR_round       ("u_round/1" , "   -0      "                               , "    0      "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "   -0      ");
   check_string (++n, "... check actual"                   , s_act                   , "    0      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    0      ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0      ");
   check_string (++n, "... check modded value"             , s_mod                   , "   r       ");
   summ ();
   focus ("multi-digit integer");
   n = s_all = s_good = 0;
   check_value  (++n, "outside low"                        , yVAR_round       ("u_round/3" , "  325      "                               , "  321      "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "  325      ");
   check_string (++n, "... check actual"                   , s_act                   , "  321      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "  325      ");
   check_string (++n, "... check actual for use"           , u_act                   , "  321      ");
   check_string (++n, "... check modded value"             , s_mod                   , "    x      ");
   check_value  (++n, "lowest match"                       , yVAR_round       ("u_round/3" , "  325      "                               , "  322      "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "  325      ");
   check_string (++n, "... check actual"                   , s_act                   , "  322      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "  322      ");
   check_string (++n, "... check actual for use"           , u_act                   , "  322      ");
   check_string (++n, "... check modded value"             , s_mod                   , "    r      ");
   check_value  (++n, "exact match"                        , yVAR_round       ("u_round/3" , "  325      "                               , "  325      "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "  325      ");
   check_string (++n, "... check actual"                   , s_act                   , "  325      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "  325      ");
   check_string (++n, "... check actual for use"           , u_act                   , "  325      ");
   check_string (++n, "... check modded value"             , s_mod                   , "           "                             );
   check_value  (++n, "highest match"                      , yVAR_round       ("u_round/3" , "  325      "                               , "  328      "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "  325      ");
   check_string (++n, "... check actual"                   , s_act                   , "  328      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "  328      ");
   check_string (++n, "... check actual for use"           , u_act                   , "  328      ");
   check_string (++n, "... check modded value"             , s_mod                   , "    r      ");
   check_value  (++n, "outside high"                       , yVAR_round       ("u_round/3" , "  325      "                               , "  329      "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "  325      ");
   check_string (++n, "... check actual"                   , s_act                   , "  329      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "  325      ");
   check_string (++n, "... check actual for use"           , u_act                   , "  329      ");
   check_string (++n, "... check modded value"             , s_mod                   , "    x      ");
   check_value  (++n, "negative"                           , yVAR_round       ("u_round/3" , "  325      "                               , " -325      "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "  325      ");
   check_string (++n, "... check actual"                   , s_act                   , " -325      ");
   check_string (++n, "... check expect for use"           , u_exp                   , "  325      ");
   check_string (++n, "... check actual for use"           , u_act                   , " -325      ");
   check_string (++n, "... check modded value"             , s_mod                   , " x         ");
   summ ();
   focus ("small decimal");            
   n = s_all = s_good = 0;
   check_value  (++n, "outside low"                        , yVAR_round       ("u_round/4" , "    1.3    "                               , "    0.8    "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "    1.3    ");
   check_string (++n, "... check actual"                   , s_act                   , "    0.8    ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    1.3    ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0.8    ");
   check_string (++n, "... check modded value"             , s_mod                   , "    x x    ");
   check_value  (++n, "lowest match"                       , yVAR_round       ("u_round/4" , "    1.3    "                               , "    0.9    "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "    1.3    ");
   check_string (++n, "... check actual"                   , s_act                   , "    0.9    ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    0.9    ");
   check_string (++n, "... check actual for use"           , u_act                   , "    0.9    ");
   check_string (++n, "... check modded value"             , s_mod                   , "    r r    ");
   check_value  (++n, "exact match"                        , yVAR_round       ("u_round/4" , "    1.3    "                               , "    1.3    "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "    1.3    ");
   check_string (++n, "... check actual"                   , s_act                   , "    1.3    ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    1.3    ");
   check_string (++n, "... check actual for use"           , u_act                   , "    1.3    ");
   check_string (++n, "... check modded value"             , s_mod                   , "           "                             );
   check_value  (++n, "highest match"                      , yVAR_round       ("u_round/4" , "    1.3    "                               , "    1.7    "                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "    1.3    ");
   check_string (++n, "... check actual"                   , s_act                   , "    1.7    ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    1.7    ");
   check_string (++n, "... check actual for use"           , u_act                   , "    1.7    ");
   check_string (++n, "... check modded value"             , s_mod                   , "      r    ");
   check_value  (++n, "outside high"                       , yVAR_round       ("u_round/4" , "    1.3    "                               , "    1.8    "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "    1.3    ");
   check_string (++n, "... check actual"                   , s_act                   , "    1.8    ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    1.3    ");
   check_string (++n, "... check actual for use"           , u_act                   , "    1.8    ");
   check_string (++n, "... check modded value"             , s_mod                   , "      x    ");
   check_value  (++n, "negative"                           , yVAR_round       ("u_round/4" , "    1.3    "                               , "   -1.3    "                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "    1.3    ");
   check_string (++n, "... check actual"                   , s_act                   , "   -1.3    ");
   check_string (++n, "... check expect for use"           , u_exp                   , "    1.3    ");
   check_string (++n, "... check actual for use"           , u_act                   , "   -1.3    ");
   check_string (++n, "... check modded value"             , s_mod                   , "   x       ");
   summ ();
   focus ("larger negative decimal");  
   n = s_all = s_good = 0;
   check_value  (++n, "outside low"                        , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12151"                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "   -3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "   -3.12151");
   check_string (++n, "... check expect for use"           , u_exp                   , "   -3.12159");
   check_string (++n, "... check actual for use"           , u_act                   , "   -3.12151");
   check_string (++n, "... check modded value"             , s_mod                   , "          x");
   check_value  (++n, "lowest match"                       , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12152"                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "   -3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "   -3.12152");
   check_string (++n, "... check expect for use"           , u_exp                   , "   -3.12152");
   check_string (++n, "... check actual for use"           , u_act                   , "   -3.12152");
   check_string (++n, "... check modded value"             , s_mod                   , "          r");
   check_value  (++n, "exact match"                        , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12159"                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "   -3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "   -3.12159");
   check_string (++n, "... check expect for use"           , u_exp                   , "   -3.12159");
   check_string (++n, "... check actual for use"           , u_act                   , "   -3.12159");
   check_string (++n, "... check modded value"             , s_mod                   , "           "                             );
   check_value  (++n, "highest match"                      , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12166"                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "   -3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "   -3.12166");
   check_string (++n, "... check expect for use"           , u_exp                   , "   -3.12166");
   check_string (++n, "... check actual for use"           , u_act                   , "   -3.12166");
   check_string (++n, "... check modded value"             , s_mod                   , "         rr");
   check_value  (++n, "outside high"                       , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12167"                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "   -3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "   -3.12167");
   check_string (++n, "... check expect for use"           , u_exp                   , "   -3.12159");
   check_string (++n, "... check actual for use"           , u_act                   , "   -3.12167");
   check_string (++n, "... check modded value"             , s_mod                   , "         xx");
   check_value  (++n, "negative"                           , yVAR_round       ("u_round/7" , "   -3.12159"                               , "    3.12159"                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "   -3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "    3.12159");
   check_string (++n, "... check expect for use"           , u_exp                   , "   -3.12159");
   check_string (++n, "... check actual for use"           , u_act                   , "    3.12159");
   check_string (++n, "... check modded value"             , s_mod                   , "   x       ");
   summ ();
   focus ("multiple numbers");               
   n = s_all = s_good = 0;
   check_value  (++n, "exact match"                        , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "pi=-3.12159"                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "pi=-3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "pi=-3.12159");
   check_string (++n, "... check expect for use"           , u_exp                   , "pi=-3.12159");
   check_string (++n, "... check actual for use"           , u_act                   , "pi=-3.12159");
   check_string (++n, "... check modded value"             , s_mod                   , "           "                             );
   check_value  (++n, "other match"                        , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "pi=-3.12166"                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "pi=-3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "pi=-3.12166");
   check_string (++n, "... check expect for use"           , u_exp                   , "pi=-3.12166");
   check_string (++n, "... check actual for use"           , u_act                   , "pi=-3.12166");
   check_string (++n, "... check modded value"             , s_mod                   , "         rr");
   check_value  (++n, "bad-text, but number match"         , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "PI/-3.12166"                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "pi=-3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "PI/-3.12166");
   check_string (++n, "... check expect for use"           , u_exp                   , "pi=-3.12166");
   check_string (++n, "... check actual for use"           , u_act                   , "PI/-3.12166");
   check_string (++n, "... check modded value"             , s_mod                   , "xxx      rr");
   check_value  (++n, "non-match"                          , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "pi=-3.12167"                             ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "pi=-3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "pi=-3.12167");
   check_string (++n, "... check expect for use"           , u_exp                   , "pi=-3.12159");
   check_string (++n, "... check actual for use"           , u_act                   , "pi=-3.12167");
   check_string (++n, "... check modded value"             , s_mod                   , "         xx");
   summ ();
   focus ("funky cases");
   check_value  (++n, "positive marker"                    , yVAR_round       ("u_round/7" , "pi=+3.12159"                               , "pi=+3.12166"                             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "pi=+3.12159");
   check_string (++n, "... check actual"                   , s_act                   , "pi=+3.12166");
   check_string (++n, "... check expect for use"           , u_exp                   , "pi=+3.12166");
   check_string (++n, "... check actual for use"           , u_act                   , "pi=+3.12166");
   check_string (++n, "... check modded value"             , s_mod                   , "         rr");
   check_value  (++n, "embedded number, no leading space"  , yVAR_round       ("u_round/1" , "test3 more"                                , "test2 more"                              ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "test3 more" );
   check_string (++n, "... check actual"                   , s_act                   , "test2 more" );
   check_string (++n, "... check expect for use"           , u_exp                   , "test3 more" );
   check_string (++n, "... check actual for use"           , u_act                   , "test2 more" );
   check_string (++n, "... check modded value"             , s_mod                   , "    x     " );
   check_value  (++n, "embedded number, no proper lead"    , yVAR_round       ("u_round/1" , "a=5"                                       , "a=4"                                     ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "a=5"        );
   check_string (++n, "... check actual"                   , s_act                   , "a=4"        );
   check_string (++n, "... check expect for use"           , u_exp                   , "a=5"        );
   check_string (++n, "... check actual for use"           , u_act                   , "a=4"        );
   check_string (++n, "... check modded value"             , s_mod                   , "  x"        );
   check_value  (++n, "multiple numbers, success"          , yVAR_round       ("u_round/7" , "pi=-3.12159, rads= 352, a 5"               , "pi=-3.12166, rads= 350, a 9"             ), 0);
   check_string (++n, "... check expect"                   , s_exp                   , "pi=-3.12159, rads= 352, a 5");
   check_string (++n, "... check actual"                   , s_act                   , "pi=-3.12166, rads= 350, a 9");
   check_string (++n, "... check expect for use"           , u_exp                   , "pi=-3.12166, rads= 350, a 9");
   check_string (++n, "... check actual for use"           , u_act                   , "pi=-3.12166, rads= 350, a 9");
   check_string (++n, "... check modded value"             , s_mod                   , "         rr          r    r");
   check_string (++n, "... check fancy value"              , s_fancy                 , "pi=-3.121" BOLD_YEL "66" FORE_OFF ", rads= 35" BOLD_YEL "0" FORE_OFF ", a " BOLD_YEL "9" FORE_OFF);
   check_value  (++n, "multiple numbers, text trouble"     , yVAR_round       ("u_round/7" , "PI=-3.12159, radn= 352, a 5 ¬¬¬¬¬¬¬¬"     , "pi=-3.12166, rads= 350, a 9 heidi 10"    ), -999);
   check_string (++n, "... check expect"                   , s_exp                   , "PI=-3.12159, radn= 352, a 5 ¬¬¬¬¬¬¬¬");
   check_string (++n, "... check actual"                   , s_act                   , "pi=-3.12166, rads= 350, a 9 heidi 10");
   check_string (++n, "... check expect for use"           , u_exp                   , "PI=-3.12166, radn= 350, a 9 ¬¬¬¬¬¬¬¬");
   check_string (++n, "... check actual for use"           , u_act                   , "pi=-3.12166, rads= 350, a 9 ¬¬¬¬¬¬¬¬");
   check_string (++n, "... check modded value"             , s_mod                   , "xx       rr     x    r    r ¬¬¬¬¬¬¬¬");
   check_string (++n, "... check fancy value"              , s_fancy                 , BOLD_RED "pi" FORE_OFF "=-3.121" BOLD_YEL "66" FORE_OFF ", rad" BOLD_RED "s" FORE_OFF "= 35" BOLD_YEL "0" FORE_OFF ", a " BOLD_YEL "9" FORE_OFF " " BOLD_MAG "¬¬¬¬¬¬¬¬" FORE_OFF);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                            driver                            ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
main (void)
{
   s_scrp = 0;
   yvar_script_string_prep  ();
   yvar_script_string_equal ();
   yvar_script_round        ();
   tinu ();
   return 0;
}



