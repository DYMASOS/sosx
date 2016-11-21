
/******************************************************************************
 *
 *   FILE
 *   ----
 *   sosxdomain.c
 *
 *   History
 *   -------
 *   2015-05-22   File created
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
#include "sosxcommon.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_UINT sosx_sosxdomain_readStyle_get(
		OV_INSTPTR_sosx_sosxdomain          pobj
) {
	return pobj->v_readStyle;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxdomain_readStyle_set(
		OV_INSTPTR_sosx_sosxdomain          pobj,
		const OV_UINT  value
) {
	pobj->v_readStyle = value;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxdomain_includeInStateFile_set(
		OV_INSTPTR_sosx_sosxdomain          pobj,
		const OV_BOOL  value
) {
	pobj->v_includeInStateFile = value;
	if(value &&
			Ov_CanCastTo(sosx_sosxdomain,Ov_GetParent(ov_containment,pobj)) &&
			Ov_DynamicPtrCast(sosx_sosxdomain,Ov_GetParent(ov_containment,pobj))->v_includeInStateFile == FALSE){
		sosx_sosxdomain_includeInStateFile_set(Ov_DynamicPtrCast(sosx_sosxdomain,Ov_GetParent(ov_containment,pobj)),TRUE);
	}
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_STRING sosx_sosxdomain_caexLibrary_get(
		OV_INSTPTR_sosx_sosxdomain          pobj
) {
	return pobj->v_caexLibrary;
}

OV_DLLFNCEXPORT OV_UINT sosx_sosxdomain_xPos_get(
    OV_INSTPTR_sosx_sosxdomain          pobj
) {
    return pobj->v_xPos;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxdomain_xPos_set(
    OV_INSTPTR_sosx_sosxdomain          pobj,
    const OV_UINT  value
) {
    pobj->v_xPos = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_UINT sosx_sosxdomain_yPos_get(
    OV_INSTPTR_sosx_sosxdomain          pobj
) {
    return pobj->v_yPos;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxdomain_yPos_set(
    OV_INSTPTR_sosx_sosxdomain          pobj,
    const OV_UINT  value
) {
    pobj->v_yPos = value;
    return OV_ERR_OK;
}
/*sosx_sosxdomain_setCaexLibrary - This function sets the caexLibary of pobj to value and evaluates the caexLibrary
 * (instantiates the pobj children specified in the caexLibrary
 * @param pobj - sosx Element of type caexLibrary
 * @param pIE -
 * @param value - caexLibrary value
 * @return
 */
