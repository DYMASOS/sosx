/*
*   This file was generated by the ACPLT/OV C-Code Generator.
*
*   C-Code Generator version: 1.6.4
*   ACPLT/OV library version: 2.0.0
*   Date of file generation:  11-Aug-2016 ( 9:06:49)
*
*   DO NOT EDIT THIS FILE!
*/

#ifndef OV_LIBRARY_fb_H_INCLUDED
#define OV_LIBRARY_fb_H_INCLUDED

#include "libov/ov_library.h"
#include "libov/ov_structure.h"
#include "libov/ov_class.h"
#include "libov/ov_association.h"
#include "libov/ov_variable.h"
#include "libov/ov_part.h"
#include "libov/ov_operation.h"
#include "ov.h"
#include "ksbase.h"

#include "fb.ovt"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OV_COMPILE_LIBRARY_fb
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

#define OV_PPT_fb_variables struct OV_INST_fb_functionchart*
#define OV_CPT_fb_variables struct OV_INST_fb_port*
#define OV_PCI_fb_variables is_of_class_fb_functionchart
#define OV_CCI_fb_variables is_of_class_fb_port

#define OV_PPT_fb_tasklist struct OV_INST_fb_task*
#define OV_CPT_fb_tasklist struct OV_INST_fb_task*
#define OV_PCI_fb_tasklist is_of_class_fb_task
#define OV_CCI_fb_tasklist is_of_class_fb_task

#define OV_PPT_fb_inputconnections struct OV_INST_fb_object*
#define OV_CPT_fb_inputconnections struct OV_INST_fb_connection*
#define OV_PCI_fb_inputconnections is_of_class_fb_object
#define OV_CCI_fb_inputconnections is_of_class_fb_connection

#define OV_PPT_fb_outputconnections struct OV_INST_fb_object*
#define OV_CPT_fb_outputconnections struct OV_INST_fb_connection*
#define OV_PCI_fb_outputconnections is_of_class_fb_object
#define OV_CCI_fb_outputconnections is_of_class_fb_connection

#define OV_BIPT_fb_dbinfoclass OV_INSTPTR_ov_object
#define OV_BVPT_fb_dbinfoclass OV_VTBLPTR_ov_object

#define OV_INSTBODY_fb_dbinfoclass \
    OV_INSTBODY_ov_object \
    OV_INT v_flush; \
    OV_STRING v_command; \
    OV_INT v_connnumber; \
    OV_INT v_instnumber; \
    OV_INT v_tasknumber; \
    OV_STRING v_serversystem; \
    OV_STRING v_version; \
    OV_STRING v_licinfo; \
    OV_STRING v_ticket;

#define OV_CIB_fb_dbinfoclass \
    OV_CIB_ov_object \
    int is_of_class_fb_dbinfoclass:1;

#define OV_STATICINSTBODY_fb_dbinfoclass

#define OV_BIPT_fb_object OV_INSTPTR_ov_domain
#define OV_BVPT_fb_object OV_VTBLPTR_ov_domain

#define OV_INSTBODY_fb_object \
    OV_INSTBODY_ov_domain

#define OV_CIB_fb_object \
    OV_CIB_ov_domain \
    int is_of_class_fb_object:1;

#define OV_STATICINSTBODY_fb_object

#define OV_BIPT_fb_task OV_INSTPTR_fb_object
#define OV_BVPT_fb_task OV_VTBLPTR_fb_object

#define OV_INSTBODY_fb_task \
    OV_INSTBODY_fb_object \
    OV_INT v_actimode; \
    OV_TIME v_proctime; \
    OV_TIME_SPAN v_cyctime; \
    OV_INT v_ErrState; \
    OV_TIME_SPAN v_calctime; \
    OV_INT v_Xpos; \
    OV_INT v_Ypos;

#define OV_CIB_fb_task \
    OV_CIB_fb_object \
    int is_of_class_fb_task:1;

#define OV_STATICINSTBODY_fb_task

#define OV_BIPT_fb_functionblock OV_INSTPTR_fb_task
#define OV_BVPT_fb_functionblock OV_VTBLPTR_fb_task

