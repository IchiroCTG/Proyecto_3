#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <unordered_map>
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;


using namespace std;
//Estructuras
struct Vestimenta{
  string Categoria;
  int Durabilidad;
  };
//Fin Estructuras
//Inicio Codigos de Limpieza
void Limpiar(vector<Vestimenta>&vestimentas,vector<int>&caminos,vector<int>&puntajes,int cantV,int cantC,int cantP){//Limpiar los vectores para la siguiente generacion
  for(int i=0;i<cantV;i++){
    vestimentas[i].Categoria="a";
    vestimentas[i].Durabilidad=0;
  }
  for(int i=0;i<cantC;i++){
    caminos[i]=0;
  }
  for (int i = 0; i < cantP; i++)
  {
    puntajes[i]=0;
  }
  
}
void limpiar_pantalla() //Funcion para limipiar la Pantalla
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
//Fin Codigos de Limpieza
//Inicio Codigos de Corroboración
string typeVestimenta(int vest){//Categoria de Vestimenta
  switch (vest)
  {
  case 0: return "Casco";
  case 1: return "Botas";
  case 2: return "Pechera";
  case 3: return "Pantalones";
  case 4: return "Guantes";
  case 5: return "Collar";
  case 6: return "Pulsera";
  case 7: return "Aros";
  case 8: return "Amuleto";
  case 9: return "Calcetines";
  case 10: return "Anillos";
  case 11: return "Cinturon";
  case 12: return "Sombrero";
  case 13: return "Bufanda";
  case 14: return "Escudo";
  };
  return "a";
}
bool Existe_BBV(vector<Vestimenta>& vec, Vestimenta valor){//Revisa si existe
    int inicio = 0;
    int fin = vec.size() - 1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        if(vec[medio].Categoria==valor.Categoria){
          if (vec[medio].Durabilidad == valor.Durabilidad) {
              return true;
          } else if (vec[medio].Durabilidad < valor.Durabilidad) {
              inicio = medio + 1;
          }   else {
              fin = medio - 1;
          }
        }
    }

    return false;
}
bool Existe_BBI(vector<int>& vec, int valor){
    int inicio = 0;
    int fin = vec.size() - 1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;

        if (vec[medio] == valor) {
            return true;
        } else if (vec[medio] < valor) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    return false;
}
void IngresoV(vector<Vestimenta>&vestimentas){
  for (int i = 0; i < (int)vestimentas.size(); i++)
  {
    std::cout<<"Categoria: "<<vestimentas[i].Categoria<<" Durabilidad: "<<vestimentas[i].Durabilidad<<endl;
  }
  
}
void IngresoC(vector<int> &caminos){
  for (int i = 0; i < (int)caminos.size(); i++)
  {
    std::cout<<"Camino "<<i<<"  Peso: "<<caminos[i]<<endl;
  }
  
}
void IngresoP(vector<int>&puntajes){
  for(int i=0;i<(int)puntajes.size();i++){
    std::cout<<"Jugador "<<i<<"  Puntaje: "<<puntajes[i]<<endl; 
  }
}
//Fin Codigos de Corroboración
//Inicio Codigos de Generación
int generar_DatosIntRandom(int min, int max){//generacion de valores random entre datos minimos y maximos
   random_device rd;  // Dispositivo para generar números aleatorios
    mt19937 gen(rd()); // Generador de números aleatorios
    uniform_int_distribution<int> dist(min, max); // Rango de números aleatorios

    return dist(gen);
}
void generar_Ascendente(int cantP,vector<int>&puntajes_A,int cantC,vector<int>&caminos_A,int cantV,vector<Vestimenta>&vestimenta_A)
{
    for (int i = 0; i < cantP; i++){
      puntajes_A[i]=i+101;
    }
    for (int i = 0; i < cantC; i++){
      caminos_A[i] =i+101;
    }
    int index=0;
    for(int i=0;i<cantV;i++){ 
      for(int f=0;f<15;f++){
        vestimenta_A[index].Categoria = typeVestimenta(f);
        vestimenta_A[index].Durabilidad = i+100;
        index++;
      }
    }
}
void generar_Descendente(int cantP,vector<int>&puntajes_D,int cantC,vector<int>&caminos_D,int cantV,vector<Vestimenta>&vestimenta_D){
    for (int i = 0; i < cantP; i++){
      puntajes_D[i] = (cantP+100)-i;
    }
    for (int i = 0; i < cantC; i++){
      caminos_D[i] = (cantC+100)-i;
    }
    int index=0;    
    for(int i=0;i<cantV;i++){ 
      for(int f=0;f<15;f++){
        vestimenta_D[index].Categoria = typeVestimenta(f);
        vestimenta_D[index].Durabilidad = (cantV+100)-i;
        index++;
      }
    }
}
void generar_Aleatorio(int cantP,vector<int>&puntajes_R,int cantC,vector<int>&caminos_R,int cantV,vector<Vestimenta>&vestimenta_R){
    for (int i = 0; i < cantP; i++){
      puntajes_R[i]=generar_DatosIntRandom(100,cantP+100);
    }
    for (int i = 0; i < cantC; i++){
      caminos_R[i] = generar_DatosIntRandom(100,cantC+100);
    }
    int index=0;
    for(int i=0;i<cantV;i++){ 
      for(int f=0;f<15;f++){
        vestimenta_R[index].Categoria = typeVestimenta(f);
        vestimenta_R[index].Durabilidad = generar_DatosIntRandom(100,cantV+100);
        index++;
      }
    }
}
void generar_AleSinRepe(int cantP,vector<int>&puntajes_RSR,int cantC,vector<int>&caminos_RSR,int cantV,vector<Vestimenta>&vestimenta_RSR){
  int index=0;
  int score;
  int street;
  Vestimenta vest;
  while (index<cantP)
  {
   score=generar_DatosIntRandom(0,cantP);
    if(!Existe_BBI(puntajes_RSR,score)){
      puntajes_RSR[index]=score;
      index++;
    }
  }
  index=0;
  while (index<cantC)
  {
   street=generar_DatosIntRandom(100,cantC+100);
    if(!Existe_BBI(caminos_RSR,street)){
      puntajes_RSR[index]=score;
      index++;
    }
  }
  int index2=0;
  while(index<cantV){ 
    for(int i=0;i<15;i++){
      vest.Categoria = typeVestimenta(i);
      vest.Durabilidad =generar_DatosIntRandom(100,cantV+100);
      if(!Existe_BBV(vestimenta_RSR,vest)){
         vestimenta_RSR[index2]=vest;
        index++;
        index2++;
      }
    }
  }

}
//Fin Codigos de Generacion

