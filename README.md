# **Parcial Arquitectura de Hardware: Nicolás Echeverri y Samuel Corrales**

## Primer Punto: calcular las raíces de un polinomio grado 2

En este programa el usuario puede ingresar tres números que representan los tres valores en una ecuación cuadrática $ax^{2}+bx+c=0$, haciendo uso del teclado matricial, al ingresar un número el usuario debe presionar la tecla '#' a modo de una tecla 'Enter' para poder pasar a ingresar el siguiente número. Al final el programa debería devolver por consola los dos resultados de la ecuación.

### Declaración de todos los caracteres en el teclado

A continuación se muestra cómo se inicializan todas las teclas:

```C++

char keyMap[numRows][numCols] = {{'1', '2', '3', 'A'},
                                  {'4', '5', '6', 'B'},
                                  {'7', '8', '9', 'C'},
                                  {'*', '0', '#', 'D'}};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8), DigitalIn(D9)};

```

### Almacenamiento de cada valor en la ecuación

Luego se enciende la fila que el usuario ingresa:

```C++

int main() {
   int contador = 0;
   float numeros[3];
   string numero;

   while (true) {
     for (int i = 0; i < numRows; i++) {
       rowPins[i] = 0;

       for (int j = 0; j < numCols; j++) {
         if (!colPins[j]) {
           numero += keyMap[i][j];
           ThisThread::sleep_for(500ms);
         }
       }
       rowPins[i] = 1;
      }
    }
}

```

Se itera a través de todas las filas para encederlas una a una. Luego se verifica si alguna tecla ha sido presionada por medio de esta línea de código:

```C++

if (!colPins[j])

```
Luego de leer la tecla oprimida por el usuario, el caracter que corresponde a dicha tecla se concatena a la cadena 'numero' para guardar un número de más de un dígito.

Ahora, para poder almacenar los tres números, mencionamos anteriormente que se debe presionar la tecla '#' para poder pasar a almacenar el siguiente número, dicho proceso se lleva a cabo mediante la siguiente parte del código:

```C++

if (numero.back() == '#') {
     numero.pop_back();
     numeros[contador] = stof(numero);
     contador++;
     numero = "";

     if (contador == 3) {
       break;
     }
}

```

Primero se verifica si el último caracter de la cadena número es el símbolo '#' a continuación se elimina dicho símbolo para poder usarlo luego en el cálculo de los resultados de la ecuación. El sistema detecta que ya se han ingresado los tres números cuando la longitud de el arreglo ``` numeros ``` tiene un valor de 3, es ahí cuando sale del ciclo while infinito.

### Cálculo de los resultados de la ecuación

Finalmente, con los tres valores de la ecuación se pasan a calcular los dos resultadosde la misma con la fórmula cuadrática general:

```C++

 if (determinante < 0) {
    cout << "No existe una solución en los números reales" << endl;
    return 0;
  }

  float x1, x2;

  x1 = (-b + sqrt(determinante)) / (2 * a);
  x2 = (-b - sqrt(determinante)) / (2 * a);

  cout << "La solucion de la ecuación es: x1 = " << x1 << endl;
  cout << "La solucion de la ecuación es: x2 = " << x2 << endl;

```

## Segundo Punto: cálculo de calificación alfanumérica

Aplicación que solicite al usuario el ingreso de una nota N del 0 al 10 y despliegue una nota alfanumérica de la forma mostrada en el código.

### Declaración de todos los caracteres en el teclado

A continuación se muestra cómo se inicializan todas las teclas:

```C++

char keyMap[numRows][numCols] = {{'1', '2', '3', 'A'},
                                  {'4', '5', '6', 'B'},
                                  {'7', '8', '9', 'C'},
                                  {'*', '0', '#', 'D'}};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8), DigitalIn(D9)};

```

### Seleccionar tecla del teclado matricial

Primero recorremos con un ciclo for los renglones verificando la corriente del renglón, después en otro ciclo verificamos las columnas y si cumple la condición se le asigna a la variable ``` num ``` el número seleccionado.

```C++

char getKeyPressed() {
    for (int i = 0; i < numRows; i++) {
        rowPins[i] = 0;
        for (int j = 0; j < numCols; j++) {
            if (!colPins[j]) {
                char num = keyMap[i][j];
                ThisThread::sleep_for(500ms);  // Avoid multiple readings while the key is pressed
                return num;
            }
        }
        rowPins[i] = 1;
    }
    return '\0';
}

```

