
#include <Entropy/InformationMeasure.h>

void test_uniform()
{
AleatoryVariable< char > *varX = new AleatoryVariable< char>();
varX->setName("X");


varX->enqueueInSequence('a');
varX->enqueueInSequence('1');
varX->enqueueInSequence('b');
varX->enqueueInSequence('1');
varX->enqueueInSequence('c');
varX->enqueueInSequence('0');
varX->estimateProbabilities();
float hmax=entropy::entropy(*varX);
std::cout<<"H :"<<hmax<<std::endl;


varX = new AleatoryVariable< char>();
varX->setName("Y");


varX->enqueueInSequence('a');
varX->enqueueInSequence('a');
varX->enqueueInSequence('a');
varX->enqueueInSequence('a');
varX->enqueueInSequence('a');
varX->enqueueInSequence('a');
varX->estimateProbabilities();
hmax=entropy::entropy(*varX);
std::cout<<"H :"<<hmax<<std::endl;

varX = new AleatoryVariable< char>();
varX->setName("Y");


varX->enqueueInSequence('a');
varX->enqueueInSequence('0');
varX->enqueueInSequence('0');
varX->enqueueInSequence('0');
varX->enqueueInSequence('0');
varX->enqueueInSequence('0');
varX->estimateProbabilities();
hmax=entropy::entropy(*varX);
std::cout<<"H :"<<hmax<<std::endl;


return;
}


void test_variable()
{
AleatoryVariable< char > *varX = new AleatoryVariable< char>();
AleatoryVariable< char > *varY = new AleatoryVariable< char>();
varX->setName("X");
varY->setName("Y");

varX->enqueueInSequence('a');
varY->enqueueInSequence('1');
varX->enqueueInSequence('b');
varY->enqueueInSequence('2');
varX->enqueueInSequence('c');
varY->enqueueInSequence('3');
varX->enqueueInSequence('c');
varY->enqueueInSequence('2');

JointVariable<char> *varXY=new JointVariable<char>();
varXY->X=varX;
varXY->Y=varY;
float mi=entropy::mutualInformation(*varXY,0);
std::cout<<"MI :"<<mi<<std::endl;

return;
}

void test_concat()
{
AleatoryVariable<string > *varX = new AleatoryVariable< string>();
AleatoryVariable<string> *varY = new AleatoryVariable< string>();
varX->setName("X");
varY->setName("Y");

varX->enqueueInSequence("a");
varY->enqueueInSequence("1");

varX->enqueueInSequence("b");
varY->enqueueInSequence("2");

varX->enqueueInSequence("c");
varY->enqueueInSequence("1");

varX->enqueueInSequence("a");
varY->enqueueInSequence("1");

varX->enqueueInSequence("d");
varY->enqueueInSequence("2");

JointVariable<string> *varXY=new JointVariable<string>();
varXY->X=varX;
varXY->Y=varY;
float mi=entropy::mutualInformation(*varXY);
std::cout<<"MI :"<<mi<<std::endl;

JointVariable<string> *varXYn=new JointVariable<string>();
varXYn->X=varX;
varXYn->Y=varY;
mi=entropy::mutualInformationN(*varXYn,2,1);
std::cout<<"MI^2 :"<<mi<<std::endl;

return;
}

void test_histogram()
{
        Histogram hist(0,360,1);
        hist.Add(10);
        hist.Add(409);

}

void test_vector_max()
{
    std::vector<double> tempvec; // declare a vector for holding the temperatures
    tempvec.push_back(10.0);
    tempvec.push_back(12.0);
    tempvec.push_back(16.0);
    tempvec.push_back(11.0);
    tempvec.push_back(10.0);

    cout<< "Maximum temperature was " << *max_element (tempvec.begin(),tempvec.end());
    cout<< "   at index" << distance(tempvec.begin(), max_element (tempvec.begin(),tempvec.end())) << endl;
}

//compute the entropy on the entire sample space
int compute_entropy_retinal_log(string folder,int binstep)
{

    return compute_entropy_retinal_log(folder,0,0,binstep);
}

