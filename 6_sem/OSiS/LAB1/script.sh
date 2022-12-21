#! /usr/bin/bash

function show_user_processes()
{
 USER_NAME=$1
 id $USER_NAME &> /dev/null
 if [ "$?" == "0" ]
 then
  ps -u $USER_NAME -o user,pid,command,%mem,time --sort $2 | head -n 6 | tee $3
 else
  echo "the user $USER_NAME does not exist" | tee $3
 fi
}

show_user_processes $1 $2 $3
# username, sort by (user, pid, etc.), where to save(file.txt)
