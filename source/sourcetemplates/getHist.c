
/******************************************************************************
*
*   FILE
*   ----
*   getHist.c
*
*   History
*   -------
*   2016-08-10   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_sosx
#define OV_COMPILE_LIBRARY_sosx
#endif


#include "sosx.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT sosx_getHist_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_sosx_getHist pinst = Ov_StaticPtrCast(sosx_getHist, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = sosx_getKsVal_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

OV_DLLFNCEXPORT void sosx_getHist_startup(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_sosx_getHist pinst = Ov_StaticPtrCast(sosx_getHist, pobj);

    /* do what the base class does first */
    sosx_getKsVal_startup(pobj);

    /* do what */


    return;
}

OV_DLLFNCEXPORT void sosx_getHist_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_sosx_getHist pinst = Ov_StaticPtrCast(sosx_getHist, pfb);

    return;
}

