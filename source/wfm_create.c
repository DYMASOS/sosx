/******************************************************************************
 *
 *   FILE
 *   ----
 *   create.c
 *
 *   History
 *   -------
 *   2014-11-13   File created
 *
 *******************************************************************************/
#ifndef OV_COMPILE_LIBRARY_sosx
#define OV_COMPILE_LIBRARY_sosx

#include "workflowManagement.h"


#define undoCreateInCaseOfError(result,pSosx)				\
		if(Ov_Fail(result)){								\
			if(pSosx != NULL){								\
				log_info("Error occurred");					\
				Ov_DeleteObject(pSosx);						\
			}												\
		}													\

/**
 * createSoSContainer - This function will create a SoSContainer and its InternalStructure based on a CAEX file
 * @param pobj - pointer to the api instance that creates the SoSContainer
 * @param pTargetElement - pointer to the ov_domain in which the SoSContainer will be created.
 * @param pInternalElement - pointer to the CEAX File that specifies the SoSContainer and its internal structure.
 * @return - the result of the SoSContainer creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createSoSContainer(
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_INSTPTR_caex_CAEXFile			pCaexFile
){
	OV_RESULT								result								= OV_ERR_OK;
	OV_INSTPTR_caex_InstanceHierarchy		pInHier								= NULL;
	OV_INSTPTR_caex_ExternalReference		pExternalRef						= NULL;
	OV_INSTPTR_caex_InternalElement			pTopLevelInternalElement			= NULL;
	OV_INSTPTR_caex_InternalElement			pTempCaex							= NULL;
	OV_INSTPTR_sosx_SoSContainer			pSoSContainer						= NULL;
	OV_STRING								FileName							= NULL;
	OV_STRING								tmpstr								= NULL;
	OV_UINT									index								= 0;
	SOSX_SoSContainerDescription			SoSContainerToBeCreated				= {NULL};

#undef Finally
#define Finally()													\
		freeSoSContainerDescription(&SoSContainerToBeCreated);		\
		ov_string_setvalue(&FileName,NULL); 						\
		ov_string_setvalue(&tmpstr,NULL); 							\

	/* check if TargetElement or InternalElement is NULL */
	if (!(pCaexFile) ||
			!(pTargetElement)){
		log_error("InternalElement and/or TargetElement not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* do not create a SoSContainer within an existing SoSX structure -> skip SoSContainer-Creation and start creating children */
	if(!(Ov_CanCastTo(sosx_BaseElement,pTargetElement) || Ov_CanCastTo(sosx_Property,pTargetElement))){

		/* set target */
		SoSContainerToBeCreated.pTarget = pTargetElement;

		/* collect attributes*/
		/* name */
		/* Remove '.xml' from Source */
		ov_string_setvalue(&tmpstr, pCaexFile->v_FileName);
		ov_string_setvalue(&FileName,strtok(tmpstr, "."));
		ov_string_setvalue(&tmpstr,NULL);
		if (!FileName) {
			log_error("No file name given");
			Finally();
			return OV_ERR_GENERIC;
		}
		ov_string_setvalue(&(SoSContainerToBeCreated.Name), FileName);

		/*  collect all externalRefrences */
		/* format AliasA@PathA */
		Ov_ForEachChildEx(ov_containment,pCaexFile,pExternalRef,caex_ExternalReference){
			if(ov_string_compare("BaseLibs",pExternalRef->v_Alias) != OV_STRCMP_EQUAL){
				ov_string_setvalue(&tmpstr,pExternalRef->v_Alias);
				ov_string_append(&tmpstr,"@");
				ov_string_append(&tmpstr,pExternalRef->v_Path);
				index++;
				Ov_SetDynamicVectorLength(&SoSContainerToBeCreated.externalReference,index,STRING);
				ov_string_setvalue(&SoSContainerToBeCreated.externalReference.value[index-1],tmpstr);
				ov_string_setvalue(&tmpstr,NULL);
			}
		}

		/* Create SoSContainer */
		result =sosx_informationModelManagement_createSimpleSoSContainer(&SoSContainerToBeCreated,&pSoSContainer);
		if (Ov_Fail(result)){
			logfile_error("Cannot create the SoSContainer:", FileName);
			Finally();
			return result;
		}
		pTargetElement = Ov_DynamicPtrCast(ov_domain,pSoSContainer);
	}

	/* create sosx structure*/
	/* find the caex InstanceHierarchy */
	Ov_ForEachChildEx(ov_containment,pCaexFile,pInHier,caex_InstanceHierarchy){
		/* skip the TopLevelInternalElement of the InstanceHierarchy */
		Ov_ForEachChildEx(ov_containment,pInHier,pTopLevelInternalElement,caex_InternalElement){
			/* create all children of the TopLevelInternalElement */
			Ov_ForEachChildEx(ov_containment,pTopLevelInternalElement,pTempCaex,caex_InternalElement){
				result = sosx_workflowManagement_createElement(pTargetElement,Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
				if(Ov_Fail(result)){
					break;
				}
			}
		}
	}

	undoCreateInCaseOfError(result,pSoSContainer);

	Finally();
	return result;
}

/**
 * createSystem - This function will create a System and its InternalStructure based on a CAEX file
 * @param pobj - pointer to the api instance that creates the System
 * @param pTargetElement - pointer to the element in which the System will be created. (Can either be a SoSContainer or a System)
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies the System and its internal structure.
 * @return - the result of the System creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createSystem(
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_sosx_System					pSystem				= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_INSTPTR_caex_InternalElement			pTempCaex			= NULL;

	OV_UINT									LenLibList			= 0;
	OV_STRING_VEC							externalInfoVec		= {0,NULL};
	OV_RESULT								result				= OV_ERR_OK;
	SOSX_SystemDescription					SystemToBeCreated	= {NULL};

#undef Finally
#define Finally()										\
		freeSystemDescription(&SystemToBeCreated);		\
		ov_free(pLibList);								\
		ov_string_freelist(externalInfoVec.value);		\

	/* check if TargetElement or InternalElement is NULL */
	if (!(pInternalElement) ||
			!(pTargetElement)){
		log_error("InternalElement and/or TargetElement not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get the LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* set source */
	SystemToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	SystemToBeCreated.pTarget = pTargetElement;

	/* collect attributes*/
	/* name */
	ov_string_setvalue(&(SystemToBeCreated.Name), pInternalElement->v_Name);

	/* caexLibrary */
	ov_string_setvalue(&(SystemToBeCreated.CaexLib), pInternalElement->v_RefBaseSystemUnitPath);

	/* externalInfo */
	/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first externalReference specified then break */
	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"externalInfo",caex_Attribute);
		if(pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if(ov_string_match(pValue->v_Value,"*,*")){
					externalInfoVec.value = ov_string_split(pValue->v_Value,",",&externalInfoVec.veclen);
					SystemToBeCreated.externalInfo = externalInfoVec;
				}else{
					Ov_SetDynamicVectorLength(&SystemToBeCreated.externalInfo,1,STRING);
					ov_string_setvalue(&(SystemToBeCreated.externalInfo.value[0]), pValue->v_Value);
				}
			}
			break;
		}
	}

	/*get validFrom and validUntil*/
	getLifeCycle(pLibList[0],pTempA,pValue,SystemToBeCreated);

	/*get x and y position */
	getPos(pLibList[0],pTempA,pValue,SystemToBeCreated);

	/*get height and width */
	getHeightAndWidth(pLibList[0],pTempA,pValue,SystemToBeCreated);

	/* Create System */
	result = sosx_informationModelManagement_createSimpleSystem(&SystemToBeCreated,&pSystem);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the System:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* create all children of the system */
	Ov_ForEachChildEx(ov_containment,pInternalElement,pTempCaex,caex_InternalElement){
		result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pSystem),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
		if(Ov_Fail(result)){
			break;
		}
	}

	undoCreateInCaseOfError(result,pSystem);
	Finally();
	return result;
}

