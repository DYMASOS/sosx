
/******************************************************************************
*
*   FILE
*   ----
*   DetailedElement.c
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


OV_DLLFNCEXPORT OV_STRING sosx_DetailedElement_name_get(
    OV_INSTPTR_sosx_DetailedElement          pobj
) {
    return pobj->v_name;
}

OV_DLLFNCEXPORT OV_RESULT sosx_DetailedElement_name_set(
    OV_INSTPTR_sosx_DetailedElement          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_name,value);
}

