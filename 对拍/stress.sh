
#!/bin/bash

g++ gen.cpp -std=c++20 -O2 -o gen || exit 1
g++ std.cpp -std=c++20 -O2 -o std || exit 1
g++ my.cpp  -std=c++20 -O2 -o my  || exit 1

i=0
while true; do
    i=$((i + 1))
    echo "Testing $i"

    echo "Generating..."
    ./gen > in.txt || break

    echo "Running std..."
    ./std < in.txt > std.txt || break

    echo "Running my..."
    ./my < in.txt > my.txt || break

    echo "Comparing..."
    if diff -w std.txt my.txt > /dev/null; then
        continue
    fi

    echo "===== Input ====="
    cat in.txt
    echo "===== Std ====="
    cat std.txt
    echo "===== My ====="
    cat my.txt
    break
done

echo "Stopped."

#chmod +x stress.sh   获得权限
# ./stress.sh          执行