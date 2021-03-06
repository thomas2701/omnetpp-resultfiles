require(omnetpp)
dataset <- loadDataset(system.file('extdata/PureAloha1-0.vec', package='omnetpp'),
             add('vector', select='name("channel utilization")'))

ops <- list(quote(add(1)),
            quote(compare(0,1,-1,2)),
            quote(crop(0, 1)),
            quote(difference()),
            quote(diffquot()),
            quote(divideBy(2)),
            quote(divtime()),
            quote(expression('yprev')),
            quote(integrate('linear')),
            quote(lineartrend(1)),
            quote(mean()),
            quote(modulo(2)),
            quote(movingavg(0.3)),
            quote(multiplyBy(2)),
            quote(removerepeats()),
            quote(slidingwinavg(10)),
            quote(substractFirstValue()),
            quote(sum()),
            quote(timeavg('linear')),
            quote(timediff()),
            quote(timeshift(dt=0.1)),
            quote(timetoserial()),
            quote(timewinavg(10)),
            quote(winavg(10)))
            
testApply <- function (dataset, op) {
  o <- op
  eval(substitute(loadVectors(dataset, NULL, apply(o))))
}

testCompute <- function (dataset, op) {
  o <- op
  eval(substitute(loadVectors(dataset, NULL, compute(o))))
}

for (op in ops) {
  print(testApply(dataset, op))
  print(testCompute(dataset, op))
}

f <- function () {
    x <- 1
    print(loadVectors(dataset, NULL, compute(add(x)), apply(mean())))
}

f()
