#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

#include "DNI.hpp"
#include "TreeAVL.hpp"


using namespace std;

Counter DNI::counter;

int main() {

  TreeAVL<int, int> tree;

  int option = 1;
  int c;

  cout << "1.Modo Demostracion\n"
  "2.Modo Estadistico\n"
  "Seleccione un Modo:"<< endl;
  cin >> c;

  switch ( c ){
    case 1:
      while (option!=0) {
          cout <<
            "0 - Salir\n"
            "1 - Insertar Clave\n"
            "2 - Eliminar Clave" << endl;
          cin >> option;

          switch (option) {
          case 0:
            break;
          case 1:
            cout << "Clave: " << flush;
            int aux;
            cin >> aux;
            tree.insert(0,aux);
            tree.byLevels();
            break;
          case 2:
            cout << "Clave: " << flush;
            cin >> aux;
            tree.eliminar(aux);
            tree.byLevels();
            break;
          default:  
  			break;  
          }
      }
      break;
    case 2:
      while(option!=0){

        int tam = 0;
        int pruebas = 0;

        cout << "Tamaño del arbol:";
        cin >> tam;
        cout << endl;
        cout << "Numero de Pruebas:";
        cin >> pruebas;
        cout << endl;

        TreeAVL<int, DNI> tree;
        vector<DNI> vec;

        for (int i = 0; i < (2*tam); ++i)
        {
          vec.push_back(DNI());
        }

        for (int i = 0; i < tam; i++) {
          tree.insert(0, vec[i]);
        }

        cout << setw(20) << "N" << setw(10) << "Pruebas" << setw(10)  << "Minimo" << setw(10) << "Medio" << setw(10) << "Maximo\n" 
        << setw(10) << "Busqueda" << setw(10) << tam << setw(10) << pruebas;
        for (int i = 0; i < pruebas; i++) {
          DNI::counter.start();
          tree.search(vec[rand()%pruebas]);
          DNI::counter.stop();
        }
        cout << setw(10) << DNI::counter.getMin()
             << setw(10) << DNI::counter.getAccum()/pruebas
             << setw(10) << DNI::counter.getMax() << endl;
        DNI::counter.reset();

        cout << setw(10) << "Insercion" << setw(10) << tam << setw(10) << pruebas;
        for (int i = 0; i < pruebas; i++) {
          DNI::counter.start();
          tree.search(vec[tam + rand() % pruebas]);
          DNI::counter.stop();
        }
        cout << setw(10) << DNI::counter.getMin()
             << setw(10) << DNI::counter.getAccum()/pruebas
             << setw(10) << DNI::counter.getMax() << endl;
        DNI::counter.reset();
        cout << endl;

      }
    break;
   default:
   	break;
 }

  return 0;
};

