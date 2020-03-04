.equ RESET_CORE_TIMER,12
.equ READ_CORE_TIMER,11
.equ PUT_CHAR,3
.equ PRINT_INT,6

.data
.text
.globl main

main:   lui $t1,0xBF88
        lw $t2,0x6050($t1)

while : li $v0,READ_CORE_TIMER 				  # while (1) {
        syscall 					              #
        blt $v0,10000000,while

        move $t2,$a0
        li $a1,0x00040002
        li $v0,PRINT_INT
        syscall

        j while
        jr $ra
