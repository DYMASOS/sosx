#ifndef SOSXCOMMON_H_INCLUDED
#define SOSXCOMMON_H_INCLUDED

#include "sosx.h"
#include "sosx.ovt"
#include "caex.h"
#include "libov/ov_path.h"
#include "libov/ov_result.h"
#include "libov/ov_macros.h"
#include "libov/ov_logfile.h"
#include "libov/ov_path.h"


/***********************************************************************
	LOGFILE - Defines
***********************************************************************/
#define log_info(log_msg) ov_logfile_info("%s %d: %s", __FILE__, __LINE__, log_msg)
#define log_debug(log_msg) ov_logfile_debug("%s %d: %s", __FILE__, __LINE__, log_msg)
#define log_warning(log_msg) ov_logfile_warning("%s %d: %s", __FILE__, __LINE__, log_msg)
#define log_error(log_msg) ov_logfile_error("%s %d: %s", __FILE__, __LINE__, log_msg)

#define logfile_info(log_msg, log_name) ov_logfile_info("%s %d: %s - %s", __FILE__, __LINE__, log_msg ,log_name)
#define logfile_debug(log_msg, log_name) ov_logfile_debug("%s %d: %s - %s", __FILE__, __LINE__, log_msg ,log_name)
#define logfile_warning(log_msg, log_name) ov_logfile_warning("%s %d: %s - %s", __FILE__, __LINE__, log_msg ,log_name)
#define logfile_error(log_msg, log_name) ov_logfile_error("%s %d: %s - %s", __FILE__, __LINE__, log_msg ,log_name)

OV_UINT max_uint(OV_UINT a, OV_UINT b);

#define freeLibList(list,len) 		\
		if(list != NULL){			\
		Ov_HeapFree(list);			\
		len = 0;}					\

OV_RESULT createExportName(
		OV_STRING		sosxName,
		OV_STRING		*ExportName,
		OV_TIME			*time
);


/*********************************************************
 *free Descriptions
 *********************************************************/
void freeSoSContainerDescription(SOSX_SoSContainerDescription* Description);
void freeSystemDescription(SOSX_SystemDescription* Description);
void freeProcessDescription(SOSX_ProcessDescription* Description);
void freePortDescription(SOSX_PortDescription* Description);
void freeSourceSinkDescription(SOSX_SourceSinkDescription* Description);
void freeDistributionNodeDescription(SOSX_DistributionNodeDescription* Description);
void freePropertyDescription(SOSX_PropertyDescription* Description);
void freePropertyInformationDescription(SOSX_PropertyInformationDescription* Description);
void freeStreamDescription(SOSX_StreamDescription* Description);

/*********************************************************************************************
 * Macros for create
 ********************************************************************************************/
#define SetVarOfSosxDomain(result,pobj,Spec)																\
		/* set caexLibrary */																				\
		result = sosx_sosxdomain_setCaexLibrary(Ov_DynamicPtrCast(sosx_sosxdomain,pobj),					\
				Ov_DynamicPtrCast(caex_CAEXBasicObject,Spec->pSource),Spec->CaexLib);						\
				if(Ov_Fail(result)){																		\
					logfile_error("Could not store the caex library attribute", pobj->v_identifier);		\
					Finally();																				\
					return result;																			\
				}																							\
				/* set xPos */																				\
		result = sosx_sosxdomain_yPos_set(Ov_DynamicPtrCast(sosx_sosxdomain,pobj), Spec->yPos);				\
		if(Ov_Fail(result)){																				\
			logfile_error("Could not store the xPos attribute",pobj->v_identifier);							\
			Finally();																						\
			return result;																					\
		}																									\
		/* set yPos */																						\
		result = sosx_sosxdomain_xPos_set(Ov_DynamicPtrCast(sosx_sosxdomain,pobj), Spec->xPos);		 		\
		if(Ov_Fail(result)){																				\
			logfile_error("Could not store the yPos attribute",pobj->v_identifier);							\
			Finally();																						\
			return result;																					\
		}																									\

#define SetVarOfBaseElement(result,pobj,Spec)																	\
		/* set validFrom */																						\
		result = sosx_BaseElement_validFrom_set(Ov_DynamicPtrCast(sosx_BaseElement,pobj),&Spec->validFrom);		\
		if(Ov_Fail(result)){																					\
			logfile_error("Could not store the validFrom attribute",pobj->v_identifier);						\
			Finally();																							\
			return result;																						\
		}																										\
		/* set validUntil*/																						\
		result = sosx_BaseElement_validUntil_set(Ov_DynamicPtrCast(sosx_BaseElement,pobj),&Spec->validUntil);	\
		if(Ov_Fail(result)){																					\
			logfile_error("Could not store the validUntil attribute",pobj->v_identifier);						\
			Finally();																							\
			return result;																						\
		}																										\

