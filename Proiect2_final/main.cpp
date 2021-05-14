#include <iostream>

#include <fstream>

#include <vector>

#include <unordered_map>

#include <set>

#include <unordered_set>

using namespace std;

ifstream f("DFA.in");
ofstream g("DFA.out");
vector < set < int >> stari_minimizate(2);
vector < set < int >> stari_temporare;


inline int find_set(string num) {

  if (num == "")
    return -1;
  int x = stoi(num);
  for (int i = 0; i < stari_minimizate.size(); ++i)
    if (stari_minimizate[i].find(x) != stari_minimizate[i].end())
      return i;

}


int main() {

  unordered_map < string, int > caractere;
  int x, y, N, M, i, j, poz, start, nr_stop;
  bool gasit_set;
  string c;
  f >> N >> M;
  string lista_adiacenta[N + 1][M];
  for (i = 0; i < M; ++i) {
    f >> x >> y >> c;
    if (caractere[c] == 0)
      caractere[c] = caractere.size();
    poz = caractere[c] - 1;
    lista_adiacenta[x][poz] = to_string(y);
  }
  if (M < N * caractere.size()) {
    for (i = 0; i < N; ++i)
      for (j = 0; j < M; ++j)
        if (lista_adiacenta[i][j] == "")
          lista_adiacenta[i][j] = N;
    for (j = 0; j < M; ++j)
      lista_adiacenta[N][j] = to_string(N);
    ++N;
  }


  f >> start;
  f >> nr_stop;
  unordered_set < int > stari_finale;
  for (i = 0; i < nr_stop; ++i) {
    f >> x;
    stari_finale.insert(x);
    stari_minimizate[1].insert(x);
  }
  for (i = 0; i < N; ++i) {
    if (stari_minimizate[1].find(i) == stari_minimizate[1].end())
      stari_minimizate[0].insert(i);
  }


  bool schimbat = true;
  while (schimbat) {
    schimbat = false;
    int nr_stari = stari_minimizate.size();
    for (i = 0; i < nr_stari; ++i) {
      std::set < int > ::iterator it = stari_minimizate[i].begin();
      int poz_set = stari_temporare.size();
      stari_temporare.push_back({
        * it
      });
      while (it != stari_minimizate[i].end()) {
        if ( * it != * stari_temporare[poz_set].begin()) {
          gasit_set = true;
          for (auto & k: caractere) {
            if (lista_adiacenta[ * it][k.second - 1] == lista_adiacenta[ * stari_temporare[poz_set].begin()][k.second - 1] ||
              find_set(lista_adiacenta[ * it][k.second - 1]) == find_set(lista_adiacenta[ * stari_temporare[poz_set].begin()][k.second - 1]))
              continue;
            else {
              schimbat = true;
              gasit_set = false;
              break;
            }
          }
          if (gasit_set)
            stari_temporare[poz_set].insert( * it);
          else {
            for (j = 0; j < stari_temporare.size(); ++j)
              if (j != poz_set) {
                gasit_set = true;
                for (auto & k: caractere) {
                  if (lista_adiacenta[ * it][k.second - 1] == lista_adiacenta[ * stari_temporare[j].begin()][k.second - 1] ||
                    find_set(lista_adiacenta[ * it][k.second - 1]) == find_set(lista_adiacenta[ * stari_temporare[j].begin()][k.second - 1]))
                    continue;
                  else {
                    schimbat = true;
                    gasit_set = false;
                    break;
                  }
                }
                if (gasit_set) {
                  stari_temporare[j].insert( * it);
                  break;
                }

              }
            if (!gasit_set)
              stari_temporare.push_back({
                * it
              });
          }
        }
        ++it;
      }
    }
    stari_minimizate = stari_temporare;
    stari_temporare.clear();
  }


  string start_final;
  vector < string > stop_final;
  g << stari_minimizate.size() << " " << stari_minimizate.size() * caractere.size() << "\n";
  for (auto & j: stari_minimizate) {
    string x = "";
    bool e_start = false;
    bool e_stop = false;
    for (auto & k: j) {
      if (k == start)
        e_start = true;
      if (stari_finale.find(k) != stari_finale.end())
        e_stop = true;
      if (x.size())
        x += ",";
      x += to_string(k);
    }
    if (e_start)
      start_final = x;
    if (e_stop)
      stop_final.push_back(x);
    for (auto & k: caractere) {
      g << x << " ";
      for (auto & l: stari_minimizate)
        if (l.find(stoi(lista_adiacenta[ * j.begin()][k.second - 1])) != l.end()) {
          string y = "";
          for (auto & m: l) {
            if (y.size())
              y += ",";
            y += to_string(m);
          }
          g << y << " " << k.first << "\n";
          break;
        }
    }
  }
  g << start_final << "\n";
  g << stop_final.size() << " ";
  for (auto & k: stop_final)
    g << k << " ";

}
