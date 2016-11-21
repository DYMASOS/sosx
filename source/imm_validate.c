/******************************************************************************
 *
 *   FILE
 *   ----
 *   validate.c
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
 * BaseElement - This function is used to validate the attributes validFrom, validUntil and caexLibrary of all Elements
 *  except Property (i.e. is not an BaseElement), PropertyInformation (i.e. is different than all other BaseElements) and Alternative (i.e. is not an BaseElement)
 * @param pTargetElement - Pointer to the BaseElement that shall be validated
 * @param pValidationLog - Pointer to the validation Log
 * @return OV_RESULT error level
 */
OV_RESULT sosx_informationModelManagement_validateBaseElement(
		OV_INSTPTR_sosx_BaseElement			pTargetElement,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	const OV_TIME							pDefaultTime	= {0,0};

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement),max_uint(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement)->v_isValid,SOSX_ISVALID_ISVALID));

	/* check caexLibrary */
	if(ov_string_compare(pTargetElement->v_caexLibrary,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","Attribute caexLibrary missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement));
	}

	/* warning if validFrom or validUntil is set to default value "1970-01-01 01:00:00.000000" */
	if(ov_time_compare(&pTargetElement->v_validFrom , &pDefaultTime) == OV_TIMECMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","validFrom is set to default value '1970-01-01 01:00:00.000000'",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement));
	}
	if(ov_time_compare(&pTargetElement->v_validUntil , &pDefaultTime) == OV_TIMECMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","validUntil is set to default value '1970-01-01 01:00:00.000000'",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement));
	}

	/* check if validFrom < validUntil */
	if(ov_time_compare(&pTargetElement->v_validFrom , &pTargetElement->v_validUntil) == OV_TIMECMP_BEFORE){
		/* everything okay */
	}else {
		extendValidationLog(pValidationLog,"Error","validFrom must be before validUntil",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement));
	}

	/* check if [validFrom, validUntil] <= [validFrom, validUntil] of the containment parent if parent is of class system */
	if(Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pTargetElement))){
		if(ov_time_compare(&(Ov_DynamicPtrCast(sosx_System,Ov_GetParent(ov_containment,pTargetElement)))->v_validFrom ,&pTargetElement->v_validFrom) != OV_TIMECMP_AFTER){
			/* everything okay */
		}else{
			extendValidationLog(pValidationLog,"Error","validFrom must be after or equal to validFrom of the parent system",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement));
		}

		if(ov_time_compare(&(Ov_DynamicPtrCast(sosx_System,Ov_GetParent(ov_containment,pTargetElement)))->v_validUntil , &pTargetElement->v_validUntil) != OV_TIMECMP_BEFORE){
			/* everything okay */
		}else{
			extendValidationLog(pValidationLog,"Error","validUntil must be before  or equal to validUntil of the parent system",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetElement));
		}
	}
	return result;
}

