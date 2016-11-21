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


#include "informationModelManagement.h"
#include "sosx.h"
#include "libov/ov_macros.h"
#include "caex.h"
#include "sosxcommon.h"
#include "libov/ov_path.h"
#include "libov/ov_result.h"

/**
 * SoSContainer
 * @param SoSContainerSpec
 * @return
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimpleSoSContainerUpdate(
		SOSX_SoSContainerDescription	*SoSContainerSpec
){
	OV_RESULT								result			= OV_ERR_OK;
#undef	Finally
#define Finally()

	/* Check if pSoSContainerToBeUpdated is NULL */
	if(SoSContainerSpec == NULL){
		log_error("SoSContainerSpec not found. Cannot update the SoSContainer");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of SoSContainer */
	/* set name */
	result = sosx_SoSContainer_name_set(Ov_DynamicPtrCast(sosx_SoSContainer,SoSContainerSpec->pTarget),SoSContainerSpec->Name);

	/* set externalReference */
	result = sosx_SoSContainer_externalReference_set(Ov_DynamicPtrCast(sosx_SoSContainer,SoSContainerSpec->pTarget),
			SoSContainerSpec->externalReference.value, SoSContainerSpec->externalReference.veclen);

	/* finished */
	return result;
}

/**
 * System
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimpleSystemUpdate(
		SOSX_SystemDescription	*SystemSpec
){
	OV_RESULT								result			= OV_ERR_OK;
#undef	Finally
#define Finally()

	/* Check if pSystemToBeUpdated is NULL */
	if(SystemSpec == NULL){
		log_error("SystemSpec not found. Cannot update the system");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of System */
	SetVarOfBaseElement(result,SystemSpec->pTarget,SystemSpec);
	SetVarOfDetailedElement(result,SystemSpec->pTarget,SystemSpec);
	SetVarOfStructureElement(result,SystemSpec->pTarget,SystemSpec);

	/* finished */
	return result;
}

/* Process
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimpleProcessUpdate(
		SOSX_ProcessDescription	*ProcessSpec
){
	OV_RESULT								result			= OV_ERR_OK;
#undef	Finally
#define Finally()

	/* Check if pProcessToBeUpdated is NULL */
	if(ProcessSpec == NULL){
		log_error("pProcessToBeUpdated not found. Cannot update the system");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of Process */
	SetVarOfBaseElement(result,ProcessSpec->pTarget,ProcessSpec);
	SetVarOfDetailedElement(result,ProcessSpec->pTarget,ProcessSpec);
	// SetVarOfSosxDomain(result,ProcessSpec->pTarget,ProcessSpec);
	SetVarOfStructureElement(result,ProcessSpec->pTarget,ProcessSpec);

	/* finished */
	return result;
}

/**
 * Port
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimplePortUpdate(
		SOSX_PortDescription	*PortSpec
){
	OV_RESULT								result			= OV_ERR_OK;
#undef	Finally
#define Finally()

	/* Check if pPortUpdated is NULL */
	if(PortSpec == NULL){
		log_error("pPortUpdated not found. Cannot update the port");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of System */
	/* set StreamType */
	result = sosx_StreamHandler_StreamType_set(Ov_DynamicPtrCast(sosx_StreamHandler,PortSpec->pTarget),PortSpec->StreamType);

	SetVarOfBaseElement(result,PortSpec->pTarget,PortSpec);
	SetVarOfDetailedElement(result,PortSpec->pTarget,PortSpec);
	// SetVarOfSosxDomain(result,PortSpec->pTarget,PortSpec);

	/* set wasConnectedTo*/
	result = sosx_StreamHandler_wasConnectedTo_set(Ov_DynamicPtrCast(sosx_StreamHandler,PortSpec->pTarget),PortSpec->wasConnectedTo);

	/* create links according to update */
	result = createLinks(&(PortSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,PortSpec->pTarget));

	/* finished */
	return result;
}


/**
 * SourceSink
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimpleSourceSinkUpdate(
		SOSX_SourceSinkDescription		*SourceSinkSpec
){
	OV_RESULT								result			= OV_ERR_OK;
#undef	Finally
#define Finally()

	/* Check if pSourceSinkToBeUpdated is NULL */
	if(SourceSinkSpec == NULL){
		log_error("pSourceSinkToBeUpdated not found. Cannot update the SourceSink");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of System */
	/* set StreamType */
	result = sosx_StreamHandler_StreamType_set(Ov_DynamicPtrCast(sosx_StreamHandler,SourceSinkSpec->pTarget),SourceSinkSpec->StreamType);

	SetVarOfBaseElement(result,SourceSinkSpec->pTarget,SourceSinkSpec);
	SetVarOfDetailedElement(result,SourceSinkSpec->pTarget,SourceSinkSpec);
	// SetVarOfSosxDomain(result,SourceSinkSpec->pTarget,SourceSinkSpec);

	/* set wasConnectedTo*/
	result = sosx_StreamHandler_wasConnectedTo_set(Ov_DynamicPtrCast(sosx_StreamHandler,SourceSinkSpec->pTarget),SourceSinkSpec->wasConnectedTo);

	/* create links according to update */
	result = createLinks(&(SourceSinkSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,SourceSinkSpec->pTarget));

	/* finished */
	return result;
}



