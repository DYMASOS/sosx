/*
*   This file was generated by the ACPLT/OV C-Code Generator.
*
*   C-Code Generator version: 1.6.4
*   ACPLT/OV library version: 2.0.0
*   Date of file generation:  11-Aug-2016 ( 9:06:49)
*
*   DO NOT EDIT THIS FILE!
*/

#ifndef OV_LIBRARY_ksxdrgethist_H_INCLUDED
#define OV_LIBRARY_ksxdrgethist_H_INCLUDED

#include "libov/ov_library.h"
#include "libov/ov_structure.h"
#include "libov/ov_class.h"
#include "libov/ov_association.h"
#include "libov/ov_variable.h"
#include "libov/ov_part.h"
#include "libov/ov_operation.h"
#include "ov.h"
#include "ksbase.h"
#include "ksxdr.h"
#include "ksapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OV_COMPILE_LIBRARY_ksxdrgethist
#if OV_COMPILER_BORLAND
#define OV_VAREXTERN extern
#else
#define OV_VAREXTERN OV_DLLVAREXPORT
#endif
#define OV_FNCEXTERN OV_DLLFNCEXPORT
#else
#define OV_VAREXTERN OV_DLLVARIMPORT
#define OV_FNCEXTERN OV_DLLVARIMPORT
#endif

#define OV_PPT_ksxdrgethist_operationGetHist struct OV_INST_ksxdrgethist_getHist*
#define OV_CPT_ksxdrgethist_operationGetHist struct OV_INST_ksxdrgethist_getHistParams*
#define OV_PCI_ksxdrgethist_operationGetHist is_of_class_ksxdrgethist_getHist
#define OV_CCI_ksxdrgethist_operationGetHist is_of_class_ksxdrgethist_getHistParams

#define OV_PPT_ksxdrgethist_HistParam struct OV_INST_ksxdrgethist_getHistParams*
#define OV_CPT_ksxdrgethist_HistParam struct OV_INST_ksxdrgethist_KsGetHistItem*
#define OV_PCI_ksxdrgethist_HistParam is_of_class_ksxdrgethist_getHistParams
#define OV_CCI_ksxdrgethist_HistParam is_of_class_ksxdrgethist_KsGetHistItem

#define OV_BIPT_ksxdrgethist_xdrGetHistClient OV_INSTPTR_ksxdr_xdrClient
#define OV_BVPT_ksxdrgethist_xdrGetHistClient OV_VTBLPTR_ksxdr_xdrClient

#define OV_INSTBODY_ksxdrgethist_xdrGetHistClient \
    OV_INSTBODY_ksxdr_xdrClient

#define OV_CIB_ksxdrgethist_xdrGetHistClient \
    OV_CIB_ksxdr_xdrClient \
    int is_of_class_ksxdrgethist_xdrGetHistClient:1;

#define OV_STATICINSTBODY_ksxdrgethist_xdrGetHistClient

#define OV_BIPT_ksxdrgethist_getHist OV_INSTPTR_ksapi_KSApiCommon
#define OV_BVPT_ksxdrgethist_getHist OV_VTBLPTR_ksapi_KSApiCommon

#define OV_INSTBODY_ksxdrgethist_getHist \
    OV_INSTBODY_ksapi_KSApiCommon

#define OV_CIB_ksxdrgethist_getHist \
    OV_CIB_ksapi_KSApiCommon \
    int is_of_class_ksxdrgethist_getHist:1;

#define OV_STATICINSTBODY_ksxdrgethist_getHist

#define OV_BIPT_ksxdrgethist_getHistParams OV_INSTPTR_ov_domain
#define OV_BVPT_ksxdrgethist_getHistParams OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ksxdrgethist_getHistParams \
    OV_INSTBODY_ov_domain \
    OV_STRING_VEC v_historypaths; \
    OV_UINT v_maxanswers;

#define OV_CIB_ksxdrgethist_getHistParams \
    OV_CIB_ov_domain \
    int is_of_class_ksxdrgethist_getHistParams:1;

#define OV_STATICINSTBODY_ksxdrgethist_getHistParams

#define OV_BIPT_ksxdrgethist_KsGetHistItem OV_INSTPTR_ov_domain
#define OV_BVPT_ksxdrgethist_KsGetHistItem OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ksxdrgethist_KsGetHistItem \
    OV_INSTBODY_ov_domain \
    OV_STRING v_part; \
    OV_UINT v_KSHSELTYPE;

