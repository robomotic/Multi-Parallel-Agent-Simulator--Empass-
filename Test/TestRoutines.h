#ifndef TESTROUTINES_H
#define TESTROUTINES_H


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace Controllers;

#define N       1000
#define CHUNKSIZE   10

void testloop()
{

int nthreads, tid, i, chunk;
float a[N], b[N], c[N];

/* Some initializations */
for (i=0; i < N; i++)
  a[i] = b[i] = i * 1.0;
chunk = CHUNKSIZE;

#pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
     std::cout<<"Number of threads = "<< nthreads << std::endl;
    }
 std::cout<<"Thread "<<tid<<" starting..." << std::endl;;

  #pragma omp for schedule(dynamic,chunk)
  for (i=0; i<N; i++)
    {
    c[i] = a[i] + b[i];
    std::cout<<"Thread "<<tid<<" c["<<i<<"]= "<<c[i]<< std::endl;
    }

  }  /* end of parallel section */
#pragma omp barrier
#pragma omp master
  {
   nthreads = omp_get_num_threads();
   std::cout << "There are " << nthreads << " threads" << std::endl;
  }

}
void helloworldtest()
{
int th_id, nthreads;
#pragma omp parallel private(th_id)
 {
  th_id = omp_get_thread_num();
  std::ostringstream ss;
  ss << "Hello World from thread " << th_id << std::endl;
  std::cout << ss.str();
#pragma omp barrier
#pragma omp master
  {
   nthreads = omp_get_num_threads();
   std::cout << "There are " << nthreads << " threads" << std::endl;
  }
 }
}

void testobject()
{

 int i,chunk;
 int th_id, nthreads;
 std::vector<LowPassFilter *> lp_vector;
 chunk = CHUNKSIZE;
 #pragma omp parallel shared(lp_vector,chunk) private(i,th_id)
 {
  th_id = omp_get_thread_num();
  if (th_id  == 0)
    {
    nthreads = omp_get_num_threads();
     std::cout<<"Number of threads = "<< nthreads << std::endl;
    }
 std::cout<<"Thread "<<th_id <<" starting..." << std::endl;;

 #pragma omp for schedule(dynamic,chunk)
 for (i=0; i<N; i++){
    th_id = omp_get_thread_num();
    std::cout << "Normalizing filter in thread  " << th_id << " filter# "<<i<<std::endl;
    lp_vector.push_back(new LowPassFilter(0.8,2.0));

    }
}
#pragma omp barrier
#pragma omp master
  {
   nthreads = omp_get_num_threads();
   std::cout << "There are " << nthreads << " threads" << std::endl;
  }
}

void testsingleICO()
{
    IcoSiso* icosiso=new IcoSiso(true,1.0,0.9);
    Gnuplot gp;
        // For debugging or manual editing of commands:
        //Gnuplot gp("cat > plot.gp");
        // or
        //Gnuplot gp("tee plot.gp | gnuplot");

        gp << "set terminal png\n";
        std::vector<double> w_pts,u0_pts,u1_pts,u0dot_pts;
        for(int k=0; k<100; k++) {
           if(k==10)
                icosiso->compute(1.0,0.0);
           else if(k==20)
                icosiso->compute(0.0,1.0);
           else
                icosiso->compute(0.0,0.0);
            w_pts.push_back(icosiso->getW1());
            u0_pts.push_back(icosiso->getU0());
            u1_pts.push_back(icosiso->getU1());
            u0dot_pts.push_back(icosiso->getDerivReflex());
        }
        gp << "set output 'icosiso_test.png'\n";
        gp << "p '-' w l t 'u0', '-' w l t 'u1' , '-' w l t 'u0dot'\n";
        gp.send(u0_pts).send(u1_pts).send(u0dot_pts);
        gp << "set output 'icosiso_w.png'\n";
        gp << "p '-' w l t 'w1' \n";
        gp.send(w_pts);

}

void testsinglefir()
{
    LowPassFilter* fir=new LowPassFilter(0.8,10.0);
    std::cout<<"Normalized constant is "<<fir->getNormconst()<<std::endl;
    fir->resetBuffer();
        Gnuplot gp;
        // For debugging or manual editing of commands:
        //Gnuplot gp("cat > plot.gp");
        // or
        //Gnuplot gp("tee plot.gp | gnuplot");

        gp << "set terminal png\n";
        std::vector<double> y_pts;
        for(int k=0; k<10000; k++) {
           if(k>=10 && k<=100)
                fir->updateFilter(10.0);
            else
                 fir->updateFilter(0.0);
                y_pts.push_back(fir->getOutput());
        }
        gp << "set output 'fir1_test.png'\n";
        gp << "p '-' w l\n";
        gp.send(y_pts);
}

void testmatrix()
{
    using namespace boost::numeric::ublas;
        matrix<double> m (3, 3);
        for (unsigned i = 0; i < m.size1 (); ++ i)
            for (unsigned j = 0; j < m.size2 (); ++ j)
                m (i, j) = 3 * i + j;
        std::cout << m << std::endl;



}

void testgp()
{
        Gnuplot gp;
        // For debugging or manual editing of commands:
        //Gnuplot gp("cat > plot.gp");
        // or
        //Gnuplot gp("tee plot.gp | gnuplot");

        gp << "set terminal png\n";

        std::vector<double> y_pts;
        for(int i=0; i<1000; i++) {
                double y = (i/500.0-1) * (i/500.0-1);
                y_pts.push_back(y);
        }

        gp << "set output 'my_graph_1.png'\n";
        gp << "p '-' w l, sin(x/200) w l\n";
        gp.send(y_pts);
        // Or this:
        //gp.send(y_pts.begin(), y_pts.end());

        // NOTE: we can use map here because the X values are intended to be
        // sorted.  If this was not the case, vector<pair<double,double>> could be
        // used instead.

        std::map<double, double> xy_pts_A;
        for(double x=-2; x<2; x+=0.01) {
                double y = x*x*x;
                xy_pts_A[x] = y;
        }

        std::map<double, double> xy_pts_B;
        for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
                double theta = alpha*2.0*3.14159;
                xy_pts_B[cos(theta)] = sin(theta);
        }

        gp << "set output 'my_graph_2.png'\n";
        gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
        gp << "p '-' w l t 'cubic', '-' w p t 'circle'\n";
        gp.send(xy_pts_A).send(xy_pts_B);
        // Or this:
        //gp.send(xy_pts_A.begin(), xy_pts_A.end());
        //gp.send(xy_pts_B.begin(), xy_pts_B.end());

}

#endif // TESTROUTINES_H
