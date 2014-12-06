/*****************************************************************************
 *
 *  advection_rt.c
 *
 *  Look at switches associated with advection.
 *
 *  $Id: advection_rt.c,v 1.2 2010-10-15 12:40:02 kevin Exp $
 *
 *  Edinburgh Soft Matter and Statistical Physics Group and
 *  Edinburgh Parallel Computing Centre
 *
 *  Kevin Stratford (kevin@epcc.ed.ac.uk)
 *  (c) 2010 The University of Edinburgh
 *
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "advection.h"
#include "advection_rt.h"

/*****************************************************************************
 *
 *  advection_run_time
 *
 *****************************************************************************/

int advection_run_time(rt_t * rt) {

  int n;
  int order;
  char key1[FILENAME_MAX];

  assert(rt);

  rt_string_parameter(rt, "free_energy", key1, FILENAME_MAX);

  if (strcmp(key1, "none") == 0 || strcmp(key1, "symmetric_lb") == 0) {
    /* No finite difference advection required. */
  }
  else {

    info("\nAdvection scheme order: ");

    n = rt_int_parameter(rt, "fd_advection_scheme_order", &order);

    if (n == 0) {
      advection_order(&order);
      info("%2d (default)\n", order);
    }
    else {
      info("%d\n", order);
      advection_order_set(order);
    }
  }

  return 0;
}
