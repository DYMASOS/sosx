#ifndef OV_COMPILE_LIBRARY_sosx
#define OV_COMPILE_LIBRARY_sosx


#include "sosxcommon.h"

OV_UINT max_uint(OV_UINT a, OV_UINT b
){
	return(a>b?a:b);
}

OV_RESULT createExportName(
		OV_STRING		sosxName,
		OV_STRING		*ExportName,
		OV_TIME			*time
){

	OV_RESULT  			result		= OV_ERR_OK;
	OV_STRING_VEC		tmpStrVec	= {0,NULL};
	OV_STRING			tmpstr		= NULL;

#undef Finally
#define Finally()							\
	ov_string_setvalue(&tmpstr,NULL);		\
	if(tmpStrVec.veclen > 0){				\
	ov_string_freelist(tmpStrVec.value);}	\

	/* create Name */
	ov_string_setvalue(ExportName,sosxName);
	ov_string_append(ExportName,"_");
	ov_string_append(ExportName,ov_time_timetoascii_local(time));
	tmpstr = strrchr(*ExportName,'.');
	*tmpstr = '\0';
	tmpstr=NULL;

	tmpStrVec.value = ov_string_split(*ExportName,"/",&tmpStrVec.veclen);
	ov_string_setvalue(&tmpstr,tmpStrVec.value[0]);
	for(OV_UINT i = 1; i < tmpStrVec.veclen; i++){
		ov_string_append(&tmpstr,tmpStrVec.value[i]);
	}
	ov_string_setvalue(ExportName,tmpstr);
	ov_string_setvalue(&tmpstr,NULL);
	if(tmpStrVec.veclen > 0){
		ov_string_freelist(tmpStrVec.value);
		tmpStrVec.veclen = 0;
	}

	tmpstr = strchr(*ExportName,' ');
	*tmpstr = '_';
	tmpstr=NULL;

	tmpStrVec.value = ov_string_split(*ExportName,":",&tmpStrVec.veclen);
	ov_string_setvalue(&tmpstr,tmpStrVec.value[0]);
	for(OV_UINT j = 1; j < tmpStrVec.veclen; j++){
		ov_string_append(&tmpstr,tmpStrVec.value[j]);
	}
	ov_string_setvalue(ExportName,tmpstr);
	ov_string_setvalue(&tmpstr,NULL);
	if(tmpStrVec.veclen > 0){
		ov_string_freelist(tmpStrVec.value);
		tmpStrVec.veclen = 0;
	}

	Finally();
	return result;
}

/**
 * This function extends the validationLog by another row with the three columns Type, Message and ObjectIdentifier
 * @param log - pointer to the validationLog
 * @param Type - mistake type used for classification e.g. Error or Warning
 * @param Msg - Fault message for description
 * @param ObjId - ObjectIdentifier of the faulty object.
 * @return OV_RESULT error level if function failed to extend log
 */
OV_RESULT extendValidationLog(
		OV_STRING_VEC 						*log,
		OV_STRING 							Type,
		OV_STRING 							Msg,
		OV_INSTPTR_sosx_sosxdomain			pobj
){
	OV_RESULT					result	= OV_ERR_OK;
	OV_UINT						index	= 0;
	OV_STRING					identifier 	= NULL;

	index = log->veclen;


	if(ov_string_compare(Type,"Error") == OV_STRCMP_EQUAL){
		sosx_sosxdomain_isValid_set(pobj,max_uint(pobj->v_isValid,SOSX_ISVALID_ERROR));
	}else if(ov_string_compare(Type,"Warning") == OV_STRCMP_EQUAL){
		sosx_sosxdomain_isValid_set(pobj,max_uint(pobj->v_isValid,SOSX_ISVALID_WARNING));
	}else{
		logfile_error("Wrong value for type: ",Type);
		result = OV_ERR_GENERIC;
		return result;
	}

	ov_string_setvalue(&identifier,"../");
	ov_string_append(&identifier,Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pobj))->v_identifier) ;
	ov_string_append(&identifier,"/");
	ov_string_append(&identifier,Ov_GetParent(ov_containment,pobj)->v_identifier);
	ov_string_append(&identifier,"/");
	ov_string_append(&identifier,pobj->v_identifier) ;

	index++;
	Ov_SetDynamicVectorLength(log,index,STRING);
	ov_string_setvalue(&log->value[index - 1],Type);

	index++;
	Ov_SetDynamicVectorLength(log,index,STRING);
	ov_string_setvalue(&log->value[index - 1],Msg);

	index++;
	Ov_SetDynamicVectorLength(log,index,STRING);
	ov_string_setvalue(&log->value[index - 1],pobj->v_identifier);

	return result;
}

