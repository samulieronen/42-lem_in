#!/bin/bash
echo "Reloading lem-in with test.txt"
make lemin && clear && ./lem-in < test.txt
