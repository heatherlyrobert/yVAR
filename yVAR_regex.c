/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"



/*====================------------------------------------====================*/
/*===----                         regex testing                        ----===*/
/*====================------------------------------------====================*/
static void      o___REGEX___________________o (void) {;}

char       /*----: standard regex pattern testing ----------------------------*/
yVAR_regex         (char a_test [LEN_TERSE], char a_regex [LEN_RECD], char a_actual [LEN_RECD])
{
   /*-----------------------------------------------functional-design-notes---#
    * *> excellent way to get the best regex format testers in one place
    * *> single point of testing and maintenance
    * *> absolutely vital to increasing "cracker resistence" through easy use
    * *> speeds up app-dev and reduces testing time and concerns
    */
   char       its_regex [100];                /* source regex                 */
   int        its_code   =  10;               /* failure identifier           */
   /* big rule :: avoid the metacharacters `'\"|*?~<>^()[]{}$\n\r */
   /*===(sub-sets)================================================*/
   if      (strcmp (a_test, "x_lower")   == 0)   strcpy (its_regex, "^[a-z]+$");
   else if (strcmp (a_test, "x_upper")   == 0)   strcpy (its_regex, "^[A-Z]+$");
   else if (strcmp (a_test, "x_digit")   == 0)   strcpy (its_regex, "^[0-9]+$");
   else if (strcmp (a_test, "x_greek")   == 0)   strcpy (its_regex, "^[è-ÿ]+$");
   else if (strcmp (a_test, "x_alpha")   == 0)   strcpy (its_regex, "^[a-zA-Z]+$");
   else if (strcmp (a_test, "x_alnum")   == 0)   strcpy (its_regex, "^[a-zA-Z0-9]+$");
   /*===(string tests)============================================*/
   else if (strcmp (a_test, "x_basic")   == 0)   strcpy (its_regex, "^[A-Za-z0-9][a-zA-Z0-9_ -]*$");
   else if (strcmp (a_test, "x_write")   == 0)   strcpy (its_regex, "^[A-Za-z0-9][A-Za-z0-9_ .,:;!?-]*$");
   else if (strcmp (a_test, "x_exten")   == 0)   strcpy (its_regex, "^[A-Za-z0-9][A-Za-z0-9_ .,:;@()-]*$");
   /*===(cgi-post tests)=======================================*/
   else if (strcmp (a_test, "x_pfield")  == 0)   strcpy (its_regex, "^[a-z][a-z0-9_]{0,10}[a-z0-9]$");
   else if (strcmp (a_test, "x_pstring") == 0)   strcpy (its_regex, "^[A-Za-z0-9][A-Za-z0-9+=&%][A-Za-z0-9]*$");
   else if (strcmp (a_test, "x_ip")      == 0)   strcpy (its_regex,
            "^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
            ".(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
            ".(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
            ".(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$");
   else if (strcmp (a_test, "x_email")   == 0)   strcpy (its_regex, "^[A-Za-z0-9_.-]+[@][A-Za-z0-9_.-]+.[A-Za-z]{2,4}$");
   /*===(integers)=============================================*/
   else if (strcmp (a_test, "x_byte")    == 0)   strcpy (its_regex, "^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$");
   else if (strcmp (a_test, "x_uint")    == 0)   strcpy (its_regex, "^(0|[1-9][0-9]*)$");
   else if (strcmp (a_test, "x_sint")    == 0)   strcpy (its_regex, "^(-)?(0|[1-9][0-9]*)$");
   else if (strcmp (a_test, "x_bin")     == 0)   strcpy (its_regex, "^(b|é|0b)?[01]*$");
   else if (strcmp (a_test, "x_binplus") == 0)   strcpy (its_regex, "^(b|é|0b)?[01'+-Ï]*$");
   else if (strcmp (a_test, "x_octal")   == 0)   strcpy (its_regex, "^(o|ö|0o|0)[0-7]*$");
   else if (strcmp (a_test, "x_hex")     == 0)   strcpy (its_regex, "^(x|õ|0x)?[0-9a-fA-F]*$");
   else if (strcmp (a_test, "x_float")   == 0)   strcpy (its_regex, "^(-)?(0|[1-9][0-9]*)([.][0-9]+)?$");
   else if (strcmp (a_test, "x_pct")     == 0)   strcpy (its_regex, "^(-)?(100|[1-9]?[0-9]([.][0-9]{1,2})?)[%]?$");
   /*===(addresses of various sorts)===========================*/
   else if (strcmp (a_test, "x_dir")     == 0)   strcpy (its_regex, "^[/]?[A-Za-z][A-Za-z0-9_./-]$");
   else if (strcmp (a_test, "x_file")    == 0)   strcpy (its_regex, "^[.]?[A-Za-z][A-Za-z0-9_.-]{0,62}[A-Za-z0-9]$");
   else if (strcmp (a_test, "x_phone")   == 0)   strcpy (its_regex, "^([(]?[2-9][0-9]{2}[)]?[-. ])?[0-9]{3}[-. ][0-9]{4}$");
   else if (strcmp (a_test, "x_zip")     == 0)   strcpy (its_regex, "^[1-9][0-9]{4}([-][0-9]{4})?$");
   /*===(program element naming)===============================*/
   else if (strcmp (a_test, "x_var")     == 0)   strcpy (its_regex, "^(_)*[a-zA-Z][a-zA-Z0-9_]*$");
   else if (strcmp (a_test, "x_myvar")   == 0)   strcpy (its_regex, "^([a-z]|[a-z][a-z0-9_]*[a-z0-9])$");
   else if (strcmp (a_test, "x_myconst") == 0)   strcpy (its_regex, "^[A-Z][A-Z0-9_]*$");
   else if (strcmp (a_test, "x_func")    == 0)   strcpy (its_regex, "^[a-z_][a-zA-Z0-9_]*[a-zA-Z0-9]$");
   /*===(linux specific)=======================================*/
   else if (strcmp(a_test, "x_path")     == 0)   strcpy (its_regex, "^[\/][\/a-zA-Z0-9_.-]*$");
   else if (strcmp(a_test, "x_mypath")   == 0)   strcpy (its_regex, "^[\/][\/a-zA-Z0-9_.]*$");
   else  its_code = 0;
   /*===(archive related)======================================*/
   /*> else if (strcmp(a_test, "arch_prefix")    == 0) {                              <* 
    *>    /+-> role and goal                                          +/              <* 
    *>    strcpy(its_regex, "^[1-9][a-z]$");                                          <* 
    *>    its_code   = 51;                                                            <* 
    *> }                                                                              <*/
   /*> else if (strcmp(a_test, "arch_index")    == 0) {                               <* 
    *>    /+-> role and goal                                          +/              <* 
    *>    strcpy(its_regex, "^[1-9][a-z][-][1-9][0-9][0-9]$");                        <* 
    *>    its_code   = 52;                                                            <* 
    *> }                                                                              <*/
   /*> else if (strcmp(a_test, "arch_desc")    == 0) {                                <* 
    *>    /+-> role and goal                                           +/             <* 
    *>    strcpy(its_regex, "^[A-Za-z][A-Za-z0-9_-]*[A-Za-z0-9]$");                   <* 
    *>    its_code   = 53;                                                            <* 
    *> }                                                                              <*/
   /*===(run it)===========================================*/
   if (its_code > 0) {
      /*---(compile the regex)-----------------------------*/
      int       x_rc = 0;
      regex_t   x_comp;
      x_rc    = regcomp(&x_comp, its_regex, REG_EXTENDED);
      if (x_rc != 0) its_code = -2;  /* could not compile successfully  */
      if (its_code > 0) {
         /*---(conduct test)--------------------------------*/
         x_rc    = regexec(&x_comp, a_actual, 0, NULL, 0);
         if (x_rc != 0) its_code = -(its_code);   /* identify the failure */
      }
      regfree(&x_comp);
   }
   /*---(complete)------------------------------*/
   return its_code;                            /* identify success     */
}

char yVAR_regexs  (char a_test [LEN_TERSE], char a_actual [LEN_RECD]) { return yVAR_regex (a_test, "", a_actual); }