OV_RESULT sosx_informationModelManagement_validatePropertyInformation(
		OV_INSTPTR_sosx_PropertyInformation	pTargetPropertyInformation,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp			= NULL;
	OV_TIME									pDefaultTime	= {0,0};
	OV_INSTPTR_ov_domain					pParent			= NULL;
	OV_INSTPTR_sosx_PropertyInformation		pTempPropertyInformation = NULL;

#undef	Finally
#define Finally()

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation),SOSX_ISVALID_NOTCHECKED);

	if(pTargetPropertyInformation == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the PropertyInformation",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: Property*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetPropertyInformation);
	if(Ov_CanCastTo(sosx_Property,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of PropertyInformation is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}

	/* check source */
	if(ov_string_compare(pTargetPropertyInformation->v_source,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","source missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}
	/* check value */
	if(pTargetPropertyInformation->v_value.value.vartype == OV_VT_VOID){
		extendValidationLog(pValidationLog,"Warning","value missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}
	/* check type */
	if(ov_string_compare(pTargetPropertyInformation->v_type,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","type missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}
	/* check unit */
	if(ov_string_compare(pTargetPropertyInformation->v_unit,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","unit missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}

	/* check caexLibrary */
	if(ov_string_compare(pTargetPropertyInformation->v_caexLibrary,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","Attribute caexLibrary missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}

	/* warning if validFrom or validUntil is set to default value "1970-01-01 01:00:00.000000" */
	if(ov_time_compare(&pTargetPropertyInformation->v_validFrom , &pDefaultTime) == OV_TIMECMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","validFrom is set to default value '1970-01-01 01:00:00.000000'",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}
	if(ov_time_compare(&pTargetPropertyInformation->v_validUntil , &pDefaultTime) == OV_TIMECMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","validUntil is set to default value '1970-01-01 01:00:00.000000'",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}

	/* check if the combination of validFrom, validUntil, type and source of PropertyInformationToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetPropertyInformation);
	/* go through all sibling of PropertyInformation*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempPropertyInformation,sosx_PropertyInformation){
		/* ignore TargetPropertyInformation*/
		if(pTempPropertyInformation != pTargetPropertyInformation){
			/* check if another PropertyInformation has the same name as targetPropertyInformation */
			if((ov_time_compare(&pTargetPropertyInformation->v_validFrom, &pTempPropertyInformation->v_validFrom) == OV_TIMECMP_EQUAL) &&
					(ov_time_compare(&pTargetPropertyInformation->v_validUntil, &pTempPropertyInformation->v_validUntil) == OV_TIMECMP_EQUAL) &&
					(ov_string_compare(pTargetPropertyInformation->v_type, pTempPropertyInformation->v_type) == OV_STRCMP_EQUAL) &&
					(ov_string_compare(pTargetPropertyInformation->v_source, pTempPropertyInformation->v_source) == OV_STRCMP_EQUAL) &&
					(ov_string_compare(pTargetPropertyInformation->v_identifier, pTempPropertyInformation->v_identifier) == OV_STRCMP_EQUAL)){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
			}
		}
	}

	/* check PropertyInformation type */
	if(!((ov_string_compare(pTargetPropertyInformation->v_type,"manipulated variable") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"SimulationResult") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"shared resource stream") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"product stream") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"production target") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"production target pure") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"production target diluted") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"additional dependent input") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"environment temperature") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"shared resource price") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"internal state") == OV_STRCMP_EQUAL) ||
			(ov_string_compare(pTargetPropertyInformation->v_type,"-") == OV_STRCMP_EQUAL))){
		extendValidationLog(pValidationLog,"Warning","Unknown PropertyInformation type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}

	/* validate Children
	 * Allowed Children class: getKsVar
	 */
	Ov_ForEachChildEx(ov_containment,pTargetPropertyInformation,pTemp,ov_domain){
		if(Ov_CanCastTo(sosx_getKsVal,pTemp)){
			if(Ov_DynamicPtrCast(sosx_getKsVal,pTemp)->v_state > 2 ){
				extendValidationLog(pValidationLog,"Error","getKsVar not working",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
			}
		}else{
			extendValidationLog(pValidationLog,"Error","PropertyInformation should not have a Child",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
		}
	}

	/* check if validFrom < validUntil */
	if(ov_time_compare(&pTargetPropertyInformation->v_validFrom, &pTargetPropertyInformation->v_validUntil) == OV_TIMECMP_BEFORE){
		/* everything okay */
	}else {
		extendValidationLog(pValidationLog,"Error","PropertyInformation - validFrom must be before validUntil",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
	}

	/* check if [validFrom, validUntil] <= [validFrom, validUntil] of the containment parent-parent if parent is of class PropertyInformation */
	pParent = Ov_GetParent(ov_containment,pTargetPropertyInformation);
	pParent = Ov_GetParent(ov_containment,pParent);
	if(pParent != NULL && Ov_CanCastTo(sosx_BaseElement,pParent)){
		if(ov_time_compare(&(Ov_DynamicPtrCast(sosx_BaseElement,pParent))->v_validFrom ,&pTargetPropertyInformation->v_validFrom) != OV_TIMECMP_AFTER){
			/* everything okay */
		}else{

			extendValidationLog(pValidationLog,"Error","validFrom must be after or equal to validFrom of the parent PropertyInformation",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
		}
		if(ov_time_compare(&(Ov_DynamicPtrCast(sosx_BaseElement,pParent))->v_validUntil , &pTargetPropertyInformation->v_validUntil) != OV_TIMECMP_BEFORE){
			/* everything okay */
		}else{
			extendValidationLog(pValidationLog,"Error","validUntil must be before  or equal to validUntil of the parent PropertyInformation",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPropertyInformation));
		}
	}

	// TO DO: offer hook-function for validation of specific element

	Finally();
	return result;
}

OV_RESULT sosx_informationModelManagement_validateProperty(
		OV_INSTPTR_sosx_Property 			pTargetProperty,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp			= NULL;
	OV_INSTPTR_ov_domain					pParent			= NULL;
	OV_INSTPTR_sosx_Property				pTempProperty	= NULL;

#undef	Finally
#define Finally()

	if(pTargetProperty == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the Property",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProperty));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProperty),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: DetailedElement*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetProperty);
	if(Ov_CanCastTo(sosx_DetailedElement,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of Property is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProperty));
	}

	/* check name */
	/* warning if name = "" */
	if(ov_string_compare(pTargetProperty->v_name,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","name missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProperty));
	}

	/* check caexLibrary */
	if(ov_string_compare(pTargetProperty->v_caexLibrary,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","Attribute caexLibrary missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProperty));
	}

	/* check if name of PropertyToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetProperty);
	/* go through all sibling of Property*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempProperty,sosx_Property){
		/* ignore TargetProperty*/
		if(pTempProperty != pTargetProperty){
			/* check if another Property has the same name as targetProperty */
			if(ov_string_compare(pTargetProperty->v_name, pTempProperty->v_name) == OV_STRCMP_EQUAL){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProperty));
			}
		}
	}

	/* validate Children
	 * Allowed Children class: PropertyInformation
	 */
	Ov_ForEachChildEx(ov_containment,pTargetProperty,pTemp,ov_domain){
		if((Ov_CanCastTo(sosx_PropertyInformation,pTemp))){
			sosx_informationModelManagement_validatePropertyInformation(Ov_DynamicPtrCast(sosx_PropertyInformation,pTemp),pValidationLog);
		}else{
			extendValidationLog(pValidationLog,"Error","Property has a Child of not allowed type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProperty));
		}
	}

	// TO DO: offer hook-function for validation of specific element

	Finally();
	return result;
}