OV_BOOL checkPropertyInfoType(
		OV_INSTPTR_caex_CAEXObject     	pCaexObj,
		OV_STRING						propInfoType
){
	OV_RESULT							result							= OV_ERR_OK;

	OV_INSTPTR_caex_CAEXObject			*pLibList						= NULL;
	OV_UINT								LenLibList						= 0;

	OV_INSTPTR_caex_RoleRequirements	pRoleReq						= NULL;
	OV_INSTPTR_caex_Attribute			pTempA							= NULL;
	OV_INSTPTR_caex_Value				pValue							= NULL;

#undef Finally
#define Finally() 							\
		freeLibList(pLibList,LenLibList);	\

	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pCaexObj),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pCaexObj->v_identifier);
		Finally();
		return FALSE;
	}

	/* check if CAEX object is a PropertyInformation */
	pRoleReq = Ov_SearchChildEx(ov_containment,pLibList[LenLibList-1],"RoleRequirements",caex_RoleRequirements);
	if(pRoleReq){
		if(ov_string_compare(pRoleReq->v_RefBaseRoleClassPath,"BaseLibs@SoS_BaseRoleLibrary/PropertyInformation") != OV_STRCMP_EQUAL){
			logfile_debug(pCaexObj->v_identifier," is not a PropertyInformation");
			Finally();
			return FALSE;
		}
	}

	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"type",caex_Attribute);
		if (pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if(pValue->v_Value){
					if(ov_string_compare(pValue->v_Value,propInfoType)== OV_STRCMP_EQUAL){
						Finally();
						return TRUE;
					}
				}
				break;
			}
		}
	}
	Finally();
	return FALSE;
}
OV_RESULT updateChildren(
		OV_INSTPTR_caex_CAEXObject		pCaexElement,
		OV_INSTPTR_ov_domain			pSosxElement,
		SOSX_UPDATE_TYPE				updateType

){
	OV_RESULT							result			= OV_ERR_OK;
	OV_INSTPTR_caex_InternalElement		pTempCaex		= NULL;
	OV_INSTPTR_ov_domain				pTempSosx		= NULL;
	OV_INSTPTR_sosx_Stream				pSosxStream		= NULL;
	OV_INSTPTR_sosx_StreamHandler		pStreamHandlerA	= NULL;
	OV_INSTPTR_sosx_StreamHandler		pStreamHandlerB	= NULL;

#undef Finally
#define Finally()

	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* destroy all streams they will be recreated during the update if necessary */
		Ov_ForEachChildEx(ov_containment,pCaexElement,pSosxStream,sosx_Stream){
			/* unlink stream */

			pStreamHandlerA = Ov_GetParent(sosx_isLinkedToSideA,pSosxStream);
			if(pStreamHandlerA){
				Ov_Unlink(sosx_isLinkedToSideA,pStreamHandlerA,pSosxStream);
			}
			pStreamHandlerB = Ov_GetParent(sosx_isLinkedToSideB,pSosxStream);
			if(pStreamHandlerB){
				Ov_Unlink(sosx_isLinkedToSideB,pStreamHandlerB,pSosxStream);
			}

			/* delete stream */
			Ov_DeleteObject(pSosxStream);
		}

		Ov_ForEachChildEx(ov_containment,pCaexElement,pTempCaex,caex_InternalElement){
			/* check if child of pUpdate exists in pSoSContainerToBeUpdated */
			pTempSosx = Ov_SearchChildEx(ov_containment,pSosxElement,pTempCaex->v_identifier,ov_domain);
			if (pTempSosx == NULL){
				/* Child does not exist in SoSContainerToBeUpdate -> create */
				result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pSosxElement),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
				if (Ov_Fail(result)) {
					log_error("Could not create child");
					Finally();
					return result;
				}
			}else{
				/* Child does exist in SoSContainerToBeUpdated and in Update -> update */
				result = sosx_workflowManagement_updateElement(pTempSosx,Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex),updateType);
				if (Ov_Fail(result)) {
					log_error("Could not update child");
					Finally();
					return result;
				}
			}
		}
		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{
		/* ignore all elements except PropertyInformations of type SimResult */

		Ov_ForEachChildEx(ov_containment,pCaexElement,pTempCaex,caex_InternalElement){
			/* check if child of pUpdate exists in pSoSContainerToBeUpdated */
			pTempSosx = Ov_SearchChildEx(ov_containment,pSosxElement,pTempCaex->v_identifier,ov_domain);
			if (pTempSosx == NULL){
				/* Child does not exist in SoSContainerToBeUpdate
				 * Check if Child is a PropertyInformation of type SIMULATIONRESULT -> create
				 * if not do nothing  */
				if(checkPropertyInfoType(Ov_DynamicPtrCast(caex_CAEXObject,pTempCaex),SIMULATIONRESULT)){
					result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pSosxElement),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
					if (Ov_Fail(result)) {
						log_error("Could not create child");
						Finally();
						return result;
					}
				}
			}else{
				/* Child does exist in SoSContainerToBeUpdated and in Update -> update */
				result = sosx_workflowManagement_updateElement(pTempSosx,Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex),updateType);
				if (Ov_Fail(result)) {
					log_error("Could not update child");
					Finally();
					return result;
				}
			}
		}
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}


