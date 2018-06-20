#!/bin/bash

RED="\e[31m"
NONE="\e[0m"

CA_C="FR" # country
CA_ST="france" # state
CA_L="Paris" # city
CA_O="MyCompagny" # Organisation
CA_OU="DevLab" # Organisation Unit
CA_CN="ox223252" # Comon Name

SR_C="FR"
SR_ST="france"
SR_L="Paris"
SR_O="MyCompagny"
SR_OU="DevLab_Server"
SR_CN="ox223252_Server"

CL_C="FR"
CL_ST="france"
CL_L="Paris"
CL_O="MyCompagny"
CL_OU="DevLab_Client"
CL_CN="ox223252_Client"


printf "$RED GCA: $NONE\n"
openssl req -new -x509 -extensions v3_ca -keyout ssl/ca.key -out ssl/ca.crt -subj "/C=$CA_C/ST=$CA_ST/L=$CA_L/O=$CA_O/OU=$CA_OU/CN=$CA_CN"

printf "$RED Server: $NONE\n"
openssl genrsa -out ssl/server.key 2048
openssl req -out ssl/server.csr -key ssl/server.key -new -subj "/C=$SR_C/ST=$SR_ST/L=$SR_L/O=$SR_O/OU=$SR_OU/CN=$SR_CN"
openssl x509 -req -in ssl/server.csr -CA ssl/ca.crt -CAkey ssl/ca.key -CAcreateserial -out ssl/server.crt

printf "$RED Client: $NONE\n"
openssl genrsa -out ssl/client.key 2048
openssl req -out ssl/client.csr -key ssl/client.key -new -subj "/C=$CL_C/ST=$CL_ST/L=$CL_L/O=$CL_O/OU=$CL_OU/CN=$CL_CN"
openssl x509 -req -in ssl/client.csr -CA ssl/ca.crt -CAkey ssl/ca.key -CAcreateserial -out ssl/client.crt

