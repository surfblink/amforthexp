# -----------------------------------------------------------------------------
  CODEWORD "ashift", ASHIFT
# ( x n -- x >> n  ) arithmetic shift x right n bits (sign fill)
# -----------------------------------------------------------------------------
  ldm psp!, {r0}
  asr r0, r0, tos
  movs tos, r0
NEXT
