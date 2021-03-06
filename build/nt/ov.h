/*
*   This file was generated by the ACPLT/OV C-Code Generator.
*
*   C-Code Generator version: 1.6.4
*   ACPLT/OV library version: 2.0.0
*   Date of file generation:   1-Jun-2016 (15:12:01)
*
*   DO NOT EDIT THIS FILE!
*/

#ifndef OV_LIBRARY_ov_H_INCLUDED
#define OV_LIBRARY_ov_H_INCLUDED

#include "libov/ov_library.h"
#include "libov/ov_structure.h"
#include "libov/ov_class.h"
#include "libov/ov_association.h"
#include "libov/ov_variable.h"
#include "libov/ov_part.h"
#include "libov/ov_operation.h"

#include "ov.ovt"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OV_COMPILE_LIBRARY_ov
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

#define OV_PPT_ov_containment struct OV_INST_ov_domain*
#define OV_CPT_ov_containment struct OV_INST_ov_object*
#define OV_PCI_ov_containment is_of_class_ov_domain
#define OV_CCI_ov_containment is_of_class_ov_object

#define OV_PPT_ov_instantiation struct OV_INST_ov_class*
#define OV_CPT_ov_instantiation struct OV_INST_ov_object*
#define OV_PCI_ov_instantiation is_of_class_ov_class
#define OV_CCI_ov_instantiation is_of_class_ov_object

#define OV_PPT_ov_inheritance struct OV_INST_ov_class*
#define OV_CPT_ov_inheritance struct OV_INST_ov_class*
#define OV_PCI_ov_inheritance is_of_class_ov_class
#define OV_CCI_ov_inheritance is_of_class_ov_class

#define OV_PPT_ov_parentrelationship struct OV_INST_ov_class*
#define OV_CPT_ov_parentrelationship struct OV_INST_ov_association*
#define OV_PCI_ov_parentrelationship is_of_class_ov_class
#define OV_CCI_ov_parentrelationship is_of_class_ov_association

#define OV_PPT_ov_childrelationship struct OV_INST_ov_class*
#define OV_CPT_ov_childrelationship struct OV_INST_ov_association*
#define OV_PCI_ov_childrelationship is_of_class_ov_class
#define OV_CCI_ov_childrelationship is_of_class_ov_association

#define OV_PPT_ov_construction struct OV_INST_ov_structure*
#define OV_CPT_ov_construction struct OV_INST_ov_variable*
#define OV_PCI_ov_construction is_of_class_ov_structure
#define OV_CCI_ov_construction is_of_class_ov_variable

#define OV_PPT_ov_embedment struct OV_INST_ov_class*
#define OV_CPT_ov_embedment struct OV_INST_ov_part*
#define OV_PCI_ov_embedment is_of_class_ov_class
#define OV_CCI_ov_embedment is_of_class_ov_part

#define OV_INSTBODY_ov_object \
    OV_STRING v_identifier; \
    OV_UINT v_idH; \
    OV_UINT v_idL; \
    OV_TIME v_creationtime; \
    OV_INSTPTR v_pouterobject; \
    OV_INT v_objectstate; \
    OV_ATBLPTR v_linktable;

#define OV_CIB_ov_object \
    int is_of_class_ov_object:1;

#define OV_STATICINSTBODY_ov_object

#define OV_BIPT_ov_domain OV_INSTPTR_ov_object
#define OV_BVPT_ov_domain OV_VTBLPTR_ov_object

#define OV_INSTBODY_ov_domain \
    OV_INSTBODY_ov_object

#define OV_CIB_ov_domain \
    OV_CIB_ov_object \
    int is_of_class_ov_domain:1;

#define OV_STATICINSTBODY_ov_domain

#define OV_BIPT_ov_library OV_INSTPTR_ov_domain
#define OV_BVPT_ov_library OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ov_library \
    OV_INSTBODY_ov_domain \
    OV_STRING v_version; \
    OV_STRING v_author; \
    OV_STRING v_copyright; \
    OV_STRING v_comment; \
    OV_DLLHANDLE v_handle;

#define OV_CIB_ov_library \
    OV_CIB_ov_domain \
    int is_of_class_ov_library:1;

