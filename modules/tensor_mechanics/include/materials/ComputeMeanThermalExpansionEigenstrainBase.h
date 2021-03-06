/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTEMEANTHERMALEXPANSIONEIGENSTRAINBASE_H
#define COMPUTEMEANTHERMALEXPANSIONEIGENSTRAINBASE_H

#include "ComputeThermalExpansionEigenstrainBase.h"

class ComputeMeanThermalExpansionEigenstrainBase;

template <>
InputParameters validParams<ComputeMeanThermalExpansionEigenstrainBase>();

/**
 * ComputeMeanThermalExpansionEigenstrainBase is a base class for computing the
 * thermal expansion eigenstrain according to a temperature-dependent mean thermal
 * expansion defined in a derived class.  This is defined as the total
 * total linear strain (\f$\delta L / L\f$) at a given temperature relative to a
 * reference temperature at which \f$\delta L = 0\f$.
 *
 * Based on:
 * M. Niffenegger and K. Reichlin. The proper use of thermal expansion coefficients
 * in finite element calculations. Nuclear Engineering and Design, 243:356-359, Feb. 2012.
 */
class ComputeMeanThermalExpansionEigenstrainBase : public ComputeThermalExpansionEigenstrainBase
{
public:
  ComputeMeanThermalExpansionEigenstrainBase(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;

  /*
   * Compute the total thermal strain relative to the stress-free temperature at the
   * current temperature, as well as the current instantaneous thermal expansion coefficient.
   * param thermal_strain    The current total linear thermal strain (\f$\delta L / L\f$)
   * param instantaneous_cte The current instantaneous coefficient of thermal expansion
   *                         (derivative of thermal_strain wrt temperature
   */
  virtual void computeThermalStrain(Real & thermal_strain, Real & instantaneous_cte) override;

  /*
   * Get the reference temperature for the mean thermal expansion relationship.  This is
   * the temperature at which \f$\delta L = 0\f$.
   */
  virtual Real referenceTemperature() = 0;

  /*
   * Compute the total mean thermal expansion relative to the reference temperature.
   * This is the linear thermal strain divided by the temperature difference:
   * \f$\bar{\alpha}=(\delta L / L)/(T - T_{ref})\f$.
   * param temperature  temperature at which this is evaluated
   */
  virtual Real meanThermalExpansionCoefficient(const Real temperature) = 0;

  /*
   * Compute the derivative of the total mean thermal expansion coefficient \f$\bar{\alpha}\f$
   * with respect to temperature, where \f$\bar{\alpha}=(\delta L / L)/(T - T_{ref})\f$.
   * param temperature  temperature at which this is evaluated
   */
  virtual Real meanThermalExpansionCoefficientDerivative(const Real temperature) = 0;

  /// Mean linear thermal expansion coefficient relative to the reference temperature
  /// evaluated at stress_free_temperature.  This is
  /// \f$\bar{\alpha} = (\delta L(T_{sf}) / L) / (T_{sf} - T_{ref})\f$
  /// where \f$T_sf\f$ is the stress-free temperature and \f$T_{ref}\f$ is the reference temperature.
  Real _alphabar_stress_free_temperature;

  /// Thermal expansion relative to the reference temperature evaluated at stress_free_temperature
  /// \f$(\delta L(T_sf) / L)\f$, where \f$T_sf\f$ is the stress-free temperature.
  Real _thexp_stress_free_temperature;
};

#endif // COMPUTEMEANTHERMALEXPANSIONEIGENSTRAINBASE_H
