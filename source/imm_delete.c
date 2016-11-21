/******************************************************************************
 *
 *   FILE
 *   ----
 *   delete.c
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



/* This macro changes the object identifier to [oldIndetifier]_Now */
#define setIdentifier(obj,Now,tmpStr) 																\
		result = ov_string_setvalue(&tmpStr,obj->v_identifier);										\
		if (Ov_Fail(result)){																		\
			Finally();																				\
			return result;																			\
		}																							\
		result = ov_string_append(&tmpStr,"_");														\
		if (Ov_Fail(result)){																		\
			Finally();																				\
			return result;																			\
		}																							\
		result = ov_string_append(&tmpStr,ov_time_timetoascii_local(&Now));							\
		if (Ov_Fail(result)){																		\
			Finally();																				\
			return result;																			\
		}																							\
		result = ov_object_rename(Ov_DynamicPtrCast(ov_object,obj),									\
				tmpStr,																				\
				Ov_DynamicPtrCast(ov_domain,Ov_GetParent(ov_containment,obj)));						\
				if (Ov_Fail(result)) {																\
					Finally();																		\
					return result;																	\
				}																					\
				if (ov_string_compare(tmpStr,obj->v_identifier) == OV_STRCMP_EQUAL) {				\
					logfile_warning("Failed to adapted the identifier of ",obj->v_identifier);		\
				}																					\

