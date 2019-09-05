# Basic list functions in R

fruits <- c("apple", "banana", "orange")
games <- c("football", "baseball", "basketball")
numbers <- c(2, 4, 5, 6, 7)

items <- list(fruits, games, numbers)

items
items[[1]]
items[[1]][2]
items[[2]][2]

lapply(items, length)
lapply(items, class)
lapply(items, mean)
summary(items)
str(items)
