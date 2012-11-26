/*=====================================================================*
 *                                                                     *
 *   Software Name : HEC-MW Library for PC-cluster                     *
 *         Version : 2.3                                               *
 *                                                                     *
 *     Last Update : 2006/06/01                                        *
 *        Category : I/O and Utility                                   *
 *                                                                     *
 *            Written by Shin'ichi Ezure (RIST)                        *
 *                                                                     *
 *     Contact address :  IIS,The University of Tokyo RSS21 project    *
 *                                                                     *
 *     "Structural Analysis System for General-purpose Coupling        *
 *      Simulations Using High End Computing Middleware (HEC-MW)"      *
 *                                                                     *
 *=====================================================================*/



#ifndef INC_HECMW_MESH_DEFINE
#define INC_HECMW_MESH_DEFINE

#define HECMW_COMMON_E_ALLOCATION 1111111
#define HECMW_COMMON_E_OUT_OF_RANGE 1111112
#define HECMW_COMMON_W_NO_EQN_BLOCK 1111113

/*
 *   element types in HEC-MW
 */
#define HECMW_ETYPE_MAX  3422

#define HECMW_ETYPE_ROD1 111
#define HECMW_ETYPE_ROD2 112
#define HECMW_ETYPE_TRI1 231
#define HECMW_ETYPE_TRI2 232
#define HECMW_ETYPE_TRI22 2322
#define HECMW_ETYPE_QUA1 241
#define HECMW_ETYPE_QUA2 242
#define HECMW_ETYPE_ROD31 301
#define HECMW_ETYPE_TET1 341
#define HECMW_ETYPE_TET2 342
#define HECMW_ETYPE_TET22 3422
#define HECMW_ETYPE_PRI1 351
#define HECMW_ETYPE_PRI2 352
#define HECMW_ETYPE_HEX1 361
#define HECMW_ETYPE_HEX2 362
#define HECMW_ETYPE_PYR1 371
#define HECMW_ETYPE_PYR2 372
#define HECMW_ETYPE_MST1 431
#define HECMW_ETYPE_MST2 432
#define HECMW_ETYPE_MSQ1 441
#define HECMW_ETYPE_MSQ2 442
#define HECMW_ETYPE_JTT1 531
#define HECMW_ETYPE_JTT2 532
#define HECMW_ETYPE_JTQ1 541
#define HECMW_ETYPE_JTQ2 542
#define HECMW_ETYPE_BEM1 611
#define HECMW_ETYPE_BEM2 612
#define HECMW_ETYPE_SHT1 731
#define HECMW_ETYPE_SHT2 732
#define HECMW_ETYPE_SHQ1 741
#define HECMW_ETYPE_SHQ2 742
#define HECMW_ETYPE_SHQ3 743
#define HECMW_ETYPE_LN11 911
#define HECMW_ETYPE_LN12 912
#define HECMW_ETYPE_LN13 913
#define HECMW_ETYPE_LN14 914
#define HECMW_ETYPE_LN15 915
#define HECMW_ETYPE_LN16 916
#define HECMW_ETYPE_LN21 921
#define HECMW_ETYPE_LN22 922
#define HECMW_ETYPE_LN23 923
#define HECMW_ETYPE_LN24 924
#define HECMW_ETYPE_LN25 925
#define HECMW_ETYPE_LN26 926
#define HECMW_ETYPE_LN31 931
#define HECMW_ETYPE_LN32 932
#define HECMW_ETYPE_LN33 933
#define HECMW_ETYPE_LN34 934
#define HECMW_ETYPE_LN35 935
#define HECMW_ETYPE_LN36 936
#define HECMW_ETYPE_LN41 941
#define HECMW_ETYPE_LN42 942
#define HECMW_ETYPE_LN43 943
#define HECMW_ETYPE_LN44 944
#define HECMW_ETYPE_LN45 945
#define HECMW_ETYPE_LN46 946
#define HECMW_ETYPE_LN51 951
#define HECMW_ETYPE_LN52 952
#define HECMW_ETYPE_LN53 953
#define HECMW_ETYPE_LN54 954
#define HECMW_ETYPE_LN55 955
#define HECMW_ETYPE_LN56 956
#define HECMW_ETYPE_LN61 961
#define HECMW_ETYPE_LN62 962
#define HECMW_ETYPE_LN63 963
#define HECMW_ETYPE_LN64 964
#define HECMW_ETYPE_LN65 965
#define HECMW_ETYPE_LN66 966

