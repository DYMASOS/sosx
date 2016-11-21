/******************************************************************************
 *
 *   FILE
 *   ----
 *   read.c
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


OV_STRING datatypeToString(
		OV_VAR_TYPE 	datatype
){

	/* Mapping between OV_VT and CAEX data types
	 * OV_VT_TIME	->	xs:dateTime
	 * OV_VT_STRING	->	xs:string
	 * OV_VT_BOOL	->	xs:boolean
	 * OV_VT_INT	->	xs:integereger
	 * OV_VT_UINT	->	xs:unsignedInt
	 * OV_VT_SINGLE	->	xs:float
	 * OV_VT_DOUBLE	->	xs:double
	 */
	switch (datatype & OV_VT_KSMASK){
	case OV_VT_STRING 	: return "xs:string";
	case OV_VT_TIME 	: return "xs:dateTime";
	case OV_VT_BOOL 	: return "xs:boolean";
	case OV_VT_INT 		: return "xs:integer";
	case OV_VT_UINT 	: return "xs:unsignedInt";
	case OV_VT_SINGLE 	: return "xs:float";
	case OV_VT_DOUBLE 	: return "xs:double";
	default : logfile_error("Wrong data type",datatype);
	return NULL;
	}
}


OV_STRING uinttostring(
		OV_UINT 		val,
		OV_STRING*		Buffer
){
	ov_string_print(Buffer,"%u",val);
	return *Buffer;
}

OV_STRING inttostring(
		OV_INT 		val,
		OV_STRING* 	Buffer
){
	ov_string_print(Buffer,"%i",val);
	return *Buffer;
}


/****************************************************
 * SoSContainer - This function reads a SoSContainer a without the internal structure of the SoSContainer
 * @param pSoSContainerDes - pointer to the structure containing all information about the SoSContainer
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_simpleSoSContainerRead(
		SOSX_SoSContainerDescription	*pSoSContainerDes
){
	OV_RESULT						result		= OV_ERR_OK;
#undef Finally
#define Finally()

	/* read name */
	ov_string_setvalue(&pSoSContainerDes->Name,Ov_DynamicPtrCast(sosx_SoSContainer,pSoSContainerDes->pTarget)->v_name);

	/* read externalReference*/
	Ov_SetDynamicVectorValue(&pSoSContainerDes->externalReference, Ov_DynamicPtrCast(sosx_SoSContainer,pSoSContainerDes->pTarget)->v_externalReference.value,
			Ov_DynamicPtrCast(sosx_SoSContainer,pSoSContainerDes->pTarget)->v_externalReference.veclen,STRING);

	return result;
}

/*********************************************************
 * SoSContainer - This function creates an CAEX-structure based on a SoSContainerDescription with all children of the SoSContainer
 * @param pSoSContainerToBeRead - pointer to the SoSContainer that will be read
 * @param pTargetContainer - Pointer to the Container in which the CAEX-structure will be placed
 * @return OV_RESULT error level
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readSoSContainer(
		OV_INSTPTR_sosx_SoSContainer		pSoSContainerToBeRead,
		OV_INSTPTR_ov_domain				pTargetContainer,
		OV_BOOL								readStateOnly
){
	OV_RESULT								result					= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTempSosx				= NULL;
	OV_INSTPTR_caex_InternalElement			pInternalElement		= NULL;
	OV_STRING								tmpFileName				= NULL;
	SOSX_SoSContainerDescription			SoSContainer			= {NULL};

#undef Finally
#define Finally() 									\
		ov_string_setvalue(&tmpFileName,NULL);		\
		freeSoSContainerDescription(&SoSContainer);	\


	if (pSoSContainerToBeRead == NULL || pTargetContainer == NULL){
		log_error("SoSContainerToBeRead and/or target not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}
	SoSContainer.pTarget = Ov_DynamicPtrCast(ov_domain,pSoSContainerToBeRead);
	sosx_informationModelManagement_simpleSoSContainerRead(&SoSContainer);

	if(Ov_CanCastTo(caex_InternalElement,pTargetContainer) &&
			ov_string_compare(Ov_DynamicPtrCast(caex_InternalElement,pTargetContainer)->v_RefBaseSystemUnitPath,"Libs@SoS_BaseLibrary/SoSContainer") == OV_STRCMP_EQUAL){
		pInternalElement = Ov_DynamicPtrCast(caex_InternalElement,pTargetContainer);
	}else{
		/* create InternalElement representing the System in CAEX */
		Sosx_CreateSystemUnit(pTargetContainer,pInternalElement,SoSContainer.Name,"Libs@SoS_BaseLibrary/SoSContainer");
	}
	/* read all children of the SoSContainer */
	Ov_ForEachChildEx(ov_containment,pSoSContainerToBeRead,pTempSosx,ov_domain){
		result = sosx_workflowManagement_readElement(pTempSosx,Ov_DynamicPtrCast(ov_domain,pInternalElement),FALSE,NULL,readStateOnly);
		if (Ov_Fail(result)){
			logfile_error("Could not read the children of ",pSoSContainerToBeRead->v_name);
			Finally();
			return result;
		}
	}
	Finally();
	return result;
}

