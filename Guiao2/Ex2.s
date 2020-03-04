    .equ RESET_CORE_TIMER,12
    .equ READ_CORE_TIMER,11
    .equ PUT_CHAR,3
    .equ PRINT_INT,6
    .equ K, 20000
    .data
    .text
    .globl delay


delay: addiu $sp, $sp, -8
       sw $ra, 0($sp)
       sw $a0, 4($sp)
for:   ble $a0, $0, endfor
       li $v0,RESET_CORE_TIMER			  #
       syscall 					              # resetCoreTimer();
while: 	li $v0,READ_CORE_TIMER 		  	#
        syscall 					            #
        blt $v0, K ,while				      # while(readCoreTimer() < K);
        addi $a0, $a0, -1
        j for
endfor:
        lw $ra, 0($sp)
        lw $a0, 4($sp)
        addiu $sp, $sp, 8
        jr $ra
