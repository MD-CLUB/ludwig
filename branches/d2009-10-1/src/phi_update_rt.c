/******************************************************************************
 *
 *  phi_update_rt.c
 *
 *  Initialise the order parameter dynamics update.
 *
 *  There is one feature that is slightly awkward: for full lattice
 *  Boltzmann for binary fluid, no update is set (it's done via the
 *  appropriate collision).
 *
 *  $Id: phi_update_rt.c,v 1.1.2.1 2010-03-26 08:41:50 kevin Exp $
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

#include "pe.h"
#include "runtime.h"
#include "phi_update.h"
#include "phi_cahn_hilliard.h"
#include "leslie_ericksen.h"
#include "blue_phase_beris_edwards.h"

/*****************************************************************************
 *
 *  phi_update_runtime
 *
 *  This could be split up if too ponderous.
 *
 *****************************************************************************/

void phi_update_run_time(void) {

  int n, p;
  char stringfe[FILENAME_MAX];
  char string[FILENAME_MAX];
  double value;

  n = RUN_get_string_parameter("free_energy", stringfe, FILENAME_MAX);

  if (n == 0 || strcmp(stringfe, "none") == 0) {
    /* No order parameter, no update. */
  }
  else {

    info("\n");
    info("Order parameter dynamics\n");
    info("------------------------\n\n");

    if (strcmp(stringfe, "symmetric") == 0) {
      /* Check if we're using full LB */
      RUN_get_string_parameter("phi_finite_difference", string,
			       FILENAME_MAX);
      if (strcmp(string, "yes") == 0) {
	phi_update_set(phi_cahn_hilliard);
	info("Using Cahn-Hilliard solver:\n");
      }
      else {
	info("Using full LB for Cahn-Hilliard:\n");
      }

      /* Mobility (always required) */
      p = RUN_get_double_parameter("mobility", &value);

      if (p == 1) {
	phi_ch_set_mobility(value);
	info("Mobility M            = %12.5e\n", phi_ch_get_mobility());
      }
    }
    else if (strcmp(stringfe, "gelx") == 0) {

      info("Using Leslie-Ericksen solver:\n");
      phi_update_set(leslie_ericksen_update);

      RUN_get_double_parameter("gelx_gamma", &value);
      leslie_ericksen_gamma_set(value);
      info("Rotational diffusion     = %12.5e\n", value);

      RUN_get_double_parameter("gelx_swim", &value);
      leslie_ericksen_swim_set(value);
      info("Self-advection parameter = %12.5e\n", value);
    }
    else if (strcmp(stringfe, "lc_blue_phase") == 0) {

      info("Using Beris-Edwards solver:\n");
      phi_update_set(blue_phase_beris_edwards);

      p = RUN_get_double_parameter("lc_Gamma", &value);
      if (p != 0) {
	blue_phase_be_set_rotational_diffusion(value);
	info("Rotational diffusion constant = %12.5e\n", value);
      }
    }

  }

  return;
}