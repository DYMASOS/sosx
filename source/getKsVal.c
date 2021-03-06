
/******************************************************************************
 *
 *   FILE
 *   ----
 *   getKsVal.c
 *
 *   History
 *   -------
 *   2016-04-29   File created
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


OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_resetall(
		OV_INSTPTR_ov_domain	root
){

	OV_INSTPTR_ov_object	tmpObject	= NULL;
	OV_RESULT				result		= OV_ERR_OK;

	Ov_ForEachChild(ov_containment,root,tmpObject){
		if(Ov_CanCastTo(sosx_getKsVal,tmpObject)){

			sosx_getKsVal_doReset_set(Ov_DynamicPtrCast(sosx_getKsVal,tmpObject),FALSE);
			sosx_getKsVal_doReset_set(Ov_DynamicPtrCast(sosx_getKsVal,tmpObject),TRUE);
			sosx_getKsVal_doReset_set(Ov_DynamicPtrCast(sosx_getKsVal,tmpObject),FALSE);

		}
		else if(Ov_CanCastTo(ov_domain,tmpObject))
		{
			sosx_getKsVal_resetall(Ov_DynamicPtrCast(ov_domain,tmpObject));
		}
	}

	return result;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_resetwitherror(
		OV_INSTPTR_ov_domain	root
){

	OV_INSTPTR_ov_object	tmpObject	= NULL;
	OV_RESULT				result		= OV_ERR_OK;

	Ov_ForEachChild(ov_containment,root,tmpObject){
		if(Ov_CanCastTo(sosx_getKsVal,tmpObject) &&
				Ov_DynamicPtrCast(sosx_getKsVal,tmpObject)->v_ErrState > 2){

			sosx_getKsVal_doReset_set(Ov_DynamicPtrCast(sosx_getKsVal,tmpObject),FALSE);
			sosx_getKsVal_doReset_set(Ov_DynamicPtrCast(sosx_getKsVal,tmpObject),TRUE);
			sosx_getKsVal_doReset_set(Ov_DynamicPtrCast(sosx_getKsVal,tmpObject),FALSE);

		}
		else if(Ov_CanCastTo(ov_domain,tmpObject))
		{
			sosx_getKsVal_resetall(Ov_DynamicPtrCast(ov_domain,tmpObject));
		}
	}

	return result;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_startall(
		OV_INSTPTR_ov_domain	root,
		OV_INT					*count
){

	OV_INSTPTR_ov_object	tmpObject	= NULL;
	OV_INSTPTR_fb_task		pTmpTask	= NULL;
	OV_RESULT				result		= OV_ERR_OK;

	Ov_ForEachChild(ov_containment,root,tmpObject){
		if(Ov_CanCastTo(sosx_getKsVal,tmpObject)){
			pTmpTask = Ov_DynamicPtrCast(fb_task,tmpObject);
			fb_task_actimode_set(pTmpTask,1);
			pTmpTask->v_proctime.secs = pTmpTask->v_proctime.secs + *count;
			/* 5 seconds break between executing fb */
			(*count) = (*count) + 5;
		}
		else if(Ov_CanCastTo(ov_domain,tmpObject))
		{
			sosx_getKsVal_startall(Ov_DynamicPtrCast(ov_domain,tmpObject),count);
		}
	}
	return result;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_stopall(
		OV_INSTPTR_ov_domain	root
){

	OV_INSTPTR_ov_object	tmpObject	= NULL;
	OV_RESULT				result		= OV_ERR_OK;

	Ov_ForEachChild(ov_containment,root,tmpObject){
		if(Ov_CanCastTo(sosx_getKsVal,tmpObject)){
			fb_task_actimode_set(Ov_DynamicPtrCast(fb_task,tmpObject),0);
		}
		else if(Ov_CanCastTo(ov_domain,tmpObject))
		{
			sosx_getKsVal_stopall(Ov_DynamicPtrCast(ov_domain,tmpObject));
		}
	}

	return result;
}