//Inicio Codigos de Ordenamiento
    //Selection Sort
double selectionSortV(vector<Vestimenta> vestimenta,int Orden) {
      int n = vestimenta.size();
      auto start = high_resolution_clock::now();
      for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Buscar el índice del elemento más pequeño en la parte no ordenada
        for (int j = i + 1; j < n; j++) {
            if(Orden==0){
              if (vestimenta[j].Durabilidad < vestimenta[minIndex].Durabilidad) {
                minIndex = j;
              }
            }
            else{
              if (vestimenta[j].Durabilidad > vestimenta[minIndex].Durabilidad) {
                minIndex = j;
              }
            }
        }
        // Intercambiar el elemento más pequeño con el primero de la parte no ordenada
        if (minIndex != i) {
            swap(vestimenta[i], vestimenta[minIndex]);
        }
      }
    auto end = high_resolution_clock::now();
    vestimenta.clear();
    return duration_cast<duration<double>>(end - start).count();
}
double selectionSortI(vector<int> vec,int Orden) {
    int n = vec.size();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Buscar el índice del elemento más pequeño en la parte no ordenada
        for (int j = i + 1; j < n; j++) {
              if(Orden==0){
                if (vec[j] < vec[minIndex]) {
                  minIndex = j;
                }
              }
              else{
                if (vec[j] > vec[minIndex]) {
                  minIndex = j;
                }
              }
        }

        // Intercambiar el elemento más pequeño con el primero de la parte no ordenada
        if (minIndex != i) {
            swap(vec[i], vec[minIndex]);
        }
    }
  auto end = high_resolution_clock::now();
  vec.clear();
  return duration_cast<duration<double>>(end - start).count();    
}
    //Bubble Sort
