#Install and load ellipse package
library("ellipse")
# Step 1: Reading the data, Set the current working directory to the location where "weather-data-set.csv" is stored
data <- read.csv("weather-data-set.csv", header=T)

#View the data set
View(data)

#Step 2: Identify numeric columns
numeric <- c("MinTemp", "MaxTemp", "Rainfall", "Evaporation",
                 "Sunshine", "WindGustSpeed", "WindSpeed9am", "WindSpeed3pm",
                 "Humidity9am", "Humidity3pm", "Pressure9am", "Pressure3pm",
                 "Cloud9am", "Cloud3pm", "Temp9am", "Temp3pm")

#take a subset of data for correlation analysis
rows <- nrow(data)
input <- sample(nrow(data), 0.9*rows)

#Step 3: Perform correlation analysis
data1 <- cor(data[input, numeric], use="pairwise", method="pearson")

#Print unsorted results
print(data1)

# Sort the results
dataSorted <- order(data1[1,])
dataFinal <- data1[dataSorted, dataSorted]

#Step 4: Print the sorted correlation data

print(dataFinal)

#Step 5: Display the correlation graphically

plotcorr(dataFinal, col=colorRampPalette(c("green", "white", "purple"))(10)[6*dataFinal + 6])
title(main="Correlation weather-data-set.csv using Pearson")