/*
 *   element types in GeoFEM
 */
#define HECMW_GEOFEM_ETYPE_MAX  722

#define HECMW_GEOFEM_ETYPE_ROD1 111
#define HECMW_GEOFEM_ETYPE_ROD2 112
#define HECMW_GEOFEM_ETYPE_TRI1 211
#define HECMW_GEOFEM_ETYPE_TRI2 212
#define HECMW_GEOFEM_ETYPE_QUA1 221
#define HECMW_GEOFEM_ETYPE_QUA2 222
#define HECMW_GEOFEM_ETYPE_TET1 311
#define HECMW_GEOFEM_ETYPE_TET2 312
#define HECMW_GEOFEM_ETYPE_PRI1 321
#define HECMW_GEOFEM_ETYPE_PRI2 322
#define HECMW_GEOFEM_ETYPE_HEX1 331
#define HECMW_GEOFEM_ETYPE_HEX2 332
#define HECMW_GEOFEM_ETYPE_MST1 411
#define HECMW_GEOFEM_ETYPE_MST2 412
#define HECMW_GEOFEM_ETYPE_MSQ1 421
#define HECMW_GEOFEM_ETYPE_MSQ2 422
#define HECMW_GEOFEM_ETYPE_JTT1 511
#define HECMW_GEOFEM_ETYPE_JTT2 512
#define HECMW_GEOFEM_ETYPE_JTQ1 521
#define HECMW_GEOFEM_ETYPE_JTQ2 522
#define HECMW_GEOFEM_ETYPE_BEM1 611
#define HECMW_GEOFEM_ETYPE_BEM2 612
#define HECMW_GEOFEM_ETYPE_SHT1 711
#define HECMW_GEOFEM_ETYPE_SHT2 712
#define HECMW_GEOFEM_ETYPE_SHQ1 721
#define HECMW_GEOFEM_ETYPE_SHQ2 722

/*
 *   element types in mesh utility
 */
#define HECMW_MESH_ETYPE_MAX  68

