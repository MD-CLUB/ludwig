/*****************************************************************************
 *
 *  polar_active_rt.h
 *
 *  $Id$
 *
 *  Edinburgh Soft Matter and Statistical Physics Group and
 *  Edinburgh Parallel Computing Centre
 *
 *  Kevin Stratford (kevin@epcc.ed.ac.uk)
 *  (c) 2011 The University of Edinburgh
 *
 *****************************************************************************/

#ifndef POLAR_ACTIVE_RT_H
#define POLAR_ACTIVE_RT_H

#include "runtime.h"
#include "field.h"

int polar_active_run_time(rt_t * rt);
int polar_active_rt_initial_conditions(rt_t * rt, field_t * p);
int polar_active_init_aster(field_t * p);

#endif
