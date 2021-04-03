### a:

  g++ td4a.cpp PosixThread.cpp chrono.cpp timespec.cpp -o td4a.rpi2 -lpthread 
  
  ./td4a.rpi2 "6" "2"
  
### result:

  Counter=2700.000000
  
  time is 50 s, 16021769 ns 这意味着创建了50个线程，nLoops = 54, nTask = 50, 我也不明白为何加了48
