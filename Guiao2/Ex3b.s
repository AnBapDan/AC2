.equ RESET_CORE_TIMER,12
.equ READ_CORE_TIMER,11
.equ PUT_CHAR,3
.equ PRINT_INT,6
.equ K, 20000

.data
.text
.globl main

main:   lui $t1,0xBF88

while : lw $t2,0x6050($t1)
        li $v0,READ_CORE_TIMER 				  # while (1) {
        syscall 					              #
        blt $v0,10000000,while
        li $v0,RESET_CORE_TIMER
        syscall

        addi $t3,$t2,1

        li $t0,1000
        div $a0,$t0,$t3

        jal delay

        andi $a0,$t2,0x0000000F
        li $a1,0x00040002
        li $v0,PRINT_INT
        syscall

        j while
        jr $ra

delay: addiu $sp, $sp, -8
       sw $ra, 0($sp)
       sw $a0, 4($sp)
for:   ble $a0, $0, endfor
       li $v0,RESET_CORE_TIMER			  #
       syscall 					              # resetCoreTimer();
while1: 	li $v0,READ_CORE_TIMER 		  	#
        syscall 					            #
        blt $v0, K ,while1				      # while(readCoreTimer() < K);
        addi $a0, $a0, -1
        j for
endfor:
        lw $ra, 0($sp)
        lw $a0, 4($sp)
        addiu $sp, $sp, 8
        jr $ra