/*
 * SoSContainer
 */

OV_RESULT sosx_informationModelManagement_validateSoSContainer(
		OV_INSTPTR_sosx_SoSContainer		pTargetSoSContainer,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp			= NULL;
	OV_INSTPTR_sosx_SoSContainer			pTempSoSC		= NULL;
	OV_INSTPTR_ov_domain					pParent			= NULL;

#define Finally()

	if(pTargetSoSContainer == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the SoSContainer",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSoSContainer));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSoSContainer),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: ov_domain i.e. no sosx element*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetSoSContainer);
	if(Ov_CanCastTo(ov_domain,pParent)&&
			!Ov_CanCastTo(sosx_BaseElement,pParent) &&
			!Ov_CanCastTo(sosx_Alternative,pParent) &&
			!Ov_CanCastTo(sosx_Property,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of SoSContainer is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSoSContainer));
	}

	/* check name */
	/* warning if name = "" */
	if(ov_string_compare(pTargetSoSContainer->v_name,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","name missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSoSContainer));
	}

	/* check externalReference */
	if(pTargetSoSContainer->v_externalReference.veclen == 0){
		extendValidationLog(pValidationLog,"Warning","Attribute externalReference missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSoSContainer));
	}

	/* check if name of SoSContainerToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetSoSContainer);
	/* go through all sibling SoSContainers*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempSoSC,sosx_SoSContainer){
		/* ignore TargetSoSContainer*/
		if(pTempSoSC != pTargetSoSContainer){
			/* check if another SoSContainer has the same name as targetSoSContainer */
			if(ov_string_compare(pTargetSoSContainer->v_name, pTempSoSC->v_name) == OV_STRCMP_EQUAL){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSoSContainer));
			}
		}
	}

	// TO DO: offer hook-function for validation of specific element

	/* validate Children
	 * Allowed Children classes: (SourceSink and not DistributionNode), Stream or  System
	 */
	Ov_ForEachChildEx(ov_containment,pTargetSoSContainer,pTemp,ov_domain){
		if((Ov_CanCastTo(sosx_SourceSink,pTemp) && !Ov_CanCastTo(sosx_DistributionNode,pTemp))||
				(Ov_CanCastTo(sosx_System,pTemp))||
				(Ov_CanCastTo(sosx_Stream,pTemp))){
			sosx_workflowManagement_validateElement(pTemp,pValidationLog);
		}else{
			extendValidationLog(pValidationLog,"Error","SoSContainer has a Child of not allowed type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSoSContainer));
		}
	}

	Finally();
	return result;
}

