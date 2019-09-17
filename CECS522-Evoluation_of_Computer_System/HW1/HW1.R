# Load data set
data <- read.csv("HW1/Neumeric-Weather-Data.csv", header=T)
# Remova NA values 
data <- na.omit(data)
# Drop X column 
data <- data[,-1]

# View all dataset
#View(data[,-1])

# Build PCA 
myPrinComp <- princomp(data)

# Task1: Give the weights for characteristic equations for new principle components.
print(myPrinComp)

# Print Proportion of Variance
# Task2: How much variation is explained by each of the new principle components?
PoV <- myPrinComp$sdev^2/sum(myPrinComp$sdev^2)
print(PoV)

# Print summary 
# Task3: How many new principle components should be considered to account for 80% 
# variation in the original data? (Please observe Cumulative Proporion)
summary(myPrinComp)
plot(myPrinComp, type="l")

# Print data set
cbind(data[1:4],myPrinComp$scores[,1:4])