int compute_entropy_retinal_log(string folder,int low,int up,int binstep)
{

AleatoryVariable<string> *motor=new AleatoryVariable<string>();
motor->setName("Motor Angle(Deg) Z");
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
cout<<"H(Z)="<<setprecision(3)<<entropy::entropy(*motor)<<endl;

// a matrix containing the serial retinal field for different taus
matrix<float> retinaltau(taumax-taumin+1,retinal_size);


    for(int i=0;i<retinal_size;i++)
    {
        RandomVarString *predict=new RandomVarString();
        predict->setName("X1");
        //cout<<"Alphabet Size "<<alphabet_size<<endl;
        predict->setAlphabetSize(3);
        CSVDatabase<string> data_reflex(predict,folder+"predictorbin.dat");
            if(low<up)
            {
            data_reflex.subset=true;
            data_reflex.lowersample=low;
            data_reflex.uppersample=up;
            }
        //data_reflex.countSamples();

        data_reflex.readCSV(i);
        //cout<<"#samples "<<data_reflex.getTotalSamples()<<endl;
        //predict->estimateProbabilities();
        //cout<<"Entropy reflex "<<entropy::entropy(*reflex)<<endl;

        if(data_reflex.getTotalSamples()!=data_motor.getTotalSamples())
        {
            cout<<"Error in sample size "<<data_reflex.getTotalSamples()<<"!="<<data_motor.getTotalSamples()<<endl;

        }

        JointVariable<string> *jvar;
        //compute the mutual information for different timings
        for(int tau=taumin;tau<=taumax;tau++)
        {
        jvar=new JointVariable<string>();
        jvar->X=motor;
        jvar->Y=predict;
        jvar->setName("MI(Z,X1)");
        retinaltau(tau-taumin,i)=entropy::mutualInformationN(*jvar,ordermax,1);
        //cout<<"MI(Z,X1("<<i<<"),tau="<<tau<<")=" <<retinaltau(tau-taumin,i)<<endl;
        //cout<<"Samples taken: "<<jvar->Nxy<<endl;
        }
    }

//cout<<"MI(Z,X1)=" <<sum_row(retinaltau,0,false)<<" Avg(MI)=" <<sum_row(retinaltau,0,true)<<endl;
boost::numeric::ublas::vector<float> avg_retinal=sum_row(retinaltau);
unsigned int max_tau_index=find_max_vector(retinaltau);
//cout<<"MI(Z,X1)="<<setprecision(3)<<avg_retinal<<endl;
cout<<"argmax_tau MI(Z,X1,tau)="<<avg_retinal(max_tau_index)<<" tau=" <<max_tau_index+taumin<<endl;

CSVExporter matexport(retinaltau,folder+"retinalflowmatrix.dat");
matexport.exportMatrix(0,retinal_W);
Gnuplot gp;
gp <<"set terminal png\n";
gp<<"set title 'Retinal flow'\n";
gp <<"set output '/home/epokh/retinal.png' \n";
gp <<"set view map\n";
gp <<"splot '"<<folder<<"retinalflowmatrix.dat"<<"' matrix with image\n";

return data_motor.getTotalSamples();
}

