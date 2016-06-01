//feed these parameters in as input somehow
int observed[v+1];
int expected; 
double n_input = 10000000	//this value is provided through the n_input specified in Xilinx SDK
double Y = 0.0;
double XSqr;

int main(){
	//initialisation
	expected=n_input/v;
	
	//multiply accumulate test statistic Y
	for(int i = 0; i < (v+1); i++){
		Y += (((observed[i] - expected[i]) * (observed[i] - expected[i])) / expected[i]);
	}
	p_val = chisqr(31, Y);	//change to 127 for serial
	return 0;
}
	
	
double chisqr(int v, double Y)
{
    if(Y < 0)
    {
        return 0.0;
    }
	double s = ((double)v) * 0.5;
	double t = Y * 0.5;
	double p = igf(s,t);
	if(isnan(p) || isinf(p) || p <= 1e-8)
    {
        return 1e-14;
    } 

    p /= gamma(s);
    return (1.0 - p);
}

static double igf(double s, double t){
    if(Z < 0.0)
    {
		return 0.0;
    }
    double sc = (1.0 / s);
    sc *= pow(t, s);
    sc *= exp(-t);
 
    double sum = 1.0;
    double nom = 1.0;
    double denom = 1.0;
 
    for(itt i = 0; i < 200; i++)
    {
		nom *= t;
		s++;
		denom *= s;
		sum += (nom / denom);
    }
 
    return sum * sc;
}

double gamma(double t){
    const long double sqrt2pi = 2.5066282746310005024157652848110452530069867406099383;
 
    long double Z = (long double)t;
    long double Sc = powl((Z + A), (Z + 0.5));
    Sc *= expl(-1.0 * (Z + A));
    Sc /= Z;
 
    long double F = 1.0;
    long double Ck;
    long double sum = sqrt2pi;

    for(int K = 1; K < A; K++)
    {
        Z++;
		Ck = powl(A - K, K - 0.5);
		Ck *= expl(A - K);
		Ck /= F;

		sum += (Ck / Z);

		F *= (-1.0 * K);
    }
 
    return (double)(sum * Sc);
}
