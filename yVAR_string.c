/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"


char        s_test      [LEN_LABEL] = "";

char        s_exp       [LEN_RECD]  = "";
char        u_exp       [LEN_RECD]  = "";
char        s_act       [LEN_RECD]  = "";

char        u_act       [LEN_RECD]  = "";
char        s_mod       [LEN_RECD]  = "";
char        s_fact      [LEN_RECD]  = "";
char        s_fexp      [LEN_RECD]  = "";

int         s_len       = 0;
int         s_alen      = 0;
int         s_elen      = 0;
char        s_range     = 0;
char        s_nmod      = 0;
char        s_off       = 0;

static      regex_t     s_regex;
static      regmatch_t  s_match   [1];



#define     MAX_TEST       50
struct {
   char        name        [LEN_LABEL];
   char        desc        [LEN_DESC];
} s_tests [MAX_TEST] = {
   { "s_equal"      , "actual   == expected"                                },
   { "s_not"        , "actual   != expected"                                },
   { "s_sub"        , "expected contained in actual"                        },
   { "s_entry"      , "actual string contained in a larger expected one"    },
   { "s_empty"      , "actual string is null/empty"                         },
   { "s_exists"     , "actual string is not null/empty"                     },
   { "s_length"     , "check for a certain number of characters"            },
   { "s_greater"    , "actual string sorts greater than expected"           },
   { "s_gequal"     , "actual string sorts greater than or equal"           },
   { "s_lesser"     , "actual string sorts lesser  than expected"           },
   { "s_lequal"     , "actual string sorts lesser  or equal"                },
   { "s_regex"      , "do regex matching on expected using actual"          },
};



/*====================------------------------------------====================*/
/*===----                         normal testing                       ----===*/
/*====================------------------------------------====================*/
static void      o___NORMAL__________________o (void) {;}