/****************************************************
 * System -  This function reads a System a without the internal structure of the System
 * @param SystemDes - pointer to the SystemDescription structure in which all informations will be placed
 * @return - OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_simpleSystemRead(
		SOSX_SystemDescription				*pSystemDes
){
	OV_RESULT								result		= OV_ERR_OK;
#undef Finally
#define Finally()

	/* read Name */
	ov_string_setvalue(&pSystemDes->Name,Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_name);

	/* caexLibrary */
	ov_string_setvalue(&pSystemDes->CaexLib,Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_caexLibrary);

	/* read validFrom */
	pSystemDes->validFrom = Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_validFrom;

	/* read validUntil */
	pSystemDes->validUntil = Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_validUntil;

	/* read externalInfo */
	Ov_SetDynamicVectorValue(&pSystemDes->externalInfo, Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_externalInfo.value,
			Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_externalInfo.veclen,STRING);

	/* read xPos */
	pSystemDes->xPos = Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_xPos;

	/* read yPos */
	pSystemDes->yPos = Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_yPos;

	/* read width */
	pSystemDes->Width = Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_width;

	/* read height */
	pSystemDes->Height = Ov_DynamicPtrCast(sosx_System,pSystemDes->pTarget)->v_height;

	return result;
}

/** @param pSystemToBeRead
 * @param pTargetContainer
 * @return
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readSystem(
		OV_INSTPTR_sosx_System				pSystemToBeRead,
		OV_INSTPTR_ov_domain				pTargetContainer,
		OV_BOOL								readStateOnly
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 				= NULL;
	OV_INSTPTR_caex_InternalElement			pInternalElement	= NULL;
	OV_INSTPTR_caex_Attribute				pTempAttribute		= NULL;
	OV_INSTPTR_caex_Value					pTempValue			= NULL;
	OV_STRING								tmpstr				= NULL;
	OV_STRING								Buffer				= NULL;
	SOSX_SystemDescription					System				= {NULL};

#undef Finally
#define Finally() 									\
		freeSystemDescription(&System);				\
		ov_string_setvalue(&tmpstr,NULL);			\
		ov_string_setvalue(&Buffer,NULL);			\

	if (pSystemToBeRead == NULL || pTargetContainer == NULL){
		log_error("System and/or target not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* read all attributes of the System */
	System.pTarget = Ov_DynamicPtrCast(ov_domain,pSystemToBeRead);
	sosx_informationModelManagement_simpleSystemRead(&System);

	/* create InternalElement representing the System in CAEX */
	Sosx_CreateSystemUnit(pTargetContainer,pInternalElement,System.Name,System.CaexLib);

	if(!readStateOnly){
		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validFrom",ov_time_timetoascii_local(&System.validFrom),"xs:dateTime");

		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validUntil",ov_time_timetoascii_local(&System.validUntil),"xs:dateTime");

		/* create xPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"xPos",uinttostring(System.xPos,&Buffer),"xs:unsignedInt");

		/* create yPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"yPos",uinttostring(System.yPos,&Buffer),"xs:unsignedInt");

		/* create Height Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"Height",inttostring(System.Height,&Buffer),"xs:integer");

		/* create Width Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"Width",inttostring(System.Width,&Buffer),"xs:integer");

		/* create externalInfo Attribute and Value */
		for(OV_UINT i = 0 ; i < System.externalInfo.veclen; i++){
			if(i == 0){
				ov_string_setvalue(&tmpstr,System.externalInfo.value[i]);
			} else {
				ov_string_append(&tmpstr,",");
				ov_string_append(&tmpstr,System.externalInfo.value[i]);
			}
		}
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"externalInfo",tmpstr,"xs:string");
		ov_string_setvalue(&tmpstr,NULL);
	}
	/* read all children of the system */
	Ov_ForEachChildEx(ov_containment,pSystemToBeRead,pTemp,ov_domain){
		result = sosx_workflowManagement_readElement(Ov_DynamicPtrCast(ov_domain,pTemp),Ov_DynamicPtrCast(ov_domain,pInternalElement),FALSE,NULL,readStateOnly);
		if (Ov_Fail(result)){
			logfile_error("Could not read the children of the system",pSystemToBeRead->v_name);
			Finally();
			return result;
		}
	}
	Finally();
	return result;
}

/**********************************************************
 * Process - This function reads a Process a without the internal structure of the Process
 * @param pProcessDes - pointer to the structure in which all the information about the proess will be stored
 * @return - OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_simpleProcessRead(
		SOSX_ProcessDescription				*pProcessDes
){
	OV_RESULT						result		= OV_ERR_OK;
#undef Finally
#define Finally()

	/* read Name */
	ov_string_setvalue(&pProcessDes->Name,Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_name);

	/* caexLibrary */
	ov_string_setvalue(&pProcessDes->CaexLib,Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_caexLibrary);

	/* read validFrom */
	pProcessDes->validFrom = Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_validFrom;

	/* read validUntil */
	pProcessDes->validUntil = Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_validUntil;

	/* read externalInfo */
	Ov_SetDynamicVectorValue(&pProcessDes->externalInfo, Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_externalInfo.value,
			Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_externalInfo.veclen,STRING);

	/* read xPos */
	pProcessDes->xPos = Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_xPos;

	/* read yPos */
	pProcessDes->yPos = Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_yPos;

	/* read width */
	pProcessDes->Width = Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_width;

	/* read height */
	pProcessDes->Height = Ov_DynamicPtrCast(sosx_Process,pProcessDes->pTarget)->v_height;

	return result;
}

