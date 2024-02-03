/*===[[ START ]]==============================================================*/
#include "yVAR.h"
#include "yVAR_priv.h"


tLOCAL    myVAR;
char        unit_answer [LEN_RECD];



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
   snprintf (yVAR_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yVAR_ver;
}

char         /*--> set debugging mode --------------------[ ------ [ ------ ]-*/
yVAR_debug         (char a_flag)
{
   /*---(set debug flag)-----------------*/
   if   (a_flag == 'y')  myVAR.debug   = 'y';
   else                  myVAR.debug   = '-';
   /*---(complete)-----------------------*/
   return 0;
}