#define HECMW_MESH_ETYPE_PNT  0
#define HECMW_MESH_ETYPE_ROD1 1
#define HECMW_MESH_ETYPE_ROD2 2
#define HECMW_MESH_ETYPE_TRI1 3
#define HECMW_MESH_ETYPE_TRI2 4
#define HECMW_MESH_ETYPE_QUA1 5
#define HECMW_MESH_ETYPE_QUA2 6
#define HECMW_MESH_ETYPE_TET1 7
#define HECMW_MESH_ETYPE_TET2 8
#define HECMW_MESH_ETYPE_PRI1 9
#define HECMW_MESH_ETYPE_PRI2 10
#define HECMW_MESH_ETYPE_HEX1 11
#define HECMW_MESH_ETYPE_HEX2 12
#define HECMW_MESH_ETYPE_PYR1 13
#define HECMW_MESH_ETYPE_PYR2 14
#define HECMW_MESH_ETYPE_MST1 15
#define HECMW_MESH_ETYPE_MST2 16
#define HECMW_MESH_ETYPE_MSQ1 17
#define HECMW_MESH_ETYPE_MSQ2 18
#define HECMW_MESH_ETYPE_JTT1 19
#define HECMW_MESH_ETYPE_JTT2 20
#define HECMW_MESH_ETYPE_JTQ1 21
#define HECMW_MESH_ETYPE_JTQ2 22
#define HECMW_MESH_ETYPE_BEM1 23
#define HECMW_MESH_ETYPE_BEM2 24
#define HECMW_MESH_ETYPE_SHT1 25
#define HECMW_MESH_ETYPE_SHT2 26
#define HECMW_MESH_ETYPE_SHQ1 27
#define HECMW_MESH_ETYPE_SHQ2 28
#define HECMW_MESH_ETYPE_SHQ3 68
#define HECMW_MESH_ETYPE_LN11 29
#define HECMW_MESH_ETYPE_LN12 30
#define HECMW_MESH_ETYPE_LN13 31
#define HECMW_MESH_ETYPE_LN14 32
#define HECMW_MESH_ETYPE_LN15 33
#define HECMW_MESH_ETYPE_LN16 34
#define HECMW_MESH_ETYPE_LN21 35
#define HECMW_MESH_ETYPE_LN22 36
#define HECMW_MESH_ETYPE_LN23 37
#define HECMW_MESH_ETYPE_LN24 38
#define HECMW_MESH_ETYPE_LN25 39
#define HECMW_MESH_ETYPE_LN26 40
#define HECMW_MESH_ETYPE_LN31 41
#define HECMW_MESH_ETYPE_LN32 42
#define HECMW_MESH_ETYPE_LN33 43
#define HECMW_MESH_ETYPE_LN34 44
#define HECMW_MESH_ETYPE_LN35 45
#define HECMW_MESH_ETYPE_LN36 46
#define HECMW_MESH_ETYPE_LN41 47
#define HECMW_MESH_ETYPE_LN42 48
#define HECMW_MESH_ETYPE_LN43 49
#define HECMW_MESH_ETYPE_LN44 50
#define HECMW_MESH_ETYPE_LN45 51
#define HECMW_MESH_ETYPE_LN46 52
#define HECMW_MESH_ETYPE_LN51 53
#define HECMW_MESH_ETYPE_LN52 54
#define HECMW_MESH_ETYPE_LN53 55
#define HECMW_MESH_ETYPE_LN54 56
#define HECMW_MESH_ETYPE_LN55 57
#define HECMW_MESH_ETYPE_LN56 58
#define HECMW_MESH_ETYPE_LN61 59
#define HECMW_MESH_ETYPE_LN62 60
#define HECMW_MESH_ETYPE_LN63 61
#define HECMW_MESH_ETYPE_LN64 62
#define HECMW_MESH_ETYPE_LN65 63
#define HECMW_MESH_ETYPE_LN66 64
#define HECMW_MESH_ETYPE_TRI22 65
#define HECMW_MESH_ETYPE_TET22 66
#define HECMW_MESH_ETYPE_ROD31 67

/*
 *   UCD labels
 */
#define HECMW_UCD_LABEL_PNT  "pt"
#define HECMW_UCD_LABEL_ROD1 "line"
#define HECMW_UCD_LABEL_ROD2 "line2"
#define HECMW_UCD_LABEL_TRI1 "tri"
#define HECMW_UCD_LABEL_TRI2 "tri2"
#define HECMW_UCD_LABEL_QUA1 "quad"
#define HECMW_UCD_LABEL_QUA2 "quad2"
#define HECMW_UCD_LABEL_TET1 "tet"
#define HECMW_UCD_LABEL_TET2 "tet2"
#define HECMW_UCD_LABEL_PRI1 "prism"
#define HECMW_UCD_LABEL_PRI2 "prism2"
#define HECMW_UCD_LABEL_HEX1 "hex"
#define HECMW_UCD_LABEL_HEX2 "hex2"
#define HECMW_UCD_LABEL_PYR1 "pyr"
#define HECMW_UCD_LABEL_PYR2 "pyr2"
#define HECMW_UCD_LABEL_MST1 "tet"
#define HECMW_UCD_LABEL_MST2 "tet2"
#define HECMW_UCD_LABEL_MSQ1 "pyr"
#define HECMW_UCD_LABEL_MSQ2 "pyr2"
#define HECMW_UCD_LABEL_JTT1 "prism"
#define HECMW_UCD_LABEL_JTT2 "prism2"
#define HECMW_UCD_LABEL_JTQ1 "hex"
#define HECMW_UCD_LABEL_JTQ2 "hex2"
#define HECMW_UCD_LABEL_BEM1 "line"
#define HECMW_UCD_LABEL_BEM2 "line2"
#define HECMW_UCD_LABEL_SHT1 "tri"
#define HECMW_UCD_LABEL_SHT2 "tri2"
#define HECMW_UCD_LABEL_SHQ1 "quad"
#define HECMW_UCD_LABEL_SHQ2 "quad2"
#define HECMW_UCD_LABEL_LN11 "line"
#define HECMW_UCD_LABEL_LN12 "line"
#define HECMW_UCD_LABEL_LN13 "line"
#define HECMW_UCD_LABEL_LN14 "line"
#define HECMW_UCD_LABEL_LN15 "line"
#define HECMW_UCD_LABEL_LN16 "line"
#define HECMW_UCD_LABEL_LN21 "line"
#define HECMW_UCD_LABEL_LN22 "line"
#define HECMW_UCD_LABEL_LN23 "line"
#define HECMW_UCD_LABEL_LN24 "line"
#define HECMW_UCD_LABEL_LN25 "line"
#define HECMW_UCD_LABEL_LN26 "line"
#define HECMW_UCD_LABEL_LN31 "line"
#define HECMW_UCD_LABEL_LN32 "line"
#define HECMW_UCD_LABEL_LN33 "line"
#define HECMW_UCD_LABEL_LN34 "line"
#define HECMW_UCD_LABEL_LN35 "line"
#define HECMW_UCD_LABEL_LN36 "line"
#define HECMW_UCD_LABEL_LN41 "line"
#define HECMW_UCD_LABEL_LN42 "line"
#define HECMW_UCD_LABEL_LN43 "line"
#define HECMW_UCD_LABEL_LN44 "line"
#define HECMW_UCD_LABEL_LN45 "line"
#define HECMW_UCD_LABEL_LN46 "line"
#define HECMW_UCD_LABEL_LN51 "line"
#define HECMW_UCD_LABEL_LN52 "line"
#define HECMW_UCD_LABEL_LN53 "line"
#define HECMW_UCD_LABEL_LN54 "line"
#define HECMW_UCD_LABEL_LN55 "line"
#define HECMW_UCD_LABEL_LN56 "line"
#define HECMW_UCD_LABEL_LN61 "line"
#define HECMW_UCD_LABEL_LN62 "line"
#define HECMW_UCD_LABEL_LN63 "line"
#define HECMW_UCD_LABEL_LN64 "line"
#define HECMW_UCD_LABEL_LN65 "line"
#define HECMW_UCD_LABEL_LN66 "line"

