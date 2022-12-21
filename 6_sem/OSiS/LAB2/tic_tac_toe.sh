#! /usr/bin/bash

PLAYER1="X"
PLAYER2="O"

TURN=1
IS_GAME_ON=true

SPOTS=( 1 2 3 4 5 6 7 8 9 )

show_game_title()
{
  echo " T | I | C "
  echo "-----------"
  echo " T | A | C "
  echo "-----------"
  echo " T | O | E "
 sleep 1.2
}

print_board()
{
  echo ""
  echo ""
  echo $"Turn: $TURN"
  echo " ${SPOTS[6]} | ${SPOTS[7]} | ${SPOTS[8]} "
  echo "-----------"
  echo " ${SPOTS[3]} | ${SPOTS[4]} | ${SPOTS[5]} "
  echo "-----------"
  echo " ${SPOTS[0]} | ${SPOTS[1]} | ${SPOTS[2]} "
  echo "============="
}


player_pick()
{
 if [[ $(($TURN % 2)) == 1 ]]
 then
  SYMBOL=$PLAYER1
  echo -n "PLAYER 1 PICK A SPOT: "
 else
  SYMBOL=$PLAYER2
  echo -n "PLAYER 2 PICK A SPOT: "
 fi

 read PLAYER_SPOT
 SPACE=${SPOTS[($PLAYER_SPOT - 1)]}

 if [[ ! $PLAYER_SPOT =~ ^-?[0-9]+$ ]] || [[ ! $SPACE =~ ^[0-9]+$ ]]
 then
  echo "The spot is not valid"
  player_pick
 else
  SPOTS[($PLAYER_SPOT - 1)]=$SYMBOL
  ((TURN=TURN+1))
 fi
 SPACE=${SPOTS[($PLAYER_SPOT - 1)]} 
}

check_match()
{
  if  [[ ${SPOTS[$1]} == ${SPOTS[$2]} ]]&& \
      [[ ${SPOTS[$2]} == ${SPOTS[$3]} ]]; then
    IS_GAME_ON=false
  fi
  if [ $IS_GAME_ON == false ]; then
    if [ ${SPOTS[$1]} == $PLAYER1 ];then
      echo "Player 1 wins!"
      return
    else
      echo "Player 2 wins!"
      return
    fi
  fi
}

check_winner()
{
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 0 1 2
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 3 4 5
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 6 7 8
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 0 4 8
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 2 4 6
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 0 3 6
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 1 4 7
  if [ $IS_GAME_ON == false ]; then return; fi
  check_match 2 5 8
  if [ $IS_GAME_ON == false ]; then return; fi

  if [ $TURN -gt 9 ]; then
    $IS_GAME_ON=false
    echo "Its a draw!"
  fi
}

show_game_title
print_board
while $IS_GAME_ON
do
  player_pick
  print_board
  check_winner
done