#define SetVarOfDetailedElement(result,pobj,Spec)																\
		/* set name */																							\
		result = sosx_DetailedElement_name_set(Ov_DynamicPtrCast(sosx_DetailedElement,pobj),Spec->Name);		\
		if(Ov_Fail(result)){																					\
			logfile_error("Could not store the Name attribute",pobj->v_identifier);								\
			Finally();																							\
			return result;																						\
		}																										\

#define SetVarOfStructureElement(result,pobj,Spec)																\
		/* set externalInfo */																					\
		result = sosx_StructureElement_externalInfo_set(Ov_DynamicPtrCast(sosx_StructureElement,pobj),			\
				Spec->externalInfo.value,Spec->externalInfo.veclen);											\
				if(Ov_Fail(result)){																			\
					logfile_error("Could not store the externalInfo attribute",pobj->v_identifier);				\
					Finally();																					\
					return result;																				\
				}																								\
				/* set width */																					\
		result = sosx_StructureElement_width_set(Ov_DynamicPtrCast(sosx_StructureElement,pobj),Spec->Width);	\
		if(Ov_Fail(result)){																					\
			logfile_error("Could not store the width attribute",pobj->v_identifier);							\
			Finally();																							\
			return result;																						\
		}																										\
		/* set height */																						\
		result = sosx_StructureElement_height_set(Ov_DynamicPtrCast(sosx_StructureElement,pobj),Spec->Height);	\
		if(Ov_Fail(result)){																					\
			logfile_error("Could not store the height attribute",pobj->v_identifier);							\
			Finally();																							\
			return result;																						\
		}																										\


#define getPos(pObjDes,pBufA,pBufVal,ObjDes)		 									\
		pBufA = Ov_SearchChildEx(ov_containment,pObjDes,"xPos",caex_Attribute);			\
		if (pBufA != NULL){																\
			Ov_ForEachChildEx(ov_containment,pBufA,pBufVal,caex_Value){					\
			ObjDes.xPos = strtol(pBufVal->v_Value,NULL,0);								\
		} 																				\
		} 																				\
		pBufA = Ov_SearchChildEx(ov_containment,pObjDes,"yPos",caex_Attribute);			\
		if (pBufA != NULL){																\
			Ov_ForEachChildEx(ov_containment,pBufA,pBufVal,caex_Value){					\
			ObjDes.yPos = strtol(pBufVal->v_Value,NULL,0);								\
		}																				\
		} 																				\

#define getHeightAndWidth(pObjDes,pBufA,pBufVal,ObjDes)		 							\
		pBufA = Ov_SearchChildEx(ov_containment,pObjDes,"Height",caex_Attribute);		\
		if (pBufA != NULL){																\
			Ov_ForEachChildEx(ov_containment,pBufA,pBufVal,caex_Value){					\
			ObjDes.Height = strtol(pBufVal->v_Value,NULL,0);							\
		} 																				\
		} 																				\
		pBufA = Ov_SearchChildEx(ov_containment,pObjDes,"Width",caex_Attribute);		\
		if (pBufA != NULL){																\
			Ov_ForEachChildEx(ov_containment,pBufA,pBufVal,caex_Value){					\
			ObjDes.Width = strtol(pBufVal->v_Value,NULL,0);								\
		}																				\
		} 																				\

#define getLifeCycle(pObjDes,pBufA,pBufVal,ObjDes)		 								\
		pBufA = Ov_SearchChildEx(ov_containment,pObjDes,"validFrom",caex_Attribute);	\
		if (pBufA != NULL){																\
			Ov_ForEachChildEx(ov_containment,pBufA,pBufVal,caex_Value){					\
			if (ov_string_compare(pBufA->v_Name, "")!=OV_STRCMP_EQUAL){					\
				ov_time_asciitotime(&(ObjDes.validFrom), pBufVal->v_Value);				\
			} 																			\
		} 																				\
		} 																				\
		pBufA = Ov_SearchChildEx(ov_containment,pObjDes,"validUntil",caex_Attribute);	\
		if (pBufA != NULL){																\
			Ov_ForEachChildEx(ov_containment,pBufA,pBufVal,caex_Value){					\
			if (ov_string_compare(pBufA->v_Name, "")!=OV_STRCMP_EQUAL){					\
				ov_time_asciitotime(&(ObjDes.validUntil), pBufVal->v_Value);			\
			}																			\
		}																				\
		} 																				\

/*********************************************************************************************
 * Macros for read
 ********************************************************************************************/

