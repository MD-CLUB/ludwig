/****************************************************************************
 *
 *  surfactant_rt.c
 *
 *  Run time initialisation for the surfactant free energy.
 *
 *  $Id: surfactant_rt.c,v 1.2 2010-10-15 12:40:03 kevin Exp $
 *
 *  Edinburgh Soft Matter and Statistical Physics Group
 *  and Edinburgh Parallel Computing Centre
 *
 *  Kevin Stratford (kevin@epcc.ed.ac.uk)
 *  (c) The University of Edinburgh (2009)
 *
 ****************************************************************************/

#include <assert.h>

#include "coords.h"
#include "free_energy.h"
#include "surfactant.h"
#include "surfactant_rt.h"

/****************************************************************************
 *
 *  surfactant_run_time
 *
 ****************************************************************************/

int surfactant_run_time(rt_t * rt) {

  double a;
  double b;
  double kappa;
  double kt;
  double epsilon;
  double beta;
  double w;

  assert(rt);

  /* Parameters */

  rt_double_parameter(rt, "surf_A", &a);
  rt_double_parameter(rt, "surf_B", &b);
  rt_double_parameter(rt, "surf_K", &kappa);

  rt_double_parameter(rt, "surf_kt", &kt);
  rt_double_parameter(rt, "surf_epsilon", &epsilon);
  rt_double_parameter(rt, "surf_beta", &beta);
  rt_double_parameter(rt, "surf_w", &w);

  info("Surfactant free energy parameters:\n");
  info("Bulk parameter A      = %12.5e\n", a);
  info("Bulk parameter B      = %12.5e\n", b);
  info("Surface penalty kappa = %12.5e\n", kappa);

  surfactant_fluid_parameters_set(a, b, kappa);

  info("Fluid parameters:\n");
  info("Surface tension       = %12.5e\n", surfactant_interfacial_tension());
  info("Interfacial width     = %12.5e\n", surfactant_interfacial_width());

  info("\n");
  info("Surface adsorption e  = %12.5e\n", epsilon);
  info("Surface psi^2 beta    = %12.5e\n", beta);
  info("Enthalpic term W      = %12.5e\n", w);
  info("Scale energy kT       = %12.5e\n", kt);

  surfactant_parameters_set(kt, epsilon, beta, w);

  info("Langmuir isotherm     = %12.5e\n", surfactant_langmuir_isotherm());

  /* For the surfactant... */

  assert(kappa > 0.0);
  assert(kt > 0.0);
  assert(epsilon > 0.0);
  assert(beta >= 0.0);
  assert(w >= 0.0);

  /* Set free energy function pointers. */

  fe_density_set(surfactant_free_energy_density);
  fe_chemical_potential_set(surfactant_chemical_potential);
  fe_isotropic_pressure_set(surfactant_isotropic_pressure);
  fe_chemical_stress_set(surfactant_chemical_stress);

  return 0;
}