#define OV_STATICINSTBODY_ov_library

#define OV_BIPT_ov_structure OV_INSTPTR_ov_domain
#define OV_BVPT_ov_structure OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ov_structure \
    OV_INSTBODY_ov_domain \
    OV_UINT v_size;

#define OV_CIB_ov_structure \
    OV_CIB_ov_domain \
    int is_of_class_ov_structure:1;

#define OV_STATICINSTBODY_ov_structure

#define OV_BIPT_ov_class OV_INSTPTR_ov_domain
#define OV_BVPT_ov_class OV_VTBLPTR_ov_domain

#define OV_INSTBODY_ov_class \
    OV_INSTBODY_ov_domain \
    OV_STRING v_comment; \
    OV_UINT v_flags; \
    OV_INT v_classprops; \
    OV_UINT v_size; \
    OV_UINT v_staticsize; \
    OV_UINT v_linktablesize; \
    OV_VTBLPTR v_pvtable;

#define OV_CIB_ov_class \
    OV_CIB_ov_domain \
    int is_of_class_ov_class:1;

#define OV_STATICINSTBODY_ov_class

#define OV_BIPT_ov_association OV_INSTPTR_ov_object
#define OV_BVPT_ov_association OV_VTBLPTR_ov_object

#define OV_INSTBODY_ov_association \
    OV_INSTBODY_ov_object \
    OV_INT v_assoctype; \
    OV_INT v_assocprops; \
    OV_STRING v_childrolename; \
    OV_STRING v_parentrolename; \
    OV_UINT v_parentoffset; \
    OV_UINT v_childoffset; \
    OV_STRING v_parentcomment; \
    OV_STRING v_childcomment; \
    OV_UINT v_parentflags; \
    OV_UINT v_childflags; \
    OV_FNCPTR_LINK v_linkfnc; \
    OV_FNCPTR_UNLINK v_unlinkfnc; \
    OV_FNCPTR_GETACCESS v_getaccessfnc;

#define OV_CIB_ov_association \
    OV_CIB_ov_object \
    int is_of_class_ov_association:1;

#define OV_STATICINSTBODY_ov_association

#define OV_BIPT_ov_variable OV_INSTPTR_ov_object
#define OV_BVPT_ov_variable OV_VTBLPTR_ov_object

#define OV_INSTBODY_ov_variable \
    OV_INSTBODY_ov_object \
    OV_INT v_vartype; \
    OV_STRING v_ctypename; \
    OV_INT v_varprops; \
    OV_UINT v_veclen; \
    OV_STRING v_comment; \
    OV_UINT v_flags; \
    OV_STRING v_techunit; \
    OV_ANY v_initialvalue; \
    OV_UINT v_size; \
    OV_UINT v_offset; \
    OV_FNCPTR_GET v_getfnc; \
    OV_FNCPTR_SET v_setfnc;

#define OV_CIB_ov_variable \
    OV_CIB_ov_object \
    int is_of_class_ov_variable:1;

#define OV_STATICINSTBODY_ov_variable

#define OV_BIPT_ov_part OV_INSTPTR_ov_object
#define OV_BVPT_ov_part OV_VTBLPTR_ov_object

#define OV_INSTBODY_ov_part \
    OV_INSTBODY_ov_object \
    OV_UINT v_offset; \
    OV_UINT v_flags;

#define OV_CIB_ov_part \
    OV_CIB_ov_object \
    int is_of_class_ov_part:1;

#define OV_STATICINSTBODY_ov_part

#define OV_BIPT_ov_operation OV_INSTPTR_ov_object
#define OV_BVPT_ov_operation OV_VTBLPTR_ov_object

#define OV_INSTBODY_ov_operation \
    OV_INSTBODY_ov_object \
    OV_INT v_opprops; \
    OV_STRING v_cfnctypename;

#define OV_CIB_ov_operation \
    OV_CIB_ov_object \
    int is_of_class_ov_operation:1;

#define OV_STATICINSTBODY_ov_operation

