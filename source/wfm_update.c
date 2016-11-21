/******************************************************************************
 *
 *   FILE
 *   ----
 *   update.c
 *
 *   History
 *   -------
 *   2014-11-13   File created
 *
 *******************************************************************************/

#ifndef OV_COMPILE_LIBRARY_sosx
#define OV_COMPILE_LIBRARY_sosx


#include "sosx.h"
#include "libov/ov_macros.h"
#include "caex.h"
#include "sosxcommon.h"
#include "libov/ov_path.h"
#include "libov/ov_result.h"


/**
 * @param pSoSContainerToBeUpdated
 * @param pUpdate
 * @return
 */
OV_RESULT sosx_workflowManagement_updateSoSContainer(
		OV_INSTPTR_sosx_SoSContainer		pSoSContainerToBeUpdated,
		OV_INSTPTR_caex_CAEXFile			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result							= OV_ERR_OK;
	OV_INSTPTR_caex_CAEXObject				pTopLevelInternalElement		= NULL;
	OV_INSTPTR_caex_ExternalReference		pExternalRef					= NULL;
	OV_INSTPTR_caex_InstanceHierarchy		pInHier							= NULL;
	OV_STRING								FileName						= NULL;
	OV_STRING								tmpstr							= NULL;
	OV_UINT									index							= 0;
	SOSX_SoSContainerDescription			SoSContainerUpdate				= {NULL};
#undef Finally
#define Finally() 											\
		freeSoSContainerDescription(&SoSContainerUpdate);	\
		ov_string_setvalue(&FileName,NULL); 				\
		ov_string_setvalue(&tmpstr,NULL); 					\

	if (pSoSContainerToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("SoSContainerToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* collect attributes*/
		/* name */
		/* Remove '.xml' from Source */
		ov_string_setvalue(&tmpstr, pUpdate->v_FileName);
		ov_string_setvalue(&FileName,strtok(tmpstr, "."));
		ov_string_setvalue(&tmpstr,NULL);
		if (!FileName) {
			log_error("No file name given");
			Finally();
			return OV_ERR_GENERIC;
		}
		ov_string_setvalue(&(SoSContainerUpdate.Name), FileName);

		/*  collect all externalRefrences */
		/* format AliasA@PathA */
		Ov_ForEachChildEx(ov_containment,pUpdate,pExternalRef,caex_ExternalReference){
			ov_string_setvalue(&tmpstr,pExternalRef->v_Alias);
			ov_string_append(&tmpstr,"@");
			ov_string_append(&tmpstr,pExternalRef->v_Path);
			index++;
			Ov_SetDynamicVectorLength(&SoSContainerUpdate.externalReference,index,STRING);
			ov_string_setvalue(&SoSContainerUpdate.externalReference.value[index-1],tmpstr);
			ov_string_setvalue(&tmpstr,NULL);
		}

		/* update Attributes of SoSContainer*/
		SoSContainerUpdate.pTarget = Ov_DynamicPtrCast(ov_domain,pSoSContainerToBeUpdated);
		sosx_informationModelManagement_SimpleSoSContainerUpdate(&SoSContainerUpdate);

		/* update children */
		/* find the caex InstanceHierarchy */
		Ov_ForEachChildEx(ov_containment,pUpdate,pInHier,caex_InstanceHierarchy){
			/* skip the TopLevelInternalElement of the InstanceHierarchy */
			Ov_ForEachChildEx(ov_containment,pInHier,pTopLevelInternalElement,caex_CAEXObject){

				/* go through all children an Update */
				result = updateChildren(pTopLevelInternalElement,Ov_DynamicPtrCast(ov_domain,pSoSContainerToBeUpdated),updateType);
				if (Ov_Fail(result)) {
					log_error("Could not update all children");
					Finally();
					return result;
				}
			}
		}
		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children */
		/* find the caex InstanceHierarchy */
		Ov_ForEachChildEx(ov_containment,pUpdate,pInHier,caex_InstanceHierarchy){
			/* skip the TopLevelInternalElement of the InstanceHierarchy */
			Ov_ForEachChildEx(ov_containment,pInHier,pTopLevelInternalElement,caex_CAEXObject){

				/* go through all children an Update */
				result = updateChildren(pTopLevelInternalElement,Ov_DynamicPtrCast(ov_domain,pSoSContainerToBeUpdated),updateType);
				if (Ov_Fail(result)) {
					log_error("Could not update all children");
					Finally();
					return result;
				}
			}
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}

/**
 * @param pSystemToBeUpdated
 * @param pUpdate
 * @return
 */
OV_RESULT sosx_workflowManagement_updateSystem(
		OV_INSTPTR_sosx_System				pSystemToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_caex_CAEXObject				*pLibList		= NULL;
	OV_INSTPTR_caex_Value					pValue			= NULL;
	OV_INSTPTR_caex_Attribute				pTempA			= NULL;
	OV_STRING_VEC							externalInfoVec	= {0,NULL};
	OV_UINT									LenLibList		= 0;
	SOSX_SystemDescription					SystemUpdate = {NULL};


#undef Finally
#define Finally() 										\
		freeSystemDescription(&SystemUpdate);			\
		if(externalInfoVec.value){						\
			ov_string_freelist(externalInfoVec.value);} \
			if(LenLibList < 0 ){						\
				freeLibList(&pLibList,LenLibList);}		\

	if (pSystemToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("SystemToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pSystemToBeUpdated->v_name);
			Finally();
			return result;
		}

		/* collect attributes*/
		/* source */
		SystemUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* name */
		ov_string_setvalue(&(SystemUpdate.Name), pUpdate->v_Name);

		/* caexLibrary */
		if(Ov_CanCastTo(caex_InternalElement,pUpdate)){
			ov_string_setvalue(&(SystemUpdate.CaexLib), Ov_DynamicPtrCast(caex_InternalElement,pUpdate)->v_RefBaseSystemUnitPath);
		}

		/* externalInfo */
		/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first externalReference specified then break */
		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"externalInfo",caex_Attribute);
			if(pTempA != NULL){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						if(ov_string_match(pValue->v_Value,"*,*")){
							externalInfoVec.value = ov_string_split(pValue->v_Value,",",&externalInfoVec.veclen);
							Ov_SetDynamicVectorValue(&SystemUpdate.externalInfo,&externalInfoVec.value,externalInfoVec.veclen,STRING);
						}else{
							Ov_SetDynamicVectorLength(&SystemUpdate.externalInfo,1,STRING);
							ov_string_setvalue(&(SystemUpdate.externalInfo.value[0]), pValue->v_Value);
						}
					}
				}
				break;
			}
		}

		/* get validFrom and validUntil */
		getLifeCycle(pLibList[0],pTempA,pValue,SystemUpdate);

		/* update Attributes of System*/
		SystemUpdate.pTarget = Ov_DynamicPtrCast(ov_domain,pSystemToBeUpdated);
		result = sosx_informationModelManagement_SimpleSystemUpdate(&SystemUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pSystemToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/*update children of the system*/
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pSystemToBeUpdated),updateType);
		if(Ov_Fail(result)){
			logfile_error("Could not update children of ",pSystemToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children only */
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pSystemToBeUpdated),updateType);
		if (Ov_Fail(result)) {
			log_error("Could not update all children");
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}



