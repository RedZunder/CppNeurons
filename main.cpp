#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

#define maxN 8  //number of Neuorns = number of "links"
#define ins 6  //number of defined attributes (inputs)
char gens[4]={'A', 'C', 'G', 'T'};

class Neuron
{
    private:
    short int size, colR, colG, colB, speedX, speedY;

    vector<char> genome={};

    public:
    unsigned short int mutationIDX;  //number between 0 and 10
    void setGenome (vector<char> v)
    {
        genome=v;
    }
    void showGenome() //show raw data
    {
        for (const auto &i :genome)
        cout<<i;
    }
    vector<char> getGenome()
    {
        return genome;
    }
    void interpret() //translate data to name of characteristics
       {
        for(const auto&i:genome)
        {
            switch(i)
            {
                default:break;
            }
            cout<<endl;
        }
    }

};

void MakeGenome(Neuron &n) //create random genome
{
    srand(time(NULL)) ;
    vector<char> vn;

    for(int i=0;i<maxN;i++)
    {
        vn.emplace_back(gens[rand()%4]) ;
    }

    n.setGenome(vn);
}

vector<char>Mutate(vector<char> g, unsigned short int idx)
{
    vector<char>gen={};
    for(const auto &i:g)
    {
        if(rand()%10+1<idx) 	gen.emplace_back(gens[rand()%4]) ;
        else
               gen.emplace_back(i) ;
    }
    return gen;

}
void ReproduceN(Neuron x)
{
    Neuron x1, x2;
    x1.mutationIDX=x.mutationIDX+rand() %2;
    x2.mutationIDX=x.mutationIDX+rand() %2;
    x1.setGenome(Mutate(x.getGenome(), x1. mutationIDX)) ;
    x2.setGenome(Mutate(x.getGenome(), x2. mutationIDX)) ;
    cout<<"x1: ";
    x1.showGenome() ;
    cout<<"\nx2: ";
    x2.showGenome() ;
}

int main()
{

    Neuron x;
    MakeGenome(x) ;
    x.mutationIDX=5;

    x.showGenome() ;
    cout<<endl;
    ReproduceN(x) ;





return 0;
}