OV_TYPEDEF_INSTANCE(ov_object);
OV_TYPEDEF_INSTANCE(ov_domain);
OV_TYPEDEF_INSTANCE(ov_library);
OV_TYPEDEF_INSTANCE(ov_structure);
OV_TYPEDEF_INSTANCE(ov_class);
OV_TYPEDEF_INSTANCE(ov_association);
OV_TYPEDEF_INSTANCE(ov_variable);
OV_TYPEDEF_INSTANCE(ov_part);
OV_TYPEDEF_INSTANCE(ov_operation);

#include "ov.ovf"

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ov_object_constructor;
OV_FNCEXTERN OV_FNC_CHECKINIT ov_object_checkinit;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ov_object_destructor;
OV_FNCEXTERN OV_FNC_STARTUP ov_object_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN ov_object_shutdown;
OV_FNCEXTERN OV_FNC_RENAME ov_object_rename;
OV_FNCEXTERN OV_FNC_GETACCESS ov_object_getaccess;
OV_FNCEXTERN OV_FNC_GETFLAGS ov_object_getflags;
OV_FNCEXTERN OV_FNC_GETCOMMENT ov_object_getcomment;
OV_FNCEXTERN OV_FNC_GETTECHUNIT ov_object_gettechunit;
OV_FNCEXTERN OV_FNC_GETVAR ov_object_getvar;
OV_FNCEXTERN OV_FNC_SETVAR ov_object_setvar;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR ov_library_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR ov_library_destructor;

#define OV_VTBLBODY_ov_object \
    OV_FNC_CONSTRUCTOR* m_constructor; \
    OV_FNC_CHECKINIT* m_checkinit; \
    OV_FNC_DESTRUCTOR* m_destructor; \
    OV_FNC_STARTUP* m_startup; \
    OV_FNC_SHUTDOWN* m_shutdown; \
    OV_FNC_RENAME* m_rename; \
    OV_FNC_GETACCESS* m_getaccess; \
    OV_FNC_GETFLAGS* m_getflags; \
    OV_FNC_GETCOMMENT* m_getcomment; \
    OV_FNC_GETTECHUNIT* m_gettechunit; \
    OV_FNC_GETVAR* m_getvar; \
    OV_FNC_SETVAR* m_setvar;

#define OV_VTBLBODY_ov_domain \
    OV_VTBLBODY_ov_object

#define OV_VTBLBODY_ov_library \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_ov_structure \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_ov_class \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_ov_association \
    OV_VTBLBODY_ov_object

#define OV_VTBLBODY_ov_variable \
    OV_VTBLBODY_ov_object

#define OV_VTBLBODY_ov_part \
    OV_VTBLBODY_ov_object

#define OV_VTBLBODY_ov_operation \
    OV_VTBLBODY_ov_object

OV_TYPEDEF_VTABLE(ov_object);
OV_TYPEDEF_VTABLE(ov_domain);
OV_TYPEDEF_VTABLE(ov_library);
OV_TYPEDEF_VTABLE(ov_structure);
OV_TYPEDEF_VTABLE(ov_class);
OV_TYPEDEF_VTABLE(ov_association);
OV_TYPEDEF_VTABLE(ov_variable);
OV_TYPEDEF_VTABLE(ov_part);
OV_TYPEDEF_VTABLE(ov_operation);

OV_DLLFNCEXPORT OV_UINT ov_object_idH_get(
    OV_INSTPTR_ov_object pobj
);

OV_DLLFNCEXPORT OV_RESULT ov_object_idH_set(
    OV_INSTPTR_ov_object pobj,
    const OV_UINT value
);

OV_DLLFNCEXPORT OV_UINT ov_object_idL_get(
    OV_INSTPTR_ov_object pobj
);

OV_DLLFNCEXPORT OV_RESULT ov_object_idL_set(
    OV_INSTPTR_ov_object pobj,
    const OV_UINT value
);

OV_DLLFNCEXPORT OV_STRING ov_library_version_get(
    OV_INSTPTR_ov_library pobj
);

OV_DLLFNCEXPORT OV_STRING ov_library_author_get(
    OV_INSTPTR_ov_library pobj
);

OV_DLLFNCEXPORT OV_STRING ov_library_copyright_get(
    OV_INSTPTR_ov_library pobj
);

OV_DLLFNCEXPORT OV_STRING ov_library_comment_get(
    OV_INSTPTR_ov_library pobj
);

