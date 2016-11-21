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

#include "sosx.h"
#include "libov/ov_macros.h"
#include "caex.h"
#include "sosxcommon.h"
#include "libov/ov_path.h"
#include "libov/ov_result.h"


#define undoCreateInCaseOfError(result,pSosx)				\
		if(Ov_Fail(result)){								\
			if(pSosx != NULL){								\
				log_info("Error occurred");					\
				Ov_DeleteObject(pSosx);						\
			}												\
		}													\

/**************************************************************************************************
 * SoSContainer
 * createSimpleSoSContainer - This function creates a simple SoSContainer based on the specification SoSContainerSpec
 * with out an internal structure.
 * @param SoSContainerSpec - pointer to a Structure that contains all important informations for the SoSContainer creation
 * @param ppCreatedSoSContainer - pointer to the created SoSContainer
 * @return - the result of SoSContainer creation (OV_RESULT)
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimpleSoSContainer(
		SOSX_SoSContainerDescription	*SoSContainerSpec,
		OV_INSTPTR_sosx_SoSContainer 	*ppCreatedSoSContainer
){
	OV_RESULT						result					= OV_ERR_OK;
	OV_INSTPTR_sosx_SoSContainer	pCreatedSoSContainer	= NULL;
	OV_STRING						StdExtRef				= NULL;

#undef	Finally
#define Finally()												\
		undoCreateInCaseOfError(result,pCreatedSoSContainer)  	\
		ov_string_setvalue(&StdExtRef,NULL);					\

	/* Check if Target or Name is NULL */
	if(SoSContainerSpec->pTarget == NULL ||
			SoSContainerSpec->Name == NULL){
		log_error("Target and/or name not found. Cannot create the SoSContainer");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* Check if SoSContainer already exists */
	if(Ov_SearchChild(ov_containment,SoSContainerSpec->pTarget,SoSContainerSpec->Name) != NULL){
		logfile_error("The SoSContainer already exists:", SoSContainerSpec->Name);
		result = OV_ERR_ALREADYEXISTS;
		Finally();
		return result;
	}

	/* create SoSContainer */
	result = Ov_CreateObject(sosx_SoSContainer,pCreatedSoSContainer,SoSContainerSpec->pTarget,SoSContainerSpec->Name);
	if(Ov_Fail(result)){
		log_error("Cannot create the SoSContainer");
		Finally();
		return result;
	}

	/* set Attributes of SoSContainer */
	/* set name */
	result = sosx_SoSContainer_name_set(pCreatedSoSContainer,SoSContainerSpec->Name);
	if (Ov_Fail(result)){
		logfile_error("Cannot set the name of: ", SoSContainerSpec->Name);
		Finally();
		return result;
	}

	/* set BaseLibrary as externalReference  */
	Ov_SetDynamicVectorLength(&SoSContainerSpec->externalReference,SoSContainerSpec->externalReference.veclen + 1,STRING);
	ov_string_setvalue(&SoSContainerSpec->externalReference.value[SoSContainerSpec->externalReference.veclen-1],"BaseLibs@./BaseLibrary.xml");

	result = sosx_SoSContainer_externalReference_set(pCreatedSoSContainer,
			SoSContainerSpec->externalReference.value, SoSContainerSpec->externalReference.veclen);
	if (Ov_Fail(result)){
		logfile_error("Cannot set the externalReference of: ", SoSContainerSpec->Name);
		Finally();
		return result;
	}

	/* finished */
	*ppCreatedSoSContainer = pCreatedSoSContainer;
	return result;
}

