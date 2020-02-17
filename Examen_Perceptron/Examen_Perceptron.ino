#include "base.h" //Llamar base de datos
float x[4], y; //Variables input y output
float peso[5] = {0.1, 0.1, 0.1, 0.1, -5}, pre_peso[5] , change[5]; //Arrays de peso actual y anterior
/*
 * ARRAY PESO y PRE_PESO
 * peso1  peso2 peso 3 peso 4 umbral
 * 
 * ARRAY DE CAMBIOS (Determina si habrá cambios o no en el peso)
 * cambio_w1 cambio_w2 cambio_w3 cambio W4 cambio_umbral
 * 
 * ARRAY INPUTS
 * x1 x2 x3 x4
 */
boolean sw = false; //Switch on off
int i = 0, j = 0; //Variables contador

void setup() {
  Serial.begin(250000); //Iniciar serial
}

void loop() {
  perceptron(300, 5, 0.003); 
}

void perceptron(int fil, int col, float E) { //Función perceptrón, E=factor de aprendizaje
  if (!sw) {
    for (i = 0; i < fil; i++) {
      for (j = 0; j < col; j++) { //Llenar array de peso anterior con pesos actuales
        if (j < 4)
          x[j] = traning[i][j];
        pre_peso[j] = peso[j];
      }
      Serial.println("--------------------");
      Serial.print("Peso 1: ");
      Serial.println(peso[0]);
      Serial.print("Peso 2: ");
      Serial.println(peso[1]);
      Serial.print("Peso 3: ");
      Serial.println(peso[2]);
      Serial.print("Peso 4: ");
      Serial.println(peso[3]);
      Serial.print("Umbral: ");
      Serial.println(peso[4]);
      y = neurona(x, peso);
//      Serial.println(y);
      Serial.println(funcion(y));
      if (funcion(y) != traning[i][4]) { //Comparar estiqueta resultante y real
        Serial.println("F");
        for (j = 0; j < col; j++) { //Corrección de pesos y Umbral en caso de necesitarlo
          if (j < 4) {
            //error = resultado esperado - resultado obtenido
            change[j] = E * x[j] * (traning[i][4] - y); //Cambio Pesos = E*(error)*x
          } else {
            change[j] = E * (traning[i][4] - y); //Cambio Umbral = E*(error)
          }
          peso[j] = pre_peso[j] + change[j]; //Pesos = peso anterior + cambio
        }
      } else { //En caso de no necesitar corrección
        Serial.println("OK");
        for (j = 0; j < col; j++) { 
          change[j] = 0; //Cambio de 0
          peso[j] = pre_peso[j] + change[j];
        }
      }
    }
    sw = true;
  }
}

float neurona(float in[], float w[]) { //Función de neurona
  return w[4] + in[0] * w[0] + in[1] * w[1] + in[2] * w[2] + in[3] * w[3]; //Sumatoria(Xi*Wi)+umbral
}

float funcion(float d) { //Función de activación
  //  Serial.println(d);
  if (d > 0) //Determinar etiqueta
    return 1;
  else
    return 2;
}