#define OV_CIB_ksxdrgethist_KsGetHistItem \
    OV_CIB_ov_domain \
    int is_of_class_ksxdrgethist_KsGetHistItem:1;

#define OV_STATICINSTBODY_ksxdrgethist_KsGetHistItem

#define OV_BIPT_ksxdrgethist_KsTimeHistSelector OV_INSTPTR_ksxdrgethist_KsGetHistItem
#define OV_BVPT_ksxdrgethist_KsTimeHistSelector OV_VTBLPTR_ksxdrgethist_KsGetHistItem

#define OV_INSTBODY_ksxdrgethist_KsTimeHistSelector \
    OV_INSTBODY_ksxdrgethist_KsGetHistItem \
    OV_UINT v_KSTIMETYPE; \
    OV_TIME_SPAN v_delta; \
    OV_UINT v_ipmode;

#define OV_CIB_ksxdrgethist_KsTimeHistSelector \
    OV_CIB_ksxdrgethist_KsGetHistItem \
    int is_of_class_ksxdrgethist_KsTimeHistSelector:1;

#define OV_STATICINSTBODY_ksxdrgethist_KsTimeHistSelector

#define OV_BIPT_ksxdrgethist_KSTTABS OV_INSTPTR_ksxdrgethist_KsTimeHistSelector
#define OV_BVPT_ksxdrgethist_KSTTABS OV_VTBLPTR_ksxdrgethist_KsTimeHistSelector

#define OV_INSTBODY_ksxdrgethist_KSTTABS \
    OV_INSTBODY_ksxdrgethist_KsTimeHistSelector \
    OV_TIME v_from; \
    OV_TIME v_to;

#define OV_CIB_ksxdrgethist_KSTTABS \
    OV_CIB_ksxdrgethist_KsTimeHistSelector \
    int is_of_class_ksxdrgethist_KSTTABS:1;

#define OV_STATICINSTBODY_ksxdrgethist_KSTTABS

#define OV_BIPT_ksxdrgethist_KSTTREL OV_INSTPTR_ksxdrgethist_KsTimeHistSelector
#define OV_BVPT_ksxdrgethist_KSTTREL OV_VTBLPTR_ksxdrgethist_KsTimeHistSelector

#define OV_INSTBODY_ksxdrgethist_KSTTREL \
    OV_INSTBODY_ksxdrgethist_KsTimeHistSelector \
    OV_TIME_SPAN v_from; \
    OV_TIME_SPAN v_to;

#define OV_CIB_ksxdrgethist_KSTTREL \
    OV_CIB_ksxdrgethist_KsTimeHistSelector \
    int is_of_class_ksxdrgethist_KSTTREL:1;

#define OV_STATICINSTBODY_ksxdrgethist_KSTTREL

#define OV_BIPT_ksxdrgethist_KsStringHistSelector OV_INSTPTR_ksxdrgethist_KsGetHistItem
#define OV_BVPT_ksxdrgethist_KsStringHistSelector OV_VTBLPTR_ksxdrgethist_KsGetHistItem

#define OV_INSTBODY_ksxdrgethist_KsStringHistSelector \
    OV_INSTBODY_ksxdrgethist_KsGetHistItem \
    OV_STRING v_mask;

#define OV_CIB_ksxdrgethist_KsStringHistSelector \
    OV_CIB_ksxdrgethist_KsGetHistItem \
    int is_of_class_ksxdrgethist_KsStringHistSelector:1;

#define OV_STATICINSTBODY_ksxdrgethist_KsStringHistSelector

#define OV_BIPT_ksxdrgethist_GetHistResult OV_INSTPTR_ov_domain
#define OV_BVPT_ksxdrgethist_GetHistResult OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ksxdrgethist_GetHistResult \
    OV_INSTBODY_ov_domain

#define OV_CIB_ksxdrgethist_GetHistResult \
    OV_CIB_ov_domain \
    int is_of_class_ksxdrgethist_GetHistResult:1;

#define OV_STATICINSTBODY_ksxdrgethist_GetHistResult

#define OV_BIPT_ksxdrgethist_KsGetHistPerHistResult OV_INSTPTR_ov_domain
#define OV_BVPT_ksxdrgethist_KsGetHistPerHistResult OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ksxdrgethist_KsGetHistPerHistResult \
    OV_INSTBODY_ov_domain \
    OV_INT v_result;