/**************************************************************************************************
 * System
 * createSimpleSystem - This function creates a simple system based on the specification SystemSpec
 * with out an internal structure.
 * @param SystemSpec - pointer to a Structure that contains all important informations for the system creation
 * @param ppCreatedSystem - pointer to the created System
 * @return - the result of system creation (OV_RESULT)
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimpleSystem(
		SOSX_SystemDescription				*SystemSpec,
		OV_INSTPTR_sosx_System 				*ppCreatedSystem
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_sosx_System				 	pCreatedSystem	= NULL;
#undef	Finally
#define Finally()											\
		undoCreateInCaseOfError(result,pCreatedSystem)  	\

	/* Check if Target or Name is NULL */
	if(SystemSpec->pTarget == NULL ||
			SystemSpec->Name == NULL){
		log_error("Target and/or name not found. Cannot create the system");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* Check if system already exists */
	if(Ov_SearchChild(ov_containment,SystemSpec->pTarget,SystemSpec->Name) != NULL){
		logfile_error("The System already exists:", SystemSpec->Name);
		result = OV_ERR_ALREADYEXISTS;
		Finally();
		return result;
	}

	/* create System */
	result = Ov_CreateObject(sosx_System,pCreatedSystem,SystemSpec->pTarget,SystemSpec->Name);
	if(Ov_Fail(result)){
		log_error("Cannot create the system");
		Finally();
		return result;
	}

	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,pCreatedSystem,SystemSpec);
	SetVarOfDetailedElement(result,pCreatedSystem,SystemSpec);
	SetVarOfSosxDomain(result,pCreatedSystem,SystemSpec);
	SetVarOfStructureElement(result,pCreatedSystem,SystemSpec);
	/* finished */
	*ppCreatedSystem = pCreatedSystem;
	return result;
}

/*****************************************************************************************
 * Process
 * createSimpleProcess - This function creates a simple Process based on the specification ProcessSpec
 * without Ports or Properties.
 * @param ProcessSpec - pointer to a Structure that contains all important informations for the Process creation
 * @param ppCreatedProcess - pointer to the created Process
 * @return - the result of the Process creation (OV_RESULT)
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimpleProcess(
		SOSX_ProcessDescription				*ProcessSpec,
		OV_INSTPTR_sosx_Process 			*ppCreatedProcess
){
	OV_RESULT					result				= OV_ERR_OK;
	OV_INSTPTR_sosx_Process 	pCreatedProcess		= NULL;

#undef	Finally
#define Finally()											\
		undoCreateInCaseOfError(result,pCreatedProcess)  	\

	/* Check if Target or Name is NULL */
	if(ProcessSpec->pTarget == NULL ||
			ProcessSpec->Name == NULL){
		log_error("Target and/or name not found. Cannot create the Process");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* check if Process already exists. */
	if(Ov_SearchChild(ov_containment,ProcessSpec->pTarget,ProcessSpec->Name) != NULL){
		logfile_error("The Process already exists:", ProcessSpec->Name);
		result = OV_ERR_ALREADYEXISTS;
		Finally();
		return result;
	}

	/* Create Process */
	result = Ov_CreateObject(sosx_Process,pCreatedProcess,ProcessSpec->pTarget, ProcessSpec->Name);
	if(Ov_Fail(result)){
		log_error("Cannot create the process");
		Finally();
		return result;
	}

	/* set name */
	result = sosx_DetailedElement_name_set(Ov_DynamicPtrCast(sosx_DetailedElement,pCreatedProcess),ProcessSpec->Name);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the name of ",pCreatedProcess->v_identifier);
		Finally();
		return result;
	}

	/* set externalInfo*/
	result = sosx_StructureElement_externalInfo_set(Ov_DynamicPtrCast(sosx_StructureElement,pCreatedProcess),ProcessSpec->externalInfo.value,ProcessSpec->externalInfo.veclen);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the externalInfo of ",pCreatedProcess->v_identifier);
		Finally();
		return result;
	}

	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,pCreatedProcess,ProcessSpec);
	SetVarOfDetailedElement(result,pCreatedProcess,ProcessSpec);
	SetVarOfSosxDomain(result,pCreatedProcess,ProcessSpec);
	SetVarOfStructureElement(result,pCreatedProcess,ProcessSpec);

	/* finished */
	*ppCreatedProcess = pCreatedProcess;
	Finally();
	return result;
}



