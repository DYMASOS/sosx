/*
*   This file was generated by the ACPLT/OV C-Code Generator.
*
*   C-Code Generator version: 1.6.4
*   ACPLT/OV library version: 2.0.0
*   Date of file generation:  15-Jun-2016 (13:10:35)
*
*   DO NOT EDIT THIS FILE!
*/

#ifndef OV_LIBRARY_fbcomlib_H_INCLUDED
#define OV_LIBRARY_fbcomlib_H_INCLUDED

#include "libov/ov_library.h"
#include "libov/ov_structure.h"
#include "libov/ov_class.h"
#include "libov/ov_association.h"
#include "libov/ov_variable.h"
#include "libov/ov_part.h"
#include "libov/ov_operation.h"
#include "ov.h"
#include "ksbase.h"
#include "fb.h"
#include "ksapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OV_COMPILE_LIBRARY_fbcomlib
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

#define OV_PPT_fbcomlib_PkgVar struct OV_INST_fbcomlib_variableOperation*
#define OV_CPT_fbcomlib_PkgVar struct OV_INST_fbcomlib_pkgVariable*
#define OV_PCI_fbcomlib_PkgVar is_of_class_fbcomlib_variableOperation
#define OV_CCI_fbcomlib_PkgVar is_of_class_fbcomlib_pkgVariable

#define OV_BIPT_fbcomlib_FBComCommon OV_INSTPTR_fb_functionblock
#define OV_BVPT_fbcomlib_FBComCommon OV_VTBLPTR_fb_functionblock

#define OV_INSTBODY_fbcomlib_FBComCommon \
    OV_INSTBODY_fb_functionblock \
    OV_STRING v_host; \
    OV_STRING v_server; \
    OV_STRING v_path; \
    OV_BOOL v_doSend; \
    OV_BOOL v_sendRequested; \
    OV_BOOL v_doCyclic; \
    OV_STRING v_stateString; \
    OV_INT v_state; \
    OV_UINT v_errorCode; \
    OV_UINT v_opResult; \
    OV_UINT v_timeout; \
    OV_UINT v_retryAfter; \
    OV_TIME v_requestSendTime;

#define OV_CIB_fbcomlib_FBComCommon \
    OV_CIB_fb_functionblock \
    int is_of_class_fbcomlib_FBComCommon:1;

#define OV_STATICINSTBODY_fbcomlib_FBComCommon

#define OV_BIPT_fbcomlib_variableOperation OV_INSTPTR_fbcomlib_FBComCommon
#define OV_BVPT_fbcomlib_variableOperation OV_VTBLPTR_fbcomlib_FBComCommon

#define OV_INSTBODY_fbcomlib_variableOperation \
    OV_INSTBODY_fbcomlib_FBComCommon \
    OV_UINT v_varResult;

#define OV_CIB_fbcomlib_variableOperation \
    OV_CIB_fbcomlib_FBComCommon \
    int is_of_class_fbcomlib_variableOperation:1;

#define OV_STATICINSTBODY_fbcomlib_variableOperation

#define OV_BIPT_fbcomlib_setVar OV_INSTPTR_fbcomlib_variableOperation
#define OV_BVPT_fbcomlib_setVar OV_VTBLPTR_fbcomlib_variableOperation

#define OV_INSTBODY_fbcomlib_setVar \
    OV_INSTBODY_fbcomlib_variableOperation \
    OV_ANY v_sendVar; \
    OV_BOOL v_doReset; \
    OV_INST_ksapi_setVar p_apiSet;

#define OV_CIB_fbcomlib_setVar \
    OV_CIB_fbcomlib_variableOperation \
    int is_of_class_fbcomlib_setVar:1;

#define OV_STATICINSTBODY_fbcomlib_setVar

#define OV_BIPT_fbcomlib_getVar OV_INSTPTR_fbcomlib_variableOperation
#define OV_BVPT_fbcomlib_getVar OV_VTBLPTR_fbcomlib_variableOperation

#define OV_INSTBODY_fbcomlib_getVar \
    OV_INSTBODY_fbcomlib_variableOperation \
    OV_ANY v_receivedVar; \
    OV_BOOL v_doReset; \
    OV_INST_ksapi_getVar p_apiGet;