#define OV_CIB_ksxdrgethist_KsGetHistPerHistResult \
    OV_CIB_ov_domain \
    int is_of_class_ksxdrgethist_KsGetHistPerHistResult:1;

#define OV_STATICINSTBODY_ksxdrgethist_KsGetHistPerHistResult

#define OV_BIPT_ksxdrgethist_KsGetHistResultItem OV_INSTPTR_ov_domain
#define OV_BVPT_ksxdrgethist_KsGetHistResultItem OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ksxdrgethist_KsGetHistResultItem \
    OV_INSTBODY_ov_domain \
    OV_INT v_result; \
    OV_ANY v_value;

#define OV_CIB_ksxdrgethist_KsGetHistResultItem \
    OV_CIB_ov_domain \
    int is_of_class_ksxdrgethist_KsGetHistResultItem:1;

#define OV_STATICINSTBODY_ksxdrgethist_KsGetHistResultItem

OV_TYPEDEF_INSTANCE(ksxdrgethist_xdrGetHistClient);
OV_TYPEDEF_INSTANCE(ksxdrgethist_getHist);
OV_TYPEDEF_INSTANCE(ksxdrgethist_getHistParams);
OV_TYPEDEF_INSTANCE(ksxdrgethist_KsGetHistItem);
OV_TYPEDEF_INSTANCE(ksxdrgethist_KsTimeHistSelector);
OV_TYPEDEF_INSTANCE(ksxdrgethist_KSTTABS);
OV_TYPEDEF_INSTANCE(ksxdrgethist_KSTTREL);
OV_TYPEDEF_INSTANCE(ksxdrgethist_KsStringHistSelector);
OV_TYPEDEF_INSTANCE(ksxdrgethist_GetHistResult);
OV_TYPEDEF_INSTANCE(ksxdrgethist_KsGetHistPerHistResult);
OV_TYPEDEF_INSTANCE(ksxdrgethist_KsGetHistResultItem);

#include "ksxdrgethist.ovf"

OV_FNCEXTERN KSXDRGETHIST_FNC_REQGETHIST ksxdrgethist_xdrGetHistClient_requestGetHist;
OV_FNCEXTERN KSXDRGETHIST_FNC_PROCGETHIST ksxdrgethist_xdrGetHistClient_processGetHist;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_getHist_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_getHist_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_getHist_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN ksxdrgethist_getHist_shutdown;
OV_FNCEXTERN KSAPI_FNC_SUBMIT ksxdrgethist_getHist_submit;
OV_FNCEXTERN KSXDRGETHIST_FNC_SETANDSUBMIT_GETHIST ksxdrgethist_getHist_setandsubmit;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_getHistParams_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_getHistParams_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_getHistParams_startup;
OV_FNCEXTERN OV_FNC_GETACCESS ksxdrgethist_getHistParams_getaccess;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_KsGetHistItem_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_KsGetHistItem_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_KsGetHistItem_startup;
OV_FNCEXTERN OV_FNC_GETACCESS ksxdrgethist_KsGetHistItem_getaccess;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_KsTimeHistSelector_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_KsTimeHistSelector_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_KsTimeHistSelector_startup;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_KSTTABS_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_KSTTABS_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_KSTTABS_startup;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_KSTTREL_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_KSTTREL_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_KSTTREL_startup;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_KsStringHistSelector_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_KsStringHistSelector_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_KsStringHistSelector_startup;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_GetHistResult_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_GetHistResult_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_GetHistResult_startup;
OV_FNCEXTERN OV_FNC_GETACCESS ksxdrgethist_GetHistResult_getaccess;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_KsGetHistPerHistResult_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_KsGetHistPerHistResult_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_KsGetHistPerHistResult_startup;
OV_FNCEXTERN OV_FNC_GETACCESS ksxdrgethist_KsGetHistPerHistResult_getaccess;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ksxdrgethist_KsGetHistResultItem_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ksxdrgethist_KsGetHistResultItem_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ksxdrgethist_KsGetHistResultItem_startup;
OV_FNCEXTERN OV_FNC_GETACCESS ksxdrgethist_KsGetHistResultItem_getaccess;

