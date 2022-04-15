#include <iostream>
#include <bits/stdc++.h>
using namespace std;
double v_acc;
// Function to get the properties at a given pressure using linear interpolation between the two nearest Pressure points from the table
vector<double> properties(double p){
    // arr stores the various pressures given in the steam table
	double steamTable[7][6];
	steamTable[0][0]=696.33,steamTable[0][1]=2570.9,steamTable[0][2]=0.0011,steamTable[0][3]=0.273,steamTable[0][4]=697.1,steamTable[0][5]=2762,
	steamTable[1][0]=708.475,steamTable[1][1]=2573.75,steamTable[1][2]=0.0011,steamTable[1][3]=0.255,steamTable[1][4]=709.3,steamTable[1][5]=2765,
	steamTable[2][0]=720.02,steamTable[2][1]=2576,steamTable[2][2]=0.0011,steamTable[2][3]=0.24,steamTable[2][4]=720.9,steamTable[2][5]=2768,
	steamTable[3][0]=731.065,steamTable[3][1]=2575.35,steamTable[3][2]=0.0011,steamTable[3][3]=0.229,steamTable[3][4]=732,steamTable[3][5]=2770,
	steamTable[4][0]=741.61,steamTable[4][1]=2578.5,steamTable[4][2]=0.0011,steamTable[4][3]=0.215,steamTable[4][4]=742.6,steamTable[4][5]=2772,
	steamTable[5][0]=751.755,steamTable[5][1]=2580.2,steamTable[5][2]=0.0011,steamTable[5][3]=0.204,steamTable[5][4]=752.8,steamTable[5][5]=2774,
	steamTable[6][0]=761.5,steamTable[6][1]=2582,steamTable[6][2]=0.0011,steamTable[6][3]=0.194,steamTable[6][4]=762.6,steamTable[6][5]=2776;
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

 double eqn_5(double p_1,double p_2,double p_f,double p_i,double alpha_i,double alpha_f,double m1_inflow,double m2_inflow,double delta_t){
    vector<double> props_f,props_i,h1_props,h2_props;
    double ans;
    props_f=properties(p_f);
    props_i=properties(p_i);
    h1_props=properties(p_1);
    h2_props=properties(p_2);
    long double g_1f,g_1i,g_2f,g_2i,b,a;
    a=(m1_inflow-m2_inflow)*delta_t;
    b=(m1_inflow*h1_props[5] - m2_inflow*h2_props[5])*delta_t;
    g_1i=(alpha_i/props_i[2]) + ((1-alpha_i)/props_i[3]);
    g_1f=(alpha_f/props_f[2]) + ((1-alpha_f)/props_f[3]);
    g_2i=(alpha_i/props_i[2])*props_i[0] + ((1-alpha_i)/props_i[3])*props_i[1];
    g_2f=(alpha_f/props_f[2])*props_f[0] + ((1-alpha_f)/props_f[3])*props_f[1];
    ans=((g_2f-g_2i)/(g_1f-g_1i)) - (b/a);
    v_acc = a/(g_1f-g_1i);
    return ans;
}

int main() {

    ifstream inputf;
    inputf.open("input.txt");
	double p_1,p_2,p_i,m1_flow,m2_flow,delta_t,alpha_i,alpha_f,p_f,a,b,temp1,temp2;
    int t=2;
    
	while(t--){
        inputf>>p_1>>p_2>>m1_flow>>m2_flow>>delta_t>>p_i>>alpha_i>>alpha_f;

    // Initial guess for p_f = (pi+p2)/2
    // Error and tol represent the error and tolerance limits, tolerance is set to 10^-4, as a limit for a precise answer.
    double tol=0.0001;
    b=p_1-50;
    a=p_2+100;
    int i=0;
    // Using Bisection method for finding the value of P_f 
    do{
        p_f=(a+b)/2;
        i++;
        if(eqn_5(p_1,p_2,p_f,p_i,alpha_i,alpha_f,m1_flow,m2_flow,delta_t)==0){
            break;
        }
        else if(eqn_5(p_1,p_2,a,p_i,alpha_i,alpha_f,m1_flow,m2_flow,delta_t)*eqn_5(p_1,p_2,p_f,p_i,alpha_i,alpha_f,m1_flow,m2_flow,delta_t)<0){
            b=p_f;
        }
        else{
            a=p_f;
        }        
    }
    while((b-a)>=tol);
    cout<<"Test case: "<<2-t<<endl;
    if(p_f>=949.9){
        cout<<"No physically valid Solution is obtained ";
    }
    else{
        cout<<"Pf obtained is "<<p_f<<endl;
        cout<<"Vacc obtained is "<<v_acc<<endl;
    }
    cout<<endl;
}
    inputf.close();
	return 0;
}