/*
 *   number of component nodes on finite element
 */
#define HECMW_MAX_NODE_MAX  20

#define HECMW_MAX_NODE_PNT   1
#define HECMW_MAX_NODE_ROD1  2
#define HECMW_MAX_NODE_ROD2  3
#define HECMW_MAX_NODE_TRI1  3
#define HECMW_MAX_NODE_TRI2  6
#define HECMW_MAX_NODE_QUA1  4
#define HECMW_MAX_NODE_QUA2  8
#define HECMW_MAX_NODE_ROD31  2
#define HECMW_MAX_NODE_TET1  4
#define HECMW_MAX_NODE_TET2 10
#define HECMW_MAX_NODE_PRI1  6
#define HECMW_MAX_NODE_PRI2 15
#define HECMW_MAX_NODE_HEX1  8
#define HECMW_MAX_NODE_HEX2 20
#define HECMW_MAX_NODE_PYR1  5
#define HECMW_MAX_NODE_PYR2 13
#define HECMW_MAX_NODE_MST1  4
#define HECMW_MAX_NODE_MST2  7
#define HECMW_MAX_NODE_MSQ1  5
#define HECMW_MAX_NODE_MSQ2  9
#define HECMW_MAX_NODE_JTT1  6
#define HECMW_MAX_NODE_JTT2 12
#define HECMW_MAX_NODE_JTQ1  8
#define HECMW_MAX_NODE_JTQ2 16
#define HECMW_MAX_NODE_BEM1  2
#define HECMW_MAX_NODE_BEM2  3
#define HECMW_MAX_NODE_SHT1  3
#define HECMW_MAX_NODE_SHT2  6
#define HECMW_MAX_NODE_SHQ1  4
#define HECMW_MAX_NODE_SHQ2  8
#define HECMW_MAX_NODE_SHQ3  9
#define HECMW_MAX_NODE_LN11  2
#define HECMW_MAX_NODE_LN12  2
#define HECMW_MAX_NODE_LN13  2
#define HECMW_MAX_NODE_LN14  2
#define HECMW_MAX_NODE_LN15  2
#define HECMW_MAX_NODE_LN16  2
#define HECMW_MAX_NODE_LN21  2
#define HECMW_MAX_NODE_LN22  2
#define HECMW_MAX_NODE_LN23  2
#define HECMW_MAX_NODE_LN24  2
#define HECMW_MAX_NODE_LN25  2
#define HECMW_MAX_NODE_LN26  2
#define HECMW_MAX_NODE_LN31  2
#define HECMW_MAX_NODE_LN32  2
#define HECMW_MAX_NODE_LN33  2
#define HECMW_MAX_NODE_LN34  2
#define HECMW_MAX_NODE_LN35  2
#define HECMW_MAX_NODE_LN36  2
#define HECMW_MAX_NODE_LN41  2
#define HECMW_MAX_NODE_LN42  2
#define HECMW_MAX_NODE_LN43  2
#define HECMW_MAX_NODE_LN44  2
#define HECMW_MAX_NODE_LN45  2
#define HECMW_MAX_NODE_LN46  2
#define HECMW_MAX_NODE_LN51  2
#define HECMW_MAX_NODE_LN52  2
#define HECMW_MAX_NODE_LN53  2
#define HECMW_MAX_NODE_LN54  2
#define HECMW_MAX_NODE_LN55  2
#define HECMW_MAX_NODE_LN56  2
#define HECMW_MAX_NODE_LN61  2
#define HECMW_MAX_NODE_LN62  2
#define HECMW_MAX_NODE_LN63  2
#define HECMW_MAX_NODE_LN64  2
#define HECMW_MAX_NODE_LN65  2
#define HECMW_MAX_NODE_LN66  2

