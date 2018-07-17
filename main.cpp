#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main() {
	double	Swr=0.3; //unitless
	double	Sorw=0.25; //unitless
	double	ut=10; //ft_per_day
	double	A=4000; //ft_square
	double	rho_oil=48; 
	double	rho_water=64;
	double	vis_w=0.5;
	double	vis_oil=2;
	double	nw=2;
	double	now=3;
	double	krow_star=0.7;
	double	krw_star=0.05;
	double	k=0.001;
	double	por=0.18;
	double	dt=0.5;
	double	fw_inj=1;
	double	dx=20;

	//input parameters
	const int IMAX = 50;//to start at 1
	int time_end = 11;
	const int INTERVAL = time_end / dt;
	//calculation parameter
	double krw, krow, mob_O, mob_W;

	//Sw vector
	double Sw[IMAX][23];
	double fw[IMAX][23];
	//vector<vector<double>> Sw(IMAX+1,vector<double>(INTERVAL+1));
	//vector<vector<double>> fw(IMAX+1, vector<double>(INTERVAL+1));
	//initialize all Sw vector to be equal to Swr (START AT 0) 0 means node 1
	for (int j = 1;j <= IMAX;j++) {
		Sw[j][0] = Swr;
		cout << Sw[j][0];
	}

	//TIME LOOP ITERATION
	for (int n = 1;n <= INTERVAL;n++) {
		for (int k = 1;k <= IMAX;k++) {
				//Calculate oil relative permeability for each node
				krw = krw_star * pow(((Sw[k][n-1] - Swr) / (1 - Swr - Sorw)), nw);
				//Calculate water relative permeability for each node
				krow = krow_star * pow(((Sw[k][n-1] - Sorw) / (1 - Swr - Sorw)), now);
				//Calculate oil mobility for each node
				mob_W= krw / vis_w;
				//Calculate water mobility for each node
				mob_O = krow / vis_oil;
				//Calculate water fractional flow for each node
				fw[k][n] = mob_W / (mob_W + mob_O);
		}

				//Calculate the new saturation for first node taking into account the imaginary node
				//Sw(1, n + 1) = Sw(1, n) - u*dt / dx*(fw(1, n) - 1);
		Sw[1][n] = Sw[1][n - 1] - (ut * dt / dx * (fw[1][n] - fw_inj));
		
		//cout << Sw[1][1] << "LALLA" << endl;
		

		for (int k = 2;k <= IMAX;k++) {
						Sw[k][n] = Sw[k][n-1] - (ut * dt / dx * (fw[k][n] - fw[k-1][n]));			//cout << "WHYYY" << endl;			//cout << Sw[2][1] << "LALLA" << endl;
		}

	}

	//OUTPUT RESULT 
	for (int n = 0;n <= INTERVAL;n++) {
		for (int k = 1;k <= IMAX;k++) {
			cout << Sw[k][n] << " ";
		}
		cout << endl;
	}


	system("pause");
	return 0;
}