# Basic functions in R
abs(-3.4) 
sqrt(35)
ceiling(6.4) 
floor(6.4) 
trunc(79.66)
round(35.789, 2)
log(64, base=2) 
exp(2)

# Complex numbers in R
 y <- 3.5 - 7i
 Re(y)
 Im(y)
 Mod(y)
 Conj(y)
 is.complex(y)
 as.complex(4)
 
 # How to get the quotient
 
 115 %/% 10
 
 # How to get the remainder
 
 115 %% 10
 
 # Statistical functions
 x <- c(1:10)
 
 mean(x)
 max(x)
 min(x)
 sd(x)
 var(x)
 median(x)
 
# probability functions
# add d= density;  p=distribution function; q = quantile function; r = random generation
rbinom(100, 32, .5)
rnorm(100, 32, .5)