/*
 *   number of component edges on finite element
 */
#define HECMW_MAX_EDGE_MAX  24

#define HECMW_MAX_EDGE_PNT   0
#define HECMW_MAX_EDGE_ROD1  1
#define HECMW_MAX_EDGE_ROD2  2
#define HECMW_MAX_EDGE_TRI1  3
#define HECMW_MAX_EDGE_TRI2  6
#define HECMW_MAX_EDGE_QUA1  4
#define HECMW_MAX_EDGE_QUA2  8
#define HECMW_MAX_EDGE_TET1  6
#define HECMW_MAX_EDGE_TET2 12
#define HECMW_MAX_EDGE_PRI1  9
#define HECMW_MAX_EDGE_PRI2 18
#define HECMW_MAX_EDGE_HEX1 12
#define HECMW_MAX_EDGE_HEX2 24
#define HECMW_MAX_EDGE_PYR1  8
#define HECMW_MAX_EDGE_PYR2 16
#define HECMW_MAX_EDGE_MST1  6
#define HECMW_MAX_EDGE_MST2  9
#define HECMW_MAX_EDGE_MSQ1  8
#define HECMW_MAX_EDGE_MSQ2 12
#define HECMW_MAX_EDGE_JTT1  9
#define HECMW_MAX_EDGE_JTT2 15
#define HECMW_MAX_EDGE_JTQ1 12
#define HECMW_MAX_EDGE_JTQ2 20
#define HECMW_MAX_EDGE_BEM1  1
#define HECMW_MAX_EDGE_BEM2  2
#define HECMW_MAX_EDGE_SHT1  3
#define HECMW_MAX_EDGE_SHT2  6
#define HECMW_MAX_EDGE_SHQ1  4
#define HECMW_MAX_EDGE_SHQ2  8
#define HECMW_MAX_EDGE_LN11  1
#define HECMW_MAX_EDGE_LN12  1
#define HECMW_MAX_EDGE_LN13  1
#define HECMW_MAX_EDGE_LN14  1
#define HECMW_MAX_EDGE_LN15  1
#define HECMW_MAX_EDGE_LN16  1
#define HECMW_MAX_EDGE_LN21  1
#define HECMW_MAX_EDGE_LN22  1
#define HECMW_MAX_EDGE_LN23  1
#define HECMW_MAX_EDGE_LN24  1
#define HECMW_MAX_EDGE_LN25  1
#define HECMW_MAX_EDGE_LN26  1
#define HECMW_MAX_EDGE_LN31  1
#define HECMW_MAX_EDGE_LN32  1
#define HECMW_MAX_EDGE_LN33  1
#define HECMW_MAX_EDGE_LN34  1
#define HECMW_MAX_EDGE_LN35  1
#define HECMW_MAX_EDGE_LN36  1
#define HECMW_MAX_EDGE_LN41  1
#define HECMW_MAX_EDGE_LN42  1
#define HECMW_MAX_EDGE_LN43  1
#define HECMW_MAX_EDGE_LN44  1
#define HECMW_MAX_EDGE_LN45  1
#define HECMW_MAX_EDGE_LN46  1
#define HECMW_MAX_EDGE_LN51  1
#define HECMW_MAX_EDGE_LN52  1
#define HECMW_MAX_EDGE_LN53  1
#define HECMW_MAX_EDGE_LN54  1
#define HECMW_MAX_EDGE_LN55  1
#define HECMW_MAX_EDGE_LN56  1
#define HECMW_MAX_EDGE_LN61  1
#define HECMW_MAX_EDGE_LN62  1
#define HECMW_MAX_EDGE_LN63  1
#define HECMW_MAX_EDGE_LN64  1
#define HECMW_MAX_EDGE_LN65  1
#define HECMW_MAX_EDGE_LN66  1