OV_RESULT findLibrary(
		OV_STRING 						*pRefPath,
		OV_INSTPTR_ov_domain			pSearchIn,
		OV_INSTPTR_ov_domain			*pCaexLibrary
){
	OV_INSTPTR_ov_domain					pSearchInTemp		= NULL;
	OV_RESULT								result				= OV_ERR_OK;
	OV_STRING								*pRefPathList		= NULL;
	OV_STRING								*pRefPathTokList	= NULL;
	OV_STRING								*pLibPathTokList	= NULL;
	OV_STRING								PathToLib			= NULL;
	OV_UINT									LenRefPathList		= 0;
	OV_UINT									LenRefPathTokList	= 0;
	OV_UINT									LenLibPathTokList	= 0;

#undef	Finally
#define Finally() 								\
		ov_string_setvalue(&PathToLib,NULL); 	\
		ov_string_freelist(pRefPathList);		\
		ov_string_freelist(pRefPathTokList);	\
		ov_string_freelist(pLibPathTokList);	\

	pSearchInTemp = pSearchIn;
	/* Find ExternalReference to understand the alias */
	/* check if RefPath specifies an Alias (pRefPath contains '@' */
	if(ov_string_match(*pRefPath,"*@*")){
		/* get the alias and find the externalReference to get the path to the library */
		pRefPathList = ov_string_split(*pRefPath,"@",&LenRefPathList);
		if(LenRefPathList == 0 ){
			log_error("RefPath Error!");
			result = OV_ERR_GENERIC;
			Finally();
			return result;
		}
		ov_string_setvalue(&PathToLib,pRefPathList[1]);
		while(Ov_SearchChildEx(ov_containment,pSearchInTemp,pRefPathList[0],caex_ExternalReference)==NULL && (pSearchInTemp != NULL)){
			pSearchInTemp=Ov_DynamicPtrCast(ov_domain,Ov_GetParent(ov_containment,pSearchInTemp));
		}
		if(pSearchInTemp == NULL){
			log_error("Cannot resolve the library path of ");
			result = OV_ERR_GENERIC;
			Finally();
			return result;
		}
		/* Follow path to Library */
		pRefPathTokList = ov_string_split((Ov_SearchChildEx(ov_containment,pSearchInTemp,pRefPathList[0],caex_ExternalReference)->v_Path),"/",&LenRefPathTokList);
		for (OV_UINT i = 1; i <= LenRefPathTokList; i++){
			if (ov_string_compare(pRefPathTokList[i-1],".")== OV_STRCMP_EQUAL){
				pSearchInTemp = Ov_DynamicPtrCast(ov_domain,Ov_GetParent(ov_containment,pSearchInTemp));
				if(pSearchInTemp == NULL){
					log_error("Cannot resolve the library path of ");
					result = OV_ERR_GENERIC;
					Finally();
					return result;
				}
			}else
				pSearchInTemp = Ov_DynamicPtrCast(ov_domain,Ov_SearchChildEx(ov_containment,pSearchInTemp,pRefPathTokList[i-1],caex_CAEXFile));
			if(pSearchInTemp == NULL){
				log_error("Cannot resolve the library path of ");
				result = OV_ERR_GENERIC;
				Finally();
				return result;
			}
		}
	}else{
		/* Library is within the same CAEXFile - get root Element of CAEXFile */
		while(!(Ov_CanCastTo(caex_CAEXFile,pSearchInTemp)) && (pSearchInTemp != NULL)){
			pSearchInTemp=Ov_DynamicPtrCast(ov_domain,Ov_GetParent(ov_containment,pSearchInTemp));
		}
		ov_string_setvalue(&PathToLib,*pRefPath);
	}

	if(pSearchInTemp == NULL){
		log_error("Cannot resolve the library path of ");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* Follow Path within the library to the object */
	pLibPathTokList = ov_string_split(PathToLib,"/",&LenLibPathTokList);
	for(OV_UINT j = 1;j <= LenLibPathTokList ; j++){
		pSearchInTemp = Ov_DynamicPtrCast(ov_domain,Ov_SearchChild(ov_containment,pSearchInTemp,pLibPathTokList[j-1]));
	}
	if(pSearchInTemp == NULL){
		log_error("Cannot resolve the library path of ");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	*pCaexLibrary = pSearchInTemp;
	Finally();
	return result;
}

OV_RESULT createLinks(
		OV_STRING_VEC					*isLinkedTo,
		OV_INSTPTR_sosx_BaseElement		pTarget
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_sosx_BaseElement				pPartnerA			= NULL;
	OV_INSTPTR_sosx_BaseElement				pPartnerB			= NULL;
	OV_INSTPTR_ov_domain					pTemp				= NULL;
	OV_STRING								*isLinkedToList		= NULL;
	OV_STRING								*Path				= NULL;
	OV_UINT									PathLen				= 0;
	OV_UINT									isLinkedToListLen	= 0;

#undef Finally
#define Finally()								\
		if(isLinkedToList != NULL){				\
			ov_string_freelist(isLinkedToList);}	\
			ov_string_freelist(Path);				\

	/*create link between StreamHandler and Stream*/
	for(OV_UINT i = 0 ; i < isLinkedTo->veclen ; i++){
		if(isLinkedTo->value == NULL || isLinkedTo->value[i] == NULL){
			continue;
		}

		isLinkedToList = ov_string_split(isLinkedTo->value[i],":",&isLinkedToListLen);

		if(isLinkedToListLen != 2){
			logfile_warning("invalid isLinkedTo specification for ", pTarget->v_identifier);
			Finally();
			return result;
		}

		if(Ov_CanCastTo(sosx_Stream,pTarget)){
			pPartnerB = pTarget;
		}else{
			pPartnerA = pTarget;
		}
		/* 1. Find other partner */
		if(pPartnerA == NULL){
			/* find the SteamHandler */
			/* follow path if necessary */
			pTemp = Ov_DynamicPtrCast(ov_domain,Ov_GetParent(ov_containment,pPartnerB));
			if(ov_string_match(isLinkedToList[0],"*/*")){
				if(Path != NULL){
					ov_string_freelist(Path);
				}
				Path = ov_string_split(isLinkedToList[0],"/",&PathLen);
				for(OV_UINT j = 0; j < PathLen ; j++){
					if(ov_string_compare(Path[j],"") != OV_STRCMP_EQUAL){
						pTemp = Ov_SearchChildEx(ov_containment,pTemp,Path[j],ov_domain);
					}
				}
			}else {
				pTemp = Ov_SearchChildEx(ov_containment,pTemp,isLinkedToList[0],ov_domain);
			}
			if(!pTemp){
				result = OV_ERR_GENERIC;
				logfile_error("Could not find the specified link partner", pTarget->v_identifier);
				Finally();
				return result;
			}
			pPartnerA = Ov_DynamicPtrCast(sosx_BaseElement,pTemp);
		}else{
			/* Search within the hierarchy level of the StreamHandler */
			Ov_ForEachChildEx(ov_containment,Ov_GetParent(ov_containment,pPartnerA),pPartnerB,sosx_BaseElement){
				if(ov_string_compare(isLinkedToList[0],pPartnerB->v_identifier) == OV_STRCMP_EQUAL){
					break;
				} else {
					pPartnerB = NULL;
				}
			}
			if(pPartnerB == NULL && Ov_CanCastTo(sosx_Port,pPartnerA)){
				/* Search on the next higher hierarchy level */
				Ov_ForEachChildEx(ov_containment,Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pPartnerA)),pPartnerB,sosx_BaseElement){
					if(ov_string_compare(isLinkedToList[0],pPartnerB->v_identifier) == OV_STRCMP_EQUAL){
						break;
					} else {
						pPartnerB = NULL;
					}
				}

				pPartnerB = Ov_SearchChildEx(ov_containment,Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pPartnerA)),isLinkedToList[0],sosx_BaseElement);
			}
		}

		if((pPartnerA != NULL && pPartnerB != NULL)){
			/* 2. Link Stream and StreamHandler */
			/* choose right association*/
			/*case 1: isLinkedToSideA */
			if(ov_string_match(isLinkedToList[1],"SideA")){
				result = Ov_Link(sosx_isLinkedToSideA,Ov_DynamicPtrCast(sosx_StreamHandler,pPartnerA),Ov_DynamicPtrCast(sosx_Stream,pPartnerB));
				/* OV_ERR_ALREADYEXISTS is OK */
				if(Ov_Fail(result) && result != OV_ERR_ALREADYEXISTS){
					logfile_warning("Could not link Stream and StreamHandler", pPartnerA->v_identifier);
					Finally();
					return result;
				}
				/* reset */
				pPartnerA = NULL;
				pPartnerB = NULL;
				result = OV_ERR_OK;
				ov_string_freelist(isLinkedToList);
				isLinkedToList = NULL;
				continue;
			}
			/*case 2: isLinkedToSideB */
			if(ov_string_match(isLinkedToList[1],"SideB")){
				result = Ov_Link(sosx_isLinkedToSideB,Ov_DynamicPtrCast(sosx_StreamHandler,pPartnerA),Ov_DynamicPtrCast(sosx_Stream,pPartnerB));
				/* OV_ERR_ALREADYEXISTS is OK */
				if(Ov_Fail(result) && result != OV_ERR_ALREADYEXISTS){
					logfile_warning("Could not link Stream and StreamHandler", pPartnerA->v_identifier);
					Finally();
					return result;
				}
				/* reset */
				pPartnerA = NULL;
				pPartnerB = NULL;
				result = OV_ERR_OK;
				ov_string_freelist(isLinkedToList);
				isLinkedToList = NULL;
				continue;
			}
		}
	}
	Finally();
	return result;
}

/*************************************************************************
 * creatCEAXHeader - creates the header for every CAEX export. Must be executed once when creating a CAEX export structure
 * @param pSosxObj - pointer to the SoSX object that shall be exported
 * @param pTargetContainer - pointer to the Container in which the export structure will be stored
 * @return OV_RESULT error message
 */
