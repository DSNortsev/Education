data = read.table("/home/dmitry/git/Education/CECS522-Evoluation_of_Computer_System/HW3/dataset.txt", header = T)
X1 = data$Bytes_unix
Y1 = data$Time_unix
X2 = data$Bytes_argus
Y2 = data$Time_argus

# Task1: Give the coefficients of linear regression models for both the operating systems.
model1=lm(Y1~X1)
summary(model1)
coefficients(model1)

model2=lm(Y2~X2)
summary(model2)
coefficients(model2)


# Task2: Draw the plot linear regression model and the data points for both the operating systems.
plot(Y1~X1)
abline(model1)

plot(Y2~X2)
abline(model2)

# Task3: Write the equations of linear models for both the operating systems.
# y^ = b0 + b1Xi

# Task4:	Give the residual errors for both models.
summary(model1)
model1$residuals

summary(model2)
model2$residuals

# Task5: Give R2 values for both the models. Which model is more accurate?
summary(model1)$adj.r.squared
summary(model2)$adj.r.squared


# Task6: Draw four visual test verification graphs for both the linear regression models. 
layout(matrix(1:4,2,2)) 
plot(model1) 