double bubbleSortI(vector<int> vec,int Orden) {
    int n = vec.size();
    auto start = high_resolution_clock::now();
    bool intercambio;

    for (int i = 0; i < n - 1; i++) {
        intercambio = false;

        // Hacer burbujear el elemento más grande hacia el final
        for (int j = 0; j < n - i - 1; j++) {
            if (Orden==0){
              if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
                intercambio = true;
              }
            }
            else{
              if (vec[j] < vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
                intercambio = true;
              }
            }
            
        }

        // Si no hubo intercambios en esta iteración, el vector está ordenado
        if (!intercambio) {
            break;
        }
    }
    auto end = high_resolution_clock::now();
    vec.clear();
    return duration_cast<duration<double>>(end - start).count();  
}
double bubbleSortV(vector<Vestimenta> vestimenta,int Orden) {
    int n = vestimenta.size();
    auto start = high_resolution_clock::now();
    bool intercambio;
    
    for (int i = 0; i < n - 1; i++) {
        intercambio = false;

        // Hacer burbujear el elemento más grande hacia el final
        for (int j = 0; j < n - i - 1; j++) {
            if(Orden==0){
              if (vestimenta[j].Durabilidad > vestimenta[j + 1].Durabilidad) {
                swap(vestimenta[j], vestimenta[j + 1]);
                intercambio = true;
              }
            }
            else{
              if (vestimenta[j].Durabilidad < vestimenta[j + 1].Durabilidad) {
                swap(vestimenta[j], vestimenta[j + 1]);
                intercambio = true;
              }              
            }
        }

        // Si no hubo intercambios en esta iteración, el vector está ordenado
        if (!intercambio) {
            break;
        }
    }
  auto end = high_resolution_clock::now();
  vestimenta.clear();
  return duration_cast<duration<double>>(end - start).count();
}
    //Insertion Sort
double insertionSortV(vector<Vestimenta> vestimenta,int Orden) {
    int n = vestimenta.size();
    auto start = high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int valorActual = vestimenta[i].Durabilidad;
        int j = i - 1;

        // Desplazar los elementos mayores que valorActual hacia la derecha
        if(Orden==0){
          while (j >= 0 && vestimenta[j].Durabilidad > valorActual) {
            vestimenta[j + 1] = vestimenta[j];
            j--;
          }
        }
        else{
          while (j >= 0 && vestimenta[j].Durabilidad < valorActual) {
            vestimenta[j + 1] = vestimenta[j];
            j--;
          }          
        }

        // Insertar valorActual en la posición correcta
        vestimenta[j + 1].Durabilidad = valorActual;
    }
    auto end = high_resolution_clock::now();
    vestimenta.clear();
    return duration_cast<duration<double>>(end - start).count();
}
double insertionSortI(vector<int> vec,int Orden) {
    int n = vec.size();
    auto start = high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int valorActual = vec[i];
        int j = i - 1;

        // Desplazar los elementos mayores que valorActual hacia la derecha
        if(Orden==0){
          while (j >= 0 && vec[j] > valorActual) {
            vec[j + 1] = vec[j];
            j--;
          }
        }
        else{
           while (j >= 0 && vec[j] < valorActual) {
            vec[j + 1] = vec[j];
            j--;
          }
        }

        // Insertar valorActual en la posición correcta
        vec[j + 1] = valorActual;
    }
  auto end = high_resolution_clock::now();
  vec.clear();
  return duration_cast<duration<double>>(end - start).count();
}
    //Shell Sort
