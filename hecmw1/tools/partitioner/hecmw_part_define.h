/*=====================================================================*
 *                                                                     *
 *   Software Name : HEC-MW Library for PC-cluster                     *
 *         Version : 2.3                                               *
 *                                                                     *
 *     Last Update : 2006/06/01                                        *
 *        Category : HEC-MW Utility                                    *
 *                                                                     *
 *            Written by Shin'ichi Ezure (RIST)                        *
 *                                                                     *
 *     Contact address :  IIS,The University of Tokyo RSS21 project    *
 *                                                                     *
 *     "Structural Analysis System for General-purpose Coupling        *
 *      Simulations Using High End Computing Middleware (HEC-MW)"      *
 *                                                                     *
 *=====================================================================*/


#ifndef INC_PART_DEFINE
#define INC_PART_DEFINE

#include "hecmw_util.h"
#include "hecmw_msgno.h"

/* #define HECMW_PART_LOG_LEVEL ( HECMW_LOG_ERROR | HECMW_LOG_WARN | HECMW_LOG_INFO ) */


#define HECMW_PART_LOG_NAME "hecmw_part.log"


#define HECMW_PART_EQUATION_BLOCK_NAME "EQUATION_BLOCK"


#define HECMW_PART_VERBOSE_MODE 0


#define HECMW_PART_SILENT_MODE 0


#define HECMW_PART_TYPE_NODE_BASED 1


#define HECMW_PART_TYPE_ELEMENT_BASED 2


#define HECMW_PART_METHOD_RCB 1


#define HECMW_PART_METHOD_KMETIS 2


#define HECMW_PART_METHOD_PMETIS 3


#define HECMW_PART_RCB_X_AXIS 1


#define HECMW_PART_RCB_Y_AXIS 2


#define HECMW_PART_RCB_Z_AXIS 3


#define HECMW_PART_E_NO_SUCH_FILE       HECMW_PART_E0001


#define HECMW_PART_E_FILE_CLOSE         HECMW_PART_E0002


#define HECMW_PART_E_TOO_LONG_FNAME     HECMW_PART_E0003


#define HECMW_PART_E_NULL_POINTER       HECMW_PART_E0004


#define HECMW_PART_E_INVALID_EOF        HECMW_PART_E0005


#define HECMW_PART_E_INV_ARG            HECMW_PART_E0006


#define HECMW_PART_E_INVALID_TOKEN      HECMW_PART_E0101


#define HECMW_PART_E_CTRL_NO_TYPE       HECMW_PART_E0111


#define HECMW_PART_E_CTRL_TYPE_INVAL    HECMW_PART_E0112


#define HECMW_PART_E_CTRL_TYPE_NOEQ     HECMW_PART_E0113


#define HECMW_PART_E_CTRL_NO_METHOD     HECMW_PART_E0121


#define HECMW_PART_E_CTRL_METHOD_INVAL  HECMW_PART_E0122


#define HECMW_PART_E_CTRL_METHOD_NOEQ   HECMW_PART_E0123


#define HECMW_PART_E_CTRL_NODEF_PMETIS  HECMW_PART_E0124


#define HECMW_PART_E_CTRL_NODEF_KMETIS  HECMW_PART_E0125


#define HECMW_PART_E_CTRL_NO_DOMAIN     HECMW_PART_E0131


#define HECMW_PART_E_CTRL_DOMAIN_INVAL  HECMW_PART_E0132


#define HECMW_PART_E_CTRL_DOMAIN_NOEQ   HECMW_PART_E0133


#define HECMW_PART_E_CTRL_DOMAIN_POW    HECMW_PART_E0134


#define HECMW_PART_E_CTRL_DEPTH_INVAL   HECMW_PART_E0141


#define HECMW_PART_E_CTRL_DEPTH_NOEQ    HECMW_PART_E0142


#define HECMW_PART_E_CTRL_UCD_TOO_LONG  HECMW_PART_E0151


#define HECMW_PART_E_CTRL_UCD_NOEQ      HECMW_PART_E0152


#define HECMW_PART_E_CTRL_UCD_INVAL     HECMW_PART_E0153


#define HECMW_PART_E_CTRL_RCB_INVAL     HECMW_PART_E0161


#define HECMW_PART_E_CTRL_RCB_FEW_DIR   HECMW_PART_E0162


#define HECMW_PART_W_CTRL_RCB_MANY_DIR  HECMW_PART_W0163


#define HECMW_PART_E_CTRL_RCB_NODIR     HECMW_PART_E0164


#define HECMW_PART_W_CTRL_DIR_WORCB     HECMW_PART_W0165


#define HECMW_PART_E_INVALID_PTYPE      HECMW_PART_E0201


#define HECMW_PART_E_INVALID_PMETHOD    HECMW_PART_E0202


#define HECMW_PART_E_INVALID_ETYPE      HECMW_PART_E0203


#define HECMW_PART_E_INVALID_RCB_DIR    HECMW_PART_E0204


#define HECMW_PART_E_INVALID_NDOMAIN    HECMW_PART_E0205


#define HECMW_PART_E_INVALID_PDEPTH     HECMW_PART_E0206


#define HECMW_PART_E_STACK_OVERFLOW     HECMW_PART_E0211


#define HECMW_PART_E_DOMAIN_MIN         HECMW_PART_E0301


#define HECMW_PART_E_DOMAIN_MAX         HECMW_PART_E0302


#define HECMW_PART_E_NNODE_MIN          HECMW_PART_E0311


#define HECMW_PART_E_NNODE_LOWER        HECMW_PART_E0311


#define HECMW_PART_E_NNINT_MIN          HECMW_PART_E0312


#define HECMW_PART_E_NNINT_MAX          HECMW_PART_E0313


#define HECMW_PART_E_NELEM_MIN          HECMW_PART_E0321


#define HECMW_PART_E_NELEM_LOWER        HECMW_PART_E0321


#define HECMW_PART_E_NEINT_MIN          HECMW_PART_E0322


#define HECMW_PART_E_NEINT_MAX          HECMW_PART_E0323


#define HECMW_PART_E_NNEIGHBORPE_LOWER  HECMW_PART_E0331


#define HECMW_PART_E_NEDGECUT_LOWER     HECMW_PART_E0301


#define HECMW_PART_E_NEDGECUTA_LOWER    HECMW_PART_E0301


#define HECMW_PART_W_NO_EQUATIONBLOCK   HECMW_PART_W0401


#define HECMW_PART_E_LOG_INIT_NOT_YET   HECMW_PART_E0501


#define HECMW_PART_W_LOG_INIT_ALREADY   HECMW_PART_W0502

#endif  /* INC_HECMW_PART_DEFINE */