/**
 * System
 */

static void checkIfSystemIsAcyclic(
		OV_INSTPTR_sosx_System				pRootSystem,
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_STRING_VEC						*pValidationLog
){
#undef Finally
#define Finally()
	OV_INSTPTR_sosx_System				pTempSystem	=	NULL;
	/* check if composition relationship of system is acyclic */
	Ov_ForEachChildEx(ov_containment,pTargetSystem,pTempSystem,sosx_System){
		if(pRootSystem == pTempSystem){
			extendValidationLog(pValidationLog,"Error","composition relationship of system is cyclic",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSystem));
			break;
		}
		checkIfSystemIsAcyclic(pTargetSystem,pTempSystem,pValidationLog);
	}
}

OV_RESULT sosx_informationModelManagement_validateSystem(
		OV_INSTPTR_sosx_System				pTargetSystem,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp			= NULL;
	OV_INSTPTR_sosx_System					pTempSys		= NULL;
	OV_INSTPTR_ov_domain					pParent			= NULL;

#undef Finally
#define Finally()

	if(pTargetSystem == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the System",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSystem));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSystem),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: SoSContainer and System*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetSystem);
	if(Ov_CanCastTo(sosx_SoSContainer,pParent)||
			Ov_CanCastTo(sosx_System,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of System is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSystem));
	}

	/* check name */
	/* warning if name = "" */
	if(ov_string_compare(pTargetSystem->v_name,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","name missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSystem));
	}

	/* validate validFrom, validUntil and caexLibrary */
	sosx_informationModelManagement_validateBaseElement(Ov_DynamicPtrCast(sosx_BaseElement,pTargetSystem),pValidationLog);

	/* check if name of SystemToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetSystem);
	/* go through all sibling systems*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempSys,sosx_System){
		/* ignore TargetSystem*/
		if(pTempSys != pTargetSystem){
			/* check if another system has the same name as targetSystem */
			if(ov_string_compare(pTargetSystem->v_name, pTempSys->v_name) == OV_STRCMP_EQUAL){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSystem));
			}
		}
	}

	/* validate Children
	 * Allowed Children classes: Process, System, DistributionNode, Port, Stream, Alternative, Property
	 */
	Ov_ForEachChildEx(ov_containment,pTargetSystem,pTemp,ov_domain){
		if((Ov_CanCastTo(sosx_Process,pTemp))||
				(Ov_CanCastTo(sosx_System,pTemp))||
				(Ov_CanCastTo(sosx_DistributionNode,pTemp))||
				(Ov_CanCastTo(sosx_Port,pTemp))||
				(Ov_CanCastTo(sosx_Stream,pTemp))||
				(Ov_CanCastTo(sosx_Alternative,pTemp))||
				(Ov_CanCastTo(sosx_Property,pTemp))){
			sosx_workflowManagement_validateElement(pTemp,pValidationLog);
		}else{
			extendValidationLog(pValidationLog,"Error","System has a Child of not allowed type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSystem));
		}
	}

	/* check if composition relationship of system is acyclic */
	checkIfSystemIsAcyclic(pTargetSystem,pTargetSystem,pValidationLog);

	// TO DO: offer hook-function for validation of specific element

	Finally();
	return result;
}