/*
 *   number of component surfaces on finite element
 */
#define HECMW_MAX_SURF_MAX   6

#define HECMW_MAX_SURF_PNT   0
#define HECMW_MAX_SURF_ROD1  0
#define HECMW_MAX_SURF_ROD2  0
#define HECMW_MAX_SURF_TRI1  3
#define HECMW_MAX_SURF_TRI2  3
#define HECMW_MAX_SURF_QUA1  4
#define HECMW_MAX_SURF_QUA2  4
#define HECMW_MAX_SURF_TET1  4
#define HECMW_MAX_SURF_TET2  4
#define HECMW_MAX_SURF_PRI1  5
#define HECMW_MAX_SURF_PRI2  5
#define HECMW_MAX_SURF_HEX1  6
#define HECMW_MAX_SURF_HEX2  6
#define HECMW_MAX_SURF_PYR1  5
#define HECMW_MAX_SURF_PYR2  5
#define HECMW_MAX_SURF_MST1  1
#define HECMW_MAX_SURF_MST2  1
#define HECMW_MAX_SURF_MSQ1  1
#define HECMW_MAX_SURF_MSQ2  1
#define HECMW_MAX_SURF_JTT1  2
#define HECMW_MAX_SURF_JTT2  2
#define HECMW_MAX_SURF_JTQ1  2
#define HECMW_MAX_SURF_JTQ2  2
#define HECMW_MAX_SURF_BEM1  0
#define HECMW_MAX_SURF_BEM2  0
#define HECMW_MAX_SURF_SHT1  2
#define HECMW_MAX_SURF_SHT2  2
#define HECMW_MAX_SURF_SHQ1  2
#define HECMW_MAX_SURF_SHQ2  2
#define HECMW_MAX_SURF_LN11  0
#define HECMW_MAX_SURF_LN12  0
#define HECMW_MAX_SURF_LN13  0
#define HECMW_MAX_SURF_LN14  0
#define HECMW_MAX_SURF_LN15  0
#define HECMW_MAX_SURF_LN16  0
#define HECMW_MAX_SURF_LN21  0
#define HECMW_MAX_SURF_LN22  0
#define HECMW_MAX_SURF_LN23  0
#define HECMW_MAX_SURF_LN24  0
#define HECMW_MAX_SURF_LN25  0
#define HECMW_MAX_SURF_LN26  0
#define HECMW_MAX_SURF_LN31  0
#define HECMW_MAX_SURF_LN32  0
#define HECMW_MAX_SURF_LN33  0
#define HECMW_MAX_SURF_LN34  0
#define HECMW_MAX_SURF_LN35  0
#define HECMW_MAX_SURF_LN36  0
#define HECMW_MAX_SURF_LN41  0
#define HECMW_MAX_SURF_LN42  0
#define HECMW_MAX_SURF_LN43  0
#define HECMW_MAX_SURF_LN44  0
#define HECMW_MAX_SURF_LN45  0
#define HECMW_MAX_SURF_LN46  0
#define HECMW_MAX_SURF_LN51  0
#define HECMW_MAX_SURF_LN52  0
#define HECMW_MAX_SURF_LN53  0
#define HECMW_MAX_SURF_LN54  0
#define HECMW_MAX_SURF_LN55  0
#define HECMW_MAX_SURF_LN56  0
#define HECMW_MAX_SURF_LN61  0
#define HECMW_MAX_SURF_LN62  0
#define HECMW_MAX_SURF_LN63  0
#define HECMW_MAX_SURF_LN64  0
#define HECMW_MAX_SURF_LN65  0
#define HECMW_MAX_SURF_LN66  0

