#include <random>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>


int main()
{
	int nsteps = 600;
	int npaths = 150;
	double ran = 0.0;
	double ran2 = 0.0;



	//hacer desagregado quitando 1 particula de cada 10, con el mismo procedimiento
	//hacer las graficas


	int limit_x = 20;//0-10
	int limit_y = 20;//0-10



	double psize=0.7;

	int size=1;


	
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

	//std::uniform_real_distribution<> dis(0.0,1.0);
	std::normal_distribution<float> dis{0,1}; //mean and standard deviation
	//	std::normal_distribution<float> ydis{0,1};
	
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
		/*
		if(ran<-0.6)
			{
			x -= 2;
			}
		else if(ran<-0.2)
		        {
			x -= -1;
			}
		else if (ran<0.2)
		     	{
			x = x;
			}
		else if (ran<0.6)
		     	{
			x += 1;
			}
		else
			{
			x += 2;
			}
		*/


		ran2 = dis(gen2);
		y += (int)ran2;
		/*
		if(ran2<-0.6)
			{
			y -= 2;
			}
		else if(ran2<-0.2)
		        {
			y -= -1;
			}
		else if (ran2<0.2)
		     	{
			y = y;
			}
		else if (ran2<0.6)
		     	{
			y += 1;
			}
		else
			{
			y += 2;
			}
		*/


		if(x==limit_x || x==-limit_x || y==limit_y || y==-limit_y)
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
			      if(floor(a)==ceil(a))
				{
			            xC[size] = 0.0;
			            yC[size] = 0.0;
				}
			      else
				{
				    xC[size] = M[n+i*nsteps-1];
			            yC[size] = N[n+i*nsteps-1];
				}
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
		  //	  printf("%5.0f cx \n", C[n]);
		}
	for(int n=size; n<2*size; n++)
		{
		  C[n]=yC[n-size];
		  //printf("-");
		  // printf("%5.0f cy \n", C[n]);
		}

	

	for(int j=0; j<nsteps; j++)
		{
		for(int i=j; i<npaths*nsteps; i += nsteps)
			{
			printf("%5.0f %5.0f  ", P[i], P[i + nsteps*npaths]);
			}
		printf (" \n");
		}


	std::ofstream cluster;
	cluster.open("cluster-datos.txt");
	
	for(int i=0; i<size; i ++)
	  {
	    cluster << xC[i] << "\t";
	    cluster << yC[i] << std::endl;	
	  } 

	cluster.close();


	/*
	printf ("CLUSTER \n");
	for(int i=0; i<size; i ++)
	  {
	    printf("%5.0f %5.0f \n", xC[i], yC[i]);	
	  }
	*/
       



	
        
	
	/*	for(int j=0; j<size+1; j++)
	        {
		  printf("%5.0f %5.0f ", S_cluster[j], S_cluster[j+npaths+1]);
		  printf(" \n");
		}
	*/

	delete [] M;
	delete [] N;
	delete [] P;
	delete [] xC;
	delete [] yC;
	delete [] C;

	
}