#define OV_CIB_fbcomlib_getVar \
    OV_CIB_fbcomlib_variableOperation \
    int is_of_class_fbcomlib_getVar:1;

#define OV_STATICINSTBODY_fbcomlib_getVar

#define OV_BIPT_fbcomlib_pkgVariable OV_INSTPTR_fb_functionblock
#define OV_BVPT_fbcomlib_pkgVariable OV_VTBLPTR_fb_functionblock

#define OV_INSTBODY_fbcomlib_pkgVariable \
    OV_INSTBODY_fb_functionblock \
    OV_STRING v_path; \
    OV_UINT v_varResult; \
    OV_INST_ksapi_Variable p_apiVar;

#define OV_CIB_fbcomlib_pkgVariable \
    OV_CIB_fb_functionblock \
    int is_of_class_fbcomlib_pkgVariable:1;

#define OV_STATICINSTBODY_fbcomlib_pkgVariable

#define OV_BIPT_fbcomlib_pkgGetVariable OV_INSTPTR_fbcomlib_pkgVariable
#define OV_BVPT_fbcomlib_pkgGetVariable OV_VTBLPTR_fbcomlib_pkgVariable

#define OV_INSTBODY_fbcomlib_pkgGetVariable \
    OV_INSTBODY_fbcomlib_pkgVariable \
    OV_ANY v_value;

#define OV_CIB_fbcomlib_pkgGetVariable \
    OV_CIB_fbcomlib_pkgVariable \
    int is_of_class_fbcomlib_pkgGetVariable:1;

#define OV_STATICINSTBODY_fbcomlib_pkgGetVariable

#define OV_BIPT_fbcomlib_pkgSetVariable OV_INSTPTR_fbcomlib_pkgVariable
#define OV_BVPT_fbcomlib_pkgSetVariable OV_VTBLPTR_fbcomlib_pkgVariable

#define OV_INSTBODY_fbcomlib_pkgSetVariable \
    OV_INSTBODY_fbcomlib_pkgVariable \
    OV_ANY v_value;

#define OV_CIB_fbcomlib_pkgSetVariable \
    OV_CIB_fbcomlib_pkgVariable \
    int is_of_class_fbcomlib_pkgSetVariable:1;

#define OV_STATICINSTBODY_fbcomlib_pkgSetVariable

#define OV_BIPT_fbcomlib_getEPidentifiers OV_INSTPTR_fbcomlib_FBComCommon
#define OV_BVPT_fbcomlib_getEPidentifiers OV_VTBLPTR_fbcomlib_FBComCommon

#define OV_INSTBODY_fbcomlib_getEPidentifiers \
    OV_INSTBODY_fbcomlib_FBComCommon \
    OV_BOOL v_doReset; \
    OV_STRING v_namemask; \
    OV_STRING_VEC v_identifierList; \
    OV_INST_ksapi_getEPidentifiers p_apiGetEPid;

#define OV_CIB_fbcomlib_getEPidentifiers \
    OV_CIB_fbcomlib_FBComCommon \
    int is_of_class_fbcomlib_getEPidentifiers:1;

#define OV_STATICINSTBODY_fbcomlib_getEPidentifiers

#define OV_BIPT_fbcomlib_createObject OV_INSTPTR_fbcomlib_FBComCommon
#define OV_BVPT_fbcomlib_createObject OV_VTBLPTR_fbcomlib_FBComCommon

#define OV_INSTBODY_fbcomlib_createObject \
    OV_INSTBODY_fbcomlib_FBComCommon \
    OV_STRING v_classPath; \
    OV_INT v_position; \
    OV_STRING v_element; \
    OV_BOOL v_doReset; \
    OV_INST_ksapi_createObject p_apiCreate;

#define OV_CIB_fbcomlib_createObject \
    OV_CIB_fbcomlib_FBComCommon \
    int is_of_class_fbcomlib_createObject:1;

#define OV_STATICINSTBODY_fbcomlib_createObject

#define OV_BIPT_fbcomlib_deleteObject OV_INSTPTR_fbcomlib_FBComCommon
#define OV_BVPT_fbcomlib_deleteObject OV_VTBLPTR_fbcomlib_FBComCommon