OV_DLLFNCEXPORT OV_STRING ov_class_comment_get(
    OV_INSTPTR_ov_class pobj
);

OV_DLLFNCEXPORT OV_UINT ov_class_flags_get(
    OV_INSTPTR_ov_class pobj
);

OV_DLLFNCEXPORT OV_INT ov_class_classprops_get(
    OV_INSTPTR_ov_class pobj
);

OV_DLLFNCEXPORT OV_UINT ov_class_size_get(
    OV_INSTPTR_ov_class pobj
);

OV_DLLFNCEXPORT OV_UINT ov_class_staticsize_get(
    OV_INSTPTR_ov_class pobj
);

OV_DLLFNCEXPORT OV_UINT ov_class_linktablesize_get(
    OV_INSTPTR_ov_class pobj
);

OV_DLLFNCEXPORT OV_INT ov_association_assoctype_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_INT ov_association_assocprops_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_STRING ov_association_childrolename_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_STRING ov_association_parentrolename_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_UINT ov_association_parentoffset_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_UINT ov_association_childoffset_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_STRING ov_association_parentcomment_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_STRING ov_association_childcomment_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_UINT ov_association_parentflags_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_UINT ov_association_childflags_get(
    OV_INSTPTR_ov_association pobj
);

OV_DLLFNCEXPORT OV_INT ov_variable_vartype_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_STRING ov_variable_ctypename_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_INT ov_variable_varprops_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_UINT ov_variable_veclen_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_STRING ov_variable_comment_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_UINT ov_variable_flags_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_STRING ov_variable_techunit_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_ANY *ov_variable_initialvalue_get(
    OV_INSTPTR_ov_variable pobj
);

OV_DLLFNCEXPORT OV_UINT ov_part_flags_get(
    OV_INSTPTR_ov_part pobj
);

OV_DLLFNCEXPORT OV_INT ov_operation_opprops_get(
    OV_INSTPTR_ov_operation pobj
);

OV_DLLFNCEXPORT OV_STRING ov_operation_cfnctypename_get(
    OV_INSTPTR_ov_operation pobj
);

OV_DECL_LINK(ov_containment);
OV_DECL_UNLINK(ov_containment);
OV_DECL_GETACCESS(ov_containment);

OV_DECL_LINK(ov_instantiation);
OV_DECL_UNLINK(ov_instantiation);
OV_DECL_GETACCESS(ov_instantiation);

OV_DECL_LINK(ov_inheritance);
OV_DECL_UNLINK(ov_inheritance);
OV_DECL_GETACCESS(ov_inheritance);

OV_DECL_LINK(ov_parentrelationship);
OV_DECL_UNLINK(ov_parentrelationship);
OV_DECL_GETACCESS(ov_parentrelationship);

OV_DECL_LINK(ov_childrelationship);
OV_DECL_UNLINK(ov_childrelationship);
OV_DECL_GETACCESS(ov_childrelationship);

OV_DECL_LINK(ov_construction);
OV_DECL_UNLINK(ov_construction);
OV_DECL_GETACCESS(ov_construction);

OV_DECL_LINK(ov_embedment);
OV_DECL_UNLINK(ov_embedment);
OV_DECL_GETACCESS(ov_embedment);

extern OV_CLASS_DEF OV_CLASS_DEF_ov_object;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_object;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_domain;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_domain;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_library;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_library;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_structure;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_structure;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_class;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_class;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_association;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_association;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_variable;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_variable;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_part;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_part;

extern OV_CLASS_DEF OV_CLASS_DEF_ov_operation;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_ov_operation;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ov_containment;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ov_containment;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ov_instantiation;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ov_instantiation;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ov_inheritance;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ov_inheritance;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ov_parentrelationship;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ov_parentrelationship;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ov_childrelationship;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ov_childrelationship;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ov_construction;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ov_construction;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_ov_embedment;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_ov_embedment;

extern OV_LIBRARY_DEF OV_LIBRARY_DEF_ov;

OV_RESULT ov_library_setglobalvars_ov(void);

OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_ov(void);

#undef OV_VAREXTERN
#undef OV_FNCEXTERN

#ifdef __cplusplus
}
#endif

#endif

/*
*   End of file
*/