OV_RESULT sosx_informationModelManagement_validateProcess(
		OV_INSTPTR_sosx_Process				pTargetProcess,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_STRING								tmpStr			= NULL;
	OV_INSTPTR_ov_domain					pTemp			= NULL;
	OV_INSTPTR_ov_domain					pParent			= NULL;
	OV_INSTPTR_sosx_Process					pTempPro		= NULL;

#undef	Finally
#define Finally()						\
		ov_string_setvalue(&tmpStr,NULL);	\

	if(pTargetProcess == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the Process",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: System */
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetProcess);
	if(Ov_CanCastTo(sosx_System,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of System is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
	}

	/* check name */
	/* warning if name = "" */
	if(ov_string_compare(pTargetProcess->v_name,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","name missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
	}

	/* check externalReference */
	if(pTargetProcess->v_externalInfo.veclen == 0){
		extendValidationLog(pValidationLog,"Warning","Attribute externalInfo missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
	}

	/* validate validFrom, validUntil and caexLibrary */
	sosx_informationModelManagement_validateBaseElement(Ov_DynamicPtrCast(sosx_BaseElement,pTargetProcess),pValidationLog);

	/* check if name of ProcessToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetProcess);
	/* go through all sibling Process*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempPro,sosx_Process){
		/* ignore TargetProcess*/
		if(pTempPro != pTargetProcess){
			/* check if another Process has the same name as targetProcess */
			if(ov_string_compare(pTargetProcess->v_name, pTempPro->v_name) == OV_STRCMP_EQUAL){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
			}
		}
	}

	/* validate Children
	 * Allowed Children classes: Port, Property, FileMonitor
	 */
	Ov_ForEachChildEx(ov_containment,pTargetProcess,pTemp,ov_domain){
		if((Ov_CanCastTo(sosx_Port,pTemp))||
				(Ov_CanCastTo(sosx_Property,pTemp))){
			sosx_workflowManagement_validateElement(pTemp,pValidationLog);
		}else if(Ov_CanCastTo(sosx_FileMonitor,pTemp)){
			/* check FileMonitor status
			 */
			for(OV_UINT i = 0 ; i < pTargetProcess->v_externalInfoStat.veclen ; i++){
				ov_string_setvalue(&tmpStr,NULL);
				if(pTargetProcess->v_externalInfoStat.value[i] == SOSX_EXTERNALINFOSTATE_CHANGED){
					ov_string_setvalue(&tmpStr, "The following file has been changed: ");
					ov_string_append(&tmpStr,pTargetProcess->v_externalInfo.value[i]);
					extendValidationLog(pValidationLog,"Warning",tmpStr,Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
				} else
					if(pTargetProcess->v_externalInfoStat.value[i] == SOSX_EXTERNALINFOSTATE_NOTFOUND){
						ov_string_setvalue(&tmpStr, "The following file is missing: ");
						ov_string_append(&tmpStr,pTargetProcess->v_externalInfo.value[i]);
						extendValidationLog(pValidationLog,"Error",tmpStr,Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
					}
			}
		}
		else{
			extendValidationLog(pValidationLog,"Error","Process has a Child of not allowed type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetProcess));
		}
	}


	// TO DO: offer hook-function for validation of specific element

	Finally();
	return result;
}

/*
 * Port
 */

OV_RESULT sosx_informationModelManagement_validatePort(
		OV_INSTPTR_sosx_Port				pTargetPort,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp 			= NULL;
	OV_INSTPTR_ov_domain					pParent			= NULL;
	OV_INSTPTR_sosx_Port					pTempPort		= NULL;

#undef	Finally
#define Finally()

	if(pTargetPort == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the Port",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPort));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPort),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: System*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetPort);
	if(Ov_CanCastTo(sosx_System,pParent) ||
			Ov_CanCastTo(sosx_Process,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of Port is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPort));
	}

	/* check name */
	/* warning if name = "" */
	if(ov_string_compare(pTargetPort->v_name,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","name missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPort));
	}

	/* check StreamType */
	if(ov_string_compare(pTargetPort->v_StreamType,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","Attribute StreamType missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPort));
	}

	/* check if name of PortToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetPort);
	/* go through all sibling Ports*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempPort,sosx_Port){
		/* ignore TargetPort*/
		if(pTempPort != pTargetPort){
			/* check if another Port has the same name as targetPort */
			if(ov_string_compare(pTargetPort->v_name, pTempPort->v_name) == OV_STRCMP_EQUAL){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPort));
			}
		}
	}

	/* validate validFrom, validUntil and caexLibrary */
	sosx_informationModelManagement_validateBaseElement(Ov_DynamicPtrCast(sosx_BaseElement,pTargetPort),pValidationLog);

	/* validate Children
	 * Allowed Children class: Property
	 */
	Ov_ForEachChildEx(ov_containment,pTargetPort,pTemp,ov_domain){
		if((Ov_CanCastTo(sosx_Property,pTemp))){
			sosx_informationModelManagement_validateProperty(Ov_DynamicPtrCast(sosx_Property,pTemp),pValidationLog);
		}else{
			extendValidationLog(pValidationLog,"Error","Port has a Child of not allowed type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetPort));
		}
	}

	/* validate Links*/
	validateLinks(Ov_DynamicPtrCast(sosx_StreamHandler,pTargetPort),pValidationLog);


	// TO DO: offer hook-function for validation of specific element

	Finally();
	return result;
}

OV_RESULT sosx_informationModelManagement_validateSourceSink(
		OV_INSTPTR_sosx_SourceSink			pTargetSourceSink,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp			= NULL;
	OV_INSTPTR_ov_domain					pParent			= NULL;
	OV_INSTPTR_sosx_SourceSink				pTempSourceSink	= NULL;


#undef	Finally
#define Finally()

	if(pTargetSourceSink == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the SourceSink",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSourceSink));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSourceSink),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: SoSContainer*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetSourceSink);
	if(Ov_CanCastTo(sosx_SoSContainer,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of SourceSink is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSourceSink));
	}

	/* check name */
	/* warning if name = "" */
	if(ov_string_compare(pTargetSourceSink->v_name,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","name missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSourceSink));
	}

	/* check StreamType */
	if(ov_string_compare(pTargetSourceSink->v_StreamType,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","Attribute SourceSinkType missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSourceSink));
	}

	/* check if name of SourceSinkToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetSourceSink);
	/* go through all sibling of SourceSink*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempSourceSink,sosx_SourceSink){
		/* ignore TargetSourceSink*/
		if(pTempSourceSink != pTargetSourceSink){
			/* check if another SourceSink has the same name as targetSourceSink */
			if(ov_string_compare(pTargetSourceSink->v_name, pTempSourceSink->v_name) == OV_STRCMP_EQUAL){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSourceSink));
			}
		}
	}

	/* validate Children
	 * Allowed Children class: Property
	 */
	Ov_ForEachChildEx(ov_containment,pTargetSourceSink,pTemp,ov_domain){
		if((Ov_CanCastTo(sosx_Property,pTemp))){
			sosx_informationModelManagement_validateProperty(Ov_DynamicPtrCast(sosx_Property,pTemp),pValidationLog);
		}else{
			extendValidationLog(pValidationLog,"Error","SourceSink has a Child of not allowed type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetSourceSink));
		}
	}

	/* validate Links*/
	validateLinks(Ov_DynamicPtrCast(sosx_StreamHandler,pTargetSourceSink),pValidationLog);

	/* validate validFrom, validUntil and caexLibrary */
	sosx_informationModelManagement_validateBaseElement(Ov_DynamicPtrCast(sosx_BaseElement,pTargetSourceSink),pValidationLog);

	// TO DO: offer hook-function for validation of specific element

	Finally();
	return result;
}