int compute_entropy_retinal_order_log(string folder,int low,int up,int binstep)
{

AleatoryVariable<string> *motor=new AleatoryVariable<string>();
motor->setName("Motor Angle(Deg) Z");
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
cout<<"H(Z)="<<setprecision(3)<<entropy::entropy(*motor)<<endl;

// a matrix containing the serial retinal field for different taus
matrix<float> retinaltau(ordermax-ordermin+1,retinal_size);


    for(int i=0;i<retinal_size;i++)
    {
        RandomVarString *predict=new RandomVarString();
        predict->setName("X1");
        //cout<<"Alphabet Size "<<alphabet_size<<endl;
        predict->setAlphabetSize(3);
        CSVDatabase<string> data_reflex(predict,folder+"predictorbin.dat");
            if(low<up)
            {
            data_reflex.subset=true;
            data_reflex.lowersample=low;
            data_reflex.uppersample=up;
            }
        //data_reflex.countSamples();

        data_reflex.readCSV(i);
        //cout<<"#samples "<<data_reflex.getTotalSamples()<<endl;
        //predict->estimateProbabilities();
        //cout<<"Entropy reflex "<<entropy::entropy(*reflex)<<endl;

        if(data_reflex.getTotalSamples()!=data_motor.getTotalSamples())
        {
            cout<<"Error in sample size "<<data_reflex.getTotalSamples()<<"!="<<data_motor.getTotalSamples()<<endl;

        }

        JointVariable<string> *jvar;
        //compute the mutual information for different timings
        for(int order=ordermin;order<=ordermax;order++)
        {
        jvar=new JointVariable<string>();
        jvar->X=motor;
        jvar->Y=predict;
        jvar->setName("MI(Z,X1)");
        retinaltau(order-ordermin,i)=entropy::mutualInformationN(*jvar,ordermax,1);
        //cout<<"MI(Z,X1("<<i<<"),tau="<<tau<<")=" <<retinaltau(tau-taumin,i)<<endl;
        //cout<<"Samples taken: "<<jvar->Nxy<<endl;
        }
    }

//cout<<"MI(Z,X1)=" <<sum_row(retinaltau,0,false)<<" Avg(MI)=" <<sum_row(retinaltau,0,true)<<endl;
boost::numeric::ublas::vector<float> avg_retinal=sum_row(retinaltau);
unsigned int max_tau_index=find_max_vector(retinaltau);
//cout<<"MI(Z,X1)="<<setprecision(3)<<avg_retinal<<endl;
cout<<"argmax_tau MI(Z,X1,tau)="<<avg_retinal(max_tau_index)<<" tau=" <<max_tau_index+taumin<<endl;

CSVExporter matexport(retinaltau,folder+"retinalflowmatrix.dat");
matexport.exportMatrix(0,retinal_W);
Gnuplot gp;
gp <<"set terminal png\n";
gp<<"set title 'Retinal flow'\n";
gp <<"set output '/home/epokh/retinal.png' \n";
gp <<"set view map\n";
gp <<"splot '"<<folder<<"retinalflowmatrix.dat"<<"' matrix with image\n";

return data_motor.getTotalSamples();
}

int compute_entropy_reflex_log(string folder,int binstep)
{
    return compute_entropy_reflex_log(folder,0,0,binstep);

}


//compute the entropy for a subset of the sample space
int compute_entropy_reflex_log(string folder,int low,int up,int binstep)
{
    Gnuplot gp;
    gp << "set terminal png\n";
    gp<<"set title 'Reflex probability'\n";
    gp<<"set auto x\n";
    gp<<"set style data histogram\n";
    gp<<"set style histogram cluster gap 1\n";
    //gp<<"set style fill solid border -1\n";
    gp<<"set boxwidth 0.9\n";
    gp<<"set xtic rotate by -45 scale 0\n";

RandomVarString *reflex=new RandomVarString();
reflex->setName("Reflex X0");
reflex->setAlphabetSize(3);
CSVDatabase<string> data_reflex(reflex,folder+"reflex.dat");

if(low<up)
{
data_reflex.subset=true;
data_reflex.lowersample=low;
data_reflex.uppersample=up;
}

data_reflex.readCSV();
reflex->estimateProbabilities();
cout<<"H(X0)="<<entropy::entropy(*reflex)<<endl;
reflex->dumpGnuplotData();
    gp<<"set xlabel 'X0'\n";
    gp<<"set ylabel 'P(X0)'\n";
    gp<<"set yrange [0:1]\n";
    gp<<"set xrange [-255:255]\n";
    gp << "set output '"<<folder<<"densityReflex.png'\n";
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
    std::vector<float> MI_Z_X0(taumax-taumin+1);
        for(int tau=taumin;tau<=taumax;tau++)
        {
        jvar=new JointVariable<string>();
        jvar->X=motor;
        jvar->Y=reflex;
        jvar->setName("MI(Z,X0)");
        MI_Z_X0[tau-taumin]=entropy::mutualInformationN(*jvar,ordermax,1);
        //cout<<"Samples taken: "<<jvar->Nxy<<endl;
        }
//cout<<"MI(Z,X0)"<<setprecision(3)<<MI_Z_X0<<endl;
float max_mi=*max_element (MI_Z_X0.begin(),MI_Z_X0.end());
unsigned int max_tau_index=distance(MI_Z_X0.begin(), max_element (MI_Z_X0.begin(),MI_Z_X0.end()));
cout<<"argmax_tau MI(Z,X0,tau)="<<max_mi<<" tau=" <<max_tau_index+taumin<<endl;
gnuplot_avg_reflex(MI_Z_X0,folder);
return data_motor.getTotalSamples();
}