#define OV_INSTBODY_fbcomlib_deleteObject \
    OV_INSTBODY_fbcomlib_FBComCommon \
    OV_BOOL v_doReset; \
    OV_INST_ksapi_deleteObject p_apiDelete;

#define OV_CIB_fbcomlib_deleteObject \
    OV_CIB_fbcomlib_FBComCommon \
    int is_of_class_fbcomlib_deleteObject:1;

#define OV_STATICINSTBODY_fbcomlib_deleteObject

#define OV_BIPT_fbcomlib_renameObject OV_INSTPTR_fbcomlib_FBComCommon
#define OV_BVPT_fbcomlib_renameObject OV_VTBLPTR_fbcomlib_FBComCommon

#define OV_INSTBODY_fbcomlib_renameObject \
    OV_INSTBODY_fbcomlib_FBComCommon \
    OV_STRING v_newpath; \
    OV_BOOL v_doReset; \
    OV_INST_ksapi_renameObject p_apiRename;

#define OV_CIB_fbcomlib_renameObject \
    OV_CIB_fbcomlib_FBComCommon \
    int is_of_class_fbcomlib_renameObject:1;

#define OV_STATICINSTBODY_fbcomlib_renameObject

#define OV_BIPT_fbcomlib_linkObject OV_INSTPTR_fbcomlib_FBComCommon
#define OV_BVPT_fbcomlib_linkObject OV_VTBLPTR_fbcomlib_FBComCommon

#define OV_INSTBODY_fbcomlib_linkObject \
    OV_INSTBODY_fbcomlib_FBComCommon \
    OV_STRING v_elementPath; \
    OV_INT v_position; \
    OV_STRING v_placePath; \
    OV_BOOL v_doReset; \
    OV_INST_ksapi_linkObject p_apiLink;

#define OV_CIB_fbcomlib_linkObject \
    OV_CIB_fbcomlib_FBComCommon \
    int is_of_class_fbcomlib_linkObject:1;

#define OV_STATICINSTBODY_fbcomlib_linkObject

#define OV_BIPT_fbcomlib_unlinkObject OV_INSTPTR_fbcomlib_FBComCommon
#define OV_BVPT_fbcomlib_unlinkObject OV_VTBLPTR_fbcomlib_FBComCommon

#define OV_INSTBODY_fbcomlib_unlinkObject \
    OV_INSTBODY_fbcomlib_FBComCommon \
    OV_STRING v_elementPath; \
    OV_BOOL v_doReset; \
    OV_INST_ksapi_unlinkObject p_apiUnlink;

#define OV_CIB_fbcomlib_unlinkObject \
    OV_CIB_fbcomlib_FBComCommon \
    int is_of_class_fbcomlib_unlinkObject:1;

#define OV_STATICINSTBODY_fbcomlib_unlinkObject

OV_TYPEDEF_INSTANCE(fbcomlib_FBComCommon);
OV_TYPEDEF_INSTANCE(fbcomlib_variableOperation);
OV_TYPEDEF_INSTANCE(fbcomlib_setVar);
OV_TYPEDEF_INSTANCE(fbcomlib_getVar);
OV_TYPEDEF_INSTANCE(fbcomlib_pkgVariable);
OV_TYPEDEF_INSTANCE(fbcomlib_pkgGetVariable);
OV_TYPEDEF_INSTANCE(fbcomlib_pkgSetVariable);
OV_TYPEDEF_INSTANCE(fbcomlib_getEPidentifiers);
OV_TYPEDEF_INSTANCE(fbcomlib_createObject);
OV_TYPEDEF_INSTANCE(fbcomlib_deleteObject);
OV_TYPEDEF_INSTANCE(fbcomlib_renameObject);
OV_TYPEDEF_INSTANCE(fbcomlib_linkObject);
OV_TYPEDEF_INSTANCE(fbcomlib_unlinkObject);