/** SoSContainer
 * This function deletes all children of a SoSContainer. Nothing happens to the SoSContainer itself
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the SoSContainer that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deleteSoSContainer(
		OV_INSTPTR_sosx_SoSContainer				pSoSContainerToBeDeleted
){
	OV_RESULT								result	= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 	= NULL;

#undef Finally
#define Finally()

	if (pSoSContainerToBeDeleted == NULL){
		log_error("SoSContainer to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* Delete all children of the SoSContainer */
	Ov_ForEachChildEx(ov_containment,pSoSContainerToBeDeleted,pTemp,ov_domain){
		result = sosx_workflowManagement_deleteElement(Ov_DynamicPtrCast(ov_domain,pTemp));
		if (Ov_Fail(result)){
			logfile_error("Could not delete all children of ", pSoSContainerToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	Finally();
	return result;
}

/** System
 * This function sets the validUntil Attribute of the System to now and deletes all children of a System.
 * The identifier of the System is change to [oldIdentifier]_Now.
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the System that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deleteSystem(
		OV_INSTPTR_sosx_System				pSystemToBeDeleted
){
	OV_RESULT								result	= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 	= NULL;
	OV_TIME									Now		= {0,0};
	OV_STRING								tmpStr	= NULL;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&tmpStr,NULL);	\

	if (pSystemToBeDeleted == NULL){
		log_error("System to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get Now */
	ov_time_gettime(&Now);

	/* set validUntil to now */
	result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pSystemToBeDeleted),&Now);
	if(Ov_Fail(result)){
		logfile_error("Could not delete the system",pSystemToBeDeleted->v_name);
		Finally();
		return result;
	}

	/* append Now to object identifier */
	// setIdentifier(pSystemToBeDeleted,Now,tmpStr);

	/*get identifier*/
	result = ov_string_setvalue(&tmpStr,pSystemToBeDeleted->v_identifier);
	if (Ov_Fail(result)){
		Finally();
		return result;
	}
	/* append _ */
	result = ov_string_append(&tmpStr,"_");
	if (Ov_Fail(result)){
		Finally();
		return result;
	}
	/* append now */
	result = ov_string_append(&tmpStr,ov_time_timetoascii_local(&Now));
	if (Ov_Fail(result)){
		Finally();
		return result;
	}
	/*replace '/' with '-' */

	for(OV_UINT i = 0 ; i < strlen(tmpStr) ; i++){
		if(tmpStr[i] == '/'){
			tmpStr[i] = '-';
		}

		if(tmpStr[i] == '.'){
			tmpStr[i] = '\0';
			break;
		}

		if(tmpStr[i] == ':'){
			tmpStr[i] = '-';
		}

		if(tmpStr[i] == ' '){
			tmpStr[i] = '_';
		}
	}

	/* rename object */
	result = ov_class_renameobject(Ov_DynamicPtrCast(ov_object,pSystemToBeDeleted),Ov_DynamicPtrCast(ov_domain,Ov_GetParent(ov_containment,pSystemToBeDeleted)),tmpStr,OV_PMH_DEFAULT,NULL);
	if (Ov_Fail(result)) {
		Finally();
		return result;
	}

	if (ov_string_compare(tmpStr,pSystemToBeDeleted->v_identifier) != OV_STRCMP_EQUAL) {
		logfile_warning("Failed to adapted the identifier of ",pSystemToBeDeleted->v_identifier);
		Finally();
		return result;
	}

	/* Delete all children of the system */
	Ov_ForEachChildEx(ov_containment,pSystemToBeDeleted,pTemp,ov_domain){
		result = sosx_workflowManagement_deleteElement(Ov_DynamicPtrCast(ov_domain,pTemp));
		if (Ov_Fail(result)){
			logfile_error("Could not delete all children of ", pSystemToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	Finally();
	return result;
}

/** Process
 * This function sets the validUntil Attribute of the Process to now and deletes all children of a Process.
 * The identifier of the Process is change to [oldIdentifier]_Now.
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the Process that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deleteProcess(
		OV_INSTPTR_sosx_Process				pProcessToBeDeleted
){
	OV_RESULT								result	= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 	= NULL;
	OV_TIME									Now		= {0,0};
	OV_STRING								tmpStr	= NULL;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&tmpStr,NULL);	\

	if (pProcessToBeDeleted == NULL){
		log_error("Process to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get Now */
	ov_time_gettime(&Now);

	/* set validUntil to now */
	result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pProcessToBeDeleted),&Now);
	if(Ov_Fail(result)){
		logfile_error("Could not delete the Process",pProcessToBeDeleted->v_name);
		Finally();
		return result;
	}

	/* append Now to object identifier */
	setIdentifier(pProcessToBeDeleted,Now,tmpStr);

	/* Delete all children of the process */
	Ov_ForEachChildEx(ov_containment,pProcessToBeDeleted,pTemp,ov_domain){
		result = sosx_workflowManagement_deleteElement(Ov_DynamicPtrCast(ov_domain,pTemp));
		if (Ov_Fail(result)){
			logfile_error("Could not delete all children of ", pProcessToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	Finally();
	return result;
}

/** Stream
 * This function sets the validUntil Attribute of the Stream.
 * If the Stream is within an valid System the Stream will be unlinked and destroyed
 * otherwise the identifier of the Stream is change to [oldIdentifier]_Now.
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the Stream that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deleteStream(
		OV_INSTPTR_sosx_Stream				pStreamToBeDeleted
) {
	OV_RESULT								result			= OV_ERR_OK;
	OV_TIME									Now				= {0,0};
	OV_INSTPTR_sosx_StreamHandler			pStreamHandlerA	= NULL;
	OV_INSTPTR_sosx_StreamHandler			pStreamHandlerB	= NULL;
	OV_INSTPTR_ov_domain					pStreamParent 	= NULL;
	OV_STRING								tmpStr			= NULL;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&tmpStr,NULL);	\

	if (pStreamToBeDeleted == NULL){
		log_error("Stream to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get Now */
	ov_time_gettime(&Now);
	/* set validUntil to now */
	result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pStreamToBeDeleted),&Now);
	if(Ov_Fail(result)){
		logfile_error("Could not delete the Stream",pStreamToBeDeleted->v_identifier);
		Finally();
		return result;
	}

	/* append Now to object identifier */
	setIdentifier(pStreamToBeDeleted,Now,tmpStr);

	/* unlink and delete stream if it is within a valid system */
	pStreamParent = Ov_GetParent(ov_containment,pStreamToBeDeleted);
	/* check if parent is valid */
	if(Ov_CanCastTo(sosx_SoSContainer,pStreamParent) ||
			ov_time_compare(&(Ov_DynamicPtrCast(sosx_BaseElement,pStreamParent)->v_validUntil),&Now) == OV_TIMECMP_AFTER){
		/* parent is valid -> destroy stream object*/
		/* get both sides of the stream */
		pStreamHandlerA = Ov_GetParent(sosx_isLinkedToSideA,pStreamToBeDeleted);
		pStreamHandlerB = Ov_GetParent(sosx_isLinkedToSideB,pStreamToBeDeleted);

		if(pStreamHandlerB != NULL && pStreamHandlerA != pStreamHandlerB){
			/* change wasConnectedTo in both StreamHandler*/
			ov_string_setvalue(&pStreamHandlerA->v_wasConnectedTo,pStreamHandlerB->v_name);
			ov_string_setvalue(&pStreamHandlerB->v_wasConnectedTo,pStreamHandlerA->v_name);
		}

		/* unlink stream */
		if(pStreamHandlerA){
			Ov_Unlink(sosx_isLinkedToSideA, pStreamHandlerA, pStreamToBeDeleted);
		}
		if(pStreamHandlerB){
			Ov_Unlink(sosx_isLinkedToSideB, pStreamHandlerB, pStreamToBeDeleted);
		}
		/* delete stream */
		Ov_DeleteObject(pStreamToBeDeleted);
	}
	Finally();
	return result;
}
/** Port
 * This function sets the validUntil Attribute of the Port to now and deletes all children and links of the Port.
 * The identifier of the Port is change to [oldIdentifier]_Now.
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the Port that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deletePort(
		OV_INSTPTR_sosx_Port				pPortToBeDeleted
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 			= NULL;
	OV_TIME									Now				= {0,0};
	OV_INSTPTR_sosx_Stream					pStream			= NULL;
	OV_STRING								tmpStr			= NULL;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&tmpStr,NULL);	\

	if (pPortToBeDeleted == NULL){
		log_error("Port to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get Now */
	ov_time_gettime(&Now);
	/* set validUntil to now */
	result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pPortToBeDeleted),&Now);
	if(Ov_Fail(result)){
		logfile_error("Could not delete the Port",pPortToBeDeleted->v_name);
		Finally();
		return result;
	}

	/* append Now to object identifier */
	setIdentifier(pPortToBeDeleted,Now,tmpStr);

	/* Delete all children of the port */
	Ov_ForEachChildEx(ov_containment,pPortToBeDeleted,pTemp,ov_domain){
		result = sosx_workflowManagement_deleteElement(Ov_DynamicPtrCast(ov_domain,pTemp));
		if (Ov_Fail(result)){
			logfile_error("Could not delete all children of ", pPortToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	/* Handle links */
	Ov_ForEachChildEx(sosx_isLinkedToSideA,pPortToBeDeleted,pStream,sosx_Stream){
		result = sosx_informationModelManagement_deleteStream(pStream);
		if(Ov_Fail(result)){
			logfile_error("Could not handle all links of ", pPortToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	Ov_ForEachChildEx(sosx_isLinkedToSideB,pPortToBeDeleted,pStream,sosx_Stream){
		result = sosx_informationModelManagement_deleteStream(pStream);
		if(Ov_Fail(result)){
			logfile_error("Could not handle all links of ", pPortToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	Finally();
	return result;
}
/** SourceSink
 * This function sets the validUntil Attribute of the SourceSink to now and deletes all children and links of the SourceSink.
 * The identifier of the SourceSink is change to [oldIdentifier]_Now.
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the SourceSink that shall be deleted
 * @return OV_RESULT error level
 */

OV_RESULT sosx_informationModelManagement_deleteSourceSink(
		OV_INSTPTR_sosx_SourceSink			pSourceSinkToBeDeleted
){
	OV_RESULT								result		= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 		= NULL;
	OV_TIME									Now			= {0,0};
	OV_INSTPTR_sosx_Stream					pStream		= NULL;
	OV_STRING								tmpStr		= NULL;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&tmpStr,NULL);	\

	if (pSourceSinkToBeDeleted == NULL){
		log_error("SourceSink to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get Now */
	ov_time_gettime(&Now);
	/* set validUntil to now */
	result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pSourceSinkToBeDeleted),&Now);
	if(Ov_Fail(result)){
		logfile_error("Could not delete the SourceSink",pSourceSinkToBeDeleted->v_name);
		Finally();
		return result;
	}

	/* append Now to object identifier */
	setIdentifier(pSourceSinkToBeDeleted,Now,tmpStr);

	/* Delete all children of the SourceSink */
	Ov_ForEachChildEx(ov_containment,pSourceSinkToBeDeleted,pTemp,ov_domain){
		result = sosx_workflowManagement_deleteElement(Ov_DynamicPtrCast(ov_domain,pTemp));
		if (Ov_Fail(result)){
			logfile_error("Could not delete all children of ", pSourceSinkToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	/* Handle links */
	Ov_ForEachChildEx(sosx_isLinkedToSideA,pSourceSinkToBeDeleted,pStream,sosx_Stream){
		result = sosx_informationModelManagement_deleteStream(pStream);
		if(Ov_Fail(result)){
			logfile_error("Could not handle all links of ", pSourceSinkToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}
	Ov_ForEachChildEx(sosx_isLinkedToSideB,pSourceSinkToBeDeleted,pStream,sosx_Stream){
		result = sosx_informationModelManagement_deleteStream(pStream);
		if(Ov_Fail(result)){
			logfile_error("Could not handle all links of ", pSourceSinkToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}
	Finally();
	return result;
}

/** DistributionNode
 * This function sets the validUntil Attribute of the DistributionNode to now and deletes all children and links of the DistributionNode.
 * The identifier of the DistributionNode is change to [oldIdentifier]_Now.
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the DistributionNode that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deleteDistributionNode(
		OV_INSTPTR_sosx_DistributionNode	pDistributionNodeToBeDeleted
){
	OV_RESULT								result		= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 		= NULL;
	OV_TIME									Now			= {0,0};
	OV_INSTPTR_sosx_Stream					pStream		= NULL;
	OV_STRING								tmpStr		= NULL;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&tmpStr,NULL);	\

	if (pDistributionNodeToBeDeleted == NULL){
		log_error("DistributionNode to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get Now */
	ov_time_gettime(&Now);
	/* set validUntil to now */
	result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pDistributionNodeToBeDeleted),&Now);
	if(Ov_Fail(result)){
		logfile_error("Could not delete the DistributionNode",pDistributionNodeToBeDeleted->v_name);
		Finally();
		return result;
	}
	/* append Now to object identifier */
	setIdentifier(pDistributionNodeToBeDeleted,Now,tmpStr);

	/* Delete all children of the DistributionNode */
	Ov_ForEachChildEx(ov_containment,pDistributionNodeToBeDeleted,pTemp,ov_domain){
		result = sosx_workflowManagement_deleteElement(Ov_DynamicPtrCast(ov_domain,pTemp));
		if (Ov_Fail(result)){
			logfile_error("Could not delete all children of ", pDistributionNodeToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	/* Handle links */
	Ov_ForEachChildEx(sosx_isLinkedToSideA,pDistributionNodeToBeDeleted,pStream,sosx_Stream){
		result = sosx_informationModelManagement_deleteStream(pStream);
		if(Ov_Fail(result)){
			logfile_error("Could not handle all links of ", pDistributionNodeToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}
	Ov_ForEachChildEx(sosx_isLinkedToSideB,pDistributionNodeToBeDeleted,pStream,sosx_Stream){
		result = sosx_informationModelManagement_deleteStream(pStream);
		if(Ov_Fail(result)){
			logfile_error("Could not handle all links of ", pDistributionNodeToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}
	Finally();
	return result;
}
/** PropertyInformation
 * This function sets the validUntil Attribute of the PropertyInformation to now and deletes all children of the PropertyInformation.
 * The identifier of the PropertyInformation is change to [oldIdentifier]_Now.
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the PropertyInformation that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deletePropertyInformation(
		OV_INSTPTR_sosx_PropertyInformation			pPropertyInformationToBeDeleted
){
	OV_RESULT								result	= OV_ERR_OK;
	OV_TIME									Now		= {0,0};
	OV_STRING								tmpStr	= NULL;

#undef Finally
#define Finally()							\
		ov_string_setvalue(&tmpStr,NULL);	\

	if (pPropertyInformationToBeDeleted == NULL){
		log_error("PropertyInformation to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* get Now */
	ov_time_gettime(&Now);
	/* set validUntil to now */
	result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pPropertyInformationToBeDeleted),&Now);
	if(Ov_Fail(result)){
		logfile_error("Could not delete the PropertyInformation",pPropertyInformationToBeDeleted->v_identifier);
		Finally();
		return result;
	}

	/* Change last TimeStamp to now */
	pPropertyInformationToBeDeleted->v_timeStamps.value[pPropertyInformationToBeDeleted->v_index] = Now;

	/* destroy getVar child */
	result = Ov_DeleteObject(Ov_SearchChildEx(ov_containment,pPropertyInformationToBeDeleted,"getVar",sosx_getVar));
	if(Ov_Fail(result)){
		logfile_error("Could not delete the getVar object of ",pPropertyInformationToBeDeleted->v_identifier);
		Finally();
		return result;
	}

	/* append Now to object identifier */
	setIdentifier(pPropertyInformationToBeDeleted,Now,tmpStr);

	Finally();
	return result;
}

/** Property
 * This function deletes all children of the PropertyInformation. The Property itself stays unchanged
 * @param pobj - pointer to the api object that called the function
 * @param pSoSContainerToBeDeleted - pointer to the Property that shall be deleted
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_deleteProperty(
		OV_INSTPTR_sosx_Property			pPropertyToBeDeleted
){
	OV_RESULT								result	= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 	= NULL;

#undef Finally
#define Finally()

	if (pPropertyToBeDeleted == NULL){
		log_error("Property to be deleted not found!");
		result = OV_ERR_GENERIC;
		Finally();
		return result;
	}

	/* Delete all children of the property */
	Ov_ForEachChildEx(ov_containment,pPropertyToBeDeleted,pTemp,ov_domain){
		result = sosx_workflowManagement_deleteElement(Ov_DynamicPtrCast(ov_domain,pTemp));
		if (Ov_Fail(result)){
			logfile_error("Could not delete all children of ", pPropertyToBeDeleted->v_identifier);
			Finally();
			return result;
		}
	}

	Finally();
	return result;
}

OV_RESULT sosx_informationModelManagement_deleteAlternative(
		OV_INSTPTR_sosx_Alternative			pAlternativeToBeDeleted
){
#define Finally()

	Finally();
	return OV_ERR_NOTIMPLEMENTED;
}


#endif
