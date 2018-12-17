#!/bin/bash
try() {
  expected="$1"
  input="$2"

  ./9cc "$input" > tmp.s
  gcc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" != "$expected" ]; then
    echo "$input expected, but got $actual"
    exit 1
  fi
}

try 0 0
try 42 42
try 21 '5+20-4'
try 41 ' 12 + 34 - 5 '
try 47 "5+6*7"
try 15 "5*(9-6)"
try 4 "(3+5)/2"
try 2 "a=2"
try 5 "a=2+3"
try 3 "g=1+2"
try 2 "a=2*1"
try 5 "a=2+3;a"
try 5 "a=b=5;b"
try 10 "a=5+1;b=3+1;a+b"
try 15 "a=2+4;b=1+9-1;c=a+b;"
try 0 "10 == 11"
try 1 "1 != 0"
try 1 "a=3; a != 4"
try 0 "a=3; a != 3"
try 0 "(1+2)!= 3"
try 1 "(1*2) == (1+1)"
echo OK