/*
 *   number of component triangular surfaces on finite element
 */
#define HECMW_MAX_TSUF_MAX   4

#define HECMW_MAX_TSUF_PNT   0
#define HECMW_MAX_TSUF_ROD1  0
#define HECMW_MAX_TSUF_ROD2  0
#define HECMW_MAX_TSUF_TRI1  0
#define HECMW_MAX_TSUF_TRI2  0
#define HECMW_MAX_TSUF_QUA1  0
#define HECMW_MAX_TSUF_QUA2  0
#define HECMW_MAX_TSUF_TET1  4
#define HECMW_MAX_TSUF_TET2  4
#define HECMW_MAX_TSUF_PRI1  2
#define HECMW_MAX_TSUF_PRI2  2
#define HECMW_MAX_TSUF_HEX1  0
#define HECMW_MAX_TSUF_HEX2  0
#define HECMW_MAX_TSUF_PYR1  4
#define HECMW_MAX_TSUF_PYR2  4
#define HECMW_MAX_TSUF_MST1  1
#define HECMW_MAX_TSUF_MST2  1
#define HECMW_MAX_TSUF_MSQ1  0
#define HECMW_MAX_TSUF_MSQ2  0
#define HECMW_MAX_TSUF_JTT1  2
#define HECMW_MAX_TSUF_JTT2  2
#define HECMW_MAX_TSUF_JTQ1  0
#define HECMW_MAX_TSUF_JTQ2  0
#define HECMW_MAX_TSUF_BEM1  0
#define HECMW_MAX_TSUF_BEM2  0
#define HECMW_MAX_TSUF_SHT1  2
#define HECMW_MAX_TSUF_SHT2  2
#define HECMW_MAX_TSUF_SHQ1  0
#define HECMW_MAX_TSUF_SHQ2  0
#define HECMW_MAX_TSUF_LN11  0
#define HECMW_MAX_TSUF_LN12  0
#define HECMW_MAX_TSUF_LN13  0
#define HECMW_MAX_TSUF_LN14  0
#define HECMW_MAX_TSUF_LN15  0
#define HECMW_MAX_TSUF_LN16  0
#define HECMW_MAX_TSUF_LN21  0
#define HECMW_MAX_TSUF_LN22  0
#define HECMW_MAX_TSUF_LN23  0
#define HECMW_MAX_TSUF_LN24  0
#define HECMW_MAX_TSUF_LN25  0
#define HECMW_MAX_TSUF_LN26  0
#define HECMW_MAX_TSUF_LN31  0
#define HECMW_MAX_TSUF_LN32  0
#define HECMW_MAX_TSUF_LN33  0
#define HECMW_MAX_TSUF_LN34  0
#define HECMW_MAX_TSUF_LN35  0
#define HECMW_MAX_TSUF_LN36  0
#define HECMW_MAX_TSUF_LN41  0
#define HECMW_MAX_TSUF_LN42  0
#define HECMW_MAX_TSUF_LN43  0
#define HECMW_MAX_TSUF_LN44  0
#define HECMW_MAX_TSUF_LN45  0
#define HECMW_MAX_TSUF_LN46  0
#define HECMW_MAX_TSUF_LN51  0
#define HECMW_MAX_TSUF_LN52  0
#define HECMW_MAX_TSUF_LN53  0
#define HECMW_MAX_TSUF_LN54  0
#define HECMW_MAX_TSUF_LN55  0
#define HECMW_MAX_TSUF_LN56  0
#define HECMW_MAX_TSUF_LN61  0
#define HECMW_MAX_TSUF_LN62  0
#define HECMW_MAX_TSUF_LN63  0
#define HECMW_MAX_TSUF_LN64  0
#define HECMW_MAX_TSUF_LN65  0
#define HECMW_MAX_TSUF_LN66  0