/**
 * @param pProcessToBeUpdated
 * @param pUpdate
 * @param updateType
 * @return
 */
OV_RESULT sosx_workflowManagement_updateProcess(
		OV_INSTPTR_sosx_Process				pProcessToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_STRING_VEC							externalInfoVec		= {0,NULL};
	OV_UINT									LenLibList			= 0;
	SOSX_ProcessDescription					ProcessUpdate		= {NULL};

#undef Finally
#define Finally() \
		freeProcessDescription(&ProcessUpdate);		\
		if(externalInfoVec.value){					\
			ov_string_freelist(externalInfoVec.value);}	\
			freeLibList(&pLibList,LenLibList);			\

	/*check if SystemToBeUpdate or pUpdate is NULL*/
	if (pProcessToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("ProcessToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pProcessToBeUpdated->v_name);
			Finally();
			return result;
		}

		/* collect attributes*/
		/* source */
		ProcessUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* name */
		ov_string_setvalue(&(ProcessUpdate.Name), pUpdate->v_Name);

		/* caexLibrary */
		if(Ov_CanCastTo(caex_InternalElement,pUpdate)){
			ov_string_setvalue(&(ProcessUpdate.CaexLib), Ov_DynamicPtrCast(caex_InternalElement,pUpdate)->v_RefBaseSystemUnitPath);
		}

		/* externalInfo */
		/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first externalReference specified then break */
		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"externalInfo",caex_Attribute);
			if(pTempA != NULL){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						if(ov_string_match(pValue->v_Value,"*,*")){
							externalInfoVec.value = ov_string_split(pValue->v_Value,",",&externalInfoVec.veclen);
							Ov_SetDynamicVectorValue(&ProcessUpdate.externalInfo,&externalInfoVec.value,externalInfoVec.veclen,STRING);
						}else{
							Ov_SetDynamicVectorLength(&ProcessUpdate.externalInfo,1,STRING);
							ov_string_setvalue(&(ProcessUpdate.externalInfo.value[0]), pValue->v_Value);
						}
					}
				}
				break;
			}
		}

		/* get validFrom and validUntil */
		getLifeCycle(pLibList[0],pTempA,pValue,ProcessUpdate);

		/* update Attributes of Process */
		ProcessUpdate.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pProcessToBeUpdated);
		result = sosx_informationModelManagement_SimpleProcessUpdate(&ProcessUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pProcessToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/*update children of the Process*/
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pProcessToBeUpdated),updateType);
		if(Ov_Fail(result)){
			logfile_error("Could not update children of ",pProcessToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children only */
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pProcessToBeUpdated),updateType);
		if (Ov_Fail(result)) {
			log_error("Could not update all children");
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}
/**
 * @param pPortToBeUpdated
 * @param pUpdate
 * @param updateType
 * @return
 */
