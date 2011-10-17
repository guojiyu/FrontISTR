/*=====================================================================*
 *                                                                     *
 *   Software Name : HEC-MW Library for PC-cluster                     *
 *         Version : 2.3                                               *
 *                                                                     *
 *     Last Update : 2007/06/29                                        *
 *        Category : I/O and Utility                                   *
 *                                                                     *
 *            Written by Kazuya Goto (AdvanceSoft)                     *
 *                                                                     *
 *     Contact address :  IIS, The University of Tokyo RSS21 project   *
 *                                                                     *
 *     "Structural Analysis System for General-purpose Coupling        *
 *      Simulations Using High End Computing Middleware (HEC-MW)"      *
 *                                                                     *
 *=====================================================================*/


#ifndef HECMW_MAP_INT_INCLUDED
#define HECMW_MAP_INT_INCLUDED

#include "hecmw_bit_array.h"

struct hecmw_map_int_value {
  int key;
  void *val;
};

struct hecmw_map_int_pair {
  int key;
  int local;
};

struct hecmw_map_int {
  int n_val;
  int max_val;

  struct hecmw_map_int_value *vals;
  struct hecmw_map_int_pair *pairs;

  int checked;
  int sorted;

  struct hecmw_bit_array *mark;

  int iter;

  void (*free_fnc)(void *);
};


extern int HECMW_map_int_init(struct hecmw_map_int *map, void (*free_fnc)(void *));

extern void HECMW_map_int_finalize(struct hecmw_map_int *map);


extern int HECMW_map_int_nval(const struct hecmw_map_int *map);

extern int HECMW_map_int_add(struct hecmw_map_int *map, int key, void *value);

extern int HECMW_map_int_check_dup(struct hecmw_map_int *map);

extern int HECMW_map_int_key2local(const struct hecmw_map_int *map, int key);

extern void *HECMW_map_int_get(const struct hecmw_map_int *map, int key);


extern void HECMW_map_int_iter_init(struct hecmw_map_int *map);

extern int HECMW_map_int_iter_next(struct hecmw_map_int *map, int *key, void **value);


extern int HECMW_map_int_mark_init(struct hecmw_map_int *map);

extern int HECMW_map_int_mark(struct hecmw_map_int *map, int key);

extern int HECMW_map_int_iter_next_unmarked(struct hecmw_map_int *map, int *key, void **value);

extern int HECMW_map_int_del_unmarked(struct hecmw_map_int *map);

#endif /* HECMW_MAP_INT_INCLUDED */
