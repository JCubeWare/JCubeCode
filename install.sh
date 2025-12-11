#!/bin/bash

           #################################
          ###                          #####
        ###     ######################### ##
      ###     ###                   ##### ##
    ####     ########################  ## ##
  ####                          ###    ## ##
####                          ####     ## ##
################################ #     ## ##
##                     #     ##  #  ## ## ##
##                     #     ##  #  ## ## ##
##                     #     ##  #  ##### ##
##                     #     ##  # ###### ##
##                     #     ##  # #  ### ##
##                     #     ##  ###  ### ##
##                     #     ##  ##    ## ##
##########             #     ##  ##    #  ##
##       #             #     ##  ##      ###
##       #             #     ##  #      ### 
##       #             #     ##       ###   
##       ###############     ##     ####    
##                           ##   ####      
##                           ## ####        
##                           #####          
################################            

############# [J][C]ube[W]are ##############
#   Be responsible. Code for the future.   #
#         (c) 2025-2025, JCubeWare         #
############################################


##====[ VARIABLES ]====##

Packages_APT=(
	"make"
	"build-essential" 
	"valgrind"
	"nasm"
)

##====[ SCRIPT ]====##

echo '[]====[ [J][C]ube[C]ode ]====[]\n'

if [[ $EUID == 0 ]]; then
   echo "[! ERR !] This script must be run as the wanted user"
   exit 1
fi

echo "[! ERR !] Enter the sudo password:" 
sudo test

echo '##====[ STAGE 1: SETUP ]====##'
echo '[@] Installing all the required tools.'

sudo apt update
for Package in "${Packages_APT[@]}" ; do
	sudo apt install --yes $Package
done
sudo apt upgrade
echo '[@] Installing done!'

echo '##====[ STAGE 2: BUILD / INSTALL ]====##'
echo '[@] Building the library itself.'
cd Library
sudo make oobe
cd ..
echo '[OK] Library done!'
echo '[OK] Building the manager!'
cd Manager
sudo make oobe
sudo cp _.build/Linux/jcc_0.0.1 /usr/bin/jcc
sudo mkdir ~/.JCubeCode
sudo cp -r ProjectExample/. ~/.JCubeCode/Example/
cd ..
echo '[@] Installing done!'
