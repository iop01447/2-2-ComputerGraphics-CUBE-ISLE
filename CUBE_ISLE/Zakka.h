#pragma once
class Zakka
{
public:
	Zakka();
	~Zakka();

	float m_xtrs, m_ytrs, m_ztrs;
	float m_xscl, m_yscl, m_zscl;
	int m_xrot, m_yrot, m_zrot;
	float size;
	int slices;

	void Init();
	void Draw();
};

