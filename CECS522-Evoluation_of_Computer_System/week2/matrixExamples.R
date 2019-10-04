# Basic matrix functions in R
x <- matrix(c(1:9), nrow=3)
x
class(x)
attributes(x)

vec <- c(1:10)
is.matrix(vec)
y <- matrix(vec, byrow=T, nrow=2)
y

dim(vec) <- c(5,2)
is.matrix(vec)

vec

newVec <- t(vec)
newVec

# Naming the rows
rownames(x) <- rownames(x, do.NULL=FALSE, prefix="row.")
x

#naming the columns
colnames <- c("c1", "c2", "c3")

colnames(x) <- colnames

x

# Calculations for row and column
rowSums(x)
apply(x, 1, sum)

colSums(x)
apply(x, 2, sum)

rowMeans(x)
apply(x, 1, mean)


colMeans(x)
apply(x, 2, mean)

# Adding rows and columns

x <- rbind(x, apply(x, 2, mean))
x <- cbind(x, apply(x, 1, var))
x


# Check
is.array(x)
is.matrix(x)