double shellSortV(vector<Vestimenta> vestimenta,int Orden) {
      int n = vestimenta.size();
      auto start = high_resolution_clock::now();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = vestimenta[i].Durabilidad;
            int j = i;

            // Desplazar los elementos mayores que temp hacia la derecha
            if(Orden==0){
              while (j >= gap && vestimenta[j - gap].Durabilidad > temp) {
                  vestimenta[j] = vestimenta[j - gap];
                  j -= gap;
              }
            }
            else{
              while (j >= gap && vestimenta[j - gap].Durabilidad < temp) {
                  vestimenta[j] = vestimenta[j - gap];
                  j -= gap;
              }
            }
            
            // Insertar temp en la posición correcta
            vestimenta[j].Durabilidad = temp;
        }
    }
        auto end = high_resolution_clock::now();
        vestimenta.clear();
    return duration_cast<duration<double>>(end - start).count();
}
double shellSortI(vector<int> arr,int Orden) {
  int n = arr.size();
  auto start = high_resolution_clock::now();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            // Desplazar los elementos mayores que temp hacia la derecha
            if(Orden==0){
              while (j >= gap && arr[j - gap] > temp) {
                  arr[j] = arr[j - gap];
                  j -= gap;
              }
            }
            else{
               while (j >= gap && arr[j - gap] < temp) {
                arr[j] = arr[j - gap];
                j -= gap;
              }
            }

            // Insertar temp en la posición correcta
            arr[j] = temp;
        }
    }
    auto end = high_resolution_clock::now();
    arr.clear();
    return duration_cast<duration<double>>(end - start).count();
}
    //Merge Sort
