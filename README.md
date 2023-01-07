## compile serial.c
gcc serial.c -o serial -lm
gcc one_mutex_lock.c -o one_mutex_lock -lpthread -lm

## run executable
./serial
./one_mutex_lock