OV_RESULT sosx_workflowManagement_updatePort(
		OV_INSTPTR_sosx_Port				pPortToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_UINT									LenLibList			= 0;
	SOSX_PortDescription					PortUpdate			= {NULL};

#undef Finally
#define Finally() 							\
		freePortDescription(&PortUpdate);	\
		freeLibList(&pLibList,LenLibList);	\

	if (pPortToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("PortToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pPortToBeUpdated->v_name);
			Finally();
			return result;
		}

		/* collect attributes*/
		/* source */
		PortUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* name */
		ov_string_setvalue(&(PortUpdate.Name), pUpdate->v_Name);

		/* caexLibrary */
		if(Ov_CanCastTo(caex_InternalElement,pUpdate)){
			ov_string_setvalue(&(PortUpdate.CaexLib), Ov_DynamicPtrCast(caex_InternalElement,pUpdate)->v_RefBaseSystemUnitPath);
		}

		/* get validFrom and validUntil */
		getLifeCycle(pLibList[0],pTempA,pValue,PortUpdate);

		/* StreamType */
		/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first StreamType specified then break */
		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"StreamType",caex_Attribute);
			if(pTempA){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						ov_string_setvalue(&(PortUpdate.StreamType), pValue->v_Value);
					}
					break;
				}
			}
		}

		/* wasConnectedTo */
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"wasConnectedTo",caex_Attribute);
		if(pTempA){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if(pValue->v_Value){
					ov_string_setvalue(&(PortUpdate.wasConnectedTo), pValue->v_Value);
				}
			}
		}

		/* try to find all InternalLinks */
		result = findInternalLinks(pLibList[0],&(PortUpdate.isLinkedTo));
		if (Ov_Fail(result)){
			logfile_warning("Cannot find all InternalLinks of Port:", pPortToBeUpdated->v_name);
		}

		/* update Attributes of Port*/
		PortUpdate.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pPortToBeUpdated);
		result = sosx_informationModelManagement_SimplePortUpdate(&PortUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pPortToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/*update children of the Port*/
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pPortToBeUpdated),updateType);
		if(Ov_Fail(result)){
			logfile_error("Could not update children of ",pPortToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children only */
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pPortToBeUpdated),updateType);
		if (Ov_Fail(result)) {
			log_error("Could not update all children");
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}

/**
 *
 * @param pSourceSinkToBeUpdated
 * @param pUpdate
 * @param updateType
 * @return
 */
