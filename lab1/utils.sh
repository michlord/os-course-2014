#!/bin/bash

function pause(){
    read -p "$*"
}

pause_msg="Press any key to continue..."

function generic_pause(){
    pause "${pause_msg}"
}