/***************************************************
 * PropertyInformation
 * createSimplePropertyInformation - This function creates a simple PropertyInformation based on the specification
 * PropertyInformationSpec
 * @param PropertyInformationSpec - Pointer to a Structure that contains all important informations for the PropertyInformation creation
 * @param ppCreatedPropertyInformation - pointer to the created PropertyInformation
 * @return - the result of the PropertyInformation creation (OV_RESULT)
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimplePropertyInformation(
		SOSX_PropertyInformationDescription	*PropertyInformationSpec,
		OV_INSTPTR_sosx_PropertyInformation	*ppCreatedPropertyInformation
){
	OV_RESULT								result						= OV_ERR_OK;
	OV_INSTPTR_sosx_PropertyInformation		pCreatedPropertyInformation	= NULL;
	OV_STRING								Identifier					= NULL;
	OV_UINT									RunningIndex				= 1;

#undef Finally
#define Finally()\
		ov_string_setvalue(&Identifier,NULL);							\
		undoCreateInCaseOfError(result,pCreatedPropertyInformation);  	\


	/* Check if Target is NULL */
	if(PropertyInformationSpec->pTarget == NULL){
		log_error("Target not found. Cannot create the PropertyInformation.");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	ov_string_setvalue(&Identifier,PropertyInformationSpec->Identifier);

	/* check if PropertyInformation with this Running Index already exists and increase Index if necessary */
	while(Ov_SearchChild(ov_containment,PropertyInformationSpec->pTarget,Identifier) != NULL){
		sprintf(Identifier,"%s%d",strrchr(Identifier,95),++RunningIndex);
	}

	/* Create PropertyInformation */
	result = Ov_CreateObject(sosx_PropertyInformation,pCreatedPropertyInformation,PropertyInformationSpec->pTarget,Identifier);
	if(Ov_Fail(result)){
		logfile_error("Cannot create the PropertyInformation:", Identifier);
		Finally();
		return result;
	}

	/* PropertyInformations should be included in the state file */
	sosx_sosxdomain_includeInStateFile_set(Ov_DynamicPtrCast(sosx_sosxdomain,pCreatedPropertyInformation),TRUE);

	/* set dataType */
	result = sosx_PropertyInformation_datatype_set(pCreatedPropertyInformation,PropertyInformationSpec->dataType);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the dataType of ",pCreatedPropertyInformation->v_identifier);
		Finally();
		return result;
	}

	/* set index */
	result = sosx_PropertyInformation_index_set(pCreatedPropertyInformation,0);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the index of ",pCreatedPropertyInformation->v_identifier);
		Finally();
		return result;
	}

	/* set value if not NULL*/
	if(PropertyInformationSpec->value.value.vartype != 0){
		Ov_SetAnyValue(&pCreatedPropertyInformation->v_value,&PropertyInformationSpec->value);
		if(Ov_Fail(result)){
			logfile_error("Cannot set the value of ",pCreatedPropertyInformation->v_identifier);
			Finally();
			return result;
		}
	}

	/* set source */
	result = sosx_PropertyInformation_source_set(pCreatedPropertyInformation,PropertyInformationSpec->source);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the source of ",pCreatedPropertyInformation->v_identifier);
		Finally();
		return result;
	}

	/* set type */
	result = sosx_PropertyInformation_type_set(pCreatedPropertyInformation,PropertyInformationSpec->type);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the type of ",pCreatedPropertyInformation->v_identifier);
		Finally();
		return result;
	}

	/* set unit */
	result = sosx_PropertyInformation_unit_set(pCreatedPropertyInformation,PropertyInformationSpec->unit);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the unit of ",pCreatedPropertyInformation->v_identifier);
		Finally();
		return result;
	}

	/* set timeStamps */
	if(PropertyInformationSpec->timeStamps.value != NULL){
		result = sosx_PropertyInformation_timeStamps_set(pCreatedPropertyInformation,PropertyInformationSpec->timeStamps.value,PropertyInformationSpec->timeStamps.veclen);
		if(Ov_Fail(result)){
			logfile_error("Cannot set the timeStamps of ",pCreatedPropertyInformation->v_identifier);
			Finally();
			return result;
		}
	}

	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,pCreatedPropertyInformation,PropertyInformationSpec);
	SetVarOfSosxDomain(result,pCreatedPropertyInformation,PropertyInformationSpec);

	/* set readStyle */
	result = sosx_sosxdomain_readStyle_set(Ov_DynamicPtrCast(sosx_sosxdomain,pCreatedPropertyInformation),PropertyInformationSpec->readStyle);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the readStyle of ",pCreatedPropertyInformation->v_identifier);
		Finally();
		return result;
	}

	/* finished */
	*ppCreatedPropertyInformation = pCreatedPropertyInformation;

	Finally();
	return result;
}