void test_matrix()
{
    matrix<float> m (1, retinal_size);
    for (unsigned i = 0; i < m.size1 (); ++ i)
        for (unsigned j = 0; j < m.size2 (); ++ j)
            m (i, j) = 3 * i + j;
    std::cout << m << std::endl;

CSVExporter test(m,"/home/epokh/matrix.txt");

test.exportMatrix(0,retinal_W);
Gnuplot gp;
gp <<"set terminal png\n";
gp <<"set output '/home/epokh/retinal.png' \n";
gp<<"set view map\n";
gp<<"splot '/home/epokh/matrix.txt' matrix with image\n";
}

void gnuplot_retinal_field(matrix<float> &retinaltau,string folder,int tau_index)
{
Gnuplot gp;
gp <<"set terminal png\n";
gp <<"set output '"<<folder<<"M(X1,Z,tau="<<tau_index+taumin<<").png' \n";
gp<<"set title 'M(X1,Z,tau="<<tau_index+taumin<<")'\n";
gp<<"unset key\n";
gp<<"set tic scale 0\n";
gp<<"set xtics border in scale 0,0 mirror norotate  offset character 0, 0, 0 \n";
gp<<"set ytics border in scale 0,0 mirror norotate  offset character 0, 0, 0 \n";
gp<<"set ztics border in scale 0,0 nomirror norotate  offset character 0, 0, 0 \n";
gp<<"set cbrange [0:1]\n";
gp<<"set cblabel 'Score' \n";
gp<<"unset cbtics\n";

gp<<"set xrange [1:4]\n";
gp<<"set yrange [1:4]\n";

gp<<"set view map\n";
gp<<"splot '-' matrix with image\n";
gp<<serialize_row(retinaltau,tau_index,retinal_W);
}

void gnuplot_avg_retinal(boost::numeric::ublas::vector<float>  &retinaltau,string folder)
{
Gnuplot gp;
gp <<"set terminal png\n";
gp <<"set output '"<<folder<<"AVG_MI(Z,X1).png' \n";
gp<<"set title 'Average of MI(Z,X1) over different tau'\n";
gp<<"set auto x\n";
gp<<"set xlabel 'tau' \n";
gp<<"set ylabel 'MI(Z,X1,tau)' \n";
gp <<"p '-' with boxes lw 1 \n";
std::map<unsigned int, float> point_data;

for(unsigned int j=0;j<retinaltau.size();++j)
{
    point_data[j+taumin]=retinaltau(j);

}
gp.send(point_data);
}

void gnuplot_avg_reflex(std::vector<float>  &retinaltau,string folder)
{
Gnuplot gp;
gp <<"set terminal png\n";
gp <<"set output '"<<folder<<"AVG_MI(Z,X0).png' \n";
gp<<"set title 'Average of MI(Z,X1) over different tau'\n";
gp<<"set auto x\n";
gp<<"set xlabel 'tau'\n";
gp<<"set ylabel 'MI(Z,X0,tau)'\n";
gp <<"p '-' with boxes lw 1 \n";
std::map<unsigned int, float> point_data;

for(unsigned int j=0;j<retinaltau.size();++j)
{
    point_data[j+taumin]=retinaltau[j];

}
gp.send(point_data);
}