OV_RESULT createCAEXHeader(
		OV_INSTPTR_ov_domain			pSosxObj,
		OV_INSTPTR_ov_domain			pTargetContainer,
		OV_STRING						HeaderName,
		OV_BOOL							readStateOnly
){
	OV_RESULT 							result				= OV_ERR_OK;
	OV_STRING							tmpFileName			= NULL;
	OV_STRING_VEC						AliasPathList		= {0,NULL};
	OV_INSTPTR_caex_CAEXFile			pCAEXFile			= NULL;
	OV_INSTPTR_ov_domain				ptmpDomain			= NULL;
	OV_INSTPTR_sosx_SoSContainer		pSoSContainer		= NULL;
	OV_INSTPTR_caex_ExternalReference	pExternalRef		= NULL;
	OV_INSTPTR_caex_InstanceHierarchy	pInHier				= NULL;
	OV_INSTPTR_caex_InternalElement		pRootIE				= NULL;

#undef Finally
#define Finally()									\
		ov_string_setvalue(&tmpFileName,NULL);		\
		ov_string_freelist(AliasPathList.value);	\


	/* create Name for export: [Root sosx obj name].export */
	if(ov_string_compare(HeaderName,"")==OV_STRCMP_EQUAL){
		ov_string_setvalue(&tmpFileName,pSosxObj->v_identifier);
		ov_string_append(&tmpFileName,".export");
	}else{
		ov_string_setvalue(&tmpFileName,HeaderName);
	}

	/* create CEAXFile */
	result = Ov_CreateObject(caex_CAEXFile,pCAEXFile,pTargetContainer,tmpFileName);
	if (Ov_Fail(result)){
		logfile_error("Could not create the CAEXFile",pSosxObj->v_identifier);
		Finally();
		return result;
	}
	/* set name of CAEXFile */
	ov_string_setvalue(&pCAEXFile->v_FileName,tmpFileName);

	/* find SoSContainer */
	ptmpDomain = pSosxObj;
	while(!Ov_CanCastTo(sosx_SoSContainer,ptmpDomain)){
		ptmpDomain = Ov_DynamicPtrCast(ov_domain,Ov_GetParent(ov_containment,ptmpDomain));
	}

	pSoSContainer = Ov_DynamicPtrCast(sosx_SoSContainer,ptmpDomain);

	/* Read ExternalReference List */
	for(OV_UINT u = 0; u < Ov_DynamicPtrCast(sosx_SoSContainer,pSoSContainer)->v_externalReference.veclen; u++){
		if(AliasPathList.value != NULL){
			ov_string_freelist(AliasPathList.value);
		}

		AliasPathList.value = ov_string_split(pSoSContainer->v_externalReference.value[u],"@",&AliasPathList.veclen);


		if(AliasPathList.veclen<2){
			logfile_error("Could not read the ExternalReference",pSoSContainer->v_identifier);
			Finally();
			return result;
		}

		/* create the ExernalReference Object */
		result = Ov_CreateObject(caex_ExternalReference,pExternalRef,pCAEXFile,AliasPathList.value[0]);
		if (Ov_Fail(result)){
			logfile_error("Could not create the ExternalReference",pSoSContainer->v_identifier);
			Finally();
			return result;
		}
		/* set Alias and Path */
		ov_string_setvalue(&pExternalRef->v_Alias,AliasPathList.value[0]);
		ov_string_setvalue(&pExternalRef->v_Path,AliasPathList.value[1]);
	}

	/* create InstanceHierarchy */
	result = Ov_CreateObject(caex_InstanceHierarchy,pInHier,pCAEXFile,"SystemOfSystems");
	if (Ov_Fail(result)){
		logfile_error("Could not create the InstanceHierarchy",pSoSContainer->v_identifier);
		Finally();
		return result;
	}
	/* set Name of InstanceHierarchy */
	ov_string_setvalue(&pInHier->v_Name,"SystemOfSystems");

	/* create root InternalElement */
	Sosx_CreateSystemUnit(pInHier,pRootIE,"SoSContainer","Libs@SoS_BaseLibrary/SoSContainer");

	/* read all children of the SoSX structure */
	result = sosx_workflowManagement_readElement(pSosxObj,Ov_DynamicPtrCast(ov_domain,pRootIE),FALSE,NULL,readStateOnly);
	if (Ov_Fail(result)){
		/* undo export in case of error */
		Ov_DeleteObject(pCAEXFile);
		logfile_error("Could not read the children of ",pSosxObj->v_identifier);
		Finally();
		return result;
	}

	Finally();
	return result;
}

