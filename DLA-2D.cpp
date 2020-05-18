#include <random>
#include <iostream>
#include <cstdio>


int main()
{
	int nsteps = 50;
	int npaths = 11;
	double ran = 0.0;






	int limit_x = 5;//0-10
	int limit_y = 5;//0-10

	//restringir area donde se crean los puntos y donde no

	double psize=0.7;

	int size=1;


	
	float* M=new float [nsteps*npaths];
	float* N=new float [nsteps*npaths];
	float* P=new float [nsteps*npaths*2];
	float* xC=new float [100];
	float* yC=new float [100];
	float* C=new float [200];

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

	//	for(int i=0; i<2*npaths+2; i++)
	//{
	//	S_cluster[i] = 0.0;
	//}

	

	int seed=9;
	std::mt19937 gen(seed);

	//std::random_device rd;
	//std::mt19937 gen(rd());

	std::uniform_real_distribution<> dis(0.0,1.0);
	//std::normal_distribution<float> d{5,2}; //mean and standard deviation

	std::uniform_real_distribution<> xdis(-limit_x,limit_x );
	std::uniform_real_distribution<> ydis(-limit_y,limit_y );
	
	for(int i=0; i<npaths; i++)
	{
	  int x=xdis(gen);
	  int y=ydis(gen);
	  bool aggregated=false;

	 
	  

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
			xC[size] = M[n+i*nsteps-1];
			yC[size] = N[n+i*nsteps-1];
			aggregated = true;
			size++;
			break;
		      }		    		   
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


	printf ("CLUSTER \n");
	for(int i=0; i<size; i ++)
	  {
	    printf("%5.0f %5.0f \n", xC[i], yC[i]);	
	  }






	
        
	
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