OV_RESULT sosx_workflowManagement_updateSourceSink(
		OV_INSTPTR_sosx_SourceSink			pSourceSinkToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_UINT									LenLibList			= 0;
	SOSX_SourceSinkDescription				SourceSinkUpdate	= {NULL};


#undef Finally
#define Finally() 										\
		freeSourceSinkDescription(&SourceSinkUpdate);	\
		freeLibList(&pLibList,LenLibList);				\

	if (pSourceSinkToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("PortToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pSourceSinkToBeUpdated->v_name);
			Finally();
			return result;
		}

		/* collect attributes*/
		/* source */
		SourceSinkUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* name */
		ov_string_setvalue(&(SourceSinkUpdate.Name), pUpdate->v_Name);

		/* caexLibrary */
		if(Ov_CanCastTo(caex_InternalElement,pUpdate)){
			ov_string_setvalue(&(SourceSinkUpdate.CaexLib), Ov_DynamicPtrCast(caex_InternalElement,pUpdate)->v_RefBaseSystemUnitPath);
		}

		/* get validFrom and validUntil */
		getLifeCycle(pLibList[0],pTempA,pValue,SourceSinkUpdate);

		/* StreamType */
		/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first StreamType specified then break */
		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"StreamType",caex_Attribute);
			if(pTempA){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						ov_string_setvalue(&(SourceSinkUpdate.StreamType), pValue->v_Value);
					}
					break;
				}
			}
		}

		/* wasConnectedTo */
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"wasConnectedTo",caex_Attribute);
		if(pTempA){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if(pValue->v_Value){
					ov_string_setvalue(&(SourceSinkUpdate.wasConnectedTo), pValue->v_Value);
				}
			}
		}

		/* try to find all InternalLinks */
		result = findInternalLinks(pLibList[0],&(SourceSinkUpdate.isLinkedTo));
		if (Ov_Fail(result)){
			logfile_warning("Cannot find all InternalLinks of DistributionNode:", pSourceSinkToBeUpdated->v_name);
		}

		/* update Attributes of SourceSink*/
		SourceSinkUpdate.pTarget = Ov_DynamicPtrCast(ov_domain,pSourceSinkToBeUpdated);
		result = sosx_informationModelManagement_SimpleSourceSinkUpdate(&SourceSinkUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pSourceSinkToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/*update children of the SourceSink*/
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pSourceSinkToBeUpdated),updateType);
		if(Ov_Fail(result)){
			logfile_error("Could not update children of ",pSourceSinkToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children only */
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pSourceSinkToBeUpdated),updateType);
		if (Ov_Fail(result)) {
			log_error("Could not update all children");
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}

/**
 *
 * @param pDistributionNodeToBeUpdated
 * @param pUpdate
 * @param updateType
 * @return
 */
OV_RESULT sosx_workflowManagement_updateDistributionNode(
		OV_INSTPTR_sosx_DistributionNode	pDistributionNodeToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result							= OV_ERR_OK;
	OV_INSTPTR_caex_Attribute				pTempA							= NULL;
	OV_INSTPTR_caex_Value					pValue							= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList						= NULL;
	OV_UINT									LenLibList						= 0;
	SOSX_DistributionNodeDescription		DistributionNodeUpdate 			= {NULL};

#undef Finally
#define Finally() \
		freeDistributionNodeDescription(&DistributionNodeUpdate);	\
		freeLibList(&pLibList,LenLibList);							\

	if (pDistributionNodeToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("pDistributionNodeToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pDistributionNodeToBeUpdated->v_name);
			Finally();
			return result;
		}

		/* collect attributes*/
		/* source */
		DistributionNodeUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* name */
		ov_string_setvalue(&(DistributionNodeUpdate.Name), pUpdate->v_Name);

		/* caexLibrary */
		if(Ov_CanCastTo(caex_InternalElement,pUpdate)){
			ov_string_setvalue(&(DistributionNodeUpdate.CaexLib), Ov_DynamicPtrCast(caex_InternalElement,pUpdate)->v_RefBaseSystemUnitPath);
		}

		/* get validFrom and validUntil */
		getLifeCycle(pLibList[0],pTempA,pValue,DistributionNodeUpdate);

		/* StreamType */
		/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first StreamType specified then break */
		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"StreamType",caex_Attribute);
			if(pTempA){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						ov_string_setvalue(&(DistributionNodeUpdate.StreamType), pValue->v_Value);
					}
					break;
				}
			}
		}

		/* wasConnectedTo */
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"wasConnectedTo",caex_Attribute);
		if(pTempA){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if(pValue->v_Value){
					ov_string_setvalue(&(DistributionNodeUpdate.wasConnectedTo), pValue->v_Value);
				}
			}
		}

		/* try to find all InternalLinks */
		result = findInternalLinks(pLibList[0],&(DistributionNodeUpdate.isLinkedTo));
		if (Ov_Fail(result)){
			logfile_warning("Cannot find all InternalLinks of DistributionNode:", pDistributionNodeToBeUpdated->v_name);
		}

		/* update Attributes of pDistributionNodeToBeUpdated*/
		DistributionNodeUpdate.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pDistributionNodeToBeUpdated);
		result = sosx_informationModelManagement_SimpleDistributionNodeUpdate(&DistributionNodeUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pDistributionNodeToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/*update children of the DistributionNode*/
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pDistributionNodeToBeUpdated),updateType);
		if(Ov_Fail(result)){
			logfile_error("Could not update children of ",pDistributionNodeToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children only */
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pDistributionNodeToBeUpdated),updateType);
		if (Ov_Fail(result)) {
			log_error("Could not update all children");
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}
/**
 *
 * @param pPropertyToBeUpdated
 * @param pUpdate
 * @param updateType
 * @return
 */