OV_RESULT findInternalLinks(
		OV_INSTPTR_caex_CAEXObject			pInternalElement,
		OV_STRING_VEC						*isLinkedTo

){
	OV_RESULT 								result 				= OV_ERR_OK;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_INSTPTR_caex_ExternalInterface		pExternalInterface	= NULL;
	OV_INSTPTR_caex_CAEXBasicObject			pCaexParent			= NULL;
	OV_INSTPTR_caex_InternalLink			pInternalLink		= NULL;
	OV_STRING								tempStr				= NULL;
	OV_STRING								StreamName			= NULL;
	OV_STRING								caexLibrary			= NULL;
	OV_STRING								RefBaseClass		= NULL;
	OV_STRING								WantedRefPatnerSide	= NULL;
	OV_UINT									LenLibList			= 0;
	OV_UINT									index				= 0;


#undef	Finally
#define Finally()								 		\
		ov_string_setvalue(&tempStr,NULL);				\
		ov_string_setvalue(&caexLibrary,NULL);			\
		ov_string_setvalue(&RefBaseClass,NULL);			\
		ov_string_setvalue(&StreamName,NULL);			\
		ov_string_setvalue(&WantedRefPatnerSide,NULL);	\
		freeLibList(pLibList,LenLibList);				\

	/* Check if InternalElement or isLinkedTo is null */
	if (pInternalElement == NULL ||
			isLinkedTo == NULL){
		logfile_error("Cannot find the isLinkedTo and/or the InternalElement ", pInternalElement->v_Name);
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get LibraryList of InternalElement*/
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* Go Through LibraryList and try to find an InternalLink for every ExternalInterface */
	for (OV_UINT u = 0 ; u < LenLibList ; u++){
		Ov_ForEachChildEx(ov_containment,pLibList[u],pExternalInterface,caex_ExternalInterface){
			/* get ExternalInterface RefBaseClass */
			if(pExternalInterface->v_RefBaseClassPath == NULL){
				logfile_error("RefBaseClassPath of ExternalInterface is missing", pInternalElement->v_Name);
				result = OV_ERR_GENERIC;
				Finally();
				return result;
			}

			/* save RefBaseClassPath */
			ov_string_setvalue(&RefBaseClass,pExternalInterface->v_RefBaseClassPath);

			/* remove Library Alias if necessary */
			if(ov_string_match(RefBaseClass,"*@*")){
				ov_string_setvalue(&RefBaseClass,strrchr(RefBaseClass,64)+1);
			}
			/* Distinguish between different types of ExternalInterface */
			/* Interface of SourceSink, DistributionNode and inside System Interface of a Port */
			if(ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/SourceInterface") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/SinkInterface") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortInsideInput") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortInsideOutput") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/DNInputInterface") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/DNOutputNodeInterface") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/StreamInterfaceA") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/StreamInterfaceB") == OV_STRCMP_EQUAL){
				/* search for InternalLink and Stream on the same ov_containment level */
				/* get the Caex parent of the InternalElement representing the StreamHandler*/
				pCaexParent = Ov_DynamicPtrCast(caex_CAEXBasicObject,Ov_GetParent(ov_containment,pInternalElement));
				/* generate the wanted RefPatnerSide*/
				ov_string_setvalue(&WantedRefPatnerSide,pInternalElement->v_Name);
				ov_string_append(&WantedRefPatnerSide,":");
				ov_string_append(&WantedRefPatnerSide,pExternalInterface->v_Name);
			}

			/* Outside Process or System Interface of a Port */
			if(ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortOutsideInput") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortOutsideOutput") == OV_STRCMP_EQUAL){
				/* search for InternalLink and Stream on the next higher ov_containment level */
				/* get the object right object to search for the InternalLink */
				/* check if parent is of instance type SystemUnitClassLib */
				if(Ov_CanCastTo(caex_SystemUnitClassLib, Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pInternalElement))) ||
						Ov_CanCastTo(caex_SystemUnitClassLib,Ov_GetParent(ov_containment,pInternalElement))){
					/*
					 * TO DO: find the specification of the links if process or system is a SystemUnitClass
					 */
				}else{
					/* parent is not of instance type SystemUnitClassLib
					 * search for the InternalLink in the parent parent */
					pCaexParent = Ov_DynamicPtrCast(caex_CAEXBasicObject,Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pInternalElement)));
					/* WantedRefPatnerSide: Parent/Port:InterfaceName e.g: Process1/LeftPort:InsideInterface */
					ov_string_setvalue(&WantedRefPatnerSide,Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,pInternalElement))->v_Name);
					ov_string_append(&WantedRefPatnerSide,"/");
					ov_string_append(&WantedRefPatnerSide,pInternalElement->v_Name);
					ov_string_append(&WantedRefPatnerSide,":");
					ov_string_append(&WantedRefPatnerSide,pExternalInterface->v_Name);
				}
			}

			/* Search for the right CAEX InternalLink within the chosen CaexParent (compare RefPartnerSideA and RefPartnerB and store the other side of the InternalLink */
			Ov_ForEachChildEx(ov_containment,pCaexParent,pInternalLink,caex_InternalLink){
				/* check if RefPatnerSideA or RefPatnerSideA matches the current InternalElement */
				if(ov_string_compare(WantedRefPatnerSide,pInternalLink->v_RefPartnerSideA) == OV_STRCMP_EQUAL){
					/* wanted RefPatnerSide found, store name of stream and stop search for the internalLink */
					ov_string_setvalue(&StreamName,pInternalLink->v_RefPartnerSideB);
					break;
				}
				if(ov_string_compare(WantedRefPatnerSide,pInternalLink->v_RefPartnerSideB) == OV_STRCMP_EQUAL){
					/* wanted RefPatnerSide found, store name of stream and stop search for the internalLink */
					ov_string_setvalue(&StreamName,pInternalLink->v_RefPartnerSideA);
					break;
				}
			}

			/* check if InternalLink found*/
			if(StreamName == NULL){
				break;
			}

			strtok(StreamName,":");
			/* Define isLinkedTo Type based on InterfaceClass */
			if(ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/SourceInterface") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortInsideOutput") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/DNOutputInterface") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/StreamInterfaceA") == OV_STRCMP_EQUAL ||
					ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortOutsideOutput") == OV_STRCMP_EQUAL){
				ov_string_append(&StreamName,":SideA");
			} else
				if(ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/SinkInterface") == OV_STRCMP_EQUAL ||
						ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortInsideInput") == OV_STRCMP_EQUAL ||
						ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/DNInputInterface") == OV_STRCMP_EQUAL ||
						ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/StreamInterfaceB") == OV_STRCMP_EQUAL ||
						ov_string_compare(RefBaseClass,"SoS_BaseInterfaceLibrary/PortOutsideInput") == OV_STRCMP_EQUAL){
					ov_string_append(&StreamName,":SideB");
				}else{
					logfile_error("Could not define isLinkedTo Type", pInternalElement->v_Name);
					result = OV_ERR_GENERIC;
					Finally();
					return result;
				}
			/* Store link partner */
			index++;
			Ov_SetDynamicVectorLength(isLinkedTo,index,STRING);
			ov_string_setvalue(&isLinkedTo->value[index-1],StreamName);
		}
	}
	// *isLinkedTo = isLinkedToTemp;
	Finally();
	return result;
}

OV_RESULT sosx_checkLink(
		OV_INSTPTR_sosx_StreamHandler			pStreamHandlerA,
		OV_INSTPTR_sosx_StreamHandler			pStreamHandlerB,
		OV_STRING_VEC							*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;

	/* check if both sides of the stream have the same StreamType */
	if(ov_string_compare(pStreamHandlerB->v_StreamType,(Ov_DynamicPtrCast(sosx_StreamHandler,pStreamHandlerA)->v_StreamType)) == OV_STRCMP_EQUAL){
		/* everything okay */
	}else{
		logfile_info("wrong streamType",pStreamHandlerA->v_identifier);
		extendValidationLog(pValidationLog,"Error","Wrong StreamType",Ov_DynamicPtrCast(sosx_sosxdomain,pStreamHandlerA));
	}

	/* check connections to streams
	 * Distinguish between Port of Process, Port of System, SourceSink and Distribution Node */
	/* pTarget is Port of Process */
	if(Ov_CanCastTo(sosx_Port,pStreamHandlerA) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerA))){
		/* allowed connections of a process port: Distribution Node, Port of Process, Port of System */
		if(Ov_CanCastTo(sosx_DistributionNode,pStreamHandlerB) || /* Distribution Node */
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerB))) || /* Port of Process */
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB))))/* Port of System */{
			/* everything okay */
			return result;
		}else{
			logfile_info("isLinkedTo relationship is not allowed",pStreamHandlerA->v_identifier);
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pStreamHandlerA));
			return result;
		}
	}

	/* pTarget is Port of System */
	if(Ov_CanCastTo(sosx_Port,pStreamHandlerA) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerA))){
		/* allowed connections of a system port: Source, Sink, Distribution Node, Port of Process, Port of System */
		if(Ov_CanCastTo(sosx_SourceSink,pStreamHandlerB) || /* SourceSink */
				Ov_CanCastTo(sosx_DistributionNode,pStreamHandlerB) || /* DistributionNode */
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerB)))/* Port of Process */ ||
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB))))/* Port of System */{
			/* everything okay */
			return result;
		}else{
			logfile_info("isLinkedTo relationship is not allowed",pStreamHandlerA->v_identifier);
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pStreamHandlerA));
			return result;
		}
	}

	/* pTarget is DistributionNode */
	if(Ov_CanCastTo(sosx_DistributionNode,pStreamHandlerA)){
		/* allowed connections: Port of System, Port of Process */
		if((Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerB))) /* Port of Process */ ||
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB)))) /* Port of System */{
			/* everything okay */
			return result;
		}else{
			logfile_info("isLinkedTo relationship is not allowed",pStreamHandlerA->v_identifier);
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pStreamHandlerA));
			return result;
		}
	}

	/* pTarget is SourceSink */
	if(Ov_CanCastTo(sosx_SourceSink,pStreamHandlerA)){
		/* allowed connections: Port of System */
		if(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB))){
			/* everything okay */
			return result;
		}else{
			logfile_info("isLinkedTo relationship is not allowed",pStreamHandlerA->v_identifier);
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pStreamHandlerA));
			return result;
		}
	}
	return result;
}