OV_RESULT sosx_informationModelManagement_validateDistributionNode(
		OV_INSTPTR_sosx_DistributionNode	pTargetDistributionNode,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result					= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp					= NULL;
	OV_INSTPTR_ov_domain					pParent					= NULL;
	OV_INSTPTR_sosx_DistributionNode		pTempDistributionNode	= NULL;

#undef	Finally
#define Finally()

	if(pTargetDistributionNode == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the DistributionNode",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetDistributionNode));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetDistributionNode),SOSX_ISVALID_ISVALID);

	/*check if parent is of right type. Allowed parents: System*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetDistributionNode);
	if(Ov_CanCastTo(sosx_System,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of DistributionNode is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetDistributionNode));
	}

	/* check name */
	/* warning if name = "" */
	if(ov_string_compare(pTargetDistributionNode->v_name,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","name missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetDistributionNode));
	}

	/* check StreamType */
	if(ov_string_compare(pTargetDistributionNode->v_StreamType,"") == OV_STRCMP_EQUAL){
		extendValidationLog(pValidationLog,"Warning","Attribute DistributionNodeType missing",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetDistributionNode));
	}

	/* check if name of DistributionNodeToBeValidated is unique */
	/* getParent */
	pParent = Ov_GetParent(ov_containment,pTargetDistributionNode);
	/* go through all sibling of DistributionNode*/
	Ov_ForEachChildEx(ov_containment,pParent,pTempDistributionNode,sosx_DistributionNode){
		/* ignore TargetDistributionNode*/
		if(pTempDistributionNode != pTargetDistributionNode){
			/* check if another DistributionNode has the same name as targetDistributionNode */
			if(ov_string_compare(pTargetDistributionNode->v_name, pTempDistributionNode->v_name) == OV_STRCMP_EQUAL){
				extendValidationLog(pValidationLog,"Error","name is not unique",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetDistributionNode));
			}
		}
	}

	/* validate Children
	 * Allowed Children class: Property
	 */
	Ov_ForEachChildEx(ov_containment,pTargetDistributionNode,pTemp,ov_domain){
		if((Ov_CanCastTo(sosx_Property,pTemp))){
			sosx_informationModelManagement_validateProperty(Ov_DynamicPtrCast(sosx_Property,pTemp),pValidationLog);
		}else{
			extendValidationLog(pValidationLog,"Error","DistributionNode has a Child of not allowed type",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetDistributionNode));
		}
	}

	/* validate Links*/
	validateLinks(Ov_DynamicPtrCast(sosx_StreamHandler,pTargetDistributionNode),pValidationLog);

	/* validate validFrom, validUntil and caexLibrary */
	sosx_informationModelManagement_validateBaseElement(Ov_DynamicPtrCast(sosx_BaseElement,pTargetDistributionNode),pValidationLog);

	// TO DO: offer hook-function for validation of specific element

	Finally();
	return result;
}


