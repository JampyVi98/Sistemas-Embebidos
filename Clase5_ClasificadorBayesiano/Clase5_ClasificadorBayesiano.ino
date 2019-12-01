/* CLASIFICADOR BAYESIANO
   N° de etiquetas
   N° de filas y columnas
   tags=1,2,3
   P(1)= Sumatoria de elementos tag1 / Total filas
   P(2)= Sumatoria de elementos tag2 / Total filas
   P(3)= Sumatoria de elementos tag3 / Total filas
   P(x)= Sumatoria de los elementos en circunferencia  / numero de filas
        Circunferencia:
          Distancia entre la nueva instancia y base de datos
          Encontrar distancia mayor y dividir para las distancia
          Definir radio de circunferencia (0-1)
   P(x|1)=Elementos en circunferencia con etiqueta 1 / Etiquetas 1
   P(x|2)=Elementos en circunferencia con etiqueta 2 / Etiquetas 2
   P(x|3)=Elementos en circunferencia con etiqueta 3 / Etiquetas 3
   P(1|x)=P(1)*P(x|1)/P(x)
   P(2|x)=P(2)*P(x|2)/P(x)
   P(3|x)=P(3)*P(x|3)/P(x)
   Encontrar probabilidad mayor
*/
#include"matriz_entrenamiento.h" //Llamar matriz de entrenamiento

float datos_prueba[5] = {6.9, 3.1, 5.1, 2.3, 3};
void setup() {
  Serial.begin(9600);
  bayes(3, 120, 5, 0.2);
}

void loop() {
}

void bayes(int tags, int filas, int columnas, float r) {
  float prob[3][tags];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < tags; j++) {
      prob[i][j] = 0;
      if (i == 0)
        prob[i][j] = j + 1;
    }
  }
  for (int t = 0; t < tags; t++) {
    for (int i = 0; i < filas; i++) {
      if (matriz[i][columnas - 1] == t+1)
        prob[1][t]++;
        prob[2][t]=prob[1][t]/filas;
    }
  }

  Serial.println("PROBABILIDADES DE ETIQUETAS");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < tags; j++) {
      Serial.print(prob[i][j], 1);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
}
