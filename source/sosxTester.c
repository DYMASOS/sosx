
/******************************************************************************
 *
 *   FILE
 *   ----
 *   sosxTester.c
 *
 *   History
 *   -------
 *   2014-11-14   File created
 *
 *******************************************************************************
 *
 *   This file is generated by the 'acplt_builder' command
 *
 ******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_sosx
#define OV_COMPILE_LIBRARY_sosx
#endif

#define FINALLY


#include "sosx.h"
#include "libov/ov_macros.h"
#include "caex.h"
#include "sosxcommon.h"


OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_constructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	// OV_INSTPTR_sosx_sosxTester pinst = Ov_StaticPtrCast(sosx_sosxTester, pobj);
	OV_RESULT    result;

	/* do what the base class does first */
	result = ov_object_constructor(pobj);
	if(Ov_Fail(result))
		return result;

	/* do what */


	return OV_ERR_OK;
}

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

OV_DLLFNCEXPORT OV_BOOL sosx_sosxTester_startTest_get(
		OV_INSTPTR_sosx_sosxTester          pobj
) {
	return pobj->v_startTest;
}

OV_DLLFNCEXPORT OV_RESULT sosx_sosxTester_startTest_set(
		OV_INSTPTR_sosx_sosxTester          pobj,
		const OV_BOOL  value
) {
	OV_STRING								*pPathToSourceList	= NULL;
	OV_UINT									LenPathToSourceList	= 0;
	OV_INT									count				= 0;
	OV_STRING								*pPathToTargetList	= NULL;
	OV_UINT									LenPathToTargetList	= 0;
	OV_INSTPTR_ov_domain					pImportExport		= NULL;
	OV_INSTPTR_ov_domain					pCAEX				= NULL;
	OV_INSTPTR_ov_domain					pTemp				= NULL;
	OV_INSTPTR_ov_domain					pSource				= NULL;
	OV_INSTPTR_ov_domain					pSOSX				= NULL;
	OV_INSTPTR_ov_domain					pTarget				= NULL;
	OV_INSTPTR_caex_InternalElement			pTempCaex			= NULL;
	OV_INSTPTR_sosx_System					pSystem				= NULL;
	OV_STRING								tmpstr				= NULL;
	OV_STRING_VEC							ValidationLog		= {0,NULL};

	OV_RESULT								result				= OV_ERR_OK;

#define Finally() 									\
		ov_string_setvalue(&tmpstr,NULL); 			\
		ov_string_freelist(pPathToSourceList); 		\
		ov_string_freelist(pPathToTargetList); 		\
		ov_string_freelist(ValidationLog.value); 	\
		pobj->v_startTest = FALSE;					\


	pobj->v_startTest = value;

	if (pobj->v_startTest == TRUE){

		if(ov_string_compare(pobj->v_Do,"create")		!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"update")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"updateSimRes")==OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"reset")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"start")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"stop")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"delete")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"read")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"load")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"export")	!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"validate")!= OV_STRCMP_EQUAL &&
				ov_string_compare(pobj->v_Do,"test")	!= OV_STRCMP_EQUAL){
			log_error("Wrong 'Do' command! Please use 'create', 'read', 'update' 'delete' or 'validate'");
			Finally();
			return OV_ERR_GENERIC;
		}
		/********************************************
		 * Search for CAEX Files
		 ********************************************/

		/* find ImportExport container */
		pImportExport	= (OV_INSTPTR_ov_domain)ov_path_getobjectpointer("/TechUnits/ImportExport", 2);
		if (!(pImportExport)){
			log_error("Cannot find domain 'ImportExport'");
			Finally();
			return OV_ERR_GENERIC;
		}

		/* find caex container */
		pCAEX  = (OV_INSTPTR_ov_domain)ov_path_getobjectpointer("/TechUnits/ImportExport/CAEX", 2);
		if (!(pCAEX)){
			log_error("Cannot find domain 'CAEX'");
			Finally();
			return OV_ERR_GENERIC;
		}
		/* find sosx container */
		pSOSX = (OV_INSTPTR_ov_domain)ov_path_getobjectpointer("/TechUnits/sosx", 2);
		if ((pSOSX == NULL)){
			log_error("Cannot find domain sosx. Please create Instanz-Container 'TechUnits/sosx'");
			Finally();
			return OV_ERR_GENERIC;
		}


		/*
		 * case: create, delete or update
		 */
		if(ov_string_compare(pobj->v_Do,"create")==OV_STRCMP_EQUAL ||
				ov_string_compare(pobj->v_Do,"update")==OV_STRCMP_EQUAL ||
				ov_string_compare(pobj->v_Do,"updateSimRes")==OV_STRCMP_EQUAL ||
				ov_string_compare(pobj->v_Do,"delete")==OV_STRCMP_EQUAL ||
				ov_string_compare(pobj->v_Do,"validate")==OV_STRCMP_EQUAL||
				ov_string_compare(pobj->v_Do,"start")==OV_STRCMP_EQUAL||
				ov_string_compare(pobj->v_Do,"stop")==OV_STRCMP_EQUAL||
				ov_string_compare(pobj->v_Do,"reset")==OV_STRCMP_EQUAL){
			/* get Source pointer for create or update */

			/* find/follow SourcePath*/
			pPathToSourceList = ov_string_split(pobj->v_Source,"/",&LenPathToSourceList);
			pTemp = pCAEX;
			for (OV_UINT u = 0; u < LenPathToSourceList; u++){
				pTemp = Ov_SearchChildEx(ov_containment,pTemp,pPathToSourceList[u],ov_domain);
				if(pTemp == NULL){
					log_error("Cannot find the Source");
					Finally();
					return OV_ERR_GENERIC;
				}
			}
			/* save source pointer*/
			pSource = pTemp;
			pTemp = NULL;
			pTempCaex = NULL;

			/* find target element within an existing sosx structure*/
			pPathToTargetList = ov_string_split(pobj->v_Target,"/",&LenPathToTargetList);
			pTemp = pSOSX;
			for (OV_UINT u = 0; u < LenPathToTargetList; u++){
				pTemp = Ov_SearchChildEx(ov_containment,pTemp,pPathToTargetList[u],ov_domain);
				if(pTemp == NULL){
					log_error("Cannot find the Target");
					Finally();
					return OV_ERR_GENERIC;
				}
			}
			pTarget = pTemp;
			pTemp = NULL;
		}
		if(ov_string_compare(pobj->v_Do,"create")==OV_STRCMP_EQUAL){
			result = sosx_workflowManagement_createElement(pTarget,Ov_DynamicPtrCast(caex_CAEXBasicObject,pSource));
			pobj->v_startTest = FALSE;
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"update")==OV_STRCMP_EQUAL){
			result = sosx_workflowManagement_updateElement(pTarget,Ov_DynamicPtrCast(caex_CAEXBasicObject,pSource),SOSX_UPDATE_COMPLETE);
			pobj->v_startTest = FALSE;
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"updateSimRes")==OV_STRCMP_EQUAL){
			result = sosx_workflowManagement_updateElement(pTarget,Ov_DynamicPtrCast(caex_CAEXBasicObject,pSource),SOSX_UPDATE_SIMRESONLY);
			pobj->v_startTest = FALSE;
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"delete")==OV_STRCMP_EQUAL){
			result = sosx_workflowManagement_deleteElement(pTarget);
			pTemp = NULL;
			pobj->v_startTest = FALSE;
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"validate")==OV_STRCMP_EQUAL){
			result = sosx_workflowManagement_validateElement(pTarget,&ValidationLog);
			pobj->v_startTest = FALSE;
			/* print validation log */
			log_info("printing validation log");
			for(OV_UINT i = 0 ; i < ValidationLog.veclen ; i = i+3){
				for(OV_UINT j = 0 ; j < 3 ; j++){
					if(j == 0){
						ov_string_setvalue(&tmpstr,ValidationLog.value[i]);
					} else {
						ov_string_append(&tmpstr," - ");
						ov_string_append(&tmpstr,ValidationLog.value[i+j]);
					}
				}
				log_info(tmpstr);
			}
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"reset")==OV_STRCMP_EQUAL){
			result = sosx_getKsVal_resetall(pTarget);
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"start")==OV_STRCMP_EQUAL){
			result = sosx_getKsVal_startall(pTarget,&count);
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"stop")==OV_STRCMP_EQUAL){
			result = sosx_getKsVal_stopall(pTarget);
			Finally();
			return result;
		}
		if(ov_string_compare(pobj->v_Do,"read")==OV_STRCMP_EQUAL){

			/* find the element to be read */
			pPathToSourceList = ov_string_split(pobj->v_Source,"/",&LenPathToSourceList);
			pTemp = pSOSX;
			for (OV_UINT u = 0; u < LenPathToSourceList; u++){
				pTemp = Ov_SearchChildEx(ov_containment,pTemp,pPathToSourceList[u],ov_domain);
				if(pTemp == NULL){
					log_error("Cannot find the Source");
					Finally();
					return OV_ERR_GENERIC;
				}
			}
			pSource = pTemp;
			pTemp = NULL;

			/* find the target for the export */
			pPathToTargetList = ov_string_split(pobj->v_Target,"/",&LenPathToTargetList);
			pTemp = pCAEX;
			for (OV_UINT u = 0; u < LenPathToTargetList; u++){
				pTemp = Ov_SearchChildEx(ov_containment,pTemp,pPathToTargetList[u],ov_domain);
				if(pTemp == NULL){
					log_error("Cannot find the Target");
					Finally();
					return OV_ERR_GENERIC;
				}
			}
			pTarget = pTemp;
			pTemp = NULL;

			result = sosx_workflowManagement_readElement(pSource,pTarget,TRUE,NULL,FALSE);


			Finally();
			return result;

		}

		if(ov_string_compare(pobj->v_Do,"export")==OV_STRCMP_EQUAL){

			/* find the element to be read */
			pPathToSourceList = ov_string_split(pobj->v_Source,"/",&LenPathToSourceList);
			pTemp = pSOSX;
			for (OV_UINT u = 0; u < LenPathToSourceList; u++){
				pTemp = Ov_SearchChildEx(ov_containment,pTemp,pPathToSourceList[u],ov_domain);
				if(pTemp == NULL){
					log_error("Cannot find the Source");
					Finally();
					return OV_ERR_GENERIC;
				}
			}
			pSource = pTemp;
			pTemp = NULL;
			result = sosx_workflowManagement_exportCaexFile(pSource,pobj->v_Target,NULL,FALSE);

			Finally();
			return result;

		}

		if(ov_string_compare(pobj->v_Do,"load")==OV_STRCMP_EQUAL){
			sosx_workflowManagement_importCaexFile(pobj->v_Source,pobj->v_FileList);
		}

		if(ov_string_compare(pobj->v_Do,"test")==OV_STRCMP_EQUAL){

			Ov_CreateObject(sosx_System,pSystem,pSOSX,"TestSystem");
			pSystem = NULL;
			Ov_CreateObject(sosx_System,pSystem,pSOSX,"TestSystem");
			log_info(pSystem->v_identifier);
		}
	}
	Finally();
	return result;
}

