# TAS1:Remove species column from data set
short_data <- iris[,-5]
short_data

head(short_data)

# View structure of dataet
#str(short_data)

# view statistical summary of dataset
#summary(iris)

# Add iris classes
short_data.class <- iris[,"Species"]

# Function to normalize data
normalize <- function(x){
  return ((x-min(x))/(max(x)-min(x)))
}
head(short_data)
short_data$Sepal.Length<- normalize(short_data$Sepal.Length)
short_data$Sepal.Width<- normalize(short_data$Sepal.Width)
short_data$Petal.Length<- normalize(short_data$Petal.Length)
short_data$Petal.Width<- normalize(short_data$Petal.Width)
head(short_data)

# TASK2: Aplly k-means algorithm with no. of clusters=3
result<- kmeans(short_data,3)

# Task3: Append the cluster number to each row of data (Short-Data).
short_data <- cbind(short_data, result$cluster)
# Task4: Display the aggregate data (Short-Data) with cluster number.
short_data_mean <- aggregate(short_data,by=list(result$cluster),FUN=mean)
# Task5: Calculate “within group sum of the squares” for the above clustering
# Sum of squares for Sepal.Length:
Sepal.Length_1_mean <- (short_data$Sepal.Length - short_data_mean$Sepal.Length[short_data_mean$`result$cluster` == 1])^2
Sepal.Length_2_mean <- (short_data$Sepal.Length - short_data_mean$Sepal.Length[short_data_mean$`result$cluster` == 2])^2
Sepal.Length_3_mean <- (short_data$Sepal.Length - short_data_mean$Sepal.Length[short_data_mean$`result$cluster` == 3])^2
sum(Sepal.Length_1_mean,Sepal.Length_2_mean,Sepal.Length_3_mean)

# Sum of squares for Sepal.Width:
Sepal.Width_1_mean <- (short_data$Sepal.Width - short_data_mean$Sepal.Width[short_data_mean$`result$cluster` == 1])^2
Sepal.Width_2_mean <- (short_data$Sepal.Length - short_data_mean$Sepal.Width[short_data_mean$`result$cluster` == 2])^2
Sepal.Width_3_mean <- (short_data$Sepal.Length - short_data_mean$Sepal.Width[short_data_mean$`result$cluster` == 3])^2
sum(Sepal.Width_1_mean,Sepal.Width_2_mean, Sepal.Width_3_mean)

# Sum of squares for Petal.Length:
Petal.Length_1_mean <- (short_data$Petal.Length - short_data_mean$Petal.Length[short_data_mean$`result$cluster` == 1])^2
Petal.Length_2_mean <- (short_data$Sepal.Length - short_data_mean$Petal.Length[short_data_mean$`result$cluster` == 2])^2
Petal.Length_3_mean <- (short_data$Sepal.Length - short_data_mean$Petal.Length[short_data_mean$`result$cluster` == 3])^2
sum(Petal.Length_1_mean,Petal.Length_1_mean,Petal.Length_3_mean)

# Sum of squares for Petal.Width:
Petal.Width_1_mean <- (short_data$Petal.Width - short_data_mean$Petal.Width[short_data_mean$`result$cluster` == 1])^2
Petal.Width_2_mean <- (short_data$Petal.Width - short_data_mean$Petal.Width[short_data_mean$`result$cluster` == 2])^2
Petal.Width_3_mean <- (short_data$Petal.Width - short_data_mean$Petal.Width[short_data_mean$`result$cluster` == 3])^2
sum(Petal.Width_1_mean,Petal.Width_2_mean,Petal.Width_3_mean)
