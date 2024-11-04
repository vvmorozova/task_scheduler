# Задание

Реализовать класс планировщик задач. В классе должен быть 
метод Add(std::function task, std:time_t timestamp), параметры: 
task -- задача на выполнение;
timestamp -- время, не раньше которого задача должна быть выполнена.

# Как собирать

```
mkdir build && cd build
```
## библиотеку

```
cmake -DBUILD_EXECUTABLE=OFF ..
make
```
## исполняемый файл

```
cmake -DBUILD_SHARED_LIBS=OFF -DBUILD_EXECUTABLE=ON ..
make
```
# Как запустить