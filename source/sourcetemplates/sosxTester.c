
/******************************************************************************
*
*   FILE
*   ----
*   sosxTester.c
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


OV_DLLFNCEXPORT OV_STRING sosx_sosxTester_Source_get(
    OV_INSTPTR_sosx_sosxTester          pobj
) {
    return pobj->v_Source;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_Source_set(
    OV_INSTPTR_sosx_sosxTester          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_Source,value);
}

OV_DLLFNCEXPORT OV_STRING sosx_sosxTester_Target_get(
    OV_INSTPTR_sosx_sosxTester          pobj
) {
    return pobj->v_Target;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_Target_set(
    OV_INSTPTR_sosx_sosxTester          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_Target,value);
}

OV_DLLFNCEXPORT OV_STRING* sosx_sosxTester_FileList_get(
    OV_INSTPTR_sosx_sosxTester          pobj,
    OV_UINT *pveclen
) {
    *pveclen = pobj->v_FileList.veclen;
    return pobj->v_FileList.value;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_FileList_set(
    OV_INSTPTR_sosx_sosxTester          pobj,
    const OV_STRING*  value,
    const OV_UINT veclen
) {
    return Ov_SetDynamicVectorValue(&pobj->v_FileList,value,veclen,STRING);
}

OV_DLLFNCEXPORT OV_STRING sosx_sosxTester_Do_get(
    OV_INSTPTR_sosx_sosxTester          pobj
) {
    return pobj->v_Do;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_Do_set(
    OV_INSTPTR_sosx_sosxTester          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_Do,value);
}

OV_DLLFNCEXPORT OV_BOOL sosx_sosxTester_startTest_get(
    OV_INSTPTR_sosx_sosxTester          pobj
) {
    return pobj->v_startTest;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_startTest_set(
    OV_INSTPTR_sosx_sosxTester          pobj,
    const OV_BOOL  value
) {
    pobj->v_startTest = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_sosx_sosxTester pinst = Ov_StaticPtrCast(sosx_sosxTester, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = ov_object_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

