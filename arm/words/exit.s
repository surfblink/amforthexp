# this is the xt that will be added by semicolon 
CODEWORD "(exit)", EXIT 
    pop {FORTHIP}
  NEXT

# this is the xt that will be added by exit
CODEWORD "exit", FINISH
# ( -- ) FLOW: exit word (instantly) 
    pop {FORTHIP}
  NEXT