/**
 * DistributionNode
 */
 OV_RESULT sosx_informationModelManagement_SimpleDistributionNodeUpdate(
		SOSX_DistributionNodeDescription	*DistributionNodeSpec
){
	OV_RESULT								result			= OV_ERR_OK;

#undef	Finally
#define Finally()

	/* Check if pDistributionNodeToBeUpdated is NULL */
	if(DistributionNodeSpec == NULL){
		log_error("pDistributionNodeToBeUpdated not found. Cannot update the SourceSink");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of System */
	/* set name */
	result = sosx_DetailedElement_name_set(Ov_DynamicPtrCast(sosx_DetailedElement,DistributionNodeSpec->pTarget),DistributionNodeSpec->Name);

	/* set StreamType */
	result = sosx_StreamHandler_StreamType_set(Ov_DynamicPtrCast(sosx_StreamHandler,DistributionNodeSpec->pTarget),DistributionNodeSpec->StreamType);

	/* set caexLibrary, validFrom, validUntil*/
	SetVarOfBaseElement(result,DistributionNodeSpec->pTarget,DistributionNodeSpec);
	SetVarOfDetailedElement(result,DistributionNodeSpec->pTarget,DistributionNodeSpec);
	// SetVarOfSosxDomain(result,DistributionNodeSpec->pTarget,DistributionNodeSpec);


	/* set wasConnectedTo*/
	result = sosx_StreamHandler_wasConnectedTo_set(Ov_DynamicPtrCast(sosx_StreamHandler,DistributionNodeSpec->pTarget),DistributionNodeSpec->wasConnectedTo);

	/* create links according to update */
	result = createLinks(&(DistributionNodeSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,DistributionNodeSpec->pTarget));

	/* finished */
	return result;
}


/**
 * Property
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimplePropertyUpdate(
		SOSX_PropertyDescription			*PropertySpec
){
	OV_RESULT								result			= OV_ERR_OK;
#undef	Finally
#define Finally()

	/* Check if pPropertyToBeUpdated is NULL */
	if(PropertySpec == NULL){
		log_error("pPropertyToBeUpdated not found. Cannot update the SourceSink");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of System */
	/* set name */
	result = sosx_Property_name_set(Ov_DynamicPtrCast(sosx_Property,PropertySpec->pTarget),PropertySpec->Name);

	/* set caexLibrary */
	result = sosx_sosxdomain_setCaexLibrary(Ov_DynamicPtrCast(sosx_sosxdomain,PropertySpec->pTarget),
			Ov_DynamicPtrCast(caex_CAEXBasicObject,PropertySpec->pSource),PropertySpec->CaexLib);

	/* finished */
	return result;
}

/* PropertyInformation
 *
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimplePropertyInformationUpdate(
		SOSX_PropertyInformationDescription			*PropertyInformationSpec
){
	OV_RESULT								result			= OV_ERR_OK;
#undef	Finally
#define Finally()

	/* Check if pPropertyInformationToBeUpdated is NULL */
	if(PropertyInformationSpec == NULL){
		log_error("pPropertyInformationToBeUpdated not found. Cannot update the SourceSink");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of PropertyInformation */
	/* set caexLibrary, validFrom, validUntil */
	SetVarOfBaseElement(result,PropertyInformationSpec->pTarget,PropertyInformationSpec);
	// SetVarOfSosxDomain(result,PropertyInformationSpec->pTarget,PropertyInformationSpec);

	/* set source */
	sosx_PropertyInformation_source_set(Ov_DynamicPtrCast(sosx_PropertyInformation,PropertyInformationSpec->pTarget),PropertyInformationSpec->source);

	/* set type */
	sosx_PropertyInformation_type_set(Ov_DynamicPtrCast(sosx_PropertyInformation,PropertyInformationSpec->pTarget),PropertyInformationSpec->type);

	/* set unit */
	sosx_PropertyInformation_unit_set(Ov_DynamicPtrCast(sosx_PropertyInformation,PropertyInformationSpec->pTarget),PropertyInformationSpec->unit);

	/* set value */
	sosx_PropertyInformation_value_set(Ov_DynamicPtrCast(sosx_PropertyInformation,PropertyInformationSpec->pTarget),&PropertyInformationSpec->value);

	/* finished */
	return result;
}

/**
 * Stream
 * @param PropertyInformationSpec
 * @param pPropertyInformationToBeUpdated
 * @return
 */
OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_SimpleStreamUpdate(
		SOSX_StreamDescription			*StreamSpec
){
	OV_RESULT								result			= OV_ERR_OK;

#undef	Finally
#define Finally()

	/* Check if pStreamToBeUpdated is NULL */
	if(StreamSpec == NULL){
		log_error("pStreamToBeUpdated not found. Cannot update the SourceSink");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* set Attributes of the Stream */
	/* set caexLibrary, validFrom, validUntil*/
	SetVarOfBaseElement(result,StreamSpec->pTarget,StreamSpec);

	/* create links according to update */
	result = createLinks(&(StreamSpec->isLinkedTo),Ov_DynamicPtrCast(sosx_BaseElement,StreamSpec->pTarget));

	/* finished */
	return result;
}

OV_DLLFNCEXPORT OV_RESULT sosx_informationModelManagement_updateAlternative(
		OV_INSTPTR_sosx_Alternative			pAlternativeToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate
){
#define Finally()

	Finally();
	return OV_ERR_NOTIMPLEMENTED;
}

#endif