#define OV_INSTBODY_fb_functionblock \
    OV_INSTBODY_fb_task \
    OV_BOOL v_iexreq; \
    OV_BOOL v_eexreq; \
    OV_TIME_SPAN v_maxcalctime; \
    OV_UINT v_methcount;

#define OV_CIB_fb_functionblock \
    OV_CIB_fb_task \
    int is_of_class_fb_functionblock:1;

#define OV_STATICINSTBODY_fb_functionblock

#define OV_BIPT_fb_connection OV_INSTPTR_ov_object
#define OV_BVPT_fb_connection OV_VTBLPTR_ov_object

#define OV_INSTBODY_fb_connection \
    OV_INSTBODY_ov_object \
    OV_BOOL v_on; \
    OV_STRING v_sourceport; \
    OV_STRING v_targetport; \
    OV_BOOL v_sourcetrig; \
    OV_STRING v_visuallayout; \
    OV_ELEMENT v_sourceelem; \
    OV_ELEMENT v_targetelem;

#define OV_CIB_fb_connection \
    OV_CIB_ov_object \
    int is_of_class_fb_connection:1;

#define OV_STATICINSTBODY_fb_connection

#define OV_BIPT_fb_functionchart OV_INSTPTR_fb_functionblock
#define OV_BVPT_fb_functionchart OV_VTBLPTR_fb_functionblock

#define OV_INSTBODY_fb_functionchart \
    OV_INSTBODY_fb_functionblock \
    OV_INST_fb_task p_intask;

#define OV_CIB_fb_functionchart \
    OV_CIB_fb_functionblock \
    int is_of_class_fb_functionchart:1;

#define OV_STATICINSTBODY_fb_functionchart

#define OV_BIPT_fb_port OV_INSTPTR_fb_object
#define OV_BVPT_fb_port OV_VTBLPTR_fb_object

#define OV_INSTBODY_fb_port \
    OV_INSTBODY_fb_object \
    OV_UINT v_flags; \
    OV_STRING v_unit; \
    OV_STRING v_comment;

#define OV_CIB_fb_port \
    OV_CIB_fb_object \
    int is_of_class_fb_port:1;

#define OV_STATICINSTBODY_fb_port

#define OV_BIPT_fb_boolport OV_INSTPTR_fb_port
#define OV_BVPT_fb_boolport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_boolport \
    OV_INSTBODY_fb_port \
    OV_BOOL v_value;

#define OV_CIB_fb_boolport \
    OV_CIB_fb_port \
    int is_of_class_fb_boolport:1;

#define OV_STATICINSTBODY_fb_boolport

#define OV_BIPT_fb_intport OV_INSTPTR_fb_port
#define OV_BVPT_fb_intport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_intport \
    OV_INSTBODY_fb_port \
    OV_INT v_value;

#define OV_CIB_fb_intport \
    OV_CIB_fb_port \
    int is_of_class_fb_intport:1;

#define OV_STATICINSTBODY_fb_intport

#define OV_BIPT_fb_uintport OV_INSTPTR_fb_port
#define OV_BVPT_fb_uintport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_uintport \
    OV_INSTBODY_fb_port \
    OV_UINT v_value;

#define OV_CIB_fb_uintport \
    OV_CIB_fb_port \
    int is_of_class_fb_uintport:1;

#define OV_STATICINSTBODY_fb_uintport

#define OV_BIPT_fb_singleport OV_INSTPTR_fb_port
#define OV_BVPT_fb_singleport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_singleport \
    OV_INSTBODY_fb_port \
    OV_SINGLE v_value;

#define OV_CIB_fb_singleport \
    OV_CIB_fb_port \
    int is_of_class_fb_singleport:1;

#define OV_STATICINSTBODY_fb_singleport

#define OV_BIPT_fb_doubleport OV_INSTPTR_fb_port
#define OV_BVPT_fb_doubleport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_doubleport \
    OV_INSTBODY_fb_port \
    OV_DOUBLE v_value;

#define OV_CIB_fb_doubleport \
    OV_CIB_fb_port \
    int is_of_class_fb_doubleport:1;

#define OV_STATICINSTBODY_fb_doubleport

