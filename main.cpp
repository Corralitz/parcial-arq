#include "mbed.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

const int numRows = 4;
const int numCols = 4;

char keyMap[numRows][numCols] = {{'1', '2', '3', 'A'},
                                 {'4', '5', '6', 'B'},
                                 {'7', '8', '9', 'C'},
                                 {'-', '0', '#', 'D'}};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4),
                               DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8),
                              DigitalIn(D9)};

PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

// Escoger una de las tres opciones por el teclado

int escogerMenu() {
  int eleccion = -1;

  while (eleccion < 0 || eleccion > 3) {
    if (eleccion < 0 || eleccion > 3)
      cout << "Numero invalido para escoger." << endl;

    for (int i = 0; i < numRows; i++) {
      rowPins[i] = 0;

      for (int j = 0; j < numCols; j++) {
        if (colPins[j] == 0) {

          char tecla = keyMap[i][j];

          if (tecla >= 0 && tecla <= 3)
            eleccion = tecla;
          else if (tecla == '#')
            break;
          ThisThread::sleep_for(500ms);
        }
      }
      rowPins[i] = 1;

      if (eleccion >= 0 && eleccion <= 3)
        break;
    }
  }
  return eleccion;
}

// PUNTO 1: Raices de un polinomio

int raices() {
  int contador = 0;
  float numeros[3];
  string numero;

  cout << "Bienvenido(a), ingrese cada valor de la ecuacion cuadratica, "
          "utilice la tecla \'*\' para poner un signo \'-\'."
       << endl
       << "Luego presione \'#\' para terminar de ingresar el numero, al "
          "ingresar "
          "los tres valores el programa debe arrojar la respuesta."
       << endl;

  while (true) {
    for (int i = 0; i < numRows; i++) {
      rowPins[i] = 0;

      for (int j = 0; j < numCols; j++) {
        if (colPins[j] == 0) {
          numero += keyMap[i][j];
          ThisThread::sleep_for(500ms);
        }
      }
      rowPins[i] = 1;
    }

    if (numero.back() == '#') {
      numero.pop_back();
      numeros[contador] = stof(numero);
      cout << "Numero ingresado: " << numeros[contador] << endl;
      contador++;
      numero = "";

      if (contador == 3)
        break;
    }
  }

  float a = (numeros[0]);
  float b = (numeros[1]);
  float c = (numeros[2]);

  float determinante = pow(b, 2) - 4 * a * c;

  if (determinante < 0) {
    cout << "No existe una solución en los números reales" << endl;
    return 0;
  }

  float x1, x2;

  x1 = (-b + sqrt(determinante)) / (2 * a);
  x2 = (-b - sqrt(determinante)) / (2 * a);

  cout << "La solucion de la ecuación es: x1 = " << x1 << endl;
  cout << "La solucion de la ecuación es: x2 = " << x2 << endl;

  return 0;
}

// PUNTO 2: Calcular nota alfanumerica

char getKeyPressed() {
  for (int i = 0; i < numRows; i++) {
    rowPins[i] = 0;
    for (int j = 0; j < numCols; j++) {
      if (!colPins[j]) {
        char num = keyMap[i][j];
        ThisThread::sleep_for(500ms);
        return num;
      }
    }
    rowPins[i] = 1;
  }
  return '\0';
}

int notas() {
  string numero = "";
  float grade;
  while (true) {
    char key = getKeyPressed();
    if (key != '\0') {
      if (key == '#') {
        if (numero.empty()) {
          printf("No grade entered.\n");
        } else {
          grade = stof(numero);
          char alphanumeric_grade;
          if (grade >= 0 && grade <= 3) {
            alphanumeric_grade = 'A';
          } else if (grade > 3 && grade <= 4) {
            alphanumeric_grade = 'B';
          } else if (grade > 4 && grade <= 5) {
            alphanumeric_grade = 'C';
          } else if (grade > 5 && grade <= 7) {
            alphanumeric_grade = 'D';
          } else if (grade > 7 && grade < 9) {
            alphanumeric_grade = 'E';
          } else if (grade >= 9 && grade <= 10) {
            alphanumeric_grade = 'F';
          } else {
            printf("Invalid grade entered.\n");
            numero = "";
            continue;
          }
          printf("Alphanumeric grade: %c\n", alphanumeric_grade);
          numero = "";
        }
      } else {
        numero += key;
      }
    }
  }
  return 0;
}

// PUNTO 3: Mostrar un color en particular ingresando los valores de R, G y B

void setRGBColor(float red, float green, float blue) {
  ledR = red;
  ledG = green;
  ledB = blue;
}

void showColors() {
  char inputBuffer[32];
  int bufferIndex = 0;
  unsigned int numerosD[3];
  int numeroA = 0;

  while (numeroA < 3) {
    for (int i = 0; i < numRows; i++) {
      rowPins[i] = 0;

      for (int j = 0; j < numCols; j++) {
        if (!colPins[j]) {
          char keyPressed = keyMap[i][j];

          if (keyPressed == '#') {
            inputBuffer[bufferIndex] = '\0';

            sscanf(inputBuffer, "%u", &numerosD[numeroA]);
            printf("Número %d ingresado: %u\n", numeroA + 1, numerosD[numeroA]);

            memset(inputBuffer, 0, sizeof(inputBuffer));
            bufferIndex = 0;

            numeroA++;

            if (numeroA >= 3) {
              break;
            }
          } else {
            inputBuffer[bufferIndex] = keyPressed;
            bufferIndex++;
          }

          ThisThread::sleep_for(500ms);
        }
      }

      if (numeroA >= 3) {
        break;
      }

      rowPins[i] = 1;
    }
  }

  float red = 1 - (float)(numerosD[0] / 255.0f);
  float green = 1 - (float)(numerosD[1] / 255.0f);
  float blue = 1 - (float)(numerosD[2] / 255.0f);

  setRGBColor(red, green, blue);
}

int codigoColor() {
  printf("Ingrese numero de 0-255 para el RGB");
  while (1) {
    showColors();
  }
}

// MAIN

int main() {
  cout << "Elija una opcion oprimiendo 1, 2 o 3 en el teclado para seguir con "
          "un programa y \'#\' para confirmar la elecccion:"
       << endl
       << "1) Raices de un polinomio." << endl
       << "2) Mostrar nota alfanumerica." << endl
       << "3) Ingresar un color al LED." << endl;

  int opcion = escogerMenu();

  switch (opcion) {
  case 1:
    raices();
    break;
  case 2:
    notas();
    break;
  case 3:
    codigoColor();
    break;
  default:
    cout << "Opcion invalida, por favor ingrese otro numero." << endl;
  }
}
