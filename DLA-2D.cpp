#include <random>
#include <iostream>
#include <cstdio>


int main()
{
	int nsteps = 500;
	int npaths = 3;
	double ran = 0.0;


	float* M=new float [nsteps*npaths];
	float* N=new float [nsteps*npaths];
	float* P=new float [nsteps*npaths*2];


	for(int i=0; i<nsteps*npaths; i++)
	{
		M[i] = 0.0;
		N[i] = 0.0;
	}

	for(int i=0; i<nsteps*npaths*2; i++)
	{
		P[i] = 0.0;
	}

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> dis(0.0,1.0);

	for(int i=0; i<npaths; i++)
	{
	int x=0;
	int y=0;
	for(int n=1; n<nsteps; n++)
		{
		ran = dis(gen);
		if(ran<0.25)
			{
			x -= 1;
			}
		else if (ran<0.5)
		     	{
			y -= 1;
			}
		else if (ran<0.75)
		     	{
			x += 1;
			}
		else
			{
			y += 1;
			}
		M[n+i*nsteps] = 1.0*x;
		N[n+i*nsteps] = 1.0*y;
		}
	}
        for(int n=0; n<nsteps*npaths; n++)
		{
		P[n]=M[n];
		}
	for(int n=nsteps*npaths; n<nsteps*npaths*2; n++)
		{
		P[n]=N[n-nsteps*npaths];
		}		
	

	for(int j=0; j<nsteps; j++)
		{
		for(int i=j; i<npaths*nsteps; i += nsteps)
			{
			printf("%5.0f %5.0f  ", P[i], P[i + nsteps*npaths]);
			}
		printf (" \n");
		}
	

	delete [] M;
	delete [] N;
	delete [] P;

	
}