/****************************************************************
 * Process
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readProcess(
		OV_INSTPTR_sosx_Process				pProcessToBeRead,
		OV_INSTPTR_ov_domain				pTargetContainer,
		OV_BOOL								readStateOnly
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 				= NULL;
	OV_INSTPTR_caex_InternalElement			pInternalElement	= NULL;
	OV_INSTPTR_caex_Attribute				pTempAttribute		= NULL;
	OV_INSTPTR_caex_Value					pTempValue			= NULL;
	OV_STRING								tmpstr				= NULL;
	OV_STRING								Buffer				= NULL;
	SOSX_ProcessDescription					Process				= {NULL};



#undef Finally
#define Finally()									\
		freeProcessDescription(&Process);			\
		ov_string_setvalue(&tmpstr,NULL);			\
		ov_string_setvalue(&Buffer,NULL);			\

	if (pProcessToBeRead == NULL || pTargetContainer == NULL){
		log_error("Process and/or target not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* read all attributes of the Process */
	Process.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pProcessToBeRead);
	sosx_informationModelManagement_simpleProcessRead(&Process);

	/* create InternalElement representing the Process in CAEX */
	Sosx_CreateSystemUnit(pTargetContainer,pInternalElement,Process.Name,Process.CaexLib);

	if(!readStateOnly){
		/* create xPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"xPos",uinttostring(Process.xPos,&Buffer),"xs:unsignedInt");

		/* create yPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"yPos",uinttostring(Process.yPos,&Buffer),"xs:unsignedInt");

		/* create Height Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"Height",inttostring(Process.Height,&Buffer),"xs:integer");

		/* create Width Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"Width",inttostring(Process.Width,&Buffer),"xs:integer");

		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validFrom",ov_time_timetoascii_local(&Process.validFrom),"xs:dateTime");

		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validUntil",ov_time_timetoascii_local(&Process.validUntil),"xs:dateTime");

		/* create externalInfo Attribute and Value */
		for(OV_UINT i = 0 ; i < Process.externalInfo.veclen; i++){
			if(i == 0){
				ov_string_setvalue(&tmpstr,Process.externalInfo.value[i]);
			} else {
				ov_string_append(&tmpstr,",");
				ov_string_append(&tmpstr,Process.externalInfo.value[i]);
			}
		}
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"externalInfo",tmpstr,"xs:string");
		ov_string_setvalue(&tmpstr,NULL);
	}
	/* read all children of the Process */
	Ov_ForEachChildEx(ov_containment,pProcessToBeRead,pTemp,ov_domain){
		result = sosx_workflowManagement_readElement(Ov_DynamicPtrCast(ov_domain,pTemp),Ov_DynamicPtrCast(ov_domain,pInternalElement),FALSE,NULL,readStateOnly);
		if(Ov_Fail(result)){
			logfile_error("Could not read the children of the process",pProcessToBeRead->v_name);
			Finally();
			return result;
		}
	}
	Finally();
	return result;
}

/**
 * Port - This function reads a Port without the internal structure of the Port
 * @param pPortDes - pointer to the structure in which the information will be stored
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_simplePortRead(
		SOSX_PortDescription				*pPortDes
){
	OV_RESULT						result		= OV_ERR_OK;
#undef Finally
#define Finally()

	/* read Name */
	ov_string_setvalue(&pPortDes->Name,Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_name);

	/* caexLibrary */
	ov_string_setvalue(&pPortDes->CaexLib,Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_caexLibrary);

	/* StreamType */
	ov_string_setvalue(&pPortDes->StreamType,Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_StreamType);

	/* wasConnectedTo */
	ov_string_setvalue(&pPortDes->wasConnectedTo,Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_wasConnectedTo);

	/* read validFrom */
	pPortDes->validFrom = Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_validFrom;

	/* read validUntil */
	pPortDes->validUntil = Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_validUntil;

	/* read xPos */
	pPortDes->xPos = Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_xPos;

	/* read yPos */
	pPortDes->yPos = Ov_DynamicPtrCast(sosx_Port,pPortDes->pTarget)->v_yPos;

	/* read all Links */
	readLinks(&pPortDes->isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pPortDes->pTarget));

	return result;
}

OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readPort(
		OV_INSTPTR_sosx_Port				pPortToBeRead,
		OV_INSTPTR_ov_domain				pTargetContainer,
		OV_BOOL								readStateOnly
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_sosx_Property				pTemp 				= NULL;
	OV_INSTPTR_caex_InternalElement			pInternalElement	= NULL;
	OV_INSTPTR_caex_Attribute				pTempAttribute		= NULL;
	OV_INSTPTR_caex_Value					pTempValue			= NULL;
	OV_STRING								Buffer				= NULL;
	SOSX_PortDescription					Port				= {NULL};

#undef	Finally
#define Finally()									\
		freePortDescription(&Port);					\
		ov_string_setvalue(&Buffer,NULL);			\

	if (pPortToBeRead == NULL || pTargetContainer == NULL){
		log_error("PortToBeRead and/or target not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* read all attributes of the Port */
	Port.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pPortToBeRead);
	sosx_informationModelManagement_simplePortRead(&Port);

	/* create InternalElement representing the Port in CAEX */
	Sosx_CreateSystemUnit(pTargetContainer,pInternalElement,Port.Name,Port.CaexLib);
	if(!readStateOnly){
		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validFrom",ov_time_timetoascii_local(&Port.validFrom),"xs:dateTime");

		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validUntil",ov_time_timetoascii_local(&Port.validUntil),"xs:dateTime");

		/* create xPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"xPos",inttostring(Port.xPos,&Buffer),"xs:unsignedInt");

		/* create yPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"yPos",inttostring(Port.yPos,&Buffer),"xs:unsignedInt");

		/* create wasConnectedTo Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"wasConnectedTo",Port.wasConnectedTo,"xs:string");

		/* create StreamType Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"StreamType",Port.StreamType,"xs:string");

		/* export links */
		result = exportLinks(&Port.isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pPortToBeRead),pInternalElement);
		if(Ov_Fail(result)){
			logfile_error("Could not export the links of ",pPortToBeRead->v_name);
			Finally();
			return result;
		}
	}
	/* read all children of the port */
	Ov_ForEachChildEx(ov_containment,pPortToBeRead,pTemp,sosx_Property){
		result = sosx_workflowManagement_readElement(Ov_DynamicPtrCast(ov_domain,pTemp),Ov_DynamicPtrCast(ov_domain,pInternalElement),FALSE,NULL,readStateOnly);
		if(Ov_Fail(result)){
			logfile_error("Could not read the children of the Port",pPortToBeRead->v_name);
			Finally();
			return result;
		}
	}

	Finally();
	return result;
}

