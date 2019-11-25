
#include"matriz_entrenamiento.h" //Llamar matriz de entrenamiento

char respuesta;
void setup() {
  Serial.begin(9600);
  respuesta = cnn(3, 120, 5);
}

void loop() {
}

char cnn(int tags, int filas, int columnas) {
  float sum1, sum2, sum3, sumatoria = 0, distancia_menor = 3000, distancia;
  int cont1 = 0, cont2 = 0, cont3 = 0, drain = 0, source = 0, tag;
  /*
     centroides -> promedio
                    promedio por columna y por etiqueta
                    almaceno vectores
                    knn entre vectores y matriz de entrenamiento

  */

  float centroid[tags][columnas];
  for (int i = 0; i < tags; i++) {
    for (int j = 0; j < columnas; j++) {
      centroid[i][j] = 0;
      if (j == columnas - 1)
        centroid[i][j] = i + 1;
    }
  }

  float dist[filas][tags + 1];
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j <= tags; j++) {
      dist[i][j] = 0;
    }
  }

  for (int j = 0; j < columnas - 1; j++) {
    cont1 = 0;
    cont2 = 0;
    cont3 = 0;
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    for (int i = 0; i < filas; i++) {
      if (matriz[i][4] == 1) {
        cont1++;
        sum1 = sum1 + matriz[i][j];
        centroid[0][j] = sum1 / cont1;
      }
      if (matriz[i][4] == 2) {
        cont2++;
        sum2 = sum2 + matriz[i][j];
        centroid[1][j] = sum2 / cont2;
      }
      if (matriz[i][4] == 3) {
        cont3++;
        sum3 = sum3 + matriz[i][j];
        centroid[2][j] = sum3 / cont3;
      }
    }
  }

  Serial.println("MATRIZ DE CENTROIDES");
  for (int i = 0; i < tags; i++) {
    for (int j = 0; j < columnas; j++) {
      Serial.print(centroid[i][j], 4);
      Serial.print(" ");
    }
    Serial.println(" ");
  }

  //Encontrar las distancias entre los centroides y entrenamiento para comparar su clasifica adecuadamente

  Serial.println(" ");
  Serial.println("MATRIZ DE SOURCE");
  for (int i = 0; i < filas; i++) { //Lee filas
    distancia_menor = 3000;
    for (int l = 0; l < tags; l++) {
      sumatoria = 0; //Encera variable sumatoria
      for (int j = 0; j < columnas - 1; j++) { //Lee columnas
        sumatoria = sumatoria + pow(matriz[i][j] - centroid[l][j], 2); //Calcula sumatoria de potencias
      }
      distancia = sqrt(sumatoria);
      if (distancia < distancia_menor) {
        distancia_menor = distancia;
        tag = centroid[l][columnas - 1];
      }
    }
    if (tag == matriz[i][columnas - 1]) {
      //      Serial.print(String(i) + ": ");
      //      Serial.println("D");
      drain++;
    } else {
      float matriz_s[source + tags][columnas];
      //      Serial.print(String(i) + ": ");
      //      Serial.println("S");
        if (source == 0) {
          for (int f = 0; f < tags; f++) {
            for (int d = 0; d < columnas; d++) {
              matriz_s[f][d] = centroid[f][d];
              Serial.print(matriz_s[f][d]);
              Serial.print(" ");
            }
            Serial.println(" ");
          }
        }
      for (int c = 0; c < columnas; c++) {
        matriz_s[source + tags][c] = matriz[i][c];
        Serial.print(matriz_s[source + tags][c]);
        Serial.print(" ");
      }
      Serial.println(" ");
      source++;
    }
  }
  
  Serial.println(" ");
  Serial.println("----------RESULTADOS----------");
  Serial.print("Datos en DRAIN: ");
  Serial.println(drain);
  Serial.print("Datos en SOURCE: ");
  Serial.println(source);
  Serial.println("------------------------------");

  return 0;
}