#define OV_BIPT_fb_timeport OV_INSTPTR_fb_port
#define OV_BVPT_fb_timeport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_timeport \
    OV_INSTBODY_fb_port \
    OV_TIME v_value;

#define OV_CIB_fb_timeport \
    OV_CIB_fb_port \
    int is_of_class_fb_timeport:1;

#define OV_STATICINSTBODY_fb_timeport

#define OV_BIPT_fb_timespanport OV_INSTPTR_fb_port
#define OV_BVPT_fb_timespanport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_timespanport \
    OV_INSTBODY_fb_port \
    OV_TIME_SPAN v_value;

#define OV_CIB_fb_timespanport \
    OV_CIB_fb_port \
    int is_of_class_fb_timespanport:1;

#define OV_STATICINSTBODY_fb_timespanport

#define OV_BIPT_fb_stringport OV_INSTPTR_fb_port
#define OV_BVPT_fb_stringport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_stringport \
    OV_INSTBODY_fb_port \
    OV_STRING v_value;

#define OV_CIB_fb_stringport \
    OV_CIB_fb_port \
    int is_of_class_fb_stringport:1;

#define OV_STATICINSTBODY_fb_stringport

#define OV_BIPT_fb_anyport OV_INSTPTR_fb_port
#define OV_BVPT_fb_anyport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_anyport \
    OV_INSTBODY_fb_port \
    OV_ANY v_value;

#define OV_CIB_fb_anyport \
    OV_CIB_fb_port \
    int is_of_class_fb_anyport:1;

#define OV_STATICINSTBODY_fb_anyport

#define OV_BIPT_fb_boolvecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_boolvecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_boolvecport \
    OV_INSTBODY_fb_port \
    OV_BOOL_VEC v_value;

#define OV_CIB_fb_boolvecport \
    OV_CIB_fb_port \
    int is_of_class_fb_boolvecport:1;

#define OV_STATICINSTBODY_fb_boolvecport

#define OV_BIPT_fb_intvecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_intvecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_intvecport \
    OV_INSTBODY_fb_port \
    OV_INT_VEC v_value;

#define OV_CIB_fb_intvecport \
    OV_CIB_fb_port \
    int is_of_class_fb_intvecport:1;

#define OV_STATICINSTBODY_fb_intvecport

#define OV_BIPT_fb_uintvecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_uintvecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_uintvecport \
    OV_INSTBODY_fb_port \
    OV_UINT_VEC v_value;

#define OV_CIB_fb_uintvecport \
    OV_CIB_fb_port \
    int is_of_class_fb_uintvecport:1;

#define OV_STATICINSTBODY_fb_uintvecport

#define OV_BIPT_fb_singlevecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_singlevecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_singlevecport \
    OV_INSTBODY_fb_port \
    OV_SINGLE_VEC v_value;

#define OV_CIB_fb_singlevecport \
    OV_CIB_fb_port \
    int is_of_class_fb_singlevecport:1;

#define OV_STATICINSTBODY_fb_singlevecport

#define OV_BIPT_fb_doublevecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_doublevecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_doublevecport \
    OV_INSTBODY_fb_port \
    OV_DOUBLE_VEC v_value;

#define OV_CIB_fb_doublevecport \
    OV_CIB_fb_port \
    int is_of_class_fb_doublevecport:1;

#define OV_STATICINSTBODY_fb_doublevecport

#define OV_BIPT_fb_timevecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_timevecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_timevecport \
    OV_INSTBODY_fb_port \
    OV_TIME_VEC v_value;

#define OV_CIB_fb_timevecport \
    OV_CIB_fb_port \
    int is_of_class_fb_timevecport:1;

#define OV_STATICINSTBODY_fb_timevecport

#define OV_BIPT_fb_timespanvecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_timespanvecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_timespanvecport \
    OV_INSTBODY_fb_port \
    OV_TIME_SPAN_VEC v_value;

#define OV_CIB_fb_timespanvecport \
    OV_CIB_fb_port \
    int is_of_class_fb_timespanvecport:1;

#define OV_STATICINSTBODY_fb_timespanvecport

#define OV_BIPT_fb_stringvecport OV_INSTPTR_fb_port
#define OV_BVPT_fb_stringvecport OV_VTBLPTR_fb_port