char
yvar_string_prep        (char a_test [LEN_TERSE], char a_expect [LEN_RECD], char a_actual [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =    0;
   char        rc          =    0;
   int         i           =    0;
   int         l           =    0;
   /*> char       *x_valid     = " s_equal s_not s_sub s_entry s_regex s_length s_empty s_exists s_greater s_gequal s_lesser s_lequal ";   <*/
   /*---(defaults)-----------------------*/
   s_alen    = s_elen    = s_len     = 0;
   s_nmod    = s_range   = s_off     = 0;
   s_exp  [0] = u_exp  [0] = s_act  [0] = u_act  [0] = s_mod  [0] = '\0';
   s_fact [0] = s_fexp [0] = '\0';
   /*---(defense)------------------------*/
   --rce;  if (a_test     == NULL  )             return rce;
   --rce;  if (a_expect   == NULL  )             return rce;
   --rce;  if (a_actual   == NULL  )             return rce;
   --rce;  if (a_expect   <  0x1000)             return rce;
   --rce;  if (a_actual   <  0x1000)             return rce;
   /*---(test type)----------------------*/
   l = strlen (a_test);
   --rce;  if (l < 5)                            return rce;
   --rce;  if (l == 9 && strncmp (a_test, "u_round/", 8) == 0) {
      s_range = a_test [8] - '0';
      if (s_range < 1 || s_range > 9)            return ('�');
   }
   /*> else if (strstr (x_valid, a_test) == NULL)  return ('�');                      <*/
   /*---(save values)--------------------*/
   strcpy (s_test, a_test);
   strcpy (s_exp , a_expect);
   strcpy (u_exp , a_expect);
   strcpy (s_act , a_actual);
   strcpy (u_act , a_actual);
   /*---(lengths)------------------------*/
   s_alen = strlen (u_act);
   --rce;  if (s_alen > 500)                     return rce;
   s_elen = strlen (u_exp);
   --rce;  if (s_elen > 500)                     return rce;
   /*---(extend masking)-----------------*/
   if (s_elen < s_alen && u_exp [s_elen - 1] == '�') {
      for (i = s_elen; i <= s_alen; ++i) {
         u_exp [i]     = '�';
         u_exp [i + 1] = '\0';
      }
   }
   s_elen = strlen (u_exp);
   /*---(truncate masking)---------------*/
   for (i = s_elen - 1; i >= s_alen; --i) {
      if (u_exp [i] != '�')  break;
      u_exp [i] = '\0';
   }
   s_elen = strlen (u_exp);
   /*---(transfer masking)---------------*/
   for (i = 0; i < s_alen; ++i) {
      if (u_exp [i] == NULL || u_act [i] == NULL)  break;
      /*> if (u_exp [i] == '�')  u_act [i] = '�';                                     <*/
   }
   s_elen = strlen (u_exp);
   s_len  = s_alen;
   if (s_len < s_elen)  s_len = s_elen;
   /*---(prepare mod)--------------------*/
   for (i = 0; i < s_len; ++i)  s_mod [i]     = ' ';
   s_mod [i] = '\0';
   /*---(prepare search)-----------------*/
   --rce;  if (s_range > 0) {
      rc = regcomp (&s_regex, "[-+ ](0|[1-9][0-9]*)([.][0-9]+)?", REG_EXTENDED);
      if (rc != 0)                               return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

/*> char                                                                                                                                 <* 
 *> yvar_string_fancify_old (int a_len, char a_orig [LEN_RECD], char a_src [LEN_RECD], char a_mod [LEN_RECD], char r_fancy [LEN_RECD])   <* 
 *> {                                                                                                                                    <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                          <* 
 *>    char        rce         =  -10;                                                                                                   <* 
 *>    int         i           =    0;                                                                                                   <* 
 *>    char        t           [LEN_TERSE] = "";                                                                                         <* 
 *>    char        m           =  '-';                                                                                                   <* 
 *>    char        s           =  '�';                                                                                                   <* 
 *>    int         l           =    0;                                                                                                   <* 
 *>    /+---(defense)------------------------+/                                                                                          <* 
 *>    --rce;  if (a_orig == NULL)  return rce;                                                                                          <* 
 *>    --rce;  if (a_src  == NULL)  return rce;                                                                                          <* 
 *>    --rce;  if (r_fancy  == NULL)  return rce;                                                                                        <* 
 *>    /+---(initialize)---------------------+/                                                                                          <* 
 *>    r_fancy [0] = '\0';                                                                                                               <* 
 *>    s = ' ';                                                                                                                          <* 
 *>    l = strlen (a_orig);                                                                                                              <* 
 *>    /+---(walk)---------------------------+/                                                                                          <* 
 *>    for (i = 0; i < s_len; ++i) {                                                                                                     <* 
 *>       m = a_mod [i];                                                                                                                 <* 
 *>       if      (i < l)      sprintf (t, "%c", a_orig [i]);                                                                            <* 
 *>       else if (i < a_len)  sprintf (t, "%c", a_src  [i]);                                                                            <* 
 *>       else                 sprintf (t, "%c", '�');                                                                                   <* 
 *>       if (m != s) {                                                                                                                  <* 
 *>          if (strchr ("x><", s) != NULL && strchr ("x><", m) != NULL) ; /+ reduce duplicates +/                                       <* 
 *>          else {                                                                                                                      <* 
 *>             if (s != ' ')  strcat (r_fancy, FORE_OFF);                                                                               <* 
 *>             switch (m) {                                                                                                             <* 
 *>             case 'x' : case '>' : case '<' :                                                                                         <* 
 *>                strcat (r_fancy, BOLD_RED);                                                                                           <* 
 *>                break;                                                                                                                <* 
 *>             case 'r' :                                                                                                               <* 
 *>                strcat (r_fancy, BOLD_YEL);                                                                                           <* 
 *>                break;                                                                                                                <* 
 *>             case '�' :                                                                                                               <* 
 *>                strcat (r_fancy, BOLD_MAG);                                                                                           <* 
 *>                break;                                                                                                                <* 
 *>             }                                                                                                                        <* 
 *>          }                                                                                                                           <* 
 *>       }                                                                                                                              <* 
 *>       s = m;                                                                                                                         <* 
 *>       strcat (r_fancy, t);                                                                                                           <* 
 *>    }                                                                                                                                 <* 
 *>    /+---(finish off)---------------------+/                                                                                          <* 
 *>    if (s != ' ')  strcat (r_fancy, FORE_OFF);                                                                                        <* 
 *>    /+---(complete)-----------------------+/                                                                                          <* 
 *>    return 0;                                                                                                                         <* 
 *> }                                                                                                                                    <*/

char
yvar_string_fancy       (char a_act [LEN_RECD], char a_mod [LEN_RECD], char r_fancy [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        x_use       [LEN_TERSE] = "";
   char        x_curr      =  '-';
   char        x_save      =  ' ';
   int         x_alen      =    0;
   int         x_mlen      =    0;
   int         x_max       =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_act   == NULL)  return rce;
   --rce;  if (a_mod   == NULL)  return rce;
   --rce;  if (r_fancy == NULL)  return rce;
   /*---(prepare)------------------------*/
   x_alen = strlen (a_act);
   --rce;  if (x_alen >= LEN_RECD)  return rce;
   /*> printf ("x_alen  = %d\n", x_alen);                                             <*/
   x_mlen = strlen (a_mod);
   --rce;  if (x_mlen >= LEN_RECD)  return rce;
   /*> printf ("x_mlen  = %d\n", x_mlen);                                             <*/
   x_max = x_mlen;
   if (x_alen > x_max)  x_max = x_alen;
   strlcpy (r_fancy, "", LEN_RECD);
   /*> printf ("x_max   = %d\n", x_max);                                              <*/
   /*---(walk)---------------------------*/
   for (i = 0; i < x_max; ++i) {
      /*---(character)-------------------*/
      x_curr = a_mod [i];
      if      (i < x_alen)  sprintf (x_use, "%c", a_act [i]);
      else if (i < x_mlen)  sprintf (x_use, "%c", a_mod [i]);
      else                  sprintf (x_use, "%c", '�');
      /*---(mark touble)-----------------*/
      if (x_curr != x_save) {
         if (strchr ("x><", x_save) != NULL && strchr ("x><", x_curr) != NULL) ; /* reduce duplicates */
         else {
            if (x_save != ' ')  strlcat (r_fancy, FORE_OFF, LEN_RECD);
            switch (x_curr) {
            case 'x' : case '>' : case '<' :
               strlcat (r_fancy, BOLD_RED, LEN_RECD);
               break;
            case 'r' :
               strlcat (r_fancy, BOLD_CYN, LEN_RECD);
               break;
            case '�' :
               strlcat (r_fancy, BOLD_MAG, LEN_RECD);
               break;
            }
         }
      }
      /*---(add character)---------------*/
      x_save = x_curr;
      strlcat (r_fancy, x_use, LEN_RECD);
      /*---(done)------------------------*/
   }
   /*---(finish off)---------------------*/
   if (x_save != ' ')  strlcat (r_fancy, FORE_OFF, LEN_RECD);
   /*---(complete)-----------------------*/
   return 0;
}

char
yvar_string_match       (char a_exp [LEN_RECD], char a_act [LEN_RECD], char r_mod [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_elen      =    0;
   int         x_alen      =    0;
   int         x_mlen      =    0;
   int         x_max       =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_exp == NULL)  return rce;
   --rce;  if (a_act == NULL)  return rce;
   --rce;  if (r_mod == NULL)  return rce;
   /*---(prepare)------------------------*/
   x_elen = strlen (a_exp);
   --rce;  if (x_elen >= LEN_RECD)  return rce;
   x_alen = strlen (a_act);
   --rce;  if (x_alen >= LEN_RECD)  return rce;
   /*---(figure max)---------------------*/
   x_max = x_elen;
   if (x_alen >  x_max)  x_max = x_alen;
   /*---(update r_mod)-------------------*/
   x_mlen = strlen (r_mod);
   --rce;  if (x_mlen >= LEN_RECD)  return rce;
   if      (x_mlen <  x_max)   strlcat (r_mod, YSTR_EMPTY, x_max);
   else if (x_mlen >  x_max)   r_mod [x_max - 1] = '\0';
   for (i == 0; i < x_max; ++i)  if (r_mod [i] != 'r')  r_mod [i] = ' ';
   /*---(create mod version)-------------*/
   for (i = 0; i < x_max; ++i) {
      /*---(past actual end)-------------*/
      if (i >= x_alen) {
         r_mod [i] = '<';
         rc = rce;
         continue;
      }
      /*---(past expect end)-------------*/
      if (i >= x_elen) {
         r_mod [i] = '>';
         rc = rce;
         continue;
      }
      /*---(masked)----------------------*/
      if (a_exp [i] == '�') {
         r_mod [i] = '�';
         continue;
      }
      /*---(match)-----------------------*/
      else if (a_exp [i] == a_act [i]) {
         continue;
      }
      /*---(failed match)----------------*/
      r_mod [i] = 'x';
      rc = rce;
      /*---(done)------------------------*/
   }
   r_mod [i] = '\0';
   /*---(complete)-----------------------*/
   return rc;
}

char
yvar_string_adjust      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_beg       =    0;
   int         x_end       =    0;
   int         x_len       =    0;
   char        x_isdec     =  '-';
   int         x_dec       =    0;
   int         i           =    0;
   int         j           =    0;
   char        x_ch        =  ' ';
   char        x_exp       [LEN_LABEL] = "";
   char        x_act       [LEN_LABEL] = "";
   double      x_num       =  0.0;
   double      x_inc       =  0.0;
   double      x_new       =  0.0;
   char        x_chk       [LEN_LABEL] = "";
   char        x_neg       [LEN_LABEL] = "";
   char        x_fin       [LEN_LABEL] = "";
   /*---(next match)---------------------*/
   DEBUG_YVAR  printf ("yvar_string_adjust() \n");
   DEBUG_YVAR  printf ("%3d s_off, %s\n", s_off, u_exp + s_off);
   rc = regexec (&s_regex, u_exp + s_off, 1, s_match, 0);
   DEBUG_YVAR  printf ("%3d rc\n", rc);
   --rce;  if (rc != 0) return rce;
   x_beg   = s_match [0].rm_so + s_off;
   x_end   = s_match [0].rm_eo + s_off;
   x_len   = x_end - x_beg;
   s_off   = x_end;
   DEBUG_YVAR  printf ("match %3d rc, %3d beg, %3d end, %3d len, %3d off\n", rc, x_beg, x_end, x_len, s_off);
   /*---(parse out)----------------------*/
   strncpy (x_exp, u_exp + x_beg, x_len);
   x_num = atof (x_exp);
   strncpy (x_act, u_act + x_beg, x_len);
   DEBUG_YVAR  printf ("expect [%s]  %16.7lf\n", x_exp, x_num);
   DEBUG_YVAR  printf ("actual [%s]\n", x_act);
   /*---(find decimals)------------------*/
   x_dec = 0;
   for (i = x_beg; i < x_end; ++i) {
      x_ch = u_exp [i];
      if (x_isdec == 'y') ++x_dec;
      if (x_ch == '.') {
         x_isdec = 'y';
         x_dec   = 0;
      }
   }
   DEBUG_YVAR  printf ("decimal %d\n", x_dec);
   /*---(adjust)-------------------------*/
   for (i = -s_range; i <= s_range; ++i) {
      /*---(multiplier)------------------*/
      x_inc = i;
      for (j = 0; j < x_dec; ++j)  x_inc /= 10;
      x_new = x_num + x_inc;
      DEBUG_YVAR  printf ("range   %2d  %16.7lf  %16.7lf\n", i, x_inc, x_new);
      /*> DEBUG_YVAR   printf ("   dec = %d, chg = %2d, base = %10lf, inc = %10lf, new = %10lf\n", x_dec, i, x_num, x_inc, x_new);   <*/
      snprintf (x_chk, LEN_LABEL, "%*.*lf", x_len, x_dec, x_new);
      snprintf (x_neg, LEN_LABEL, "%*.*lf", x_len, x_dec, x_new - 0.000000001);
      DEBUG_YVAR  printf ("chk    [%s]\n", x_chk);
      DEBUG_YVAR  printf ("neg    [%s]\n", x_neg);
      DEBUG_YVAR  printf ("act    [%s]\n", x_act);
      /*> DEBUG_YVAR   printf ("   checking  = <<%s>>  :: ", x_chk);               <*/
      /*---(exact match)------------------*/
      if (strcmp (x_chk, x_act) == 0) {
         /*> DEBUG_YVAR   printf ("match\n");                                         <*/
         strncpy (x_fin, x_chk, LEN_LABEL);
         break;
      }
      /*---(negative zeros)--------------*/
      else if (strcmp(x_neg, x_act) == 0) {
         /*> DEBUG_YVAR   printf ("match neg zero\n");                                <*/
         strncpy (x_fin, x_neg, LEN_LABEL);
         break;
      }
      /*---(actual has leading plus)-----*/
      else if (x_chk [0] == ' ' && x_act [0] == '+') {
         x_chk [0] = '+';
         if (strcmp (x_chk, x_act) == 0) {
            /*> DEBUG_YVAR   printf ("match\n");                                         <*/
            strncpy (x_fin, x_chk, LEN_LABEL);
            break;
         }
      }
      /*---(done)------------------------*/
   }
   DEBUG_YVAR  printf ("fin    [%s]\n", x_fin);
   --rce;  if (strcmp (x_fin, "") == 0) {
      DEBUG_YVAR  printf ("NO MATCH\n");
      return rce;
   }
   /*---(fix exp and mod)----------------*/
   for (i = x_beg; i <= x_end; ++i) {
      if (x_fin [i - x_beg] == '\0')  break;
      if (u_exp [i] != x_fin [i - x_beg]) {
         s_mod [i] = 'r';
         u_exp [i] = x_fin [i - x_beg];
         ++s_nmod;
      }
   }
   DEBUG_YVAR  printf ("MATCH\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
yVAR_string             (char a_test [LEN_TERSE], char a_expect [LEN_RECD], char a_actual [LEN_RECD])
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
   char        rce         =  -10;
   char        rc          =    0;
   char        x_match     =    0;
   int         i           =    0;
   char        x_entry     [LEN_TITLE] = "";
   regex_t     x_comp;
   /*---(defenses)-----------------------*/
   rc = yvar_string_prep (a_test, a_expect, a_actual);
   if (rc == '�')  return rc;
   if (rc <   0 )  return rc;
   /*---(normal tests)-------------------*/
   if        (strcmp (a_test, "s_equal")   == 0) {
      rc = -('e');
      x_match = yvar_string_match (u_exp, u_act, s_mod);
      yvar_string_fancy (u_act, s_mod, s_fact);
      if (x_match >= 0)                   rc *= -1;
   } else if (strcmp (a_test, "s_not")     == 0) {
      rc = -('n');
      if (strcmp (u_act, u_exp) != 0)     rc *= -1;
   } else if (strcmp (a_test, "s_greater") == 0) {
      rc = -('g');
      if (strcmp (u_act, u_exp) >  0)     rc *= -1;
   } else if (strcmp (a_test, "s_gequal" ) == 0) {
      rc = -('G');
      if (strcmp (u_act, u_exp) >= 0)     rc *= -1;
   } else if (strcmp (a_test, "s_lesser")  == 0) {
      rc = -('l');
      if (strcmp (u_act, u_exp) <  0)     rc *= -1;
   } else if (strcmp (a_test, "s_lequal")  == 0) {
      rc = -('L');
      if (strcmp (u_act, u_exp) <= 0)     rc *= -1;
   }
   /*---(lengths)------------------------*/
   else if   (strcmp (a_test, "s_empty")   == 0) {
      rc = -('z');
      if (strlen (u_act) == 0 ) rc *= -1;
   } else if (strcmp (a_test, "s_exists")  == 0) {
      rc = -('x');
      if (strlen (u_act) >  0 ) rc *= -1;
   } else if (strcmp (a_test, "s_length")  == 0) {
      rc = -('l');
      if (strlen (u_act) == atoi (u_exp)) rc *= -1;
   }
   /*---(search tests)-------------------*/
   else if   (strcmp (a_test, "s_sub")     == 0) {
      rc = -('s');
      if      (strcmp (a_expect, a_actual) == 0)    rc *= -1;
      else if (strstr (a_expect, a_actual) != NULL) rc *= -1;
   } else if (strcmp (a_test, "s_super")   == 0) {
      rc = -('s');
      if      (strcmp (a_actual, a_expect) == 0)    rc *= -1;
      else if (strstr (a_actual, a_expect) != NULL) rc *= -1;
   } else if (strcmp(a_test, "s_entry")     == 0) {
      rc = -('i');
      sprintf (x_entry, ",%s,", a_actual);
      if (strstr (a_expect, x_entry) != NULL) rc *= -1;
   }
   /*---(regex test)---------------------*/
   else if   (strcmp (a_test, "s_regex")    == 0) {
      rc = -('r');
      rc    = regcomp(&x_comp, u_exp, REG_EXTENDED);
      if (rc == 0) {
         rc    = regexec(&x_comp, u_act, 0, NULL, 0);
         if (rc != 0) rc *= -1;
      }
      regfree(&x_comp);
   }
   /*---(complete)-----------------------*/
   return rc;
}

char yVAR_strs   (char a_test [LEN_TERSE], char a_actual [LEN_RECD]) { return yVAR_string (a_test, "", a_actual); }
char yVAR_yunit  (char a_expect [LEN_RECD], char a_actual [LEN_RECD], char r_modify [LEN_RECD]) { return yvar_string_match (a_expect, a_actual, r_modify); }

char
yVAR_round              (char a_test [LEN_TERSE], char a_expect [LEN_RECD], char a_actual [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         i           =    0;
   char        mods_str    [LEN_LABEL] = "";
   /*---(defenses)-----------------------*/
   rc = yvar_string_prep (a_test, a_expect, a_actual);
   if (rc == '�')  return rc;
   if (rc <   0 )  return -66;
   --rce;  if (s_range < 1)        return rce;
   --rce;  if (a_test [0] != 'u')  return rce;
   /*---(process matches)--------------------*/
   while (rc == 0) {
      rc = yvar_string_adjust ();
   }
   regfree (&s_regex);
   /*---(finish)---------------------------------------*/
   rc = yvar_string_match (u_exp, u_act, s_mod);
   if (rc < 0)  rc = -('u');
   else         rc = 'u';
   yvar_string_fancy (u_act, s_mod, s_fact);
   /*---(complete)-------------------------------------*/
   return rc;
}

char
yVAR_results            (char *a_exp, char *a_act, char *a_mod, char *a_fexp, char *a_fact)
{
   if (a_exp  != NULL)  strcpy (a_exp , u_exp);
   if (a_act  != NULL)  strcpy (a_act , u_act);
   if (a_mod  != NULL)  strcpy (a_mod , s_mod);
   if (a_fexp != NULL)  strcpy (a_fexp, u_exp);
   if (a_fact != NULL)  strcpy (a_fact, s_fact);
   return 0;
}