/**
 * createProcess - This function will create a Process and its Ports and Properties based on a CAEX file
 * @param pobj - pointer to the api instance that creates the Process
 * @param pTargetSystem - pointer to the System in which the Process will be created. (Can only be a System)
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies the Process and its Ports and Properties.
 * @return - the result of Process creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createProcess(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_sosx_Process					pProcess			= NULL;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_INSTPTR_caex_InternalElement			pTempCaex			= NULL;

	OV_UINT									LenLibList			= 0;
	OV_STRING_VEC							externalInfoVec		= {0,NULL};
	OV_RESULT								result				= OV_ERR_OK;
	SOSX_ProcessDescription					ProcessToBeCreated	= {NULL};


#undef Finally
#define Finally() 										\
		freeProcessDescription(&ProcessToBeCreated);	\
		ov_string_freelist(externalInfoVec.value);		\
		ov_free(pLibList);								\

	/* check if TargetSystem or InternalElement is NULL */
	if (!(pInternalElement) ||
			!(pTargetSystem)){
		log_error("InternalElement and/or TargetSystem not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get the LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* set source */
	ProcessToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	ProcessToBeCreated.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pTargetSystem);

	/* collect Attributes */
	/* name */
	ov_string_setvalue(&(ProcessToBeCreated.Name),pInternalElement->v_Name);

	/* caexLibrary */
	ov_string_setvalue(&(ProcessToBeCreated.CaexLib),pInternalElement->v_RefBaseSystemUnitPath);

	/* externalInfo */
	/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first externalReference specified then break */
	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"externalInfo",caex_Attribute);
		if(pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				if(ov_string_match(pValue->v_Value,"*,*")){
					externalInfoVec.value = ov_string_split(pValue->v_Value,",",&externalInfoVec.veclen);
					ProcessToBeCreated.externalInfo = externalInfoVec;
				}else{
					Ov_SetDynamicVectorLength(&ProcessToBeCreated.externalInfo,1,STRING);
					ov_string_setvalue(&(ProcessToBeCreated.externalInfo.value[0]), pValue->v_Value);
				}
			}
			break;
		}
	}

	/*get validFrom and validUntil*/
	getLifeCycle(pLibList[0],pTempA,pValue,ProcessToBeCreated);

	/*get x and y position */
	getPos(pLibList[0],pTempA,pValue,ProcessToBeCreated);

	/*get height and width */
	getHeightAndWidth(pLibList[0],pTempA,pValue,ProcessToBeCreated);

	/* create Process */
	result = sosx_informationModelManagement_createSimpleProcess(&ProcessToBeCreated,&pProcess);
	if(Ov_Fail(result)){
		logfile_error("Cannot create the Process:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* create all children of the process */
	Ov_ForEachChildEx(ov_containment,pInternalElement,pTempCaex,caex_InternalElement){
		result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pProcess),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
		if(Ov_Fail(result)){
			break;
		}
	}

	undoCreateInCaseOfError(result,pProcess);

	Finally();
	return result;
}

