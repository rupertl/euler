#!/usr/bin/Rscript --slave
# Plot output from the euler program
#
# usage: plot.R [pngfile]
#
# Will read input from stdin - expects the CSV format outputted by euler
# Will write a plot of the data to pngfile, or "euler.png" if not
# specified

# Load the lattice library for plotting data
if (! library(lattice, logical.return = TRUE))
{
  cat("Please install the lattice package from CRAN\n")
  q(status = 1)
}

# Set the output file
argv <- commandArgs(TRUE)
output <- if (length(argv) > 0 ) argv[1] else "euler.png"
png(output, 600, 600)

# Read the input from stdin - expects header line
euler <- read.csv("stdin", header = TRUE)
if (nrow(euler) == 0)
{
  cat("Please provide CSV input with a header row\n")
  q(status = 1)
}

# Do a x/y line plot for each solution,  x=input, y=time_ns
xyplot(time_ns~input|solution, data=euler, type='b',
       main=paste("Euler Problem", euler[["problem"]][1]),
       xlab="input", ylab="time (ns)")

# Write the output file
done <- dev.off()
cat("Written plot to", output, "\n")
