## compile serial.c
gcc serial.c -o serial -lm

## compile one_mutex_lock.c
gcc one_mutex_lock.c -o one_mutex_lock -lpthread -lm

## compile read_write_lock.c
gcc read_write_lock.c -o read_write_lock -lpthread -lm

## run executable

./serial
</br></br>
./one_mutex_lock
</br></br>
./read_write_lock.c