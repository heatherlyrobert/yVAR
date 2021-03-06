/*===[[ START ]]==============================================================*/
#include    "yVAR.h"
#include    "yVAR_priv.h"

#include    <yUNIT_solo.h>



/*====================------------------------------------====================*/
/*===----                       unit test scripts                      ----===*/
/*====================------------------------------------====================*/
static void      o___SCRIPTS_________________o (void) {;}

char
yvar_script_string_prep (void)
{
   yUNIT_minscrp ("yvar_string_prep");

   yUNIT_mincond ("simple defense and saving values");
   yUNIT_minval  ("call string prep"                   , yvar_string_prep ("s_equal"   , "123456789-123456789-123456789-123456789-", "-987654321-987654321-987654321-987654321"), 0);
   yUNIT_minstr  ("... check test"                     , s_test                  , "s_equal"                                 );
   yUNIT_minstr  ("... check expect"                   , s_exp                   , "123456789-123456789-123456789-123456789-");
   yUNIT_minstr  ("... check actual"                   , s_act                   , "-987654321-987654321-987654321-987654321");
   yUNIT_minstr  ("... check expect for use"           , u_exp                   , "123456789-123456789-123456789-123456789-");
   yUNIT_minstr  ("... check actual for use"           , u_act                   , "-987654321-987654321-987654321-987654321");
   yUNIT_minstr  ("... check mod"                      , s_mod                   , "                                        ");
   yUNIT_minval  ("call string prep"                   , yvar_string_prep ("s_lesser"  , "test"                                    , "another"                                 ), 0);
   yUNIT_minstr  ("... check test"                     , s_test                  , "s_lesser"                                );
   yUNIT_minstr  ("... check expect"                   , s_exp                   , "test"                                    );
   yUNIT_minstr  ("... check actual"                   , s_act                   , "another"                                 );
   yUNIT_minstr  ("... check expect for use"           , u_exp                   , "test"                                    );
   yUNIT_minstr  ("... check actual for use"           , u_act                   , "another"                                 );
   yUNIT_minstr  ("... check mod"                      , s_mod                   , "       "                                 );
   yUNIT_minval  ("call with nulls"                    , yvar_string_prep (NULL        , "test"                                    , "another"                                 ), -1);
   yUNIT_minval  ("call with nulls"                    , yvar_string_prep ("s_round"   , NULL                                      , "another"                                 ), -2);
   yUNIT_minval  ("call with nulls"                    , yvar_string_prep ("s_round"   , "test"                                    , NULL                                      ), -3);
   yUNIT_minval  ("call with bad test"                 , yvar_string_prep ("s_honk"    , "test"                                    , NULL                                      ), -999);
   yUNIT_minval  ("call with bad test"                 , yvar_string_prep ("S_EQUAL"   , "test"                                    , NULL                                      ), -999);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify mask transfer, trunc, extend");
   yUNIT_minval ("no masking"                         , yvar_string_prep ("s_equal"   , "chupacabras are a very creepy proto-human", "chupacabras are a very creepy proto-human"), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "chupacabras are a very creepy proto-human");
   yUNIT_minstr ("... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "chupacabras are a very creepy proto-human");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "chupacabras are a very creepy proto-human");
   yUNIT_minstr ("... check mod"                      , s_mod                   , "                                         ");
   yUNIT_minval ("... check length"                   , s_len                   , 41);
   yUNIT_minval ("equal length, mask in middle"       , yvar_string_prep ("s_equal"   , "chupacabras are ������������� proto-human", "chupacabras are a very creepy proto-human"), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "chupacabras are ������������� proto-human");
   yUNIT_minstr ("... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "chupacabras are ������������� proto-human");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "chupacabras are ������������� proto-human");
   yUNIT_minstr ("... check mod"                      , s_mod                   , "                                         ");
   yUNIT_minval ("... check length"                   , s_len                   , 41);
   yUNIT_minval ("actual longer, exp not tail masked" , yvar_string_prep ("s_equal"   , "chupacabras are a ����������b"            , "chupacabras are a very creepy proto-human"), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "chupacabras are a ����������b");
   yUNIT_minstr ("... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "chupacabras are a ����������b");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "chupacabras are a ����������y proto-human");
   yUNIT_minstr ("... check mod"                      , s_mod                   , "                                         ");
   yUNIT_minval ("... check length"                   , s_len                   , 41);
   yUNIT_minval ("actual longer, exp tail masked"     , yvar_string_prep ("s_equal"   , "chupacabras are a �����������"            , "chupacabras are a very creepy proto-human"), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "chupacabras are a �����������");
   yUNIT_minstr ("... check actual"                   , s_act                   , "chupacabras are a very creepy proto-human");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "chupacabras are a �����������������������");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "chupacabras are a �����������������������");
   yUNIT_minstr ("... check mod"                      , s_mod                   , "                                         ");
   yUNIT_minval ("... check length"                   , s_len                   , 41);
   yUNIT_minval ("expected longer, exp not tail mask" , yvar_string_prep ("s_equal"   , "chupacabras are a very ������������-human", "chupacabras are a proto-human"), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "chupacabras are a very ������������-human");
   yUNIT_minstr ("... check actual"                   , s_act                   , "chupacabras are a proto-human");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "chupacabras are a very ������������-human");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "chupacabras are a proto������");
   yUNIT_minstr ("... check mod"                      , s_mod                   , "                                         ");
   yUNIT_minval ("... check length"                   , s_len                   , 41);
   yUNIT_minval ("expected longer, exp tail masked"   , yvar_string_prep ("s_equal"   , "chupacabras are a very ������������������", "chupacabras are a proto-human"), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "chupacabras are a very ������������������");
   yUNIT_minstr ("... check actual"                   , s_act                   , "chupacabras are a proto-human");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "chupacabras are a very ������");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "chupacabras are a proto������");
   yUNIT_minstr ("... check mod"                      , s_mod                   , "                             ");
   yUNIT_minval ("... check length"                   , s_len                   , 29);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yvar_script_string_equal (void)
{
   yUNIT_minscrp ("yVAR_string");

   yUNIT_mincond ("verify unmasked comparisons");
   yUNIT_minval ("equal strings"                      , yVAR_string      ("s_equal"   , "testing123"                              , "testing123"                              ), 0);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          "                              );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "testing123"                              );
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "testing123"                              );
   yUNIT_minval ("expect longer"                      , yVAR_string      ("s_equal"   , "testing123456789-"                       , "testing123"                              ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          <<<<<<<"                       );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "testing123" BOLD_RED "456789-" BOLD_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "testing123" BOLD_RED "�������" BOLD_OFF);
   yUNIT_minval ("actual longer"                      , yVAR_string      ("s_equal"   , "testing123"                              , "testing123abcd"                          ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          >>>>"                          );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "testing123" BOLD_RED "����" BOLD_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "testing123" BOLD_RED "abcd" BOLD_OFF);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify masked comparisons");
   yUNIT_minval ("equal strings, middle masked"       , yVAR_string      ("s_equal"   , "tes����123"                              , "testing123"                              ), 0);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   ����   "                              );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "tes" BOLD_MAG "����" BOLD_OFF "123");
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "tes" BOLD_MAG "����" BOLD_OFF "123");
   yUNIT_minval ("expect longer"                      , yVAR_string      ("s_equal"   , "tes����123456789-"                       , "testing123"                              ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   ����   <<<<<<<"                       );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "tes" BOLD_MAG "����" BOLD_OFF "123" BOLD_RED "456789-" BOLD_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "tes" BOLD_MAG "����" BOLD_OFF "123" BOLD_RED "�������" BOLD_OFF);
   yUNIT_minval ("actual longer"                      , yVAR_string      ("s_equal"   , "tes����123"                              , "testing123abcd"                          ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   ����   >>>>"                          );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "tes" BOLD_MAG "����" BOLD_OFF "123" BOLD_RED "����" BOLD_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "tes" BOLD_MAG "����" BOLD_OFF "123" BOLD_RED "abcd" BOLD_OFF);
   yUNIT_minval ("actual longer, tail masked"         , yVAR_string      ("s_equal"   , "tes�"                                    , "testing123abcd"                          ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "tes�");
   yUNIT_minstr ("... check actual"                   , s_act                   , "testing123abcd");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "tes�����������");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "tes�����������");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   �����������"                       );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "tes" BOLD_MAG "�����������" BOLD_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "tes" BOLD_MAG "�����������" BOLD_OFF);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify trouble marking");
   yUNIT_minval ("different strings"                  , yVAR_string      ("s_equal"   , "testing123"                              , "testingabs"                              ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "       xxx"                              );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "testing" BOLD_RED "123" BOLD_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "testing" BOLD_RED "abs" BOLD_OFF);
   yUNIT_minval ("different strings"                  , yVAR_string      ("s_equal"   , "hosty"                                   , "testingabs"                              ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "xx  x>>>>>"                              );
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , BOLD_RED "ho" BOLD_OFF "st" BOLD_RED "y�����" BOLD_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , BOLD_RED "te" BOLD_OFF "st" BOLD_RED "ingabs" BOLD_OFF);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yvar_script_round        (void)
{
   yUNIT_minscrp ("yVAR_round");

   yUNIT_mincond ("verify non-numeric comparisons (same as s_equal");
   yUNIT_minval ("equal strings"                      , yVAR_round       ("u_round/1" , "testing123"                              , "testing123"                              ), 0);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          "                              );
   yUNIT_minval ("expect longer"                      , yVAR_round       ("u_round/1" , "testing123456789-"                       , "testing123"                              ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          <<<<<<<"                       );
   yUNIT_minval ("actual longer"                      , yVAR_round       ("u_round/1" , "testing123"                              , "testing123abcd"                          ), -10);
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          >>>>"                          );
   yUNIT_mindnoc ();

   yUNIT_mincond ("simple numbers");
   yUNIT_minval ("outside low"                        , yVAR_round       ("u_round/1" , "   -2      "                               , "    0      "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -2      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "   -2      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   xx      ");
   yUNIT_minval ("lowest match"                       , yVAR_round       ("u_round/1" , "   -1      "                               , "    0      "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -1      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    0      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   rr      ");
   yUNIT_minval ("exact match"                        , yVAR_round       ("u_round/1" , "    0      "                               , "    0      "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    0      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    0      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "           "                             );
   yUNIT_minval ("highest match"                      , yVAR_round       ("u_round/1" , "    1      "                               , "    0      "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    1      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    0      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    r      ");
   yUNIT_minval ("outside high"                       , yVAR_round       ("u_round/1" , "    2      "                               , "    0      "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    2      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    2      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    x      ");
   yUNIT_minval ("negative"                           , yVAR_round       ("u_round/1" , "   -0      "                               , "    0      "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -0      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    0      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   r       ");
   yUNIT_mindnoc ();

   yUNIT_mincond ("multi-digit integer");
   yUNIT_minval ("outside low"                        , yVAR_round       ("u_round/3" , "  325      "                               , "  321      "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "  325      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "  321      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "  325      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "  321      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    x      ");
   yUNIT_minval ("lowest match"                       , yVAR_round       ("u_round/3" , "  325      "                               , "  322      "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "  325      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "  322      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "  322      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "  322      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    r      ");
   yUNIT_minval ("exact match"                        , yVAR_round       ("u_round/3" , "  325      "                               , "  325      "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "  325      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "  325      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "  325      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "  325      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "           "                             );
   yUNIT_minval ("highest match"                      , yVAR_round       ("u_round/3" , "  325      "                               , "  328      "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "  325      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "  328      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "  328      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "  328      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    r      ");
   yUNIT_minval ("outside high"                       , yVAR_round       ("u_round/3" , "  325      "                               , "  329      "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "  325      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "  329      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "  325      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "  329      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    x      ");
   yUNIT_minval ("negative"                           , yVAR_round       ("u_round/3" , "  325      "                               , " -325      "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "  325      ");
   yUNIT_minstr ("... check actual"                   , s_act                   , " -325      ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "  325      ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , " -325      ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , " x         ");
   yUNIT_mindnoc ();

   yUNIT_mincond ("small decimal");            
   yUNIT_minval ("outside low"                        , yVAR_round       ("u_round/4" , "    1.3    "                               , "    0.8    "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0.8    ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0.8    ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    x x    ");
   yUNIT_minval ("lowest match"                       , yVAR_round       ("u_round/4" , "    1.3    "                               , "    0.9    "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    0.9    ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    0.9    ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    0.9    ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    r r    ");
   yUNIT_minval ("exact match"                        , yVAR_round       ("u_round/4" , "    1.3    "                               , "    1.3    "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    1.3    ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    1.3    ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "           "                             );
   yUNIT_minval ("highest match"                      , yVAR_round       ("u_round/4" , "    1.3    "                               , "    1.7    "                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    1.7    ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    1.7    ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    1.7    ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "      r    ");
   yUNIT_minval ("outside high"                       , yVAR_round       ("u_round/4" , "    1.3    "                               , "    1.8    "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    1.8    ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    1.8    ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "      x    ");
   yUNIT_minval ("negative"                           , yVAR_round       ("u_round/4" , "    1.3    "                               , "   -1.3    "                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual"                   , s_act                   , "   -1.3    ");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "    1.3    ");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "   -1.3    ");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   x       ");
   yUNIT_mindnoc ();

   yUNIT_mincond ("larger negative decimal");  
   yUNIT_minval ("outside low"                        , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12151"                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "   -3.12151");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "   -3.12151");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          x");
   yUNIT_minval ("lowest match"                       , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12152"                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "   -3.12152");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "   -3.12152");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "   -3.12152");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "          r");
   yUNIT_minval ("exact match"                        , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12159"                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "   -3.12159");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "   -3.12159");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "           "                             );
   yUNIT_minval ("highest match"                      , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12166"                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "   -3.12166");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "   -3.12166");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "   -3.12166");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "         rr");
   yUNIT_minval ("outside high"                       , yVAR_round       ("u_round/7" , "   -3.12159"                               , "   -3.12167"                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "   -3.12167");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "   -3.12167");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "         xx");
   yUNIT_minval ("negative"                           , yVAR_round       ("u_round/7" , "   -3.12159"                               , "    3.12159"                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "    3.12159");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "   -3.12159");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "    3.12159");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "   x       ");
   yUNIT_mindnoc ();

   yUNIT_mincond ("multiple numbers");               
   yUNIT_minval ("exact match"                        , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "pi=-3.12159"                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "pi=-3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "pi=-3.12159");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "pi=-3.12159");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "pi=-3.12159");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "           "                             );
   yUNIT_minval ("other match"                        , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "pi=-3.12166"                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "pi=-3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "pi=-3.12166");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "pi=-3.12166");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "pi=-3.12166");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "         rr");
   yUNIT_minval ("bad-text, but number match"         , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "PI/-3.12166"                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "pi=-3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "PI/-3.12166");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "pi=-3.12166");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "PI/-3.12166");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "xxx      rr");
   yUNIT_minval ("non-match"                          , yVAR_round       ("u_round/7" , "pi=-3.12159"                               , "pi=-3.12167"                             ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "pi=-3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "pi=-3.12167");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "pi=-3.12159");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "pi=-3.12167");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "         xx");
   yUNIT_mindnoc ();

   yUNIT_mincond ("funky cases");
   yUNIT_minval ("positive marker"                    , yVAR_round       ("u_round/7" , "pi=+3.12159"                               , "pi=+3.12166"                             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "pi=+3.12159");
   yUNIT_minstr ("... check actual"                   , s_act                   , "pi=+3.12166");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "pi=+3.12166");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "pi=+3.12166");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "         rr");
   yUNIT_minval ("embedded number, no leading space"  , yVAR_round       ("u_round/1" , "test3 more"                                , "test2 more"                              ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "test3 more" );
   yUNIT_minstr ("... check actual"                   , s_act                   , "test2 more" );
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "test3 more" );
   yUNIT_minstr ("... check actual for use"           , u_act                   , "test2 more" );
   yUNIT_minstr ("... check modded value"             , s_mod                   , "    x     " );
   yUNIT_minval ("embedded number, no proper lead"    , yVAR_round       ("u_round/1" , "a=5"                                       , "a=4"                                     ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "a=5"        );
   yUNIT_minstr ("... check actual"                   , s_act                   , "a=4"        );
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "a=5"        );
   yUNIT_minstr ("... check actual for use"           , u_act                   , "a=4"        );
   yUNIT_minstr ("... check modded value"             , s_mod                   , "  x"        );
   yUNIT_minval ("multiple numbers, success"          , yVAR_round       ("u_round/7" , "pi=-3.12159, rads= 352, a 5"               , "pi=-3.12166, rads= 350, a 9"             ), 0);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "pi=-3.12159, rads= 352, a 5");
   yUNIT_minstr ("... check actual"                   , s_act                   , "pi=-3.12166, rads= 350, a 9");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "pi=-3.12166, rads= 350, a 9");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "pi=-3.12166, rads= 350, a 9");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "         rr          r    r");
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , "pi=-3.121" BOLD_YEL "59" FORE_OFF ", rads= 35" BOLD_YEL "2" FORE_OFF ", a " BOLD_YEL "5" FORE_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , "pi=-3.121" BOLD_YEL "66" FORE_OFF ", rads= 35" BOLD_YEL "0" FORE_OFF ", a " BOLD_YEL "9" FORE_OFF);
   yUNIT_minval ("multiple numbers, text trouble"     , yVAR_round       ("u_round/7" , "PI=-3.12159, radn= 352, a 5 ��������"     , "pi=-3.12166, rads= 350, a 9 heidi 10"    ), -999);
   yUNIT_minstr ("... check expect"                   , s_exp                   , "PI=-3.12159, radn= 352, a 5 ��������");
   yUNIT_minstr ("... check actual"                   , s_act                   , "pi=-3.12166, rads= 350, a 9 heidi 10");
   yUNIT_minstr ("... check expect for use"           , u_exp                   , "PI=-3.12166, radn= 350, a 9 ��������");
   yUNIT_minstr ("... check actual for use"           , u_act                   , "pi=-3.12166, rads= 350, a 9 ��������");
   yUNIT_minstr ("... check modded value"             , s_mod                   , "xx       rr     x    r    r ��������");
   yUNIT_minstr ("... check fancy expect"             , s_fexp                  , BOLD_RED "PI" FORE_OFF "=-3.121" BOLD_YEL "59" FORE_OFF ", rad" BOLD_RED "n" FORE_OFF "= 35" BOLD_YEL "2" FORE_OFF ", a " BOLD_YEL "5" FORE_OFF " " BOLD_MAG "��������" FORE_OFF);
   yUNIT_minstr ("... check fancy actual"             , s_fact                  , BOLD_RED "pi" FORE_OFF "=-3.121" BOLD_YEL "66" FORE_OFF ", rad" BOLD_RED "s" FORE_OFF "= 35" BOLD_YEL "0" FORE_OFF ", a " BOLD_YEL "9" FORE_OFF " " BOLD_MAG "��������" FORE_OFF);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}

char
yvar_script_string_other (void)
{
   yUNIT_minscrp ("yVAR_string");

   yUNIT_mincond ("verify not equal");
   yUNIT_minval ("equal strings"                      , yVAR_string      ("s_not"     , "testing123"                              , "testing123"                              ), -999);
   yUNIT_minval ("first char different"               , yVAR_string      ("s_not"     , "testing123"                              , "Testing123"                              ),    0);
   yUNIT_minval ("last char different"                , yVAR_string      ("s_not"     , "testing123"                              , "testing12a"                              ),    0);
   yUNIT_minval ("middle char different"              , yVAR_string      ("s_not"     , "testing123"                              , "testqng123"                              ),    0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify greater");
   yUNIT_minval ("must lesser"                        , yVAR_string      ("s_greater" , "abcde"                                   , "aabbadea"                                ), -999);
   yUNIT_minval ("lesser"                             , yVAR_string      ("s_greater" , "abcde"                                   , "abcdd"                                   ), -999);
   yUNIT_minval ("equal"                              , yVAR_string      ("s_greater" , "abcde"                                   , "abcde"                                   ), -999);
   yUNIT_minval ("greater"                            , yVAR_string      ("s_greater" , "abcde"                                   , "abcdf"                                   ),    0);
   yUNIT_minval ("much greater"                       , yVAR_string      ("s_greater" , "abcde"                                   , "zequae"                                  ),    0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify greater or equal");
   yUNIT_minval ("must lesser"                        , yVAR_string      ("s_gequal"  , "abcde"                                   , "aabbadea"                                ), -999);
   yUNIT_minval ("lesser"                             , yVAR_string      ("s_gequal"  , "abcde"                                   , "abcdd"                                   ), -999);
   yUNIT_minval ("equal"                              , yVAR_string      ("s_gequal"  , "abcde"                                   , "abcde"                                   ),    0);
   yUNIT_minval ("greater"                            , yVAR_string      ("s_gequal"  , "abcde"                                   , "abcdf"                                   ),    0);
   yUNIT_minval ("much greater"                       , yVAR_string      ("s_gequal"  , "abcde"                                   , "zequae"                                  ),    0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify lesser or equal");
   yUNIT_minval ("must lesser"                        , yVAR_string      ("s_lequal"  , "abcde"                                   , "aabbadea"                                ),    0);
   yUNIT_minval ("lesser"                             , yVAR_string      ("s_lequal"  , "abcde"                                   , "abcdd"                                   ),    0);
   yUNIT_minval ("equal"                              , yVAR_string      ("s_lequal"  , "abcde"                                   , "abcde"                                   ),    0);
   yUNIT_minval ("greater"                            , yVAR_string      ("s_lequal"  , "abcde"                                   , "abcdf"                                   ), -999);
   yUNIT_minval ("much greater"                       , yVAR_string      ("s_lequal"  , "abcde"                                   , "zequae"                                  ), -999);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify lesser");                     
   yUNIT_minval ("must lesser"                        , yVAR_string      ("s_lesser"  , "abcde"                                   , "aabbadea"                                ),    0);
   yUNIT_minval ("lesser"                             , yVAR_string      ("s_lesser"  , "abcde"                                   , "abcdd"                                   ),    0);
   yUNIT_minval ("equal"                              , yVAR_string      ("s_lesser"  , "abcde"                                   , "abcde"                                   ), -999);
   yUNIT_minval ("greater"                            , yVAR_string      ("s_lesser"  , "abcde"                                   , "abcdf"                                   ), -999);
   yUNIT_minval ("much greater"                       , yVAR_string      ("s_lesser"  , "abcde"                                   , "zequae"                                  ), -999);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify sub");
   yUNIT_minval ("equal strings"                      , yVAR_string      ("s_sub"     , "testing123"                              , "testing123"                              ),    0);
   yUNIT_minval ("leading string"                     , yVAR_string      ("s_sub"     , "test"                                    , "testing123"                              ),    0);
   yUNIT_minval ("trailing string"                    , yVAR_string      ("s_sub"     , "ing"                                     , "testing12a"                              ),    0);
   yUNIT_minval ("middle string"                      , yVAR_string      ("s_sub"     , "123"                                     , "testqng123"                              ),    0);
   yUNIT_minval ("not found"                          , yVAR_string      ("s_sub"     , "honk"                                    , "testqng123"                              ), -999);
   yUNIT_minval ("not found"                          , yVAR_string      ("s_sub"     , "321"                                     , "testqng123"                              ), -999);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify entry");
   yUNIT_minval ("equal strings"                      , yVAR_string      ("s_entry"   , "testing123"                              , "testing123"                              ),    0);
   yUNIT_minval ("leading string"                     , yVAR_string      ("s_entry"   , "testing123"                              , "test"                                    ),    0);
   yUNIT_minval ("trailing string"                    , yVAR_string      ("s_entry"   , "testing123"                              , "ing"                                     ),    0);
   yUNIT_minval ("middle string"                      , yVAR_string      ("s_entry"   , "testing123"                              , "123"                                     ),    0);
   yUNIT_minval ("not found"                          , yVAR_string      ("s_entry"   , "testing123"                              , "honk"                                    ), -999);
   yUNIT_minval ("not found"                          , yVAR_string      ("s_entry"   , "testing123"                              , "321"                                     ), -999);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify empty");  
   yUNIT_minval ("empty"                              , yVAR_string      ("s_empty"   , ""                                        , ""                                        ),    0);
   yUNIT_minval ("small"                              , yVAR_string      ("s_empty"   , ""                                        , "a"                                       ), -999);
   yUNIT_minval ("larger"                             , yVAR_string      ("s_empty"   , ""                                        , "ing"                                     ), -999);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify exists"); 
   yUNIT_minval ("empty"                              , yVAR_string      ("s_exists"  , ""                                        , ""                                        ), -999);
   yUNIT_minval ("small"                              , yVAR_string      ("s_exists"  , ""                                        , "a"                                       ),    0);
   yUNIT_minval ("larger"                             , yVAR_string      ("s_exists"  , ""                                        , "ing"                                     ),    0);
   yUNIT_mindnoc ();

   yUNIT_mincond ("verify length"); 
   yUNIT_minval ("empty"                              , yVAR_string      ("s_length"  , "0"                                       , ""                                        ),    0);
   yUNIT_minval ("empty"                              , yVAR_string      ("s_length"  , "1"                                       , ""                                        ), -999);
   yUNIT_minval ("small"                              , yVAR_string      ("s_length"  , "0"                                       , "a"                                       ), -999);
   yUNIT_minval ("small"                              , yVAR_string      ("s_length"  , "1"                                       , "a"                                       ),    0);
   yUNIT_minval ("larger"                             , yVAR_string      ("s_length"  , "0"                                       , "ing"                                     ), -999);
   yUNIT_minval ("larger"                             , yVAR_string      ("s_length"  , "3"                                       , "ing"                                     ),    0);
   yUNIT_mindnoc ();

   yUNIT_minprcs ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                            driver                            ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVER__________________o (void) {;}

char
main (void)
{
   yvar_script_string_prep  ();
   yvar_script_string_equal ();
   yvar_script_round        ();
   yvar_script_string_other ();
   yUNIT_mintinu ();
   return 0;
}