/************************************************************
 * Property
 * createSimpleProperty - This function creates a simple Property based on the specification PropertySpec
 * without any PropertyInformations
 * @param PropertySpec  - pointer to a Structure that contains all important informations for the Property creation
 * @param ppCreatedProperty - pointer to the created Property
 * @return - the result of the Property creation (OV_RESULT)
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimpleProperty(
		SOSX_PropertyDescription			*PropertySpec,
		OV_INSTPTR_sosx_Property			*ppCreatedProperty
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_sosx_Property				pCreatedProperty	= NULL;

#undef Finally
#define Finally()										\
		undoCreateInCaseOfError(result,pCreatedProperty)  	\

	/* Check if Target or Name is NULL */
	if(PropertySpec->pTarget == NULL ||
			PropertySpec->Name == NULL){
		log_error("Target and/or name not found. Cannot create the Property.");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* check if Property already exists */
	if(Ov_SearchChild(ov_containment,PropertySpec->pTarget,PropertySpec->Name) != NULL){
		logfile_error("The Property already exists:", PropertySpec->Name);
		result = OV_ERR_ALREADYEXISTS;
		Finally();
		return result;
	}

	/* Create Property */
	result = Ov_CreateObject(sosx_Property,pCreatedProperty,PropertySpec->pTarget,PropertySpec->Name);
	if(Ov_Fail(result)){
		logfile_error("Cannot create the Property:", PropertySpec->Name);
		Finally();
		return result;
	}

	/* set name */
	result = sosx_Property_name_set(pCreatedProperty,PropertySpec->Name);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the name of ",pCreatedProperty->v_identifier);
		Finally();
		return result;
	}

	/* set caexLibrary */
	result = sosx_sosxdomain_setCaexLibrary(Ov_DynamicPtrCast(sosx_sosxdomain,pCreatedProperty),
			Ov_DynamicPtrCast(caex_CAEXBasicObject,PropertySpec->pSource),PropertySpec->CaexLib);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the name of ",pCreatedProperty->v_identifier);
		Finally();
		return result;
	}

	SetVarOfSosxDomain(result,pCreatedProperty,PropertySpec);

	/* finished */
	*ppCreatedProperty = pCreatedProperty;

	Finally();
	return result;
}

/************************************************************************************
 * Port
 * createSimplePort - This function creates a simple Port based on the specification PortSpec
 * without any Property
 * @param PortSpec  - pointer to a Structure that contains all important informations for the Port creation
 * @param ppCreatedPort - pointer to the created Port
 * @return - the result of the Port creation (OV_RESULT)
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimplePort(
		SOSX_PortDescription				*PortSpec,
		OV_INSTPTR_sosx_Port				*ppCreatedPort
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_sosx_Port					pCreatedPort	= NULL;

#undef Finally
#define Finally()										\
		undoCreateInCaseOfError(result,pCreatedPort); 	\

	/* Check if Target or Name is NULL */
	if(PortSpec->pTarget == NULL ||
			PortSpec->Name == NULL){
		log_error("Target and/or name not found. Cannot create the Port");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* check if Port already exists */
	if(Ov_SearchChild(ov_containment,PortSpec->pTarget,PortSpec->Name) != NULL){
		logfile_error("The Port already exists:", PortSpec->Name);
		result = OV_ERR_ALREADYEXISTS;
		Finally();
		return result;
	}

	/* Create Port */
	result = Ov_CreateObject(sosx_Port,pCreatedPort,PortSpec->pTarget,PortSpec->Name);
	if(Ov_Fail(result)){
		logfile_error("Cannot create the Port:", PortSpec->Name);
		Finally();
		return result;
	}

	/* set name */
	result = sosx_DetailedElement_name_set(Ov_DynamicPtrCast(sosx_DetailedElement,pCreatedPort),PortSpec->Name);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the name of ",pCreatedPort->v_identifier);
		Finally();
		return result;
	}

	/* set StreamType */
	result = sosx_StreamHandler_StreamType_set(Ov_DynamicPtrCast(sosx_StreamHandler,pCreatedPort),PortSpec->StreamType);
	if(Ov_Fail(result)){
		logfile_error("Cannot set the StreamType of ",pCreatedPort->v_identifier);
		Finally();
		return result;
	}

	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,pCreatedPort,PortSpec);
	SetVarOfDetailedElement(result,pCreatedPort,PortSpec);
	SetVarOfSosxDomain(result,pCreatedPort,PortSpec);

	/* create Links */
	result = createLinks(&(PortSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,pCreatedPort));
	if(Ov_Fail(result)){
		logfile_error("Cannot create the links of ",pCreatedPort->v_identifier);
		Finally();
		return result;
	}

	/* finished */
	*ppCreatedPort = pCreatedPort;

	Finally();
	return result;
}

