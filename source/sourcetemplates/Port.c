
/******************************************************************************
*
*   FILE
*   ----
*   Port.c
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


OV_DLLFNCEXPORT OV_UINT sosx_Port_portType_get(
    OV_INSTPTR_sosx_Port          pobj
) {
    return pobj->v_portType;
}

OV_DLLFNCEXPORT OV_RESULT sosx_Port_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_sosx_Port pinst = Ov_StaticPtrCast(sosx_Port, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = sosx_StreamHandler_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}
