#include "stdafx.h"
#include "online_attack_32.h"
#include "Helper.h"
#include "simeck32.h"
#include <iostream>
#include <time.h>

using namespace std;

int NUMBER_OF_CUBES[10] = {0,0,0,7,7,7,7,7,7,19};

int _out[10][19] = 
{
	{0},{0},{0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{29,3,22,16,30,29,25},
	{24,25,30,25,28,23,16},
	{27,26,19,26,24,29,21,17,27,18,22,21,25,20,26,25,27,25,31}
};
int _size[10][30] = 
{
	{0},{0},{0},
	{4,4,4,5,3,3,4},
	{6,4,6,4,6,8,4},
	{8,9,8,9,10,8,7},
	{8,13,13,13,11,13,12},
	{17,17,15,15,17,15,18},
	{20,20,20,20,20,19,20},
	{25,25,26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27}
};
int _key_index[10][30][26] =
{
	// round 1
	{{0}},
	
	// round 2
	{{0}},
	
	// round 3
	{{0}},

	// round 4
	{{0},{6},{5},{27},{1},{11},{10}},
	
	// round 5
	{{5},{11},{6},{12},{10},{15},{1}},
	
	// round 6
	{{22},{10},{9},{5},{0},{1},{6}},
	
	// round 7
	{{12},{4},{5},{1},{6},{11},{38}},
	
	// round 8
	{{35},{9},{7},{1},{2},{1,19,35},{11}},

	// round 9
	{{10},
	{14,24,25,26,29,37,42,45,46,58},
	{42,47},
	{47},
	{50},
	{61},
	{2,17}
	},

	// round 10
	{{44},{63},{5,20,47,52,56,63},{46,47,63},{40,41,52,57},{35,46,50,51},{58},{49},{20,47},{21},{44,59,60},{41},{34},{48,52},{42,43,54,59},{53,57},{48},{43},{34,40}},
};
int _key_size[10][20] = 
{
	// ROUND 1
	{},

	// ROUND 2
	{},

	// ROUND 3
	{},

	// ROUND 4
	{1,1,1,1,1,1,1},

	// ROUND 5
	{1,1,1,1,1,1,1},

	// ROUND 6
	{1,1,1,1,1,1,1},

	// ROUND 7
	{1,1,1,1,1,1,1},

	// ROUND 8
	{1,1,1,1,1,3,1},

	// ROUND 9
	{1,10,2,1,1,1,2},

	// ROUND 10
	{1,1,6,3,4,4,1,1,2,1,3,1,1,2,4,2,1,1,2}
};

uint64_t _free[10][30] =
{
	// ROUND 1
	{},

	// ROUND 2
	{},

	// ROUND 3
	{},

	// ROUND 4
	{0ull,0ull,0ull,1ull,0ull,0ull,1ull},

	// ROUND 5
	{0ull,0ull,0ull,0ull,0ull,0ull,0ull},

	// ROUND 6
	{1ull,0ull,0ull,0ull,0ull,0ull,1ull},

	// ROUND 7
	{0ull,0ull,0ull,0ull,0ull,0ull,1ull},

	// ROUND 8
	{1ull,1ull,0ull,0ull,0ull,1ull,0ull},

	// ROUND 9
	{0ull,0ull,0ull,1ull,1ull,0ull,0ull},

	// ROUND 10
	{1ull,1ull,1ull,0ull,1ull,0ull,1ull,1ull,1ull,1ull,0ull,0ull,0ull,0ull,1ull,0ull,0ull,0ull,0ull},
};
int cube[10][30][30]=
{
	// ROUND 1 CUBES
	{{0}},

	// ROUND 2 CUBES
	{{0}},

	// ROUND 3 CUBES
	{{0}},

	// ROUND 4 CUBES
	{{11,6,25,26},{31,10,6,9},{9,22,14,27},{0,21,11,6,9},{26,13,5},{22,21,13},{9,10,16,4}},
	
	// ROUND 5 CUBES
	{{11,22,30,26,8,17},{13,6,5,7},{31,20,27,6,4,26},{6,25,12,0},{8,11,20,21,15,10},{26,28,25,5,10,22,17,0},{16,29,26,22}},

	// ROUND 6 CUBES
	{{1,26,15,19,13,27,21,22},{12,6,21,0,23,25,28,3,5},{4,3,27,22,1,15,5,29},{5,10,11,13,24,19,6,8,17},{8,3,23,29,4,22,11,28,17,1},{24,19,5,28,25,13,4,26},{8,9,31,25,16,27,6}},

	// ROUND 7 CUBES
	{{12,0,4,21,8,25,19,30},{10,4,22,25,11,19,8,16,5,28,9,29,17},{20,29,26,24,17,25,3,5,23,31,28,16,6},{19,28,30,22,13,9,23,20,12,25,8,16,21},{16,29,28,3,17,25,15,8,24,19,6},{14,5,3,2,29,21,20,16,24,6,8,28,17},{11,9,30,19,23,17,14,20,15,27,5,13}},

	// ROUND 8 CUBES
	{{22,0,14,2,26,4,19,18,24,13,27,23,3,8,11,9,15},{7,9,18,27,24,13,3,28,6,8,19,11,22,23,10,1,31},{16,24,18,31,25,13,15,9,28,29,11,0,12,21,2},{15,23,18,20,10,11,24,14,13,26,21,2,12,27,8},{13,10,27,30,12,22,19,24,8,20,6,7,26,4,9,3,14},{28,26,29,1,21,13,18,4,20,0,25,22,24,11,19},{16,17,19,31,0,29,6,13,24,20,28,8,18,1,26,5,14,9}},

	// ROUND 9 CUBES
	{{16,22,9,27,2,19,18,8,14,0,29,20,1,23,25,17,28,31,12,21},{29,2,31,1,16,18,3,27,19,22,11,13,17,4,15,14,23,0,7,26},{22,24,17,1,12,23,8,3,7,5,0,6,13,26,19,15,29,28,31,21},{1,30,26,11,29,13,17,12,18,5,3,25,24,31,23,4,28,0,14,10},{26,31,16,9,15,28,23,8,10,2,5,12,6,18,21,19,0,20,7,3},{26,21,28,27,24,3,13,30,1,12,10,25,29,8,5,4,16,22,0},{26,27,5,7,8,19,25,17,9,11,21,24,30,10,20,22,29,23,14,15}},

	// ROUND 10 CUBES
	{
		{12,8,10,28,4,30,15,23,2,24,22,25,7,1,26,16,9,19,3,13,21,18,20,29,27},
	{1,3,24,14,27,2,18,16,22,28,29,19,7,17,30,0,26,5,15,23,12,6,31,8,21},
		{22,30,26,7,4,14,25,28,20,10,31,29,27,24,16,9,13,0,11,18,19,3,12,1,17,6},
		{7,4,12,16,10,1,26,17,22,13,0,5,27,28,14,11,21,29,8,24,20,31,25,9,23,3},
		{3,23,7,27,13,14,5,25,17,26,10,2,22,30,15,12,20,31,24,16,6,18,28,4,19,1},
		{27,6,10,24,17,5,23,28,1,20,11,22,2,31,25,18,4,15,13,16,26,19,0,12,9,3},
		{15,23,25,24,16,13,27,30,3,22,6,1,7,29,20,10,11,9,12,8,2,28,4,17,19,26,14},
		{9,11,30,13,10,22,5,29,0,28,21,3,17,18,19,8,27,14,16,1,24,2,12,25,23,7,4},
		{18,31,29,10,11,14,23,5,27,9,12,7,13,28,17,15,3,8,25,0,6,19,2,22,21,1,16},
		{22,12,13,11,5,24,31,18,9,16,6,17,10,23,28,29,0,3,2,15,20,27,1,4,25,14,7},
		{17,11,22,5,3,23,13,21,8,29,30,20,31,27,18,26,2,16,25,7,4,10,24,15,14,1,28},
		{11,24,8,4,7,0,21,29,31,14,16,22,13,28,3,19,10,26,27,1,23,2,9,18,15,17,6},
		{18,30,9,26,22,27,12,14,21,4,16,19,25,2,23,8,5,13,10,11,1,20,31,15,17,3,24},
		{28,23,8,17,11,3,12,2,16,14,1,24,10,19,29,20,27,9,5,21,25,30,15,31,13,0,4},
		{31,16,26,19,25,27,18,21,22,13,1,0,7,17,8,20,15,24,28,9,4,23,3,29,6,5,30},
		{7,26,5,2,30,4,15,6,17,9,18,29,21,3,24,20,25,1,13,0,12,27,23,8,22,31,16},
		{25,4,12,20,16,18,30,29,13,7,31,28,9,24,17,27,2,21,0,1,8,14,23,11,10,22,5},
		{11,24,0,12,3,23,14,22,8,2,25,5,26,21,27,31,30,28,10,15,1,7,20,18,6,17,13},
		{31,2,29,14,7,20,1,10,22,4,11,23,16,15,0,13,19,5,9,30,26,24,21,27,3,12,25}
	}
};

// TEXT AND KEY
uint16_t text32[2];
uint16_t key64[4];

void online_attack_32(int rnds, int n)
{
	srand (time(NULL));
	
	if((rnds > 3) && (rnds < 11))
	{

	 int i = 1;
	  do
	  {
		  cout << "\tTry Number : " << i << endl;
		  read_maxterms(rnds);
		  i++;
		  cout << endl;
	  }while(i <= n);
	}
	else
		cout << "Error : Current available rounds are : 4, 5, 6, 7, 8, 9, 10";
  }

void read_maxterms(int rnds)
{

	for(int j = 0; j<NUMBER_OF_CUBES[rnds-1];j++)
	{
		compute_cube(j, rnds);
	}
}
void compute_cube(int index, int rnds)
{
	uint64_t sum = 0ull;
	uint64_t outbit = 1ull << _out[rnds-1][index];
	uint64_t k_temp = rand64();
	((uint64_t*)key64)[0] = k_temp;
	uint16_t key_val = 0ull;
	for(int i = 0; i < _key_size[rnds-1][index]; i++)
		if(key_value(_key_index[rnds-1][index][i]))
			key_val ^= 1ull;
	key_val ^= _free[rnds-1][index];

	for(int i = 0; i < (1<<_size[rnds-1][index]); i++)
	{
		((uint64_t*)key64)[0] = k_temp;
		memset(text32,0ull,sizeof text32);

		for(int j = 0; j < _size[rnds-1][index]; j++)
		{
			if(cube[rnds-1][index][j] < 16)
				text32[0] ^= ((i>>j) & 1ull) << (cube[rnds-1][index][j]);
			else
				text32[1] ^= ((i>>j) & 1ull) << (cube[rnds-1][index][j]-16);
		}
		
		simeck_32_64(key64, text32, text32,rnds);

		if (((uint32_t*)text32)[0] & outbit)
			sum ^= 1ull;
	}
	printf("Secret Adjusted Key Value : %d\tCube Attack Result : %d\t",(int)key_val,(int)(sum));

	if( (sum ^ key_val) == 0ull)
		cout << "\tMATCH";
	else
		cout << "\tCONFLICT";

	cout << "\tMaxterm : ";
	for(int i = 0; i < _key_size[rnds-1][index]; i++)
	{
		cout << "X" << _key_index[rnds-1][index][i];
		if(i != (_key_size[rnds-1][index]-1))
			cout << " + ";
	}
	if(_free[rnds-1][index])
		cout << " + 1";

	cout << endl;
}
uint64_t key_value(int k_index)
{
	return ((((uint64_t*)key64)[0] & (1ull<<k_index))>>k_index);
}