/*********************************************************************
* Rice University Software Distribution License
*
* Copyright (c) 2010, Rice University
* All Rights Reserved.
*
* For a full description see the file named LICENSE.
*
*********************************************************************/

/* Author: Ioan Sucan */

#include "omplapp/apps/SE3ControlPlanning.h"


ompl::base::ScopedState<> ompl::app::SE3ControlPlanning::getDefaultStartState(void) const
{
    base::ScopedState<base::SE3StateSpace> sSE3(getGeometricComponentStateSpace());
    aiVector3D s = getRobotCenter(0);

    sSE3->setX(s.x);
    sSE3->setY(s.y);
    sSE3->setZ(s.z);
    sSE3->rotation().setIdentity();
    return getFullStateFromGeometricComponent(sSE3);
}


ompl::base::ScopedState<> ompl::app::SE3ControlPlanning::getFullStateFromGeometricComponent(const base::ScopedState<> &state) const
{
    base::ScopedState<> st(si_);
    st[7] = 0.0;
    st << state;
    return st;
}

void ompl::app::SE3ControlPlanning::setDefaultBounds()
{
    base::RealVectorBounds bounds(1), cbounds(4);
    bounds.setLow(-1.);
    bounds.setHigh(1.);
    getStateSpace()->as<base::CompoundStateSpace>()->as<base::RealVectorStateSpace>(1)->setBounds(bounds);

    cbounds.setLow(-1.);
    cbounds.setHigh(1.);
    getControlSpace()->as<control::RealVectorControlSpace>()->setBounds(cbounds);
}

void ompl::app::SE3ControlPlanning::propagateForward(const base::State *from, const control::Control *ctrl, const double duration, base::State *result)
{
    // random dynamics; please fill in something reasonable

    const double *c = ctrl->as<control::RealVectorControlSpace::ControlType>()->values;

    result->as<base::CompoundState>()->as<base::SE3StateSpace::StateType>(0)->
        setX(from->as<base::CompoundState>()->as<base::SE3StateSpace::StateType>(0)->getZ() + c[0]);

    result->as<base::CompoundState>()->as<base::SE3StateSpace::StateType>(0)->
        setY(from->as<base::CompoundState>()->as<base::SE3StateSpace::StateType>(0)->getZ() + c[0]);

    result->as<base::CompoundState>()->as<base::SE3StateSpace::StateType>(0)->
        setZ(from->as<base::CompoundState>()->as<base::SE3StateSpace::StateType>(0)->getZ() + c[0]);

    result->as<base::CompoundState>()->as<base::SE3StateSpace::StateType>(0)->rotation().setAxisAngle(c[1], c[2], c[3], 0.1);
    result->as<base::CompoundState>()->as<base::RealVectorStateSpace::StateType>(1)->values[0] = c[0];
}