OV_RESULT validateLinks(
		OV_INSTPTR_sosx_StreamHandler			pStreamHandlerA,
		OV_STRING_VEC							*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_sosx_Stream					pStream			= NULL;
	OV_INSTPTR_sosx_StreamHandler			pStreamHandlerB	= NULL;



#undef	Finally
#define Finally() \

	/* check links of StreamHandler */
	/* get Stream */
	Ov_ForEachChildEx(sosx_isLinkedToSideA, Ov_DynamicPtrCast(sosx_StreamHandler,pStreamHandlerA), pStream, sosx_Stream){
		/* get children of the Stream */
		pStreamHandlerB = Ov_GetParent(sosx_isLinkedToSideB,pStream);
		/* ignore pTarget */
		sosx_checkLink(	pStreamHandlerA,pStreamHandlerB,pValidationLog);
	}
	Ov_ForEachChildEx(sosx_isLinkedToSideB, Ov_DynamicPtrCast(sosx_StreamHandler,pStreamHandlerA), pStream, sosx_Stream){
		/* get children of the Stream */
		pStreamHandlerB = Ov_GetParent(sosx_isLinkedToSideA,pStream);
		/* ignore pTarget */
		sosx_checkLink(	pStreamHandlerA,pStreamHandlerB,pValidationLog);
	}

	Finally();
	return result;
}

OV_RESULT readLinks(
		OV_STRING_VEC						*isLinkedTo,
		OV_INSTPTR_sosx_BaseElement 		pToBeRead
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_sosx_Stream					pStream				= NULL;
	OV_INSTPTR_sosx_StreamHandler			pStreamHandler		= NULL;
	OV_STRING								Link				= NULL;
	OV_UINT									index				= 0;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&Link,NULL);		\



	/*check if pToBeRead is StreamHandler or Stream*/
	/* is StreamHandler */
	if(Ov_CanCastTo(sosx_StreamHandler,pToBeRead)){
		/* read all input Streams */
		Ov_ForEachChildEx(sosx_isLinkedToSideB,Ov_DynamicPtrCast(sosx_StreamHandler,pToBeRead),pStream,sosx_Stream){
			if(Ov_GetParent(ov_containment,pToBeRead) == Ov_GetParent(ov_containment,pStream)){
				ov_string_setvalue(&Link,pStream->v_identifier);
				ov_string_append(&Link,":SideB");
			}else{
				ov_string_setvalue(&Link,":SideB");
				/* TO DO: Handle Streams on a higher hierarchy level. I.e. a port can be connected to a Stream which is on the same hierarchy level as the ports parent.
				 * The stream will create the InternalLink, but the Port has to create the ExternalInterface.
				 * Workaround for now: Port in BaseLibrary has all ExternalInterfaces
				 */
			}
			index++;
			Ov_SetDynamicVectorLength(isLinkedTo,index,STRING);
			ov_string_setvalue(&isLinkedTo->value[index-1],Link);
			ov_string_setvalue(&Link,NULL);
		}

		/* read all output Streams */
		Ov_ForEachChildEx(sosx_isLinkedToSideA,Ov_DynamicPtrCast(sosx_StreamHandler,pToBeRead),pStream,sosx_Stream){
			if(Ov_GetParent(ov_containment,pToBeRead) == Ov_GetParent(ov_containment,pStream)){
				ov_string_setvalue(&Link,pStream->v_identifier);
				ov_string_append(&Link,":SideA");
			}else{
				ov_string_setvalue(&Link,":SideA");
				/* TO DO: Handle Streams on a higher hierarchy level. */
			}
			index++;
			Ov_SetDynamicVectorLength(isLinkedTo,index,STRING);
			ov_string_setvalue(&isLinkedTo->value[index-1],Link);
			ov_string_setvalue(&Link,NULL);
		}
		Finally();
		return result;
	}

	/* is Stream */
	if(Ov_CanCastTo(sosx_Stream,pToBeRead)){
		/* read SideA StreamHandler */
		pStreamHandler = Ov_GetParent(sosx_isLinkedToSideA,Ov_DynamicPtrCast(sosx_Stream,pToBeRead));
		if(pStreamHandler != NULL){
			if(Ov_GetParent(ov_containment,pToBeRead) == Ov_GetParent(ov_containment,pStreamHandler)){
				ov_string_setvalue(&Link,pStreamHandler->v_identifier);
			}else{
				ov_string_setvalue(&Link,Ov_GetParent(ov_containment,pStreamHandler)->v_identifier);
				ov_string_append(&Link,"/");
				ov_string_append(&Link,pStreamHandler->v_identifier);
			}
			ov_string_append(&Link,":SideA");
			index++;
			Ov_SetDynamicVectorLength(isLinkedTo,index,STRING);
			ov_string_setvalue(&isLinkedTo->value[index-1],Link);
			ov_string_setvalue(&Link,NULL);
		}
		/* read SideB StreamHandler */
		pStreamHandler = Ov_GetParent(sosx_isLinkedToSideB,Ov_DynamicPtrCast(sosx_Stream,pToBeRead));
		if(pStreamHandler != NULL){
			if(Ov_GetParent(ov_containment,pToBeRead) == Ov_GetParent(ov_containment,pStreamHandler)){
				ov_string_setvalue(&Link,pStreamHandler->v_identifier);
			}else{
				ov_string_setvalue(&Link,Ov_GetParent(ov_containment,pStreamHandler)->v_identifier);
				ov_string_append(&Link,"/");
				ov_string_append(&Link,pStreamHandler->v_identifier);
			}
			ov_string_append(&Link,":SideB");
			index++;
			Ov_SetDynamicVectorLength(isLinkedTo,index,STRING);
			ov_string_setvalue(&isLinkedTo->value[index-1],Link);
			ov_string_setvalue(&Link,NULL);
		}
		Finally();
		return result;
	}
	Finally();
	return result;
}