OV_RESULT sosx_workflowManagement_updateProperty(
		OV_INSTPTR_sosx_Property			pPropertyToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_UINT									LenLibList			= 0;
	SOSX_PropertyDescription				PropertyUpdate		= {NULL};

#undef Finally
#define Finally() \
		freePropertyDescription(&PropertyUpdate);	\
		freeLibList(&pLibList,LenLibList);			\

	if (pPropertyToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("PortToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pPropertyToBeUpdated->v_name);
			Finally();
			return result;
		}

		/* collect attributes*/
		/* source */
		PropertyUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* name */
		ov_string_setvalue(&(PropertyUpdate.Name), pUpdate->v_Name);

		/* caexLibrary */
		if(Ov_CanCastTo(caex_InternalElement,pUpdate)){
			ov_string_setvalue(&(PropertyUpdate.CaexLib), Ov_DynamicPtrCast(caex_InternalElement,pUpdate)->v_RefBaseSystemUnitPath);
		}

		/* update Attributes of Property*/
		PropertyUpdate.pTarget = Ov_DynamicPtrCast(ov_domain,pPropertyToBeUpdated);
		result = sosx_informationModelManagement_SimplePropertyUpdate(&PropertyUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pPropertyToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/*update children of the Property*/
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pPropertyToBeUpdated),updateType);
		if(Ov_Fail(result)){
			logfile_error("Could not update children of ",pPropertyToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children only */
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pPropertyToBeUpdated),updateType);
		if (Ov_Fail(result)) {
			log_error("Could not update all children");
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}
/**
 *
 * @param pPropertyInformationToBeUpdated
 * @param pUpdate
 * @param updateType
 * @return
 */
OV_RESULT sosx_workflowManagement_updatePropertyInformation(
		OV_INSTPTR_sosx_PropertyInformation		pPropertyInformationToBeUpdated,
		OV_INSTPTR_caex_CAEXObject				pUpdate,
		SOSX_UPDATE_TYPE						updateType
){
	OV_RESULT									result							= OV_ERR_OK;
	OV_INSTPTR_caex_CAEXObject					*pLibList						= NULL;
	OV_INSTPTR_caex_RoleRequirements			pRoleReq						= NULL;
	OV_INSTPTR_caex_Attribute					pTempA							= NULL;
	OV_INSTPTR_caex_Value						pValue							= NULL;
	OV_UINT										LenLibList						= 0;
	OV_STRING_VEC								ListBuf							= {0,NULL};
	OV_STRING_VEC								timeStampList					= {0,NULL};
	SOSX_PropertyInformationDescription			PropertyInformationUpdate		= {NULL};


	OV_TIME_SPAN							oneHour							= {-3600,0};

#undef Finally
#define Finally() \
		freePropertyInformationDescription(&PropertyInformationUpdate);		\
		if(ListBuf.value != NULL){											\
			ov_string_freelist(ListBuf.value);								\
			ListBuf.veclen = 0;}											\
		if(timeStampList.value != NULL){									\
			ov_string_freelist(timeStampList.value);						\
			timeStampList.veclen = 0;}										\
		freeLibList(pLibList,LenLibList);									\

	if (pPropertyInformationToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("PortToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pPropertyInformationToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/* collect attributes */
		/* source */
		PropertyInformationUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* caexLibrary */
		pRoleReq = Ov_SearchChildEx(ov_containment,pLibList[0],"RoleRequirements",caex_RoleRequirements);
		if(pRoleReq){
			ov_string_setvalue(&(PropertyInformationUpdate.CaexLib),pRoleReq->v_RefBaseRoleClassPath);
		}

		/* get validFrom and validUntil */
		getLifeCycle(pLibList[0],pTempA,pValue,PropertyInformationUpdate);
		PropertyInformationUpdate.value.time = PropertyInformationUpdate.validFrom;

		/* value */
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"value",caex_Attribute);
		if (pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if(pValue->v_Value){
					PropertyInformationUpdate.value.value.vartype = stringToDatatype(pTempA->v_AttributeDataType);
					switch (PropertyInformationUpdate.value.value.vartype){

					case OV_VT_BOOL :
						PropertyInformationUpdate.value.value.valueunion.val_bool = atoi(pValue->v_Value);
						break;

					case OV_VT_STRING :
						ov_string_setvalue(&PropertyInformationUpdate.value.value.valueunion.val_string,pValue->v_Value);
						break;

					case OV_VT_INT :
						PropertyInformationUpdate.value.value.valueunion.val_int = atoi(pValue->v_Value);
						break;

					case OV_VT_UINT :
						PropertyInformationUpdate.value.value.valueunion.val_uint = atoi(pValue->v_Value);
						break;

					case OV_VT_SINGLE :
						PropertyInformationUpdate.value.value.valueunion.val_single = atof(pValue->v_Value);
						break;

					case OV_VT_DOUBLE :
						PropertyInformationUpdate.value.value.valueunion.val_double = atof(pValue->v_Value);
						break;

					default :
						logfile_error("unknown datatype",PropertyInformationUpdate.Identifier);
						return OV_ERR_BADTYPE;
					}
				}
			}
		}

		/* valueVec */
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"valueVec",caex_Attribute);
		if (pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if( (pValue->v_Value) && (ov_string_compare(pValue->v_Value,"(null)") == OV_STRCMP_EQUAL) ){
					break;
				}

				switch (PropertyInformationUpdate.value.value.vartype){

				case OV_VT_BOOL : PropertyInformationUpdate.valueVec.value.vartype = OV_VT_BOOL_VEC;
				ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
				Ov_SetDynamicVectorLength(&PropertyInformationUpdate.valueVec.value.valueunion.val_bool_vec,ListBuf.veclen,BOOL);
				for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
					PropertyInformationUpdate.valueVec.value.valueunion.val_bool_vec.value[i] = atoi(ListBuf.value[ListBuf.veclen - 1 - i]);
				}
				break;

				case OV_VT_STRING : PropertyInformationUpdate.valueVec.value.vartype = OV_VT_STRING_VEC;
				ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
				Ov_SetDynamicVectorLength(&PropertyInformationUpdate.valueVec.value.valueunion.val_string_vec,ListBuf.veclen,STRING);
				for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
					ov_string_setvalue(&PropertyInformationUpdate.valueVec.value.valueunion.val_string_vec.value[i],ListBuf.value[ListBuf.veclen - 1 - i]);
				}
				break;

				case OV_VT_INT : PropertyInformationUpdate.valueVec.value.vartype = OV_VT_INT_VEC;
				ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
				Ov_SetDynamicVectorLength(&PropertyInformationUpdate.valueVec.value.valueunion.val_int_vec,ListBuf.veclen,INT);
				for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
					PropertyInformationUpdate.valueVec.value.valueunion.val_int_vec.value[i] = atoi(ListBuf.value[ListBuf.veclen - 1 - i]);
				}
				break;

				case OV_VT_UINT : PropertyInformationUpdate.valueVec.value.vartype = OV_VT_UINT_VEC;
				ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
				Ov_SetDynamicVectorLength(&PropertyInformationUpdate.valueVec.value.valueunion.val_uint_vec,ListBuf.veclen,UINT);
				for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
					PropertyInformationUpdate.valueVec.value.valueunion.val_uint_vec.value[i] = atoi(ListBuf.value[ListBuf.veclen - 1- i]);
				}
				break;

				case OV_VT_SINGLE : PropertyInformationUpdate.valueVec.value.vartype = OV_VT_SINGLE_VEC;
				ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
				Ov_SetDynamicVectorLength(&PropertyInformationUpdate.valueVec.value.valueunion.val_single_vec,ListBuf.veclen,SINGLE);
				for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
					PropertyInformationUpdate.valueVec.value.valueunion.val_single_vec.value[i] = atof(ListBuf.value[ListBuf.veclen - 1- i]);
				}
				break;

				case OV_VT_DOUBLE : PropertyInformationUpdate.valueVec.value.vartype = OV_VT_DOUBLE_VEC;
				ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
				Ov_SetDynamicVectorLength(&PropertyInformationUpdate.valueVec.value.valueunion.val_double_vec,ListBuf.veclen,DOUBLE);
				for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
					PropertyInformationUpdate.valueVec.value.valueunion.val_double_vec.value[i] = atof(ListBuf.value[ListBuf.veclen - 1- i]);
				}
				break;

				default :
					logfile_error("unknown datatype",PropertyInformationUpdate.Identifier);
					return OV_ERR_BADTYPE;
				}
			}
		}

		/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first type, source, unit specified then break */
		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"type",caex_Attribute);
			if (pTempA != NULL){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						ov_string_setvalue(&(PropertyInformationUpdate.type), pValue->v_Value);
					}
					break;
				}
			}
		}
		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"source",caex_Attribute);
			if (pTempA != NULL){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						ov_string_setvalue(&(PropertyInformationUpdate.source), pValue->v_Value);
					}
					break;
				}
			}
		}

		for (OV_UINT y = 0 ; y < LenLibList ; y++){
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"unit",caex_Attribute);
			if (pTempA != NULL){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						ov_string_setvalue(&(PropertyInformationUpdate.unit), pValue->v_Value);
					}
					break;
				}
			}
		}

		/* update timeStamps */
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"timeStamps",caex_Attribute);
		if (pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				timeStampList.value = ov_string_split(pValue->v_Value,",",&timeStampList.veclen);
				Ov_SetDynamicVectorLength(&PropertyInformationUpdate.timeStamps,timeStampList.veclen,TIME);

				for(OV_INT i = timeStampList.veclen - 1; i >= 0; i--){
					ov_time_asciitotime(&PropertyInformationUpdate.timeStamps.value[i],timeStampList.value[timeStampList.veclen - 1- i]);
				}
			}
		}

		/* update Attributes of PropertyInformation */
		PropertyInformationUpdate.pTarget = Ov_DynamicPtrCast(ov_domain,pPropertyInformationToBeUpdated);
		result = sosx_informationModelManagement_SimplePropertyInformationUpdate(&PropertyInformationUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pPropertyInformationToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/* do not update children */

		Finally();
		return result;
	}

	/***********************************************************************
	* UPDATE SIM RES ONLY
	***********************************************************************/
	case SOSX_UPDATE_SIMRESONLY :{
		if(checkPropertyInfoType(pUpdate,SIMULATIONRESULT)){
			/* getLibList */
			result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
			if (Ov_Fail(result)){
				logfile_error("Cannot resolve the library path of ", pPropertyInformationToBeUpdated->v_identifier);
				Finally();
				return result;
			}

			/* collect attributes */
			/* source */
			PropertyInformationUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

			/* caexLibrary */
			pRoleReq = Ov_SearchChildEx(ov_containment,pLibList[0],"RoleRequirements",caex_RoleRequirements);
			if(pRoleReq){
				ov_string_setvalue(&(PropertyInformationUpdate.CaexLib),pRoleReq->v_RefBaseRoleClassPath);
			}

			/* get validFrom and validUntil */
			getLifeCycle(pLibList[0],pTempA,pValue,PropertyInformationUpdate);
			ov_time_add(&PropertyInformationUpdate.value.time,&PropertyInformationUpdate.validFrom,&oneHour);

			/* value */
			pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"value",caex_Attribute);
			if (pTempA != NULL){
				Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
					if(pValue->v_Value){
						PropertyInformationUpdate.value.value.vartype = stringToDatatype(pTempA->v_AttributeDataType);
						switch (PropertyInformationUpdate.value.value.vartype){

						case OV_VT_BOOL :
							PropertyInformationUpdate.value.value.valueunion.val_bool = atoi(pValue->v_Value);
							break;

						case OV_VT_STRING :
							ov_string_setvalue(&PropertyInformationUpdate.value.value.valueunion.val_string,pValue->v_Value);
							break;

						case OV_VT_INT :
							PropertyInformationUpdate.value.value.valueunion.val_int = atoi(pValue->v_Value);
							break;

						case OV_VT_UINT :
							PropertyInformationUpdate.value.value.valueunion.val_uint = atoi(pValue->v_Value);
							break;

						case OV_VT_SINGLE :
							PropertyInformationUpdate.value.value.valueunion.val_single = atof(pValue->v_Value);
							break;

						case OV_VT_DOUBLE :
							PropertyInformationUpdate.value.value.valueunion.val_double = atof(pValue->v_Value);
							break;

						default :
							logfile_error("unknown datatype",PropertyInformationUpdate.Identifier);
							return OV_ERR_BADTYPE;
						}
					}
				}
			}

			/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first type, source, unit specified then break */
			for (OV_UINT y = 0 ; y < LenLibList ; y++){
				pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"type",caex_Attribute);
				if (pTempA != NULL){
					Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
						if(pValue->v_Value){
							ov_string_setvalue(&(PropertyInformationUpdate.type), pValue->v_Value);
						}
						break;
					}
				}
			}
			for (OV_UINT y = 0 ; y < LenLibList ; y++){
				pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"source",caex_Attribute);
				if (pTempA != NULL){
					Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
						if(pValue->v_Value){
							ov_string_setvalue(&(PropertyInformationUpdate.source), pValue->v_Value);
						}
						break;
					}
				}
			}

			for (OV_UINT y = 0 ; y < LenLibList ; y++){
				pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"unit",caex_Attribute);
				if (pTempA != NULL){
					Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
						if(pValue->v_Value){
							ov_string_setvalue(&(PropertyInformationUpdate.unit), pValue->v_Value);
						}
						break;
					}
				}
			}

			/* update Attributes of PropertyInformation */
			PropertyInformationUpdate.pTarget = Ov_DynamicPtrCast(ov_domain,pPropertyInformationToBeUpdated);
			result = sosx_informationModelManagement_SimplePropertyInformationUpdate(&PropertyInformationUpdate);
			if(Ov_Fail(result)){
				logfile_error("Update failed",pPropertyInformationToBeUpdated->v_identifier);
				Finally();
				return result;
			}

			/* do not update children */

			Finally();
			return result;
		}
		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		Finally();
		return OV_ERR_NOTIMPLEMENTED;
	}
}

