
#pragma once

class Bochka 
{
	float m_V;// в %
	float m_Vcup;
	float m_spirt; // в %
public:
	
	Bochka(float,float);
	~Bochka();
	void Pereliv(Bochka&);
	int getPercent();
	void printV();
};
