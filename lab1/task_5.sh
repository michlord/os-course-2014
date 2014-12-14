#!/bin/bash

ret_val=$(xeyes ; echo $?)
#kill it in a separate terminal
echo ${ret_val}
echo "whatever"
echo $?

# Po wykonaniu polecenia kod wyjscia zapisuje się w zmiennej $?.
# Zero oznacza poprawne zakończenie.
# Zakończenie sygnałem spowoduje że kod wyjście będzie niezerowy.
# Niektóre niezerowe wartości mają specjalne znaczenie:

# Przykładowo 130 oznacza, że proces został zabity za pomocą Ctrl-C.
