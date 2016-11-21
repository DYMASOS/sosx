#ifndef INFORMATIONMODELMANAGEMENT_H
#define INFORMATIONMODELMANAGEMENT_H


#include "sosx.h"
#include "libov/ov_macros.h"
#include "caex.h"
#include "sosxcommon.h"
#include "libov/ov_path.h"
#include "libov/ov_result.h"

/*****************************************************************************
 * D E L E T E
 ****************************************************************************/
OV_RESULT sosx_informationModelManagement_deleteSoSContainer(
		OV_INSTPTR_sosx_SoSContainer				pSoSContainerToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deleteSystem(
		OV_INSTPTR_sosx_System				pSystemToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deleteProcess(
		OV_INSTPTR_sosx_Process				pProcessToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deleteStream(
		OV_INSTPTR_sosx_Stream				pStreamToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deletePort(
		OV_INSTPTR_sosx_Port				pPortToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deleteSourceSink(
		OV_INSTPTR_sosx_SourceSink			pSourceSinkToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deleteDistributionNode(
		OV_INSTPTR_sosx_DistributionNode	pDistributionNodeToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deletePropertyInformation(
		OV_INSTPTR_sosx_PropertyInformation			pPropertyInformationToBeDeleted
);
OV_RESULT sosx_informationModelManagement_deleteProperty(
		OV_INSTPTR_sosx_Property			pPropertyToBeDeleted
);

/*****************************************************************************
 * V A L I D A T E
 ****************************************************************************/

OV_RESULT sosx_informationModelManagement_validateBaseElement(
		OV_INSTPTR_sosx_BaseElement			pTargetElement,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validatePropertyInformation(
		OV_INSTPTR_sosx_PropertyInformation	pTargetPropertyInformation,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validateProperty(
		OV_INSTPTR_sosx_Property 			pTargetProperty,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validateSoSContainer(
		OV_INSTPTR_sosx_SoSContainer		pTargetSoSContainer,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validateSystem(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validateProcess(
		OV_INSTPTR_sosx_Process				pTargetProcess,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validatePort(
		OV_INSTPTR_sosx_Port				pTargetPort,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validateSourceSink(
		OV_INSTPTR_sosx_SourceSink			pTargetSourceSink,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validateDistributionNode(
		OV_INSTPTR_sosx_DistributionNode	pTargetDistributionNode,
		OV_STRING_VEC						*pValidationLog
);

OV_RESULT sosx_informationModelManagement_validateStream(
		OV_INSTPTR_sosx_Stream				pTargetStream,
		OV_STRING_VEC						*pValidationLog
);

#endif