/***
 * SourceSink
 * @param pSourceSinkDes
 * @return
 */
OV_RESULT sosx_informationModelManagement_simpleSourceSinkRead(
		SOSX_SourceSinkDescription			*pSourceSinkDes
){
	OV_RESULT						result		= OV_ERR_OK;
#undef Finally
#define Finally()

	/* read Name */
	ov_string_setvalue(&pSourceSinkDes->Name,Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_name);

	/* caexLibrary */
	ov_string_setvalue(&pSourceSinkDes->CaexLib,Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_caexLibrary);

	/* StreamType */
	ov_string_setvalue(&pSourceSinkDes->StreamType,Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_StreamType);

	/* wasConnectedTo */
	ov_string_setvalue(&pSourceSinkDes->wasConnectedTo,Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_wasConnectedTo);

	/* read validFrom */
	pSourceSinkDes->validFrom = Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_validFrom;

	/* read validUntil */
	pSourceSinkDes->validUntil = Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_validUntil;

	/* read xPos */
	pSourceSinkDes->xPos = Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_xPos;

	/* read yPos */
	pSourceSinkDes->yPos = Ov_DynamicPtrCast(sosx_SourceSink,pSourceSinkDes->pTarget)->v_yPos;

	/* read all Links */
	readLinks(&pSourceSinkDes->isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pSourceSinkDes->pTarget));

	return result;
}

OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readSourceSink(
		OV_INSTPTR_sosx_SourceSink			pSourceSinkToBeRead,
		OV_INSTPTR_ov_domain				pTargetContainer,
		OV_BOOL								readStateOnly
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_sosx_Property				pTemp 				= NULL;
	OV_INSTPTR_caex_InternalElement			pInternalElement	= NULL;
	OV_INSTPTR_caex_Attribute				pTempAttribute		= NULL;
	OV_INSTPTR_caex_Value					pTempValue			= NULL;
	OV_STRING								Buffer				= NULL;
	SOSX_SourceSinkDescription				SourceSink			= {NULL};

#undef	Finally
#define Finally()									\
		freeSourceSinkDescription(&SourceSink);		\
		ov_string_setvalue(&Buffer,NULL);			\

	if (pSourceSinkToBeRead == NULL || pTargetContainer == NULL){
		log_error("SourceSinkToBeRead and/or target not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* read all attributes of the SourceSink */
	SourceSink.pTarget = Ov_DynamicPtrCast(ov_domain,pSourceSinkToBeRead);
	sosx_informationModelManagement_simpleSourceSinkRead(&SourceSink);

	/* create InternalElement representing the SourceSink in CAEX */
	Sosx_CreateSystemUnit(pTargetContainer,pInternalElement,SourceSink.Name,SourceSink.CaexLib);
	if(!readStateOnly){
		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validFrom",ov_time_timetoascii_local(&SourceSink.validFrom),"xs:dateTime");

		/* create validFrom Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validUntil",ov_time_timetoascii_local(&SourceSink.validUntil),"xs:dateTime");

		/* create xPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"xPos",inttostring(SourceSink.xPos,&Buffer),"xs:unsignedInt");

		/* create yPos Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"yPos",inttostring(SourceSink.yPos,&Buffer),"xs:unsignedInt");


		/* create wasConnectedTo Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"wasConnectedTo",SourceSink.wasConnectedTo,"xs:string");

		/* create StreamType Attribute and Value */
		Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"StreamType",SourceSink.StreamType,"xs:string");

		/* export links */
		result = exportLinks(&SourceSink.isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pSourceSinkToBeRead),pInternalElement);
		if(Ov_Fail(result)){
			logfile_error("Could not export the links of ",pSourceSinkToBeRead->v_name);
			Finally();
			return result;
		}
	}
	/* read all children of the SourceSink (Properties)*/
	Ov_ForEachChildEx(ov_containment,pSourceSinkToBeRead,pTemp,sosx_Property){
		result = sosx_workflowManagement_readElement(Ov_DynamicPtrCast(ov_domain,pTemp),Ov_DynamicPtrCast(ov_domain,pInternalElement),FALSE,NULL,readStateOnly);
		if(Ov_Fail(result)){
			logfile_error("Could not read the children of the SourceSink",pSourceSinkToBeRead->v_name);
			Finally();
			return result;
		}
	}

	Finally();
	return result;
}