/**
 *createPropertyInformation -  This function will create a PropertyInformation based on a CAEX file
 * @param pobj - pointer to the api instance that creates the PropertyInformation
 * @param pTargetProperty - pointer to the Property in which the PropertyInformation will be created.
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies the PropertyInformation
 * @return - the result of the PropertyInformation creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createPropertyInformation(
		OV_INSTPTR_sosx_Property			pTargetProperty,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_caex_Attribute					pTempA							= NULL;
	OV_INSTPTR_caex_Value						pValue							= NULL;
	OV_INSTPTR_sosx_PropertyInformation			pPropertyInformation			= NULL;
	OV_INSTPTR_caex_CAEXObject					*pLibList						= NULL;
	OV_INSTPTR_caex_RoleRequirements			pRoleReq						= NULL;

	OV_STRING									*VecValue						= NULL;
	OV_STRING									*timeStampsList					= NULL;
	OV_STRING_VEC								ListBuf							= {0,NULL};
	OV_STRING									dataType						= NULL;
	OV_UINT										timeStampsListLen				= 0;
	OV_UINT										LenLibList						= 0;
	OV_RESULT									result							= OV_ERR_OK;
	SOSX_PropertyInformationDescription			PropertyInformationToBeCreated	= {NULL};


#undef Finally
#define Finally() \
		freePropertyInformationDescription(&PropertyInformationToBeCreated);	\
		ov_string_setvalue(&dataType,NULL);										\
		ov_string_freelist(VecValue);											\
		ov_string_freelist(ListBuf.value);										\
		ov_string_freelist(timeStampsList);										\
		ov_free(pLibList);														\


	/* check if TargetElement or InternalElement is NULL */
	if (!(pInternalElement) || !(pTargetProperty)){
		log_error("InternalElement and/or TargetElement not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get the LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}
	/* set source */
	PropertyInformationToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	PropertyInformationToBeCreated.pTarget = Ov_DynamicPtrCast(ov_domain,pTargetProperty);

	/* collect Attributes*/
	/* Identifier */
	result = ov_string_setvalue(&(PropertyInformationToBeCreated.Identifier),pInternalElement->v_identifier);

	/* caexLibrary */
	pRoleReq = Ov_SearchChildEx(ov_containment,pInternalElement,"RoleRequirements",caex_RoleRequirements);
	if(pRoleReq){
		result = ov_string_setvalue(&(PropertyInformationToBeCreated.CaexLib),pRoleReq->v_RefBaseRoleClassPath);
	}

	/*get validFrom and validUntil*/
	getLifeCycle(pLibList[0],pTempA,pValue,PropertyInformationToBeCreated);

	/*get x and y position */
	getPos(pLibList[0],pTempA,pValue,PropertyInformationToBeCreated);

	/* value */
	pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"value",caex_Attribute);
	if (pTempA != NULL){
		Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
			PropertyInformationToBeCreated.value.value.vartype = stringToDatatype(pTempA->v_AttributeDataType);
			PropertyInformationToBeCreated.dataType = stringToDatatype(pTempA->v_AttributeDataType);
			switch (PropertyInformationToBeCreated.value.value.vartype){

			case OV_VT_BOOL :
				PropertyInformationToBeCreated.value.value.valueunion.val_bool = atoi(pValue->v_Value);
				break;

			case OV_VT_STRING :
				ov_string_setvalue(&PropertyInformationToBeCreated.value.value.valueunion.val_string,pValue->v_Value);
				break;

			case OV_VT_INT :
				PropertyInformationToBeCreated.value.value.valueunion.val_int = strtol(pValue->v_Value,NULL,0);
				break;

			case OV_VT_UINT :
				PropertyInformationToBeCreated.value.value.valueunion.val_uint = strtol(pValue->v_Value,NULL,0);
				break;

			case OV_VT_SINGLE :
				PropertyInformationToBeCreated.value.value.valueunion.val_single = strtof(pValue->v_Value,NULL);
				break;

			case OV_VT_DOUBLE :
				PropertyInformationToBeCreated.value.value.valueunion.val_double = strtof(pValue->v_Value,NULL);
				break;

			default :
				logfile_error("unknown datatype",PropertyInformationToBeCreated.Identifier);
				return OV_ERR_BADTYPE;
			}

		}
	}

	/* valueVec */
	pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"valueVec",caex_Attribute);
	if (pTempA != NULL){
		Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){

			if(ov_string_compare(pValue->v_Value,"(null)") == OV_STRCMP_EQUAL){
				break;
			}

			switch (PropertyInformationToBeCreated.value.value.vartype){

			case OV_VT_BOOL : PropertyInformationToBeCreated.valueVec.value.vartype = OV_VT_BOOL_VEC;
			ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
			Ov_SetDynamicVectorLength(&PropertyInformationToBeCreated.valueVec.value.valueunion.val_bool_vec,ListBuf.veclen,BOOL);
			for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
				PropertyInformationToBeCreated.valueVec.value.valueunion.val_bool_vec.value[i] = atoi(ListBuf.value[ListBuf.veclen - 1 - i]);
			}
			break;

			case OV_VT_STRING : PropertyInformationToBeCreated.valueVec.value.vartype = OV_VT_STRING_VEC;
			ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
			Ov_SetDynamicVectorLength(&PropertyInformationToBeCreated.valueVec.value.valueunion.val_string_vec,ListBuf.veclen,STRING);
			for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
				ov_string_setvalue(&PropertyInformationToBeCreated.valueVec.value.valueunion.val_string_vec.value[i],ListBuf.value[ListBuf.veclen - 1 - i]);
			}
			break;

			case OV_VT_INT : PropertyInformationToBeCreated.valueVec.value.vartype = OV_VT_INT_VEC;
			ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
			Ov_SetDynamicVectorLength(&PropertyInformationToBeCreated.valueVec.value.valueunion.val_int_vec,ListBuf.veclen,INT);
			for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
				PropertyInformationToBeCreated.valueVec.value.valueunion.val_int_vec.value[i] = atoi(ListBuf.value[ListBuf.veclen - 1 - i]);
			}
			break;

			case OV_VT_UINT : PropertyInformationToBeCreated.valueVec.value.vartype = OV_VT_UINT_VEC;
			ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
			Ov_SetDynamicVectorLength(&PropertyInformationToBeCreated.valueVec.value.valueunion.val_uint_vec,ListBuf.veclen,UINT);
			for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
				PropertyInformationToBeCreated.valueVec.value.valueunion.val_uint_vec.value[i] = atoi(ListBuf.value[ListBuf.veclen - 1- i]);
			}
			break;

			case OV_VT_SINGLE : PropertyInformationToBeCreated.valueVec.value.vartype = OV_VT_SINGLE_VEC;
			ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
			Ov_SetDynamicVectorLength(&PropertyInformationToBeCreated.valueVec.value.valueunion.val_single_vec,ListBuf.veclen,SINGLE);
			for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
				PropertyInformationToBeCreated.valueVec.value.valueunion.val_single_vec.value[i] = atof(ListBuf.value[ListBuf.veclen - 1- i]);
			}
			break;

			case OV_VT_DOUBLE : PropertyInformationToBeCreated.valueVec.value.vartype = OV_VT_DOUBLE_VEC;
			ListBuf.value = ov_string_split(pValue->v_Value ,"," , &ListBuf.veclen);
			Ov_SetDynamicVectorLength(&PropertyInformationToBeCreated.valueVec.value.valueunion.val_double_vec,ListBuf.veclen,DOUBLE);
			for(OV_INT i = ListBuf.veclen - 1; i >= 0; i--){
				PropertyInformationToBeCreated.valueVec.value.valueunion.val_double_vec.value[i] = atof(ListBuf.value[ListBuf.veclen - 1- i]);
			}
			break;

			default :
				logfile_error("unknown datatype",PropertyInformationToBeCreated.Identifier);
				return OV_ERR_BADTYPE;
			}

		}
	}

	/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first type, source, unit specified then break */
	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"type",caex_Attribute);
		if (pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				ov_string_setvalue(&(PropertyInformationToBeCreated.type), pValue->v_Value);
				break;
			}
		}
	}
	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"source",caex_Attribute);
		if (pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				ov_string_setvalue(&(PropertyInformationToBeCreated.source), pValue->v_Value);
				break;
			}
		}
	}

	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"unit",caex_Attribute);
		if (pTempA != NULL){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				ov_string_setvalue(&(PropertyInformationToBeCreated.unit), pValue->v_Value);
				break;
			}
		}
	}


	pTempA = Ov_SearchChildEx(ov_containment,pLibList[0],"timeStamps",caex_Attribute);
	if (pTempA != NULL){
		Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
			timeStampsList = ov_string_split(pValue->v_Value,",",&timeStampsListLen);
			Ov_SetDynamicVectorLength(&PropertyInformationToBeCreated.timeStamps,timeStampsListLen,TIME);

			for(OV_INT i = timeStampsListLen - 1; i >= 0; i--){
				ov_time_asciitotime(&PropertyInformationToBeCreated.timeStamps.value[i],timeStampsList[timeStampsListLen - 1- i]);
			}
		}
	}

	/* create PropertyInformation*/
	result = sosx_informationModelManagement_createSimplePropertyInformation(&PropertyInformationToBeCreated,&pPropertyInformation);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the PropertyInformation:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	undoCreateInCaseOfError(result,pPropertyInformation);

	Finally();
	return result;
}