OV_DLLFNCEXPORT OV_STRING sosx_getKsVal_host_get(
		OV_INSTPTR_sosx_getKsVal          pobj
) {
	return pobj->v_host;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_host_set(
		OV_INSTPTR_sosx_getKsVal          pobj,
		const OV_STRING  value
) {
	return ov_string_setvalue(&pobj->v_host,value);
}

OV_DLLFNCEXPORT OV_STRING sosx_getKsVal_server_get(
		OV_INSTPTR_sosx_getKsVal          pobj
) {
	return pobj->v_server;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_server_set(
		OV_INSTPTR_sosx_getKsVal          pobj,
		const OV_STRING  value
) {
	return ov_string_setvalue(&pobj->v_server,value);
}

OV_DLLFNCEXPORT OV_STRING sosx_getKsVal_path_get(
		OV_INSTPTR_sosx_getKsVal          pobj
) {
	return pobj->v_path;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_path_set(
		OV_INSTPTR_sosx_getKsVal          pobj,
		const OV_STRING  value
) {
	return ov_string_setvalue(&pobj->v_path,value);
}

OV_DLLFNCEXPORT OV_BOOL sosx_getKsVal_doReset_get(
		OV_INSTPTR_sosx_getKsVal          pobj
) {
	return pobj->v_doReset;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_doReset_set(
		OV_INSTPTR_sosx_getKsVal          pobj,
		const OV_BOOL  value
) {
	OV_INSTPTR_sosx_getVar 			getVar	 		= NULL;
	OV_INSTPTR_sosx_getHist			getHist	 		= NULL;
	OV_INSTPTR_ksxdrgethist_getHist	apigetHist	 	= NULL;
	OV_INSTPTR_ksapi_getVar 		ksapigetVar		= NULL;
	OV_VTBLPTR_ksbase_ClientBase	pVtblClient 	= NULL;
	OV_RESULT 						result 			= OV_ERR_OK;

	if(value && (!pobj->v_doReset))
	{
		pobj->v_doReset = TRUE;
		pobj->v_state = KSAPI_COMMON_INITIAL;
		pobj->v_errorCode = OV_ERR_OK;

		/***
		 * reset getVar
		 * 1. get object pointer
		 * 2. disable FB
		 * 3. reset API
		 */

		if(Ov_CanCastTo(sosx_getVar,pobj))
		{
			/* get object pointer */
			getVar = Ov_DynamicPtrCast(sosx_getVar,pobj);
			ksapigetVar = &getVar->p_apiGet;

			/*disable FB */
			result = fb_task_actimode_set(Ov_DynamicPtrCast(fb_task,pobj),0);
			if(Ov_Fail(result))
			{
				logfile_error("Could not disable the getVar task ",pobj->v_identifier);
				return result;
			}
		}

		/* reset api */
		ksapigetVar->v_Reset = TRUE;
		ksapigetVar->v_Reset = FALSE;

		/* reset ksapi_getVar*/
		/***
		 * reset getHistFb
		 * 1. get object pointer
		 * 2. disable FB
		 * 3. reset API
		 */

		if(Ov_CanCastTo(sosx_getHist,pobj))
		{
			ov_logfile_debug(" reseting %s", pobj->v_identifier);
			/* get object pointer */
			getHist = Ov_DynamicPtrCast(sosx_getHist,pobj);
			apigetHist = &getHist->p_apiHist;

			/* disable FB */
			result = fb_task_actimode_set(Ov_DynamicPtrCast(fb_task,pobj),0);
			if(Ov_Fail(result))
			{
				logfile_error("Could not disable the getHist task ",pobj->v_identifier);
				return result;
			}

			/* reset API*/
			Ov_GetVTablePtr(ksbase_ClientBase, pVtblClient, Ov_DynamicPtrCast(ksbase_ClientBase,apigetHist));
			if(pVtblClient)
			{
				result = pVtblClient->m_reset(Ov_DynamicPtrCast(ksbase_ClientBase,apigetHist));
			}
		}
	}
	pobj->v_doReset = FALSE;
	return result;
}

OV_DLLFNCEXPORT OV_INT sosx_getKsVal_state_get(
		OV_INSTPTR_sosx_getKsVal          pobj
) {
	return pobj->v_state;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_state_set(
		OV_INSTPTR_sosx_getKsVal          pobj,
		const OV_INT  value
) {
	OV_TIME_SPAN newCyctime = pobj->v_cyctimeMem;

	/* execute every second if in state FBCOMLIB_STATE_WAITING */
	if(value == FBCOMLIB_STATE_WAITING){
		/* store real cyctime in memory */
		newCyctime.secs = 1;
	}
	if(value == FBCOMLIB_STATE_OK){
		/* switch back to real cyctime  */
		if(pobj->v_cyctimeMem.secs - pobj->v_waitStateCount > 0){
			newCyctime.secs = pobj->v_cyctimeMem.secs - pobj->v_waitStateCount;
		}
	}

	pobj->v_waitStateCount = 0;

	fb_task_cyctime_set(Ov_DynamicPtrCast(fb_task,pobj),&newCyctime);
	pobj->v_state = value;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_getKsVal_constructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	OV_INSTPTR_sosx_getKsVal 	pinst		= Ov_StaticPtrCast(sosx_getKsVal, pobj);
	OV_INSTPTR_fb_task			pUrTask		= NULL;
	OV_RESULT    				result		= OV_ERR_OK;

	/* do what the base class does first */
	result = fb_functionblock_constructor(pobj);
	if(Ov_Fail(result))
		return result;

	pUrTask = Ov_DynamicPtrCast(fb_task,ov_path_getobjectpointer("/Tasks/UrTask",2));
	/* add to task list */
	result = Ov_Link(fb_tasklist,pUrTask,Ov_DynamicPtrCast(fb_task,pinst));

	return OV_ERR_OK;
}

OV_DLLFNCEXPORT void sosx_getKsVal_startup(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	//OV_INSTPTR_sosx_getKsVal pinst = Ov_StaticPtrCast(sosx_getKsVal, pobj);

	/* do what the base class does first */
	fb_functionblock_startup(pobj);

	/* do what */


	return;
}
