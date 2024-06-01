#!/bin/bash

if ! ls org/*.org 1> /dev/null; then echo -e "\n-----ERROR-----\n\nThere is no original songs in \"org/\" directory, \nplease download \"data/\" dir and run ./nx prog to extract necessary music data\n\n--------------\n" && exit; fi

org_names=($(ls org/))

for i in "${!org_names[@]}"; do ./org2xm_exec org/${org_names[i]} ./org2xm/ORG210EN.DAT; done
mv org/*.xm xm/
