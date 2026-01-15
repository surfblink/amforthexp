
@ -----------------------------------------------------------------------------
  CODEWORD "2rot", 2ROT
  # ( p3 p2 p1 -- p2 p1 p3 ) STACK: rotate p3 to be TOS
@ -----------------------------------------------------------------------------
  popnos r0 @ p2
  popnos r1 @ p3
  pushnos r0 @ p2
  pushnos tos @ p1
  movs tos, r1 @ p3
NEXT