#define OV_INSTBODY_fb_stringvecport \
    OV_INSTBODY_fb_port \
    OV_STRING_VEC v_value;

#define OV_CIB_fb_stringvecport \
    OV_CIB_fb_port \
    int is_of_class_fb_stringvecport:1;

#define OV_STATICINSTBODY_fb_stringvecport

OV_TYPEDEF_INSTANCE(fb_dbinfoclass);
OV_TYPEDEF_INSTANCE(fb_object);
OV_TYPEDEF_INSTANCE(fb_task);
OV_TYPEDEF_INSTANCE(fb_functionblock);
OV_TYPEDEF_INSTANCE(fb_connection);
OV_TYPEDEF_INSTANCE(fb_functionchart);
OV_TYPEDEF_INSTANCE(fb_port);
OV_TYPEDEF_INSTANCE(fb_boolport);
OV_TYPEDEF_INSTANCE(fb_intport);
OV_TYPEDEF_INSTANCE(fb_uintport);
OV_TYPEDEF_INSTANCE(fb_singleport);
OV_TYPEDEF_INSTANCE(fb_doubleport);
OV_TYPEDEF_INSTANCE(fb_timeport);
OV_TYPEDEF_INSTANCE(fb_timespanport);
OV_TYPEDEF_INSTANCE(fb_stringport);
OV_TYPEDEF_INSTANCE(fb_anyport);
OV_TYPEDEF_INSTANCE(fb_boolvecport);
OV_TYPEDEF_INSTANCE(fb_intvecport);
OV_TYPEDEF_INSTANCE(fb_uintvecport);
OV_TYPEDEF_INSTANCE(fb_singlevecport);
OV_TYPEDEF_INSTANCE(fb_doublevecport);
OV_TYPEDEF_INSTANCE(fb_timevecport);
OV_TYPEDEF_INSTANCE(fb_timespanvecport);
OV_TYPEDEF_INSTANCE(fb_stringvecport);

#include "fb.ovf"

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fb_dbinfoclass_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR fb_dbinfoclass_destructor;
OV_FNCEXTERN OV_FNC_STARTUP fb_dbinfoclass_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN fb_dbinfoclass_shutdown;
OV_FNCEXTERN OV_FNC_GETACCESS fb_dbinfoclass_getaccess;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fb_object_constructor;
OV_FNCEXTERN OV_FNC_GETFLAGS fb_object_getflags;
OV_FNCEXTERN OV_FNC_GETACCESS fb_object_getaccess;
OV_FNCEXTERN OV_FNC_SETVAR fb_object_setvar;
OV_FNCEXTERN OV_FNC_GETVAR fb_object_getvar;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fb_task_constructor;
OV_FNCEXTERN OV_FNC_DESTRUCTOR fb_task_destructor;
OV_FNCEXTERN OV_FNC_STARTUP fb_task_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN fb_task_shutdown;
OV_FNCEXTERN OV_FNC_GETACCESS fb_task_getaccess;
OV_FNCEXTERN FB_FNC_EXECUTE fb_task_execute;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fb_functionblock_constructor;
OV_FNCEXTERN OV_FNC_CHECKINIT fb_functionblock_checkinit;
OV_FNCEXTERN OV_FNC_DESTRUCTOR fb_functionblock_destructor;
OV_FNCEXTERN OV_FNC_SETVAR fb_functionblock_setvar;
OV_FNCEXTERN OV_FNC_GETVAR fb_functionblock_getvar;
OV_FNCEXTERN OV_FNC_STARTUP fb_functionblock_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN fb_functionblock_shutdown;
OV_FNCEXTERN OV_FNC_GETFLAGS fb_functionblock_getflags;
OV_FNCEXTERN OV_FNC_GETACCESS fb_functionblock_getaccess;
OV_FNCEXTERN FB_FNC_EXECUTE fb_functionblock_execute;
OV_FNCEXTERN FB_FNC_TYPEMETHOD fb_functionblock_typemethod;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fb_connection_constructor;
OV_FNCEXTERN OV_FNC_CHECKINIT fb_connection_checkinit;
OV_FNCEXTERN OV_FNC_DESTRUCTOR fb_connection_destructor;
OV_FNCEXTERN OV_FNC_STARTUP fb_connection_startup;
OV_FNCEXTERN OV_FNC_GETACCESS fb_connection_getaccess;
OV_FNCEXTERN FB_FNC_TRIGGER fb_connection_trigger;
OV_FNCEXTERN FB_FNC_CHECKELEMENTS fb_connection_checkelements;

