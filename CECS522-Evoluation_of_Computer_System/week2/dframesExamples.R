# Basic file loading and processing dframes operations
# Set the working directory to directory where trees.txt file is located
data <- read.table("trees.txt", header=T)
data
head(data)
tail(data)
data[3,]
data[3,2]
class(data[3,])
class(data[3,2])

data[order(data$Girth),]

data[rev(order(data$Girth)),]

na.omit(data)

unique(data)