/**
 *
 * @param pStreamToBeUpdated
 * @param pUpdate
 * @param updateType
 * @return
 */
OV_RESULT sosx_workflowManagement_updateStream(
		OV_INSTPTR_sosx_Stream				pStreamToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_caex_RoleRequirements		pRoleReq			= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_UINT									LenLibList			= 0;
	SOSX_StreamDescription					StreamUpdate;


#undef Finally
#define Finally() \
		freeStreamDescription(&StreamUpdate);	\
		freeLibList(&pLibList,LenLibList);		\

	if (pStreamToBeUpdated == NULL
			|| pUpdate == NULL){
		log_error("PortToBeUpdated and/or Update not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	switch(updateType){
	case SOSX_UPDATE_COMPLETE : {
		/* getLibraryList */
		result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pUpdate),&pLibList,&LenLibList);
		if (Ov_Fail(result)){
			logfile_error("Cannot resolve the library path of ", pStreamToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/* source */
		StreamUpdate.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pUpdate);

		/* caexLibrary */
		pRoleReq = Ov_SearchChildEx(ov_containment,pLibList[0],"RoleRequirements",caex_RoleRequirements);
		if(pRoleReq){
			ov_string_setvalue(&(StreamUpdate.CaexLib),pRoleReq->v_RefBaseRoleClassPath);
		}

		/* get validFrom and validUntil */
		getLifeCycle(pLibList[0],pTempA,pValue,StreamUpdate);

		/* try to find all InternalLinks */
		result = findInternalLinks(pLibList[0],&(StreamUpdate.isLinkedTo));
		if (Ov_Fail(result)){
			logfile_warning("Cannot find all InternalLinks of DistributionNode:", StreamUpdate.Identifier);
		}

		/* update Attributes of PropertyInformation */
		StreamUpdate.pTarget = Ov_DynamicPtrCast(ov_domain,pStreamToBeUpdated);
		result = sosx_informationModelManagement_SimpleStreamUpdate(&StreamUpdate);
		if(Ov_Fail(result)){
			logfile_error("Update failed",pStreamToBeUpdated->v_identifier);
			Finally();
			return result;
		}

		/* do not update children */

		Finally();
		return result;
	}
	case SOSX_UPDATE_SIMRESONLY :{

		/* update children only */
		result = updateChildren(pUpdate,Ov_DynamicPtrCast(ov_domain,pStreamToBeUpdated),updateType);
		if (Ov_Fail(result)) {
			log_error("Could not update all children");
			Finally();
			return result;
		}

		Finally();
		return result;
	}
	default :
		log_error("Update type not implemented");
		return OV_ERR_NOTIMPLEMENTED;
	}
}



#endif