/***********************************************************************************************
 * SourceSink
 * createSimpleSourceSink - This function creates a simple SourceSink based on the specification
 * SourceSinkSpec without any Property
 * @param SourceSinkSpec - Pointer to a Structure that contains all important informations for the SourceSink creation
 * @param ppCreatedSourceSink - pointer to the created SourceSink
 * @return - the result of the SourceSink creation (OV_RESULT)
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimpleSourceSink(
		SOSX_SourceSinkDescription			*SourceSinkSpec,
		OV_INSTPTR_sosx_SourceSink			*ppCreatedSourceSink
){
	OV_RESULT								result				= OV_ERR_OK;
	OV_INSTPTR_sosx_SourceSink				pCreatedSourceSink	= NULL;

#undef Finally
#define Finally()											\
		undoCreateInCaseOfError(result,pCreatedSourceSink)  \

	/* Check if Target or Name is NULL */
	if(SourceSinkSpec->pTarget == NULL ||
			SourceSinkSpec->Name == NULL){
		log_error("Target and/or name not found. Cannot create the SourceSink");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	if(Ov_SearchChild(ov_containment,SourceSinkSpec->pTarget,SourceSinkSpec->Name) != NULL){
		logfile_error("The SourceSink already exists:", SourceSinkSpec->Name);
		result = OV_ERR_ALREADYEXISTS;
		Finally();
		return result;
	}
	/* Create SourceSink */
	result = Ov_CreateObject(sosx_SourceSink,pCreatedSourceSink,SourceSinkSpec->pTarget, SourceSinkSpec->Name);
	if (Ov_Fail(result)){
		logfile_error("Cannot create the SourceSink:", SourceSinkSpec->Name);
		Finally();
		return result;
	}

	/* set name */
	result = sosx_DetailedElement_name_set(Ov_DynamicPtrCast(sosx_DetailedElement,pCreatedSourceSink),SourceSinkSpec->Name);
	if (Ov_Fail(result)){
		logfile_error("Cannot set the name of: ", SourceSinkSpec->Name);
		Finally();
		return result;
	}

	/* set StreamType */
	result = sosx_StreamHandler_StreamType_set(Ov_DynamicPtrCast(sosx_StreamHandler,pCreatedSourceSink),SourceSinkSpec->StreamType);
	if (Ov_Fail(result)){
		logfile_error("Cannot set the StreamType of: ", SourceSinkSpec->Name);
		Finally();
		return result;
	}

	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,pCreatedSourceSink,SourceSinkSpec);
	SetVarOfDetailedElement(result,pCreatedSourceSink,SourceSinkSpec);
	SetVarOfSosxDomain(result,pCreatedSourceSink,SourceSinkSpec);

	/* create Links */
	result = createLinks(&(SourceSinkSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,pCreatedSourceSink));
	if (Ov_Fail(result)){
		logfile_error("Cannot create the links of: ", SourceSinkSpec->Name);
		Finally();
		return result;
	}

	/* finished */
	*ppCreatedSourceSink = pCreatedSourceSink;

	Finally();
	return result;
}



