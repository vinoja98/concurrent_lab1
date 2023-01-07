## compile serial.c
gcc serial.c -o serial -lm
gcc one_mutex_lock.c -o one_mutex_lock -lpthread -lm
gcc read_write.c -o rw -lm -lpthread

## run executable
./serial
./one_mutex_lock
./rw