OV_FNCEXTERN FB_FNC_TYPEMETHOD fb_functionchart_typemethod;
OV_FNCEXTERN FB_FNC_GETPORT fb_functionchart_getport;
OV_FNCEXTERN FB_FNC_SETPORT fb_functionchart_setport;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR fb_port_constructor;
OV_FNCEXTERN OV_FNC_GETFLAGS fb_port_getflags;
OV_FNCEXTERN OV_FNC_GETCOMMENT fb_port_getcomment;
OV_FNCEXTERN OV_FNC_GETTECHUNIT fb_port_gettechunit;
OV_FNCEXTERN OV_FNC_SETVAR fb_port_setvar;

#define OV_VTBLBODY_fb_dbinfoclass \
    OV_VTBLBODY_ov_object

#define OV_VTBLBODY_fb_object \
    OV_VTBLBODY_ov_domain

#define OV_VTBLBODY_fb_task \
    OV_VTBLBODY_fb_object \
    FB_FNC_EXECUTE* m_execute;

#define OV_VTBLBODY_fb_functionblock \
    OV_VTBLBODY_fb_task \
    FB_FNC_TYPEMETHOD* m_typemethod;

#define OV_VTBLBODY_fb_connection \
    OV_VTBLBODY_ov_object \
    FB_FNC_TRIGGER* m_trigger; \
    FB_FNC_CHECKELEMENTS* m_checkelements;

#define OV_VTBLBODY_fb_functionchart \
    OV_VTBLBODY_fb_functionblock \
    FB_FNC_GETPORT* m_getport; \
    FB_FNC_SETPORT* m_setport;

#define OV_VTBLBODY_fb_port \
    OV_VTBLBODY_fb_object

#define OV_VTBLBODY_fb_boolport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_intport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_uintport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_singleport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_doubleport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_timeport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_timespanport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_stringport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_anyport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_boolvecport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_intvecport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_uintvecport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_singlevecport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_doublevecport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_timevecport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_timespanvecport \
    OV_VTBLBODY_fb_port

#define OV_VTBLBODY_fb_stringvecport \
    OV_VTBLBODY_fb_port

OV_TYPEDEF_VTABLE(fb_dbinfoclass);
OV_TYPEDEF_VTABLE(fb_object);
OV_TYPEDEF_VTABLE(fb_task);
OV_TYPEDEF_VTABLE(fb_functionblock);
OV_TYPEDEF_VTABLE(fb_connection);
OV_TYPEDEF_VTABLE(fb_functionchart);
OV_TYPEDEF_VTABLE(fb_port);
OV_TYPEDEF_VTABLE(fb_boolport);
OV_TYPEDEF_VTABLE(fb_intport);
OV_TYPEDEF_VTABLE(fb_uintport);
OV_TYPEDEF_VTABLE(fb_singleport);
OV_TYPEDEF_VTABLE(fb_doubleport);
OV_TYPEDEF_VTABLE(fb_timeport);
OV_TYPEDEF_VTABLE(fb_timespanport);
OV_TYPEDEF_VTABLE(fb_stringport);
OV_TYPEDEF_VTABLE(fb_anyport);
OV_TYPEDEF_VTABLE(fb_boolvecport);
OV_TYPEDEF_VTABLE(fb_intvecport);
OV_TYPEDEF_VTABLE(fb_uintvecport);
OV_TYPEDEF_VTABLE(fb_singlevecport);
OV_TYPEDEF_VTABLE(fb_doublevecport);
OV_TYPEDEF_VTABLE(fb_timevecport);
OV_TYPEDEF_VTABLE(fb_timespanvecport);
OV_TYPEDEF_VTABLE(fb_stringvecport);

OV_DLLFNCEXPORT OV_INT fb_dbinfoclass_flush_get(
    OV_INSTPTR_fb_dbinfoclass pobj
);