/*
 *   number of component quadrilateral surfaces on finite element
 */
#define HECMW_MAX_QSUF_MAX   6

#define HECMW_MAX_QSUF_PNT   0
#define HECMW_MAX_QSUF_ROD1  0
#define HECMW_MAX_QSUF_ROD2  0
#define HECMW_MAX_QSUF_TRI1  0
#define HECMW_MAX_QSUF_TRI2  0
#define HECMW_MAX_QSUF_QUA1  0
#define HECMW_MAX_QSUF_QUA2  0
#define HECMW_MAX_QSUF_TET1  0
#define HECMW_MAX_QSUF_TET2  0
#define HECMW_MAX_QSUF_PRI1  3
#define HECMW_MAX_QSUF_PRI2  3
#define HECMW_MAX_QSUF_HEX1  6
#define HECMW_MAX_QSUF_HEX2  6
#define HECMW_MAX_QSUF_PYR1  1
#define HECMW_MAX_QSUF_PYR2  1
#define HECMW_MAX_QSUF_MST1  0
#define HECMW_MAX_QSUF_MST2  0
#define HECMW_MAX_QSUF_MSQ1  1
#define HECMW_MAX_QSUF_MSQ2  1
#define HECMW_MAX_QSUF_JTT1  0
#define HECMW_MAX_QSUF_JTT2  0
#define HECMW_MAX_QSUF_JTQ1  2
#define HECMW_MAX_QSUF_JTQ2  2
#define HECMW_MAX_QSUF_BEM1  0
#define HECMW_MAX_QSUF_BEM2  0
#define HECMW_MAX_QSUF_SHT1  0
#define HECMW_MAX_QSUF_SHT2  0
#define HECMW_MAX_QSUF_SHQ1  2
#define HECMW_MAX_QSUF_SHQ2  2
#define HECMW_MAX_QSUF_LN11  0
#define HECMW_MAX_QSUF_LN12  0
#define HECMW_MAX_QSUF_LN13  0
#define HECMW_MAX_QSUF_LN14  0
#define HECMW_MAX_QSUF_LN15  0
#define HECMW_MAX_QSUF_LN16  0
#define HECMW_MAX_QSUF_LN21  0
#define HECMW_MAX_QSUF_LN22  0
#define HECMW_MAX_QSUF_LN23  0
#define HECMW_MAX_QSUF_LN24  0
#define HECMW_MAX_QSUF_LN25  0
#define HECMW_MAX_QSUF_LN26  0
#define HECMW_MAX_QSUF_LN31  0
#define HECMW_MAX_QSUF_LN32  0
#define HECMW_MAX_QSUF_LN33  0
#define HECMW_MAX_QSUF_LN34  0
#define HECMW_MAX_QSUF_LN35  0
#define HECMW_MAX_QSUF_LN36  0
#define HECMW_MAX_QSUF_LN41  0
#define HECMW_MAX_QSUF_LN42  0
#define HECMW_MAX_QSUF_LN43  0
#define HECMW_MAX_QSUF_LN44  0
#define HECMW_MAX_QSUF_LN45  0
#define HECMW_MAX_QSUF_LN46  0
#define HECMW_MAX_QSUF_LN51  0
#define HECMW_MAX_QSUF_LN52  0
#define HECMW_MAX_QSUF_LN53  0
#define HECMW_MAX_QSUF_LN54  0
#define HECMW_MAX_QSUF_LN55  0
#define HECMW_MAX_QSUF_LN56  0
#define HECMW_MAX_QSUF_LN61  0
#define HECMW_MAX_QSUF_LN62  0
#define HECMW_MAX_QSUF_LN63  0
#define HECMW_MAX_QSUF_LN64  0
#define HECMW_MAX_QSUF_LN65  0
#define HECMW_MAX_QSUF_LN66  0

/*
 *   DOFs
 */
#define HECMW_MESH_NDOFGRP_MAX 3
#define HECMW_MESH_DOF_MAX   6
#define HECMW_MESH_DOF_TOT   3

#define HECMW_MESH_DOF_TWO   2
#define HECMW_MESH_DOF_THREE 3
#define HECMW_MESH_DOF_SIX   6

#endif
