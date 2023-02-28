#pragma once

#include "VelocitySet.h"
#include "Domain.h"
#include "OutputFile.h"

class Simulation
{
private:
	Domain m_domain;
	double m_relaxation;
private:
	void Collision();
	void Streaming();
	void MovingWallBC();
	void LeftWallBC();
	void RightWallBC();

public:
	Simulation(Domain& domain);
	~Simulation();

	void Iterate();
	void SetRelaxation(double tau);
	void WriteOutput(int iter);
};

