#include "ZouHe.h"
#include <cmath>
#include <iostream>


ZouHe::ZouHe(int coord_x, int coord_y,std::shared_ptr <VelocitySet> velset)
	:	Node(coord_x, coord_y)
{
	SetInletVel(0.1,0.0);
	velSet = velset;
}


ZouHe::~ZouHe()
{
}

void ZouHe::ApplyBC()
{
	double density = 1;	 // boundary condition is taken from :  
	double du, u_sqr;
	if (IsLeftCornerLow() == 1)
	{
		m_distributions[1] = m_distributions[3] + 2 / 3 * density * m_inletVel[0];
		m_distributions[2] = m_distributions[4] + 2 / 3 * density * m_inletVel[1];
		m_distributions[5] = m_distributions[7] + 1 / 6 * density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[6] = -density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[8] = density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[0] = density - m_distributions[1] - m_distributions[2] - m_distributions[3] -
			m_distributions[4] - m_distributions[5] - m_distributions[6] - m_distributions[7] - m_distributions[8];
	}
	else if (IsLeftCornerTop() == 1)
	{
		m_distributions[1] = m_distributions[3] + 2 / 3 * density * m_inletVel[0];
		m_distributions[4] = m_distributions[2] + 2 / 3 * density * m_inletVel[1];
		m_distributions[5] = density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[7] = -density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[8] = m_distributions[6] + 1 / 6 * density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[0] = density - m_distributions[1] - m_distributions[2] - m_distributions[3] - m_distributions[4]
			- m_distributions[5] - m_distributions[6] - m_distributions[7] - m_distributions[8];
	}

	if (IsRightCornerLow() == 1)
	{
		m_distributions[1] = m_distributions[3] + 2 / 3 * density * m_inletVel[0];
		m_distributions[2] = m_distributions[4] + 2 / 3 * density * m_inletVel[1];
		m_distributions[5] = m_distributions[7] + 1 / 6 * density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[6] = -density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[8] = density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[0] = density - m_distributions[1] - m_distributions[2] - m_distributions[3] -
			m_distributions[4] - m_distributions[5] - m_distributions[6] - m_distributions[7] - m_distributions[8];
	}
	else if (IsRightCornerTop() == 1)
	{
		m_distributions[1] = m_distributions[3] + 2 / 3 * density * m_inletVel[0];
		m_distributions[4] = m_distributions[2] + 2 / 3 * density * m_inletVel[1];
		m_distributions[5] = density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[7] = -density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[8] = m_distributions[6] + 1 / 6 * density * (m_inletVel[0] + m_inletVel[1]);
		m_distributions[0] = density - m_distributions[1] - m_distributions[2] - m_distributions[3] - m_distributions[4]
			- m_distributions[5] - m_distributions[6] - m_distributions[7] - m_distributions[8];
	}


	else
	{
		//m_distributions[4] = m_distributions[2] - 2 / 3 * density * m_inletVel[1];
		//m_distributions[7] = m_distributions[5] - (density / 6.0) * (m_inletVel[0] + m_inletVel[1]);
		//m_distributions[8] = m_distributions[6] - (density / 6.0) * (-m_inletVel[0] + m_inletVel[1]);


		m_distributions[4] = m_distributions[2] - 2 / 3 * density * m_inletVel[1];
		m_distributions[7] = m_distributions[5] + 0.5 * (m_distributions[1] - m_distributions[3]) - 0.5 * density * m_inletVel[0] - (1.0 / 6) * m_inletVel[1];
		m_distributions[8] = m_distributions[6] - 0.5 * (m_distributions[1] - m_distributions[3]) + 0.5 * density * m_inletVel[0] - (1.0 / 6) * m_inletVel[1];


		//for (int dir = 1; dir < 9; dir++) {

		//	du = m_inletVel[0] * velSet->GetDirection(dir)[0] + m_inletVel[1] * velSet->GetDirection(dir)[1];
		//	u_sqr = m_inletVel[0] * m_inletVel[0] + m_inletVel[1] * m_inletVel[1];
		//	m_distributions[dir] = Equilibrium(velSet, dir);
		//}

	}

}

double ZouHe::Density()
{
	return 1;
}

std::vector<double> ZouHe::Velocity(std::shared_ptr<VelocitySet> velSet)
{
	return m_inletVel;
}

void ZouHe::SetInletVel(double ux, double uy)
{
	m_inletVel.push_back(ux);
	m_inletVel.push_back(uy);
}

bool ZouHe::IsCorner()
{
	int nNeighbours = 0;
	for (auto neighbour : m_neighbours)
		if (neighbour != nullptr)
			nNeighbours++;
	if (nNeighbours > 3)
		return 0;
	else
		return 1;
}

bool ZouHe::IsLeftCornerLow()
{
	if (IsCorner() && y_position == 0 && x_position == 0)
		return 1;
	else
		return 0;
}

bool ZouHe::IsLeftCornerTop()
{
	if (IsCorner() && y_position != 0 && x_position == 0)
		return 1;
	else
		return 0;
}


bool ZouHe::IsRightCornerLow()
{
	if (IsCorner() && y_position != 0 && x_position == 0)
		return 1;
	else
		return 0;
}

bool ZouHe::IsRightCornerTop()
{
	if (IsCorner() && y_position != 0 && x_position != 0)
		return 1;
	else
		return 0;
}

const double ZouHe::PI = 3.1415;
