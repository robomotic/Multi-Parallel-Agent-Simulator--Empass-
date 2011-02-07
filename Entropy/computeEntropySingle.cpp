#include <Entropy/InformationMeasure.h>


int compute_entropy_predictor_log(string folder,int binpred,int binstep);
int compute_entropy_predictor_log(string folder,int low,int up,int binpred,int binstep);


int compute_entropy_predictor_log(string folder,int binpred,int binstep)
{
    return compute_entropy_predictor_log(folder,0,0,binpred,binstep);

}


//compute the entropy for a subset of the sample space
int compute_entropy_predictor_log(string folder,int low,int up,int binpred,int binstep)
{
    Gnuplot gp;
    gp <<"set terminal png\n";
    gp<<"set title 'Reflex probability'\n";
    gp<<"set auto x\n";
    gp<<"set style data histogram\n";
    gp<<"set style histogram cluster gap 1\n";
    //gp<<"set style fill solid border -1\n";
    gp<<"set boxwidth 0.9\n";
    gp<<"set xtic rotate by -45 scale 0\n";

RandomVarString *reflex=new RandomVarString();
reflex->setName("Predictor X1");
reflex->setAlphabetSize(3);
CSVDatabase<string> data_reflex(reflex,folder+"predictor.dat");

if(low<up)
{
data_reflex.subset=true;
data_reflex.lowersample=low;
data_reflex.uppersample=up;
}

data_reflex.readCSV(binpred);
reflex->estimateProbabilities();
reflex->dumpGnuplotData();
cout<<"H(X1)="<<entropy::entropy(*reflex)<<endl;

    gp<<"set xlabel 'X1'\n";
    gp<<"set ylabel 'P(X1)'\n";
    gp<<"set yrange [0:1]\n";
    gp<<"set xrange [-255:255]\n";
    gp << "set output '"<<folder<<"densityPredictor.png'\n";
    gp << "p '-' with boxes lw 1 \n";
    gp.send(reflex->bin_data);

AleatoryVariable<string> *motor=new AleatoryVariable<string>();
motor->setName("MotorAngle Z");
unsigned int alphabet_size=angle_range/angle_resolution[binstep-offset_angle];
motor->setAlphabetSize(alphabet_size);
CSVDatabase<string> data_motor(motor,folder+"angle.dat");

if(low<up)
{
data_motor.subset=true;
data_motor.lowersample=low;
data_motor.uppersample=up;
}
data_motor.readCSV(binstep);
motor->estimateProbabilities();
motor->dumpGnuplotData();
cout<<"H(Z)="<<setprecision(3)<<entropy::entropy(*motor)<<endl;


    if(data_reflex.getTotalSamples()!=data_motor.getTotalSamples())
    {
        cout<<"Error in sample size"<<data_reflex.getTotalSamples()<<"!="<<data_motor.getTotalSamples()<<endl;

    }


    gp<<"set title 'Motor output probability'\n";
    gp<<"set xlabel 'Z[degree] deltaZ="<<setprecision(3)<<angle_resolution[binstep-offset_angle]<<"'\n";
    gp<<"set ylabel '0<=P(Z)<=1'\n";
    gp<<"set auto x\n";
    gp<<"set yrange [0:1]\n";
    gp <<"set output '"<<folder<<"densityMotorOutputAngle.png'\n";
    gp <<"p '-' with boxes lw 1 \n";
    gp.send(motor->bin_data);

    JointVariable<string> *jvar;
    std::vector<float> MI_Z_X1(taumax-taumin+1);
    for(int tau=taumin;tau<=taumax;tau++)
    {
        jvar=new JointVariable<string>();
        jvar->X=motor;
        jvar->Y=reflex;
        jvar->setName("MI(Z,X1)");
        MI_Z_X1[tau-taumin]=entropy::mutualInformation(*jvar,tau);
        //cout<<"Samples taken: "<<jvar->Nxy<<endl;
    }
//cout<<"MI(Z,X0)"<<setprecision(3)<<MI_Z_X0<<endl;
float max_mi=*max_element (MI_Z_X1.begin(),MI_Z_X1.end());
unsigned int max_tau_index=distance(MI_Z_X1.begin(), max_element (MI_Z_X1.begin(),MI_Z_X1.end()));
cout<<"argmax_tau MI(Z,X1,tau)="<<max_mi<<" tau=" <<max_tau_index+taumin<<endl;
gnuplot_avg_reflex(MI_Z_X1,folder);
return data_motor.getTotalSamples();
}