/**
 * createProperty -  This function will create a Property and its PropertyInformations based on a CAEX file
 * @param pobj - pointer to the api instance that creates the Property
 * @param pTargetElement - pointer to the element in which the Property will be created. (Can be a Process, a System, a Port, A DistributionNode, a SourceSink)
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies the Property and its PropertyInformations.
 * @return - the result of the Property creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createProperty(
		OV_INSTPTR_sosx_DetailedElement		pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_sosx_Property				pProperty			= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_UINT									LenLibList			= 0;
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	SOSX_PropertyDescription				PropertyToBeCreated	= {NULL};
	OV_INSTPTR_caex_InternalElement			pTempCaex			= NULL;

#undef Finally
#define Finally() 										\
		freePropertyDescription(&PropertyToBeCreated);	\
		ov_free(pLibList);								\

	/* check if TargetElement or InternalElement is NULL */
	if (!(pInternalElement) || !(pTargetElement)){
		log_error("InternalElement and/or TargetElement not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get the LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* set source */
	PropertyToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	PropertyToBeCreated.pTarget = Ov_DynamicPtrCast(ov_domain,pTargetElement);

	/* collect Attributes*/
	/* name */
	ov_string_setvalue(&(PropertyToBeCreated.Name),pInternalElement->v_Name);

	/* caexLibrary */
	ov_string_setvalue(&(PropertyToBeCreated.CaexLib),pInternalElement->v_RefBaseSystemUnitPath);

	/*get x and y position */
	getPos(pLibList[0],pTempA,pValue,PropertyToBeCreated);

	/* create Property*/
	sosx_informationModelManagement_createSimpleProperty(&PropertyToBeCreated,&pProperty);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the Property:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* create all children of the property */
	Ov_ForEachChildEx(ov_containment,pInternalElement,pTempCaex,caex_InternalElement){
		result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pProperty),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
		if(Ov_Fail(result)){
			break;
		}
	}

	undoCreateInCaseOfError(result,pProperty);

	Finally();
	return result;
}

