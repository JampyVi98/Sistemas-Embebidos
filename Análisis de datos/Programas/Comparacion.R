#Librerías utilizadas
library(caTools)
library(class)
library(e1071)
set.seed(169)

#Cargar base de datos al entorno de R
datos=read.csv("datos.csv",header =TRUE, sep = ";")
split=sample.split(datos$LABEL,SplitRatio = 0.80)
training_set=subset(datos,split==TRUE)
test_set=subset(datos,split==FALSE)

#########CLASIFICADOR KNN CON VALOR DE TURBIDEZ##########
y_pred = knn(train = training_set[,-5],
             test = test_set[,-5],
             cl = training_set[,5],
             k = 3)
cm_knn = table(test_set$LABEL,y_pred, dnn = c("Actual", "Predicción"))
round(prop.table(cm_knn)*100, 2) #Representado en porcentaje

#########CLASIFICADOR KNN SIN VALOR DE TURBIDEZ##########
y_pred = knn(train = training_set[,2:4],
             test = test_set[,2:4],
             cl = training_set[,5],
             k = 3)
cm_knn = table(test_set$LABEL,y_pred, dnn = c("Actual", "Predicción"))
round(prop.table(cm_knn)*100, 2) #Representado en porcentaje

#########CLASIFICADOR BAYESIANO##########
#Convertir a factor la etiqueta

training_set$LABEL = factor(training_set$LABEL, levels = c(1,2,3))

#modelo

class_bayes = naiveBayes(x= training_set[,-5], y = training_set[,5])
y_pred = predict(class_bayes, newdata = test_set[,-5])

class_bayes = naiveBayes(x = training_set[,-5], y = training_set[,5])
y_pred = predict(class_bayes, newdata = test_set[,-5])

#MATRIZ DE CONFUSION
cm_bay = table(test_set$LABEL, y_pred, dnn = c("Actual", "Predicción"))
cm_bay
############DEDUCCIONES A PARTIR DE LA MATRIZ DE CONFUSION#############
#Sensibilidad y Rendimiento del clasificador KNN
round(prop.table(cm_knn)*100, 2) #Representado en porcentaje
33.05+30.51+30.51 #Eficiencia del 94.07%
round(prop.table(cm_knn, 1)*100, 2) #Representado en porcentaje por filas
0+7.69+10.0 #Taza de error de 17.69%
100 - 17.69 #Rendimiento de 82.31%

#Sensibilidad y Rendimiento del clasificador Bayesiano
round(prop.table(cm_bay)*100, 2) #Representado en porcentaje
31.36+31.36+33.9 #96.62%
round(prop.table(cm_bay, 1)*100, 2) #Representado en porcentaje por filas
5.13+5.13+0 #Taza de error de 10.26%
100 - 10.26 #Rendimiento de 89.74%