OV_DLLFNCEXPORT OV_RESULT sosx_sosxdomain_setCaexLibrary(
		OV_INSTPTR_sosx_sosxdomain			pobj,
		OV_INSTPTR_caex_CAEXBasicObject		pIE,
		const OV_STRING  					value
){
	OV_RESULT							result			= OV_ERR_OK;

	OV_INSTPTR_caex_CAEXObject			*pLibList		= NULL;
	OV_UINT								LenLibList		= 0;
	OV_INSTPTR_caex_InternalElement		pTempIE			= NULL;
	OV_INSTPTR_ov_domain				pCaex			= NULL;
	OV_STRING_VEC						pRefPathTokList	= {0,NULL};

	OV_INSTPTR_ov_domain				pTmpObj			= NULL;
	OV_INSTPTR_sosx_SoSContainer		pSoSContainer	= NULL;

	OV_STRING							tmpStr			= NULL;
	OV_STRING							AliasIE			= NULL;
	OV_STRING							PathIE			= NULL;
	OV_STRING							AliasSoSC		= NULL;
	OV_STRING							PathSoSC		= NULL;
	OV_BOOL								aliasFound		= FALSE;

#undef Finally
#define Finally()												\
		ov_string_setvalue(&tmpStr,NULL);						\
		ov_string_setvalue(&AliasIE,NULL);						\
		ov_string_setvalue(&PathIE,NULL);						\
		ov_string_setvalue(&PathSoSC,NULL);						\
		ov_string_setvalue(&AliasSoSC,NULL);					\
		if(pRefPathTokList.veclen > 0){							\
			ov_string_freelist(pRefPathTokList.value);			\
			pRefPathTokList.veclen = 0;}						\
		freeLibList(pLibList,LenLibList);						\




	/////////////////////////////* set attribute *////////////////////////////////////////
	result = ov_string_setvalue(&pobj->v_caexLibrary,value);
	if(Ov_Fail(result)){
		Finally();
		return result;
	}

	/////////////////////////* check if externalReference is stored in SoSCotainer *///////////////////
	/* find SoSContainer Object */
	pTmpObj = Ov_DynamicPtrCast(ov_domain,pobj);
	while(!Ov_CanCastTo(sosx_SoSContainer,pTmpObj)){
		pTmpObj = Ov_GetParent(ov_containment,pTmpObj);
	}
	pSoSContainer = Ov_DynamicPtrCast(sosx_SoSContainer,pTmpObj);

	/* get alias of library */
	ov_string_setvalue(&tmpStr,value);
	ov_string_setvalue(&AliasIE,strtok(tmpStr,"@"));
	ov_string_setvalue(&PathIE,strtok(NULL,"@"));
	ov_string_setvalue(&tmpStr,NULL);

	/* check if SoSContainer already knows the Alias */
	for(OV_UINT i = 0 ; i < pSoSContainer->v_externalReference.veclen ; i++){
		ov_string_setvalue(&tmpStr,pSoSContainer->v_externalReference.value[i]);
		ov_string_setvalue(&AliasSoSC,strtok(tmpStr,"@"));
		ov_string_setvalue(&PathSoSC,strtok(NULL,"@"));
		ov_string_setvalue(&tmpStr,NULL);
		if(ov_string_compare(AliasIE,AliasSoSC) == OV_STRCMP_EQUAL){
			aliasFound = TRUE;
			break;
		}
	}

	if(!aliasFound){
		/* new library needs to be added to the externalRefernce list */
		logfile_error("Cannot find the specified library. Please add the Library to the externalReference list.",value);
		return OV_ERR_GENERIC;
	}

	//////////////////////* Instantiate children of pobj specified in the caex library */////////////////////////
	/* get the LibraryList */
	if(pIE == NULL){

		/* find the library object defined by value */
		/* get the CAEX container */
		pCaex = (OV_INSTPTR_ov_domain)ov_path_getobjectpointer("/TechUnits/ImportExport/CAEX", 2);

		/* start searching in the CAEX domain */
		pTmpObj = pCaex;

		/* find library  follow PathSoSC */
		pRefPathTokList.value = ov_string_split(PathSoSC,"/",&pRefPathTokList.veclen);
		for (OV_UINT i = 1; i < pRefPathTokList.veclen; i++){
			if(Ov_SearchChild(ov_containment,pTmpObj,pRefPathTokList.value[i])){
				pTmpObj = Ov_DynamicPtrCast(ov_domain,Ov_SearchChild(ov_containment,pTmpObj,pRefPathTokList.value[i]));
			}else{
				logfile_error("Cannot find the Library",value);
				Finally();
				return OV_ERR_BADVALUE;
			}
		}

		Ov_SetDynamicVectorLength(&pRefPathTokList,0,STRING);

		/* find class within the library */
		pRefPathTokList.value = ov_string_split(PathIE,"/",&pRefPathTokList.veclen);
		for (OV_UINT i = 0; i < pRefPathTokList.veclen; i++){
			if(Ov_SearchChild(ov_containment,pTmpObj,pRefPathTokList.value[i])){
				pTmpObj = Ov_DynamicPtrCast(ov_domain,Ov_SearchChild(ov_containment,pTmpObj,pRefPathTokList.value[i]));
			}else{
				logfile_error("Cannot find the class with in the Library",value);
				Finally();
				return OV_ERR_BADVALUE;
			}
		}
		pIE = Ov_DynamicPtrCast(caex_CAEXBasicObject,pTmpObj);
	}

	if(pIE == NULL){
		Finally();
		return result;
	}

	/* get the libraryList of this object */
	result = sosx_workflowManagement_getLibraryList(pIE,&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pIE->v_identifier);
		Finally();
		return result;
	}

	/* Instantiate children according to libraryList */
	for (OV_UINT u = 1 ; u < LenLibList ; u++){
		Ov_ForEachChildEx(ov_containment,pLibList[u],pTempIE,caex_InternalElement){
			/* check if child already exists from previous loop through libraryList*/
			if(Ov_SearchChild(ov_containment,pobj,pTempIE->v_Name) == NULL){
				/* child does not exist -> create*/
				result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pobj),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempIE));
				if(Ov_Fail(result)){
					break;
				}
			}else{
				/* child exists -> update*/
				result = sosx_workflowManagement_updateElement(Ov_DynamicPtrCast(ov_domain,Ov_SearchChild(ov_containment,pobj,pTempIE->v_Name)),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempIE),SOSX_UPDATE_COMPLETE);
				if(Ov_Fail(result)){
					break;
				}
			}
		}
	}
	Finally();
	return result;
}

OV_DLLFNCEXPORT OV_UINT sosx_sosxdomain_isValid_get(
		OV_INSTPTR_sosx_sosxdomain          pobj
) {
	return pobj->v_isValid;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxdomain_isValid_set(
		OV_INSTPTR_sosx_sosxdomain          pobj,
		const OV_UINT  value
) {
	OV_UINT internalValue	= 0;

	internalValue = max_uint(value,pobj->v_isValid);

	if (pobj->v_isValid != internalValue){
		if(Ov_CanCastTo(sosx_sosxdomain,Ov_GetParent(ov_containment,pobj))){
			sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,Ov_GetParent(ov_containment,pobj)),value);
		}
	}

	pobj->v_isValid = internalValue;
	return OV_ERR_OK;
}

/**
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_sosxdomain_restIsValidIfValueChanged(
		OV_INSTPTR_sosx_sosxdomain		pobj
){
	OV_RESULT 			result	= OV_ERR_OK;

	pobj->v_isValid = 0;
	return result;
}

OV_DLLFNCEXPORT OV_ACCESS sosx_sosxdomain_getaccess(
		OV_INSTPTR_ov_object	pobj,
		const OV_ELEMENT		*pelem,
		const OV_TICKET			*pticket
) {

	/*
	 *	switch based on the element's type
	 */
	switch(pelem->elemtype) {
	case OV_ET_VARIABLE:
		if(pelem->elemunion.pvar->v_offset >= offsetof(OV_INST_ov_object,__classinfo)) {
			if(pelem->elemunion.pvar->v_vartype == OV_VT_CTYPE)
				return OV_AC_NONE;
			else
				return OV_AC_READWRITE;
		}
		break;
	default:
		break;
	}
	return ov_object_getaccess(pobj, pelem, pticket);
}

OV_DLLFNCEXPORT void sosx_sosxdomain_destructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	// OV_INSTPTR_sosx_sosxdomain pinst = Ov_StaticPtrCast(sosx_sosxdomain, pobj);

	/* do what */

	/* destroy object */
	ov_object_destructor(pobj);

	return;
}
