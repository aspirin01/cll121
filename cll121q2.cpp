#include <iostream>
#include <bits/stdc++.h>
using namespace std;
double v_acc;
vector<double> properties(double p){
    // Storing the data into a steam table matrix
	double steamTable[7][6];
	steamTable[0][0]=696.33,steamTable[0][1]=2570.9,steamTable[0][2]=0.0011,steamTable[0][3]=0.273,steamTable[0][4]=697.1,steamTable[0][5]=2762,
	steamTable[1][0]=708.475,steamTable[1][1]=2573.75,steamTable[1][2]=0.0011,steamTable[1][3]=0.255,steamTable[1][4]=709.3,steamTable[1][5]=2765,
	steamTable[2][0]=720.02,steamTable[2][1]=2576,steamTable[2][2]=0.0011,steamTable[2][3]=0.24,steamTable[2][4]=720.9,steamTable[2][5]=2768,
	steamTable[3][0]=731.065,steamTable[3][1]=2575.35,steamTable[3][2]=0.0011,steamTable[3][3]=0.229,steamTable[3][4]=732,steamTable[3][5]=2770,
	steamTable[4][0]=741.61,steamTable[4][1]=2578.5,steamTable[4][2]=0.0011,steamTable[4][3]=0.215,steamTable[4][4]=742.6,steamTable[4][5]=2772,
	steamTable[5][0]=751.755,steamTable[5][1]=2580.2,steamTable[5][2]=0.0011,steamTable[5][3]=0.204,steamTable[5][4]=752.8,steamTable[5][5]=2774,
	steamTable[6][0]=761.5,steamTable[6][1]=2582,steamTable[6][2]=0.0011,steamTable[6][3]=0.194,steamTable[6][4]=762.6,steamTable[6][5]=2776;
    // arr stores the various pressures given in the steam table
    int arr[7]={700,750,800,850,900,950,1000};
    int i=0;
    // To find the coordinates to linear interpolate for properties at given pressure P(kPa)
    while(true){
        if(arr[i]>=p){
            break;
        }
        i++;
    }
    
    double temp;
   
    vector<double> ans;
    for(int j=0;j<6;j++){
        temp= steamTable[i-1][j] +(p-arr[i-1])*((steamTable[i][j]-steamTable[i-1][j])/(arr[i]-arr[i-1]));
        ans.push_back(temp);
    }
    return ans;
}


int main() {

    ifstream inputf;
    inputf.open("input2.txt");
	double p_1,p_2,p_i,m1_flow,m2_flow,delta_t,alpha_i,alpha_f,p_f,a,b;
    inputf>>p_1>>p_2>>m1_flow>>m2_flow>>delta_t>>p_i>>alpha_i>>p_f;
    vector<double> props_f,props_i,h1_props,h2_props;
    long double g_1f,g_1i,g_2f,g_2i;
    props_f=properties(p_f);
    props_i=properties(p_i);
    h1_props=properties(p_1);
    h2_props=properties(p_2);
    a=(m1_flow-m2_flow)*delta_t;
    b=(m1_flow*h1_props[5] - m2_flow*h2_props[5])*delta_t;
    g_1i=(alpha_i/props_i[2]) + ((1-alpha_i)/props_i[3]);
    g_2i=(alpha_i/props_i[2])*props_i[0] + ((1-alpha_i)/props_i[3])*props_i[1];
    // g_2f=(alpha_f/props_f[2])*props_f[0] + ((1-alpha_f)/props_f[3])*props_f[1];
       alpha_f =(g_2i -b*g_1i/a +b*(1/props_f[3])/a -props_f[1]/props_f[3])/((props_f[0]/props_f[2] - props_f[1]/props_f[3]-b*(1/props_f[2]-1/props_f[3])/a));
    g_1f=(alpha_f/props_f[2]) + ((1-alpha_f)/props_f[3]);
    cout<< "Alpha_f calculated is "<<alpha_f<<endl;
    v_acc = a/(g_1f-g_1i);
    cout<<"Volume obtained is: "<<v_acc<<endl;
    inputf.close();
	return 0;
}