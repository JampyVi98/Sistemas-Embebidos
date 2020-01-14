####librerias
library(knitr)
library(ROCR)
library(e1071)
library(caTools)
library(nnet)
library(scales)
library(mlbench)
library(caret)
library(class)
datos=read.csv("datos.csv",header=TRUE ,sep=",")
#observar los datos
View(datos)
#aleatoriedad de base de datos
set.seed(123)
############# normalizar con formula
##datos_norm <- as.data.frame(apply(datos[, 1:4], 2, function(x) (x - min(x))/(max(x)-min(x))))
##datos_norm$Label <- datos$Label
##View(datos_norm)

########## 
split= sample.split(datos$Label, SplitRatio=0.80)
training_set= subset(datos,split==TRUE)
test_set= subset(datos,split==FALSE)

training_set$ï..Turbidez=rescale(training_set$ï..Turbidez,to=c(0,1))
training_set$Temperatura=rescale(training_set$Temperatura,to=c(0,1))
training_set$TDS=rescale(training_set$TDS,to=c(0,1))
training_set$PH=rescale(training_set$PH,to=c(0,1))
test_set$ï..Turbidez=rescale(test_set$ï..Turbidez,to=c(0,1))
test_set$Temperatura=rescale(test_set$Temperatura,to=c(0,1))
test_set$TDS=rescale(test_set$TDS,to=c(0,1))
test_set$PH=rescale(test_set$PH,to=c(0,1))
training_set$Label=factor(training_set$Label,levels=c(1,2,3))
test_set$Label=factor(test_set$Label,levels=c(1,2,3))
                      
######################## K-NN #######################
training_set

y_pred=knn(train = training_set[,-5],
           test =test_set[,-5],
           cl=training_set[,5],
           k=3)
cm=table(test_set$Label,y_pred)
cm
#################BAYESIANO#######################

training_set$Label=factor(training_set$Label,levels = c(1,2,3))
training_set=training_set[,-6]
class_bayes=naiveBayes(x=training_set[,-5],
                       y=training_set[,5])
y_pred=predict(class_bayes,newdata = test_set[,-5])
cm=table(test_set$Label,y_pred)
cm

###############################REDUCIR LA BASE DE DATOS###################33
library(NoiseFiltersR)
cnn_training_set=CNN(training_set)
cnn_training_set
cnn_training_set=cnn_training_set$cleanData
########################k-nn con reduccion de datos#########################
y_pred=knn(train = cnn_training_set[,-5],
           test =test_set[,-5],
           cl=cnn_training_set[,5],
           k=3)
cm=table(test_set$Label,y_pred)
cm

################################# bayesiano con reduccion#############################3
class_bayes=naiveBayes(x=cnn_training_set[,-5],
                       y=cnn_training_set[,5])
y_pred=predict(class_bayes,newdata = test_set[,-5])
cm=table(test_set$Label,y_pred)
cm





















