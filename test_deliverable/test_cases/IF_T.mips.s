#######-- if_true --#######
if_true:
addiu $sp, $sp, 80
sw $fp, 76($sp)
move $fp, $sp
sw $s0, 0($fp)
sw $s1, 4($fp)
sw $s2, 8($fp)
sw $s3, 12($fp)
sw $s4, 16($fp)
sw $s5, 20($fp)
sw $s6, 24($fp)
sw $s7, 28($fp)
sw $s8, 32($fp)
swc1 $20, 36($fp)
swc1 $21, 40($fp)
swc1 $22, 44($fp)
swc1 $23, 48($fp)
swc1 $24, 52($fp)
swc1 $25, 56($fp)
swc1 $26, 60($fp)
swc1 $27, 64($fp)
swc1 $28, 68($fp)
swc1 $29, 72($fp)
swc1 $30, 76($fp)
li $t0, 1

move $8, $8
beq $t0, $0, L0
li $t0, 0

move $2, $8
move $sp, $fp
lw $fp, 76($sp)
addiu $sp, $sp, 80
j $31
nop
L0:
L1:
li $t0, 1

move $2, $8
move $sp, $fp
lw $fp, 76($sp)
addiu $sp, $sp, 80
j $31
nop
#######^^ if_true ^^#######
