## compile serial.c
gcc serial.c -o serial -lm

## run executable
./serial

## compile read_write_lock.c
gcc read_write_lock.c -o read_write_lock -lpthread -lm

## run executable
./read_write_lock