/**
 *  DistributionNode
 * @param pDistributionNodeDes
 * @return
 */OV_RESULT sosx_informationModelManagement_simpleDistributionNodeRead(
		 SOSX_DistributionNodeDescription		*pDistributionNodeDes
 ){
	 OV_RESULT						result		= OV_ERR_OK;
#undef Finally
#define Finally()

	 /* read Name */
	 ov_string_setvalue(&pDistributionNodeDes->Name,Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_name);

	 /* caexLibrary */
	 ov_string_setvalue(&pDistributionNodeDes->CaexLib,Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_caexLibrary);

	 /* StreamType */
	 ov_string_setvalue(&pDistributionNodeDes->StreamType,Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_StreamType);

	 /* wasConnectedTo */
	 ov_string_setvalue(&pDistributionNodeDes->wasConnectedTo,Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_wasConnectedTo);

	 /* read validFrom */
	 pDistributionNodeDes->validFrom = Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_validFrom;

	 /* read validUntil */
	 pDistributionNodeDes->validUntil = Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_validUntil;

	 /* read xPos */
	 pDistributionNodeDes->xPos = Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_xPos;

	 /* read yPos */
	 pDistributionNodeDes->yPos = Ov_DynamicPtrCast(sosx_DistributionNode,pDistributionNodeDes->pTarget)->v_yPos;

	 /* read all Links */
	 readLinks(&pDistributionNodeDes->isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pDistributionNodeDes->pTarget));

	 return result;
 }

 OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readDistributionNode(
		 OV_INSTPTR_sosx_DistributionNode		pDistributionNodeToBeRead,
		 OV_INSTPTR_ov_domain					pTargetContainer,
		 OV_BOOL								readStateOnly
 ){
	 OV_RESULT									result				= OV_ERR_OK;
	 OV_INSTPTR_sosx_Property					pTemp 				= NULL;
	 OV_INSTPTR_caex_InternalElement			pInternalElement	= NULL;
	 OV_INSTPTR_caex_Attribute					pTempAttribute		= NULL;
	 OV_INSTPTR_caex_Value						pTempValue			= NULL;
	 OV_STRING									Buffer				= NULL;
	 SOSX_DistributionNodeDescription			DistributionNode	= {NULL};

#undef	Finally
#define Finally()											\
		freeDistributionNodeDescription(&DistributionNode);	\
		ov_string_setvalue(&Buffer,NULL);					\

	 if (pDistributionNodeToBeRead == NULL || pTargetContainer == NULL){
		 log_error("DistributionNodeToBeRead and/or target not found!");
		 result = OV_ERR_GENERIC;
		 Finally();
		 return result;
	 }

	 /* read all attributes of the DistributionNode */
	 DistributionNode.pTarget = Ov_DynamicPtrCast(sosx_DetailedElement,pDistributionNodeToBeRead);
	 sosx_informationModelManagement_simpleDistributionNodeRead(&DistributionNode);

	 /* create InternalElement representing the DistributionNode in CAEX */
	 Sosx_CreateSystemUnit(pTargetContainer,pInternalElement,DistributionNode.Name,DistributionNode.CaexLib);
	 if(!readStateOnly){
		 /* create validFrom Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validFrom",ov_time_timetoascii_local(&DistributionNode.validFrom),"xs:dateTime");

		 /* create validFrom Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validUntil",ov_time_timetoascii_local(&DistributionNode.validUntil),"xs:dateTime");

		 /* create xPos Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"xPos",inttostring(DistributionNode.xPos,&Buffer),"xs:unsignedInt");

		 /* create yPos Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"yPos",inttostring(DistributionNode.yPos,&Buffer),"xs:unsignedInt");


		 /* create wasConnectedTo Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"wasConnectedTo",DistributionNode.wasConnectedTo,"xs:string");

		 /* create StreamType Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"StreamType",DistributionNode.StreamType,"xs:string");

		 /* export links */
		 result = exportLinks(&DistributionNode.isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pDistributionNodeToBeRead),pInternalElement);
		 if(Ov_Fail(result)){
			 logfile_error("Could not export the links of ",pDistributionNodeToBeRead->v_name);
			 Finally();
			 return result;
		 }
	 }
	 /* read all children of the SourceSink (Properties) */
	 Ov_ForEachChildEx(ov_containment,pDistributionNodeToBeRead,pTemp,sosx_Property){
		 result = sosx_workflowManagement_readElement(Ov_DynamicPtrCast(ov_domain,pTemp),Ov_DynamicPtrCast(ov_domain,pInternalElement),FALSE,NULL,readStateOnly);
		 if(Ov_Fail(result)){
			 logfile_error("Could not read the children of the distribution node",pDistributionNodeToBeRead->v_name);
			 Finally();
			 return result;
		 }
	 }
	 Finally();
	 return result;
 }

 /**
  * Property
  */
 OV_RESULT sosx_informationModelManagement_simplePropertyRead(
		 SOSX_PropertyDescription				*pPropertyDes
 ){
	 OV_RESULT						result		= OV_ERR_OK;
#undef Finally
#define Finally()

	 /* read Name */
	 ov_string_setvalue(&pPropertyDes->Name,Ov_DynamicPtrCast(sosx_Property,pPropertyDes->pTarget)->v_name);

	 /* caexLibrary */
	 ov_string_setvalue(&pPropertyDes->CaexLib,Ov_DynamicPtrCast(sosx_Property,pPropertyDes->pTarget)->v_caexLibrary);

	 /* read xPos */
	 pPropertyDes->xPos = Ov_DynamicPtrCast(sosx_Property,pPropertyDes->pTarget)->v_xPos;

	 /* read yPos */
	 pPropertyDes->yPos = Ov_DynamicPtrCast(sosx_Property,pPropertyDes->pTarget)->v_yPos;

	 return result;
 }


 OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readProperty(
		 OV_INSTPTR_sosx_Property				pPropertyToBeRead,
		 OV_INSTPTR_ov_domain					pTargetContainer,
		 OV_BOOL								readStateOnly
 ){
	 OV_RESULT									result				= OV_ERR_OK;
	 OV_INSTPTR_sosx_PropertyInformation		pTemp 				= NULL;
	 OV_INSTPTR_caex_InternalElement			pInternalElement	= NULL;
	 OV_INSTPTR_caex_Attribute					pTempAttribute		= NULL;
	 OV_INSTPTR_caex_Value						pTempValue			= NULL;
	 OV_STRING									Buffer				= NULL;
	 SOSX_PropertyDescription					Property			= {NULL};

#undef Finally
#define Finally()								\
		freePropertyDescription(&Property);		\
		ov_string_setvalue(&Buffer,NULL);		\

	 if (pPropertyToBeRead == NULL || pTargetContainer == NULL){
		 log_error("PropertyToBeRead and/or target not found!");
		 result = OV_ERR_GENERIC;
		 Finally();
		 return result;
	 }

	 /* read all attributes of the Property */
	 Property.pTarget = Ov_DynamicPtrCast(ov_domain,pPropertyToBeRead);
	 sosx_informationModelManagement_simplePropertyRead(&Property);

	 /* create InternalElement representing the Property in CAEX */
	 Sosx_CreateSystemUnit(pTargetContainer,pInternalElement,Property.Name,Property.CaexLib);
	 if(!readStateOnly){
		 /* create xPos Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"xPos",inttostring(Property.xPos,&Buffer),"xs:unsignedInt");

		 /* create yPos Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"yPos",inttostring(Property.yPos,&Buffer),"xs:unsignedInt");


		 /* create name Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"name",Property.Name,"xs:string");
	 }
	 /* read all children of the Property (PropertyInformation) */
	 Ov_ForEachChildEx(ov_containment,pPropertyToBeRead,pTemp,sosx_PropertyInformation){
		 result = sosx_workflowManagement_readElement(Ov_DynamicPtrCast(ov_domain,pTemp),Ov_DynamicPtrCast(ov_domain,pInternalElement),FALSE,NULL,readStateOnly);
		 if(Ov_Fail(result)){
			 logfile_error("Could not read the children of the property",pPropertyToBeRead->v_name);
			 Finally();
			 return result;
		 }
	 }

	 Finally();
	 return result;
 }

 /********************************************************************************************
  * PropertyInformation - This function reads a PropertyInformation
  * @param pPropertyInformationDes - Pointer to the structure in which the information will be stored
  * @return OV_RESULT error level
  */
 OV_RESULT sosx_informationModelManagement_simplePropertyInformationRead(
		 SOSX_PropertyInformationDescription		*pPropertyInformationDes
 ){
	 OV_RESULT									result		= OV_ERR_OK;

#undef Finally
#define Finally()

	 /* identifier */
	 ov_string_setvalue(&pPropertyInformationDes->Identifier,Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_identifier);

	 /* caexLibrary */
	 ov_string_setvalue(&pPropertyInformationDes->CaexLib,Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_caexLibrary);

	 /* source */
	 ov_string_setvalue(&pPropertyInformationDes->source,Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_source);

	 /* value */
	 ov_variable_setanyvalue(&pPropertyInformationDes->value,sosx_PropertyInformation_value_get(Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)));

	 /* valueVec */
	 ov_variable_setanyvalue(&pPropertyInformationDes->valueVec,sosx_PropertyInformation_valueVec_get(Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)));

	 /* unit */
	 ov_string_setvalue(&pPropertyInformationDes->unit,Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_unit);

	 /* type */
	 ov_string_setvalue(&pPropertyInformationDes->type,Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_type);

	 /* read validFrom */
	 pPropertyInformationDes->validFrom = Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_validFrom;

	 /* read validUntil */
	 pPropertyInformationDes->validUntil = Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_validUntil;

	 /* read xPos */
	 pPropertyInformationDes->xPos = Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_xPos;

	 /* read yPos */
	 pPropertyInformationDes->yPos = Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_yPos;

	 /* read timeStamps */
	 Ov_SetDynamicVectorValue(&pPropertyInformationDes->timeStamps,
			 Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_timeStamps.value,
			 Ov_DynamicPtrCast(sosx_PropertyInformation,pPropertyInformationDes->pTarget)->v_timeStamps.veclen,TIME);

	 return result;
 }


 OV_STRING valueToString(
		 OV_ANY				*value,
		 OV_UINT			index,
		 OV_STRING*			tmpStr
 ){
	 OV_STRING			tmpStr2 	= NULL;
	 OV_UINT			memsize		= 0;

#undef Finally
#define Finally()								\
		ov_string_setvalue(&tmpStr2,NULL);		\

	 switch(value->value.vartype & OV_VT_KSMASK){

	 case (OV_VT_STRING ) : Finally();
	 return value->value.valueunion.val_string;

	 case (OV_VT_STRING_VEC)	:	{
		 if(value->value.valueunion.val_string_vec.veclen > 0){
			 memsize = value->value.valueunion.val_string_vec.veclen;
			 ov_string_setvalue(tmpStr,value->value.valueunion.val_string_vec.value[index]);
			 for(OV_UINT i = 1;i < memsize ;i++){
				 if(index + i < memsize){
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,value->value.valueunion.val_string_vec.value[index + i]);
				 }else{
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,value->value.valueunion.val_string_vec.value[index + i - memsize]);
				 }
			 }
		 }
		 Finally();
		 return *tmpStr;
	 }

	 case (OV_VT_BOOL) : ov_string_print(tmpStr,"%d", value->value.valueunion.val_bool);
	 Finally();
	 return *tmpStr;

	 case (OV_VT_BOOL_VEC)	:	{
		 if(value->value.valueunion.val_bool_vec.veclen > 0){
			 memsize = value->value.valueunion.val_bool_vec.veclen;
			 ov_string_print(tmpStr,"%d", value->value.valueunion.val_bool_vec.value[index]);
			 for(OV_UINT i = 1;i < memsize ;i++){
				 if(index + i < memsize){
					 ov_string_print(&tmpStr2,"%d", value->value.valueunion.val_bool_vec.value[index + i]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }else{
					 ov_string_print(&tmpStr2,"%d", value->value.valueunion.val_bool_vec.value[index  + i - memsize]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }
			 }
		 }
		 Finally();
		 return *tmpStr;
	 }

	 case  (OV_VT_INT) : ov_string_print(tmpStr,"%d", value->value.valueunion.val_int);
	 Finally();
	 return *tmpStr;

	 case  (OV_VT_INT_VEC) :{
		 if(value->value.valueunion.val_int_vec.veclen > 0){
			 memsize = value->value.valueunion.val_int_vec.veclen;
			 ov_string_print(tmpStr,"%d", value->value.valueunion.val_int_vec.value[index]);
			 for(OV_UINT i = 1;i < memsize ;i++){
				 if(index + i < memsize){
					 ov_string_print(&tmpStr2,"%d", value->value.valueunion.val_int_vec.value[index + i]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }else{
					 ov_string_print(&tmpStr2,"%d", value->value.valueunion.val_int_vec.value[index  + i - memsize]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }
			 }
		 }
		 Finally();
		 return *tmpStr;
	 }

	 case (OV_VT_UINT) : ov_string_print(tmpStr,"%u", value->value.valueunion.val_uint);
	 Finally();
	 return *tmpStr;

	 case (OV_VT_UINT_VEC)	:	{
		 if(value->value.valueunion.val_uint_vec.veclen > 0){
			 memsize = value->value.valueunion.val_uint_vec.veclen;
			 ov_string_print(tmpStr,"%u", value->value.valueunion.val_uint_vec.value[index]);
			 for(OV_UINT i = 1;i < memsize ;i++){
				 if(index + i < memsize){
					 ov_string_print(&tmpStr2,"%u", value->value.valueunion.val_uint_vec.value[index + i]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }else{
					 ov_string_print(&tmpStr2,"%u", value->value.valueunion.val_uint_vec.value[index  + i - memsize]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }
			 }
		 }
		 Finally();
		 return *tmpStr;
	 }

	 case (OV_VT_SINGLE) : ov_string_print(tmpStr,"%f", value->value.valueunion.val_single);
	 Finally();
	 return *tmpStr;

	 case (OV_VT_SINGLE_VEC) :	{
		 if(value->value.valueunion.val_single_vec.veclen > 0){
			 memsize = value->value.valueunion.val_single_vec.veclen;
			 ov_string_print(tmpStr,"%f", value->value.valueunion.val_single_vec.value[index]);
			 for(OV_UINT i = 1;i < memsize ;i++){
				 if(index + i < memsize){
					 ov_string_print(&tmpStr2,"%f", value->value.valueunion.val_single_vec.value[index + i]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }else{
					 ov_string_print(&tmpStr2,"%f", value->value.valueunion.val_single_vec.value[index  + i - memsize]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }
			 }
		 }
		 Finally();
		 return *tmpStr;
	 }

	 case (OV_VT_DOUBLE) : ov_string_print(tmpStr,"%f", value->value.valueunion.val_double);
	 Finally();
	 return *tmpStr;

	 case (OV_VT_DOUBLE_VEC)	:	{
		 if(value->value.valueunion.val_double_vec.veclen > 0){
			 memsize = value->value.valueunion.val_double_vec.veclen;
			 ov_string_print(tmpStr,"%f", value->value.valueunion.val_double_vec.value[index]);
			 for(OV_UINT i = 1;i < memsize ;i++){
				 if(index + i < memsize){
					 ov_string_print(&tmpStr2,"%f", value->value.valueunion.val_double_vec.value[index + i]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }else{
					 ov_string_print(&tmpStr2,"%f", value->value.valueunion.val_double_vec.value[index  + i - memsize]);
					 ov_string_append(tmpStr,",");
					 ov_string_append(tmpStr,tmpStr2);
				 }
			 }
		 }
		 Finally();
		 return *tmpStr;
	 }

	 default : Finally();
	 return NULL;
	 }

	 return NULL;
 }

 OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readPropertyInformation(
		 OV_INSTPTR_sosx_PropertyInformation			pPropertyInformationToBeRead,
		 OV_INSTPTR_ov_domain							pTargetContainer,
		 OV_BOOL										readStateOnly
 ){
	 OV_RESULT									result				= OV_ERR_OK;
	 OV_INSTPTR_caex_InternalElement			pInternalElement	= NULL;
	 OV_INSTPTR_caex_Attribute					pTempAttribute		= NULL;
	 OV_INSTPTR_caex_Value						pTempValue			= NULL;
	 OV_INSTPTR_caex_RoleRequirements			pRoleReq			= NULL;
	 OV_STRING									timeStamps			= NULL;
	 OV_STRING									Buffer				= NULL;
	 SOSX_PropertyInformationDescription		PropertyInformation	= {NULL};

#undef Finally
#define Finally()													\
		freePropertyInformationDescription(&PropertyInformation);	\
		ov_string_setvalue(&timeStamps,NULL);						\
		ov_string_setvalue(&Buffer,NULL);							\

	 if (pPropertyInformationToBeRead == NULL || pTargetContainer == NULL){
		 log_error("PropertyInfoarmationToBeRead and/or target not found!");
		 result = OV_ERR_GENERIC;
		 Finally();
		 return result;
	 }

	 /* read all attributes of the PropertyInformation */
	 PropertyInformation.pTarget = Ov_DynamicPtrCast(ov_domain,pPropertyInformationToBeRead);
	 sosx_informationModelManagement_simplePropertyInformationRead(&PropertyInformation);

	 /* create InternalElement representing the PropertyInformtion in CAEX */
	 Sosx_CreateRole(pTargetContainer,pInternalElement,PropertyInformation.Identifier,pRoleReq,PropertyInformation.CaexLib);

	 /* create validFrom Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validFrom",ov_time_timetoascii_local(&PropertyInformation.validFrom),"xs:dateTime");

	 /* create validUntil Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validUntil",ov_time_timetoascii_local(&PropertyInformation.validUntil),"xs:dateTime");

	 /* create type Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"type",PropertyInformation.type,"xs:string");

	 /* create source Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"source",PropertyInformation.source,"xs:string");

	 /* create value Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"value",valueToString(&PropertyInformation.value,pPropertyInformationToBeRead->v_index,&Buffer), datatypeToString(PropertyInformation.value.value.vartype));

	 /* create unit Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"unit",PropertyInformation.unit,"xs:string");

	 if(!readStateOnly){
		 /* create valueVec Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"valueVec",valueToString(&PropertyInformation.valueVec,pPropertyInformationToBeRead->v_index,&Buffer),"xs:string");

		 /* create xPos Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"xPos",inttostring(PropertyInformation.xPos,&Buffer),"xs:unsignedInt");

		 /* create yPos Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"yPos",inttostring(PropertyInformation.yPos,&Buffer),"xs:unsignedInt");

		 /* create timeStamps string */
		 if(PropertyInformation.timeStamps.veclen != 0){
			 ov_string_setvalue(&timeStamps,ov_time_timetoascii_local(&PropertyInformation.timeStamps.value[pPropertyInformationToBeRead->v_index]));
			 for(OV_UINT i = 1;i < PropertyInformation.timeStamps.veclen ;i++){
				 if(pPropertyInformationToBeRead->v_index + i < PropertyInformation.timeStamps.veclen){
					 ov_string_append(&timeStamps,",");
					 ov_string_append(&timeStamps,ov_time_timetoascii_local(&PropertyInformation.timeStamps.value[pPropertyInformationToBeRead->v_index + i]));
				 }else{
					 ov_string_append(&timeStamps,",");
					 ov_string_append(&timeStamps,ov_time_timetoascii_local(&PropertyInformation.timeStamps.value[pPropertyInformationToBeRead->v_index + i - PropertyInformation.timeStamps.veclen]));
				 }
			 }
		 }
		 /* create timeStamps Attribute and Value */
		 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"timeStamps",timeStamps,"xs:string");
	 }

	 Finally();
	 return result;
 }

 /**
  * Stream
  */
 OV_RESULT sosx_informationModelManagement_simpleStreamRead(
		 SOSX_StreamDescription					*pStreamDes
 ){
	 OV_RESULT									result				= OV_ERR_OK;

#undef Finally
#define Finally()

	 /* read identifier */
	 ov_string_setvalue(&pStreamDes->Identifier,Ov_DynamicPtrCast(sosx_Stream,pStreamDes->pTarget)->v_identifier);

	 /* caexLibrary */
	 ov_string_setvalue(&pStreamDes->CaexLib,Ov_DynamicPtrCast(sosx_Stream,pStreamDes->pTarget)->v_caexLibrary);

	 /* read validFrom */
	 pStreamDes->validFrom = Ov_DynamicPtrCast(sosx_Stream,pStreamDes->pTarget)->v_validFrom;

	 /* read validUntil */
	 pStreamDes->validUntil = Ov_DynamicPtrCast(sosx_Stream,pStreamDes->pTarget)->v_validUntil;

	 /*read visualLayout*/
	 pStreamDes->visualLayout = Ov_DynamicPtrCast(sosx_Stream,pStreamDes->pTarget)->v_visualLayout;

	 /* read all Links */
	 readLinks(&pStreamDes->isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pStreamDes->pTarget));

	 return result;
 }

 OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readStream(
		 OV_INSTPTR_sosx_Stream				pStreamToBeRead,
		 OV_INSTPTR_ov_domain				pTargetContainer,
		 OV_BOOL							readStateOnly
 ){
	 OV_RESULT								result				= OV_ERR_OK;
	 OV_INSTPTR_caex_InternalElement		pInternalElement	= NULL;
	 OV_INSTPTR_caex_Attribute				pTempAttribute		= NULL;
	 OV_INSTPTR_caex_Value					pTempValue			= NULL;
	 OV_INSTPTR_caex_RoleRequirements		pRoleReq			= NULL;
	 SOSX_StreamDescription					Stream				= {NULL};


#undef	Finally
#define Finally()									\
		freeStreamDescription(&Stream);				\

	 if (pStreamToBeRead == NULL || pTargetContainer == NULL){
		 log_error("StreamToBeRead and/or target not found!");
		 result = OV_ERR_GENERIC;
		 Finally();
		 return result;
	 }

	 /* read all attributes of the Stream */
	 Stream.pTarget = Ov_DynamicPtrCast(ov_domain,pStreamToBeRead);
	 sosx_informationModelManagement_simpleStreamRead(&Stream);

	 /* create InternalElement representing the Stream in CAEX */
	 Sosx_CreateRole(pTargetContainer,pInternalElement,Stream.Identifier,pRoleReq,Stream.CaexLib);

	 /* create validFrom Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validFrom",ov_time_timetoascii_local(&Stream.validFrom),"xs:dateTime");

	 /* create validFrom Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"validUntil",ov_time_timetoascii_local(&Stream.validUntil),"xs:dateTime");

	 /* create visualLayout Attribute and Value */
	 Sosx_CreateAttributeAndValue(pTempAttribute,pTempValue,pInternalElement,"visualLayout",Stream.visualLayout,"xs:string");

	 /* export links */
	 result = exportLinks(&Stream.isLinkedTo,Ov_DynamicPtrCast(sosx_BaseElement,pStreamToBeRead),pInternalElement);
	 if(Ov_Fail(result)){
		 logfile_error("Could not export the links of ",pStreamToBeRead->v_identifier);
		 Finally();
		 return result;
	 }

	 Finally();
	 return result;
 }

 OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_readAlternative(
		 OV_INSTPTR_sosx_Alternative			pAlternativeToBeRead,
		 OV_INSTPTR_ov_domain				pTragetContainer,
		 OV_BOOL								readStateOnly
 ){
#undef Finally
#define Finally()

	 Finally();
	 return OV_ERR_NOTIMPLEMENTED;
 }

#endif