#define Sosx_CreateSystemUnit(pTarget,pIE,Id,RefBasePath)							\
		/* check if InternalElement already exist */								\
		pIE = Ov_SearchChildEx(ov_containment,pTarget,Id,caex_InternalElement);		\
		if(pIE == NULL){ 															\
			/* create internal element */											\
		result = Ov_CreateObject(caex_InternalElement,pIE,pTarget,Id);				\
		if (Ov_Fail(result)){														\
			logfile_error("Could not create the CAEX-InternalElement for ",Id);		\
			Finally();																\
			return result;															\
		}																			\
		}																			\
		/* set standard attributes of the internal element */						\
		ov_string_setvalue(&pIE->v_Name,Id);										\
		/* set v_RefBaseSystemUnitPath */											\
		ov_string_setvalue(&pIE->v_RefBaseSystemUnitPath,RefBasePath);				\


#define Sosx_CreateAttributeAndValue(pA,pV,pIE,Name,Value,dataType)			\
		/* create validFrom and validUntil attributes and values*/			\
		/* create Attribute */												\
		if(Value != NULL){													\
		result = Ov_CreateObject(caex_Attribute,pA,pIE,Name);				\
		if(Ov_Fail(result)){												\
			logfile_error("Could not create a CAEX-Attribute for ",Name);	\
			Finally();														\
			return result;													\
		}																	\
		/* set name of attribute */											\
		ov_string_setvalue(&pA->v_Name,Name);								\
		/* create value */													\
			result = Ov_CreateObject(caex_Value,pV,pA,"Value");				\
			if(Ov_Fail(result)){											\
				logfile_error("Could create the CAEX-Value for ",Name);		\
				Finally();													\
				return result;												\
			}																\
			/* set value vartype to string and store the value */			\
		ov_string_setvalue(&pV->v_Value,Value);								\
		ov_string_setvalue(&pA->v_AttributeDataType,dataType);				\
		}																	\


#define Sosx_CreateRole(pTarget,pIE,Id,pRoleReq,RefBasePath)									\
		/* create internal element */															\
		result = Ov_CreateObject(caex_InternalElement,pIE,pTarget,Id);							\
		if(Ov_Fail(result)){																	\
			logfile_error("Could not create the CAEX-InternalElement for: ",Id);				\
			Finally();																			\
			return result;																		\
		}																						\
		/* set standard attributes of the internal element */									\
		ov_string_setvalue(&pIE->v_Name,Id);													\
		/* create roleRequirement */															\
		result = Ov_CreateObject(caex_RoleRequirements,pRoleReq,pIE,"RoleRequirements");		\
		if(Ov_Fail(result)){																	\
			logfile_error("Could not create the CAEX-RoleRequirement for: ",Id);				\
			Finally();																			\
			return result;																		\
		}																						\
		/* set  RefBaseRoleClassPath */															\
		ov_string_setvalue(&pRoleReq->v_RefBaseRoleClassPath,RefBasePath);						\


OV_RESULT createCAEXHeader(
		OV_INSTPTR_ov_domain			pSosxObj,
		OV_INSTPTR_ov_domain			pTargetContainer,
		OV_STRING						HeaderName,
		OV_BOOL							readStateOnly
);

OV_RESULT extendValidationLog(
		OV_STRING_VEC 						*log,
		OV_STRING 							Type,
		OV_STRING 							Msg,
		OV_INSTPTR_sosx_sosxdomain			pobj
);

OV_BOOL checkPropertyInfoType(
		OV_INSTPTR_caex_CAEXObject     	pCaexObj,
		OV_STRING						propInfoType
);

OV_RESULT updateChildren(
		OV_INSTPTR_caex_CAEXObject		pCaexElement,
		OV_INSTPTR_ov_domain			pSosxElement,
		SOSX_UPDATE_TYPE				updateType
);

OV_RESULT findLibrary(
		OV_STRING 						*pRefPath,
		OV_INSTPTR_ov_domain			pSearchIn,
		OV_INSTPTR_ov_domain			*pCaexLibrary
);

OV_RESULT createLinks(
		OV_STRING_VEC					*isLinkedTo,
		OV_INSTPTR_sosx_BaseElement		pTarget
);

OV_RESULT findInternalLinks(
		OV_INSTPTR_caex_CAEXObject			pInternalElement,
		OV_STRING_VEC						*isLinkedTo

);

OV_RESULT sosx_checkLink(
		OV_INSTPTR_sosx_StreamHandler			pStreamHandlerA,
		OV_INSTPTR_sosx_StreamHandler			pStreamHandlerB,
		OV_STRING_VEC							*pValidationLog
);

OV_RESULT validateLinks(
		OV_INSTPTR_sosx_StreamHandler			pStreamHandlerA,
		OV_STRING_VEC							*pValidationLog
);

OV_RESULT readLinks(
		OV_STRING_VEC						*isLinkedTo,
		OV_INSTPTR_sosx_BaseElement 		pToBeRead
);

OV_RESULT  exportLinks(
		OV_STRING_VEC						*isLinkedTo,
		OV_INSTPTR_sosx_BaseElement			pToBeRead,
		OV_INSTPTR_caex_InternalElement		pInternalElement
);

OV_VAR_TYPE stringToDatatype(
		OV_STRING		datatype
);

#endif