#include "fbcomlib.ovf"

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fbcomlib_FBComCommon_constructor;
OV_FNCEXTERN FBCOM_FNC_RESET fbcomlib_FBComCommon_resetAbstract;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fbcomlib_setVar_constructor;
OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_setVar_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_setVar_typemethod;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fbcomlib_getVar_constructor;
OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_getVar_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_getVar_typemethod;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fbcomlib_pkgGetVariable_constructor;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_pkgGetVariable_typemethod;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fbcomlib_pkgSetVariable_constructor;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_pkgSetVariable_typemethod;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fbcomlib_getEPidentifiers_constructor;
OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_getEPidentifiers_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_getEPidentifiers_typemethod;

OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_createObject_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_createObject_typemethod;

OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_deleteObject_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_deleteObject_typemethod;

OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_renameObject_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_renameObject_typemethod;

OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_linkObject_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_linkObject_typemethod;

OV_FNCEXTERN OV_FNC_STARTUP fbcomlib_unlinkObject_startup;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fbcomlib_unlinkObject_typemethod;

#define OV_VTBLBODY_fbcomlib_FBComCommon \
    OV_VTBLBODY_fb_functionblock \
    FBCOM_FNC_RESET* m_resetAbstract;

#define OV_VTBLBODY_fbcomlib_variableOperation \
    OV_VTBLBODY_fbcomlib_FBComCommon

#define OV_VTBLBODY_fbcomlib_setVar \
    OV_VTBLBODY_fbcomlib_variableOperation

#define OV_VTBLBODY_fbcomlib_getVar \
    OV_VTBLBODY_fbcomlib_variableOperation

#define OV_VTBLBODY_fbcomlib_pkgVariable \
    OV_VTBLBODY_fb_functionblock

#define OV_VTBLBODY_fbcomlib_pkgGetVariable \
    OV_VTBLBODY_fbcomlib_pkgVariable

#define OV_VTBLBODY_fbcomlib_pkgSetVariable \
    OV_VTBLBODY_fbcomlib_pkgVariable

#define OV_VTBLBODY_fbcomlib_getEPidentifiers \
    OV_VTBLBODY_fbcomlib_FBComCommon

#define OV_VTBLBODY_fbcomlib_createObject \
    OV_VTBLBODY_fbcomlib_FBComCommon

#define OV_VTBLBODY_fbcomlib_deleteObject \
    OV_VTBLBODY_fbcomlib_FBComCommon

#define OV_VTBLBODY_fbcomlib_renameObject \
    OV_VTBLBODY_fbcomlib_FBComCommon

#define OV_VTBLBODY_fbcomlib_linkObject \
    OV_VTBLBODY_fbcomlib_FBComCommon

#define OV_VTBLBODY_fbcomlib_unlinkObject \
    OV_VTBLBODY_fbcomlib_FBComCommon

OV_TYPEDEF_VTABLE(fbcomlib_FBComCommon);
OV_TYPEDEF_VTABLE(fbcomlib_variableOperation);
OV_TYPEDEF_VTABLE(fbcomlib_setVar);
OV_TYPEDEF_VTABLE(fbcomlib_getVar);
OV_TYPEDEF_VTABLE(fbcomlib_pkgVariable);
OV_TYPEDEF_VTABLE(fbcomlib_pkgGetVariable);
OV_TYPEDEF_VTABLE(fbcomlib_pkgSetVariable);
OV_TYPEDEF_VTABLE(fbcomlib_getEPidentifiers);
OV_TYPEDEF_VTABLE(fbcomlib_createObject);
OV_TYPEDEF_VTABLE(fbcomlib_deleteObject);
OV_TYPEDEF_VTABLE(fbcomlib_renameObject);
OV_TYPEDEF_VTABLE(fbcomlib_linkObject);
OV_TYPEDEF_VTABLE(fbcomlib_unlinkObject);

