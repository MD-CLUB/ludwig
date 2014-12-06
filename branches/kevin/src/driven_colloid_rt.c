
#include <assert.h>

#include "coords.h"
#include "driven_colloid.h"
#include "driven_colloid_rt.h"

/*****************************************************************************
 *
 *  driven_colloid_runtime
 *
 *****************************************************************************/

int driven_colloid_runtime(rt_t * rt) {

  int n;
  double f0 = 0.0;

  assert(rt);

  n = rt_double_parameter(rt, "driving_force_magnitude", &f0);
  
  if (n == 1)driven_colloid_fmod_set(f0);
  
  f0 = driven_colloid_fmod_get();
  info("\n");
  info("Colloid driving force magnitude: %12.5e\n", f0);

  return 0;
}