OV_RESULT  exportLinks(
		OV_STRING_VEC						*isLinkedTo,
		OV_INSTPTR_sosx_BaseElement			pToBeRead,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_STRING								LinkName			= NULL;
	OV_STRING								RefSideA			= NULL;
	OV_STRING								RefSideB			= NULL;
	OV_STRING								*isLinkedToList		= NULL;
	OV_STRING								InterfaceName		= NULL;
	OV_STRING								RefBaseClassPath	= NULL;
	OV_INSTPTR_caex_InternalElement			pTargetContainer	= NULL;
	OV_INSTPTR_caex_InternalLink			pInternalLink		= NULL;
	OV_INSTPTR_caex_ExternalInterface		pExternalInterface	= NULL;
	OV_UINT									isLinkedToListLen	= 0;

#undef Finally
#define Finally()										\
		ov_string_setvalue(&LinkName,NULL);				\
		ov_string_setvalue(&RefSideA,NULL);				\
		ov_string_setvalue(&RefSideB,NULL);				\
		ov_string_setvalue(&InterfaceName,NULL);		\
		ov_string_setvalue(&RefBaseClassPath,NULL);		\
		ov_string_freelist(isLinkedToList);				\

	/* create InternalLinks representing connections between StreamHandler and Stream */
	for(OV_UINT i = 0 ; i < isLinkedTo->veclen ; i++){
		if(isLinkedTo->value == NULL || isLinkedTo->value[i] == NULL){
			continue;
		}

		if(isLinkedToList != NULL){
			ov_string_freelist(isLinkedToList);
		}

		isLinkedToList = ov_string_split(isLinkedTo->value[i],":",&isLinkedToListLen);

		if(isLinkedToListLen != 2){
			logfile_warning("invalid isLinkedTo specification for ", pToBeRead->v_identifier);
			Finally();
			return result;
		}

		/* pToBeRead is Stream*/
		if(Ov_CanCastTo(sosx_Stream,pToBeRead)){

			/* create Link Name: [StreamHandlerName]:[StreamIdentifier]*/
			ov_string_setvalue(&LinkName,isLinkedToList[0]);
			ov_string_append(&LinkName,":");
			ov_string_append(&LinkName,pToBeRead->v_identifier);

			/* set RefSideA: [StreamHandlerName] */
			ov_string_setvalue(&RefSideA,"/");
			ov_string_setvalue(&RefSideA,isLinkedToList[0]);

			/* set RefSideB: [StreamIdetifier] */
			ov_string_setvalue(&RefSideB,pToBeRead->v_identifier);

			if(ov_string_compare(isLinkedToList[1],"SideA") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"SideA");

				/* set RefBaseClassPath */
				ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/StreamInterfaceA");

				/* append RefSideA InterfaceName: [StreamHandlerName]:[InterfaceName] */
				ov_string_append(&RefSideA,":Output");

				/* append RefSideB InterfaceName: [StreamIdentifier]:[InterfaceName] */
				ov_string_append(&RefSideB,":SideA");

				pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,pInternalElement));
			}
			if(ov_string_compare(isLinkedToList[1],"SideB") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"SideB");

				/* set RefBaseClassPath */
				ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/StreamInterfaceB");

				/* append RefSideA InterfaceName: [StreamHandlerName]:[InterfaceName] */
				ov_string_append(&RefSideA,":Input");

				/* append RefSideB InterfaceName: [StreamIdentifier]:[InterfaceName] */
				ov_string_append(&RefSideB,":SideB");
			}
		}

		if(Ov_CanCastTo(sosx_StreamHandler,pToBeRead) && ov_string_compare(isLinkedToList[0],"") != OV_STRCMP_EQUAL ){
			/* create Link Name: [StreamHandlerName]:[StreamIdentifier]*/
			ov_string_setvalue(&LinkName,pToBeRead->v_identifier);
			ov_string_append(&LinkName,":");
			ov_string_append(&LinkName,isLinkedToList[0]);

			/* set RefSideA: [StreamHandlerName] */
			ov_string_setvalue(&RefSideA,"/");
			ov_string_append(&RefSideA,pToBeRead->v_identifier);

			/* set RefSideB: [StreamIdetifier] */
			ov_string_setvalue(&RefSideB,isLinkedToList[0]);

			if(ov_string_compare(isLinkedToList[1],"SideA") == OV_STRCMP_EQUAL){

				/* append RefSideA InterfaceName: [StreamHandlerName]:[InterfaceName] */
				ov_string_append(&RefSideA,":Output");

				/* append RefSideB InterfaceName: [StreamIdentifier]:[InterfaceName] */
				ov_string_append(&RefSideB,":SideA");
			}
			if(ov_string_compare(isLinkedToList[1],"SideB") == OV_STRCMP_EQUAL){

				/* append RefSideA InterfaceName: [StreamHandlerName]:[InterfaceName] */
				ov_string_append(&RefSideA,":Input");

				/* append RefSideB InterfaceName: [StreamIdentifier]:[InterfaceName] */
				ov_string_append(&RefSideB,":SideB");
			}
		}

		/* pToBeRead is DistributionNode*/
		if(Ov_CanCastTo(sosx_DistributionNode,pToBeRead)){

			pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,pInternalElement));

			if(ov_string_compare(isLinkedToList[1],"SideA") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"Output");

				/* set RefBaseClassPath */
				ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/DNOutputInterface");

			}
			if(ov_string_compare(isLinkedToList[1],"SideB") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"Input");

				/* set RefBaseClassPath */
				ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/DNInputInterface");
			}
		}

		/* pToBeRead is SourceSink*/
		if(Ov_CanCastTo(sosx_SourceSink,pToBeRead) && !Ov_CanCastTo(sosx_DistributionNode,pToBeRead)){

			pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,pInternalElement));

			if(ov_string_compare(isLinkedToList[1],"SideA") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"Output");

				/* set RefBaseClassPath */
				ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/SourceInterface");

			}
			if(ov_string_compare(isLinkedToList[1],"SideB") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"Input");

				/* set RefBaseClassPath */
				ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/SinkInterface");

			}
		}

		/* pToBeRead is Port */
		if(Ov_CanCastTo(sosx_Port,pToBeRead)){

			pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,pInternalElement));

			if(ov_string_compare(isLinkedToList[1],"SideA") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"Output");

				if(!Ov_CanCastTo(sosx_Process, Ov_GetParent(ov_containment,pToBeRead)) ||
						Ov_SearchChildEx(ov_containment , Ov_GetParent(ov_containment,pToBeRead) , isLinkedToList[0] , sosx_Stream) != NULL){
					/* set RefBaseClassPath */
					ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/PortInsideOutput");
					pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,pInternalElement));
				}

				if(Ov_CanCastTo(sosx_Process, Ov_GetParent(ov_containment,pToBeRead)) ||
						Ov_SearchChildEx(ov_containment , Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pToBeRead)) , isLinkedToList[0] , sosx_Stream) != NULL){
					/* set RefBaseClassPath */
					ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/PortOutsideOutput");
					pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pInternalElement)));
				}

			}
			if(ov_string_compare(isLinkedToList[1],"SideB") == OV_STRCMP_EQUAL){

				/* set InterfaceName */
				ov_string_setvalue(&InterfaceName,"Input");

				if(!Ov_CanCastTo(sosx_Process, Ov_GetParent(ov_containment,pToBeRead)) ||
						Ov_SearchChildEx(ov_containment , Ov_GetParent(ov_containment,pToBeRead) , isLinkedToList[0] , sosx_Stream) != NULL){
					/* set RefBaseClassPath */
					ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/PortInsideInput");
					pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,pInternalElement));
				}

				if(Ov_CanCastTo(sosx_Process, Ov_GetParent(ov_containment,pToBeRead)) ||
						Ov_SearchChildEx(ov_containment , Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pToBeRead)) , isLinkedToList[0] , sosx_Stream) != NULL){
					/* set RefBaseClassPath */
					ov_string_setvalue(&RefBaseClassPath,"BaseLibs@SoS_BaseInterfaceLibrary/PortOutsideInput");
					pTargetContainer = Ov_DynamicPtrCast(caex_InternalElement,Ov_GetParent(ov_containment,Ov_GetParent(ov_containment,pInternalElement)));
				}
			}
		}


		/* check if all necessary parameters were set (for interface creation)*/
		if(InterfaceName != NULL &&
				RefBaseClassPath != NULL){
			/* create the ExternalInterface within the InternalElement, check if Interface already exists */
			if(Ov_SearchChildEx(ov_containment,pInternalElement,InterfaceName,caex_ExternalInterface) == NULL){
				result = Ov_CreateObject(caex_ExternalInterface,pExternalInterface,pInternalElement,InterfaceName);
				if(Ov_Fail(result)){
					logfile_error("Could not create the CAEX-ExternalInterface for: ",pToBeRead->v_identifier);
					Finally();
					return result;
				}
				/* set name */
				ov_string_setvalue(&pExternalInterface->v_Name,InterfaceName);
				/* set RefBaseClassPath of the ExternalInterface */
				ov_string_setvalue(&pExternalInterface->v_RefBaseClassPath,RefBaseClassPath);
			}
		}

		/* check if all necessary parameters were set (for InternalLink creation) */
		if(	pTargetContainer != NULL &&
				RefSideA != NULL &&
				RefSideB != NULL &&
				LinkName != NULL){

			/* remove '/' from LinkName */
			for(OV_UINT i = 0 ; i < strlen(LinkName); i++){
				if(LinkName[i] == '/'){
					LinkName[i] = '-';
				}
			}

			/* create InternalLink, check if InternalLink already exist first */
			if(Ov_SearchChildEx(ov_containment,pTargetContainer,LinkName,caex_InternalLink) == NULL){
				result = Ov_CreateObject(caex_InternalLink,pInternalLink,pTargetContainer,LinkName);
				if(Ov_Fail(result)){
					logfile_error("Could not create the CAEX-InternalLink for: ",pToBeRead->v_identifier);
					Finally();
					return result;
				}

				/* set name */
				ov_string_setvalue(&pInternalLink->v_Name,LinkName);
				/* set RefPartnerSideA & B */
				ov_string_setvalue(&pInternalLink->v_RefPartnerSideA,RefSideA);
				ov_string_setvalue(&pInternalLink->v_RefPartnerSideB,RefSideB);
			}
		}
	}
	Finally();
	return result;
}

