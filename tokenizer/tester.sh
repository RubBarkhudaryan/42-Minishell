#!/bin/bash

while IFS= read -r cmd; do
    echo ">>> $cmd"
    eval "$cmd"
    echo "-----------------------------"
done <<'EOF'
echo
echo echo
eCho 
eChO
eCHO
ECHO
echo $
echo "$"
echo '$'
echo nenie_iri
echo nenie iri
echo 'nenie_iri'
echo "nenie_iri"
echo -n
echo -n nenie_iri
echo -nn nenie_iri
echo -n -n -n nenie_iri
echo "-n" nenie_iri
echo -n"-n" nenie_iri
echo "-nnnn" nenie_iri
echo "-n -n -n"-n nenie_iri
echo "-n -n" nenie_iri
echo "-n '-n'" nenie_iri
echo $USER
echo "$USER"
echo '$USER'
echo "'$USER'"
echo " '$USER' "
echo nenie_iri"$USER"
echo nenie_iri"'$USER'" ' $USER '
echo "nenie_iri"   "$USER"    "$USER"
echo '              $USER          '
echo               nenie_iri "$USER"            "$USER"nenie_iri
echo ''''''''''$USER''''''''''
echo """"""""$USER""""""""
echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
echo $USER '' $USER $USER '' $USER '' $USER -n $USER
echo ' \' ' \'
echo "$USER""$USER""$USER"
echo nenie"$USER"iri
echo '$USER' "$USER" "nenie \' iri"
echo $USER " "
echo "$USER""Users/$USER/file""'$USER'"'$USER'
echo "$USER$USER$USER"
echo '$USER'"$USER"'$USER'
echo '"$USER"''$USER'"""$USER"
echo " $USER  "'$PWD'
echo $USER=4
echo $?
echo $USER213
echo "$USER=12$USER"
echo $PWD
echo $PWD/file
echo "$PWD/file"
echo "nenie_iri" "nenie_iri$USER" ... "$USER"
echo test      tout
EOF