/**
 *  createPort -  This function will create a Port and its Properties based on a CAEX file
 * @param pobj - pointer to the api instance that creates the Port
 * @param pTargetElement - pointer to the element in which the Port will be created. (Can either be a Process or a System)
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies the Port and its Properties.
 * @return - the result of the Port creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createPort(
		OV_INSTPTR_sosx_DetailedElement		pTargetElement, //Process or System
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_sosx_Port					pPort			= NULL;
	OV_INSTPTR_caex_Attribute				pTempA			= NULL;
	OV_INSTPTR_caex_Value					pValue			= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList		= NULL;
	OV_UINT									LenLibList		= 0;
	OV_RESULT								result			= OV_ERR_OK;
	SOSX_PortDescription					PortToBeCreated	= {NULL};
	OV_INSTPTR_caex_InternalElement			pTempCaex			= NULL;

#undef	Finally
#define Finally() 								\
		freePortDescription(&PortToBeCreated);	\
		ov_free(pLibList);						\

	/* check if TargetElement or InternalElement is NULL */
	if (!(pInternalElement) || !(pTargetElement)){
		log_error("InternalElement and/or TargetElement not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get the LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}
	/* set source */
	PortToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	PortToBeCreated.pTarget = pTargetElement;

	/* collect Attributes*/
	/* name */
	ov_string_setvalue(&(PortToBeCreated.Name),pInternalElement->v_Name);

	/* caexLibrary */
	ov_string_setvalue(&(PortToBeCreated.CaexLib),pInternalElement->v_RefBaseSystemUnitPath);

	/*get validFrom and validUntil*/
	getLifeCycle(pLibList[0],pTempA,pValue,PortToBeCreated);

	/*get x and y position */
	getPos(pLibList[0],pTempA,pValue,PortToBeCreated);

	/* StreamType */
	/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first StreamType specified then break */
	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"StreamType",caex_Attribute);
		if(pTempA){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				ov_string_setvalue(&(PortToBeCreated.StreamType), pValue->v_Value);
				break;
			}
		}
	}

	/* try to find the InternalLinks */
	result = findInternalLinks(pLibList[0],&(PortToBeCreated.isLinkedTo));
	if (Ov_Fail(result)){
		logfile_warning("Could not find all InternalLinks of Port:", pInternalElement->v_Name);
	}

	/* create Port*/
	result = sosx_informationModelManagement_createSimplePort(&PortToBeCreated,&pPort);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the Port:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* create all children of the port */
	Ov_ForEachChildEx(ov_containment,pInternalElement,pTempCaex,caex_InternalElement){
		result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pPort),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
		if(Ov_Fail(result)){
			break;
		}
	}

	undoCreateInCaseOfError(result,pPort);

	Finally();
	return result;
}

