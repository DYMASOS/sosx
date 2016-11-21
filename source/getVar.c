
/******************************************************************************
 *
 *   FILE
 *   ----
 *   getVar.c
 *
 *   History
 *   -------
 *   2015-05-11   File created
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
#include "libov/ov_path.h"
#include "sosxcommon.h"
#include "ksapi_commonFuncs.h"
#include "config.h" /* fbcomlib*/



OV_DLLFNCEXPORT OV_ANY* sosx_getVar_receivedVar_get(
		OV_INSTPTR_sosx_getVar          pobj
) {
	return &pobj->v_receivedVar;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getVar_receivedVar_set(
		OV_INSTPTR_sosx_getVar          pobj,
		const OV_ANY*  value
) {
	OV_RESULT 								result		= OV_ERR_OK;
	OV_INSTPTR_sosx_PropertyInformation		pPropInfo 	= NULL;


	/* store value */
	result =  ov_variable_setanyvalue(&pobj->v_receivedVar,value);
	if(Ov_Fail(result)){
		return result;
	}

	/* pass the value to the PropertyInformation */

	pPropInfo = Ov_DynamicPtrCast(sosx_PropertyInformation,Ov_GetParent(ov_containment,pobj));
	if(pPropInfo == NULL){
		logfile_error("Could not get the PropertyInformation",pobj->v_identifier);
		return result;
	}

	/* set PropertyInformation value */
	result = sosx_PropertyInformation_value_set(pPropInfo,value);
	if(Ov_Fail(result)){
		return result;
	}

	return result;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getVar_constructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	OV_INSTPTR_sosx_getVar 		pinst 		= Ov_StaticPtrCast(sosx_getVar, pobj);
	OV_RESULT    				result		= OV_ERR_OK;

#undef Finally
#define Finally()

	/* do what the base class does first */
	result = sosx_getKsVal_constructor(pobj);
	if(Ov_Fail(result)){
		return result;
	}

	pinst->v_receivedVar.value.vartype = OV_VT_VOID;
	pinst->v_receivedVar.value.valueunion.val_double = 0.0;

	return result;
}

OV_DLLFNCEXPORT void sosx_getVar_startup(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	// OV_INSTPTR_sosx_getVar pinst = Ov_StaticPtrCast(sosx_getVar, pobj);

	/* do what the base class does first */
	fb_functionblock_startup(pobj);

	/* do what */


	return;
}

OV_DLLFNCEXPORT void sosx_getVar_typemethod(
		OV_INSTPTR_fb_functionblock	pfb,
		OV_TIME						*pltc
) {
	/*
	 *   local variables
	 */
	OV_INSTPTR_sosx_getVar 		pinstGetVar		= Ov_StaticPtrCast(sosx_getVar, pfb);
	OV_INSTPTR_ov_domain		pPropertyInfo	= Ov_GetParent(ov_containment,pfb);
	OV_INSTPTR_sosx_getKsVal 	pinst			= Ov_StaticPtrCast(sosx_getKsVal, pfb);
	OV_VTBLPTR_ksapi_getVar 	pVtblGetVar 	= (OV_VTBLPTR_ksapi_getVar) pclass_ksapi_getVar->v_pvtable;
	OV_ANY						varValue		= {};
	OV_RESULT 					result			= OV_ERR_OK;


	if(pinst->v_state == FBCOMLIB_STATE_WAITING)
	{	/*	waiting: calculate timeouts and check ksapi-object for answer	*/
		/* count seconds in state waiting */
		pinstGetVar->v_waitStateCount++;
		if(pinstGetVar->p_apiGet.v_status == KSAPI_COMMON_REQUESTCOMPLETED)
		{	/*	ksapi-request completed --> get answer	*/
			pinst->v_opResult = pinstGetVar->p_apiGet.v_result;
			pinst->v_varResult = pinstGetVar->p_apiGet.v_varRes;
			Ov_SetAnyValue(&varValue,&(pinstGetVar->p_apiGet.v_varValue));
			varValue.time = *pltc;
			result = sosx_getVar_receivedVar_set(pinstGetVar, &varValue);
			Ov_SetAnyValue(&varValue,NULL);
			if(Ov_OK(result)){
				sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_OK);
			return;
			} else {
				sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_INTERNAL_ERROR);
				pinst->v_errorCode = result;
				logfile_error("getVar failed (InternalError)",pPropertyInfo->v_identifier);
				return;
			}
			pinst->v_errorCode = OV_ERR_OK;
		}
		else if(pinstGetVar->p_apiGet.v_status == KSAPI_COMMON_INTERNALERROR)
		{
			sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_KSAPI_ERROR);
			pinst->v_errorCode = pinstGetVar->p_apiGet.v_result;
			logfile_error("getVar failed (KSAPI_Error)",pPropertyInfo->v_identifier);
			return;
		}
		else if(pinstGetVar->p_apiGet.v_status == KSAPI_COMMON_EXTERNALERROR)
		{
			sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_EXTERNAL_ERROR);
			pinst->v_errorCode = OV_ERR_GENERIC;
			logfile_error("getVar failed (EXTERNAL_ERROR)",pPropertyInfo->v_identifier);
			return;
		}
		else if(pinstGetVar->p_apiGet.v_status == KSAPI_COMMON_WAITINGFORANSWER)
		{
			if(pltc->secs > (pinst->v_requestSendTime.secs + pinst->v_timeout))
			{
				sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_TIMEOUT);
				logfile_error("getVar failed (TIMEOUT)",pPropertyInfo->v_identifier);
				return;
			}
		}
	}

	if((pinst->v_state == FBCOMLIB_STATE_OK) || (pinst->v_state == FBCOMLIB_STATE_INIT))
	{	/*	ready to start	*/
		/*	ksapi-object found	*/
		if(pinst->v_sendRequested)
		{	/*	single send requested	*/
			result = ov_string_setvalue(&(pinstGetVar->p_apiGet.v_serverHost), pinst->v_host);
			if(Ov_Fail(result))
			{
				pinst->v_errorCode = result;
				sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_INTERNAL_ERROR);
				logfile_error("getVar failed (InternalError I)",pPropertyInfo->v_identifier);
				return;
			}
			result = ov_string_setvalue(&(pinstGetVar->p_apiGet.v_serverName), pinst->v_server);
			if(Ov_Fail(result))
			{
				pinst->v_errorCode = result;
				sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_INTERNAL_ERROR);
				logfile_error("getVar failed (InternalError II)",pPropertyInfo->v_identifier);
				return;
			}
			result = ov_string_setvalue(&(pinstGetVar->p_apiGet.v_path), pinst->v_path);
			if(Ov_Fail(result))
			{
				pinst->v_errorCode = result;
				sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_INTERNAL_ERROR);
				logfile_error("getVar failed (InternalError III)",pPropertyInfo->v_identifier);
				return;
			}
		}

		pinstGetVar->p_apiGet.v_holdConnection = TRUE;

		/*	send Requested */
		pVtblGetVar->m_submit(Ov_StaticPtrCast(ksapi_KSApiCommon, &(pinstGetVar->p_apiGet)));

		sosx_getKsVal_state_set(pinst, FBCOMLIB_STATE_WAITING);

		pinst->v_requestSendTime = *pltc;
		pinst->v_sendRequested = FALSE;
		return;
	}
	else if(pinst->v_state != FBCOMLIB_STATE_WRONGINPUT)
	{
		if(pinst->v_retryAfter)
		{
			if(pltc->secs > (pinst->v_requestSendTime.secs + pinst->v_retryAfter))
			{
				if(pinst->v_doReset){
					sosx_getKsVal_doReset_set(pinst, FALSE);
					sosx_getKsVal_doReset_set(pinst, TRUE);
					sosx_getKsVal_doReset_set(pinst, FALSE);
				}
			}
		}
	}
	return;
}
