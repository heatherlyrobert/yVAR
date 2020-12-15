/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"



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