/**
 *createSourceSink -  This function will create a SourceSink and its Properties based on a CAEX file
 * @param pobj - pointer to the api instance that creates the SourceSink
 * @param pTargetContainer - pointer to the SoSContainer in which the SourceSink will be created.
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies the SourceSink and its Properties.
 * @return - the result of the SourceSink creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createSourceSink(
		OV_INSTPTR_sosx_SoSContainer		pTargetContainer,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_sosx_SourceSink				pSourceSink				= NULL;
	OV_INSTPTR_caex_Attribute				pTempA					= NULL;
	OV_INSTPTR_caex_Value					pValue					= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList				= NULL;
	OV_UINT									LenLibList				= 0;
	OV_RESULT								result					= OV_ERR_OK;
	SOSX_SourceSinkDescription				SourceSinkToBeCreated	= {NULL};
	OV_INSTPTR_caex_InternalElement			pTempCaex			= NULL;

#undef	Finally
#define Finally() 											\
		freeSourceSinkDescription(&SourceSinkToBeCreated);	\
		ov_free(pLibList);									\

	/* check if TargetElement or InternalElement is NULL */
	if (!(pInternalElement) ||
			!(pTargetContainer)){
		log_error("InternalElement and/or TargetContainer not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}
	/* set source */
	SourceSinkToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	SourceSinkToBeCreated.pTarget = Ov_DynamicPtrCast(ov_domain,pTargetContainer);

	/* collect all Attributes */
	/* name */

	result = ov_string_setvalue(&(SourceSinkToBeCreated.Name), pInternalElement->v_Name);

	/* caexLibrary */
	result = ov_string_setvalue(&(SourceSinkToBeCreated.CaexLib), pInternalElement->v_RefBaseSystemUnitPath);

	/* StreamType */
	/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first StreamType specified then break */
	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"StreamType",caex_Attribute);
		if(pTempA){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				ov_string_setvalue(&(SourceSinkToBeCreated.StreamType), pValue->v_Value);
				break;
			}
		}
	}

	/*get validFrom and validUntil*/
	getLifeCycle(pLibList[0],pTempA,pValue,SourceSinkToBeCreated);

	/*get x and y position */
	getPos(pLibList[0],pTempA,pValue,SourceSinkToBeCreated);

	/* try to find all InternalLinks */
	result = findInternalLinks(pLibList[0],&SourceSinkToBeCreated.isLinkedTo);
	if (Ov_Fail(result)){
		logfile_warning("Cannot find all InternalLinks of SourceSink:", pInternalElement->v_Name);
	}

	/* create SourceSink*/
	result = sosx_informationModelManagement_createSimpleSourceSink(&SourceSinkToBeCreated,&pSourceSink);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the SourceSink:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* create all children of the source sink */
	Ov_ForEachChildEx(ov_containment,pInternalElement,pTempCaex,caex_InternalElement){
		result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pSourceSink),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
		if(Ov_Fail(result)){
			break;
		}
	}

	undoCreateInCaseOfError(result,pSourceSink);

	Finally();
	return result;
}

