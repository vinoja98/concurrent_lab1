## compile serial.c
gcc serial.c -o serial -lm

## compile one_mutex_lock.c
gcc one_mutex_lock.c -o one_mutex_lock -lpthread -lm

## run executable
./serial
</br>
./one_mutex_lock