#define OV_VTBLBODY_ksxdrgethist_xdrGetHistClient \
    OV_VTBLBODY_ksxdr_xdrClient \
    KSXDRGETHIST_FNC_REQGETHIST* m_requestGetHist; \
    KSXDRGETHIST_FNC_PROCGETHIST* m_processGetHist;

#define OV_VTBLBODY_ksxdrgethist_getHist \
    OV_VTBLBODY_ksapi_KSApiCommon \
    KSXDRGETHIST_FNC_SETANDSUBMIT_GETHIST* m_setandsubmit;

#define OV_VTBLBODY_ksxdrgethist_getHistParams \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_ksxdrgethist_KsGetHistItem \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_ksxdrgethist_KsTimeHistSelector \
    OV_VTBLBODY_ksxdrgethist_KsGetHistItem

#define OV_VTBLBODY_ksxdrgethist_KSTTABS \
    OV_VTBLBODY_ksxdrgethist_KsTimeHistSelector

#define OV_VTBLBODY_ksxdrgethist_KSTTREL \
    OV_VTBLBODY_ksxdrgethist_KsTimeHistSelector

#define OV_VTBLBODY_ksxdrgethist_KsStringHistSelector \
    OV_VTBLBODY_ksxdrgethist_KsGetHistItem

#define OV_VTBLBODY_ksxdrgethist_GetHistResult \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_ksxdrgethist_KsGetHistPerHistResult \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_ksxdrgethist_KsGetHistResultItem \
    OV_VTBLBODY_ov_domain

OV_TYPEDEF_VTABLE(ksxdrgethist_xdrGetHistClient);
OV_TYPEDEF_VTABLE(ksxdrgethist_getHist);
OV_TYPEDEF_VTABLE(ksxdrgethist_getHistParams);
OV_TYPEDEF_VTABLE(ksxdrgethist_KsGetHistItem);
OV_TYPEDEF_VTABLE(ksxdrgethist_KsTimeHistSelector);
OV_TYPEDEF_VTABLE(ksxdrgethist_KSTTABS);
OV_TYPEDEF_VTABLE(ksxdrgethist_KSTTREL);
OV_TYPEDEF_VTABLE(ksxdrgethist_KsStringHistSelector);
OV_TYPEDEF_VTABLE(ksxdrgethist_GetHistResult);
OV_TYPEDEF_VTABLE(ksxdrgethist_KsGetHistPerHistResult);
OV_TYPEDEF_VTABLE(ksxdrgethist_KsGetHistResultItem);

OV_DLLFNCEXPORT OV_ANY *ksxdrgethist_KsGetHistResultItem_value_get(
    OV_INSTPTR_ksxdrgethist_KsGetHistResultItem pobj
);

OV_DECL_LINK(ksxdrgethist_operationGetHist);
OV_DECL_UNLINK(ksxdrgethist_operationGetHist);
OV_DECL_GETACCESS(ksxdrgethist_operationGetHist);

OV_DECL_LINK(ksxdrgethist_HistParam);
OV_DECL_UNLINK(ksxdrgethist_HistParam);
OV_DECL_GETACCESS(ksxdrgethist_HistParam);

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_xdrGetHistClient;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_xdrGetHistClient;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_getHist;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_getHist;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_getHistParams;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_getHistParams;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_KsGetHistItem;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_KsGetHistItem;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_KsTimeHistSelector;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_KsTimeHistSelector;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_KSTTABS;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_KSTTABS;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_KSTTREL;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_KSTTREL;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_KsStringHistSelector;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_KsStringHistSelector;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_GetHistResult;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_GetHistResult;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_KsGetHistPerHistResult;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_KsGetHistPerHistResult;

extern OV_CLASS_DEF OV_CLASS_DEF_ksxdrgethist_KsGetHistResultItem;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ksxdrgethist_KsGetHistResultItem;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ksxdrgethist_operationGetHist;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ksxdrgethist_operationGetHist;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ksxdrgethist_HistParam;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ksxdrgethist_HistParam;

extern OV_LIBRARY_DEF OV_LIBRARY_DEF_ksxdrgethist;

OV_RESULT ov_library_setglobalvars_ksxdrgethist(void);

OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_ksxdrgethist(void);

#undef OV_VAREXTERN
#undef OV_FNCEXTERN

#ifdef __cplusplus
}
#endif

#endif

/*
*   End of file
*/