/**
 * createDistributionNode -  This function will create a DistributionNode and its Properties based on a CAEX file
 * @param pobj - pointer to the api instance that creates the DistributionNode
 * @param pTargetElement - pointer to the System in which the DistributionNode will be created.
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies DistributionNode and its Properties.
 * @return - the result of the DistributionNode creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createDistributionNode(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_sosx_DistributionNode		pDistributionNode			= NULL;
	OV_INSTPTR_caex_Attribute				pTempA						= NULL;
	OV_INSTPTR_caex_Value					pValue						= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList					= NULL;
	OV_UINT									LenLibList					= 0;
	OV_RESULT								result						= OV_ERR_OK;
	SOSX_DistributionNodeDescription		DistributionNodeToBeCreated	= {NULL};
	OV_INSTPTR_caex_InternalElement			pTempCaex			= NULL;

#undef	Finally
#define Finally()														\
		freeDistributionNodeDescription(&DistributionNodeToBeCreated);	\
		ov_free(pLibList);												\

	/* check if TargetElement or InternalElement is NULL */
	if (!(pInternalElement) || !(pTargetSystem)){
		log_error("InternalElement and/or TargetElement not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get the LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}
	/* set source */
	DistributionNodeToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	DistributionNodeToBeCreated.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pTargetSystem);

	/* collect Attributes*/
	/* name */
	result = ov_string_setvalue(&(DistributionNodeToBeCreated.Name),pInternalElement->v_Name);

	/* caexLibrary */
	result = ov_string_setvalue(&(DistributionNodeToBeCreated.CaexLib),pInternalElement->v_RefBaseSystemUnitPath);

	/*get validFrom and validUntil*/
	getLifeCycle(pLibList[0],pTempA,pValue,DistributionNodeToBeCreated);

	/*get x and y position */
	getPos(pLibList[0],pTempA,pValue,DistributionNodeToBeCreated);

	/* StreamType */
	/* go through LibList (InternalElement -> Library -> ... -> BaseLibrary) and set first StreamType specified then break */
	for (OV_UINT y = 0 ; y < LenLibList ; y++){
		pTempA = Ov_SearchChildEx(ov_containment,pLibList[y],"StreamType",caex_Attribute);
		if(pTempA){
			Ov_ForEachChildEx(ov_containment,pTempA,pValue,caex_Value){
				ov_string_setvalue(&(DistributionNodeToBeCreated.StreamType), pValue->v_Value);
				break;
			}
		}
	}

	/* try to find all InternalLinks */
	result = findInternalLinks(pLibList[0],&(DistributionNodeToBeCreated.isLinkedTo));
	if (Ov_Fail(result)){
		logfile_warning("Cannot find all InternalLinks of DistributionNode:", pInternalElement->v_Name);
	}

	/* create DistributionNode*/
	result = sosx_informationModelManagement_createSimpleDistributionNode(&DistributionNodeToBeCreated,&pDistributionNode);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the DistributionNode:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	/* create all children of the DistributionNode */
	Ov_ForEachChildEx(ov_containment,pInternalElement,pTempCaex,caex_InternalElement){
		result = sosx_workflowManagement_createElement(Ov_DynamicPtrCast(ov_domain,pDistributionNode),Ov_DynamicPtrCast(caex_CAEXBasicObject,pTempCaex));
		if(Ov_Fail(result)){
			break;
		}
	}

	undoCreateInCaseOfError(result,pDistributionNode);

	Finally();
	return result;
}

