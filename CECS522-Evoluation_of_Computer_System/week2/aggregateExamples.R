# View data set mtcars
mtcars
aggregate(mtcars, by=list(mtcars$cyl), FUN=mean)
aggregate(mtcars, by=list(mtcars$cyl), FUN=mean)
aggregate(. ~ cyl, data = mtcars, mean)
aggregate(cbind(mpg, hp) ~ cyl, data = mtcars, mean)
aggregate(. ~ cyl+hp, data = mtcars, mean)
aggregate(cbind(mpg, disp) ~ cyl+hp, data = mtcars, mean)

# Examples of by function
by(mtcars[,1], mtcars[,2], summary)
by(mtcars[,1], mtcars[,2], mean)
by(mtcars[,1:3], mtcars[,2], summary)
by(mtcars[,c(1,3)], mtcars[,2], summary)
by(mtcars, mtcars[,2], function(x)lm(mpg ~ hp, data=x))


