/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "CoupledForce.h"

template <>
InputParameters
validParams<CoupledForce>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("v", "The coupled variable which provides the force");

  return params;
}

CoupledForce::CoupledForce(const InputParameters & parameters)
  : Kernel(parameters), _v_var(coupled("v")), _v(coupledValue("v"))
{
}

Real
CoupledForce::computeQpResidual()
{
  return -_v[_qp] * _test[_i][_qp];
}

Real
CoupledForce::computeQpJacobian()
{
  return 0;
}

Real
CoupledForce::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var)
    return -_phi[_j][_qp] * _test[_i][_qp];
  return 0.0;
}
