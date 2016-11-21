
#ifndef WORKFLOWMANAGEMENT_H
#define WORKFLOWMANAGEMENT_H

#include "sosx.h"
#include "libov/ov_macros.h"
#include "caex.h"
#include "sosxcommon.h"
#include "libov/ov_path.h"
#include "libov/ov_result.h"

/**************************************************************
 *  C R E A T E
 *************************************************************/

OV_RESULT sosx_workflowManagement_createSoSContainer(
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_INSTPTR_caex_CAEXFile			pCaexFile
);

OV_RESULT sosx_workflowManagement_createSystem(
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createProcess(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createPropertyInformation(
		OV_INSTPTR_sosx_Property			pTargetProperty,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createProperty(
		OV_INSTPTR_sosx_DetailedElement		pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createPort(
		OV_INSTPTR_sosx_DetailedElement		pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createSourceSink(
		OV_INSTPTR_sosx_SoSContainer		pTargetContainer,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createDistributionNode(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createStream(
		OV_INSTPTR_ov_domain				pTargetElement,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_RESULT sosx_workflowManagement_createAlternative(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

/**************************************************************
 *  U P D A T E
 *************************************************************/
OV_RESULT sosx_workflowManagement_updateSoSContainer(
		OV_INSTPTR_sosx_SoSContainer		pSoSContainerToBeUpdated,
		OV_INSTPTR_caex_CAEXFile			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);

OV_RESULT sosx_workflowManagement_updateSystem(
		OV_INSTPTR_sosx_System				pSystemToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);

OV_RESULT sosx_workflowManagement_updateProcess(
		OV_INSTPTR_sosx_Process				pProcessToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);

OV_RESULT sosx_workflowManagement_updatePort(
		OV_INSTPTR_sosx_Port				pPortToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);

OV_RESULT sosx_workflowManagement_updateSourceSink(
		OV_INSTPTR_sosx_SourceSink			pSourceSinkToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);

OV_RESULT sosx_workflowManagement_updateDistributionNode(
		OV_INSTPTR_sosx_DistributionNode	pDistributionNodeToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);

OV_RESULT sosx_workflowManagement_updateProperty(
		OV_INSTPTR_sosx_Property			pPropertyToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);

OV_RESULT sosx_workflowManagement_updatePropertyInformation(
		OV_INSTPTR_sosx_PropertyInformation		pPropertyInformationToBeUpdated,
		OV_INSTPTR_caex_CAEXObject				pUpdate,
		SOSX_UPDATE_TYPE						updateType
);

OV_RESULT sosx_workflowManagement_updateStream(
		OV_INSTPTR_sosx_Stream				pStreamToBeUpdated,
		OV_INSTPTR_caex_CAEXObject			pUpdate,
		SOSX_UPDATE_TYPE					updateType
);


#endif
