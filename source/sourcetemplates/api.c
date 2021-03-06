
/******************************************************************************
*
*   FILE
*   ----
*   api.c
*
*   History
*   -------
*   2016-08-10   File created
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


OV_DLLFNCEXPORT OV_RESULT sosx_api_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_sosx_api pinst = Ov_StaticPtrCast(sosx_api, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = ov_object_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_importCaexFile(
		OV_INSTPTR_sosx_api					pobj,
		OV_STRING							DirPath,
		OV_STRING_VEC 						FileList
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_exportCaexFile(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_STRING							DirPath,
		OV_STRING							Name	
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_exportCaexCyclic(
		OV_INSTPTR_sosx_api					pobj,
		OV_STRING							ElementToBeRead,
		OV_STRING							FilePath,
		OV_TIME_SPAN						cyctime
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_executeSimulationCyclic(
		OV_INSTPTR_sosx_api					pobj,
		OV_STRING							pathToSimFolder,
		OV_TIME_SPAN						cycTimeSec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_getLibraryList(
		OV_INSTPTR_caex_CAEXBasicObject		pInternalElement,
		OV_INSTPTR_caex_CAEXObject			**pLibList,
		OV_UINT								*LenLibList
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createElement(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_ov_domain				pTargetSys,
		OV_INSTPTR_caex_CAEXBasicObject		pElement
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_updateElement(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_ov_domain				pElementToBeUpdated,
		OV_INSTPTR_caex_CAEXBasicObject		pUpdate
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readElement(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_ov_domain				pElementToBeRead,
		OV_INSTPTR_ov_domain				pTarget,
		OV_BOOL								writeHeader,
		OV_STRING							HeaderName
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_deleteElement(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_ov_domain				pElementToBeDeleted
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_validateElement(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_STRING_VEC						*pValidationLog
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimpleSoSContainer(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_SoSContainerDescription		*SoSContainerSpec,
		OV_INSTPTR_sosx_SoSContainer 		*ppCreatedSoSContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimpleSoSContainerUpdate(
		SOSX_SoSContainerDescription	*SoSContainerSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readSoSContainer(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_SoSContainer		pSoSContainerToBeRead,
		OV_INSTPTR_ov_domain				pTragetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimpleSystem(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_SystemDescription				*SystemSpec,
		OV_INSTPTR_sosx_System 				*ppCreatedSystem
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimpleSystemUpdate(
		SOSX_SystemDescription	*SystemSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readSystem(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_System				pSystemToBeRead,
		OV_INSTPTR_ov_domain				pTargetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimpleProcess(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_ProcessDescription				*ProcessSpec,
		OV_INSTPTR_sosx_Process 			*ppCreatedProcess
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimpleProcessUpdate(
		SOSX_ProcessDescription	*ProcessSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readProcess(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_Process				pProcessToBeRead,
		OV_INSTPTR_ov_domain				pTargetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimplePort(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_PortDescription				*PortSpec,
		OV_INSTPTR_sosx_Port				*ppCreatedPort
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimplePortUpdate(
		SOSX_PortDescription	*PortSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readPort(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_Port				pPortToBeRead,
		OV_INSTPTR_ov_domain				pTragetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimpleSourceSink(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_SourceSinkDescription			*SourceSinkSpec,
		OV_INSTPTR_sosx_SourceSink			*ppCreatedSourceSink
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimpleSourceSinkUpdate(
		SOSX_SourceSinkDescription	*SourceSinkSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readSourceSink(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_SourceSink			pSourceSinkToBeRead,
		OV_INSTPTR_ov_domain				pTragetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimpleDistributionNode(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_DistributionNodeDescription	*DistributionNodeSpec,
		OV_INSTPTR_sosx_DistributionNode	*ppCreatedDistributionNode
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimpleDistributionNodeUpdate(
		SOSX_DistributionNodeDescription	*DistributionNodeSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readDistributionNode(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_DistributionNode	pDistributionNodeToBeRead,
		OV_INSTPTR_ov_domain				pTragetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimpleProperty(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_PropertyDescription			*PropertySpec,
		OV_INSTPTR_sosx_Property			*ppCreatedProperty
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimplePropertyUpdate(
		SOSX_PropertyDescription	*PropertySpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readProperty(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_Property			pPropertyToBeRead,
		OV_INSTPTR_ov_domain				pTragetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimplePropertyInformation(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_PropertyInformationDescription	*PropertyInformationSpec,
		OV_INSTPTR_sosx_PropertyInformation	*ppCreatedPropertyInformation
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimplePropertyInformationUpdate(
		SOSX_PropertyInformationDescription	*PropertyInformationUpdateSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readPropertyInformation(
		OV_INSTPTR_sosx_api							pobj,
		OV_INSTPTR_sosx_PropertyInformation			pPropertyInformationToBeRead,
		OV_INSTPTR_ov_domain						pTragetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createSimpleStream(
		OV_INSTPTR_sosx_api					pobj,
		SOSX_StreamDescription				*StreamSpec,
		OV_INSTPTR_sosx_Stream				*ppCreatedStream
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_SimpleStreamUpdate(
		SOSX_StreamDescription	*StreamSpec
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readStream(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_Stream				pStreamToBeRead,
		OV_INSTPTR_ov_domain				pTragetContainer
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_createAlternative(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_System				pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT sosx_api_readAlternative(
		OV_INSTPTR_sosx_api					pobj,
		OV_INSTPTR_sosx_Alternative			pAlternativeToBeRead,
		OV_INSTPTR_ov_domain				pTragetContainer
) {

    return OV_ERR_OK;
}