/*********************************************************************************************
 * DistributionNode
 * createSimpleDistributionNode - This function creates a simple DistributionNode based on the specification PropertySpec
 * without any Properties
 * @param PropertySpec  - pointer to a Structure that contains all important informations for the DistributionNode creation
 * @param ppCreatedProperty - pointer to the created DistributionNode
 * @return - the result of the DistributionNode creation (OV_RESULT)
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimpleDistributionNode(
		SOSX_DistributionNodeDescription	*DistributionNodeSpec,
		OV_INSTPTR_sosx_DistributionNode	*ppCreatedDistributionNode
){
	OV_RESULT								result						= OV_ERR_OK;
	OV_INSTPTR_sosx_DistributionNode		pCreatedDistributionNode	= NULL;

#undef Finally
#define Finally()													\
		undoCreateInCaseOfError(result,pCreatedDistributionNode)  	\

	/* Check if Target or Name is NULL */
	if(DistributionNodeSpec->pTarget == NULL ||
			DistributionNodeSpec->Name == NULL){
		log_error("Target and/or name not found. Cannot create the Port");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* check if DistributionNode already exists */
	if(Ov_SearchChild(ov_containment,DistributionNodeSpec->pTarget,DistributionNodeSpec->Name) != NULL){
		logfile_error("The DistributionNode already exists:", DistributionNodeSpec->Name);
		result = OV_ERR_ALREADYEXISTS;
		Finally();
		return result;
	}

	/* Create DistributionNode */
	result = Ov_CreateObject(sosx_DistributionNode,pCreatedDistributionNode,DistributionNodeSpec->pTarget,DistributionNodeSpec->Name);
	if(Ov_Fail(result)){
		logfile_error("Cannot create the DistributionNode:", DistributionNodeSpec->Name);
		Finally();
		return result;
	}

	/* set name */
	result = sosx_DetailedElement_name_set(Ov_DynamicPtrCast(sosx_DetailedElement,pCreatedDistributionNode),DistributionNodeSpec->Name);
	if (Ov_Fail(result)){
		logfile_error("Cannot set the name of: ", DistributionNodeSpec->Name);
		Finally();
		return result;
	}

	/* set StreamType */
	result = sosx_StreamHandler_StreamType_set(Ov_DynamicPtrCast(sosx_StreamHandler,pCreatedDistributionNode),DistributionNodeSpec->StreamType);
	if (Ov_Fail(result)){
		logfile_error("Cannot set the StreamType of: ", DistributionNodeSpec->Name);
		Finally();
		return result;
	}

	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,pCreatedDistributionNode,DistributionNodeSpec);
	SetVarOfDetailedElement(result,pCreatedDistributionNode,DistributionNodeSpec);
	SetVarOfSosxDomain(result,pCreatedDistributionNode,DistributionNodeSpec);

	/* create Links */
	result = createLinks(&(DistributionNodeSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,pCreatedDistributionNode));
	if (Ov_Fail(result)){
		logfile_error("Cannot create the links of: ", DistributionNodeSpec->Name);
		Finally();
		return result;
	}

	/* finished */
	*ppCreatedDistributionNode = pCreatedDistributionNode;

	Finally();
	return result;
}

/**********************************************************
 * Stream
 * createSimpleStream - This function creates a simple Stream based on the specification
 * StreamSpec
 * @param StreamSpec - Pointer to a Structure that contains all important informations for the Stream creation
 * @param ppCreatedStream - pointer to the created Stream
 * @return - the result of the Stream creation (OV_RESULT)
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_createSimpleStream(
		SOSX_StreamDescription				*StreamSpec,
		OV_INSTPTR_sosx_Stream				*ppCreatedStream
){
	OV_RESULT								result						= OV_ERR_OK;
	OV_INSTPTR_sosx_Stream					pCreatedStream				= NULL;
	OV_STRING								Identifier					= NULL;

#undef Finally
#define Finally()											\
		ov_string_setvalue(&Identifier,NULL);				\
		undoCreateInCaseOfError(result,pCreatedStream);  	\

	/* Check if Target is NULL */
	if(StreamSpec->pTarget == NULL){
		log_error("Target not found. Cannot create the Stream.");
		result = OV_ERR_BADPARAM;
		Finally();
		return result;
	}

	/* Create Stream */
	result = Ov_CreateObject(sosx_Stream,pCreatedStream,StreamSpec->pTarget,StreamSpec->Identifier);
	if(Ov_Fail(result)){
		logfile_error("Cannot create the Stream:",StreamSpec->Identifier);
		Finally();
		return result;
	}

	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,pCreatedStream,StreamSpec);

	result = sosx_sosxdomain_setCaexLibrary(Ov_DynamicPtrCast(sosx_sosxdomain,pCreatedStream),
			Ov_DynamicPtrCast(caex_CAEXBasicObject,StreamSpec->pSource),StreamSpec->CaexLib);
			if(Ov_Fail(result)){
				logfile_error("Could not store the caex library attribute", pCreatedStream->v_identifier);
				Finally();
				return result;
			}

	result = sosx_Stream_visualLayout_set(pCreatedStream,StreamSpec->visualLayout);
	if(Ov_Fail(result)){
		logfile_error("Could not store the visualLayout attribute",pCreatedStream->v_identifier);
		Finally();
		return result;
	}

	/* create Links */
	result = createLinks(&(StreamSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,pCreatedStream));
	if (Ov_Fail(result)){
		logfile_error("Cannot create the links of: ", pCreatedStream->v_identifier);
		Finally();
		return result;
	}

	/* finished */
	*ppCreatedStream = pCreatedStream;

	Finally();
	return result;
}

#endif