### Verificación de nota

Primero verificamos si el usuario esta ingresando un valor y los esta confirmando con '#'

```C++

string numero = "";
float grade;
while (true) {
    char key = getKeyPressed();
    if (key != '\0') {
        if (key == '#') {
            if (numero.empty()) {
                printf("No grade entered.\n");
            }
```

luego comenzamos a comprobar la nota ingresada con condicionales, los cuales imprimiran la nota dependiente a el valor ingresado por el usuario.

```C++
else {
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
}

```

Por último verificamos si el número ingresado es inválido, y retornamos 0 para que vuelva a empezar el ciclo.

```C++

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

```

## Tercer punto: Encender Led RGB con el teclado

Aplicación que permita generar colores en un LED RGB con base en el código de color RGB.

### Definimos las RGB

Definimos el periodo, creamos PwmOut para controlar los led y definimos la funsion set Color para establecer la intecidad de los RGB.

```C++

#define BLINKING_RATE     50ms

UnbufferedSerial serial(USBTX, USBRX, 9600);
PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

void setRGBColor(float red, float green, float blue) {
    ledR = red;
    ledG = green;
    ledB = blue;
}

```

### Declaración de todos los caracteres en el teclado

A continuación se muestra cómo se inicializan todas las teclas:

```C++

char keyMap[numRows][numCols] = {{'1', '2', '3', 'A'},
                                  {'4', '5', '6', 'B'},
                                  {'7', '8', '9', 'C'},
                                  {'*', '0', '#', 'D'}};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8), DigitalIn(D9)};

```

### Buscar en la matriz
estas variables se utilizan para almacenar y rastrear datos dentro del programa en el que se encuentran. Sus nombres sugieren que están relacionadas con el manejo de entrada de datos y el seguimiento de valores numéricos.

```C++

void showColors() {
    char inputBuffer[32];
    int bufferIndex = 0;
    unsigned int numerosD[3];
    int numeroA = 0;

    while (numeroActual < 3) {
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;

            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    char keyPressed = keyMap[i][j];

```
El ciclo while es el que hemos visto en los anteriores casos, es para rastrear el numero en la matriz.

### Elegir intensidad de cada color(RGB)
Al principio del codigo mostrado podemos ver que para confirmaar la intensidad de un numero tenemos que precionar el *
Esta línea coloca un carácter nulo ('\0') al final de una cadena de caracteres llamada inputBuffer. Esto es importante porque indica el final de la cadena y prepara inputBuffer para ser procesada como una cadena de caracteres.

```C++
                    if (keyPressed == '*') {
                        inputBuffer[bufferIndex] = '\0';
```

Esta línea utiliza la función sscanf para analizar la cadena de caracteres almacenada en inputBuffer como un número sin signo (%u) y almacenar ese valor en el arreglo numerosD en la posición indicada por numeroActual(numeroA).
Despues lo imprime

```C++
                        sscanf(inputBuffer, "%u", &numerosD[numeroA]);
                        printf("Número %d ingresado: %u\n", numeroA + 1, numerosD[numeroA]);
```

Esta línea utiliza la función memset para llenar inputBuffer con ceros, es decir, para borrar su contenido anterior y prepararlo para recibir una nueva entrada del usuario. Y el numeroA va incrementando demostrando que se guardo excitosamente.

```C++

                        memset(inputBuffer, 0, sizeof(inputBuffer));
                        bufferIndex = 0;

                        numeroA++;
```

Esta línea verifica si se han almacenado ya tres números (o más) en el arreglo numerosD. Si es así, el programa sale del bucle en el que se encuentra. Esto sugiere que el programa espera que el usuario ingrese tres números y luego continúa con alguna otra lógica o procesamiento.

```C++
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

```

este código toma tres valores numéricos almacenados en numerosD , normaliza esos valores al rango de 0 a 1 y luego invierte esos valores (restando de 1) para calcular las componentes roja, verde y azul de un color. Luego, utiliza la función setRGBColor para aplicar ese color calculado en algún contexto específico.

```C++
float red = 1 - (float)(numerosD[0] / 255.0f);
    float green = 1 - (float)(numerosD[1] / 255.0f);    
    float blue = 1 - (float)(numerosD[2] / 255.0f);

    setRGBColor(red, green, blue);
}
int main() {
    while (1) {
        showColors();
    }
}
```







