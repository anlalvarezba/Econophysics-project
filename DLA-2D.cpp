#include <random>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>


int main()
{
  int nr=10; //numero de repeticiones para encontrar distribucion tamaños

  float* T=new float [nr]; //guarda los tamaños de los clusters
  float* NR=new float [300]; //suma de los clusters de cada tamaño, debe ser del numero de particulas

	

	for(int i=0; i<nr; i++)
	{
		T[i] = 0.0;
	}


		for(int i=0; i<300; i++)
	{
		NR[i] = 0.0;
	}
  
  for(int c=0; c<nr; c++)
    {
  
	int nsteps = 600;
	int npaths = 300;
	double ran = 0.0;
	double ran2 = 0.0;



	//contar el numero de puntos del cluster
	//reducir particulas y limites
	//correrlo 500 veces y con el conteo de puntos mirar si se distribuyen normalmente
	//ver como se forma el agregado y luego ver como cambia con el desagregado para diferentes ratas de desagregacion


	int limit_x = 20;//0-10
	int limit_y = 20;//0-10


	double psize=0.7;


	int size=1;

	int dg = 0; //numero de particulas desagregadas


	
	float* M=new float [nsteps*npaths];
	float* N=new float [nsteps*npaths];
	float* P=new float [nsteps*npaths*2];
	float* xC=new float [npaths];
	float* yC=new float [npaths];
	float* C=new float [2*npaths];

	xC[0] = 0.0;
	yC[0] = 0.0;


	for(int i=0; i<nsteps*npaths; i++)
	{
		M[i] = 0.0;
		N[i] = 0.0;
	}

	for(int i=0; i<nsteps*npaths*2; i++)
	{
		P[i] = 0.0;
	}


	

	//int seed=2;
	//int seed0=1;
	//int seed1=1;
	//int seed2=1;
	
	//std::mt19937 gen(seed);
	//std::mt19937 gen0(seed0);
	//std::mt19937 gen1(seed1);
	//std::mt19937 gen2(seed2);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::mt19937 gen0(rd());
	std::mt19937 gen1(rd());
	std::mt19937 gen2(rd());


	std::normal_distribution<float> dis{0,1}; //mean and standard deviation

	
	std::uniform_real_distribution<> xdis(-limit_x,limit_x );
	std::uniform_real_distribution<> ydis(-limit_y,limit_y );
	
	for(int i=0; i<npaths; i++)
	{
	  int x=xdis(gen);
	  int y=ydis(gen0);
	  bool aggregated=false;
	  bool almost_aggregated=false;

	  double a = i/10.0;

	  


	 
	  

	  if((x<=-psize*limit_x || x>=psize*limit_x) && (y<=-psize*limit_y || y>=psize*limit_y))
	    {	      
	    	for(int n=0; n<nsteps; n++)
		{
		  
		  if (aggregated)
		    {
		      	M[n+i*nsteps] = 0.0;
			N[n+i*nsteps] = 0.0;
			continue;
		     }
		  
		ran = dis(gen1);
		x += (int)ran;
		

		ran2 = dis(gen2);
		y += (int)ran2;


		if(x>limit_x || x<-limit_x || y>limit_y || y<-limit_y)
		  {
		    i -= 1;
		    break;
		  }

			M[n+i*nsteps] = 1.0*x;
			N[n+i*nsteps] = 1.0*y;

		  for(int j=0; j<size; j++)
		  {
		    if(xC[j]==1.0*x && yC[j]==1.0*y)
		      {
			if(sqrt(pow(M[n+i*nsteps]-M[n+i*nsteps-1],2)+pow(N[n+i*nsteps]-N[n+i*nsteps-1],2))==1)
			{
			  //if(floor(a)==ceil(a)) 
			  //	  {
			  //	      xC[size] = 0.0;
			  //	      yC[size] = 0.0;
			  //	      dg += 1;
			  //	  }
			  //     else
			  //	  {
				    xC[size] = M[n+i*nsteps-1];
			            yC[size] = N[n+i*nsteps-1];
				    //	  }
				aggregated = true;
				size++;
			}
			else
			{			 
				almost_aggregated = true;
			}
			break;
		      }		    		   
		  }

		  if(almost_aggregated)
		    {
		      i -= 1;
		      break;
		    }
		  
		}		
	    }
	  else
	    {
	      i--;
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





        for(int n=0; n<size; n++)
		{
		  C[n]=xC[n];
		}
	for(int n=size; n<2*size; n++)
		{
		  C[n]=yC[n-size];
		}

	
	/*
	for(int j=0; j<nsteps; j++)
		{
		for(int i=j; i<npaths*nsteps; i += nsteps)
			{
			printf("%5.0f %5.0f  ", P[i], P[i + nsteps*npaths]);
			}
		printf (" \n");
		}
	*/



	/////////////

	//T[c]=size-1; //para DLA y ag sin considerar huecos ag
	T[c]=size-dg-1;//para ag considerando huecos


	/////////////////////////////


		//std::ofstream cluster;
		//cluster.open("cluster-datos.txt");
	
		//for(int i=0; i<size; i ++)
		//{
		//cluster << xC[i] << "\t";
		//cluster << yC[i] << std::endl;	
		//} 

		//cluster.close();

	//////////////////////////////////

	//NR[size-2] += 1; //para DLA y ag sin considerar huecos
	NR[size-2-dg] +=1; //para ag considerando huecos

	///////////////////////////////////////

	delete [] M;
	delete [] N;
	delete [] P;
	delete [] xC;
	delete [] yC;
	delete [] C;
    }



  for(int j=0; j<nr; j++)
		{
		printf("%5.0f  ", T[j]);
		printf (" \n");
		}

		std::ofstream sizesnumber;
		sizesnumber.open("sizesnumber-datos.txt");
	
		for(int i=0; i<300; i ++)
		{
		sizesnumber << i+1 << "\t";
		sizesnumber << NR[i] << std::endl;	
		} 

		sizesnumber.close();



  delete [] T;
  delete [] NR;
	

	
}



