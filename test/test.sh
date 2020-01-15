[[ $debug = true ]] && set -x

versions=("$versions")
expected_output=
pass=true
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
epsilon=0.1

for version in ${versions[@]}
do
    echo -n "$version .. "
    output=$(./stencil-$version 2>&1 >/dev/null | egrep -o '[0-9]+\.[0-9]+')
    if [[ -z "$expected_output" ]]
    then
        expected_output=$output
    fi


    if [[ $(echo "print((1.0-$epsilon)*${expected_output}<=$output<=(1.0+$epsilon)*$expected_output)" | python)  != "True" ]]
    then
        echo "${red}NOK$reset"
        echo "$green+expected $expected_output$reset"
        echo "$red-actual $output$reset"
        pass=false
    else
        echo "${green}OK$reset"
    fi
done


if [[ $pass = "false" ]]
then
    exit 1
fi