OV_DLLFNCEXPORT OV_RESULT fb_dbinfoclass_flush_set(
    OV_INSTPTR_fb_dbinfoclass pobj,
    const OV_INT value
);

OV_DLLFNCEXPORT OV_STRING fb_dbinfoclass_command_get(
    OV_INSTPTR_fb_dbinfoclass pobj
);

OV_DLLFNCEXPORT OV_RESULT fb_dbinfoclass_command_set(
    OV_INSTPTR_fb_dbinfoclass pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_STRING fb_dbinfoclass_version_get(
    OV_INSTPTR_fb_dbinfoclass pobj
);

OV_DLLFNCEXPORT OV_STRING fb_dbinfoclass_licinfo_get(
    OV_INSTPTR_fb_dbinfoclass pobj
);

OV_DLLFNCEXPORT OV_STRING fb_dbinfoclass_ticket_get(
    OV_INSTPTR_fb_dbinfoclass pobj
);

OV_DLLFNCEXPORT OV_RESULT fb_dbinfoclass_ticket_set(
    OV_INSTPTR_fb_dbinfoclass pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_RESULT fb_task_actimode_set(
    OV_INSTPTR_fb_task pobj,
    const OV_INT value
);

OV_DLLFNCEXPORT OV_RESULT fb_task_proctime_set(
    OV_INSTPTR_fb_task pobj,
    const OV_TIME *pvalue
);

OV_DLLFNCEXPORT OV_RESULT fb_task_cyctime_set(
    OV_INSTPTR_fb_task pobj,
    const OV_TIME_SPAN *pvalue
);

OV_DLLFNCEXPORT OV_RESULT fb_connection_on_set(
    OV_INSTPTR_fb_connection pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_RESULT fb_connection_sourceport_set(
    OV_INSTPTR_fb_connection pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_RESULT fb_connection_targetport_set(
    OV_INSTPTR_fb_connection pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_RESULT fb_port_flags_set(
    OV_INSTPTR_fb_port pobj,
    const OV_UINT value
);

OV_DECL_LINK(fb_variables);
OV_DECL_UNLINK(fb_variables);
OV_DECL_GETACCESS(fb_variables);

OV_DECL_LINK(fb_tasklist);
OV_DECL_UNLINK(fb_tasklist);
OV_DECL_GETACCESS(fb_tasklist);

OV_DECL_LINK(fb_inputconnections);
OV_DECL_UNLINK(fb_inputconnections);
OV_DECL_GETACCESS(fb_inputconnections);

OV_DECL_LINK(fb_outputconnections);
OV_DECL_UNLINK(fb_outputconnections);
OV_DECL_GETACCESS(fb_outputconnections);

extern OV_CLASS_DEF OV_CLASS_DEF_fb_dbinfoclass;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_dbinfoclass;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_object;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_object;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_task;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_task;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_functionblock;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_functionblock;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_connection;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_connection;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_functionchart;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_functionchart;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_port;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_port;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_boolport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_boolport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_intport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_intport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_uintport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_uintport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_singleport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_singleport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_doubleport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_doubleport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_timeport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_timeport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_timespanport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_timespanport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_stringport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_stringport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_anyport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_anyport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_boolvecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_boolvecport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_intvecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_intvecport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_uintvecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_uintvecport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_singlevecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_singlevecport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_doublevecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_doublevecport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_timevecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_timevecport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_timespanvecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_timespanvecport;

extern OV_CLASS_DEF OV_CLASS_DEF_fb_stringvecport;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_fb_stringvecport;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_fb_variables;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_fb_variables;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_fb_tasklist;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_fb_tasklist;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_fb_inputconnections;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_fb_inputconnections;

extern OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_fb_outputconnections;
OV_VAREXTERN OV_INSTPTR_ov_association passoc_fb_outputconnections;

extern OV_LIBRARY_DEF OV_LIBRARY_DEF_fb;

OV_RESULT ov_library_setglobalvars_fb(void);

OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_fb(void);

#undef OV_VAREXTERN
#undef OV_FNCEXTERN

#ifdef __cplusplus
}
#endif

#endif

/*
*   End of file
*/