void mergeV(vector<Vestimenta>& arr, int inicio, int medio, int fin, int Orden) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    vector<Vestimenta> L(n1);
    vector<Vestimenta> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[medio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = inicio;

    // Combinar las dos mitades en orden ascendente o descendente
    while (i < n1 && j < n2) {
        if ((Orden==0 && L[i].Durabilidad <= R[j].Durabilidad) || (Orden!=0 && L[i].Durabilidad >= R[j].Durabilidad)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
double mergeSortV(vector<Vestimenta> arr, int inicio, int fin, int Orden) {
  auto start = high_resolution_clock::now();
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        mergeSortV(arr, inicio, medio, Orden);
        mergeSortV(arr, medio + 1, fin, Orden);
        mergeV(arr, inicio, medio, fin, Orden);
    }
    auto end = high_resolution_clock::now();
    arr.clear();
    return duration_cast<duration<double>>(end - start).count();
}
void merge(vector<int>& arr, int inicio, int medio, int fin, int Orden) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[medio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = inicio;

    // Combinar las dos mitades en orden ascendente o descendente
    while (i < n1 && j < n2) {
        if ((Orden==0 && L[i] <= R[j]) || (Orden!=0 && L[i] >= R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
double mergeSort(vector<int> arr, int inicio, int fin, int Orden) {
    auto start = high_resolution_clock::now();
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        mergeSort(arr, inicio, medio, Orden);
        mergeSort(arr, medio + 1, fin, Orden);
        merge(arr, inicio, medio, fin, Orden);
    }
    auto end = high_resolution_clock::now();
    arr.clear();
    return duration_cast<duration<double>>(end - start).count();
}
    //Quick Sort
int particionV(vector<Vestimenta>& arr, int inicio, int fin, int Orden) {
    int pivote = arr[fin].Durabilidad;
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if ((Orden==0 && arr[j].Durabilidad <= pivote) || (Orden!=0 && arr[j].Durabilidad >= pivote)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[fin]);
    return i + 1;
}  
double quickSortV(vector<Vestimenta> vestimenta, int inicio, int fin,int Orden) {
    auto start = high_resolution_clock::now();
    if (inicio < fin) {
        int indicePivote = particionV(vestimenta, inicio, fin, Orden);

        quickSortV(vestimenta, inicio, indicePivote - 1, Orden);
        quickSortV(vestimenta, indicePivote + 1, fin, Orden);
    }
    auto end = high_resolution_clock::now();
    vestimenta.clear();
    return duration_cast<duration<double>>(end - start).count();
}
int particion(vector<int>& arr, int inicio, int fin, int Orden) {
    int pivote = arr[fin];
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if ((Orden==0 && arr[j] <= pivote) || (Orden!=0 && arr[j] >= pivote)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[fin]);
    return i + 1;
}
double quickSortI(vector<int> arr, int inicio, int fin, int Orden) {
    auto start = high_resolution_clock::now();
    if (inicio < fin) {
        int indicePivote = particion(arr, inicio, fin, Orden);

        quickSortI(arr, inicio, indicePivote - 1, Orden);
        quickSortI(arr, indicePivote + 1, fin, Orden);
    }
    auto end = high_resolution_clock::now();
    arr.clear();
    return duration_cast<duration<double>>(end - start).count();
}
    //Heap Sort
void heapifyV(vector<Vestimenta>& arr, int n, int i, int Orden) {
    int mayor_o_menor = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (Orden==0) {
        if (izquierda < n && arr[izquierda].Durabilidad > arr[mayor_o_menor].Durabilidad) {
            mayor_o_menor = izquierda;
        }

        if (derecha < n && arr[derecha].Durabilidad > arr[mayor_o_menor].Durabilidad) {
            mayor_o_menor = derecha;
        }
    } else {
        if (izquierda < n && arr[izquierda].Durabilidad < arr[mayor_o_menor].Durabilidad) {
            mayor_o_menor = izquierda;
        }

        if (derecha < n && arr[derecha].Durabilidad < arr[mayor_o_menor].Durabilidad) {
            mayor_o_menor = derecha;
        }
    }

    if (mayor_o_menor != i) {
        swap(arr[i], arr[mayor_o_menor]);
        heapifyV(arr, n, mayor_o_menor, Orden);
    }
}
double heapSortV(vector<Vestimenta> arr, int Orden) {
    int n = arr.size();
    auto start = high_resolution_clock::now();
    // Construir el montículo (heap)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyV(arr, n, i, Orden);
    }

    // Extraer elementos del montículo uno por uno
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyV(arr, i, 0, Orden);
    }
    auto end = high_resolution_clock::now();
    arr.clear();
    return duration_cast<duration<double>>(end - start).count();
}
void heapify(vector<int>& arr, int n, int i, int Orden) {
    int mayor_o_menor = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (Orden==0) {
        if (izquierda < n && arr[izquierda] > arr[mayor_o_menor]) {
            mayor_o_menor = izquierda;
        }

        if (derecha < n && arr[derecha] > arr[mayor_o_menor]) {
            mayor_o_menor = derecha;
        }
    } else {
        if (izquierda < n && arr[izquierda] < arr[mayor_o_menor]) {
            mayor_o_menor = izquierda;
        }

        if (derecha < n && arr[derecha] < arr[mayor_o_menor]) {
            mayor_o_menor = derecha;
        }
    }

    if (mayor_o_menor != i) {
        swap(arr[i], arr[mayor_o_menor]);
        heapify(arr, n, mayor_o_menor, Orden);
    }
}
double heapSort(vector<int> arr, int Orden) {
    int n = arr.size();
    auto start = high_resolution_clock::now();
    // Construir el montículo (heap)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, Orden);
    }

    // Extraer elementos del montículo uno por uno
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, Orden);
    }
    auto end = high_resolution_clock::now();
    arr.clear();
    return duration_cast<duration<double>>(end - start).count();
}
void RacersI(vector<int>&vec,int Orden){
  std::cout<<"Selection Sort: " << selectionSortI(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Bubble Sort: "<< bubbleSortI(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Insertion Sort: "<< insertionSortI(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Shell Sort: "<<shellSortI(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Merge Sort: "<<mergeSort(vec,0,vec.size()-1,Orden)<<" segundos"<<endl;
  //std::cout<<"Quick Sort: "<<quickSortI(vec, 0, vec.size() - 1, Orden)<<" segundos"<<endl;
  std::cout<<"Heap Sort: "<<heapSort(vec,Orden)<<" segundos"<<endl;
}
void RacersV(vector<Vestimenta>&vec,int Orden){
  std::cout<<"Selection Sort: " << selectionSortV(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Bubble Sort: "<< bubbleSortV(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Insertion Sort: "<< insertionSortV(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Shell Sort: "<<shellSortV(vec,Orden)<<" segundos"<<endl;
  std::cout<<"Merge Sort: "<<mergeSortV(vec,0,vec.size()-1,Orden)<<" segundos"<<endl;
  //std::cout<<"Quick Sort: "<<quickSortV(vec,0,vec.size()-1,Orden)<<" segundos"<<endl;
  std::cout<<"Heap Sort: "<<heapSortV(vec,Orden)<<" segundos"<<endl;
}
void Ordenar(vector<Vestimenta> &vestimenta,vector<int>&caminos,vector<int>&puntajes,int mode,int Orden){
  string modo;
  string a;
  switch (mode)
  {
  case 0: modo = "Modo Lineal"; break;
  case 1: modo = "Modo Inverso"; break;
  case 2:modo = "Modo Aleatorio";break;
  default: modo = "Modo Aleatorio sin Repetecion";break;
  }
  cout<<"Carrera de Puntajes, "<<modo<<endl;
  RacersI(puntajes,Orden);
  cin>>a;
  limpiar_pantalla();
  cout<<"Carrera de Caminos, "<<modo<<endl;
  RacersI(caminos,Orden);
  cin>>a;
  limpiar_pantalla();
  cout<<"Carrera de Accesorios, "<<modo<<endl;
  RacersV(vestimenta,Orden);
  cin>>a;
  limpiar_pantalla();
}
int main(){
    int seleccion;
    int num_Aditamentos=0;
    int num_Puntajes=0;
    int num_Caminos=0;
    
    do{
        std::cout<<"Carreras de algoritmos"<<endl<<"1. Ascendente"<<endl<<"2. Descendente"<<endl<<"Opcion Elegida: ";
        std::cin>>seleccion;
    }while(seleccion!=1&&seleccion!=2);

    num_Aditamentos= generar_DatosIntRandom(500,1000);
    num_Puntajes = generar_DatosIntRandom(90000,100000);
    num_Caminos = generar_DatosIntRandom(50000,70000);

    vector<int> puntajes = vector<int>(num_Puntajes);
    vector<Vestimenta> aditamentos = vector<Vestimenta>(num_Aditamentos*15);
    vector<int> caminos = vector<int>(num_Caminos);
    
    
    
    if(seleccion==1){
        generar_Ascendente(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,0,0);
        Limpiar(aditamentos,caminos,puntajes,num_Aditamentos,num_Caminos,num_Puntajes);
        generar_Descendente(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,1,0);
        Limpiar(aditamentos,caminos,puntajes,num_Aditamentos,num_Caminos,num_Puntajes);
        generar_Aleatorio(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,2,0);
        Limpiar(aditamentos,caminos,puntajes,num_Aditamentos,num_Caminos,num_Puntajes);
        generar_AleSinRepe(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,3,0);
    }
    else{
        generar_Descendente(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,0,1);
        Limpiar(aditamentos,caminos,puntajes,num_Aditamentos,num_Caminos,num_Puntajes);
        generar_Ascendente(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,1,1);
        Limpiar(aditamentos,caminos,puntajes,num_Aditamentos,num_Caminos,num_Puntajes);
        generar_Aleatorio(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,2,1);
        Limpiar(aditamentos,caminos,puntajes,num_Aditamentos,num_Caminos,num_Puntajes);
        generar_AleSinRepe(num_Puntajes,puntajes,num_Caminos,caminos,num_Aditamentos,aditamentos);
        Ordenar(aditamentos,caminos,puntajes,3,1);
    }
    puntajes.clear();
    aditamentos.clear();
    caminos.clear();
    
    return 0;
}