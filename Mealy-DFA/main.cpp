#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
using namespace std;

ifstream f ("teste.in");
ofstream g ("rezultate.txt");

struct tranzitie //retinem ce litera din alfabet e necesare pt. tranzitie si
//intr-un alt string output-ul asociat(pe aceeasi pozitie)
{
    string caracter;
    string output;
};


int main()
{
    short nr_nod,nr_muchii,i,j,k,nod1,nod2,nod_start;
    short index_coada,nr_stari_finale,nod_final;
    short nr_teste,test,nod_curent;
    bool ok;
    string chr_test,str_output;
    char caracter_necesar,caracter_output;
    vector <vector<tranzitie>> xs;
    vector<short> coada;
    vector<short> stari_finale;
    //initializam matricea de adiacenta
    f>>nr_nod>>nr_muchii;
    xs.resize(nr_nod);
    for (i=0; i<nr_nod; i++)
        xs[i].resize(nr_nod);
    //citim muchiile(caracterele necesare pt tranzitie si output-ul asociat)
    for (i=0; i<nr_muchii; i++)
    {
        f>>nod1>>nod2>>caracter_necesar>>caracter_output;
        xs[nod1][nod2].caracter+=caracter_necesar;
        xs[nod1][nod2].output+=caracter_output;
    }
    //citim starea initiala
    f>>nod_start;
    //citim starile finale
    f>>nr_stari_finale;
    stari_finale.resize(nr_stari_finale);
    for (i=0; i<nr_stari_finale; i++)
    {
        f>>nod_final;
        stari_finale[i]=nod_final;
    }
    f>>nr_teste;
    for (test=0; test<nr_teste; test++)
    {
        coada.resize(0);
        coada.push_back(nod_start);//folosim o coada(simulata) pt a putea reconstrui
        //traseul la final.Inseram nodul de start
        index_coada=-1;
        str_output="";
        //citim urmatoare litera din cuvant
        f>>chr_test;
        for (i=0; i<chr_test.size() && index_coada+1<int(coada.size()); i++)
        {
            index_coada++;//simulam pop
            nod_curent=coada[index_coada]; //extragem nodul care a fost "eliminat"
            for (j=0; j<nr_nod; j++)
                //verificam daca din nodul curent exista o muchie care are starea de tranzitie litera curenta
                for (k=0; k<xs[nod_curent][j].caracter.size(); k++)
                    //daca exista legatura inseram nodul din celalalt capat al muchiei,introducem litera care trebuie afisata in output
                    if (xs[nod_curent][j].caracter[k]==chr_test[i])
                    {
                        coada.push_back(j);
                        str_output+=xs[nod_curent][j].output[k];
                        //ne oprim deoarece e DFA
                        break;
                    }
        }
        //testam daca am ajuns la finalul cuvantului
        if (i==chr_test.size())
        {
            ok=false; //presupunem ca nu exista stare finala
            for (i=0; i<nr_stari_finale; i++)
                //am gasit o stare finala,deci cuvantul este acceptat
                if (stari_finale[i]==coada[index_coada])
                {
                    ok=true;
                    break;
                }
            //daca e acceptat afisam informatiile
            if (ok)
            {
                g<<"DA\n";
                g<<"Output: "<<str_output<<"\n";
                g<<"Traseu: ";
                for (i=0; i<coada.size(); i++)
                    g<<coada[i]<<" ";
                g<<"\n";
            }
            else
                g<<"NU\n";
        }
        else
            g<<"NU\n";
        g<<"\n";
    }
}