/**
 * createStream -  This function will create a Stream based on a CAEX file
 * @param pobj - pointer to the api instance that creates the Stream
 * @param pTargetElement - pointer to the element in which the Stream will be created. (Can either be a System or a SoSContainer)
 * @param pInternalElement - pointer to the InternalElement of a CAEX file that specifies the Stream.
 * @return - the result of the Stream creation (OV_RESULT)
 */
OV_RESULT sosx_workflowManagement_createStream(
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
	OV_INSTPTR_sosx_Stream					pStream				= NULL;
	OV_INSTPTR_caex_CAEXObject				*pLibList			= NULL;
	OV_INSTPTR_caex_RoleRequirements		pRoleReq			= NULL;
	OV_INSTPTR_caex_Value					pValue				= NULL;
	OV_INSTPTR_caex_Attribute				pTempA				= NULL;
	OV_UINT									LenLibList			= 0;
	OV_RESULT								result				= OV_ERR_OK;
	SOSX_StreamDescription					StreamToBeCreated	= {NULL};


#undef	Finally
#define Finally() 									\
		freeStreamDescription(&StreamToBeCreated);	\
		ov_free(pLibList);							\

	/* check if TargetElement or InternalElement is NULL */
	if (!(pInternalElement) ||
			!(pTargetElement)){
		log_error("InternalElement and/or TargetContainer not found!");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* get LibraryList */
	result = sosx_workflowManagement_getLibraryList(Ov_DynamicPtrCast(caex_CAEXBasicObject,pInternalElement),&pLibList,&LenLibList);
	if (Ov_Fail(result)){
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}
	/* set source */
	StreamToBeCreated.pSource = Ov_DynamicPtrCast(caex_CAEXObject,pInternalElement);

	/* set target */
	StreamToBeCreated.pTarget = Ov_DynamicPtrCast(ov_domain,pTargetElement);

	/* collect all Attributes */
	/* Identifier */
	result = ov_string_setvalue(&(StreamToBeCreated.Identifier),pInternalElement->v_identifier);

	/* caexLibrary */
	pRoleReq = Ov_SearchChildEx(ov_containment,pInternalElement,"RoleRequirements",caex_RoleRequirements);
	if(pRoleReq){
		result = ov_string_setvalue(&(StreamToBeCreated.CaexLib),pRoleReq->v_RefBaseRoleClassPath);
	} else {
		logfile_error("Cannot resolve the library path of ", pInternalElement->v_Name);
		Finally();
		return result;
	}



	/*get validFrom and validUntil*/ //DO TO
	getLifeCycle(pLibList[0],pTempA,pValue,StreamToBeCreated);

	/* try to find all InternalLinks */
	result = findInternalLinks(pLibList[0],&(StreamToBeCreated.isLinkedTo));
	if (Ov_Fail(result)){
		logfile_warning("Cannot find all InternalLinks of DistributionNode:", pInternalElement->v_Name);
	}

	/* create Stream*/
	result = sosx_informationModelManagement_createSimpleStream(&StreamToBeCreated,&pStream);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the Stream:", pInternalElement->v_Name);
		Finally();
		return result;
	}

	undoCreateInCaseOfError(result,pStream);

	Finally();
	return result;
}

/**
 * create Alternative
 * @param pTargetSystem
 * @param pInternalElement
 * @return
 */

OV_RESULT sosx_workflowManagement_createAlternative(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_INSTPTR_caex_InternalElement		pInternalElement
){
#undef Finally
#define Finally()


	Finally();
	return OV_ERR_NOTIMPLEMENTED;
}

#endif
