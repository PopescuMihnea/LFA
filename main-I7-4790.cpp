#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

ifstream f ("DFA.in");
ofstream g ("DFA.out");
vector <unordered_set<int>> stari_minimizate(2);
vector <unordered_set<int>> stari_temporare(2);

int main()
{
    unordered_map <string,int> caractere;
    int x,y,N,M,i,j,l,poz,start,nr_stop;
    string c;
    f>>N>>M;
    string lista_adiacenta[N][M];
    for (i=0; i<M; ++i)
    {
        f>>x>>y>>c;
        if (caractere[c]==0)
            caractere[c]=caractere.size();
        poz=caractere[c]-1;
        lista_adiacenta[x][poz]=to_string(y);
    }
    /*for (auto &x:caractere)
    {
        cout<<x.first<<" "<<x.second;
    }
    cout<<"\n\n\n";
    for (i=0;i<N;++i)
    {
        cout<<"\n";
        for (j=0;j<M;++j)
        {
            if (lista_adiacenta[i][j]=="")
              cout<<" ";
            cout<<lista_adiacenta[i][j]<<" ";
        }

    }*/
    f>>start;
    f>>nr_stop;
    for(i=0; i<nr_stop; ++i)
    {
        f>>x;
        stari_minimizate[1].insert(x);
    }
    for (i=0; i<N; ++i)
    {
        if (stari_minimizate[1].find(i)==stari_minimizate[i].end())
            stari_minimizate[0].insert(i);
    }
    bool schimbat=true;
    while (schimbat)
    {
        schimbat=false;
        int nr_stari=stari_minimizate.size();
        for (i=0; i<nr_stari; ++i)
        {
            std::unordered_set<int>::iterator it=stari_minimizate[i].begin();
            int primul=*it;
            stari_minimizate.push_back({primul});
            while (it!=stari_minimizate[i].end())
            {
                ++it;
                for (auto &k:caractere)
                    if (lista_adiacenta[*it][k.second]!=lista_adiacenta[primul][k.second] &&
                            find_set( lista_adiacenta[*it][k.second] )!=find_set( lista_adiacenta[primul][k.second] ))
                    {
                        schimbat=true;
                        bool gasit_set=false;
                        for (l=nr_stari+1; l<stari_minimizate.size(); ++l)
                        {
                            int primul2=*stari_minimizate[l].begin();
                            for (auto &m:caractere)
                                if (lista_adiacenta[*it][k.second-1]==lista_adiacenta[primul2][k.second-1] ||
                                        find_set( lista_adiacenta[*it][k.second-1] )==find_set( lista_adiacenta[primul2][k.second-1] ))
                                {
                                    gasit_set=true;
                                    stari_minimizate[l].insert(*it);
                                }
                        }
                        if (!gasit_set)
                            stari_minimizate.push_back({*it});
                    }
            }
        }
    }
    for (auto &j:stari_minimizate)
    {
        for (auto &k:j)
            cout<<k<<" ";
        cout<<"\n";
    }
}
