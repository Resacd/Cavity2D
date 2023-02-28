#pragma once
#include "Node.h"

class ZouHe : public Node
{
private:
	std::vector<double> m_inletVel;
	std::shared_ptr<VelocitySet> velSet;
public:
	static const double PI;
public:
	ZouHe(int coord_x, int coord_y,std::shared_ptr <VelocitySet> velset);
	~ZouHe();

	//double Density() override;
	void ApplyBC() override;
	void SetInletVel(double ux, double uy);
	bool IsCorner();
	bool IsLeftCornerLow();
	bool IsLeftCornerTop();
	bool IsRightCornerLow();
	bool IsRightCornerTop();
	double Density() override;
	virtual std::vector<double> Velocity(std::shared_ptr<VelocitySet> velSet) override;
	const std::shared_ptr<VelocitySet> GetVelSet();
};

