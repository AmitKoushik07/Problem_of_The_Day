#include<stdio.h>
#define n 15
#define DAYS 30
typedef struct urban_params
{
    float sky_view_factor;
    float veg_density_ratio;
    float pop_density;
    int prev_surface_frac;
    int imprev_surface_frac;
    int status;// 0 for urban and 1 for rural
    float distance[n];// distance of particular station from itself is zero 
}urban_params;

typedef struct weather_params
{
    float temp[DAYS];
    float hum[DAYS];
}weather_params;

typedef struct station
{ 
  urban_params u;
  weather_params w;
}station; 

void highest_heat(station A[], int size, float avg_city_temp)
{
    int count=0, heat_degree_DAYS[n], max;
    for(int i=0; i<n; i++)
    {   count=0;
        for(int j=0; j<DAYS; j++)
        {
            if(A[i].w.temp[j]> avg_city_temp)
            {
                count++;
            }
        }
        heat_degree_DAYS[i]=count;
    }
    max=heat_degree_DAYS[0];
    for(int i=0; i<n; i++)
    {
        if(heat_degree_DAYS[i]>max)
        {
            max=heat_degree_DAYS[i];
        }
    }
    for(int i=0; i<n; i++)
    {
        if(heat_degree_DAYS[i]==max)
        {
            printf("%d",i);
        }
    }
}
int nearest_rural_station(station A[], int size, int option)
{   float min=A[option].u.distance[0];
    int check=0;
    int pos;
    //only one rural station
    while(check!=1)
    {
    
     for(int i=0; i<n && check==0; i++)
     {
        if(A[option].u.distance[i]< min)
        { 
           min=A[option].u.distance[i];
           pos=i;
            
        }
              
     }
     if(A[pos].u.status==0)
     {
            check=0;
     }    
     else
     {
       check=1;
     }
    }
    return pos;
}

void thermally_DAYS(station A[], int size, int option)
{
    int nearest_rural, minimum, day, days[n], count=0;
    nearest_rural=nearest_rural_station(A, size, option);
    float difference[DAYS];
    for(int i=0; i<DAYS; i++)
    {
        difference[i]=A[option].w.temp[i]-A[nearest_rural].w.temp[i];
        
    }
    minimum=difference[0];
    for(int i=0; i<DAYS; i++)
    {
        if(difference[i]<minimum)
        {
            minimum=difference[i];
        }
    }
    for(int i=0; i<DAYS; i++)
    { if(difference[i]==minimum)
      {
        days[count]=i;
        count++;
      }
      
    }
    for(int i=0; i<count; i++)
    {
        printf("%d",  days[i]);
    }
    
}

float avg_temp(station A[], int size, int option)
{   float sum=0;
    for(int i=0; i<DAYS;i++)
    { 
      sum+=A[option].w.temp[i];
    }
    return sum/DAYS;
}
void heat_island_intensity( station A[], int size)
{   int pos, intensity;
    for(int i=0; i<n; i++)
    {
        if(A[i].u.status==0)
        {
           pos=nearest_rural_station(A, size, i);//assuming only one rural station
           intensity=avg_temp(A, size, i)-avg_temp(A, size, pos);
           printf("%d", intensity);
        }
    }
}
void function( station A[],int size,float avg_city_temp)
{
    int i,j,arr[n],t;
    
    for(i=0;i<n;i++)
    {
        arr[i]=i;
    }
    
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(A[j].u.veg_density_ratio>A[j+1].u.veg_density_ratio)
             {
                 t=arr[j];
              arr[j]=arr[j+1];
              arr[j+1]=t;
            }    
        }
    }
    
    for(i=0;i<n;i++)
    {   
        printf("Station %d",i);
        for(j=0;j<DAYS;j++)
        {
        if(A[arr[i]].w.temp[j]>avg_city_temp)
        {
            printf("Day:%d",j);
        }
        }
        printf("\n");
    } 
}
void min_pop_den( station A[],int size,int k)
{
    int i,j,t,arr_station[n];
    float high_temp[n],max;
    
    
    for(i=0;i<n;i++)
    {   max=0;
        for(j=0;j<DAYS;j++)
        {
            if(A[i].w.temp[j]>max)
            {
                max=A[i].w.temp[j];
            }
        }
        high_temp[i]=max;
    }

    for(i=0;i<n;i++)
    {
        arr_station[i]=i;
    }
    
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(A[j].u.pop_density>A[j+1].u.pop_density)
             {
                 t=arr_station[j];
              arr_station[j]=arr_station[j+1];
              arr_station[j+1]=t;
            }    
            else if(A[j].u.pop_density==A[j+1].u.pop_density)
            {
                if(high_temp[j]>high_temp[j+1])
                {
                    t=arr_station[j];
                    arr_station[j]=arr_station[j+1];
                    arr_station[j+1]=t;
                }
            }    
        }
    }
     
    for(i=0;i<k;i++)
    {
        printf("%d",arr_station[i]);
    }
    
}
int main()
{
    int i,j,k,N,days;
    struct station A[n];
    
    printf("Enter the no of stations.");
    scanf("%d",&N);
    
    printf("Enter the no of DAYS.");
    scanf("%d",&days);
    
    for(i=0;i<N;i++)
    {   
    
    //Urban Parameters
        printf("For station %d:\n",i);
        printf("Urban Parameters.\n");
        printf("Sky View Factor:\n");
        scanf("%f",&A[i].u.sky_view_factor);
        printf("Vegetation Density Ratio:\n");
        scanf("%f",&A[i].u.veg_density_ratio);
        printf("Population Density:\n");
        scanf("%f",&A[i].u.pop_density);
        printf("Pervious Surface Fraction:\n");
        scanf("%d",&A[i].u.prev_surface_frac);
        printf("Impervious Surface Fraction:\n");
        scanf("%d",&A[i].u.imprev_surface_frac);
        printf("Station Status:\n");
        scanf("%d",&A[i].u.status);
        for(j=0;j<N-1;j++)
        {
        printf("Distance between station %d and %d:\n",i,j+1);
        scanf("%f",&A[i].u.distance[j]);
        }
    }   
    //Weather Parameters 
    for(j=0;j<DAYS;j++)
    {
        printf("Air Temperature for day %d:\n",j+1);
        scanf("%f",&A[i].w.temp[j]);    
        printf("Relative Humidity for day %d:\n",j+1);
        scanf("%f",&A[i].w.hum[j]);
    }
    
    return 0;
}
