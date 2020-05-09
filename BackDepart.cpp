// BackDepart.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include "math.h"

#define Width 640
#define Height 480
#define picnum 5
#define blocksize 16
#define T 1700


void main()
{
	FILE *file1,*file2;
	unsigned char* temp1y,* temp1u,* temp1v;
	unsigned char* temp2y,* temp2u,* temp2v;
	
	unsigned char tempy1[Height][Width];

	int i,j,k,lastColumn, lastRow, column, row;
	int s1,s2;

	file1=fopen("E:/≤‚ ‘–Ú¡–/stereo640_480/Toys2_1.yuv","rb");
	file2=fopen("E:/≤‚ ‘–Ú¡–/stereo640_480/TOY_Back.yuv","wb");
	
	lastColumn = Height/blocksize;
	lastRow = Width/blocksize;

	for(k=0;k<picnum;k++)
	{
		temp1y=(unsigned char*)malloc(Width*Height*sizeof(unsigned char*));
		temp1u=(unsigned char*)malloc(Width*Height/4*sizeof(unsigned char*));
		temp1v=(unsigned char*)malloc(Width*Height/4*sizeof(unsigned char*));
		temp2y=(unsigned char*)malloc(Width*Height*sizeof(unsigned char*));
		temp2u=(unsigned char*)malloc(Width*Height/4*sizeof(unsigned char*));
		temp2v=(unsigned char*)malloc(Width*Height/4*sizeof(unsigned char*));



		fread(temp1y,1,Width*Height,file1);
		fread(temp1u,1,Width*Height/4,file1);
		fread(temp1v,1,Width*Height/4,file1);
		

		
		if(k == 0)
			{
				for(j = 0;j < Height;j++)
					for(i = 0;i < Width;i++)
						temp2y[j * Width + i] = temp1y[j * Width + i];
			}
		else
			{
				for(column = 0;column < lastColumn;column ++)
					for(row = 0;row < lastRow;row ++)
					{
						s1 = 0;
						s2 = 0;
						
						for(j = 0;j < blocksize;j++)
							for(i = 0;i < blocksize;i++)
							{
								s1 += tempy1[column * blocksize + j][row * blocksize + i];
								s2 += temp1y[(column * blocksize + j) * Width + row * blocksize + i];
							}
						
						if(abs(s2 - s1) <= T)
							{
								for(j = 0;j < blocksize;j++)
									for(i = 0;i < blocksize;i++)temp2y[(column * blocksize + j) * Width + row * blocksize + i] = 0;
	
							}
						
						else 
							{
								for(j = 0;j < blocksize;j++)
									for(i = 0;i < blocksize;i++)temp2y[(column * blocksize + j) * Width + row * blocksize + i] = 255;
							
							}

					}
				}


		for(j = 0;j < Height;j++)
			for(i = 0;i < Width;i++)
				tempy1[j][i] = temp1y[j * Width + i];
		
		for(j = 0;j < Height/2;j++)
			for(i = 0;i < Width/2;i++)
			{
				temp2u[j * Width/2 + i] = 128;
				temp2v[j * Width/2 + i] = 128;
			}
  


		fwrite(temp2y,1,Width*Height,file2);
		fwrite(temp2u,1,Width*Height/4,file2);
		fwrite(temp2v,1,Width*Height/4,file2);


		free(temp1y);
		free(temp1u);
		free(temp1v);
		free(temp2y);
		free(temp2u);
		free(temp2v);

	
	} 
	
	fclose(file1);
	fclose(file2);

	
}