OV_VAR_TYPE stringToDatatype(
		OV_STRING		datatype
){
	/* Mapping between OV_VT and CAEX data types
	 * OV_VT_TIME	->	xs:dateTime
	 * OV_VT_STRING	->	xs:string
	 * OV_VT_BOOL	->	xs:boolean
	 * OV_VT_INT	->	xs:integer
	 * OV_VT_UINT	->	xs:unsignedInt
	 * OV_VT_SINGLE	->	xs:float
	 * OV_VT_DOUBLE	->	xs:double
	 *
	 */
	if(ov_string_compare(datatype,"xs:string") == OV_STRCMP_EQUAL){
		return OV_VT_BOOL;
	}
	if(ov_string_compare(datatype,"xs:boolean") == OV_STRCMP_EQUAL){
		return OV_VT_BOOL;
	}
	if(ov_string_compare(datatype,"xs:integer") == OV_STRCMP_EQUAL){
		return OV_VT_INT;
	}
	if(ov_string_compare(datatype,"xs:unsignedInt") == OV_STRCMP_EQUAL){
		return OV_VT_UINT;
	}
	if(ov_string_compare(datatype,"xs:float") == OV_STRCMP_EQUAL){
		return OV_VT_SINGLE;
	}
	if(ov_string_compare(datatype,"xs:double") == OV_STRCMP_EQUAL){
		return OV_VT_DOUBLE;
	}
	logfile_error("Unknown dataType",datatype);
	return OV_VT_VOID;
}

/***************************************************************
 * F R E E D E S C R I P T I O N S
 **************************************************************/

void freeSoSContainerDescription(
		SOSX_SoSContainerDescription			*Description
){
	ov_string_setvalue(&Description->Name,NULL);
	Ov_SetDynamicVectorLength(&Description->externalReference,0,STRING);
}

void freeSystemDescription(
		SOSX_SystemDescription*					Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Name,NULL);
	if(Description->externalInfo.veclen > 0){
		Ov_SetDynamicVectorLength(&Description->externalInfo,0,STRING);
	}
}

void freeProcessDescription(
		SOSX_ProcessDescription*				Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Name,NULL);
	if(Description->externalInfo.veclen > 0){
		Ov_SetDynamicVectorLength(&Description->externalInfo,0,STRING);
	}
}

void freePortDescription(
		SOSX_PortDescription*					Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Name,NULL);
	ov_string_setvalue(&Description->StreamType,NULL);
	ov_string_setvalue(&Description->wasConnectedTo,NULL);
	if(Description->isLinkedTo.veclen > 0){
		Ov_SetDynamicVectorLength(&Description->isLinkedTo,0,STRING);
	}
}

void freeSourceSinkDescription(
		SOSX_SourceSinkDescription*				Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Name,NULL);
	ov_string_setvalue(&Description->StreamType,NULL);
	ov_string_setvalue(&Description->wasConnectedTo,NULL);
	if(Description->isLinkedTo.veclen > 0){
		Ov_SetDynamicVectorLength(&Description->isLinkedTo,0,STRING);
	}
}

void freeDistributionNodeDescription(
		SOSX_DistributionNodeDescription*		Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Name,NULL);
	ov_string_setvalue(&Description->StreamType,NULL);
	ov_string_setvalue(&Description->wasConnectedTo,NULL);
	if(Description->isLinkedTo.veclen > 0){
		Ov_SetDynamicVectorLength(&Description->isLinkedTo,0,STRING);
	}
}

void freePropertyDescription(
		SOSX_PropertyDescription*				Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Name,NULL);
}

void freePropertyInformationDescription(
		SOSX_PropertyInformationDescription*	Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Identifier,NULL);
	ov_string_setvalue(&Description->source,NULL);
	ov_string_setvalue(&Description->type,NULL);
	ov_string_setvalue(&Description->unit,NULL);
	if(Description->timeStamps.veclen > 0){
		Ov_SetDynamicVectorLength(&Description->timeStamps,0,TIME);
	}
	Ov_SetAnyValue(&Description->value,NULL);
	Ov_SetAnyValue(&Description->valueVec,NULL);
}

void freeStreamDescription(
		SOSX_StreamDescription*					Description
){
	ov_string_setvalue(&Description->CaexLib,NULL);
	ov_string_setvalue(&Description->Identifier,NULL);
	ov_string_setvalue(&Description->visualLayout,NULL);
	if(Description->isLinkedTo.veclen > 0){
		Ov_SetDynamicVectorLength(&Description->isLinkedTo,0,STRING);
	}
}

#endif