OV_DLLFNCEXPORT OV_STRING fbcomlib_FBComCommon_host_get(
    OV_INSTPTR_fbcomlib_FBComCommon pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_FBComCommon_host_set(
    OV_INSTPTR_fbcomlib_FBComCommon pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_STRING fbcomlib_FBComCommon_server_get(
    OV_INSTPTR_fbcomlib_FBComCommon pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_FBComCommon_server_set(
    OV_INSTPTR_fbcomlib_FBComCommon pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_STRING fbcomlib_FBComCommon_path_get(
    OV_INSTPTR_fbcomlib_FBComCommon pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_FBComCommon_path_set(
    OV_INSTPTR_fbcomlib_FBComCommon pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_FBComCommon_doSend_get(
    OV_INSTPTR_fbcomlib_FBComCommon pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_FBComCommon_doSend_set(
    OV_INSTPTR_fbcomlib_FBComCommon pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_FBComCommon_doCyclic_get(
    OV_INSTPTR_fbcomlib_FBComCommon pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_FBComCommon_doCyclic_set(
    OV_INSTPTR_fbcomlib_FBComCommon pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_STRING fbcomlib_FBComCommon_stateString_get(
    OV_INSTPTR_fbcomlib_FBComCommon pobj
);

OV_DLLFNCEXPORT OV_INT fbcomlib_FBComCommon_state_get(
    OV_INSTPTR_fbcomlib_FBComCommon pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_FBComCommon_state_set(
    OV_INSTPTR_fbcomlib_FBComCommon pobj,
    const OV_INT value
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_setVar_sendVar_set(
    OV_INSTPTR_fbcomlib_setVar pobj,
    const OV_ANY *pvalue
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_setVar_doReset_get(
    OV_INSTPTR_fbcomlib_setVar pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_setVar_doReset_set(
    OV_INSTPTR_fbcomlib_setVar pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_getVar_doReset_get(
    OV_INSTPTR_fbcomlib_getVar pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_getVar_doReset_set(
    OV_INSTPTR_fbcomlib_getVar pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_pkgVariable_path_set(
    OV_INSTPTR_fbcomlib_pkgVariable pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_getEPidentifiers_doReset_get(
    OV_INSTPTR_fbcomlib_getEPidentifiers pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_getEPidentifiers_doReset_set(
    OV_INSTPTR_fbcomlib_getEPidentifiers pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_createObject_doReset_get(
    OV_INSTPTR_fbcomlib_createObject pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_createObject_doReset_set(
    OV_INSTPTR_fbcomlib_createObject pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_deleteObject_doReset_get(
    OV_INSTPTR_fbcomlib_deleteObject pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_deleteObject_doReset_set(
    OV_INSTPTR_fbcomlib_deleteObject pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_renameObject_doReset_get(
    OV_INSTPTR_fbcomlib_renameObject pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_renameObject_doReset_set(
    OV_INSTPTR_fbcomlib_renameObject pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_linkObject_doReset_get(
    OV_INSTPTR_fbcomlib_linkObject pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_linkObject_doReset_set(
    OV_INSTPTR_fbcomlib_linkObject pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_BOOL fbcomlib_unlinkObject_doReset_get(
    OV_INSTPTR_fbcomlib_unlinkObject pobj
);

OV_DLLFNCEXPORT OV_RESULT fbcomlib_unlinkObject_doReset_set(
    OV_INSTPTR_fbcomlib_unlinkObject pobj,
    const OV_BOOL value
);

OV_DECL_LINK(fbcomlib_PkgVar);
OV_DECL_UNLINK(fbcomlib_PkgVar);
OV_DECL_GETACCESS(fbcomlib_PkgVar);

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_FBComCommon;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_FBComCommon;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_variableOperation;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_variableOperation;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_setVar;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_setVar;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_getVar;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_getVar;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_pkgVariable;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_pkgVariable;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_pkgGetVariable;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_pkgGetVariable;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_pkgSetVariable;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_pkgSetVariable;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_getEPidentifiers;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_getEPidentifiers;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_createObject;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_createObject;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_deleteObject;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_deleteObject;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_renameObject;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_renameObject;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_linkObject;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_linkObject;

extern OV_CLASS_DEF OV_CLASS_DEF_fbcomlib_unlinkObject;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fbcomlib_unlinkObject;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_fbcomlib_PkgVar;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_fbcomlib_PkgVar;

extern OV_LIBRARY_DEF OV_LIBRARY_DEF_fbcomlib;

OV_RESULT ov_library_setglobalvars_fbcomlib(void);

OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_fbcomlib(void);

#undef OV_VAREXTERN
#undef OV_FNCEXTERN

#ifdef __cplusplus
}
#endif

#endif

/*
*   End of file
*/