OV_RESULT sosx_informationModelManagement_validateStream(
		OV_INSTPTR_sosx_Stream				pTargetStream,
		OV_STRING_VEC						*pValidationLog
){
	OV_RESULT								result			= OV_ERR_OK;
	OV_INSTPTR_ov_domain					pTemp			= NULL;
	OV_INSTPTR_ov_domain					pParent			= NULL;
	OV_INSTPTR_sosx_StreamHandler			pStreamHandlerA	= NULL;
	OV_INSTPTR_sosx_StreamHandler			pStreamHandlerB	= NULL;

#undef	Finally
#define Finally()

	if(pTargetStream == NULL){
		result = OV_ERR_GENERIC;
		extendValidationLog(pValidationLog,"Error","Could not find the Stream",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
		Finally();
		return result;
	}

	sosx_sosxdomain_isValid_set(Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream),1);

	/*check if parent is of right type. Allowed parents: SoSContainer or System*/
	/* get parent */
	pParent = Ov_GetParent(ov_containment,pTargetStream);
	if(Ov_CanCastTo(sosx_System,pParent) ||
			Ov_CanCastTo(sosx_SoSContainer,pParent)){
		/* everything okay */
	}else{
		/* parent is of wrong type */
		extendValidationLog(pValidationLog,"Error","Parent of Stream is of wrong type.",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
	}

	/* validate Children
	 * Allowed Children class: none
	 */
	Ov_ForEachChildEx(ov_containment,pTargetStream,pTemp,ov_domain){
		extendValidationLog(pValidationLog,"Error","Stream should not have a Child",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
	}

	/* validate validFrom, validUntil and caexLibrary */
	sosx_informationModelManagement_validateBaseElement(Ov_DynamicPtrCast(sosx_BaseElement,pTargetStream),pValidationLog);

	// TO DO: offer hook-function for validation of specific element

	/* validateLinks */
	/* get both StreamHandler */
	pStreamHandlerA = Ov_GetParent(sosx_isLinkedToSideA,Ov_DynamicPtrCast(sosx_Stream,pTargetStream));
	pStreamHandlerB = Ov_GetParent(sosx_isLinkedToSideB,Ov_DynamicPtrCast(sosx_Stream,pTargetStream));

	/* check if two StreamHandler found */
	if(pStreamHandlerA == NULL || pStreamHandlerB == NULL){
		extendValidationLog(pValidationLog,"Error","One or both ends of the Stream is/are not linked to a StreamHandler",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
		return result;
	}

	/* check if both sides of the stream have the same StreamType */
	if(ov_string_compare(pStreamHandlerA->v_StreamType,pStreamHandlerB->v_StreamType) == OV_STRCMP_EQUAL){
		/* everything okay */
	}else{
		extendValidationLog(pValidationLog,"Error","Wrong StreamType",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
	}

	if(Ov_CanCastTo(sosx_DistributionNode,pStreamHandlerA) == FALSE &&
			Ov_CanCastTo(sosx_SourceSink,pStreamHandlerA) == TRUE){
		// if side a: Source			then side b: Port of System
		// if side a: Sink				then side b: Port of System
		if(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB))){
			/* everything okay */
			return result;
		}else{
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
			return result;
		}
	}

	if(Ov_CanCastTo(sosx_DistributionNode,pStreamHandlerA)){
		// if side a: Distribution Node	then side b: Port of Process or Port of System
		if((Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerB)))||
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB)))){
			/* everything okay */
			return result;
		}else{
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
			return result;
		}
	}

	if(Ov_CanCastTo(sosx_Port,pStreamHandlerA) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerA))){
		// if side a: Port of Process	then side b: Distribution Node, Port of Process or Port of System
		if(Ov_CanCastTo(sosx_DistributionNode,pStreamHandlerB) ||
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerB))) ||
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB)))){
			/* everything okay */
			return result;
		}else{
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
			return result;
		}
	}

	if(Ov_CanCastTo(sosx_Port,pStreamHandlerA) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerA))){
		// if side a: Port of System	then side b: Source, Sink, DistributionNode, Port of Process, Port of System
		if((Ov_CanCastTo(sosx_DistributionNode,pStreamHandlerB)) ||
				(Ov_CanCastTo(sosx_SourceSink,pStreamHandlerB)) ||
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_Process,Ov_GetParent(ov_containment,pStreamHandlerB))) ||
				(Ov_CanCastTo(sosx_Port,pStreamHandlerB) && Ov_CanCastTo(sosx_System,Ov_GetParent(ov_containment,pStreamHandlerB)))){
			/* everything okay */
			return result;
		}else{
			extendValidationLog(pValidationLog,"Error","isLinkedTo relationship is not allowed",Ov_DynamicPtrCast(sosx_sosxdomain,pTargetStream));
			return result;
		}
	}
	Finally();
	return result;
}

OV_RESULT sosx_workflowManagement_validateAlternative(
		OV_INSTPTR_sosx_Alternative			pTargetAlternative,
		OV_STRING_VEC						*validateLog
){
	OV_RESULT								result			= OV_ERR_OK;

#define Finally()
	Finally();
	return result;
}

#endif
