#Plotting for R
png("weierstrass.png")
data <- read.table("./weierstrass.csv",sep=",")
plot(0, type = "n", main = "Plot Title", xlab = "Number of Evaluations", ylab = "Fitness", xlim = c(0,20480) )
grid() # add grid
lines(data[,3], data[,4], lty = 1) #draw first dataset
lines(data[,3], data[,5], lty = 2) #draw second dataset
lines(data[,3], data[,6], lty = 3) #draw third dataset
legend("topright", c("Best Fitness", "Average", "StdDev"), lty = c(1, 2, 3) )
